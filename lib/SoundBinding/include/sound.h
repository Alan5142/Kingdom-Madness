//
// Created by alan2 on 26/02/2020.
//

#ifndef PROGRA_SOUND_H
#define PROGRA_SOUND_H

#ifdef __cplusplus
extern "C"
{
#endif

 void *create_sound();

 void sound_open_file(void *music_ptr, const char *file);

 void play_sound(void *music_ptr);

 void delete_sound(void *music_ptr);

 void stop_sound(void *music_ptr);

 void set_loop(void *music_ptr, unsigned char loop);

#ifdef __cplusplus
}
#endif

#endif //PROGRA_SOUND_H
