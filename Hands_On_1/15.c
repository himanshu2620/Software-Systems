#include<stdio.h>
extern char **environ;

void main() {
   char* curr = *environ;
   int cnt=1;
   while(curr){
     printf("%s\n",curr);
     curr = *(environ+cnt);
     cnt++;
   }
}
