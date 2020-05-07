#include <game/magic.h>
#include <utils/render_graph.h>
#include <stdlib.h>
#include <utils/colors.h>

magic_t *create_magic(render_node_t * render_node)
{
    magic_t *magic = malloc(sizeof(magic_t));
    magic->window = newwin(1, 6, 0, getmaxx(stdscr) / 2 - 3);
    magic->magic_node = render_node;
    magic->magic = 75;
    render_node->draw_callback = (draw_callback_c) draw_magic;
    render_node->param = magic;

    return magic;
}

void draw_magic(magic_t *magic)
{
    wclear(magic->window);
    wattron(magic->window, COLOR_PAIR(SCORE_COLOR_PAIR));
    mvwprintw(magic->window, 0, 0, "% 3dMP", magic->magic);
    wattroff(magic->window, COLOR_PAIR(SCORE_COLOR_PAIR));

    wrefresh(magic->window);
}

void delete_magic(magic_t *magic)
{
    delwin(magic->window);
    free(magic);
}
