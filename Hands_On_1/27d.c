#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){
  char *const argv1[] = {"/bin/ls","-Rl",NULL};
  printf("Executing ls -Rl using execv system call\n");
  execv("/bin/ls",argv1); // args :  path , argv[])
}
