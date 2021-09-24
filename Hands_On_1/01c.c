#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){
  // Using mkfifo library function
  char* mkFifoFile = "mkfifoFile";
  int st1 = mkfifo(mkFifoFile,S_IRWXU);
  if(st1==-1){
    printf("Error in creating the Fifo file using mkfifo library function\n");
  }
  else{
    printf("Fifo File created successfully using mkfifo library function\n");
  }

  // Using mknod system call
  char* mkNodFile = "mkNodFile";
  int st2 = mknod(mkNodFile,S_IRWXU | S_IFIFO,0); // 2nd argument is bitwise OR of file type and file mode
  if(st2==-1){
    printf("Error in creating the Fifo file using mknod system call\n");
  }
  else{
    printf("Fifo File created successfully using mknod system call\n");
  }
}
