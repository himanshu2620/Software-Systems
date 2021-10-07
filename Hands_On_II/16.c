#include <stdio.h>
#include <unistd.h>

void main(){
  int fds1[2];
  int fds2[2];
  pipe(fds1);
  pipe(fds2);
  pid_t pid = fork();
  if(pid!=0){ // parent enters this block
    close(fds1[0]); // close the unused ends (descriptors) , here it is read (fds[0])
    write(fds1[1],"Hello World1\n",12);
    close(fds1[1]);
    sleep(2);

    close(fds2[1]); // close write end of fds2
    char readBuffer[12];
    read(fds2[0],readBuffer,12);
    close(fds2[0]);
    printf("Data passed from Child to Parent process is : %s\n", readBuffer);
  }
  else{ // child enters this block
      close(fds1[1]);
      char readBuffer[12];
      read(fds1[0],readBuffer,12);
      close(fds1[0]);
      printf("Data passed from Parent to Child process is : %s\n", readBuffer);

      close(fds2[0]);
      write(fds2[1],"Hello World2\n",12);
      close(fds2[1]);
      sleep(2);
  }
}
