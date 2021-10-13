#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>

void main(){
  char* srcTicketFile = "ticketFile.txt";
  int fd = open(srcTicketFile, O_CREAT | O_RDWR,S_IRWXU);
  key_t key = ftok("temp_23file",10);
  int id = semget(key,1,0);
  struct sembuf currBuf;
  currBuf.sem_num = 0;
  currBuf.sem_op = -1;
  currBuf.sem_flg = 0;
  int status = semop(id,&currBuf,1);
  if(status==-1){
    printf("Error while entering the Critical section\n");
  }
  else{
    printf("Now in the Critical Section\n");
    FILE *inputFile = fopen(srcTicketFile, "r+"); // open file in read and write mode
    int currTicket;
    fread(&currTicket,sizeof(int),1,inputFile);
    printf("Current ticket is : %d\n",currTicket);
    currTicket = currTicket + 1 ; // increment the current ticket by 1
    printf("New ticket is : %d\n",currTicket);
    fseek(inputFile,0,0);
    fwrite(&currTicket,sizeof(int),1,inputFile);
    fclose(inputFile);
    currBuf.sem_op = 1;
    semop(id,&currBuf,1);
    printf("Now leaving the Critical Section\n");
    close(fd);
  }
}
