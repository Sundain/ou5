#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define MAXCHAR 1000

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

  for (size_t i = 0; i < number_of_edges; i++) {
    printf("%s %s\n", origins[i], destinations[i]);
  }

  // graph g = graph_empty(number_of_edges);
  //
  // for (size_t i = 0; i < number_of_edges; i++) {
  //   if (graph_find_node(g, origins[i]) != NULL)
  //     graph_insert_node(g, origins[i]);
  // }
  //
  // for (size_t i = 0; i < number_of_edges; i++) {
  //   if (graph_find_node(g, destinations[i]) != NULL)
  //     graph_insert_node(g, destinations[i]);
  // }
  //
  // for (size_t i = 0; i < number_of_edges; i++) {
  //   struct node n1 = graph_find_node(g, origins[i]);
  //   struct node n2 = graph_find_node(g, destinations[i]);
  //   graph_insert_edge(g, n1, n2);
  // }

  return 0;
}
