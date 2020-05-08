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
#include <game/save_game.h>
#include <game/store_menu.h>
#include <sound.h>
#include <stdlib.h>
#include <time.h>
#include <utils/render_graph.h>
#include <utils/sound_manager.h>
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

    bool defended = false;

    char music_path[64];

    sprintf(music_path, "game/%d.ogg", rand() % 6 + 1);
    sound_open_file(music, music_path);
    set_loop(music, true);
    play_sound(music);
    set_volume(music, 40);

    health_t *player_health = start_health(add_child(render_graph->entry_point, NULL));

    magic_t *magic = create_magic(add_child(render_graph->entry_point, NULL));

    score_t *score = start_score(add_next(player_health->health_node, NULL));

    WINDOW *game = newwin(getmaxy(stdscr) - 1, getmaxx(stdscr), 1, 0);

    player_t *player = create_player(game, player_health, magic);

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

    pause_menu_t *menu               = create_pause_menu(game, add_child(render_graph->entry_point, NULL));
    save_game_menu_t *save_game_menu = create_save_menu(game, add_child(render_graph->entry_point, NULL));

    game_state_t state;
    memset(&state, 0, sizeof(game_state_t));
    if (slot != -1)
    {
        bool success;
        state = load_game(slot, &success);
        if (success)
        {
            score->score               = state.score;
            score->money               = state.money;
            player->health->health     = state.health;
            player->health->max_health = state.max_health;
            get_inventory_from_game_state(player->inventory, &state);
        }
        else
        {
            state.money      = score->money;
            state.score      = score->score;
            state.max_health = player->health->max_health;
            state.health     = player->health->health;
            fill_game_state_inventory_data(&state, player->inventory);
            save_game(&state, slot);
        }
    }
    else
    {
        state.health     = player->health->health;
        state.max_health = player->health->max_health;
        fill_game_state_inventory_data(&state, player->inventory);
    }

    // para no lidiar con derrotar a los jefes cuando estemos en pruebas :)
#if !defined(NDEBUG)
    state.boss_defeated.boss1 = 1;
    state.boss_defeated.boss2 = 0;
    state.boss_defeated.boss3 = 0;
    state.boss_defeated.boss4 = 0;
