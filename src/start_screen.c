#include "start_screen.h"
#include <curses.h>
#include <stdbool.h>
#include <utils/menu.h>
#include <utils/sprite.h>

const int X_POSITION = 40;

start_screen_result_e start_screen(void)
{
    draw_sprite(stdscr, 0, 0, "CASTLE.txt", NULL, NULL);
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
    clear();
    refresh();
    return result;
}
