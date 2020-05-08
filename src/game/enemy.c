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
        enemy.health = 1500;
        enemy.max_health = 2000;
        enemy.power = 19;
        enemy.reward = 1500;
        enemy.sprite = "enemy/DEVIL.txt";
        enemy.enemy_number = 3;
    }
    else if(pos_x == 1 && pos_y == 0)
    {
        enemy.health = 400;
        enemy.max_health = 800;
        enemy.power = 12;
        enemy.reward = 500;
        enemy.sprite = "enemy/REAPER.txt";
        enemy.enemy_number = 2;
    }
    else if(pos_x == 1 && pos_y == 1)
    {
        enemy.health = 200;
        enemy.max_health = 450;
        enemy.power = 9;
        enemy.reward = 200;
        enemy.sprite = "enemy/GHOST.txt";
        enemy.enemy_number = 1;
    }
    else if(pos_x == 0 && pos_y == 2)
    {
        enemy.health = 150;
        enemy.max_health = 250;
        enemy.power = 7;
        enemy.reward = 100;
        enemy.sprite = "enemy/DRAGON.txt";
        enemy.enemy_number = 0;
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
