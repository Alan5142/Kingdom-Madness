//
// Created by alan2 on 03/03/2020.
//
#include "game/player/player.h"
#include "game/health.h"
#include <game/game_state.h>
#include <stdlib.h>

typedef struct
{
    int16_t y;
    int16_t x;
} coordinates_t;

coordinates_t player_coordinates[3][2] = {{{9, 7}, {9, 56}}, {{26, 25}, {26, 66}}, {{36, 49}, {38, 80}}};

player_t *create_player(WINDOW *parent, health_t *health, magic_t *magic)
{
    player_t *player          = malloc(sizeof(player_t));
    player->owning_window     = parent;
    player->health            = health;
    player->x                 = player_coordinates[2][1].x;
    player->y                 = player_coordinates[2][1].y;
    player->previous_x        = player->x;
    player->previous_y        = player->y;
    player->inventory         = create_inventory(parent);
    player->damage_multiplier = 1.f;
    player->armor_multiplier  = 1.f;
    player->location_x        = 1;
    player->location_y        = 2;
    player->magic = magic;
    return player;
}

void delete_player(player_t *player)
{
    delete_inventory(player->inventory);
    delete_health(player->health);
    delete_magic(player->magic);
    free(player);
}

void draw_player(player_t *player)
{
    if (player->inventory->shown)
        return;
    mvwprintw(player->owning_window, player->previous_y, player->previous_x, " ");
    mvwaddstr(player->owning_window, player->y, player->x, "⛹");
    wrefresh(player->owning_window);
}

bool can_move_to_position(uint16_t pos_x, uint16_t pos_y, game_state_t *state)
{
    if (pos_x == 0 && pos_y == 0)
    {
        return state->boss_defeated.boss3;
    }
    else if (pos_x == 1 && pos_y == 0)
    {
        return state->boss_defeated.boss2;
    }
    else if ((pos_x == 0 && pos_y == 1) || (pos_x == 1 && pos_y == 1))
    {
        return state->boss_defeated.boss1;
    }
    return true;
}

bool process_player_input(player_t *player, int key, game_state_t *state)
{
    bool require_redraw = true;
    if (player->inventory->shown)
    {
        return false;
    }
    player->previous_y = player->y;
    player->previous_x = player->x;
    switch (key)
    {
        case KEY_UP:
        {
            int next_y_location = player->location_y - 1;
            if (next_y_location == -1)
                next_y_location = 0;

            if (!can_move_to_position(player->location_x, next_y_location, state))
                return false;
            player->location_y = next_y_location;
            break;
        }
        case KEY_DOWN:
        {
            int next_y_location = player->location_y + 1;
            if (next_y_location == 3)
                next_y_location = 2;

            if (!can_move_to_position(player->location_x, next_y_location, state))
                return false;
            player->location_y = next_y_location;
            break;
        }
        case KEY_RIGHT:
        {
            int next_x_location = player->location_x + 1;
            if (next_x_location == 2)
                next_x_location = 1;

            if (!can_move_to_position(next_x_location, player->location_y, state))
                return false;
            player->location_x = next_x_location;
            break;
        }
        case KEY_LEFT:
        {
            int next_x_location = player->location_x - 1;
            if (next_x_location == -1)
                next_x_location = 0;

            if (!can_move_to_position(next_x_location, player->location_y, state))
                return false;
            player->location_x = next_x_location;
            break;
        }
        default:
            require_redraw = false;
            break;
    }
    player->x = player_coordinates[player->location_y][player->location_x].x;
    player->y = player_coordinates[player->location_y][player->location_x].y;
    return require_redraw;
}

void draw_player_inventory(player_t *player)
{
    player->inventory->shown = true;
    draw_inventory(player->inventory);
}

void hide_player_inventory(player_t *player)
{
    wclear(player->inventory->window);
    wrefresh(player->inventory->window);
    player->inventory->shown = false;
}

void take_damage(player_t *player, uint8_t quantity)
{
    int8_t health_result = (int8_t)((float)quantity * player->armor_multiplier);
    add_health(player->health, -health_result);
}
