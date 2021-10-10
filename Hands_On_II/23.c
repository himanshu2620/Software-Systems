#include <stdio.h>
#include <unistd.h>

void main(){
  printf("the maximum number of files that can be opened within a process is : %ld\n",sysconf(_SC_OPEN_MAX));
  printf("Size of the pipe is : %ld \n", pathconf(".",_PC_PIPE_BUF));
}
