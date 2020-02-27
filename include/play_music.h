//
// Created by alan2 on 25/02/2020.
//

#ifndef PROGRA_PLAY_MUSIC_H
#define PROGRA_PLAY_MUSIC_H
#include <stdbool.h>
typedef enum music_t
{
    MUSIC_INTRO,
    MUSIC_GAME
} music_t;

/**
 * Reproduce un sonido en formato ".WAV", los sonidos están definidos en la enumeración \ref music_t
 * @param music sonido a reproducir, debe ser miembro de music_t
 * @param loop Indica si el sonido se reproducirá en loop o dejará de reproducirse en cuanto termine
 */
void play_music(music_t music);

#endif //PROGRA_PLAY_MUSIC_H
