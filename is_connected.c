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

 /**
 * copy_string() - Create a dynamic copy of a string.
 * @s: String to be copied.
 *
 * Allocates memory for a dynamic copy of s and copies the contents of
 * s into the copy.
 *
 * Returns: Pointer to the copy of s.
 */
char *copy_string(const char *s)
{
  int len=strlen(s);

  /* Allocate memory for new string, with an extra char for \0 */
  char *dest = malloc(sizeof(char)*(len+1));

  /* Malloc failed, return NULL */
  if (dest == NULL) {
    return NULL;
  }

  /* Copy content to new memory */
  strncpy(dest, s, len);

  /* Strings should always be null terminated */
  dest[len] = '\0';
  return dest;
}

 bool find_path(graph *g, node *src, node *dest)
 {
   //Creating an empty queue
   queue *q = queue_empty(NULL);
   bool seen = true;

   if (nodes_are_equal(dest,src))
   {
     queue_kill(q);
     return true;
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
           dlist_kill(neighbours);
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
   dlist_kill(neighbours);
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
  graph *g = graph_empty(100); //empty graph
  if (argc == 1) {
    printf("No map!\n");
    exit(EXIT_FAILURE);
  }

  //string vector containing nodes connected by edges
  while (fgets(str, MAXCHAR, fp) != NULL) {

    if (str[0] != '#' && str[0] != ' ' && number_of_edges == -1) {
      number_of_edges = atoi(str);
    }

    //ignors rows starting with # or blanck space
    else if (str[0] != '#' && str[0] != ' ')
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
      if (error) {
        break;
      }
      sub[j] = '\0';
      char* origin = copy_string(sub);

      j++;
      int k = 0;
      //reads the name until it ends
      while(str[j] != ' ' && str[j] != '#' && str[j] != '\n') {
        sub[k] = str[j];
        j++;
        k++;
      }
      sub[k] = '\0';
      char* destination = copy_string(sub);
      i++;

      bool free_origin = false;
      bool free_destination = false;
      //inserts the origin nodes
      if (graph_find_node(g, origin) == NULL) {
        graph_insert_node(g, origin);
      }
      else
        free_origin = true;
      //inserts the destination nodes
      if (graph_find_node(g, destination) == NULL) {
        graph_insert_node(g, destination);
      }
      else
        free_destination = true;
      //inserts the edges
      struct node *n1 = graph_find_node(g, origin);
      struct node *n2 = graph_find_node(g, destination);
      graph_insert_edge(g, n1, n2);

      if (free_origin)
        free(origin);
      if (free_destination)
        free(destination);
    }
  }

  //checks if number_of_edges has been given a value
  if (number_of_edges < 1)
    error = true;

  //checks that the indicated number of edges is correct
  if (i != number_of_edges)
    error = true;

  //error message
  if (error) {
    printf("Invalid map\n");
    exit(EXIT_FAILURE);
  }

  fclose(fp);

  bool loop=true;
  while (loop)
  {
    // char* src_name;
    // char* dest_name;
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
      // src_name = copy_string(names[0]);
      // dest_name = copy_string(names[1]);
      //checks if nodes exist
      if (graph_find_node(g, names[0]) == NULL ||
          graph_find_node(g, names[1]) == NULL)
          error = true;

      if (!error) {
        struct node *src = graph_find_node(g,  names[0]);
        struct node *dest = graph_find_node(g,  names[1]);

        bool connected = find_path(g, src, dest); //try to find a path
        //message
        if (connected)
        {
          printf("There is a path from %s to %s.\n",  names[0],  names[1]);
        }
        else
        {
          printf("There is no path from %s to %s.\n",  names[0],  names[1]);
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
