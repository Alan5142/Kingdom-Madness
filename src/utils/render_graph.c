//
// Created by alan2 on 24/03/2020.
//
#include "utils/render_graph.h"
#include <stdlib.h>

render_node_t *create_node(draw_callback_c callback)
{
    render_node_t *node = malloc(sizeof(render_node_t));
    node->draw_callback = callback;
    node->child = NULL;
    node->next = NULL;
    node->previous = NULL;
    node->parent = NULL;
    node->param = NULL;
    node->node_id = -1;
    node->require_redraw = true;
    return node;
}

render_graph_t *create_new_graph(void)
{
    render_graph_t *graph = malloc(sizeof(render_graph_t));
    graph->entry_point = create_node(NULL);
    graph->entry_point->node_id = 0;
    return graph;
}

static void draw_render_graph_internal(render_node_t *node)
{
    if (node->draw_callback != NULL && node->require_redraw)
    {
        node->draw_callback(node->param);
        node->require_redraw = false;
    }
    if (node->child)
    {
        draw_render_graph_internal(node->child);
    }
    if (node->next)
    {
        draw_render_graph_internal(node->next);
    }
}

void draw_render_graph(render_graph_t *render_graph)
{
    draw_render_graph_internal(render_graph->entry_point);
}

static void delete_render_graph_internal(render_node_t *node)
{
    if (node->next)
    {
        delete_render_graph_internal(node->next);
    }
    if (node->child)
    {
        delete_render_graph_internal(node->child);
    }
    free(node);
}

void delete_render_graph(render_graph_t *render_graph)
{
    delete_render_graph_internal(render_graph->entry_point);
    free(render_graph);
}

render_node_t *add_child(render_node_t *parent, draw_callback_c callback)
{
    render_node_t *child = create_node(callback);
    child->node_id = rand() + 1;

    render_node_t *bro = parent->child;
    if (bro != NULL)
    {
        bro = parent->child;
        while (bro->next) bro = bro->next;
        bro->next = child;
    }
    else
    {
        parent->child = child;
    }
    child->parent = parent;

    return child;
}

render_node_t *add_next(render_node_t *previous, draw_callback_c callback)
{
    render_node_t *next = create_node(callback);
    next->node_id = rand() + 1;
    previous->next = next;
    next->previous = previous;
    return next;
}

render_node_t *add_node_at_end(render_graph_t *render_graph, draw_callback_c callback)
{
    render_node_t *node = render_graph->entry_point->child;
    if (!node)
    {
        return add_child(render_graph->entry_point, callback);
    }
    while (node->next) node = node->next;
    return add_next(node, callback);
}

void delete_node(render_node_t *node)
{
    if (node->parent) // si tiene un padre, entonces debemos decirle al padre que ya no tiene hijos
    {
        node->parent->child = NULL;
        return;
    }

    if (node->child) // si tiene un hijo, entonces eliminamos a los hijos
    {
        delete_node(node->child);
    }

    if (node->previous)
    {
        node->previous->next = node->next; // solo vamos a eliminar este,
    }
    free(node);
}

void delete_last(render_graph_t *render_graph)
{
    render_node_t *node = render_graph->entry_point->child;
    if (!node->child)
    {
        return; // No hay hijos por lo tanto no hay nada que eliminar
    }
    if (!node->next) // no tiene nodos siguientes,
    {
        delete_node(node);
    }
    while (node->next->next) node = node->next;
    delete_node(node->next);
}
