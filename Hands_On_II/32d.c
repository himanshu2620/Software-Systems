#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>

void main(){
  key_t key = ftok("temp_23file",10);
  int id = semget(key,1,IPC_CREAT | 0744);
  int status = semctl(id,0,IPC_RMID);
  if(status==0){
    printf("Successfully removed the semaphore\n");
  }
  else{
    printf("Error\n");
  }
}
