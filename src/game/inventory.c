//
// Created by alan2 on 11/03/2020.
//
#include "game/inventory.h"
#include <stdlib.h>
#include <utils/sprite.h>
#include <utils/colors.h>

void on_start_draw_potion_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw) {
    if (character_to_draw == ' ' && (y > 2 && x != 0 && y < 6) | (y > 0 && y < 3 && x > 1 && x < 9)) {
        wattron(window, COLOR_PAIR(POTION_LOW_COLOR_PAIR));
    }
}

void on_end_draw_potion_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw) {
    if (character_to_draw == ' ' && (y > 2 && x != 0 && y < 6) | (y > 0 && y < 3 && x > 1 && x < 9)) {
        wattroff(window, COLOR_PAIR(POTION_LOW_COLOR_PAIR));
    }
}

void on_start_draw_potion_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y > 2 && x != 0 && y < 6) | (y > 0 && y < 3 && x > 1 && x < 9)) {
        wattron(window, COLOR_PAIR(POTION_MEDIUM_COLOR_PAIR));
    }
}

void on_end_draw_potion_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y > 2 && x != 0 && y < 6) | (y > 0 && y < 3 && x > 1 && x < 9)) {
        wattroff(window, COLOR_PAIR(POTION_MEDIUM_COLOR_PAIR));
    }
}

void on_start_draw_armor_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y > 0 && y <= 3) | (y == 4 && x > 1) | (y == 5 && x > 2)) {
        wattron(window, COLOR_PAIR(ARMOR_LOW_COLOR_PAIR));
    }
}

void on_end_draw_armor_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y > 0 && y <= 3) | (y == 4 && x > 1) | (y == 5 && x > 2)) {
        wattroff(window, COLOR_PAIR(ARMOR_LOW_COLOR_PAIR));
    }
}

void on_start_draw_armor_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y > 0 && y <= 3) | (y == 4 && x > 1) | (y == 5 && x > 2)) {
        wattron(window, COLOR_PAIR(ARMOR_MEDIUM_COLOR_PAIR));
    }
}

void on_end_draw_armor_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y > 0 && y <= 3) | (y == 4 && x > 1) | (y == 5 && x > 2)) {
        wattroff(window, COLOR_PAIR(ARMOR_MEDIUM_COLOR_PAIR));
    }
}

void on_start_draw_power_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y == 1 | y == 2 && x > 2) | (y == 3 && x > 0) | (y > 3 && x > 3)) {
        wattron(window, COLOR_PAIR(POWER_LOW_COLOR_PAIR));
    }
}

void on_end_draw_power_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y == 1 | y == 2 && x > 2) | (y == 3 && x > 0) | (y > 3 && x > 3)) {
        wattroff(window, COLOR_PAIR(POWER_LOW_COLOR_PAIR));
    }
}

void on_start_draw_power_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y == 1 | y == 2 && x > 2) | (y == 3 && x > 0) | (y > 3 && x > 3)) {
        wattron(window, COLOR_PAIR(POWER_MEDIUM_COLOR_PAIR));
    }
}

void on_end_draw_power_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (y == 1 | y == 2 && x > 2) | (y == 3 && x > 0) | (y > 3 && x > 3)) {
        wattroff(window, COLOR_PAIR(POWER_MEDIUM_COLOR_PAIR));
    }
}

inventory_t *create_inventory(WINDOW *parent) {
    inventory_t *inventory = malloc(sizeof(inventory_t));
    inventory->window = subwin(parent, getmaxy(parent) - 5, getmaxx(parent) - 4, 3, 2);
    inventory->shown = false;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 2; j++) {
            inventory->items[i][j].item = NONE;
            inventory->items[i][j].quantity = 0;
            inventory->items[i][j].item_effect = NULL;
        }
    }
    return inventory;
}

void delete_inventory(inventory_t *inventory) {
    delwin(inventory->window);
    free(inventory);
}

void draw_inventory(inventory_t *inventory) {
    wclear(inventory->window);
    wattron(inventory->window, COLOR_PAIR(5));

    for (int i = 0; i < 2; ++i) {
        mvwvline(inventory->window, 1, getmaxx(inventory->window) / 3 * (i + 1), 0, getmaxy(inventory->window));
    }
    for (int j = 0; j < 1; ++j) {
        mvwhline(inventory->window, getmaxy(inventory->window) / 2 * (j + 1), 0, 0, getmaxx(inventory->window));
    }
    box(inventory->window, 0, 0);

    for (int i = 0; i <= 1; i++)
    {
        bool end = false;
        for (int j = 0; j <= 2; j++)
        {
            if (inventory->items[i][j].item == NONE)
            {
                end = true;
                break;
            } else {
                switch (inventory->items[i][j].item)
                {

                    case POTION_LOW:
                        draw_sprite(inventory->window,
                                  i * getmaxy(inventory->window) / 2 + 5,
                                    j * getmaxx(inventory->window) / 3 + getmaxx(inventory->window) / 6 -5,
                                    "POTION.txt", on_start_draw_potion_low,
                                    on_end_draw_potion_low);
                        break;
                    case POTION_MEDIUM:
                        draw_sprite(inventory->window,
                                    i * getmaxy(inventory->window) / 2 + 3,
                                    j * getmaxx(inventory->window) / 3 + 4,
                                    "POTION.txt", on_start_draw_potion_medium,
                                    on_end_draw_potion_medium);
                        break;
                    case ARMOR_LOW:
                        draw_sprite(inventory->window,
                                    i * getmaxy(inventory->window) / 2 + 3,
                                    j * getmaxx(inventory->window) / 3 + 4,
                                    "ARMOR.txt", on_start_draw_armor_low,
                                    on_end_draw_armor_low);
                        break;
                    case ARMOR_MEDIUM:
                        draw_sprite(inventory->window,
                                    i * getmaxy(inventory->window) / 2 + 3,
                                    j * getmaxx(inventory->window) / 3 + 4,
                                    "ARMOR.txt", on_start_draw_armor_medium,
                                    on_end_draw_armor_medium);
                        break;
                    case POWER_LOW:
                        draw_sprite(inventory->window,
                                    i * getmaxy(inventory->window) / 2 + 3,
                                    j * getmaxx(inventory->window) / 3 + 4,
                                    "POWER.txt", on_start_draw_power_low,
                                    on_end_draw_power_low);
                        break;
                    case POWER_MEDIUM:
                        draw_sprite(inventory->window,
                                    i * getmaxy(inventory->window) / 2 + 3,
                                    j * getmaxx(inventory->window) / 3 + 4,
                                    "POWER.txt", on_start_draw_power_medium,
                                    on_end_draw_power_medium);
                        break;
                    case NONE:
                        break;
                }
                wattron(inventory->window, A_REVERSE);
                mvwprintw(inventory->window, i*getmaxy(inventory->window) / 2 + 13, j * getmaxx(inventory->window) / 3 + getmaxx(inventory->window) / 6 - 1 , "%03d", inventory->items[i][j].quantity);
                wattroff(inventory->window, A_REVERSE);
            }
        }
        if (end) {
            break;
        }
    }

    wrefresh(inventory->window);
}
