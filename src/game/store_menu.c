//
// Created by lghhs on 09/04/2020.
//

#include "game/store_menu.h"
#include <stdlib.h>
#include <utils/render_graph.h>

store_menu_t *create_store_menu(WINDOW *parent, render_node_t *node)
{
    store_menu_t *menu = malloc(sizeof(store_menu_t));
    static const char *choices[] = {"【   POTION LOW ¤50   】", "【 POTION MEDIUM ¤100 】", "【   ARMOR LOW ¤40    】", "【  ARMOR MEDIUM ¤80  】", "【   POWER LOW ¤40    】", "【  POWER MEDIUM ¤90  】", "", "【        EXIT        】"};
    node->draw_callback = (draw_callback_c) draw_store_menu;
    node->param = menu;
    menu->should_show = false;
    menu->menu = create_menu(choices, 8, parent, 10, 26, getmaxy(parent) / 2 - 2, getmaxx(parent) / 2 + 5, COLOR_PAIR(5));
    menu->store_menu_node = node;
    node->require_redraw = false;

    return menu;
}

void draw_store_menu(store_menu_t *menu)
{
    if (menu->should_show == false)
    {
        return;
    }
    set_menu_attribute(menu->menu, COLOR_PAIR(5));

    draw_menu(menu->menu);
}

void delete_store_menu(store_menu_t *menu)
{
    delete_menu(menu->menu);
    free(menu);
}

store_choice_e execute_store_menu(store_menu_t *menu)
{
    store_choice_e return_choice = STORE_NONE;

    switch (menu->option)
    {
        case KEY_UP:
            execute_action(menu->menu, MENU_MOVE_UP);
            menu->store_menu_node->require_redraw = true;
            break;
        case KEY_DOWN:
            execute_action(menu->menu, MENU_MOVE_DOWN);
            menu->store_menu_node->require_redraw = true;
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


