//
// Created by alan2 on 25/02/2020.
//
#include "game/health.h"
#include "game/player/player.h"
#include "game/score.h"
#include "utils/colors.h"
#include <Windows.h>
#include <curses.h>
#include <game/battle.h>
#include <game/battle_menu.h>
#include <game/enemy.h>
#include <game/game_state.h>
#include <game/pause.h>
#include <game/store_menu.h>
#include <sound.h>
#include <stdlib.h>
#include <time.h>
#include <utils/render_graph.h>
#include <utils/sprite.h>
#include <utils/standby_window.h>

void draw_castle_begin(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{

    if (!(x >= 0 && y == 0 && character_to_draw == ' '))
    {
        wattron(window, COLOR_PAIR(CASTLE_COLOR_PAIR));
    }
}

bool can_enter_battle(int pos_y, int pos_x, game_state_t *state)
{
    if (pos_x == 0 && pos_y == 0)
    {
        return state->boss_defeated.boss3;
    }
    else if (pos_x == 1 && pos_y == 0)
    {
        return state->boss_defeated.boss2;
    }
    else if (pos_x == 1 && pos_y == 1)
    {
        return state->boss_defeated.boss1;
    }
    return true;
}

void draw_castle_end(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (!(x >= 0 && y == 0 && character_to_draw == ' '))
    {
        wattroff(window, COLOR_PAIR(CASTLE_COLOR_PAIR));
    }
}

void draw_graveyard_start(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    (void)y;
    (void)x;
    (void)character_to_draw;
    wattron(window, COLOR_PAIR(CASTLE_COLOR_PAIR));
}

void draw_graveyard_end(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    (void)y;
    (void)x;
    (void)character_to_draw;
    wattroff(window, COLOR_PAIR(CASTLE_COLOR_PAIR));
}

void draw_game_screen(WINDOW *game)
{
    wclear(game);

    draw_sprite(game, 33, 30, "map/BRIDGE.txt", NULL, NULL);

    draw_sprite(game, 20, 20, "map/STORE.txt", NULL, NULL);

    draw_sprite(game, 20, 60, "map/CHAPEL.txt", NULL, NULL);

    draw_sprite(game, 4, 50, "map/GRAVEYARD.txt", draw_graveyard_start, draw_graveyard_end);

    draw_sprite(game, 33, 70, "map/HOUSE.txt", NULL, NULL);

    draw_sprite(game, 4, 2, "map/CASTLE.txt", draw_castle_begin, draw_castle_end);

    wrefresh(game);
}

void start_game(int8_t slot)
{
    srand(time(NULL));
    render_graph_t *render_graph = create_new_graph();
    sound_t music                = create_sound();

    bool first_pass = true;

    char music_path[64];

    sprintf(music_path, "game/%d.ogg", rand() % 2 + 1);
    sound_open_file(music, music_path);
    set_loop(music, true);
    play_sound(music);
    set_volume(music, 40);

    health_t *player_health = start_health(add_child(render_graph->entry_point, NULL));

    score_t *score = start_score(add_next(player_health->health_node, NULL));

    WINDOW *game = newwin(getmaxy(stdscr) - 1, getmaxx(stdscr), 1, 0);

    player_t *player = create_player(game, player_health);

    render_node_t *game_screen_node = add_child(render_graph->entry_point, (draw_callback_c)draw_game_screen);
    game_screen_node->param         = game;

    render_node_t *player_render_node = add_child(game_screen_node, (draw_callback_c)draw_player);
    player_render_node->param         = player;

    render_node_t *store_screen = add_child(game_screen_node, (draw_callback_c)draw_store);
    store_t *store              = create_store(game, store_screen);

    render_node_t *battle_screen = add_child(game_screen_node, (draw_callback_c)draw_battle_screen);
    battle_t *battle             = create_battle_screen(game, battle_screen);

    nodelay(game, true);
    keypad(game, true);

    wbkgd(game, COLOR_PAIR(GAME_COLOR_PAIR));

    pause_menu_t *menu = create_pause_menu(game, add_child(render_graph->entry_point, NULL));

    game_state_t state;
    memset(&state, 0, sizeof(game_state_t));
    if (slot != -1)
    {
        bool success;
        state = load_game(slot, &success);
        if (success)
        {
            player->health->health     = state.health;
            player->health->max_health = state.max_health;
            get_inventory_from_game_state(player->inventory, &state);
        }
        else
        {
            state.max_health = player->health->max_health;
            state.health     = player->health->health;
            fill_game_state_inventory_data(&state, player->inventory);
            save_game(&state, slot);
        }
    }
    else
    {
        state.health = player->health->health;
        state.max_health = player->health->max_health;
        fill_game_state_inventory_data(&state, player->inventory);
    }

    while (1)
    {
        draw_render_graph(render_graph);
        wrefresh(game);
        int key = wgetch(game);
        if (store->should_show)
        {
            store->buy_menu->option = key;
            store_choice_e choice   = execute_store_menu(store->buy_menu);
            switch (choice)
            {

                case STORE_EXIT:
                    store->should_show               = false;
                    store->buy_menu->should_show     = false;
                    game_screen_node->require_redraw = true;
                    break;
                case STORE_BUY_POTION_LOW:
                    if (score->money < 50)
                    {
                        static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    else
                    {
                        score->money -= 50;
                        add_item(player->inventory, ITEM_POTION_LOW);
                        score->score_node->require_redraw = true;
                    }
                    break;
                case STORE_BUY_POTION_MEDIUM:
                    if (score->money < 100)
                    {
                        static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    else
                    {
                        score->money -= 100;
                        add_item(player->inventory, ITEM_POTION_MEDIUM);
                        score->score_node->require_redraw = true;
                    }
                    break;
                case STORE_BUY_ARMOR_LOW:
                    if (score->money < 40)
                    {
                        static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    else
                    {
                        score->money -= 40;
                        add_item(player->inventory, ITEM_ARMOR_LOW);
                        score->score_node->require_redraw = true;
                    }
                    break;
                case STORE_BUY_ARMOR_MEDIUM:
                    if (score->money < 80)
                    {
                        static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    else
                    {
                        score->money -= 80;
                        add_item(player->inventory, ITEM_ARMOR_MEDIUM);
                        score->score_node->require_redraw = true;
                    }
                    break;
                case STORE_BUY_POWER_LOW:
                    if (score->money < 40)
                    {
                        static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    else
                    {
                        score->money -= 40;
                        add_item(player->inventory, ITEM_POWER_LOW);
                        score->score_node->require_redraw = true;
                    }
                    break;
                case STORE_BUY_POWER_MEDIUM:
                    if (score->money < 90)
                    {
                        static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    else
                    {
                        score->money -= 90;
                        add_item(player->inventory, ITEM_POWER_MEDIUM);
                        score->score_node->require_redraw = true;
                    }
                    break;
                case STORE_NONE:
                    break;
            }
            if (key == 27)
            {
                store->should_show               = false;
                store->buy_menu->should_show     = false;
                game_screen_node->require_redraw = true;
            }
            continue;
        }
        if (battle->should_show)
        {
            if (battle->turn == true)
            {
                battle->battle_menu->option = key;
                battle_choice_e choice      = execute_battle_menu(battle->battle_menu);

                char player_attack[64];
                switch (choice)
                {
                    case BATTLE_EXIT:
                    {
                        int mon = score->money - 20;
                        if (mon < 0)
                        {
                            score->money = 0;
                        }
                        battle->should_show              = false;
                        battle->battle_menu->should_show = false;
                        game_screen_node->require_redraw = true;
                        first_pass                       = true;
                    }
                    break;
                    case BATTLE_ATTACK:
                    {
                        sound_t character_attack = create_sound();
                        sprintf(player_attack, "sfx/ataques/player_%d.ogg", 1);
                        sound_open_file(character_attack, player_attack);
                        int milliseconds = get_sound_milliseconds_duration(character_attack);
                        set_loop(character_attack, false);
                        play_sound(character_attack);
                        flash();
                        Sleep(milliseconds);
                        battle->enemy.health -= (int)(player->damage_multiplier * 10 * (rand() % 51 + 80) / 100);
                        battle->turn = false;
                        delete_sound(character_attack);
                    }
                    break;
                    case BATTLE_DEFENSE:
                        battle->turn = false;
                        break;
                    case BATTLE_MAGIC:
                        battle->turn = false;
                        break;
                    case BATTLE_NONE:
                    {
                        if (first_pass)
                        {
                            static const char *text[] = {"¡HAS SIDO EMBOSCADO!                            "};
                            standby_window_t *stdby_w =
                                create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                            draw_standby_window(stdby_w);
                            first_pass = false;
                        }
                        else if (battle->battle_menu->option == KEY_UP || battle->battle_menu->option == KEY_DOWN)
                        {
                            int current = battle->battle_menu->menu->current_choice;
                            switch (current)
                            {
                                case 0:
                                {
                                    static const char *text[] = {"Un ataque de daño medio, ¡Úsalo cuando quieras! "};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w);
                                }
                                break;
                                case 1:
                                {
                                    static const char *text[] = {"¡Un fuerte ataaque mágico!, pero necesita MP    "};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w);
                                }
                                break;
                                case 2:
                                {
                                    static const char *text[] = {"¡Cúbrete para recibir menos daño y recuperar MP!"};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w);
                                }
                                break;
                                case 3:
                                {
                                    static const char *text[] = {"Accede a tu inventario y usa uno de tus objetos "};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w);
                                }
                                break;
                                case 4:
                                {
                                    static const char *text[] = {"Es mejor aquí corrió que aquí murió...          "};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w);
                                }
                                break;
                            }
                        }
                    }
                    break;
                    default:
                        break;
                    case BATTLE_ITEM:
                        break;
                }
            }
            else
            {
                sound_t enemy_attack = create_sound();
                char rand_n[64];
                sprintf(rand_n, "sfx/ataques/enemy_%d.ogg", 1);
                sound_open_file(enemy_attack, rand_n);
                int milliseconds = get_sound_milliseconds_duration(enemy_attack);
                set_loop(enemy_attack, false);
                play_sound(enemy_attack);
                flash();
                Sleep(milliseconds);
                add_health(player_health,
                           -(int)(player->armor_multiplier * battle->enemy.power * (rand() % 51 + 80) / 100));
                score->score_node->require_redraw          = true;
                player_health->health_node->require_redraw = true;
                battle->turn                               = true;
                delete_sound(enemy_attack);
            }
            continue;
        }
        if (menu->should_show)
        {
            menu->option         = key;
            menu_choice_e choice = execute_pause_menu_action(menu);
            if (choice == MENU_NONE)
            {
                menu->pause_node->require_redraw = true;
            }
            if (choice == MENU_EXIT)
            {
                // delete_pause_menu(menu);
                break;
            }
            if (key == 27)
            {
                menu->pause_node->require_redraw = false;
                menu->should_show                = false;
                game_screen_node->require_redraw = true;
                continue;
            }
            switch (choice)
            {
                case MENU_RESUME:
                    menu->pause_node->require_redraw = false;
                    menu->should_show                = false;
                    game_screen_node->require_redraw = true;
                    break;
                case MENU_INVENTORY:
                    menu->should_show                                                            = false;
                    game_screen_node->require_redraw                                             = true;
                    add_node_at_end(render_graph, (draw_callback_c)draw_player_inventory)->param = player;
                    break;
                case MENU_SAVE:
                    // TODO guardar
                    break;
                default:
                    break;
            }
            continue;
        }
        if (key == 27) // menu
        {
            if (player->inventory->shown) // eliminar
            {
                hide_player_inventory(player);
                delete_last(render_graph);
                game_screen_node->require_redraw = true;
            }
            else
            {
                menu->pause_node->require_redraw = true;
                menu->option                     = 0;
                execute_pause_menu_action(menu);
                menu->should_show          = true;
                menu->menu->current_choice = 0;
            }
        }

        // se muestra el inventario, procesar para este ;)
        if (player->inventory->shown)
        {
            if (process_inventory_input(player, key))
            {
                hide_player_inventory(player);
                delete_last(render_graph);
                game_screen_node->require_redraw = true;
            }
        }
        else
        {
            player_render_node->require_redraw =
                process_player_input(player, key, &state) ? true : player_render_node->require_redraw;
        }

        if (key == 10)
        {
            if (player->location_x == 0 && player->location_y == 1)
            {
                store_screen->require_redraw = true;
                store->should_show           = true;
                store->buy_menu->should_show = true;
            }
            else if ((player->location_x != 1 || player->location_y != 2))
            {
                battle_screen->require_redraw    = true;
                battle->should_show              = true;
                battle->battle_menu->should_show = true;
                battle->enemy                    = create_enemy(player->location_x, player->location_y);
                battle->turn                     = false;
            }
        }
    }

    // clean resources
    delete_pause_menu(menu);
    delete_render_graph(render_graph);
    delete_player(player);
    stop_sound(music);
    delete_sound(music);
    clean_score(score);
}
