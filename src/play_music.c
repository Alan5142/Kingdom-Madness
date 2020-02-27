//
// Created by alan2 on 25/02/2020.
//

#include "play_music.h"
#include <windows.h>
#include <wchar.h>
#include <time.h>
#include <sound.h>

void play_music(music_t music)
{
    unsigned flags = SND_ASYNC | SND_LOOP;
    wchar_t sound[256];
    switch (music)
    {
        case MUSIC_INTRO:
            swprintf(sound, 256, L"sound/intro/%d.wav", rand() % 3 + 1);
            PlaySoundW(sound, NULL, flags);
            break;
        case MUSIC_GAME:
            PlaySoundW(L"sound/game.wav", NULL, flags);
            break;
    }
}
