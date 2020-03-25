//
// Created by alan2 on 25/03/2020.
//
#include "game/store.h"
#include "game/player/player.h"
#include <stdlib.h>
#include <utils/menu.h>
#include <utils/sprite.h>

store_t *create_store(WINDOW *parent, uint16_t x, uint16_t y)
{
    store_t *store = malloc(sizeof(store_t));
    static const char *options[ITEM_NONE];
    store->window = subwin(parent, 35, getmaxx(parent) - 2, y, x);
    store->should_show = false;
    for (int i = 0; i < ITEM_NONE; ++i)
    {
        options[i] = get_item_display_name((item_resource_e) i);
    }
    store->buy_menu = create_menu(options, ITEM_NONE, store->window, ITEM_NONE + 3, 20, 20, 10, 5);

    return store;
}

void draw_store(store_t *store)
{
    wclear(store->window);
    wattron(store->window, COLOR_PAIR(5));
    draw_sprite(store->window, 0, 0, "STORE_INTERNAL.txt", NULL, NULL);
    draw_menu(store->buy_menu);
    wrefresh(store->window);
}

void delete_store(store_t *store)
{
    delete_menu(store->buy_menu);
    free(store);
}
