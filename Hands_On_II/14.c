#include <stdio.h>
#include <unistd.h>

void main(){
  int fds[2];
  pipe(fds);
  printf("Writing to the pipe\n");
  write(fds[1],"Hello World\n",11);
  char readBuffer[11];
  printf("Now reading from the pipe\n");
  read(fds[0],readBuffer,11); // reading from the pipe
  printf("Data read from the pipe is %s\n",readBuffer);
}
