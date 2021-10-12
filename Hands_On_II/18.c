#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// ls -l | grep ^d | wc
void main(){
  int fd[2];// for communication b/w child 1 and child 2
  int fd1[2]; // for communication b/w child 2 and Parent
  pipe(fd);
  pipe(fd1);
  pid_t firstChild = fork();
  if(firstChild==0){ // first child process enters this branch
    //sleep(3);
    close(1);
    close(fd[0]);
    close(fd1[0]);
    close(fd1[1]);
    dup2(fd[1],1);
    execl("/bin/ls","ls","-l",NULL);
  }
  else{
    pid_t secondChild = fork();
    if(secondChild==0){ // second child process enters this branch
      close(0);// close the STDIN
      close(1);// close the STDOUT
      close(fd[1]); // close write end of pipe b/w child 1 and child 2
      close(fd1[0]);// close read end of pipe b/w child 2 and parent
      dup2(fd[0],0);
      dup2(fd1[1],1);
      execl("/bin/grep","grep","^d",NULL);
    }
    else{ // Parent process enters here
      //waitpid(secondChild,NULL,0);
      close(0);
      close(fd[0]);
      close(fd[1]);
      close(fd1[1]);
      dup2(fd1[0],0);
      execl("/usr/bin/wc","wc",NULL);
    }
  }
}
