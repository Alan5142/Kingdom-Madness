//
// Created by lghhs on 16/04/2020.
//

#ifndef PROGRA_ENEMY_H
#define PROGRA_ENEMY_H

#include <stdbool.h>
#include <curses.h>

typedef struct enemy_t
{
    int health;
    const char *sprite;
    int max_health;
    int power;
    int reward;
    int8_t enemy_number;
}enemy_t;

enemy_t create_enemy(int pos_x, int pos_y);

void delete_enemy(enemy_t *enemy);

void draw_enemy(WINDOW *parent, enemy_t *enemy);

#endif //PROGRA_ENEMY_H
