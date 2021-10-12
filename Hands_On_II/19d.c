#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(){
    int status = mknod("myFifoMknod",S_IFIFO | 0744,0);
    if(status==-1){
      printf("Error in creating Fifo using mknod\n");
    }
    else{
      printf("Fifo file created successfully\n");
    }
}
