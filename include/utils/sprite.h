//
// Created by alan2 on 15/03/2020.
//

#ifndef PROGRA_SPRITE_H
#define PROGRA_SPRITE_H

#include <stdint.h>
#include <curses.h>

typedef void(*on_start_draw_t)(WINDOW *window, int16_t y, int16_t x, int character_to_draw);
typedef void(*on_end_draw_t)(WINDOW *window, int16_t y, int16_t x, int character_drawn);


void draw_sprite(WINDOW *win, int16_t y, int16_t x, const char *sprite, on_start_draw_t on_start_draw, on_end_draw_t on_end_draw);

#endif //PROGRA_SPRITE_H
