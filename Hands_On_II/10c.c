#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(){
  printf("signal SIGFPE caught successfully using sigaction\n");
  exit(0);
}
void main(){
  struct sigaction currAction;
  currAction.sa_handler = handler;
  int status = sigaction(SIGFPE,&currAction,NULL);
  if(status==-1){
    printf("error can't catch the SIGFPE signal properly\n");
  }
  else{
    raise(SIGFPE);
  }
}
