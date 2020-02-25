//
// Created by alan2 on 25/02/2020.
//
#include <play_music.h>
#include "game/game.h"
#include "game/health.h"

void start_game(void)
{
    play_music(MUSIC_GAME, true);
    health_t *player_health = start_health();

    getch();
}
