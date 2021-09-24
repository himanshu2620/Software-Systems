#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){
  printf("Executing ls -Rl using execle system call\n");
  execle("/bin/ls","/bin/ls","-Rl",NULL,NULL); // this also allows user to specify environment of the program using envp argument
}
