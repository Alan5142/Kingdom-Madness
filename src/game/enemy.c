//
// Created by lghhs on 16/04/2020.
//

#include <game/enemy.h>
#include <assert.h>
#include <utils/sprite.h>
#include <stdlib.h>

enemy_t create_enemy(int pos_x, int pos_y)
{
    enemy_t enemy;
    if (pos_x == 0 && pos_y == 0)
    {
        enemy.health = 700;
        enemy.max_health = 1000;
        enemy.power = 15;
        enemy.reward = 1000;
        enemy.sprite = "enemy/DEVIL.txt";
    }
    else if(pos_x == 1 && pos_y == 0)
    {
        enemy.health = 400;
        enemy.max_health = 800;
        enemy.power = 10;
        enemy.reward = 500;
        enemy.sprite = "enemy/REAPER.txt";
    }
    else if(pos_x == 1 && pos_y == 1)
    {
        enemy.health = 200;
        enemy.max_health = 600;
        enemy.power = 7;
        enemy.reward = 100;
        enemy.sprite = "enemy/GHOST.txt";
    }
    else if(pos_x == 0 && pos_y == 2)
    {
        enemy.health = 100;
        enemy.max_health = 300;
        enemy.power = 5;
        enemy.reward = 50;
        enemy.sprite = "enemy/DRAGON.txt";
    }
    else
    {
        abort();
    }

    return enemy;
}

void draw_enemy(WINDOW *parent, enemy_t *enemy)
{
    draw_sprite(parent, 2, getmaxx(parent) - 62, enemy->sprite, NULL, NULL);
}
