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

        //mvwaddch(health->window, 1, 1 + i, ACS_DIAMOND);
        // mvwaddrawch(health->window, 1, 1 + i, 2665);
        mvwaddwstr(health->window, 0, i, L"♥");

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

void clean_health(health_t *health)
{
    delwin(health->window);
    free(health);
}
