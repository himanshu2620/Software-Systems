#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(){
  printf("signal SIGFPE caught successfully\n");
  exit(0);
}
void main(){
  __sighandler_t status = signal(SIGFPE,handler);
  if(status==SIG_ERR){
    printf("error can't catch the SIGFPE signal properly\n");
  }
  else{
    raise(SIGFPE);
  }
}
