#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>

void main(){
  pid_t pid = getpid();
  int currSchedPolicy = sched_getscheduler(pid);
  struct sched_param priority;
  priority.sched_priority = 1;
  /*
    policy :
      SCHED_OTHER = 0
      SCHED_FIFO = 1
      SCHED_RR = 2
  */
  if(currSchedPolicy==0 || currSchedPolicy==1){ // if current policy is SCHED_OTHER or SCHED_FIFO change it to SCHED_RR
    printf("Current policy is: %d \n", currSchedPolicy);
    sched_setscheduler(pid,2,&priority);
    int changedPolicy  = sched_getscheduler(pid);
    printf("New policy is: %d \n", changedPolicy);
  }

  else if(currSchedPolicy==2){ // if current policy is SCHED_RR change it to SCHED_FIFO
    printf("Current policy is: %d \n", currSchedPolicy);
    sched_setscheduler(pid,1,&priority);
    int changedPolicy  = sched_getscheduler(pid);
    printf("New policy is: %d \n", changedPolicy);

  }
  else{
    printf("error\n");
  }
}
