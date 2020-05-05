#include <game/save_game.h>
#include <stdlib.h>
#include <utils/render_graph.h>

save_game_menu_t *create_save_menu(WINDOW *parent, render_node_t *node)
{
    save_game_menu_t *menu       = malloc(sizeof(save_game_menu_t));
    menu->window = parent;
    static const char *choices[] = {"【 SLOT 1 】", "【 SLOT 2 】", "【 SLOT 3 】"};
    node->draw_callback          = (draw_callback_c)draw_save_menu;
    node->param                  = menu;
    menu->should_show            = false;
    menu->menu =
        create_menu(choices, 3, parent, 5, 14, getmaxy(stdscr) / 2 - 2, getmaxx(stdscr) / 2 - 8, COLOR_PAIR(5));
    menu->render_node    = node;
    node->require_redraw = true;
    return menu;
}

save_choice_e execute_save_menu_action(save_game_menu_t *menu)
{
    save_choice_e return_choice = SLOT_NONE;

    switch (menu->option)
    {
        case KEY_UP:
            execute_action(menu->menu, MENU_MOVE_UP);
            break;
        case KEY_DOWN:
            execute_action(menu->menu, MENU_MOVE_DOWN);
            break;
        case 10:
            return_choice = execute_action(menu->menu, MENU_ENTER);
            break;
        default:
            execute_action(menu->menu, MENU_REDRAW);
            break;
    }
    return return_choice;
}

void draw_save_menu(save_game_menu_t *menu)
{
    if (!menu->should_show)
        return;
    set_menu_attribute(menu->menu, COLOR_PAIR(5));

    draw_menu(menu->menu);
}

void delete_save_menu(save_game_menu_t *menu)
{
    delete_menu(menu->menu);
    free(menu);
}
