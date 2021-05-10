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
