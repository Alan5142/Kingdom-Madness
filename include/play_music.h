//
// Created by alan2 on 25/02/2020.
//

#ifndef PROGRA_PLAY_MUSIC_H
#define PROGRA_PLAY_MUSIC_H
#include <stdbool.h>
typedef enum
{
    MUSIC_INTRO,
    MUSIC_GAME
} music_t;

void play_music(music_t music, bool loop);

#endif //PROGRA_PLAY_MUSIC_H
