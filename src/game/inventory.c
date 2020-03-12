//
// Created by alan2 on 11/03/2020.
//
#include "game/inventory.h"
#include <stdlib.h>


inventory_t *create_inventory_screen(WINDOW *parent)
{
    inventory_t *inventory = malloc(sizeof(inventory_t));
    inventory->window = subwin(parent, getmaxy(parent)-5, getmaxx(parent)-4, 3, 2);
    return inventory;
}

void delete_inventory(inventory_t *inventory)
{
    delwin(inventory->window);
    free(inventory);
}

void draw_inventory(inventory_t *inventory)
{
    wclear(inventory->window);
    wattron(inventory->window, COLOR_PAIR(5));
    for (int i = 0; i < 3; ++i)
    {
        mvwvline(inventory->window, 1, getmaxx(inventory->window)/4 * (i + 1), 0, getmaxy(inventory->window));
    }
    for (int j = 0; j < 3; ++j)
    {
        mvwhline(inventory->window, getmaxy(inventory->window)/4 * (j + 1), 0, 0, getmaxx(inventory->window));
    }
    box(inventory->window,0,0);
    wrefresh(inventory->window);
}
