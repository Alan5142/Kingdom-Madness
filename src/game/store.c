//
// Created by alan2 on 25/03/2020.
//
#include "game/store.h"
#include "game/player/player.h"
#include <stdlib.h>
#include <utils/menu.h>
#include <utils/sprite.h>
#include <utils/render_graph.h>
#include <game/store_menu.h>

store_t *create_store(WINDOW* parent, render_node_t* node)
{
    store_t *store = malloc(sizeof(store_t));
    //static const char *options[ITEM_NONE];
    store->window = subwin(parent, getmaxy(parent) - 5, getmaxx(parent) - 4, 3, 2);
    store->should_show = false;
    node->param = store;
    store->node = node;
    /*for (int i = 0; i < ITEM_NONE; ++i)
    {
        options[i] = get_item_display_name((item_resource_e) i);
    }*/
    store->buy_menu = create_store_menu(store->window, add_child(node, (draw_callback_c)draw_store_menu));
    store->buy_menu->should_show = false;

    return store;
}

void draw_store(store_t *store)
{
    if (store->should_show == false)
    {
        return;
    }
    wclear(store->window);
    wattron(store->window, COLOR_PAIR(5));
    box(store->window, 0,0);
    draw_sprite(store->window, 1, 28, "store/STORE_SIGN.txt", NULL, NULL);
    draw_sprite(store->window, 10, 20, "store/STORE_SELLER.txt", NULL, NULL);
    wrefresh(store->window);
    store->buy_menu->option = 0;
    execute_store_menu(store->buy_menu);
}

void delete_store(store_t *store)
{
    delete_store_menu(store->buy_menu);
    free(store);
}
