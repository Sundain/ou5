#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "queue.h"
#include "graph.h"

#define MAXCHAR 1000

int main(void) {

  while(input == 'quit')
  {
    if (src == dest || find_path(g, src, dest) )
    {
      printf("There is a path from %s to %s.\n", src->name, dest->name);
    }
    else
    {
      printf("There is no path from %s to %s.\n", src->name, dest->name);
    }
    //reset seen status between runs:
    g=graph_reset_seen(g);

  }
  printf("Normal exit.\n");

  return 0;
}

bool find_path(graph *g, node *src, node *dest)
{
  //travsering the graph
  g=BreadthFirst(g,src);

  //return if the destination have been marked as seen
  return dest_found(g, dest);
}

graph BreadthFirst(graph *g, node *n)
{
  Queue q = queue_empty(NULL);
  g=graph_node_is_seen(g, n, true); // (n,g)←seen(n,g) , mark the node as seen.
  q = queue_enqueue(q,n); // Put node in queue.
  while (!queue_is_empty(q))
  {
    struct node p = queue_front(q); // Pick first node from queue
    q=queue_dequeue(q); //Remove the first element from the queue
    struct dlist neighbours=graph_neighbours(g,p);

    dlist_pos pos = dlist_first(neighbours)
    while(!dlist_is_empty(neighbours)
    {
      struct node m = dlist_inspect(neighbours, pos);
      if (!graph_node_is_seen(g, m))
      {
        g=graph_node_is_seen(g, m, true);
        q = queue_enqueue(q,m);
      }
    }
  return g;
}

bool dest_found(graph *g, node *n2)
{
  return graph_node_is_seen(const graph *g, const node *n2);
}
