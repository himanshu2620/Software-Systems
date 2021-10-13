#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// run as cc -o write 21a.c
// then   cc -o read 21b.c
// then ./write
// then ./read
void main(){
    int fd1 = open("fifo1_21",O_RDONLY);// fifo file 1
    int fd2 = open("fifo2_21",O_WRONLY);// fifo file 2
    if(fd1==-1 || fd2==-1){
      printf("Couldn't open one of the Fifo file \n");
    }
    else{
      char buff[20];
      read(fd1,buff,sizeof(buff));
      printf("Message Read from FIFO1 file is : %s\n", buff);
      close(fd1);

      char buff2[]="Hello World 2";
      int bytes = write(fd2,&buff2,sizeof(buff2));
      if(bytes==-1){
        printf("Couldn't write to file\n");
        close(fd2);
      }
    }
  }
