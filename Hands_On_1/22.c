#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void main(){
  char* srcFile = "sample.txt";
  int fd = open(srcFile, O_CREAT | O_WRONLY, S_IRWXU);
  pid_t pid = fork();
  if(pid == 0){ // child enters this branch
    write(fd , "HelloFromChild \n" , 14); // args : fd , buf, count
  }
  else if(pid!=0){
    write(fd , "HelloFromParent \n" , 15);
  }
  close(fd);
}
