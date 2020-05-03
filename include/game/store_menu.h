//
// Created by lghhs on 09/04/2020.
//

#ifndef PROGRA_STORE_MENU_H
#define PROGRA_STORE_MENU_H

#include <curses.h>
#include <stdint.h>
#include <utils/menu.h>
#include <stdbool.h>

struct render_node_t;

typedef struct store_menu_t
{
    menu_t *menu;
    WINDOW *window;
    bool should_show;
    int option;
    struct render_node_t* store_menu_node;
} store_menu_t;

typedef enum
{
    STORE_BUY_POTION_LOW = 0,
    STORE_BUY_POTION_MEDIUM,
    STORE_BUY_ARMOR_LOW,
    STORE_BUY_ARMOR_MEDIUM,
    STORE_BUY_POWER_LOW,
    STORE_BUY_POWER_MEDIUM,
    STORE_EXIT,
    STORE_NONE
} store_choice_e;

store_menu_t *create_store_menu(WINDOW *parent, struct render_node_t *node);

store_choice_e execute_store_menu(store_menu_t *menu);

void draw_store_menu(store_menu_t *menu);

void delete_store_menu(store_menu_t *menu);

#endif //PROGRA_STORE_MENU_H
