#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

// run as cc -o write 20a.c
// then   cc -o read 20b.c
// then ./write
// then ./read in a new terminal
void main(){
    int currFd = open("myFifo_22",O_RDONLY);
    if(currFd==-1){
      printf("Error couldn't open file properly\n");
    }
    else{
      char buff[11];
      struct timeval currTO;//timeout
      currTO.tv_sec = 10;
      currTO.tv_usec = 0;
      int nfds = currFd + 1;
      fd_set rfds;// read
      FD_ZERO(&rfds);
      FD_SET(currFd,&rfds);
      int status1 = select(nfds,&rfds,NULL,NULL,&currTO);
      if(status1==-1){
        printf("Error using the select call\n");
      }
      else if(status1){
        read(currFd,buff,sizeof(buff));
        printf("Message Read from FIFO file is : %s\n", buff);
        close(currFd);
      }
      else{
        printf("No data sent within the 10 seconds interval\n");
      }
    }
}