#endif

    player_health->health = player_health->max_health;

    while (1)
    {
        destroy_finished_sounds();
        draw_render_graph(render_graph);
        wrefresh(game);
        int key = wgetch(game);
        if(state.boss_defeated.boss1 == 1)
        {
            player->base_armor = .8f;
            player->base_damage = 1.2f;
        }
        if(state.boss_defeated.boss2 == 1)
        {
            player->base_armor = .6f;
            player->base_damage = 1.4f;
        }
        if(state.boss_defeated.boss3 == 1)
        {
            player->base_armor = .4f;
            player->base_damage = 1.6f;
        }
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
                    sprintf(music_path, "game/%d.ogg", rand() % 6 + 1);
                    sound_open_file(music, music_path);
                    play_sound(music);
                    break;
                case STORE_BUY_POTION_LOW:
                    if (score->money < 50)
                    {
                        static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w, 0x0D);
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
                    if (state.boss_defeated.boss2 == 1)
                    {
                        if (score->money < 100)
                        {
                            static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                         "(Presione alguna tecla para continuar)"};
                            standby_window_t *stdby_w = create_standby_window(
                                text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                            draw_standby_window(stdby_w, 0x0D);
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
                    }
                    else
                    {
                        sound_t sound = create_sound();
                        char rand_n[64];
                        sprintf(rand_n, "sfx/error/%d.ogg", rand() % 1 + 1);
                        sound_open_file(sound, rand_n);
                        set_loop(sound, false);
                        play_sound(sound);
                        add_sound_to_manager(sound);
                        static const char *text[] = {"Para desbloquear este objeto          ",
                                                     "antes necesitad derrotar al GHOST.    ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 3, game, 5, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w, 0x0D);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    break;
                case STORE_BUY_ARMOR_LOW:
                    if (score->money < 40)
                    {
                        static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w, 0x0D);
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
                    if(state.boss_defeated.boss3 == 1)
                    {
                        if (score->money < 80)
                        {
                            static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                         "(Presione alguna tecla para continuar)"};
                            standby_window_t *stdby_w = create_standby_window(
                                text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                            draw_standby_window(stdby_w, 0x0D);
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
                    }
                    else
                    {
                        sound_t sound = create_sound();
                        char rand_n[64];
                        sprintf(rand_n, "sfx/error/%d.ogg", rand() % 1 + 1);
                        sound_open_file(sound, rand_n);
                        set_loop(sound, false);
                        play_sound(sound);
                        add_sound_to_manager(sound);
                        static const char *text[] = {"Para desbloquear este objeto          ",
                                                     "antes necesitad derrotar al REAPER.   ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 3, game, 5, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w, 0x0D);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    break;
                case STORE_BUY_POWER_LOW:
                    if(state.boss_defeated.boss2 == 1)
                    {
                        if (score->money < 40)
                        {
                            static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                         "(Presione alguna tecla para continuar)"};
                            standby_window_t *stdby_w = create_standby_window(
                                text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                            draw_standby_window(stdby_w, 0x0D);
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
                    }
                    else
                    {
                        sound_t sound = create_sound();
                        char rand_n[64];
                        sprintf(rand_n, "sfx/error/%d.ogg", rand() % 1 + 1);
                        sound_open_file(sound, rand_n);
                        set_loop(sound, false);
                        play_sound(sound);
                        add_sound_to_manager(sound);
                        static const char *text[] = {"Para desbloquear este objeto          ",
                                                     "antes necesitad derrotar al GHOST.    ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 3, game, 5, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w, 0x0D);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    break;
                case STORE_BUY_POWER_MEDIUM:
                    if(state.boss_defeated.boss3 == 1)
                    {
                        if (score->money < 90)
                        {
                            static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                         "(Presione alguna tecla para continuar)"};
                            standby_window_t *stdby_w = create_standby_window(
                                text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                            draw_standby_window(stdby_w, 0x0D);
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
                    }
                    else
                    {
                        sound_t sound = create_sound();
                        char rand_n[64];
                        sprintf(rand_n, "sfx/error/%d.ogg", rand() % 1 + 1);
                        sound_open_file(sound, rand_n);
                        set_loop(sound, false);
                        play_sound(sound);
                        add_sound_to_manager(sound);
                        static const char *text[] = {"Para desbloquear este objeto          ",
                                                     "antes necesitad derrotar al REAPER.   ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 3, game, 5, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w, 0x0D);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                        store->should_show           = true;
                        store->buy_menu->should_show = true;
                    }
                    break;
                case STORE_BUY_HP:
                {
                    int hp_cost = (player_health->max_health - 80) / 10;
                    hp_cost     = hp_cost == 0 ? 100 : (300 * hp_cost);

                    if ((player_health->max_health / 10 >= 10 && !state.boss_defeated.boss2) || (player_health->max_health / 10 >= 15 && !state.boss_defeated.boss3))
                    {
                        static const char *text[] = {"No tenemos existencias, vuelve mas tarde",
                                                     "(  Presione alguna tecla para continuar  )"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 41, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w, 0x0D);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                    }
                    else if (score->money < hp_cost)
                    {
                        static const char *text[] = {"No cuentas con dinero suficiente.     ",
                                                     "(Presione alguna tecla para continuar)"};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                        draw_standby_window(stdby_w, 0x0D);
                        while (!getch())
                            ;
                        delete_standby_window(stdby_w);
                        store_screen->require_redraw = true;
                    }
                    else
                    {
                        sound_t sound = create_sound();
                        char rand_n[64];
                        sprintf(rand_n, "sfx/coins/coin_%d.ogg", rand() % 3 + 1);
                        sound_open_file(sound, rand_n);
                        set_loop(sound, false);
                        play_sound(sound);
                        add_sound_to_manager(sound);

                        score->money -= hp_cost;
                        player_health->max_health += 10;
                        player_health->health = player_health->max_health;
                        player_health->health_node->require_redraw = true;
                        score->score_node->require_redraw = true;
                        store_screen->require_redraw = true;

                        static char store_hp[32];

                        hp_cost = (player_health->max_health - 80) / 10;
                        hp_cost     = hp_cost == 0 ? 100 : (300 * hp_cost);

                        sprintf(store_hp, "【     HP ¤% 5d      】", hp_cost);

                        store->buy_menu->menu->options[6] = store_hp;
                    }

                    break;
                }
                case STORE_NONE:
                    break;
            }
            if (key == 27)
            {
                sprintf(music_path, "game/%d.ogg", rand() % 6 + 1);
                sound_open_file(music, music_path);
                play_sound(music);
                store->should_show               = false;
                store->buy_menu->should_show     = false;
                game_screen_node->require_redraw = true;
            }
            continue;
        }
        if (battle->should_show)
        {
            int *monster_health = 0;
            switch (battle->enemy.enemy_number)
            {
                case 0:
                    monster_health =(state.boss_defeated.boss1 == 1) ? &battle->enemy.max_health : &battle->enemy.health;
                    break;
                case 1:
                    monster_health =(state.boss_defeated.boss2 == 1) ? &battle->enemy.max_health : &battle->enemy.health;
                    break;
                case 2:
                    monster_health =(state.boss_defeated.boss3 == 1) ? &battle->enemy.max_health : &battle->enemy.health;
                    break;
                case 3:
                    monster_health =(state.boss_defeated.boss4 == 1) ? &battle->enemy.max_health : &battle->enemy.health;
                    break;
            }
            if (battle->turn == true)
            {
                // jugador muerto :(
                if (player->health->health <= 0)
                {
                    sprintf(music_path, "derrota/%d.ogg", rand() % 2 + 1);
                    set_loop(music, false);
                    sound_open_file(music, music_path);
                    play_sound(music);
                    static const char *text[] = {
                        " ██╗██╗  ██╗ █████╗ ███████╗    ███████╗██╗██████╗  ██████╗                     ",
                        " ╚═╝██║  ██║██╔══██╗██╔════╝    ██╔════╝██║██╔══██╗██╔═══██╗                    ",
                        " ██╗███████║███████║███████╗    ███████╗██║██║  ██║██║   ██║                    ",
                        " ██║██╔══██║██╔══██║╚════██║    ╚════██║██║██║  ██║██║   ██║                    ",
                        " ██║██║  ██║██║  ██║███████║    ███████║██║██████╔╝╚██████╔╝                    ",
                        " ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝╚═════╝  ╚═════╝                        ",
                        "                                                                                ",
                        " ██████╗ ███████╗██████╗ ██████╗  ██████╗ ████████╗ █████╗ ██████╗  ██████╗ ██╗ ",
                        " ██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗██╔══██╗██╔═══██╗██║ ",
                        " ██║  ██║█████╗  ██████╔╝██████╔╝██║   ██║   ██║   ███████║██║  ██║██║   ██║██║ ",
                        " ██║  ██║██╔══╝  ██╔══██╗██╔══██╗██║   ██║   ██║   ██╔══██║██║  ██║██║   ██║╚═╝ ",
                        " ██████╔╝███████╗██║  ██║██║  ██║╚██████╔╝   ██║   ██║  ██║██████╔╝╚██████╔╝██╗ ",
                        " ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝ ",
                        "El mundo será consumido en la oscuridad...                                      ",
                        "(Presione alguna tecla para continuar)                                          "};

                    standby_window_t *stdby_w =
                        create_standby_window(text, 15, game, 17, 82, getmaxy(game) / 2 - 8, getmaxx(game) / 2 - 42);
                    draw_standby_window(stdby_w, 0x0D);
                    while (!getch())
                        ;
                    set_loop(music, true);
                    delete_standby_window(stdby_w);
                    break;
                }

                battle->battle_menu->option       = key;
                battle_choice_e choice            = execute_battle_menu(battle->battle_menu);
                magic->magic_node->require_redraw = true;
                bool success_action               = false;

                char player_move[64];
                switch (choice)
                {
                    case BATTLE_EXIT:
                    {
                        if (score->money < 20)
                        {
                            static const char *text[] = {"¡NO TIENES SUFICIENTE DINERO!                   "};
                            standby_window_t *stdby_w =
                                create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                            draw_standby_window(stdby_w, 0x0D);
                        }
                        else
                        {
                            score->money                       = score->money - 20;
                            battle->should_show                = false;
                            battle->battle_menu->should_show   = false;
                            game_screen_node->require_redraw   = true;
                            player_render_node->require_redraw = true;
                            score->score_node->require_redraw  = true;
                            first_pass                         = true;
                            sprintf(music_path, "game/%d.ogg", rand() % 6 + 1);
                            sound_open_file(music, music_path);
                            play_sound(music);
                            player->health->health = player->health->max_health;
                            player->magic->magic   = 100;
                        }
                    }
                    break;
                    case BATTLE_ATTACK:
                    {
                        sound_t character_attack = create_sound();
                        add_sound_to_manager(character_attack);

                        sprintf(player_move, "sfx/ataques/player_%d.ogg", 1);
                        sound_open_file(character_attack, player_move);
                        set_loop(character_attack, false);
                        play_sound(character_attack);
                        int milliseconds = get_sound_milliseconds_duration(character_attack);
                        flash();
                        Sleep(milliseconds);
                        int dmg;
                        if(battle->enemy.enemy_number == 3 && rand() % 100 + 1 > 90)
                        {
                            static const char *text[] = {"¡EL ENEMIGO SE HA DEFENDIDO!                    "};
                            standby_window_t *stdby_w =
                                create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                            draw_standby_window(stdby_w, 0x0D);
                            dmg = (int)(player->damage_multiplier * player->base_damage * 5 * (rand() % 51 + 80) / 100);
                            Sleep(1000);
                            static const char *text2[] = {"¡TU TURNO!                                      "};
                            standby_window_t *stdby_w2 =
                                create_standby_window(text2, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                            draw_standby_window(stdby_w2, 5);
                        }
                        else
                        {
                            dmg = (int)(player->damage_multiplier * player->base_damage * 10 * (rand() % 51 + 80) / 100);
                            battle->turn = false;
                            Sleep(1000);
                        }
                        *monster_health -= dmg;
                    }
                    break;
                    case BATTLE_DEFENSE:
                    {
                        sound_t character_deffense = create_sound();
                        add_sound_to_manager(character_deffense);

                        sprintf(player_move, "sfx/defensas/%d.ogg", 1);
                        sound_open_file(character_deffense, player_move);
                        set_loop(character_deffense, false);
                        play_sound(character_deffense);
                        int milliseconds = get_sound_milliseconds_duration(character_deffense);
                        flash();
                        Sleep(500);
                        flash();
                        Sleep(milliseconds - 500);
                        battle->turn = false;
                        defended     = true;
                        player->armor_multiplier *= .5;
                        player->magic->magic += 10;
                        player->magic->magic = min(100, player->magic->magic);
                        Sleep(1000);
                    }
                    break;
                    case BATTLE_MAGIC:
                    {
                        if ((player->magic->magic - 25) >= 0)
                        {
                            player->magic->magic -= 25;
                            player->magic->magic = max(0, player->magic->magic);
                            sound_t character_magic = create_sound();
                            add_sound_to_manager(character_magic);

                            sprintf(player_move, "sfx/magia/%d.ogg", rand() % 2 + 1);
                            sound_open_file(character_magic, player_move);
                            set_loop(character_magic, false);
                            play_sound(character_magic);
                            int milliseconds = get_sound_milliseconds_duration(character_magic);
                            for (int i = 0; i < milliseconds / 100; i++)
                            {
                                flash();
                                Sleep(milliseconds / 100);
                            }
                            if (battle->enemy.enemy_number == 3 && rand() % 100 + 1 > 90)
                            {
                                static const char *text[] = {"¡EL ENEMIGO SE HA DEFENDIDO!                    "};
                                standby_window_t *stdby_w =
                                    create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                draw_standby_window(stdby_w, 0x0D);
                                *monster_health -= (int)(player->damage_multiplier * player->base_damage * 9 *
                                                         (rand() % 51 + 80) / 100);
                                Sleep(1000);
                                static const char *text2[] = {"¡TU TURNO!                                      "};
                                standby_window_t *stdby_w2 =
                                    create_standby_window(text2, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                draw_standby_window(stdby_w2, 5);
                            }
                            else
                            {
                                *monster_health -= (int)(player->damage_multiplier * player->base_damage * 17 *
                                                         (rand() % 51 + 80) / 100);
                                battle->turn   = false;
                                success_action = true;
                                Sleep(1000);
                            }
                        }
                        else
                        {

                            static const char *text[] = {"¡NO TIENES SUFICIENTE MANA!                     "};
                            standby_window_t *stdby_w =
                                create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                            draw_standby_window(stdby_w, 0x0D);
                        }
                    }
                    break;
                    case BATTLE_ITEM:
                        game_screen_node->require_redraw = true;
                        battle_screen->require_redraw    = true;
                        render_node_t *inventory_battle =
                            add_node_at_end(render_graph, (draw_callback_c)draw_player_inventory);
                        inventory_battle->param          = player;
                        inventory_battle->require_redraw = true;
                        draw_render_graph(render_graph);
                        wrefresh(game);
                        int menu_in = wgetch(game);
                        while (!process_inventory_input(player, menu_in) && menu_in != 27)
                        {
                            menu_in = wgetch(game);
                        }
                        if (menu_in != 27)
                        {
                            success_action = true;
                            battle->turn   = false;
                            Sleep(1000);
                        }
                        delete_node(inventory_battle);
                        game_screen_node->require_redraw = true;
                        battle_screen->require_redraw    = true;
                        player->inventory->shown         = false;
                        draw_render_graph(render_graph);
                        Sleep(1500);
                        break;
                    case BATTLE_NONE:
                    {
                        if (battle->battle_menu->option == KEY_UP || battle->battle_menu->option == KEY_DOWN)
                        {
                            int current = battle->battle_menu->menu->current_choice;
                            switch (current)
                            {
                                case 0:
                                {
                                    static const char *text[] = {"Un ataque de daño medio, ¡Úsalo cuando quieras! "};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w, 5);
                                }
                                break;
                                case 1:
                                {
                                    static const char *text[] = {"¡Un fuerte ataque mágico!, pero necesita MP     "};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w, 5);
                                }
                                break;
                                case 2:
                                {
                                    static const char *text[] = {"¡Cúbrete para recibir menos daño y recuperar MP!"};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w, 5);
                                }
                                break;
                                case 3:
                                {
                                    static const char *text[] = {"Accede a tu inventario y usa uno de tus objetos "};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w, 5);
                                }
                                break;
                                case 4:
                                {
                                    static const char *text[] = {"Es mejor aquí corrió que aquí murió...          "};
                                    standby_window_t *stdby_w =
                                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                                    draw_standby_window(stdby_w, 5);
                                }
                                break;
                            }
                        }
                    }
                    break;
                    default:
                        break;
                }
                if (*monster_health > 0)
                {
                    if ((success_action && (choice == BATTLE_ITEM || choice == BATTLE_MAGIC)) ||
                        choice == BATTLE_ATTACK)
                    {
                        static const char *text[] = {"¡EL ENEMIGO ATACA!                              "};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                        draw_standby_window(stdby_w, 0x0D);
                    }
                    if (choice == BATTLE_DEFENSE)
                    {
                        static const char *text[] = {"¡BIEN DEFENDIDO!                                "};
                        standby_window_t *stdby_w =
                            create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                        draw_standby_window(stdby_w, 5);
                    }
                }
            }
            else
            {
                if (first_pass)
                {
                    static const char *text[] = {"¡HAS SIDO EMBOSCADO!                            "};
                    standby_window_t *stdby_w =
                        create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                    draw_standby_window(stdby_w, 5);
                    first_pass = false;
                }
                // BOOM muerto
                if (*monster_health <= 0)
                {
                    standby_window_t *stdby_w;
                    if (battle->enemy.enemy_number == 3)
                    {
                        sprintf(music_path, "victoria_final/%d.ogg", rand() % 1 + 1);
                        sound_open_file(music, music_path);
                        play_sound(music);
                        static const char *text[] = {" ██╗██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██████╗ ██╗ █████╗ ██╗ ",
                                                     " ╚═╝██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗██║ ",
                                                     " ██╗██║   ██║██║██║        ██║   ██║   ██║██████╔╝██║███████║██║ ",
                                                     " ██║╚██╗ ██╔╝██║██║        ██║   ██║   ██║██╔══██╗██║██╔══██║╚═╝ ",
                                                     " ██║ ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║  ██║██║██║  ██║██╗ ",
                                                     " ╚═╝  ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝ ",
                                                     "El mundo ha sido salvado...                                      ",
                                                     "(Presione alguna tecla para continuar)                           "};
                        stdby_w =
                            create_standby_window(text, 8, game, 10, 67, getmaxy(game) / 2 - 5, getmaxx(game) / 2 - 34);
                        state.boss_defeated.boss4 = 1;
                    }
                    else
                    {
                        sprintf(music_path, "victoria/%d.ogg", rand() % 2 + 1);
                        sound_open_file(music, music_path);
                        play_sound(music);
                        static const char *text[] = {
                            " ██╗██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██████╗ ██╗ █████╗ ██╗ ",
                            " ╚═╝██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗██║ ",
                            " ██╗██║   ██║██║██║        ██║   ██║   ██║██████╔╝██║███████║██║ ",
                            " ██║╚██╗ ██╔╝██║██║        ██║   ██║   ██║██╔══██╗██║██╔══██║╚═╝ ",
                            " ██║ ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║  ██║██║██║  ██║██╗ ",
                            " ╚═╝  ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝ ",
                            "Has ganado, pero aún quedan batallas...                          ",
                            "(Presione alguna tecla para continuar)                           "};
                        stdby_w =
                            create_standby_window(text, 8, game, 10, 67, getmaxy(game) / 2 - 5, getmaxx(game) / 2 - 34);
                        switch (battle->enemy.enemy_number)
                        {
                            case 0:
                                state.boss_defeated.boss1 = 1;
                                break;
                            case 1:
                                state.boss_defeated.boss2 = 1;
                                break;
                            case 2:
                                state.boss_defeated.boss3 = 1;
                                break;
                        }
                    }

                    draw_standby_window(stdby_w, 0x0E);
                    while (!getch())
                        ;
                    delete_standby_window(stdby_w);
                    sprintf(music_path, "game/%d.ogg", rand() % 6 + 1);
                    sound_open_file(music, music_path);
                    play_sound(music);
                    battle->should_show                        = false;
                    render_graph->entry_point->require_redraw  = true;
                    game_screen_node->require_redraw           = true;
                    magic->magic_node->require_redraw          = true;
                    player->health->health                     = player->health->max_health;
                    player->magic->magic                       = 100;
                    player_health->health_node->require_redraw = true;
                    score->money += battle->enemy.reward;
                    score->score_node->require_redraw = true;
                    score->score += battle->enemy.reward * 5;
                    continue;
                }

                    sound_t enemy_attack = create_sound();
                    add_sound_to_manager(enemy_attack);

                    char rand_n[64];
                    sprintf(rand_n, "sfx/ataques/enemy_%d.ogg", 1);
                    sound_open_file(enemy_attack, rand_n);
                    set_loop(enemy_attack, false);
                    play_sound(enemy_attack);
                    int milliseconds = get_sound_milliseconds_duration(enemy_attack);
                    flash();
                    Sleep(milliseconds);
                    int damage = -(int)(player->base_armor * player->armor_multiplier * battle->enemy.power *
                                        (rand() % 51 + 80) / 100);
                    add_health(player_health, damage);
                static const char *text[] = {"¡TU TURNO!                                      "};
                standby_window_t *stdby_w =
                    create_standby_window(text, 1, game, 3, 50, getmaxy(battle->window) - 7, 16);
                draw_standby_window(stdby_w, 5);
                if (defended)
                {
                    player->armor_multiplier *= 2;
                    defended = false;
                }

                if (player->shield_counter == 0)
                {
                    player->armor_multiplier = 1.f;
                }
                else
                {
                    player->shield_counter--;
                }

                if (player->power_counter == 0)
                {
                    player->damage_multiplier = 1.f;
                }
                else
                {
                    player->power_counter--;
                }
                score->score_node->require_redraw          = true;
                player_health->health_node->require_redraw = true;
                battle->turn                               = true;
                player->magic->magic += 3;
                player->magic->magic = min(100, player->magic->magic);
            }
            continue;
        }

        if (save_game_menu->should_show)
        {
            save_game_menu->option = key;
            save_choice_e choice   = execute_save_menu_action(save_game_menu);
            bool saved             = true;
            switch (choice)
            {
                case SLOT_1:
                    state.score = score->score;
                    state.money = score->money;
                    state.max_health = player->health->max_health;
                    fill_game_state_inventory_data(&state, player->inventory);
                    save_game(&state, 1);
                    break;
                case SLOT_2:
                    state.score = score->score;
                    state.money = score->money;
                    state.max_health = player->health->max_health;
                    fill_game_state_inventory_data(&state, player->inventory);
                    save_game(&state, 2);
                    break;
                case SLOT_3:
                    state.score = score->score;
                    state.money = score->money;
                    state.max_health = player->health->max_health;
                    fill_game_state_inventory_data(&state, player->inventory);
                    save_game(&state, 3);
                    break;
                default:
                    saved = false;
                    break;
            }
            if (saved)
            {
                static const char *text[] = {"Guardado correctamente                ",
                                             "(Presione alguna tecla para continuar)"};
                standby_window_t *stdby_w =
                    create_standby_window(text, 2, game, 4, 40, getmaxy(game) / 2 + 8, getmaxx(game) / 2 + 5);
                draw_standby_window(stdby_w, 5);
                while (!getch())
                    ;
                delete_standby_window(stdby_w);
            }
            if (key == 27 || saved)
            {
                save_game_menu->should_show      = false;
                game_screen_node->require_redraw = true;
                continue;
            }
            save_game_menu->render_node->require_redraw = true;
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
                    save_game_menu->should_show                 = true;
                    menu->should_show                           = false;
                    game_screen_node->require_redraw            = true;
                    save_game_menu->render_node->require_redraw = true;
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

        if (!player->inventory->shown)
        {
            player_render_node->require_redraw =
                process_player_input(player, key, &state) ? true : player_render_node->require_redraw;
        }

        if (key == 10)
        {
            if (player->location_x == 0 && player->location_y == 1)
            {
                sprintf(music_path, "tienda/%d.ogg", rand() % 2 + 1);
                sound_open_file(music, music_path);
                play_sound(music);
                store_screen->require_redraw = true;
                store->should_show           = true;

                static char store_hp[32];

                int hp_cost = (player_health->max_health - 80) / 10;
                hp_cost     = hp_cost == 0 ? 100 : (300 * hp_cost);

                sprintf(store_hp, "【     HP ¤% 5d      】", hp_cost);

                store->buy_menu->menu->options[6] = store_hp;

                store->buy_menu->should_show = true;
            }
            else if ((player->location_x != 1 || player->location_y != 2))
            {
                if (player->location_x == 0 && player->location_y == 0)
                {
                    sprintf(music_path, "combate_final/%d.ogg", rand() % 5 + 1);
                }
                else
                {
                    sprintf(music_path, "combate/%d.ogg", rand() % 5 + 1);
                }
                sound_open_file(music, music_path);
                play_sound(music);
                player->magic->magic             = 75;
                battle_screen->require_redraw    = true;
                battle->should_show              = true;
                battle->battle_menu->should_show = true;
                battle->enemy                    = create_enemy(player->location_x, player->location_y);
                battle->turn                     = false;
                defended = false;
                player_health->health = player_health->max_health;
            }
        }
    }

    // clean resources
    destroy_finished_sounds();
    delete_pause_menu(menu);
    delete_render_graph(render_graph);
    delete_player(player);
    stop_sound(music);
    delete_sound(music);
    clean_score(score);
}
