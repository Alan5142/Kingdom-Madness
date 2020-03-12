//
// Created by alan2 on 11/03/2020.
//
#include "utils/menu.h"
#include <stdlib.h>

menu_t *
create_menu(const char **options,
            int size,
            WINDOW *parent,
            uint16_t nlines,
            uint16_t ncolumns,
            uint16_t y,
            uint16_t x,
            chtype default_attribute)
{
    menu_t *menu = malloc(sizeof(menu_t));
    menu->length = size;
    menu->options = options;
    menu->current_choice = 0;
    menu->window = subwin(parent, nlines, ncolumns, y, x);
    wclear(menu->window);
    set_menu_attribute(menu, default_attribute);
    box(menu->window, 0, 0);
    execute_action(menu, -1);
    return menu;
}

void delete_menu(menu_t *menu)
{
    delwin(menu->window);
    free(menu);
}

void set_menu_attribute(menu_t *menu, chtype attribute)
{
    wattron(menu->window, attribute);
}

void clear_menu_attribute(menu_t *menu, chtype attribute)
{
    wattroff(menu->window, attribute);
}

int16_t execute_action(menu_t *menu, menu_action_t action)
{
    switch (action)
    {
        case MENU_MOVE_UP:
            menu->current_choice--;
            if (menu->current_choice == -1)
                menu->current_choice = menu->length - 1;
            break;
        case MENU_MOVE_DOWN:
            menu->current_choice++;
            if (menu->current_choice == menu->length)
                menu->current_choice = 0;
            break;
        case MENU_ENTER:
            return menu->current_choice;
        default:
            break;
    }

    for (int i = 0; i < menu->length; i++)
    {
        if (i == menu->current_choice)
        {
            wattron(menu->window, A_STANDOUT);
        }
        else
        {
            wattroff(menu->window, A_STANDOUT);
        }
        mvwprintw(menu->window, i + 1, 1, menu->options[i]);
    }
    return -1;
}

void draw_menu(menu_t *menu)
{
    wrefresh(menu->window);
}

