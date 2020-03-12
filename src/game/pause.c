//
// Created by alan2 on 11/03/2020.
//

#include "game/pause.h"
#include <stdlib.h>

pause_menu_t *create_pause_menu(WINDOW *parent)
{
    pause_menu_t *menu = malloc(sizeof(pause_menu_t));
    static const char *choices[] = {"【 Continuar 】", "【 Inventario】", "【  Guardar  】", "【   Salir   】"};

    menu->menu = create_menu(choices, 4, parent, 6, 17, getmaxy(stdscr) / 2 - 2, getmaxx(stdscr) / 2 - 8, COLOR_PAIR(5));
    draw_pause_menu(menu, MENU_NONE);

    return menu;
}

menu_choice_e draw_pause_menu(pause_menu_t *menu, int option)
{
    set_menu_attribute(menu->menu, COLOR_PAIR(5));
    menu_choice_e return_choice = MENU_NONE;

    switch (option)
    {
        case KEY_UP:
            execute_action(menu->menu, MENU_MOVE_UP);
            break;
        case KEY_DOWN:
            execute_action(menu->menu, MENU_MOVE_DOWN);
            break;
        case 10:
            return_choice = execute_action(menu->menu, MENU_ENTER);
        default:
            break;
    }
    draw_menu(menu->menu);
    return return_choice;
}

void delete_pause_menu(pause_menu_t *menu)
{
    delete_menu(menu->menu);
    free(menu);
}
