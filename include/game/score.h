//
// Created by alan2 on 25/02/2020.
//

#ifndef PROGRA_SCORE_H
#define PROGRA_SCORE_H


#include <stdint.h>
#include <curses.h>

typedef struct
{
    WINDOW *window;
    uint32_t score;
} score_t;

score_t *start_score(void);

void draw_score(score_t *health);

void clean_score(score_t *health);

#endif //PROGRA_SCORE_H
