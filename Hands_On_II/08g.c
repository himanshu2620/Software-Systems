#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void handler(){
  printf("signal SIGPROF caught successfully\n");
  exit(0);
}
void main(){
  __sighandler_t status = signal(SIGPROF,handler);
  struct itimerval currTimer;
  currTimer.it_interval.tv_sec = 0;
  currTimer.it_interval.tv_usec = 0;
  currTimer.it_value.tv_sec = 2; // set an alarm that raises SIGPROF after 2 seconds
  currTimer.it_value.tv_usec = 0;
  if(status==SIG_ERR){
    printf("error can't catch the SIGPROF signal properly\n");
  }
  else{
    setitimer(ITIMER_PROF,&currTimer,NULL);
    while(1);
  }
}
