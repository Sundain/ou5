#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "dlist.h"
#include "util.h"

struct graph {
	dlist *nodes;
  dlist *edges;
}

bool nodes_are_equal(const node *n1,const node *n2)
{

}

graph *graph_empty()
{
  // Allocate the graph header.
  graph *g = calloc(1, sizeof(graph));
  // Create the lists to hold the nodes and edges.
  g->nodes = dlist_empty(NULL);
  g->edges = dlist_empty(NULL);

  return g;
}

bool graph_is_empty(const graph *g)
{

}

bool graph_has_edges(const graph *g)
{

}

graph *graph_insert_node(graph *g, const char *s)
{

}

node *graph_find_node(const graph *g, const char *s)
{

}

bool graph_node_is_seen(const graph *g, const node *n)
{

}

graph *graph_node_set_seen(graph *g, node *n, bool seen)
{

}

graph *graph_reset_seen(graph *g)
{

}

graph *graph_insert_edge(graph *g, node *n1, node *n2)
{

}

graph *graph_delete_node(graph *g, node *n)
{

}

graph *graph_delete_edge(graph *g, node *n1, node *n2)
{

}

node *graph_choose_node(const graph *g)
{

}

dlist *graph_neighbours(const graph *g,const node *n)
{

}

void graph_kill(graph *g)
{

}

void graph_print(const graph *g)
{

}
