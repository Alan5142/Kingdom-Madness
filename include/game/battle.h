//
// Created by lghhs on 16/04/2020.
//

#ifndef PROGRA_BATTLE_H
#define PROGRA_BATTLE_H

#include <curses.h>
#include <stdbool.h>
#include <game/enemy.h>

struct player_t;
struct battle_menu_t;
struct render_node_t;

typedef struct battle_t
{
    WINDOW *window;
    struct battle_menu_t *battle_menu;
    bool should_show;
    struct render_node_t *node;
    enemy_t enemy;
} battle_t;

battle_t *create_battle_screen(WINDOW* parent, struct render_node_t* node);

void draw_battle_screen(battle_t *battle_screen);

void delete_battle_screen(battle_t *battle_screen);

#endif //PROGRA_BATTLE_H
