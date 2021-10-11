#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void main(){
  struct sigaction currAction;
  currAction.sa_handler = SIG_IGN;
  printf("Now ignoring the sigint for 4 seconds\n");
  sigaction(SIGINT,&currAction,NULL);
  sleep(4); // ignoring sigint for 4 seconds

  printf("Now changing to the default action of SIGINT\n");
  currAction.sa_handler = SIG_DFL;
  sigaction(SIGINT,&currAction,NULL);
  sleep(4);

}
