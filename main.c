#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

int execFork(char * comm){
  char * source = comm;
  char * storage[256];
  int counter = 0;
  while(source){
    storage[counter] = strsep(&source, " ");
    counter++;
  }
  storage[counter] = NULL;
  int f;
  f = fork();
  if(!f){
    execvp(storage[0],storage);
  }
  else{
    int holder;
    wait(&holder);
  }
}
void commCentral(char *comm){
  char * tempHolder = comm;
  char * fixedComm[256];
  while(tempHolder){
    char * currentProcess = strsep(&tempHolder,";");
    int i = 0;
    while(currentProcess){
      fixedComm[i] =strsep(&currentProcess," ");
      i++;
    }
    fixedComm[i] = NULL;
    if(!strcmp(fixedComm[0],"cd")){
      chdir(fixedComm[1]);
    }
    else if(!strcmp(fixedComm[0],"exit")){
      exit(0);
    }
    else{
      printf("%s\n",currentProcess);
      execFork(currentProcess);
    }
    commCentral(tempHolder);
  }
}

int main(){
  signal(SIGINT, sigHandle);
  signal(SIGUSR1, sigHandle);
  char directory[256];
  char comm[256];
  while(1){
    if(getcwd(directory,sizeof(directory))!=NULL){
      printf("%s# ",directory);
    }
    fgets(comm,sizeof(comm), stdin);
    char *temp;
    temp = strstr(comm,"\n");
    int index;
    index = temp - comm;
    comm[index] = 0;
    commCentral(comm);
  }
  return 0;
}
