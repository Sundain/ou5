#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "dlist.h"
#include "util.h"

struct graph {
	dlist *nodes;
};

struct node {
  dlist *edges;
  char *name;
  bool *seen;
};
