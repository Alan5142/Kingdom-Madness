//
// Created by alan2 on 11/03/2020.
//
#ifndef PROGRA_INVENTORY_H
#define PROGRA_INVENTORY_H

#include <stdint.h>
#include <stdbool.h>
#include "health.h"

typedef enum
{
    POTION_LOW,
    POTION_MEDIUM,
    ARMOR_LOW,
    ARMOR_MEDIUM,
    POWER_LOW,
    POWER_MEDIUM,
    NONE
} item_resource_e;

typedef void(*item_effect_c)(struct player_t *);

typedef struct
{
    uint8_t quantity;
    item_resource_e item;
    item_effect_c item_effect;
} item_t;

typedef struct inventory_t
{
    WINDOW *window;
    item_t items[2][3];
    bool shown;
} inventory_t;

inventory_t *create_inventory(WINDOW *parent);

void draw_inventory(inventory_t *inventory);

void delete_inventory(inventory_t *inventory);

#endif //PROGRA_INVENTORY_H
