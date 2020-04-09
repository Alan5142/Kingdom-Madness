//
// Created by lghhs on 09/04/2020.
//

#include "game/store_menu.h"
#include <stdlib.h>
#include <utils/render_graph.h>

store_menu_t *create_store_menu(WINDOW *parent, render_node_t *node)
{
    store_menu_t *menu = malloc(sizeof(store_menu_t));
    static const char *choices[] = {"【  POTION LOW   】", "【 POTION MEDIUM 】", "【   ARMOR LOW   】", "【 ARMOR MEDIUM  】", "【   POWER LOW   】", "【 POWER MEDIUM  】"};
    node->draw_callback = (draw_callback_c) draw_store_menu;
    node->param = menu;
    menu->should_show = false;
    menu->menu = create_menu(choices, 6, parent, 6, 17, getmaxy(stdscr) / 2 - 2, getmaxx(stdscr) / 2 - 8, COLOR_PAIR(5));
    menu->current_choice = &menu->menu->current_choice;
    menu->store_menu_node = node;
    node->require_redraw = false;

    return menu;
}

void draw_store_menu(store_menu_t *menu)
{
    set_menu_attribute(menu->menu, COLOR_PAIR(5));

    draw_menu(menu->menu);
}

void delete_store_menu(store_menu_t *menu)
{
    delete_menu(menu->menu);
    free(menu);
}

store_choice_e execute_store_menu_buy(store_menu_t *menu)
{
    store_choice_e return_choice = STORE_NONE;

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


