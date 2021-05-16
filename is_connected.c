#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "queue.h"
#include "graph.h"
#include "dlist.h"

#define MAXCHAR 1000

/*
 * Implementation of a breadth-first algorithm to determine if a path is connected.
 * The program first scans a map file to create a graph.
 * The graph is then traversed with a breadth-first algorihm.
 *
 * Authors: Adam Nilsson (ens17ann@cs.umu.se)
 *	    Marcus Sundin (tfy18msn@cs.umu.se)
 *
 * Version information:
 *   2021-05-16: v1.0, first public version.
 */


bool find_path(graph *g, node *src, node *dest)
{
  //Creating an empty queue
  queue *q = queue_empty(NULL);
  bool seen = true;

  graph_node_set_seen(g, src, seen); // Mark the "src" node as seen.
  queue_enqueue(q,src); // Put "src" node in queue.

  //Check if the nodes are the same, returns that the nodes are connected if true.
  if (nodes_are_equal(dest,src))
  {
    return true;
  }


  while (!queue_is_empty(q) )
  {
    printf("1\n");
    struct node *p = queue_front(q); // Pick first node from queue
    queue_dequeue(q); //Remove the first element from the queue
    struct dlist *neighbours=graph_neighbours(g,p);//saving the neighbours in a directed list.

    dlist_pos pos = dlist_first(neighbours); //checking the position of first element.
    //Go through neighbours and add to queue if the node is not set to seen.
    while(!dlist_is_end(neighbours,pos))
    {
      printf("1\n");
      struct node *m = dlist_inspect(neighbours, pos);

      //Check if the node "m" is set as seen.
      if (!graph_node_is_seen(g, m))
      {
        //Check if the node "m" is the same as "dest",
        //returns that the nodes are connected if true.
        if (nodes_are_equal(m,dest))
        {
          return true;
        }
        //If nodes  are not equal continue with the traversing by setting the node as seen.
        //The node is also added into the queue.
        else
        {
          g=graph_node_set_seen(g, m, seen); //Set the node "m" as seen.
          q = queue_enqueue(q,m); //Add the node "m" to the queue.
        }
      }
      pos = dlist_next(neighbours,pos); //Save the position of the next element.
      //free(m);
    }
    free(neighbours);
  }
  return false; //if "dest" not found return false
}

int main(void) {
  //Creating empty graph.
  graph *g = graph_empty(1000);

  graph_insert_node(g, "A");
  graph_insert_node(g, "B");
  graph_insert_node(g, "C");
  graph_insert_node(g, "D");
  graph_insert_node(g, "E");
  graph_insert_node(g, "F");

  struct node *A = graph_find_node(g,"A");
  struct node *B = graph_find_node(g,"B");
  struct node *C = graph_find_node(g,"C");
  struct node *D = graph_find_node(g,"D");
  struct node *E = graph_find_node(g,"E");
  struct node *F = graph_find_node(g,"F");

  graph_insert_edge(g, A, B);
  graph_insert_edge(g, A, C);
  graph_insert_edge(g, C, D);
  graph_insert_edge(g, B, C);
  graph_insert_edge(g, D, A);
  graph_insert_edge(g, E, F);

  struct node *src = A;
  struct node *dest = B;
  bool connected = find_path(g, src, dest);

  if (connected)
  {
    printf("There is a path \n");
    //printf("There is a path from %s to %s.\n",
    //*graph_node_name(g, src), *graph_node_name(g, dest));
  }
  else
  {
    printf("There is no path \n");
  }

    //reset seen status between runs:
    g=graph_reset_seen(g);

    printf("Normal exit.\n");
    return 0;
}
//Finns slide 38/104 bredden-först-travisering, sida 110
//Check if destination and source is seen.
//Graph reset: Use graph_reset_seen
//Hur avallokeras dynamiskt minne?
