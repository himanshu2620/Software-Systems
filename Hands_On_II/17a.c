#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void main(){
  int fd[2];// fd[0] for read & fd[1] for write
  pipe(fd);
  pid_t pid = fork();
  if(pid==0){// child enters this block
      close(0);// close stdin so as to Read from pipe
      close(fd[1]);
      dup(fd[0]);
      execl("/usr/bin/wc","wc",NULL);
  }
  else{// parent enters here
    // ls -l | wc
    close(1);// close stdout so that the output of ls -l doesn't go to STDOUT
    close(fd[0]);
    dup(fd[1]);
    execl("/bin/ls","ls","-l",NULL);
  }
}
