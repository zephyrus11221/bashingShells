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
void rmChar (char arr[], int start){
    char temp;
    int i;
    for (i=start; i < sizeof(arr)/sizeof(arr[0]); i++){
        temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
    }
}
void commCentral(char *comm){
  char * tempHolder = comm;
  while(tempHolder){
    char * fixedComm[256];
    int index = 0;
    int start = 0;
    char * currentProcess = strsep(&tempHolder,";");
    int i = 0;
    while(currentProcess){
      fixedComm[i] =strsep(&currentProcess," ");
      //printf("fixedComm[%i]: %s\n",i,fixedComm[i]);
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
      int check;
      int checker;
      if(!f){
       	//printf("I'm here 1\n");
        for(check = 0; fixedComm[check]!= NULL; check++){
	  if(strchr(fixedComm[check],'>')!= NULL){
	    checker = 1;
	  }
	  if(strchr(fixedComm[check],'<')!= NULL){
	    checker = 2;
	  }
	  if(strchr(fixedComm[check],'|')!= NULL){
	    checker = 3;
	  }
	}
	if(checker == 1){
	  //printf("I'm here 2\n");
	    int storage = dup(STDOUT_FILENO);
	    int count = 0;
	    int count2 = 0;
	    char * temp[256];
	    for(count; strcmp(fixedComm[count],">")!=0; count++){
	    }
	    count++;
	    char * fileName = fixedComm[count];
	    for(count2; count2 < count - 1; count2++){
	      temp[count2] = fixedComm[count2];
	    }
	    temp[count2] = NULL;
	    int fd;
	    fd = open(fileName, O_RDWR | O_CREAT, 0644);
	    dup2(fd,STDOUT_FILENO);
	    execvp(temp[0],temp);
	    dup2(storage,STDOUT_FILENO);
	    close(fd);
	}
	if(checker == 2){
	  int storage = dup(STDIN_FILENO);
	  int count = 0;
	  int count2 = 0;
	  char * temp[256];
	  for(count; strcmp(fixedComm[count],"<")!=0; count++){
	  }
	  count++;
	  char * fileName = fixedComm[count];
	  for(count2; count2 < count - 1; count2++){
	    temp[count2] = fixedComm[count2];
	  }
	  temp[count2] = NULL;
	  int fd;
	  fd = open(fileName, O_RDONLY, 0644);
	  dup2(fd,STDIN_FILENO);
	  execvp(temp[0],temp);
	  dup2(storage,STDIN_FILENO);
	  close(fd);
	}
	if(checker ==3){
	  int storage = dup(STDOUT_FILENO);
	    int count = 0;
	    int count2 = 0;
	    char * temp[256];
	    for(count; strcmp(fixedComm[count],"|")!=0; count++){
	    }
	    
	    int fd;
	    fd = open("temp.txt", O_RDWR | O_CREAT, 0777);
	    fixedComm[count] = 0;
	    dup2(fd,STDOUT_FILENO);
	    execvp(fixedComm[0],fixedComm);
	    dup2(storage,STDOUT_FILENO);
	    close(fd);
	    
	    fd = open("temp.txt",O_RDWR,0777);
	    int storage2 = dup(STDIN_FILENO);
	    dup2(fd,STDIN_FILENO);
	    while(count+1 < strlen(fixedComm)){
	      temp[count2]=fixedComm[count+1];
	    }
	    execvp(temp[0],temp);
	    dup2(storage2,STDIN_FILENO);
	    remove("temp.txt");
	}
	    
	if(checker == 3){
	    int storage = dup(STDOUT_FILENO);
	    int count = 0;
	    int count2 = 0;
	    char * temp[256];
	    for(count; strcmp(fixedComm[count],">")!=0; count++){
	    }
	    count++;
	    for(count2; count2 < count - 1; count2++){
	      temp[count2] = fixedComm[count2];
	    }
	    temp[count2] = NULL;
	    int fd;
	    fd = open("pipe.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	    dup2(fd,STDOUT_FILENO);
	    int f2 = fork();
	    if(f2){
    	    execvp(temp[0],temp);
	        dup2(storage,STDOUT_FILENO);
	        close(fd);
	    }else{
	        int holder;
	        wait(&holder);
	        count = 0;
      	    count2 = 0;
	        for(count; strcmp(fixedComm[count],"<")!=0; count++){
    	    }
	        count++;
	        for(count2; count2 < count - 1; count2++){
	        temp[count2] = fixedComm[count2];
            }
	        temp[count2] = NULL;
	        int fd;
	        fd = open("pipe.txt", O_RDONLY, 0644);
	        dup2(fd,STDIN_FILENO);
	        execvp(temp[0],temp);
	    }
	}
	  else{
	  //printf("I'm here 1\n");
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
