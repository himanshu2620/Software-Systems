#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void main(){
    key_t key = ftok("temp_23file",10);
    int msgqid = msgget(key, IPC_CREAT | 0744);
    struct msqid_ds currMsg;
    msgctl(msgqid,IPC_STAT, &currMsg);
    printf("Access Permission info : %u\n", currMsg.msg_perm.mode);
    printf("UID is %d and GID is %d\n", currMsg.msg_perm.uid , currMsg.msg_perm.gid);
    printf("time of last message sent is: %ld and time of last message received is: %ld", currMsg.msg_stime, currMsg.msg_rtime);
    printf("time of last change in the message queue is: %ld \n", currMsg.msg_ctime);
    printf("current size of the message queue is: %lu\n", currMsg.__msg_cbytes);
    printf("number of messages in the queue is: %ld\n", currMsg.msg_qnum);
    printf("maximum number of bytes allowed are: %ld\n", currMsg.msg_qbytes);
    printf("pid of msgsnd (last message sent) is : %d and pid of msgrcv(last message received) is: %d\n", currMsg.msg_lspid, currMsg.msg_lrpid);
}
