#include <stdio.h>
#include <sched.h>

void main(){
  int min_priority = sched_get_priority_min(SCHED_FIFO);
  int max_priority = sched_get_priority_max(SCHED_FIFO);
  printf("Maximum priority is : %d\n", max_priority);
  printf("Minimum priority is : %d\n", min_priority);
}
