#include <stdio.h>
#include <unistd.h>

void main(){
  int fds[2];
  pipe(fds);
  pid_t pid = fork();
  if(pid!=0){ // parent enters this block
    close(fds[0]); // close the unused ends (descriptors) , here it is read (fds[0])
    write(fds[1],"Hello World\n",11);
    close(fds[1]);
  }
  else{ // child enters this block
      close(fds[1]);
      char readBuffer[11];
      read(fds[0],readBuffer,11);
      close(fds[0]);
      printf("Data passed from Parent to Child process is : %s\n", readBuffer);
  }
}
