//
// Created by alan2 on 25/02/2020.
//

#include "game/health.h"
#include <curses.h>
#include <stdlib.h>

const uint8_t START_HEALTH = 8;
const uint8_t MAX_HEALTH = 12;

// color constants
const uint16_t HEART_POINT_BACKGROUND = COLOR_WHITE;
const uint16_t HEART_POINT_FOREGROUND = COLOR_RED;
const uint16_t HEART_POINT = 0x01;

const uint16_t HEART_LOST_BACKGROUND = COLOR_WHITE;
const uint16_t HEART_LOST_FOREGROUND = COLOR_BLACK;
const uint16_t HEART_LOST = 0x02;

void draw_health(health_t *health)
{
    box(health->window, 0, 0);

    for (int i = 0; i < health->max_health; ++i)
    {
        const uint16_t color = i < health->health ? HEART_POINT : HEART_LOST;
        wattron(health->window, COLOR_PAIR(color));
        mvwaddch(health->window, 1, 1 + i, ACS_DIAMOND);
        wattroff(health->window, COLOR_PAIR(color));
    }

    wrefresh(health->window);
}

health_t *start_health(void)
{
    health_t *health = malloc(sizeof(health_t));
    health->window = newwin(3, 14, 1, 1);
    health->health = START_HEALTH;
    health->max_health = 12;

    init_pair(HEART_POINT, HEART_POINT_FOREGROUND, HEART_POINT_BACKGROUND);
    init_pair(HEART_LOST, HEART_LOST_FOREGROUND, HEART_LOST_BACKGROUND);
    draw_health(health);

    return health;
}
