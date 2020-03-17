//
// Created by alan2 on 15/03/2020.
//
#include "utils/sprite.h"
#include <stdio.h>

void draw_sprite(WINDOW *win, int16_t y, int16_t x, const char *sprite, on_start_draw_t on_start_draw,
                 on_end_draw_t on_end_draw)
{
    char path[64];
    sprintf(path, "sprites/%s", sprite);
    FILE *sprite_file = fopen(path, "r");

    int chr = 0;
    int16_t y_relative = 0, x_relative = 0;
    while ((chr = fgetc(sprite_file)) != EOF)
    {
        if (chr == '\n')
        {
            y_relative++;
            x_relative = 0;
            continue;
        }
        if (on_start_draw != NULL)
            on_start_draw(win, y_relative, x_relative, chr);

        mvwprintw(win, y + y_relative, x + x_relative, "%c", chr);

        if (on_end_draw != NULL)
            on_end_draw(win, y_relative, x_relative, chr);
        x_relative++;
    };

    fclose(sprite_file);
}
