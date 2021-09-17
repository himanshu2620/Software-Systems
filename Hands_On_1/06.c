#include<stdio.h>
#include<unistd.h>

void main(){
  char buff[50]="";
  printf("Enter your message\n");
  read(0,buff,50);
  printf("you entered: \n");
  write(1,buff,50);
}
