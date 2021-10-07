#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

void main(){
  struct rlimit resLim;
  int status1 = getrlimit(RLIMIT_CORE,&resLim); // status : 0 --> success , -1 if error
  if(status1==0){
      printf("Current Soft limit on RLIMIT_CORE is %lu bytes\n",resLim.rlim_cur);
      printf("Current Hard limit on RLIMIT_CORE is %lu bytes\n",resLim.rlim_max);

      resLim.rlim_cur = 2048; // set 2048 bytes as the new soft limit
      setrlimit(RLIMIT_CORE,&resLim);

      printf("New Soft limit on RLIMIT_CORE is %lu bytes\n",resLim.rlim_cur);
      printf("New Hard limit on RLIMIT_CORE is %lu bytes\n",resLim.rlim_max);
  }
  else{
    printf("error in getting system resource limits \n");
  }
}
