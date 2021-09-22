#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// compile as gcc 10.c
// run the program as ./a.out srcfile

void main(int argc, char *argv[]) {
  if(argc==2){
    char* srcFile = argv[1];
    int fd = open(srcFile,O_RDWR);
    if(fd!=-1){
      int cnt = write(fd,"HelloThere",10);
      int offset = lseek(fd,10,SEEK_CUR); // SEEK_CUR --> curr location + offset
      cnt = write(fd,"HelloThere",10);
      printf("the lseek value is : %d \n", offset);
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
