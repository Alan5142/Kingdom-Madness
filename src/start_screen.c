#include "start_screen.h"
#include <curses.h>
#include <string.h>
#include <ctype.h>

const int X_POSITION = 85;

start_screen_result_t start_screen(void)
{
    mvprintw(1, X_POSITION, "  _____       _      _       ");
    mvprintw(2, X_POSITION, " |_   _|     (_)    (_)      ");
    mvprintw(3, X_POSITION, "   | |  _ __  _  ___ _  ___  ");
    mvprintw(4, X_POSITION, "   | | | '_ \\| |/ __| |/ _ \\ ");
    mvprintw(5, X_POSITION, "  _| |_| | | | | (__| | (_) |");
    mvprintw(6, X_POSITION, " |_____|_| |_|_|\\___|_|\\___/ ");

    WINDOW *menu = newwin(10, 31, 15, X_POSITION);
    resize_term(60, 200);

    box(menu, '*', '*');
    wrefresh(menu);

    keypad(menu, true);
    curs_set(0);

    int choice = 0;

    const char *choices[] = {"Jugar", "Salir"};
    start_screen_result_t result;

    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == choice)
            {
                wattron(menu, A_STANDOUT);
            }
            else
            {
                wattroff(menu, A_STANDOUT);
            }
            mvwprintw(menu, i + 1, 2, choices[i]);
        }
        wrefresh(menu);
        int g = wgetch(menu);
        switch (g)
        {
            case KEY_UP:
                choice--;
                if (choice == -1)
                    choice = 1;
                break;
            case KEY_DOWN:
                choice++;
                if (choice == 2)
                    choice = 0;
                break;
            default:
                break;
        }
        if (g == 10)
        {
            if (choice == 1)
            {
                result = START_SCREEN_QUIT;
            }
            else
            {
                result = START_SCREEN_PLAY;
            }
            break;
        }
    }
    delwin(menu);
    clear();
    refresh();
    return result;
}