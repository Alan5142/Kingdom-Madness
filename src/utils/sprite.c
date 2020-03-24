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

    char unicode_str[5];
    uint8_t unicode_str_index = 0;
    uint8_t unicode_str_bytes = 0;

    while ((chr = fgetc(sprite_file)) != EOF)
    {
        if (chr & 128 || unicode_str_index != 0) // inicio unicode
        {
            if (unicode_str_index == 0)
            {
                if ((chr & 240) == 240)
                {
                    unicode_str_bytes = 4;
                }
                else if ((chr & 224) == 224)
                {
                    unicode_str_bytes = 3;
                }
                else if ((chr & 192) == 192)
                {
                    unicode_str_bytes = 2;
                }
            }

            unicode_str[unicode_str_index++] = chr;
            if (unicode_str_index >= unicode_str_bytes) // fin
            {
                unicode_str[unicode_str_index] = 0;
                unicode_str_index = 0;
                if (on_start_draw != NULL)
                    on_start_draw(win, y_relative, x_relative, chr);
                mvwprintw(win, y + y_relative, x + x_relative, "%s", unicode_str);
                if (on_end_draw != NULL)
                    on_end_draw(win, y_relative, x_relative, chr);
                x_relative++;
            }
            continue;
        }
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
    }

    fclose(sprite_file);
}
