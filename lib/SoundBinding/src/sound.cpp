//
// Created by alan2 on 26/02/2020.
//
#include "sound.h"
#include <SFML/Audio.hpp>

sound_t create_sound()
{
    auto sound = new sf::Music;
    return sound;
}

void sound_open_file(sound_t music_ptr, const char *file)
{
    char path[64];
    sprintf(path, "sound/%s", file);
    static_cast<sf::Music*>(music_ptr)->openFromFile(path);
}

void play_sound(sound_t music_ptr)
{
    static_cast<sf::Music*>(music_ptr)->play();
}

void delete_sound(sound_t music_ptr)
{
    delete static_cast<sf::Music*>(music_ptr);
}

void stop_sound(sound_t music_ptr)
{
    static_cast<sf::Music*>(music_ptr)->stop();
}

void set_loop(sound_t music_ptr, unsigned char loop)
{
    static_cast<sf::Music*>(music_ptr)->setLoop(loop);
}

int get_sound_milliseconds_duration(sound_t sound)
{
    return static_cast<sf::Music*>(sound)->getDuration().asMilliseconds();
}

void set_volume(sound_t sound, float level)
{
    static_cast<sf::Music*>(sound)->setVolume(level);
}
