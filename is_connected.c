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
   {
     if (nodes_are_equal(dest,src))
     {
       return true;
     }
   }

   graph_node_set_seen(g, src, seen); // Mark the "src" node as seen.
   queue_enqueue(q,src); // Put "src" node in queue.
   //Check if the nodes are the same, returns that the nodes are connected if true.

   while (!queue_is_empty(q))
   {

     struct node *p = queue_front(q); // Pick first node from queue
     queue_dequeue(q); //Remove the first element from the queue
     struct dlist *neighbours=graph_neighbours(g,p);//saving the neighbours in a directed list.
     dlist_pos pos = dlist_first(neighbours); //checking the position of first element.
     //Go through neighbours and add to queue if the node is not set to seen.

     while(!dlist_is_end(neighbours,pos))
     {
       char* name = dlist_inspect(neighbours, pos);
       struct node *m = graph_find_node(g, name);
       //Check if the node "m" is set as seen.
       if (!graph_node_is_seen(g, m))
       {
         //Check if the node "m" is the same as "dest",
         //returns that the nodes are connected if true.
         if (nodes_are_equal(m,dest))
         {
           while (!queue_is_empty(q))
           {
             queue_dequeue(q);
           }
           queue_kill(q);
           return true;
         }
         //If nodes  are not equal continue with the traversing by setting the node as seen.
         //The node is also added into the queue.
         else
         {
           g = graph_node_set_seen(g, m, seen); //Set the node "m" as seen.
           q = queue_enqueue(q,m); //Add the node "m" to the queue.
         }
       }
       //dlist_pos pos_temp=pos;
       pos = dlist_next(neighbours,pos); //Save the position of the next element.
       //dlist_remove(neighbours,pos_temp);
     }
     //dlist_kill(neighbours);
   }
   queue_kill(q);

   return false; //if "dest" not found return false
 }

int main(int argc, char** argv) {

  FILE *fp;
  char str[MAXCHAR];
  char* filename = argv[argc-1];

  fp = fopen(filename, "r");

  int i = 0;
  int number_of_edges = -1;

  while (fgets(str, MAXCHAR, fp) != NULL) {
    if (str[0] != '#' && str[0] != ' ') {
      number_of_edges = atoi(str);
      break;
    }
  }
  char origins[number_of_edges][41];
  char destinations[number_of_edges][41];

  while (fgets(str, MAXCHAR, fp) != NULL) {
    if (str[0] != '#' && str[0] != ' ') {
      char sub[41];
      int j = 0;
      while(str[j] != ' ') {
        sub[j] = str[j];
        j++;
      }
      strcpy(origins[i], sub);
      memset(sub, 0, strlen(sub));

      j++;
      int k = 0;
      while(str[j] != ' ' && str[j] != '#' && str[j] != '\n') {
        sub[k] = str[j];
        j++;
        k++;
      }
      strcpy(destinations[i], sub);
      memset(sub, 0, strlen(sub));
      i++;
    }
  }

  fclose(fp);

  graph *g = graph_empty(10);

  for (size_t i = 0; i < number_of_edges; i++) {
    if (graph_find_node(g, origins[i]) == NULL) {
      graph_insert_node(g, origins[i]);
    }
  }

  for (size_t i = 0; i < number_of_edges; i++) {
    if (graph_find_node(g, destinations[i]) == NULL) {
      graph_insert_node(g, destinations[i]);
    }
  }

  for (size_t i = 0; i < number_of_edges; i++) {
    struct node *n1 = graph_find_node(g, origins[i]);
    struct node *n2 = graph_find_node(g, destinations[i]);
    graph_insert_edge(g, n1, n2);
  }

  bool loop=true;
  while (loop)
  {

    char src_name[41];
    char dest_name[41];
    char array[2][41];

    printf("Enter origin and destination (quit to exit): ");
    int i=0;
    while (i < 2) {
      scanf("%s", array[i]);
      if (!strcmp(array[0], "quit")) {
        loop=false;
        break;
      }
      i++;
    }
    if (loop)
    {
      strcpy(src_name, array[0]);
      strcpy(dest_name, array[1]);
      memset(array[0], 0, strlen(array[0]));
      memset(array[1], 0, strlen(array[1]));

      struct node *src = graph_find_node(g, src_name);
      struct node *dest = graph_find_node(g, dest_name);

      bool connected = find_path(g, src, dest);
      if (connected)
      {
        printf("There is a path from %s to %s. \n", src_name, dest_name);
        //printf("There is a path from %s to %s.\n",
        //*graph_node_name(g, src), *graph_node_name(g, dest));
      }
      else
      {
        printf("There is no path from %s to %s. \n", src_name, dest_name);
      }


      //reset seen status between runs:
      g = graph_reset_seen(g);
    }
  }
  graph_kill(g);
  printf("Normal exit.\n");
  return 0;
}
