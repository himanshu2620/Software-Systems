#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main(){
  union semun{
    int val;
    struct semid_ds *buff;
    unsigned short int *arr;
  };
  union semun arg;
  key_t key = ftok("temp_23file",11);
  int semID = semget(key,1,IPC_CREAT | 0744);
  arg.val = 3;
  int status = semctl(semID,0,SETVAL,arg);
  if(status==-1){
    printf("Error while creating semaphore\n");
  }
  else{
    printf("Counting Semaphore created successfully\n");
  }
}
