#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// compile as gcc 12.c
// run the program as ./a.out srcfile

void main(int argc, char *argv[]) {
  if(argc==2){
    char* srcFile = argv[1];
    int fd = open(srcFile,O_RDONLY);
    if(fd!=-1){
      int status = fcntl(fd , F_GETFL);
      int mode = O_ACCMODE & status;
      printf("Flag values: \n");
      printf("RDONLY: 0\n");
      printf("WRONLY: 1\n");
      printf("O_RDWR: 2\n");
      if(mode==0){
        printf("File is opened in read only mode\n");
      }
      else if(mode==1){
        printf("File is opened in write only mode\n");
      }
      else if(mode==2){
        printf("File is opened in read and write mode \n");
      }
    }
    else{
      printf("Error in opening the file\n");
    }
    close(fd);
  }
  else{
    printf("Pass correct arguments\n");
  }
}
