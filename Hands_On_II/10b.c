#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(){
  printf("signal SIGINT caught successfully using sigaction\n");
  exit(0);
}
void main(){
  struct sigaction currAction;
  currAction.sa_handler = handler;
  int status = sigaction(SIGINT,&currAction,NULL);
  if(status==-1){
    printf("error can't catch the SIGINT signal properly\n");
  }
  else{
    sleep(4);
    printf("No SIGINT within 4 seconds\n");
  }
}
