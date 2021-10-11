#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(){
  printf("signal SIGINT caught successfully\n");
  exit(0);
}
void main(){
  __sighandler_t status = signal(SIGINT,handler);
  if(status==SIG_ERR){
    printf("error can't catch the SIGINT signal properly\n");
  }
  else{
    while(1);
  }
}
