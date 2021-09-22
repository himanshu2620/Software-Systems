#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void main(){
  pid_t pid = fork();
  if(pid){ // parent enters this block
    printf("parent process pid is : %d\n", getpid());
    printf("Now exiting parent process...\n");
    _exit(0);
  }
  else if(pid==0){ // child process enters here
    printf("Child process pid is : %d \n", getpid());
    printf("Child process is going to sleep now..\n");
    sleep(40);
    printf("Child process is awake now\n");
  }
}
