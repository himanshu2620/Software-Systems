#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// run as cc -o write 20a.c
// then   cc -o read 20b.c
// then ./write
// then ./read 
void main(){
    int currFd = open("myFifo_20",O_RDONLY);
    if(currFd==-1){
      printf("Error couldn't open file properly\n");
    }
    else{
      char buff[11];
      read(currFd,buff,sizeof(buff));
      printf("Message Read from FIFO file is : %s\n", buff);
      close(currFd);
    }
  }
