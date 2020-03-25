//
// Created by alan2 on 25/02/2020.
//
#include "game/score.h"
#include "game/health.h"
#include "utils/colors.h"
#include <curses.h>
#include <sound.h>
#include <stdlib.h>
#include <game/pause.h>
#include <utils/render_graph.h>
#include "game/player/player.h"

void draw_game_screen(WINDOW *game)
{
    wclear(game);
    wrefresh(game);
}

void start_game(void)
{
    render_graph_t *render_graph = create_new_graph();
    sound_t music = create_sound();

    char music_path[64];

    sprintf(music_path, "game/%d.ogg", rand() % 2 + 1);
    sound_open_file(music, music_path);
    set_loop(music, true);
    play_sound(music);

    health_t *player_health = start_health();
    render_node_t *health_node = add_child(render_graph->entry_point, (draw_callback_c) draw_health);
    health_node->param = player_health;

    score_t *score = start_score();

    // dibujar una carita bien prrona
    WINDOW *face = newwin(0, 16, 0, getmaxx(stdscr) / 2 - 8);

    mvwaddstr(face, 0, 0, "(ﾒ￣▽￣)︻┳═一");
    wrefresh(face);

    WINDOW *game = newwin(getmaxy(stdscr) - 1, getmaxx(stdscr), 1, 0);

    player_t *player = create_player(game, player_health);

    render_graph->entry_point->draw_callback = (draw_callback_c) draw_game_screen;
    render_graph->entry_point->param = game;

    render_node_t *player_render_node = add_child(render_graph->entry_point, (draw_callback_c) draw_player);
    player_render_node->param = player;

    nodelay(game, true);
    keypad(game, true);

    wbkgd(game, COLOR_PAIR(GAME_COLOR_PAIR));

    pause_menu_t *menu = create_pause_menu(game);
    render_node_t *menu_node = NULL;

    draw_render_graph(render_graph);
    while (1)
    {
        draw_render_graph(render_graph);
        int key = wgetch(game);
        if (menu->should_show)
        {
            menu->option = key;
            menu_choice_e choice = execute_pause_menu_action(menu);
            if (choice == MENU_NONE)
            {
                menu_node->require_redraw = true;
            }
            if (choice == MENU_EXIT)
            {
                // delete_pause_menu(menu);
                break;
            }
            if (key == 27)
            {
                //delete_pause_menu(menu);
                delete_node(menu_node);
                menu_node = NULL;
                menu->should_show = false;
                menu->should_show = false;
                render_graph->entry_point->require_redraw = true;
                player_render_node->require_redraw = true;
                continue;
            }
            switch (choice)
            {
                case MENU_RESUME:
                    delete_node(menu_node);
                    menu_node = NULL;
                    menu->should_show = false;
                    render_graph->entry_point->require_redraw = true;
                    player_render_node->require_redraw = true;
                    break;
                case MENU_INVENTORY:
                    delete_node(menu_node);
                    menu->should_show = false;
                    render_graph->entry_point->require_redraw = true;
                    add_node_at_end(render_graph, (draw_callback_c) draw_player_inventory)->param = player;
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
                render_graph->entry_point->require_redraw = true;
                player_render_node->require_redraw = true;
            }
            else
            {
                menu_node = add_node_at_end(render_graph, (draw_callback_c) draw_pause_menu);
                menu_node->param = menu;
                menu->option = 0;
                execute_pause_menu_action(menu);
                menu->should_show = true;
                *menu->current_choice = 0;
                menu_node->require_redraw = true;
            }
        }

        player_render_node->require_redraw = process_player_input(player, key) ? true : player_render_node->require_redraw;
    }

    // clean resources
    delwin(face);
    delete_pause_menu(menu);
    delete_render_graph(render_graph);
    delete_player(player);
    stop_sound(music);
    delete_sound(music);
    clean_score(score);
}
