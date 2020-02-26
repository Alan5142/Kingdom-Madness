#include <curses.h>
#include <game/game.h>
#include <utils/colors.h>
#include "start_screen.h"
#include "play_music.h"

int main()
{
    initscr();

    if (has_colors())
        start_color();

    noecho();

    refresh();
    play_music(MUSIC_INTRO, false);
    init_color_pairs();
    switch (start_screen())
    {
        case START_SCREEN_QUIT:
            break;
        case START_SCREEN_PLAY:
            start_game();
            break;
    }

    endwin();
}
