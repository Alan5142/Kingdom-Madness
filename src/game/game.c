//
// Created by alan2 on 25/02/2020.
//
#include <play_music.h>
#include "game/score.h"
#include "game/health.h"
#include "utils/colors.h"
#include <curses.h>
#include <sound.h>
#include <stdlib.h>
#include <game/pause.h>
#include <game/inventory.h>
#include "game/player/player.h"

void start_game(void)
{
    void *music = create_sound();

    char music_path[64];

    sprintf(music_path, "sound/game/%d.ogg", rand() % 2 + 1);
    sound_open_file(music, music_path);
    set_loop(music, true);
    play_sound(music);

    health_t *player_health = start_health();
    score_t *score = start_score();

    // dibujar una carita bien prrona
    WINDOW *face = newwin(0, 16, 0, getmaxx(stdscr) / 2 - 8);

    mvwaddstr(face, 0, 0, "(ﾒ￣▽￣)︻┳═一");
    wrefresh(face);

    WINDOW *game = newwin(getmaxy(stdscr) - 1, getmaxx(stdscr), 1, 0);


    player_t *player = create_player(game, player_health);
    draw_player(player);

    mvwaddstr(game, player->y, player->x, "☺");
    wrefresh(game);

    inventory_t *inventory = create_inventory_screen(game);

    nodelay(game, true);
    keypad(game, true);

    wbkgd(game, COLOR_PAIR(GAME_COLOR_PAIR));

    pause_menu_t *menu = NULL;

    while (1)
    {
        int key = wgetch(game);
        if (menu != NULL)
        {
            menu_choice_e choice = draw_pause_menu(menu, key);
            if (choice == MENU_EXIT)
            {
                delete_pause_menu(menu);
                break;
            }
            if (key == 27)
            {
                delete_pause_menu(menu);
                menu = NULL;
                wclear(game);
                wrefresh(game);
                mvwaddstr(game, player->y, player->x, "😂");
                continue;
            }
            switch (choice)
            {
                case MENU_RESUME:
                    delete_pause_menu(menu);
                    menu = NULL;
                    wclear(game);
                    wrefresh(game);
                    mvwaddstr(game, player->y, player->x, "😂");
                    break;
                case MENU_INVENTORY:
                    delete_pause_menu(menu);
                    wclear(game);
                    wrefresh(game);
                    menu = NULL;
                    draw_inventory(inventory);
                    // TODO crear inventario
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
            menu = create_pause_menu(game);
            continue;
        }

        if (process_player_input(player, key))
        {
            draw_player(player);
        }
    }

    // clean resources
    delete_player(player);
    stop_sound(music);
    delete_sound(music);
    clean_score(score);
}
