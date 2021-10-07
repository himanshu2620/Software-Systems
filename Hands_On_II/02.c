#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

void main(){
  struct rlimit resLim;
  int status = getrlimit(RLIMIT_CPU,&resLim); // status : 0 --> success , -1 if error
  // RLIMIT_CPU is a limit, in seconds, on the amount of CPU time that the process can consume
  if(status==0){
      printf("Soft limit on the amount of Cpu time that the process can consume is %lu seconds\n",resLim.rlim_cur);
      printf("Hard limit on the amount of Cpu time that the process can consume is %lu seconds\n",resLim.rlim_max);
  }
  else{
    printf("error in getting system resource limits \n");
  }
}
