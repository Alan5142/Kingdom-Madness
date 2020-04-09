//
// Created by alan2 on 08/04/2020.
//

#ifndef PROGRA_LOAD_GAME_HPP
#define PROGRA_LOAD_GAME_HPP

#include <curses.h>
#include <stdint.h>
#include <utils/menu.h>
#include <stdbool.h>

struct render_node_t;

typedef struct
{
    menu_t *menu;
    WINDOW *window;
    int option;
    struct render_node_t* pause_node;
    bool should_show;
} load_game_menu_t;

typedef enum
{
    LOAD_GAME_SLOT1 = 0,
    LOAD_GAME_SLOT2,
    LOAD_GAME_SLOT3,
    LOAD_GAME_EXIT,
    LOAD_GAME_NONE
} load_game_menu_choice_e;

load_game_menu_t *create_load_game_menu(WINDOW *parent, struct render_node_t *node);

load_game_menu_choice_e execute_load_game_menu_action(load_game_menu_t *menu);

void draw_load_game_menu(load_game_menu_t *menu);

void delete_load_game_menu(load_game_menu_t *menu);

#endif // PROGRA_LOAD_GAME_HPP
