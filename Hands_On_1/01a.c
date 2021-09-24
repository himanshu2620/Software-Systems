#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
// execute as ./a.out srcfilePath softLinkfilePath
void main(int argc, char *argv[]) {
  if(argc==3){
      char* srcFile = argv[1];
      char* softLink = argv[2];
      int status = symlink(srcFile,softLink);
      if(status==0){
        printf("softLink created successfully\n");
      }
      else{
        printf("Error in creating the soft link\n");
      }
  }
  else{
    printf("Enter correct arguments\n");
  }
}
