#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(){
  printf("signal SIGSEGV caught successfully\n");
  exit(0);
}
void main(){
  __sighandler_t status = signal(SIGSEGV,handler);
  if(status==SIG_ERR){
    printf("error can't catch the SIGSEGV signal properly\n");
  }
  else{
    raise(SIGSEGV);
  }
}
