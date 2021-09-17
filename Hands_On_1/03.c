#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(){
    char* fileName = "myFile.txt";
    int fd = creat(fileName,S_IRWXU); // mode S_IRWXU provides read, write and execute permissions to the user
    // creat() returns -1 if there's an error in creating the file
    if(fd == -1){
      printf("error in creating the file \n" );
    }
    else{
      printf("File %s was created successfully with fileDescriptor value being %d \n",fileName,fd);
    }
}
