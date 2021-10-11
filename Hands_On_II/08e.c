#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void handler(){
  printf("signal SIGALRM caught successfully\n");
  exit(0);
}
void main(){
  __sighandler_t status = signal(SIGALRM,handler);
  struct itimerval currTimer;
  currTimer.it_interval.tv_sec = 0;
  currTimer.it_interval.tv_usec = 0;
  currTimer.it_value.tv_sec = 2; // set an alarm that raises SIGALRM after 2 seconds
  currTimer.it_value.tv_usec = 0;
  if(status==SIG_ERR){
    printf("error can't catch the SIGALRM signal properly\n");
  }
  else{
    setitimer(ITIMER_REAL,&currTimer,NULL);
    while(1);
  }
}
