#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

void main(){
    key_t key = ftok("temp_23file",10);
    int msgqid = msgget(key, IPC_CREAT | 0744);
    int status = msgctl(msgqid,IPC_RMID,0);
    if(status==-1){
      printf("Error in removing the message queue\n");
      return;
    }
    printf("Message queue removed successfully\n");
}
