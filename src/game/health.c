//
// Created by alan2 on 25/02/2020.
//

#include "game/health.h"
#include "utils/colors.h"
#include <curses.h>
#include <stdlib.h>

const uint8_t START_HEALTH = 8;
const uint8_t MAX_HEALTH = 12;

void draw_health(health_t *health)
{
    resize_window(health->window, 1, health->max_health);

    for (int i = 0; i < health->max_health; ++i)
    {
        const uint16_t color = i < health->health ? HEART_POINT_COLOR_PAIR : HEART_LOST_COLOR_PAIR;
        wattron(health->window, COLOR_PAIR(color));
        mvwaddstr(health->window, 0, i, "♥");
        wattroff(health->window, COLOR_PAIR(color));
    }

    wrefresh(health->window);
}

health_t *start_health(void)
{
    health_t *health = malloc(sizeof(health_t));
    health->window = newwin(1, 14, 0, 0);
    health->health = START_HEALTH;
    health->max_health = START_HEALTH;
    draw_health(health);

    return health;
}

void delete_health(health_t *health)
{
    delwin(health->window);
    free(health);
}

void add_health(health_t *health, int8_t quantity)
{
    if ((int8_t) health->health + quantity < 0) // quantity < 0
    {
        health->health = 0;
    }
    else if (health->health > health->max_health)
    {
        health->health = health->max_health;
    }
    else
    {
        health->health += quantity;
    }
}
