#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <graph.h>

#define MAXCHAR 1000

int main(void) {

  // char text[8];
  // printf("Enter origin and destination (quit to exit): ");
  // scanf("%s", text);
  //
  // char destination1[3] = {text[0], text[1], text[2]};
  // char destination2[3] = {text[4], text[5], text[6]};

  FILE *fp;
  char str[MAXCHAR];
  char* filename = "c:\\Users\\Adden\\Desktop\\doan\\OU5\\airmap1.map";

  fp = fopen(filename, "r");
  if (fp == NULL){
      printf("Could not open file %s",filename);
      return 1;
  }

  int number_of_edges = -1;
  while (fgets(str, MAXCHAR, fp) != NULL) {

      if(str[0] != '#' && number_of_edges != -1){
        edges[1] = {str[0], str[1], str[2], str[3], str[4], str[5], str[6]};
      }
      else if(str[0] != '#') {
        number_of_edges = atoi(str);
        char edges[number_of_edges][8];
      }
  }
  printf("%d\n", number_of_edges);
  fclose(fp);

  return 0;
}
