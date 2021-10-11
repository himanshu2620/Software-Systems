#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>

void main(){
  pid_t parPid = getpid();
  pid_t pid = fork();
  if(pid==0){ // child enters this block
      printf("Child pid is : %d\n",getpid());
      kill(parPid,SIGKILL);
      sleep(6);
  }
  else{ // parent enters here
    printf("Parent process id is : %d\n",parPid);
    sleep(4);
  }
}
