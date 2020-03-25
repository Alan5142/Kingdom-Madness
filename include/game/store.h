//
// Created by alan2 on 25/03/2020.
//

#ifndef PROGRA_STORE_H
#define PROGRA_STORE_H


#include <curses.h>
#include <stdbool.h>
#include "inventory.h"

struct player_t;
struct menu_t;

typedef struct store_t
{
    WINDOW *window;
    struct menu_t *buy_menu;
    bool should_show;
} store_t;

store_t *create_store(WINDOW *parent, uint16_t x, uint16_t y);

void draw_store(store_t *store);

void delete_store(store_t *store);

#endif //PROGRA_STORE_H
