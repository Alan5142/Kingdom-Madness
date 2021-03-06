//
// Created by lghhs on 16/04/2020.
//

#include "game/battle.h"
#include "game/player/player.h"
#include <game/battle_menu.h>
#include <stdlib.h>
#include <utils/colors.h>
#include <utils/render_graph.h>
#include <utils/sprite.h>

battle_t *create_battle_screen(WINDOW *parent, render_node_t *node)
{
    battle_t *battle_screen    = malloc(sizeof(battle_t));
    battle_screen->rematch     = false;
    battle_screen->window      = subwin(parent, getmaxy(parent), getmaxx(parent), 1, 0);
    battle_screen->should_show = false;
    node->param                = battle_screen;
    battle_screen->node        = node;
    battle_screen->battle_menu =
        create_battle_menu(battle_screen->window, add_child(node, (draw_callback_c)draw_battle_menu));
    battle_screen->battle_menu->should_show = false;

    return battle_screen;
}

void draw_battle_screen(battle_t *battle_screen)
{
    if (battle_screen->should_show == false)
    {
        return;
    }
    wclear(battle_screen->window);
    wattron(battle_screen->window, COLOR_PAIR(5));
    box(battle_screen->window, 0, 0);
    if (battle_screen->rematch)
    {
        wattroff(battle_screen->window, COLOR_PAIR(5));
        wattron(battle_screen->window, COLOR_PAIR(REMATCH_COLOR_PAIR));

        draw_enemy(battle_screen->window, &battle_screen->enemy);

        wattroff(battle_screen->window, COLOR_PAIR(REMATCH_COLOR_PAIR));
        wattron(battle_screen->window, COLOR_PAIR(5));
    }
    else
    {
        draw_enemy(battle_screen->window, &battle_screen->enemy);
    }
    draw_sprite(battle_screen->window, getmaxy(battle_screen->window) - 26, 1, "PLAYER.txt", NULL, NULL);
    wrefresh(battle_screen->window);
    battle_screen->battle_menu->option = 0;
    execute_battle_menu(battle_screen->battle_menu);
}

void delete_battle_screen(battle_t *battle_screen)
{
    delete_battle_menu(battle_screen->battle_menu);
    free(battle_screen);
}
