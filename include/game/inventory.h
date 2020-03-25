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
    ITEM_POTION_LOW = 0,
    ITEM_POTION_MEDIUM,
    ITEM_ARMOR_LOW,
    ITEM_ARMOR_MEDIUM,
    ITEM_POWER_LOW,
    ITEM_POWER_MEDIUM,
    ITEM_NONE
} item_resource_e;


struct player_t;

typedef void(*item_effect_c)(struct player_t *);

typedef struct item_t
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

item_t create_item(item_resource_e item);

const char *get_item_display_name(item_resource_e item);

#endif //PROGRA_INVENTORY_H
