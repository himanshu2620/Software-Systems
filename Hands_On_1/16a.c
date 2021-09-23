#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// compile as gcc 16a.c
// run the program as ./a.out srcfile

void main(int argc, char *argv[]) {
  if(argc==2){
      char* srcFile = argv[1];
      int fd = open(srcFile, O_RDWR);
      if(fd==-1){
        printf("Error in opening the file\n");
      }
      else{
        struct flock curr;
        curr.l_type = F_WRLCK;
        curr.l_whence = SEEK_SET;
        curr.l_start = 0;
        curr.l_len =0; // 0 is to lock all bytes
        curr.l_pid = getpid();
        fcntl(fd,F_SETLK,&curr);
        printf("Write lock has been applied to file\n");
      }
  }
  else{
    printf("Pass correct arguments\n");
  }
}
