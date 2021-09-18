#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// compile as gcc 07.c
// run the program as ./a.out srcfilePath desFilePath

void main(int argc, char *argv[]) {
  char* srcFilePath = argv[1];
  char* desFilePath = argv[2];
  if(argc==3){
      int srcFd = open(srcFilePath,O_RDONLY); // open the source file in read only mode
      int desFd = open(desFilePath, O_CREAT | O_RDWR, 00700); // open the destination file in read write mode , also if it doesn't exist create it
      if(srcFd==-1 || desFd == -1){
        printf("Error in opening the source or destination file\n");
        return;
      }
      char c;
      while(read(srcFd,&c,1)){
        write(desFd,&c,1);
      }
      close(srcFd);
      close(desFd);
  }
  else{
    printf("Enter correct arguments\n");
  }
}
