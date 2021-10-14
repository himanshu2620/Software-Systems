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
          write(nsd,"Hello from Server",18);
          printf("Data sent to Client from server\n");
          char data[20];
          read(nsd,data,20);
          printf("Data received from Client is : %s\n", data);
        }
        else{
          close(nsd);
        }
      }
      close(sfd);
    }
}
