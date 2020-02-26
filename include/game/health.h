//
// Created by alan2 on 25/02/2020.
//

#ifndef PROGRA_HEALTH_H
#define PROGRA_HEALTH_H


#include <stdbool.h>
#include <curses.h>
#include <stdint.h>

typedef struct
{
    WINDOW *window;
    uint8_t health;
    uint8_t max_health;
} health_t;

health_t *start_health(void);

void draw_health(health_t *health);

bool is_alive(health_t *health);

void clean_health(health_t *health);


#endif //PROGRA_HEALTH_H
