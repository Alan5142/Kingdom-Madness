//
// Created by alan2 on 08/04/2020.
//
#include "load_game.h"
#include <stdlib.h>
#include <utils/render_graph.h>

load_game_menu_t *create_load_game_menu(WINDOW *parent, render_node_t *node)
{
    load_game_menu_t *menu       = malloc(sizeof(load_game_menu_t));
    static const char *choices[] = {"【 Slot 1 】", "【 Slot 2 】", "【 Slot 3 】", "【 Salir  】"};
    node->draw_callback          = (draw_callback_c)draw_load_game_menu;
    node->param                  = menu;
    menu->menu =
        create_menu(choices, 4, parent, 6, 14, getmaxy(stdscr) / 2 - 3, getmaxx(stdscr) / 2 - 8 + 15, COLOR_PAIR(5));
    menu->pause_node     = node;
    node->require_redraw = false;
    menu->should_show = false;
    return menu;
}
load_game_menu_choice_e execute_load_game_menu_action(load_game_menu_t *menu)
{
    load_game_menu_choice_e return_choice = LOAD_GAME_NONE;
    switch (menu->option)
    {
        case KEY_UP:
            execute_action(menu->menu, MENU_MOVE_UP);
            break;
        case KEY_DOWN:
            execute_action(menu->menu, MENU_MOVE_DOWN);
            break;
        case 10:
            return_choice = execute_action(menu->menu, MENU_ENTER);
            break;
        default:
            execute_action(menu->menu, MENU_REDRAW);
            break;
    }
    return return_choice;
}
void draw_load_game_menu(load_game_menu_t *menu)
{
    if (!menu->should_show) return;
    set_menu_attribute(menu->menu, COLOR_PAIR(5));

    draw_menu(menu->menu);
}

void delete_load_game_menu(load_game_menu_t *menu)
{
    delete_menu(menu->menu);
    free(menu);
}
