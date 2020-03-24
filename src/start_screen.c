#include "start_screen.h"
#include <curses.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <utils/menu.h>

const int X_POSITION = 40;

start_screen_result_e start_screen(void)
{
    mvwaddstr(stdscr, 1, 0, "　　　　　　　　　　/￣ヽ\n"
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

    mvwaddstr(stdscr, 36, 0, " ──────▄▀▄─────▄▀▄\n"
                             "─────▄█░░▀▀▀▀▀░░█▄\n"
                             "─▄▄──█░░░░░░░░░░░█──▄▄\n"
                             "█▄▄█─█░░▀░░┬░░▀░░█─█▄▄█");

    wrefresh(stdscr);

    static const char *choices[] = {"【Ｊｕｇａｒ】", "【Ｓａｌｉｒ】"};
    menu_t *menu = create_menu(choices, 2, stdscr, 10, 17, 15, X_POSITION, COLOR_PAIR(5));
    draw_menu(menu);

    keypad(stdscr, true);
    curs_set(0);

    start_screen_result_e result = START_SCREEN_NONE;

    while (1)
    {
        int g = wgetch(stdscr);
        switch (g)
        {
            case KEY_UP:
                execute_action(menu, MENU_MOVE_UP);
                break;
            case KEY_DOWN:
                execute_action(menu, MENU_MOVE_DOWN);
                break;
            case 10:
                result = execute_action(menu, MENU_ENTER);
                break;
            default:
                break;
        }
        draw_menu(menu);
        if (result != START_SCREEN_NONE)
        {
            break;
        }
    }
    delete_menu(menu);
    menu = NULL;
    clear();
    refresh();
    return result;
}
