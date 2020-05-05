#include <utils/sound_manager.h>
#include <stdlib.h>
#include <stdint.h>

sound_t SOUNDS[64];
static size_t SOUNDS_COUNT = 0;

void add_sound_to_manager(sound_t sound)
{
    SOUNDS[SOUNDS_COUNT++] = sound;
}

int sort_sound_cmp(const void *_a, const void *_b)
{
    (void)_b;
    sound_t *a = (sound_t*)_a;
    return *a == NULL ? 1 : -1;
}

void destroy_finished_sounds()
{
    for (size_t i = 0; i < SOUNDS_COUNT; ++i)
    {
        if (sound_finished(SOUNDS[i]) == SOUND_STOPPED)
        {
            delete_sound(SOUNDS[i]);
            SOUNDS[i] = NULL;
        }
    }
    qsort(SOUNDS, 64, sizeof(sound_t), sort_sound_cmp);
    for (size_t i = 0; i < 64; ++i)
    {
        if (SOUNDS[i] == NULL)
        {
            SOUNDS_COUNT = i;
            break;
        }
    }
}
