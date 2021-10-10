#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

void main(){
    key_t key = ftok("temp_23file",10);
    int msgqid = msgget(key, IPC_CREAT | 0744);

    struct msqid_ds currMsg;
    currMsg.msg_perm.mode = 0777;
    int status = msgctl(msgqid,IPC_SET,&currMsg);
    if(status==-1){
      printf("Error in changing permissions\n");
      return;
    }
    printf("permissions successfully changed\n");
}
