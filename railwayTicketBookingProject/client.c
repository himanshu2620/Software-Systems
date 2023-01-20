#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include "clientHelper.h"
// run as cc -o cli client.c
// then   cc -o serv server.c
// then ./serv
// then ./cli in a new terminal
void main(){
    int temp1, temp;
    struct sockaddr_in serv;
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1){
       printf("Error in creating socket\n");
    }
    else{
      serv.sin_family = AF_INET;
      serv.sin_addr.s_addr = INADDR_ANY;
      serv.sin_port = htons(8089);
      int status = connect(sfd,(struct sockaddr *)  &serv,sizeof(serv));
      if(status==-1){
        printf("Couldn't connect to server\n");
      }
      else{
        sleep(0.01);
        char data[500];
        read(sfd,data,sizeof(data)); // Welcome message
        printf("%s",data);

        handleMainMenu(sfd);


      }
      close(sfd);
    }
}
