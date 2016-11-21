#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "shell.h"

int main(){
  char *comm;
  char *s[256];
  comm = (char*)malloc(sizeof(char *));
  fgets(comm, 255, stdin);
  int i = 0;
  char *temp;
  temp = strstr(comm,"\n");
  int index;
  index = temp - comm;
  comm[index] = 0;
  return 0;
}
