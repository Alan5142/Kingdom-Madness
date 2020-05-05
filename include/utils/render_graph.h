//
// Created by alan2 on 24/03/2020.
//

#ifndef PROGRA_RENDER_GRAPH_H
#define PROGRA_RENDER_GRAPH_H

#include <stdint.h>
#include <stdbool.h>
#include <game/magic.h>


typedef void (*draw_callback_c)(void *);

typedef struct render_node_t
{
    int32_t node_id;
    draw_callback_c draw_callback;
    struct render_node_t *child;
    struct render_node_t *parent;
    struct render_node_t *next;
    struct render_node_t *previous;
    void *param;
    bool require_redraw;
} render_node_t;

typedef struct render_graph_t
{
    /**
     * Top, inicia a renderizar a partir de aquí
     */
    render_node_t *entry_point;
} render_graph_t;

render_node_t *create_node(draw_callback_c callback);

render_node_t *add_child(render_node_t *parent, draw_callback_c callback);

render_node_t *add_next(render_node_t *previous, draw_callback_c callback);

render_node_t *add_node_at_end(render_graph_t *render_graph, draw_callback_c callback);

void delete_last(render_graph_t *render_graph);

render_graph_t *create_new_graph(void);

void draw_render_graph(render_graph_t *render_graph);

void delete_render_graph(render_graph_t *render_graph);

void delete_node(render_node_t *node);

#endif //PROGRA_RENDER_GRAPH_H
