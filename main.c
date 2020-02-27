#include <curses.h>
#include <game/game.h>
#include <utils/colors.h>
#include "start_screen.h"
#include "play_music.h"
#include <windows.h>
#include <sound.h>
#include <time.h>

int main()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfie;
    ZeroMemory(&cfie, sizeof(cfie));
    cfie.cbSize = sizeof(cfie);
    cfie.dwFontSize.Y = 20;
    lstrcpyW(cfie.FaceName, L"MS Gothic");
    SetCurrentConsoleFontEx(hStdOut, false, &cfie);

    initscr();

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
