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


	while (!dlist_is_end(n1->edges,pos) && !dlist_is_end(n2->edges,pos2)
	{
		if (pos1 != pos2)
		{
			return false;
		}

		if !strcomp(n1->name, n2->name);
		{
			return false;
		}

		dlist_pos pos = dlist_next(n1->edges);
		dlist_pos pos2 = dlist_next(n2->edges);
	}
  return true;
}

graph *graph_empty()
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
    struct node n = dlist_inspect(g->nodes, pos);
    if (!dlist_is_empty(n)) {
      return true;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return false;
}

graph *graph_insert_node(graph *g, const char *s)
{
	dlist_insert(g->nodes, s, dlist_first(g->nodes));

	return g;
}

node *graph_find_node(const graph *g, const char *s)
{
  dlist_pos pos = dlist_first(g->nodes)

  while (!dlist_is_end(g->nodes, pos)) {
    struct node n = dlist_inspect(g->nodes, pos);
    if (strcmp(n->name, s)) {
      return n;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return NULL;
}

bool graph_node_is_seen(const graph *g, const node *n)
{
	dlist_pos pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos))
	{
		struct node m = dlist_inspect(g->nodes,pos);
		if(strcomp(m->name,n->name))
		{
			if (!n->seen)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	//If node not found return false
	return false
}

graph *graph_node_set_seen(graph *g, node *n, bool seen)
{
  n->seen = true;
  dlist_pos pos = dlist_first(g->nodes);

  while (!dlist_is_end(g->nodes, pos)) {
    struct node m = dlist_inspect(g->nodes, pos);
    if (strcmp(m->name, n->name)) {
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
	dlist_pos pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos))
	{
		struct node n = dlist_inspect(g->nodes,pos);

		if (n->seen)
		{
			n->seen=false
			dlist_remove(g->nodes, pos);
			dlist_insert(g->nodes, n, pos);
		}
	//go to next node
	pos = dlist_next(g->nodes, pos);
	}
	return g
}

graph *graph_insert_edge(graph *g, node *n1, node *n2)
{
  dlist_insert(n1->edges, n2->name, dlist_first(n1->edge));

  dlist_pos pos = dlist_first(g->nodes);
  while (!dlist_is_end(g->nodes, pos)) {
    struct node m = dlist_inspect(g->nodes, pos);
    if (strcmp(m->name, n1->name)) {
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
    struct node m = dlist_inspect(g->nodes, pos1);
    if (strcmp(m->name, n1->name)) {
      dlist_pos pos2 = dlist_first(n1->edges);
      while (!dlist_is_end(n1->edges, pos2) {
        char e = dlist_inspect(n1->edge, pos2);
        if (strcmp(e, n2->name)) {
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
    struct node m = dlist_inspect(g->nodes, pos);
    if (strcmp(m->name, n->name)) {
      return m->edges;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return NULL;
}

void graph_kill(graph *g)
{

}
