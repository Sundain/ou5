<<<<<<< HEAD
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>
#include <graph.h>

#define MAXCHAR 1000

int main(void) {
  return 0;
}

graph BreadthFirst(graph g, node n)
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
}
=======
>>>>>>> af3d847e333ba6463ce44387cda2118e52fff5e6
