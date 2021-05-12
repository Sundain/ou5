#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000
#define MAX_NUMBER_OF_EDGES 1000

int main(void) {

  FILE *fp;
  char str[MAXCHAR];
  char* filename = "c:\\Users\\Adden\\Desktop\\doan\\OU5\\airmap1.map";

  fp = fopen(filename, "r");

  int i = 0;
  int number_of_edges = -1;
  char origins[MAX_NUMBER_OF_EDGES][4];
  char destinations[MAX_NUMBER_OF_EDGES][4];
  while (fgets(str, MAXCHAR, fp) != NULL) {

      if((str[0] != '#' || str[0] != ' ') && number_of_edges == -1){
        number_of_edges = atoi(str);
      }
      else if(str[0] != '#' || str[0] != ' ') {
        char sub[3];

        for (size_t j = 0; j < 3; j++) {
          sub[j] = str[j];
        }
        strcpy(origins[i], sub);

        for (size_t j = 0; j < 3; j++) {
          sub[j] = str[j+4];
        }
        strcpy(destinations[i], sub);

        i++;
      }
  }
  fclose(fp);

  return 0;
}
