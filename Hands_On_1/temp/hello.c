#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]){
      int i;
      for(i=0;i<argc;i++){
         printf("Hello %s\n",argv[i]);
      }
}
