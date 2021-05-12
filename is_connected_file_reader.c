#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000
#define MAX_NUMBER_OF_EDGES 1000

int main(void) {

  FILE *fp;
  char str[MAXCHAR];
  char* filename = "c:\\Users\\Adden\\Desktop\\doan\\OU5\\airmap2.map";

  fp = fopen(filename, "r");

  int i = 0;
  int number_of_edges = -1;
  char origins[MAX_NUMBER_OF_EDGES][41];
  char destinations[MAX_NUMBER_OF_EDGES][41];
  while (fgets(str, MAXCHAR, fp) != NULL) {

    if (str[0] != '#' && str[0] != ' ') {
      if(number_of_edges == -1){
        number_of_edges = atoi(str);
      }
      else {
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
  }
  fclose(fp);

  return 0;
}
