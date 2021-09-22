#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// compile as gcc 04.c
// run the program as ./a.out srcfile

void main(int argc, char *argv[]) {
  if(argc == 2){
    char *srcFile = argv[1];
    int fd = open(srcFile, O_RDWR);
    if(fd!=-1){
      printf("File opened successfully in read write mode\n");
    }
    else{
      printf("Error while opening the file\n");
    }
  }
  else{
    printf("enter correct arguments\n");
  }
}
