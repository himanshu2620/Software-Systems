#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(){
    int status = mkfifo("myFifoMkfifo",0744);
    if(status==-1){
      printf("Error in creating Fifo using mkfifo\n");
    }
    else{
      printf("Fifo file created successfully\n");
    }
}
