#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){
  char* srcTicketFile = "ticketFile.txt";
  int fd = open(srcTicketFile, O_CREAT | O_RDWR,S_IRWXU);
  if(fd!=-1){
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0; // lock offset
    lock.l_len = 0; // lock all bytes
    lock.l_pid = getpid();
    int status = fcntl(fd,F_GETLK,&lock); // get the current lock status of the file
    if(status!=-1){
          // set write lock on the source ticket file
          fcntl(fd,F_SETLKW,&lock);
          FILE *inputFile = fopen(srcTicketFile, "r+"); // open file in read and write mode
          int currTicket;
          fread(&currTicket,sizeof(int),1,inputFile);
          printf("Current ticket is : %d\n",currTicket);
          currTicket = currTicket + 1 ; // increment the current ticket by 1
          printf("New ticket is : %d\n",currTicket);
          fseek(inputFile,0,0);
          fwrite(&currTicket,sizeof(int),1,inputFile);
          fclose(inputFile);
          close(fd);
    }
    else{
      printf("Error in getting the locks on the source ticket file\n");
    }
  }
  else{
    printf("Error in opening the source ticket file\n");
  }
}
