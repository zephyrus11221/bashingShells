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
  int f;
  f = fork();
  if(!f){
    // printf("fixedComm[%d]:%s\n",0,fixedComm[0]);
    execvp(comm[0],comm);
  }
  else{
    int holder;
    wait(&holder);
    holder = 0;
    return holder;
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
      //printf("fixedComm[%d]:%s\n",i,fixedComm[i]);
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
	// printf("fixedComm[%d]:%s\n",0,fixedComm[0]);
	execvp(fixedComm[0],fixedComm);
      }
      else{
	int holder;
	wait(&holder);
      }
    }
    commCentral(tempHolder);
  }
}

/*int * pipe(char *comm){
  }*/
int *redirWrite(char *comm){
  char * commSplit;
  char * file2;
  int i =0;
  int checker = 1;
  while(i < strlen(comm)){
    if(strcmp(comm[i]," ")){
      i++;
    }
    else{
      checker = 0;
    }
  }
  if(checker){
    int i = strlen(comm);
    for(;i>0;i--){
      file2 = strsep(&comm," ");
    }
  }
  else{
    commSplit = strstr(comm,">");
    strncpy(file2,commSplit + 1,strlen(commSplit)-1);
  }


  commSplit = strstr(comm,">");
  char * fileName;
//strcpy(commSplit,fileName,
}

  /*int * redirApp(char *comm){
    }*/
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
