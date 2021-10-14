#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

void main(){
  key_t key = ftok("temp_23file",10);
  int shmId = shmget(key,256,IPC_CREAT | 0744);

  key_t semKey = ftok("temp_23file",11);
  int semId = semget(semKey,1,0);
  struct sembuf currBuf;
  currBuf.sem_num = 0;
  currBuf.sem_op = -1;
  currBuf.sem_flg = 0;
  int status = semop(semId,&currBuf,1);
  if(status==-1){
    printf("Error while entering the Critical section\n");
  }
  else{
    printf("Now entering Critical section\n");
    char* data = shmat(shmId,(void *)0,0);
    printf("Enter some data to write to shared memory:\n");
    scanf(" %[^\n]", data);
    printf("Shared memory contents are : %s\n",data);
    currBuf.sem_op = 1;
    semop(semId,&currBuf,1);
    printf("Now leaving the Critical Section\n");
  }
}
