#include <curses.h>
#include <game/game.h>
#include <utils/colors.h>
#include "start_screen.h"
#include <windows.h>
#include <sound.h>
#include <time.h>
#include <stdbool.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // para que no genere la adevertencia de que no estan siendo utilizados
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;

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
    while (start_screen() != START_SCREEN_QUIT)
    {
        stop_sound(music);
        start_game();
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
