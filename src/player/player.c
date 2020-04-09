//
// Created by alan2 on 03/03/2020.
//
#include "game/player/player.h"
#include <stdlib.h>
#include "game/health.h"

typedef struct {
    int16_t y;
    int16_t x;
}coordinates_t;

coordinates_t player_coordinates [3][2]= {
        {{9, 7},{9,56}},
        {{26,25},{26,66}},
        {{36,49},{38,80}}
};

player_t *create_player(WINDOW *parent, health_t *health)
{
    player_t *player = malloc(sizeof(player_t));
    player->owning_window = parent;
    player->health = health;
    player->x = player_coordinates[2][1].x;
    player->y = player_coordinates[2][1].y;
    player->previous_x = player->x;
    player->previous_y = player->y;
    player->inventory = create_inventory(parent);
    player->armor_multiplier = 1.f;
    player->location_x = 1;
    player->location_y = 2;
    return player;
}

void delete_player(player_t *player)
{
    delete_inventory(player->inventory);
    delete_health(player->health);
    free(player);
}

void draw_player(player_t *player)
{
    if (player->inventory->shown) return;
    mvwprintw(player->owning_window, player->previous_y, player->previous_x, " ");
    mvwaddstr(player->owning_window, player->y, player->x, "⛹");
    wrefresh(player->owning_window);
}

bool process_player_input(player_t *player, int key)
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
            player->location_y--;
            if (player->location_y == -1)
                player->location_y = 0;
            break;
        case KEY_DOWN:
            player->location_y++;
            if (player->location_y == 3)
                player->location_y = 2;
            break;
        case KEY_RIGHT:
            player->location_x++;
            if (player->location_x == 2)
                player->location_x = 1;
            break;
        case KEY_LEFT:
            player->location_x--;
            if (player->location_x == -1)
                player->location_x = 0;
            break;
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
