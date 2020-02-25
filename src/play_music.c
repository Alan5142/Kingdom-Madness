//
// Created by alan2 on 25/02/2020.
//

#include "play_music.h"
#include <windows.h>

void play_music(music_t music, bool loop)
{
    unsigned flags = SND_ASYNC;
    if (loop)
        flags |= SND_LOOP;

    switch (music)
    {
        case MUSIC_INTRO:
            PlaySoundW(L"sound/intro.wav", NULL, flags);
            break;
        case MUSIC_GAME:
            PlaySoundW(L"sound/game.wav", NULL, flags);
            break;
    }
}
