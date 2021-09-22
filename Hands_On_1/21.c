#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void main(){
  pid_t pid = fork();
  if(pid > 0){
    int parent_pid = getpid();
    printf("Parent process id is: %d \n", parent_pid);
  }
  else if(pid==0){
    int child_pid = getpid();
    printf("Child process id is: %d\n", child_pid);
  }
  else{
    perror("fork");
  }
}
