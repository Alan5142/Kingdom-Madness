#include <curses.h>
#include <game/game.h>
#include <utils/colors.h>
#include "start_screen.h"
#include "play_music.h"
#include <windows.h>
#include <sound.h>
#include <time.h>


extern void HandleMenuToggle( unsigned char *ptr_ignore_resize);

int main()
{
    initscr();
    resize_term(40, 100);
    srand(time(0));
    if (has_colors())
        start_color();

    noecho();

    refresh();
    void *music = create_sound();

    char music_path[64];

    sprintf(music_path, "sound/intro/%d.ogg", rand() % 4 + 1);
    sound_open_file(music, music_path);
    set_loop(music, true);
    play_sound(music);

    init_color_pairs();
    switch (start_screen())
    {
        case START_SCREEN_QUIT:
            break;
        case START_SCREEN_PLAY:
            stop_sound(music);
            start_game();
            break;
    }


    delete_sound(music);

    endwin();
}
