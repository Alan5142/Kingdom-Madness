//
// Created by alan2 on 11/03/2020.
//

#ifndef PROGRA_PAUSE_H
#define PROGRA_PAUSE_H

#include <curses.h>
#include <stdint.h>
#include <utils/menu.h>
#include <stdbool.h>

struct render_node_t;

typedef struct
{
    menu_t *menu;
    WINDOW *window;
    int16_t *current_choice;
    bool should_show;
    int option;
    struct render_node_t* pause_node;
} pause_menu_t;

typedef enum
{
    MENU_RESUME = 0,
    MENU_INVENTORY,
    MENU_SAVE,
    MENU_EXIT,
    MENU_NONE
} menu_choice_e;

pause_menu_t *create_pause_menu(WINDOW *parent, struct render_node_t *node);

menu_choice_e execute_pause_menu_action(pause_menu_t *menu);

void draw_pause_menu(pause_menu_t *menu);

void delete_pause_menu(pause_menu_t *menu);

#endif //PROGRA_PAUSE_H
