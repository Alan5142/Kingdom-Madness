//
// Created by alan2 on 25/02/2020.
//

#ifndef PROGRA_SCORE_H
#define PROGRA_SCORE_H


#include <stdint.h>
#include <curses.h>

struct render_node_t;

typedef struct
{
    WINDOW *window;
    uint32_t score;
    int32_t money;
    struct render_node_t* score_node;
} score_t;

score_t *start_score(struct render_node_t *node);

void draw_score(score_t *health);

void clean_score(score_t *health);

#endif //PROGRA_SCORE_H
