#include <stdio.h>
#include <sys/time.h>

void main(){
  struct itimerval timer;
  // timer for first time
  timer.it_value.tv_sec = 10;
  timer.it_value.tv_usec = 10;

  // timer for every interval
  timer.it_interval.tv_sec = 10;
  timer.it_interval.tv_usec = 10;
  int status = setitimer(ITIMER_PROF,&timer,NULL);
  while(1);
}
