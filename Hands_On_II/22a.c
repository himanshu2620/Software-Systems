#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
// run as cc -o write 22a.c
// then   cc -o read 22b.c
// then ./write
// then ./read
void main(){
  int currFd;
  int status = mkfifo("myFifo_22",0744);
  if(status==-1){
    printf("Error while creating the fifo file\n");
  }
  else{
    currFd = open("myFifo_22",O_WRONLY);
    if(currFd==-1){
      printf("Couldn't open Fifo file \n");
    }
    else{
      char buff[]="Hello World";
      int bytes = write(currFd,&buff,sizeof(buff));
      if(bytes==-1){
        printf("Couldn't write to file\n");
        close(currFd);
      }
    }
  }

}
