#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "dlist.h"
#include "util.h"

struct graph {
	dlist *nodes;
  int nmrOfNodes;
};

struct node {
  dlist *edges;
  char *name;
  bool seen;
};

bool nodes_are_equal(const node *n1,const node *n2)
{
  return n1->name == n2->name;
}

graph *graph_empty(int max_nodes)
{
  // Allocate the graph header.
  struct graph *g = calloc(1, sizeof(graph));
  // Create the lists to hold the nodes and edges.
  g->nodes = dlist_empty(NULL);
	g->nmrOfNodes = 0;

  return g;
}

bool graph_is_empty(const graph *g)
{
	return g->nmrOfNodes == 0;
}

graph *graph_insert_node(graph *g, const char *s)
{
	struct node *n = calloc(1, sizeof(node));
	n->edges = dlist_empty(NULL);
	strcpy(n->name, s);
	n->seen = false;
	g->nmrOfNodes++;
	dlist_insert(g->nodes, n, dlist_first(g->nodes));

	return g;
}

node *graph_find_node(const graph *g, const char *s)
{
  dlist_pos pos = dlist_first(g->nodes);

  while (!dlist_is_end(g->nodes, pos)) {
    struct node *n = dlist_inspect(g->nodes, pos);
    if (strcmp(n->name, s)) {
      return n;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return NULL;
}

bool graph_node_is_seen(const graph *g, const node *n)
{
	return n->seen;
}

graph *graph_node_set_seen(graph *g, node *n, bool seen)
{
  n->seen = seen;
  return g;
}

graph *graph_reset_seen(graph *g)
{
	dlist_pos pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos))
	{
		struct node *n = dlist_inspect(g->nodes,pos);
		n->seen = false;

		pos = dlist_next(g->nodes, pos);
	}
	return g;
}

graph *graph_insert_edge(graph *g, node *n1, node *n2)
{
  dlist_insert(n1->edges, n2->name, dlist_first(n1->edges));
  return g;
}

dlist *graph_neighbours(const graph *g,const node *n)
{
	return n->edges;
}

void graph_kill(graph *g)
{

}
