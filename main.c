#include <curses.h>
#include <game/game.h>
#include <utils/colors.h>
#include "start_screen.h"
#include "play_music.h"
#include <windows.h>

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

    if (has_colors())
        start_color();

    noecho();

    refresh();
    play_music(MUSIC_INTRO, false);
    init_color_pairs();
    switch (start_screen())
    {
        case START_SCREEN_QUIT:
            break;
        case START_SCREEN_PLAY:
            start_game();
            break;
    }

    endwin();
    CloseWindow(GetConsoleWindow());
    SendMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
}
