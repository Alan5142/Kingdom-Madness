//
// Created by lghhs on 16/04/2020.
//

#ifndef PROGRA_BATTLE_MENU_H
#define PROGRA_BATTLE_MENU_H

#include <curses.h>
#include <stdint.h>
#include <utils/menu.h>
#include <stdbool.h>

struct render_node_t;

typedef struct battle_menu_t
{
    menu_t *menu;
    WINDOW *window;
    bool should_show;
    int option;
    struct render_node_t* battle_menu_node;
} battle_menu_t;

typedef enum
{
    BATTLE_ATTACK = 0,
    BATTLE_MAGIC,
    BATTLE_DEFENSE,
    BATTLE_ITEM,
    BATTLE_EXIT,
    BATTLE_NONE
} battle_choice_e;

battle_menu_t *create_battle_menu(WINDOW *parent, struct render_node_t *node);

battle_choice_e execute_battle_menu(battle_menu_t *menu);

void draw_battle_menu(battle_menu_t *menu);

void delete_battle_menu(battle_menu_t *menu);

#endif //PROGRA_BATTLE_MENU_H
