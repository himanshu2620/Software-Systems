#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

void main(){
  key_t key = ftok("temp_23file",10);
  int shmid = shmget(key,256,IPC_CREAT | 0744);
  if(shmid==-1){
    printf("Error in creating shared memory\n");
  }
  else{
    char* data = shmat(shmid,(void *)0,0);
    printf("Enter some data to write to shared memory:\n");
    scanf(" %[^\n]", data);
    printf("Shared memory contents are : %s\n",data);
    char* data1 = shmat(shmid,(void *)0,SHM_RDONLY);
    printf("Shared memory contents are : %s\n",data1);

    printf("Now detaching shared memory segment\n");
    shmdt(data1);

    printf("Now removing shared memory\n");
    shmctl(shmid,IPC_RMID,NULL);
  }
}
