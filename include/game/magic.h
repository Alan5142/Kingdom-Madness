//
// Created by alan2 on 25/02/2020.
//

#ifndef PROGRA_MAGIC_H
#define PROGRA_MAGIC_H


#include <stdbool.h>
#include <curses.h>
#include <stdint.h>

struct render_node_t;

typedef struct magic_t
{
    WINDOW *window;
    int8_t magic;
    struct render_node_t* magic_node;
} magic_t;

magic_t *create_magic(struct render_node_t *);

void draw_magic(magic_t *health);

void delete_magic(magic_t *health);


#endif //PROGRA_MAGIC_H
