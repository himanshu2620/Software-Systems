#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(){
  printf("signal SIGSTOP caught successfully\n");
  exit(0);
}
void main(){
  pid_t parPid = getpid();
  pid_t pid = fork();
  if(pid==0){//child enters this block
    printf("Now trying to stop the parent process using SIGSTOP\n");
    kill(parPid,SIGSTOP);
  }
  else{//parent enters here
    signal(SIGSTOP,handler);
    while(1);
  }
}
