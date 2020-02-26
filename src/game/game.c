//
// Created by alan2 on 25/02/2020.
//
#include <play_music.h>
#include "game/score.h"
#include "game/game.h"
#include "game/health.h"
#include "utils/colors.h"
#include <curses.h>

typedef struct
{
    int16_t x;
    int16_t y;

    uint16_t previous_x;
    uint16_t previous_y;
} player;

void start_game(void)
{
    play_music(MUSIC_GAME, true);
    health_t *player_health = start_health();
    score_t *score = start_score();

    // dibujar una carita bien prrona
    WINDOW *face = newwin(0, 11, 0, getmaxx(stdscr) / 2 - 2);

    mvwaddwstr(face, 0, 0, L"(ᵔᴥᵔ)");
    wrefresh(face);

    WINDOW *game = newwin(getmaxy(stdscr) - 1, getmaxx(stdscr), 1, 0);


    player player;
    player.x = getmaxx(game) / 2;
    player.y = getmaxy(game) / 2;
    player.previous_x = player.x;
    player.previous_y = player.y;

    mvwaddwstr(game, player.y, player.x, L"☺");
    wrefresh(game);

    nodelay(game, true);
    keypad(game, true);

    wbkgd(game, COLOR_PAIR(GAME_COLOR_PAIR));

    while (1)
    {
        int key = wgetch(game);
        if (key == 27)
        {
            break;
        }
        switch (key)
        {
            case KEY_UP:
                player.previous_y = player.y;
                player.previous_x = player.x;
                player.y--;
                if (player.y == -1)
                    player.y = 0;
                break;
            case KEY_DOWN:
                player.previous_y = player.y;
                player.previous_x = player.x;
                player.y++;
                if (player.y == getmaxy(game))
                    player.y = getmaxy(game) - 1;
                break;
            case KEY_RIGHT:
                player.previous_y = player.y;
                player.previous_x = player.x;
                player.x++;
                if (player.x == getmaxx(game))
                    player.x = getmaxx(game) - 1;
                break;
            case KEY_LEFT:
                player.previous_y = player.y;
                player.previous_x = player.x;
                player.x--;
                if (player.x == -1)
                    player.x = 0;
                break;
            default:
                break;
        }

        if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_DOWN || key == KEY_UP)
        {
            mvwdelch(game, player.previous_y, player.previous_x);
            mvwaddwstr(game, player.y, player.x, L"☺");
            wrefresh(game);
        }

    }

    // clean resources
    clean_health(player_health);
    clean_score(score);
}
