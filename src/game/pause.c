//
// Created by alan2 on 11/03/2020.
//

#include "game/pause.h"
#include <stdlib.h>
#include <utils/render_graph.h>

pause_menu_t *create_pause_menu(WINDOW *parent, render_node_t *node)
{
    pause_menu_t *menu = malloc(sizeof(pause_menu_t));
    static const char *choices[] = {"【 Continuar 】", "【 Inventario】", "【  Guardar  】", "【   Salir   】"};
    node->draw_callback = (draw_callback_c) draw_pause_menu;
    node->param = menu;
    menu->should_show = false;
    menu->menu = create_menu(choices, 4, parent, 6, 17, getmaxy(stdscr) / 2 - 2, getmaxx(stdscr) / 2 - 8, COLOR_PAIR(5));
    menu->current_choice = &menu->menu->current_choice;
    menu->pause_node = node;
    node->require_redraw = false;

    return menu;
}

void draw_pause_menu(pause_menu_t *menu)
{
    set_menu_attribute(menu->menu, COLOR_PAIR(5));

    draw_menu(menu->menu);
}

void delete_pause_menu(pause_menu_t *menu)
{
    delete_menu(menu->menu);
    free(menu);
}

menu_choice_e execute_pause_menu_action(pause_menu_t *menu)
{
    menu_choice_e return_choice = MENU_NONE;

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
