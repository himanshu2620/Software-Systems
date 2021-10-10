#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void main(){
    key_t key = ftok("temp_23file",10);
    int msgqid = msgget(key, IPC_CREAT | 0744);
    printf("key is : %d\n", key);
    printf("Message queue id is : %d\n", msgqid);
}
