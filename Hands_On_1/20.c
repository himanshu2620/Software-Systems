#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>

void main(){
    id_t pid = getpid();
    int curr_Priority = getpriority(PRIO_PROCESS,pid);
    printf("Current priority of the process : %d\n", curr_Priority);
    nice(3);
    int new_Priority = getpriority(PRIO_PROCESS,pid);
    printf("New priority of the process : %d \n", new_Priority );
}
