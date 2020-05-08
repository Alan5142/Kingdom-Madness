//
// Created by lghhs on 03/05/2020.
//

#include "utils/standby_window.h"
#include <stdlib.h>

standby_window_t *
create_standby_window(const char **text_list,
                      int size,
                      WINDOW *parent,
                      uint16_t nlines,
                      uint16_t ncolumns,
                      uint16_t y,
                      uint16_t x)
{
    standby_window_t *window = malloc(sizeof(standby_window_t));

    window->length = size;
    window->text = text_list;
    window->window = subwin(parent, nlines, ncolumns, y, x);
    return window;
}

void delete_standby_window(standby_window_t *window)
{
    delwin(window->window);
    free(window);
}

void draw_standby_window(standby_window_t *window, int color)
{
    wclear(window->window);
    wattron(window->window, COLOR_PAIR(color));
    box(window->window, 0, 0);
    for (int i = 0; i < window->length; i++)
    {
        mvwprintw(window->window, i + 1, 1, window->text[i]);
    }
    wrefresh(window->window);
}

