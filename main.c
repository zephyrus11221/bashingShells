#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "shell.h"

void sigHandle(int sigNum){
  if(sigNum ==SIGINT){
    printf("SIGINT needs me, I'm out\n");
    exit(0);
  }
  if(sigNum == SIGUSR1){
    printf("My parent PID: %d\n",getppid());
  }
}

int main(){
  signal(SIGINT, sigHandle);
  signal(SIGUSR1, sigHandle);
  char *comm;
  char *s[256];
  comm = (char*)malloc(sizeof(char *));
  int i = 0;
  char *temp;
  int index, f;
  while(1){
    printf("waddya want:");
    fgets(comm, 255, stdin);
    temp = strstr(comm,"\n");
    index = temp - comm;
    comm[index] = 0;
    f = fork();
    if(!f){
      while (comm){
	s[i]=strsep(&comm, " ");
	i++;
      }
      s[i] = NULL;
      if(execvp(s[0], s)){
	printf("sumting wong in child\n");
	printf("%s\n", strerror(errno));
      }
    }
    wait();
  }
  return 0;
}
