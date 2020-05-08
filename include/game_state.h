//
// Created by alan2 on 30/03/2020.
//

#ifndef PROGRA_GAME_DATA_H
#define PROGRA_GAME_DATA_H

#include "game/inventory.h"
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

typedef struct item_data_t
{
    item_resource_e item;
    uint8_t quantity;
} item_data_t;

typedef struct game_state_t
{
    struct
    {
        unsigned int boss1: 1;
        unsigned int boss2: 1;
        unsigned int boss3: 1;
        unsigned int boss4: 1;
    } boss_defeated;
    uint8_t health;
    uint8_t max_health;
    uint32_t score;
    uint16_t money;
    item_data_t items[2][3];
    time_t saved_time;
} game_state_t;


void save_game(game_state_t *state, uint8_t slot);

void fill_game_state_inventory_data(game_state_t *state, inventory_t *inventory);

void get_inventory_from_game_state(inventory_t *inventory, game_state_t *state);

game_state_t load_game(uint8_t slot, bool *success);

#endif //PROGRA_GAME_DATA_H
