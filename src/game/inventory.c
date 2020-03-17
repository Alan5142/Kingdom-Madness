//
// Created by alan2 on 11/03/2020.
//
#include "game/inventory.h"
#include <stdlib.h>
#include <utils/sprite.h>
#include <utils/colors.h>

void on_start_draw_potion(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && y > 1 && x != 0)
    {
        wattron(window, COLOR_PAIR(POTION_COLOR_PAIR));
    }
}

void on_end_draw_potion(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && y > 1 && x != 0)
    {
        wattroff(window, COLOR_PAIR(POTION_COLOR_PAIR));
    }
}

inventory_t *create_inventory(WINDOW *parent)
{
    inventory_t *inventory = malloc(sizeof(inventory_t));
    inventory->window = subwin(parent, getmaxy(parent) - 5, getmaxx(parent) - 4, 3, 2);
    inventory->shown = false;
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
        mvwvline(inventory->window, 1, getmaxx(inventory->window) / 4 * (i + 1), 0, getmaxy(inventory->window));
    }
    for (int j = 0; j < 3; ++j)
    {
        mvwhline(inventory->window, getmaxy(inventory->window) / 4 * (j + 1), 0, 0, getmaxx(inventory->window));
    }
    box(inventory->window, 0, 0);

    draw_sprite(inventory->window, 2, getmaxx(inventory->window) / 8 - 3, "potion.txt", on_start_draw_potion, on_end_draw_potion);
    wattron(inventory->window, A_REVERSE);
    mvwprintw(inventory->window, 7, getmaxx(inventory->window) / 8 - 1, "%02d", 45);
    wattroff(inventory->window, A_REVERSE);

    wrefresh(inventory->window);
}
