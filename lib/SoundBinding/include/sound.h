//
// Created by alan2 on 26/02/2020.
//

#ifndef PROGRA_SOUND_H
#define PROGRA_SOUND_H

#ifdef __cplusplus
extern "C"
{
#endif


typedef void* sound_t;

sound_t create_sound();

int get_sound_milliseconds_duration(sound_t sound);

 void sound_open_file(sound_t music_ptr, const char *file);

 void play_sound(sound_t music_ptr);

 void delete_sound(sound_t music_ptr);

 void stop_sound(sound_t music_ptr);

 void set_loop(sound_t music_ptr, unsigned char loop);

 void set_volume(sound_t sound, float level);

#ifdef __cplusplus
}
#endif

#endif //PROGRA_SOUND_H
