//
// Created by alan2 on 11/03/2020.
//
#include "game/inventory.h"
#include <stdlib.h>


inventory_t *create_inventory_screen(WINDOW *parent)
{
    inventory_t *inventory = malloc(sizeof(inventory_t));
    inventory->window = subwin(parent, 10, 20, 10, 10);
    box(inventory->window, 0, 0);
    draw_inventory(inventory);
    return inventory;
}

void delete_inventory(inventory_t *inventory)
{
    delwin(inventory->window);
    free(inventory);
}

void draw_inventory(inventory_t *inventory)
{

    for (int i = 0; i < 4; ++i)
    {
        mvwvline(inventory->window, 0, 3 * (i + 1), 0, 20);
        for (int j = 0; j < 4; ++j)
        {
            mvwhline(inventory->window, 3 * (j + 1), 0, 0, 20);
        }
    }
    wrefresh(inventory->window);
}
