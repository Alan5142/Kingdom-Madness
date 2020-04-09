//
// Created by alan2 on 30/03/2020.
//

#include "game/game_state.h"
#include <stdlib.h>
#define WIN32_LEAN_AND_MEAN // <- para no incluir todo
#include <shlwapi.h>

bool get_save_path(char *buffer, uint8_t slot)
{
    char *app_data = getenv("APPDATA");
    sprintf(buffer, "%s\\proy_progra", app_data);
    if (CreateDirectory(buffer, NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
    {
        sprintf(buffer, "%s\\proy_progra\\%02dgame.save", app_data, slot);
        return true;
    }
    else
    {
        return false;
    }
}

bool get_load_path(char *buffer, uint8_t slot)
{
    char *app_data = getenv("APPDATA");
    sprintf(buffer, "%s\\proy_progra\\%02dgame.save", app_data, slot);

    return PathFileExists(buffer);
}

void save_bytes(FILE *file, const unsigned char *buffer, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        fprintf(file, "%02X", buffer[i]);
    }
}

void load_bytes(FILE *file, unsigned char *buffer, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        uint32_t byte_at_position;
        fscanf(file, "%02X", &byte_at_position);
        buffer[i] = byte_at_position;
    }
}

void save_game(game_state_t *state, uint8_t slot)
{
    char path[256];

    if (get_save_path(path, slot))
    {
        FILE *file = fopen(path, "w");
        state->saved_time = time(NULL);

        save_bytes(file, (const unsigned char *)&state->health, sizeof(state->health));
        save_bytes(file, (const unsigned char *)&state->max_health, sizeof(state->max_health));
        save_bytes(file, (const unsigned char *) &state->items, sizeof(state->items[0][0]) * 2 * 3);
        save_bytes(file, (const unsigned char *) &state->saved_time, sizeof(state->saved_time));
        save_bytes(file, (const unsigned char *) &state->boss_defeated, sizeof(state->boss_defeated));

        fclose(file);
    }
    else // ops, no debería pasar (:
    {
        abort();
    }
}

game_state_t load_game(uint8_t slot, bool *success)
{
    game_state_t saved_state;
    char path[256];

    *success = get_load_path(path, slot);

    if (*success)
    {
        FILE *file = fopen(path, "r");

        load_bytes(file, &saved_state.health, sizeof(saved_state.health));
        load_bytes(file, &saved_state.max_health, sizeof(saved_state.max_health));
        load_bytes(file, (unsigned char *) &saved_state.items, sizeof(saved_state.items[0][0]) * 2 * 3);
        load_bytes(file, (unsigned char *) &saved_state.saved_time, sizeof(saved_state.saved_time));
        load_bytes(file, (unsigned char *) &saved_state.boss_defeated, sizeof(saved_state.boss_defeated));

        fclose(file);
    }

    return saved_state;
}

void fill_game_state_inventory_data(game_state_t *state, inventory_t *inventory)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            state->items[i][j].quantity = inventory->items[i][j].quantity;
            state->items[i][j].item = inventory->items[i][j].item;
        }
    }
}

void get_inventory_from_game_state(inventory_t *inventory, game_state_t *state)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            inventory->items[i][j] = create_item(state->items[i][j].item);
            inventory->items[i][j].quantity = state->items[i][j].quantity;
        }
    }
}
