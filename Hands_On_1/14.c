#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// compile as gcc 14.c
// run the program as ./a.out srcfile

void main(int argc, char *argv[]) {
  if(argc==2){
    struct stat fileType;
    char* srcFile = argv[1];
    int val = lstat(srcFile, &fileType);
    if(val == -1){
      perror("error");
    }
    else{
      if (S_ISREG(fileType.st_mode)){
        printf("File type is: Regular file\n");
      }
      else if (S_ISDIR(fileType.st_mode)){
        printf("File type is: Directory file\n");
      }
      else if (S_ISCHR(fileType.st_mode)){
        printf("File type is: Character file\n");
      }
      else if (S_ISLNK(fileType.st_mode)){
        printf("File type is: Symlink file\n");
      }
      else if (S_ISSOCK(fileType.st_mode)){
        printf("File type is: Socket file\n");
      }
      else if (S_ISBLK(fileType.st_mode)){
        printf("File type is: Block file\n");
      }
      else if (S_ISFIFO(fileType.st_mode)){
        printf("File type is: Fifo file \n");
      }
      else{
        printf("File type is: UNKNOWN \n");
      }
    }
  }
  else{
    printf("Pass correct arguments\n");
  }
}
