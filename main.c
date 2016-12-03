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

void execFork(char * comm){
  printf("%s\n",comm[0]);
  int f;
  f = fork();
  if(!f){
    execvp(comm[0],comm);
  }
  else{
    int holder;
    wait(&holder);
  }
}
void commCentral(char *comm){
  char * tempHolder = comm;
  while(tempHolder){
    char * fixedComm[256];
    char * currentProcess = strsep(&tempHolder,";");
    int i = 0;
    while(currentProcess){
      fixedComm[i] =strsep(&currentProcess," ");
      printf("fixedComm[%i]: %s\n",i,fixedComm[i]);
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
      int f;
      f = fork();
      if(!f){
	if(strchr(fixedComm,'>')!=NULL){
	  int storage = dup(STDOUT_FILENO);
	  char * fileName = fixedComm[2];
	  int fd;
	  fd = open(fileName, O_WRONLY | O_CREAT, 0644);
	  dup2(fd,STDOUT_FILENO);
	  execvp(fixedComm[0],fixedComm);
	  dup2(storage,STDOUT_FILENO);
	}
	else{
	  execvp(fixedComm[0],fixedComm);
	}
      }
      else{
	int holder;
	wait(&holder);
      }
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
