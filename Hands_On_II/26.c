#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
// check using ipcs -q
void main(){
    key_t key = ftok("temp_23file",10);
    int msgqid = msgget(key, IPC_CREAT | 0744);
    struct msgBuf{
      long mtype;
      char mtext[15];
    } currMsg;
    currMsg.mtype = 1;
    strncpy(currMsg.mtext,"HelloWorld\n",15);
    int status = msgsnd(msgqid, &currMsg, sizeof(currMsg),0);
    if(status == -1){
      printf("Error in sending messages to the message queue\n");
      return;
    }
    printf("Message successfully sent\n");
}
