#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// compile as gcc 08.c
// run the program as ./a.out srcfile

void main(int argc, char *argv[]) {
    if(argc==2){
        char* srcFile = argv[1];
        int fd = open(srcFile,O_RDONLY);
        if(fd!=-1){
            char curr;
            while(read(fd,&curr,1)){
              if(curr == '\n'){
                printf("\n");
              }
              else{
                printf("%c",curr);
              }
            }
        }
        else{
          printf("error in opening the source file \n");
        }
        close(fd);
    }
    else{
      printf("pass correct arguments\n");
    }
}
