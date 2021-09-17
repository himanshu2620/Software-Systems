#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
  compile using gcc 05.c
  run as ---> ./a.out &
  so as to run this program in the background   
*/

void main(){
    char path[50];
    int cnt = 1;
    while(1){
        if(cnt<6){
          sprintf(path,"/home/himanshu/Desktop/SS_Hands_On_1/tempFile%d",cnt);
          cnt++;
          int fd = creat(path,00744);
          if(fd == -1){
              printf("error in creating the file \n" );
          }
          else{
              printf("File at path %s was created successfully with fileDescriptor value being %d \n",path,fd);
          }
        }
    }
}
