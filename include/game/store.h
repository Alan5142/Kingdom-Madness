//
// Created by alan2 on 25/03/2020.
//

#ifndef PROGRA_STORE_H
#define PROGRA_STORE_H


#include <curses.h>
#include <stdbool.h>
#include "inventory.h"

struct player_t;
struct store_menu_t;
struct render_node_t;

typedef struct store_t
{
    WINDOW *window;
    struct store_menu_t *buy_menu;
    bool should_show;
    struct render_node_t *node;

} store_t;

store_t *create_store(WINDOW* parent, struct render_node_t* node);

void draw_store(store_t *store);

void delete_store(store_t *store);

#endif //PROGRA_STORE_H
