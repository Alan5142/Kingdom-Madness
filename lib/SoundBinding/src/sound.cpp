//
// Created by alan2 on 26/02/2020.
//
#include "sound.h"
#include <SFML/Audio.hpp>

void *create_sound()
{
    auto sound = new sf::Music;
    return sound;
}

void sound_open_file(void *music_ptr, const char *file)
{
    static_cast<sf::Music*>(music_ptr)->openFromFile(file);
}

void play_sound(void *music_ptr)
{
    static_cast<sf::Music*>(music_ptr)->play();
}

void delete_sound(void *music_ptr)
{
    delete static_cast<sf::Music*>(music_ptr);
}

void stop_sound(void *music_ptr)
{
    static_cast<sf::Music*>(music_ptr)->stop();
}

void set_loop(void *music_ptr, unsigned char loop)
{
    static_cast<sf::Music*>(music_ptr)->setLoop(loop);
}
