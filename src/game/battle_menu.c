//
// Created by lghhs on 16/04/2020.
//

#include "game/battle_menu.h"
#include <stdlib.h>
#include <utils/render_graph.h>

battle_menu_t *create_battle_menu(WINDOW *parent, render_node_t *node)
{
    battle_menu_t *menu = malloc(sizeof(battle_menu_t));
    static const char *choices[] = {"【 ATTACK  】", "【  MAGIC  】", "【 DEFENSE 】", "【   RUN   】", "【  ITEM   】"};
    node->draw_callback = (draw_callback_c) draw_battle_menu;
    node->param = menu;
    menu->should_show = false;
    menu->menu = create_menu(choices, 5, parent, 7, 15, getmaxy(parent) - 8, 1, COLOR_PAIR(5));
    menu->battle_menu_node = node;
    node->require_redraw = false;

    return menu;
}

void draw_battle_menu(battle_menu_t *menu)
{
    if (menu->should_show == false)
    {
        return;
    }
    set_menu_attribute(menu->menu, COLOR_PAIR(5));

    draw_menu(menu->menu);
}

void delete_battle_menu(battle_menu_t *menu)
{
    delete_menu(menu->menu);
    free(menu);
}

battle_choice_e execute_battle_menu(battle_menu_t *menu)
{
    battle_choice_e return_choice = BATTLE_NONE;

    switch (menu->option)
    {
        case KEY_UP:
            execute_action(menu->menu, MENU_MOVE_UP);
            menu->battle_menu_node->require_redraw = true;
            break;
        case KEY_DOWN:
            execute_action(menu->menu, MENU_MOVE_DOWN);
            menu->battle_menu_node->require_redraw = true;
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



