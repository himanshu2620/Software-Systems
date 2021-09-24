#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
void main(){
  char * srcTicketFile = "ticketFile.txt";
  FILE *inputFile = fopen(srcTicketFile, "r+");
  int initialTicket = 1;
  fwrite(&initialTicket,sizeof(int),1,inputFile);
  fclose(inputFile);
}
