#include<stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

void main(){
  int res;
  struct timeval timeout;
  // now set timeout to 10 seconds as given in the problem description
  timeout.tv_sec = 10;
  timeout.tv_usec = 0;

  fd_set readFdSet;
  fd_set writeFdSet;
  FD_SET(STDIN_FILENO, &readFdSet); // add STDIN to the read file descriptor set
  FD_SET(STDOUT_FILENO, &writeFdSet);// add STDOUT to the write file descriptor set

  res = select(1, &readFdSet , &writeFdSet , NULL , &timeout);
  if(res==1){
    printf("input data is available within 10 seconds \n");
  }
  else if(res==0){
    printf("input not available within 10 seconds\n");
  }
}
