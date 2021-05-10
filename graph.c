#include <stdlib.h>
#include <stdio.h>

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
  bool *seen;
};

bool nodes_are_equal(const node *n1,const node *n2)
{
	dlist_pos pos = dlist_first(n1->edges);
	dlist_pos pos2 = dlist_first(n2->edges);
	bool equal = true;

	while (!dlist_is_end(n1->edges,pos), equal) && !dlist_is_end(n2->edges,pos2), equal)
	{
		if (pos1 != pos2)
		{
			equal = false;
		}

		if (dlist_inspect(n1->edges,pos) != dlist_inspect(n2->edges,pos2));
		{
			equal = false;
		}

		dlist_pos pos = dlist_next(n1->edges);
		dlist_pos pos2 = dlist_next(n2->edges);
	}
  return equal;
}

graph *graph_empty()
{
  // Allocate the graph header.
  graph *g = calloc(1, sizeof(graph));
  // Create the lists to hold the nodes and edges.
  g->nodes = dlist_empty(NULL);

  return g;
}

bool graph_is_empty(const graph *g)
{
  if (graph->nmrOfNodes != 0){
      return false;
  }
  else
  {
    return true;
  }
}

bool graph_has_edges(const graph *g)
{
  dlist_pos pos = dlist_first(g->nodes)

  while (!dlist_is_end(g->nodes, pos)) {
    node n = dlist_inspect(g->nodes, pos);
    if (!dlist_is_empty(n)) {
      return true;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return false;
}

graph *graph_insert_node(graph *g, const char *s)
{

}

node *graph_find_node(const graph *g, const char *s)
{
  dlist_pos pos = dlist_first(g->nodes)

  while (!dlist_is_end(g->nodes, pos)) {
    node n = dlist_inspect(g->nodes, pos);
    if (n->name == s) {
      return n;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return NULL;
}

bool graph_node_is_seen(const graph *g, const node *n)
{

}

graph *graph_node_set_seen(graph *g, node *n, bool seen)
{
  n->seen = true;
  dlist_pos pos = dlist_first(g->nodes);
  while (!dlist_is_end(g->nodes, pos)) {
    node m = dlist_inspect(g->nodes, pos);
    if (m->name == n->name) {
      dlist_remove(g->nodes, pos);
      dlist_insert(g->nodes, n, pos);
      return g;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return g;
}

graph *graph_reset_seen(graph *g)
{

}

graph *graph_insert_edge(graph *g, node *n1, node *n2)
{
  char *e = calloc(1, sizeof(e));
  e = n2->name;
  dlist_insert(n1->edges, e, dlist_first(n1->edge));

  dlist_pos pos = dlist_first(g->nodes);
  while (!dlist_is_end(g->nodes, pos)) {
    node m = dlist_inspect(g->nodes, pos);
    if (m->name == n1->name) {
      dlist_remove(g->nodes, pos);
      dlist_insert(g->nodes, n1, pos);
      return g;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return g;
}

graph *graph_delete_node(graph *g, node *n)
{

}

graph *graph_delete_edge(graph *g, node *n1, node *n2)
{
  dlist_pos pos1 = dlist_first(g->nodes);
  while (!dlist_is_end(g->nodes, pos1)) {
    node m = dlist_inspect(g->nodes, pos1);
    if (m->name == n1->name) {
      dlist_pos pos2 = dlist_first(n1->edges);
      while (!dlist_is_end(n1->edges, pos2) {
        edge e = dlist_inspect(n1->edge, pos2);
        if (e->destination_node == n2->name) {
          dlist_remove(n1->edge, pos2);
          return g;
        }
      }
      pos2 = dlist_next(n1->edge, pos2);
    }
    pos1 = dlist_next(g->nodes, pos1);
  }
  return g;
}

node *graph_choose_node(const graph *g)
{

}

dlist *graph_neighbours(const graph *g,const node *n)
{
  dlist_pos pos = dlist_first(g->nodes);
  while (!dlist_is_end(g->nodes, pos)) {
    node m = dlist_inspect(g->nodes, pos);
    if (m->name == n->name) {
      return m->edges;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return NULL;
}

void graph_kill(graph *g)
{

}
