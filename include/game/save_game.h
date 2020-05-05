//
// Created by alan2 on 05/05/2020.
//

#ifndef PROGRA_SAVE_GAME_H
#define PROGRA_SAVE_GAME_H

#include <curses.h>
#include <stdint.h>
#include <utils/menu.h>
#include <stdbool.h>

struct render_node_t;

typedef struct save_game_menu_t
{
    menu_t *menu;
    WINDOW *window;
    bool should_show;
    int option;
    struct render_node_t* render_node;
} save_game_menu_t;

typedef enum
{
    SLOT_1 = 0,
    SLOT_2,
    SLOT_3,
    SLOT_EXIT,
    SLOT_NONE
} save_choice_e;

save_game_menu_t *create_save_menu(WINDOW *parent, struct render_node_t *node);

save_choice_e execute_save_menu_action(save_game_menu_t *menu);

void draw_save_menu(save_game_menu_t *menu);

void delete_save_menu(save_game_menu_t *menu);

#endif // PROGRA_SAVE_GAME_H
