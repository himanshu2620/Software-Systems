#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void main(){
  pid_t pid = fork();
  if(pid==0){
    printf("Current process id is : %d\n", getpid());
    setsid();
    chdir("/");
    umask(0);
    struct tm executionTime; // time at which to execute the script
    executionTime.tm_hour = 20;
    executionTime.tm_min = 10;
    while(1){
      // get the current time
      struct tm *currTime;
      time_t ctime;
      time(&ctime);
      currTime = localtime(&ctime);
      if(executionTime.tm_hour==currTime->tm_hour && executionTime.tm_min==currTime->tm_min ){
        printf("Start executing the script now\n");
        exit(0);
      }
    }
  }
  else{
    exit(0);
  }
}
