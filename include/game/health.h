//
// Created by alan2 on 25/02/2020.
//

#ifndef PROGRA_HEALTH_H
#define PROGRA_HEALTH_H


#include <stdbool.h>
#include <curses.h>
#include <stdint.h>

struct render_node_t;

typedef struct health_t
{
    WINDOW *window;
    uint16_t health;
    uint16_t max_health;
    struct render_node_t* health_node;
} health_t;

health_t *start_health(struct render_node_t *);

void draw_health(health_t *health);

void add_health(health_t *health, int16_t quantity);

bool is_alive(health_t *health);

void delete_health(health_t *health);


#endif //PROGRA_HEALTH_H
