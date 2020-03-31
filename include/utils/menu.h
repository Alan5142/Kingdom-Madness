//
// Created by alan2 on 11/03/2020.
//

#ifndef PROGRA_MENU_H
#define PROGRA_MENU_H

#include <curses.h>
#include <sound.h>

typedef struct menu_t
{
    WINDOW *window;
    const char **options;
    int length;
    int16_t current_choice;
    cchar_t default_attribute;
    sound_t cursor_sfx;
} menu_t;

typedef enum
{
    MENU_MOVE_UP,
    MENU_MOVE_DOWN,
    MENU_ENTER,
    MENU_REDRAW
} menu_action_t;

menu_t *create_menu(const char **options,
                    int size,
                    WINDOW *parent,
                    uint16_t nlines,
                    uint16_t ncolumns,
                    uint16_t y,
                    uint16_t x,
                    chtype default_attribute);

void set_menu_attribute(menu_t *menu, chtype attribute);

void draw_menu(menu_t *menu);

void clear_menu_attribute(menu_t *menu, chtype attribute);

int16_t execute_action(menu_t *menu, menu_action_t action);

void delete_menu(menu_t *menu);

#endif //PROGRA_MENU_H
