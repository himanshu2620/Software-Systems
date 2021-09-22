#include<stdio.h>
extern char **environ;

int checkUser(char* temp){
  if(temp[0]=='U' && temp[1]=='S' && temp[4]=='=' ){
    return 1;
  }
  else{
    return 0;
  }
}

void main() {
   int cnt=0;
   while(1){
     if(environ[cnt]){
          if(checkUser(environ[cnt])){
            printf("%s\n", environ[cnt]);
          }
          cnt++;
     }
     else{
       break;
     }
   }
}
