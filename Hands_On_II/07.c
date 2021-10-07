#include <pthread.h>
#include <stdio.h>

void *printFun(void* arg){
  printf("Current thread Id is %lu\n",pthread_self());
}

void main(){
  pthread_t myThread1;
  pthread_t myThread2;
  pthread_t myThread3;
  pthread_create(&myThread1 , NULL , printFun, NULL);
  pthread_create(&myThread2 , NULL , printFun, NULL);
  pthread_create(&myThread3 , NULL , printFun, NULL);
  pthread_exit(NULL);
}
