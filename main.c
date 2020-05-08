#include "game/game.h"
#include "start_screen.h"
#include <curses.h>
#include <sound.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <utils/colors.h>

int main()
{
    initscr();
    resize_term(40, 100);
    srand((unsigned int)time(NULL));
    if (has_colors())
        start_color();

    noecho();
    cbreak();

    refresh();
    sound_t music = create_sound();

    char music_path[64];

    sprintf(music_path, "intro/%d.ogg", rand() % 5 + 1);
    sound_open_file(music, music_path);
    set_loop(music, true);
    set_volume(music, 60);
    play_sound(music);

    init_color_pairs();
    start_screen_result_e result;
    while ((result = start_screen()) != START_SCREEN_QUIT)
    {
        stop_sound(music);
        switch (result)
        {
            case START_SCREEN_LOAD1:
                start_game(1);
                break;
            case START_SCREEN_LOAD2:
                start_game(2);
                break;
            case START_SCREEN_LOAD3:
                start_game(3);
                break;
            default:
                start_game(-1);
                break;
        }
        clear();
        refresh();
        sprintf(music_path, "intro/%d.ogg", rand() % 5 + 1);
        sound_open_file(music, music_path);
        play_sound(music);
    }

    delete_sound(music);

    endwin();
    return 0;
}
