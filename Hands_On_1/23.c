// ps aux | grep 'Z'
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void main(){
  pid_t pid = fork();
  if(pid){ // parent enters this block
    printf("parent process pid is : %d\n", getpid());
    printf("parent process now goes to sleep\n");
    sleep(40);
    printf("parent process is awake now\n");
  }
  else if(pid==0){ // child process enters here
    printf("Child process pid is : %d \n", getpid());
    printf("Child process is terminated now\n");
    _exit(0);// at this point child is terminated and since is parent is in sleep state , we now have a zombie state
  }
}
