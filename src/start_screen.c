#include "start_screen.h"
#include <curses.h>
#include <load_game.h>
#include <stdbool.h>
#include <utils/menu.h>
#include <utils/render_graph.h>
#include <utils/sprite.h>

const int X_POSITION = 40;

void draw_start_screen(WINDOW *win)
{
    wclear(win);
    draw_sprite(win, 0, 0, "CASTLE.txt", NULL, NULL);
    wrefresh(win);
}

start_screen_result_e start_screen(void)
{
    render_graph_t *render_graph = create_new_graph();

    WINDOW *window = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);

    render_graph->entry_point->draw_callback  = (draw_callback_c)draw_start_screen;
    render_graph->entry_point->param          = window;
    render_graph->entry_point->require_redraw = true;

    // draw_sprite(stdscr, 0, 0, "CASTLE.txt", NULL, NULL);
    // wrefresh(stdscr);

    static const char *start_screen_choices[] = {"【 Ｊｕｇａｒ 】", "【Ｃａｒｇａｒ】", "【 Ｓａｌｉｒ 】"};
    menu_t *menu = create_menu(start_screen_choices, 3, stdscr, 5, 18, 15, X_POSITION, COLOR_PAIR(5));
    // draw_menu(menu);

    render_node_t *menu_node = add_child(render_graph->entry_point, (draw_callback_c)draw_menu);
    menu_node->param         = menu;

    keypad(stdscr, true);
    curs_set(0);

    start_screen_result_e result = START_SCREEN_NONE;

    load_game_menu_t *load_menu =
        create_load_game_menu(window, add_next(menu_node, (draw_callback_c)draw_load_game_menu));

    while (1)
    {
        draw_render_graph(render_graph);
        int g = wgetch(stdscr);

        if (load_menu->should_show)
        {
            load_menu->option              = g;
            load_game_menu_choice_e choice = execute_load_game_menu_action(load_menu);
            bool should_exit = false;
            switch (choice)
            {
                case LOAD_GAME_SLOT1:
                    should_exit = true;
                    result = START_SCREEN_LOAD1;
                    break;
                case LOAD_GAME_SLOT2:
                    should_exit = true;
                    result = START_SCREEN_LOAD2;
                    break;
                case LOAD_GAME_SLOT3:
                    should_exit = true;
                    result = START_SCREEN_LOAD3;
                    break;
                default:
                    break;
            }
            if (should_exit) break;
            if (choice == LOAD_GAME_EXIT)
            {
                load_menu->should_show = false;
                load_menu->menu->current_choice = 0;
                render_graph->entry_point->require_redraw = true;
            }
            else
            {
                load_menu->pause_node->require_redraw = true;
            }
            continue;
        }

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
        // draw_menu(menu);
        menu_node->require_redraw = true;
        if (result == START_SCREEN_LOAD)
        {
            load_menu->should_show                = true;
            load_menu->pause_node->require_redraw = true;
            menu_node->require_redraw = false;
        }
        else if (result != START_SCREEN_NONE)
        {
            break;
        }
        result = START_SCREEN_NONE;
    }
    delete_render_graph(render_graph);
    delete_menu(menu);
    delete_load_game_menu(load_menu);
    clear();
    refresh();
    return result;
}
