#ifndef PROGRA_SOUND_H
#define PROGRA_SOUND_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum sound_state_e
    {
        SOUND_STOPPED,
        SOUND_PAUSED,
        SOUND_PLAYING
    } sound_state_e;


typedef void* sound_t;

sound_t create_sound();

int get_sound_milliseconds_duration(sound_t sound);

 void sound_open_file(sound_t music_ptr, const char *file);

 void play_sound(sound_t music_ptr);

 void delete_sound(sound_t music_ptr);

 void stop_sound(sound_t music_ptr);

 void set_loop(sound_t music_ptr, unsigned char loop);


 void set_volume(sound_t sound, float level);

sound_state_e sound_finished(sound_t sound);

#ifdef __cplusplus
}
#endif

#endif //PROGRA_SOUND_H
