#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
// run as cc -o cli 34a_client.c
// then   cc -o serv 34a_server.c
// then ./serv
// then ./cli in a new terminal
void main(){
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
        char data[20];
        read(sfd,data,20);
        printf("Data received from server is : %s\n",data);
        write(sfd,"Hello from Client",18);
      }
      close(sfd);
    }
}
