#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void main(){
  __sighandler_t status = signal(SIGINT,SIG_IGN);
  sleep(4); // ignoring sigint for 4 seconds

  printf("Now changing to the default action of SIGINT\n");
  signal(SIGINT,SIG_DFL);
  sleep(4);
  
}
