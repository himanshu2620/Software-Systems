#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){
  printf("Executing ls -Rl using execlp system call\n");
  // execlp search for the file using the PATH environment variable
  execlp("ls","ls","-Rl",NULL);
}
