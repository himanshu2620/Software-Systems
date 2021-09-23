#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// compile as gcc 11a.c
// run the program as ./a.out srcfile

void main(int argc, char *argv[]) {
  if(argc==2){
    char* srcFile = argv[1];
    int fd = open(srcFile,O_RDWR,O_APPEND);
    if(fd!=-1){
      int dupFd = dup(fd);
      write(fd,"write from original fd ",23);
      write(dupFd,"write from duplicated fd",24);
      close(fd);
    }
  }
  else{
    printf("Enter correct arguments\n");
  }
}
