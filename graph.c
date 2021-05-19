#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "dlist.h"
#include "util.h"

/*
 * Implementation of a generic graph for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University.
 *
 * Authors: Adam Nilsson (ens17ann@cs.umu.se)
 *	    Adam Dahlgren Lindstrom (din tfy18msn@cs.umu.se)
 *
 * Version information:
 *   2021-05-14: v1.0, first public version.
 */

// ===========INTERNAL DATA TYPES============

struct graph {
	dlist *nodes;
	int nmrOfNodes;
};

struct node {
  dlist *edges;
  char *name;
  bool seen;
};

// ===========INTERNAL FUNCTION IMPLEMENTATIONS============

/**
 * nodes_are_equal() - Check whether two nodes are equal.
 * @n1: Pointer to node 1.
 * @n2: Pointer to node 2.
 *
 * Returns: true if the nodes are considered equal, otherwise false.
 *
 */
bool nodes_are_equal(const node *n1,const node *n2)
{
  return n1->name == n2->name;
}

// =================== GRAPH STRUCTURE INTERFACE ======================

/**
 * graph_empty() - Create an empty graph.
 * @max_nodes: The maximum number of nodes the graph can hold.
 *
 * Returns: A pointer to the new graph.
 */
graph *graph_empty(int max_nodes)
{
  // Allocate the graph header.
  struct graph *g = calloc(1, sizeof(graph));
  // Create the lists to hold the nodes and edges.
  g->nodes = dlist_empty(NULL);
	g->nmrOfNodes = 0;

  return g;
}

/**
 * graph_is_empty() - Check if a graph is empty, i.e. has no nodes.
 * @g: Graph to check.
 *
 * Returns: True if graph is empty, otherwise false.
 */
bool graph_is_empty(const graph *g)
{
	return g->nmrOfNodes == 0;
}

/**
 * graph_insert_node() - Inserts a node with the given name into the graph.
 * @g: Graph to manipulate.
 * @s: Node name.
 *
 * Creates a new node with a copy of the given name and puts it into
 * the graph.
 *
 * Returns: The modified graph.
 */
 graph *graph_insert_node(graph *g, const char *s)
 {
 	struct node *n = malloc(sizeof(struct node));
 	n->edges = dlist_empty(NULL);
 	n->name = (char*) s;
 	n->seen = false;
 	dlist_insert(g->nodes, n, dlist_first(g->nodes));
 	g->nmrOfNodes++;

 	return g;
 }

/**
 * graph_find_node() - Find a node stored in the graph.
 * @g: Graph to manipulate.
 * @s: Node identifier, e.g. a char *.
 *
 * Returns: A pointer to the found node, or NULL.
 */
node *graph_find_node(const graph *g, const char *s)
{
  dlist_pos pos = dlist_first(g->nodes);
  while (!dlist_is_end(g->nodes, pos)) {
    struct node *n = dlist_inspect(g->nodes, pos);
    if (!strcmp(n->name, s)) {
      return n;
    }
    pos = dlist_next(g->nodes, pos);
  }
  return NULL;
}

/**
 * graph_node_is_seen() - Return the seen status for a node.
 * @g: Graph storing the node.
 * @n: Node in the graph to return seen status for.
 *
 * Returns: The seen status for the node.
 */
bool graph_node_is_seen(const graph *g, const node *n)
{
	return n->seen;
}

/**
 * graph_node_set_seen() - Set the seen status for a node.
 * @g: Graph storing the node.
 * @n: Node in the graph to set seen status for.
 * @s: Status to set.
 *
 * Returns: The modified graph.
 */
graph *graph_node_set_seen(graph *g, node *n, bool seen)
{
  n->seen = seen;
  return g;
}

/**
 * graph_reset_seen() - Reset the seen status on all nodes in the graph.
 * @g: Graph to modify.
 *
 * Returns: The modified graph.
 */
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

/**
 * graph_insert_edge() - Insert an edge into the graph.
 * @g: Graph to manipulate.
 * @n1: Source node (pointer) for the edge.
 * @n2: Destination node (pointer) for the edge.
 *
 * NOTE: Undefined unless both nodes are already in the graph.
 *
 * Returns: The modified graph.
 */
graph *graph_insert_edge(graph *g, node *n1, node *n2)
{
  dlist_insert(n1->edges, n2->name, dlist_first(n1->edges));
  return g;
}

/**
 * graph_neighbours() - Return a list of neighbour nodes.
 * @g: Graph to inspect.
 * @n: Node to get neighbours for.
 *
 * Returns: A pointer to a list of nodes. Note: The list must be
 * dlist_kill()-ed after use.
 */
 dlist *graph_neighbours(const graph *g,const node *n)
 {
 	// struct dlist *neighbours = dlist_empty(NULL);
 	// neighbours= n->edges;

 	// dlist_pos pos = dlist_first(n->edges);
 	// dlist_pos pos2 = dlist_first(neighbours);
	//
 	// while (!dlist_is_end(n->edges, pos)){
	//
 	// 	char sub[41];
 	// 	strcpy(sub, dlist_inspect(n->edges,pos));
 	// 	dlist_insert(neighbours, sub, pos);
	//
 	// 	pos = dlist_next(n->edges, pos);
 	// 	pos2 = dlist_next(neighbours, pos2);
 	// }
 	return n -> edges;
 }

/**
 * graph_kill() - Destroy a given graph.
 * @g: Graph to destroy.
 *
 * Return all dynamic memory used by the graph.
 *
 * Returns: Nothing.
 */

void graph_kill(graph *g)
{
	// Iterate over the list. Destroy all elements.
	dlist_pos pos1 = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos1)) {
		struct node *n = dlist_inspect(g->nodes, pos1);

		dlist_pos pos2 = dlist_first(n->edges);

		while (!dlist_is_end(n->edges, pos2)) {
		//	char *edge = dlist_inspect(n->edges, pos2);
			dlist_pos pos_temp = pos2;
			pos2 = dlist_next(n->edges, pos2);
			dlist_remove(n->edges,pos_temp);
		}

		// Move on to next element.
		pos1 = dlist_next(g->nodes, pos1);
    // Deallocate the table entry structure.
    free(n);
	}

	// Kill what's left of the list...
	dlist_kill(g->nodes);
	// ...and the table.
	free(g);
}
