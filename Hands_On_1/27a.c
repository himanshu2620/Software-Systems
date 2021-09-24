#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){
  printf("Executing ls -Rl using execl system call\n");
  execl("/bin/ls","/bin/ls","-Rl",NULL);
}
