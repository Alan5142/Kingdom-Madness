//
// Created by alan2 on 11/03/2020.
//

#ifndef PROGRA_PAUSE_H
#define PROGRA_PAUSE_H

#include <curses.h>
#include <stdint.h>
#include <utils/menu.h>

typedef struct
{
    menu_t *menu;
    WINDOW *window;
    int8_t current_choice;
} pause_menu_t;

typedef enum
{
    MENU_RESUME = 0,
    MENU_INVENTORY,
    MENU_SAVE,
    MENU_EXIT,
    MENU_NONE
} menu_choice_e;

pause_menu_t *create_pause_menu(WINDOW *parent);
menu_choice_e draw_pause_menu(pause_menu_t *menu, int option);
void delete_pause_menu(pause_menu_t *menu);

#endif //PROGRA_PAUSE_H
