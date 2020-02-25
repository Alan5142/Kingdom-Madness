#include <curses.h>
#include <game/game.h>
#include "start_screen.h"

int main()
{
    initscr();

    if (has_colors())
        start_color();

    noecho();

    refresh();
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
