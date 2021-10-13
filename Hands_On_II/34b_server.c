#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/ip.h>
// run as cc -o cli 34b_client.c
// then   cc -o serv 34b_server.c -lpthread
// then ./serv
// then ./cli in a new terminal
void threadHandler(int *nsd){
  int fd = *nsd;
  write(fd,"Hello from Server",18);
  printf("Data sent to Client from server\n");
  char data[20];
  read(fd,data,20);
  printf("Data received from Client is : %s\n", data);
  close(fd);
  return;
}
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
      pthread_t currThread;
      while(1){
        int clientSize =  sizeof(cli);
        int nsd = accept(sfd,(struct sockaddr *) &cli, &clientSize);

        int threadStatus = pthread_create(&currThread,NULL,(void*) threadHandler,&nsd);// 2nd Attribute --> NULL for default Attributes for the thread
        if(threadStatus){
          printf("error while creating the thread using pthread_create\n");
        }

      }
      close(sfd);
    }
}
