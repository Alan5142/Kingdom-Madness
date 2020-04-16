//
// Created by lghhs on 16/04/2020.
//

#include "game/battle.h"
#include "game/player/player.h"
#include <stdlib.h>
#include <utils/sprite.h>
#include <utils/render_graph.h>

battle_t *create_battle_screen(WINDOW* parent, render_node_t* node)
{
    battle_t *battle_screen = malloc(sizeof(battle_t));
    battle_screen->window = subwin(parent, getmaxy(parent) - 5, getmaxx(parent) - 4, 3, 2);
    battle_screen->should_show = false;
    node->param = battle_screen;
    battle_screen->node = node;
    //battle_screen->battle_menu = create_store_menu(store->window, add_child(node, (draw_callback_c)draw_store_menu));
    //store->buy_menu->should_show = false;

    return battle_screen;
}

void draw_battle_screen(battle_t *battle_screen, char *enemy_sprite)
{
    if (battle_screen->should_show == false)
    {
        return;
    }
    wclear(battle_screen->window);
    wattron(battle_screen->window, COLOR_PAIR(5));
    box(battle_screen->window, 0,0);
    //draw_sprite(battle_screen->window, 1, 28, enemy_sprite, NULL, NULL);
    wrefresh(battle_screen->window);
    //battle_screen->battle_menu->option = 0;
}

void delete_battle_screen(battle_t *battle_screen)
{
    //delete_store_menu(store->buy_menu);
    free(battle_screen);
}