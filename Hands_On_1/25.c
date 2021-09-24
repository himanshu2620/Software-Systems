#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main(){
  pid_t firstChild = fork();
  if(firstChild==0){ // first child process enters this branch
    sleep(5);
    printf("First child process exits\n");
  }
  else{
    // Parent process enters here
    pid_t secondChild = fork();
    if(secondChild==0){ // second child process enters this branch
      sleep(7);
      printf("Second child process exits\n");
    }
    else{
      pid_t thirdChild = fork();
      if(thirdChild==0){ // third child process enters this branch
        sleep(9);
        printf("Third child process exits\n");
      }
      else{ // Parent enters this branch
          printf("Parent process waiting for third child process: %d\n", thirdChild);
          waitpid(thirdChild,NULL,0);
          printf("Parent exits now\n");
      }
    }
  }
}
