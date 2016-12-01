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
int * cd(char *dir){
}
int check(char * comm){
  const char *shellComms = "cd,>,>>,<,<<,|,&";
  int def = -1;
  char *temp;
  while(comm){
    temp = strsep(shellComms,",");
    if(!strcmp(comm,temp)){
      def = 0;
    }
  }
  return def;
}
int * pipe(char *comm){
}
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
    int i = 2;
    for(;i>0;i--){
      file2 = strsep(comm," ");
    }
  }
  else{
    commSplit = strstr(comm,">");
    strncpy(file2,commSplit + 1;strlen(commSplit)-1);
  }
}

  commSplit = strstr(comm,">");
  char * fileName;
  strcpy(commSplit,fileName,
}
int * redirApp(char *comm){
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
      strsep(s, ">");
      if(s){
	char hold = strsep(s, " ");
	if(hold){
	  int fd = open(hold, O_CREAT|O_RDWR, 0644);
	}
	if(s){
	  int fd = open(s, O_CREAT|O_RDWR, 0644);
	}
	dup2(fd, stdout);
      if(execvp(s[0], s)){
	printf("sumting wong in child\n");
	printf("%s\n", strerror(errno));
      }
    }
    wait();
  }
  return 0;
}
