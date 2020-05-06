//
// Created by lghhs on 03/05/2020.
//

#ifndef PROGRA_STANDBY_WINDOW_H
#define PROGRA_STANDBY_WINDOW_H

#include <curses.h>

struct render_node_t;

typedef struct standby_window_t
{
    WINDOW *window;
    int length;
    const char** text;
} standby_window_t;

standby_window_t *create_standby_window(const char **text_list,
                                        int size,
                                        WINDOW *parent,
                                        uint16_t nlines,
                                        uint16_t ncolumns,
                                        uint16_t y,
                                        uint16_t x);

void draw_standby_window(standby_window_t *menu, int color);

void delete_standby_window(standby_window_t *menu);

#endif // PROGRA_STANDBY_WINDOW_H
