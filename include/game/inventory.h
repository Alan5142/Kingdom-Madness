//
// Created by alan2 on 11/03/2020.
//
#ifndef PROGRA_INVENTORY_H
#define PROGRA_INVENTORY_H
#include <stdint.h>
#include "player/player.h"
#include "health.h"

typedef enum
{
    POTION_LOW,
    POTION_MEDIUM,
} item_resource_e;

typedef void(*item_effect_c)(player_t*);

typedef struct
{
    uint8_t quantity;
    item_resource_e item;
    item_effect_c item_effect;
} item_t;

typedef struct inventory_t
{
    WINDOW *window;
    item_t items[4][4];
} inventory_t;

inventory_t *create_inventory_screen(WINDOW *parent);

void draw_inventory(inventory_t *inventory);

void delete_inventory(inventory_t *inventory);

#endif //PROGRA_INVENTORY_H