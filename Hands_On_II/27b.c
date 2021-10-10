#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

void main(){
    key_t key = ftok("temp_23file",10);
    int msgqid = msgget(key, IPC_CREAT | 0744);
    struct msgBuf{
      long mtype;
      char mtext[15];
    } currMsg;
    int msgtype = 1;
    int status = msgrcv(msgqid, &currMsg, sizeof(currMsg),msgtype, IPC_NOWAIT);
    if(status==-1){
      printf("Error in receiving message\n");
      return;
    }
    printf("Received message from the queue is : %s\n", currMsg.mtext);
}
