//
// Created by alan2 on 03/03/2020.
//
#include "game/player/player.h"
#include <stdlib.h>
#include "game/health.h"

player_t *create_player(WINDOW *parent, health_t *health)
{
    player_t *player = malloc(sizeof(player_t));
    player->owning_window = parent;
    player->health = health;
    player->x = getmaxx(parent) / 2;
    player->y = getmaxy(parent) / 2;
    player->previous_x = player->x;
    player->previous_y = player->y;
    player->inventory = create_inventory(parent);
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

        return true;
    }
    switch (key)
    {
        case KEY_UP:
            player->previous_y = player->y;
            player->previous_x = player->x;
            player->y--;
            if (player->y == -1)
                player->y = 0;
            break;
        case KEY_DOWN:
            player->previous_y = player->y;
            player->previous_x = player->x;
            player->y++;
            if (player->y == getmaxy(player->owning_window))
                player->y = getmaxy(player->owning_window) - 1;
            break;
        case KEY_RIGHT:
            player->previous_y = player->y;
            player->previous_x = player->x;
            player->x++;
            if (player->x == getmaxx(player->owning_window))
                player->x = getmaxx(player->owning_window) - 1;
            break;
        case KEY_LEFT:
            player->previous_y = player->y;
            player->previous_x = player->x;
            player->x--;
            if (player->x == -1)
                player->x = 0;
            break;
        default:
            require_redraw = false;
            break;
    }

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
