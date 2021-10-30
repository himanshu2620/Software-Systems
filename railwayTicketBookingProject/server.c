#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <time.h>
#include "serverHelper.h"


// run as cc -o cli lient.c
// then   cc -o serv server.c
// then ./serv
// then ./cli in a new terminal
void main(){
    struct sockaddr_in serv;
    struct sockaddr_in cli;
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1){
       printf("Error in creating socket\n");
    }
    else{
      serv.sin_family = AF_INET;
      serv.sin_addr.s_addr = INADDR_ANY;
      serv.sin_port = htons(8089);
      bind(sfd,(struct sockaddr *) &serv,sizeof(serv));
      listen(sfd,5);
      while(1){
        int clientSize =  sizeof(cli);
        int nsd = accept(sfd,(struct sockaddr *) &cli, &clientSize);
        pid_t pid = fork();
        if(pid==0){
          write(nsd,"Welcome to Railway Reservation System\n",39);
          handleInitialLogin(nsd);
          close(nsd);
        }
        else{
          close(nsd);
        }
      }
      close(sfd);
    }
}
