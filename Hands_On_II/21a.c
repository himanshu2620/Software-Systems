#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
// run as cc -o write 21a.c
// then   cc -o read 21b.c
// then ./write
// then ./read
void main(){

    int fd1 = open("fifo1_21",O_WRONLY);
    int fd2 = open("fifo2_21",O_RDONLY);
    if(fd1==-1 || fd2==-1){
      printf("Couldn't open one of the Fifo file \n");
    }
    else{
      char buff[]="Hello World 1";
      int bytes = write(fd1,&buff,sizeof(buff));
      if(bytes==-1){
        printf("Couldn't write to file\n");
        close(fd1);
      }

      char buff2[20];
      read(fd2,buff2,sizeof(buff2));
      printf("Message Read from FIFO file is : %s\n", buff2);
      close(fd2);
    }
  }
