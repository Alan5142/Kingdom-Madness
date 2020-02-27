//
// Created by alan2 on 25/02/2020.
//

#include "game/score.h"
#include "utils/colors.h"
#include <stdlib.h>

score_t *start_score(void)
{
    score_t *score = malloc(sizeof(score_t));
    score->score = 0;
    score->money = 0;

    score->window = newwin(3, 21, 0, getmaxx(stdscr) - 21);

    draw_score(score);

    return score;
}

void draw_score(score_t *score)
{
    // box(score->window, 0, 0);

    wattron(score->window, COLOR_PAIR(SCORE_COLOR_PAIR));
    mvwprintw(score->window, 0, 0, "$%04d Puntaje: %08d", score->money, score->score);
    wattroff(score->window, COLOR_PAIR(SCORE_COLOR_PAIR));

    wrefresh(score->window);
}

void clean_score(score_t *health)
{
    delwin(health->window);
    free(health);
}
