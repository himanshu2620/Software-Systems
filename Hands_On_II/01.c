// man 2 setitimer
/*
  1-> user time
  2--> user + io + kernel
  3--> user + kernel
*/
#include <stdio.h>
#include <sys/time.h>

void main(){
  struct itimerval timer;
  timer.time
  int status = setitimer(ITIMER_REAL,,NULL);
}
