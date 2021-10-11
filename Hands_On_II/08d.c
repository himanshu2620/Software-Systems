#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(){
  printf("signal SIGALRM caught successfully\n");
  exit(0);
}
void main(){
  __sighandler_t status = signal(SIGALRM,handler);
  if(status==SIG_ERR){
    printf("error can't catch the SIGALRM signal properly\n");
  }
  else{
    alarm(2); // generates SIGALRM after 2 seconds
    while(1);
  }
}
