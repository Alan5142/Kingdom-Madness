#include "start_screen.h"
#include <curses.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

const int X_POSITION = 40;

start_screen_result_t start_screen(void)
{
    mvwaddwstr(stdscr, 1, 0, L"　　　　　　　　　　/￣ヽ\n"
                    "　　　　　　　　　/⌒⌒⌒ヽ／|\n"
                    "　　　　　　　⊂|　◎　　　　　∥\n"
                    "　　　　　　　　　ヽ　 ﾟ∀ﾟ丿＼|\n"
                    "　　　　　　　　　 __ 〃ヽ〈＿\n"
                    "　 　　 　γ´⌒´-－ヾｖーヽ⌒ヽ-:,,　　\n"
                    "　 　 　／⌒　 ｨ 　　 ／＼　　）; ｀ヽ-:,,　\n"
                    "　　 　/　　 　ﾉ＾ ､　 | 萬 |　 _人　　|　\"-:,,\n"
                    "　　　 !　　,,,ノ（　　　 ＼／　ﾉｒ;＾ >　 ）　　＼,\n"
                    "　　　 .|　　 <_ ＼ﾍ､,, __,　､__ｒﾉ/＼ /:　　　　ヽ,,\n"
                    "　 　 　|ヽ_／＼ ）ゝ､__,　､_ｱ〃 ／　　　　　　　＼\n"
                    "　 　　 | ヽ､___ ヽ.=┬─┬〈　 ｿ　　　　　　　　　　\"-.,\n"
                    "　　　　|　 　〈J　.〉､| 亀 |,　|ヽ-´　　　　　　　　　　　ゝ\n"
                    "　　　　.|　　　/\"\"　| 甲 |:　| 　　　　　　　　　　　　　　ﾐ\n"
                    "　　　　 |　　　ﾚ　　:| 男 .|　ﾘ　　　　　　　　　　　　　　　\"-:,,\n"
                    "　　　　 |　　 /　　ﾉ|＿＿|　|　　　　　　　　　　　　　　　　　　\"-:,,\n"
                    "　　　　 .|　　|　,,　ｿ　 ヽ　　） 　　　　　　　　　　　　　　　,,,-ｰ\"\n"
                    "　　　　　|　.,ゝ 　 ）　　ｲ ヽ ﾉ　　　　　　　　　　　　　,,,-ｰ\"\n"
                    "　　　　　.|　ｙ　｀ﾚｌ　　 〈´　 ﾘ 　　　　　　　　　,,,-ｰ\"\n"
                    "　　　　　 | /　　 ﾉ　　　|　　 |　　　　／ \"\"\"\"\n"
                    "　　　　　　ｌ￣￣/　　　ｌ￣￣|　　,,,-\n"
                    "　　　　　　 〉　〈 `ｰ-ｰ-| 　　|-ｰ\"　\n"
                    "　　　　　 /　　::|　　　　（_　　 ＼\n"
                    "　　　　　(＿＿ﾉ　　　　　 ＼＿__）");

    mvwaddwstr(stdscr, 36, 0, L"A──────▄▀▄─────▄▀▄\n"
                     "─────▄█░░▀▀▀▀▀░░█▄\n"
                     "─▄▄──█░░░░░░░░░░░█──▄▄\n"
                     "█▄▄█─█░░▀░░┬░░▀░░█─█▄▄█");

    wrefresh(stdscr);

    WINDOW *menu = newwin(10, 31, 15, X_POSITION);

    box(menu, '*', '*');
    wrefresh(menu);

    keypad(menu, true);
    curs_set(0);

    int choice = 0;

    const char *choices[] = {"Jugar", "Salir"};
    start_screen_result_t result;

    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == choice)
            {
                wattron(menu, A_STANDOUT);
            }
            else
            {
                wattroff(menu, A_STANDOUT);
            }
            mvwprintw(menu, i + 1, 2, choices[i]);
        }
        wrefresh(menu);
        int g = wgetch(menu);
        switch (g)
        {
            case KEY_UP:
                choice--;
                if (choice == -1)
                    choice = 1;
                break;
            case KEY_DOWN:
                choice++;
                if (choice == 2)
                    choice = 0;
                break;
            default:
                break;
        }
        if (g == 10)
        {
            if (choice == 1)
            {
                result = START_SCREEN_QUIT;
            }
            else
            {
                result = START_SCREEN_PLAY;
            }
            break;
        }
    }
    delwin(menu);
    clear();
    refresh();
    return result;
}