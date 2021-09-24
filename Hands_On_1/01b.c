#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
// execute as ./a.out srcfilePath hardLinkfilePath
void main(int argc, char *argv[]) {
  if(argc==3){
      char* srcFile = argv[1];
      char* softLink = argv[2];
      int status = link(srcFile,softLink);
      if(status==0){
        printf("Hard Link created successfully\n");
      }
      else{
        printf("Error in creating the hard link\n");
      }
  }
  else{
    printf("Enter correct arguments\n");
  }
}
