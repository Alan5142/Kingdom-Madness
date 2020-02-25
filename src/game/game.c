//
// Created by alan2 on 25/02/2020.
//
#include "game/game.h"
#include "game/health.h"

void start_game(void)
{
    health_t *player_health = start_health();

    getch();
}
