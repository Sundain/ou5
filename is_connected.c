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
 *	        Marcus Sundin (tfy18msn@cs.umu.se)
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
       pos = dlist_next(neighbours,pos); //Save the position of the next element.
     }
   }
   queue_kill(q);

   return false; //if "dest" not found return false
 }

int main(int argc, char** argv) {

  FILE *fp;
  char str[MAXCHAR];
  char* filename = argv[argc-1];

  fp = fopen(filename, "r");  //Open mapfile

  int i = 0;
  int number_of_edges = -1;
  bool error = false;         //Checks if everything works correctly

  //error message
  if (error) {
    printf("Invalid map\n");
    exit(EXIT_FAILURE);
  }


  //loops until it sees a number
  while (fgets(str, MAXCHAR, fp) != NULL) {
    //ignors if the row starts with a # or blanck space
    if (str[0] != '#' && str[0] != ' ') {
      number_of_edges = atoi(str);
      break;
    }
  }
  //checks if number_of_edges have been given a value
  if (number_of_edges < 1)
  {
    error = true;
  }

  //string vector containing nodes connected by edges
  char origins[number_of_edges][41];
  char destinations[number_of_edges][41];

  //loops over the rest of the file
  while (fgets(str, MAXCHAR, fp) != NULL && !error) {
    //ignors rows starting with # or blanck space
    if (str[0] != '#' && str[0] != ' ')
    {
      char sub[41]; //name holder variable
      int j = 0;
      //reads the name until it hits a blanck space
      while(str[j] != ' ' && !error)
      {
        sub[j] = str[j];
        if (str[j] == '\n') //error if it hits a new row already
          error = true;
        j++;
      }
      if (error){
        break;
      }

      strcpy(origins[i], sub);    //puts in origin name
      memset(sub, 0, strlen(sub));

      j++;
      int k = 0;
      //reads the name until it ends
      while(str[j] != ' ' && str[j] != '#' && str[j] != '\n') {
        sub[k] = str[j];
        j++;
        k++;
      }
      strcpy(destinations[i], sub); //puts in the new destination name
      memset(sub, 0, strlen(sub));
      i++;
    }
  }
  //checks that the indicated number of edges is correct
  if (i != number_of_edges)
    error = true;

  //error message
  if (error) {
    printf("Invalid map\n");
    exit(EXIT_FAILURE);
  }

  fclose(fp);

  graph *g = graph_empty(10); //empty graph

  //inserts the origin nodes
  for (size_t i = 0; i < number_of_edges; i++) {
    if (graph_find_node(g, origins[i]) == NULL) {
      graph_insert_node(g, origins[i]);
    }
  }
  //inserts the destination nodes
  for (size_t i = 0; i < number_of_edges; i++) {
    if (graph_find_node(g, destinations[i]) == NULL) {
      graph_insert_node(g, destinations[i]);
    }
  }
  //inserts the edges
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
    char names[2][41];
    error = false;  //reset error
    //asks for node names
    printf("Enter origin and destination (quit to exit): ");
    for (int i = 0; i < 2; i++) {
      scanf("%s", names[i]);
      //checks if user has entered "quit"
      if (!strcmp(names[0], "quit")) {
        loop = false;
        break;
      }
    }

    if (loop)
    {
      strcpy(src_name, names[0]);
      strcpy(dest_name, names[1]);
      //checks if nodes exist
      if (graph_find_node(g, src_name) == NULL ||
          graph_find_node(g, dest_name) == NULL)
          error = true;

      if (!error) {
        struct node *src = graph_find_node(g, src_name);
        struct node *dest = graph_find_node(g, dest_name);

        bool connected = find_path(g, src, dest); //try to find a path
        //message
        if (connected)
        {
          printf("There is a path from %s to %s.\n", src_name, dest_name);
        }
        else
        {
          printf("There is no path from %s to %s.\n", src_name, dest_name);
        }
        //reset seen status between runs:
        g = graph_reset_seen(g);
      }
      else
        printf("Invalid input\n");
    }
  }
  graph_kill(g);  //kill the graph
  printf("Normal exit.\n");
  return 0;
}
