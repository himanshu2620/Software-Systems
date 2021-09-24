#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/* execute as ./a.out choice
  ex : ./a.out 2
  choice : 1 --> Lock Record one
           2 --> Lock Record two
           3 --> Lock Record three
*/

void main(int argc, char const *argv[]){
  if(argc==2){
  char *records[] = {"First Record\n","Second Record\n","Third Record\n"};
  int fd = open("file1.txt",O_CREAT |O_RDWR , S_IRWXU);
  if(fd!=-1){
    printf("Creating three records\n");
    int i;
    for(i=0;i<3;i++){
      int recordLen = strlen(records[i]);
      write(fd, records[i],recordLen);
    }

    int pref[4];
    pref[0] = 0;
    for(int i=1;i<=3;i++){
        pref[i] = pref[i-1] + strlen(records[i-1]);
    }
    int ch = (int)*argv[1]-'0';
    int bytesToLock = pref[ch]-pref[ch-1];
    struct flock curr;
    curr.l_type = F_WRLCK;
    curr.l_whence = SEEK_SET;
    curr.l_start = pref[ch-1];
    curr.l_len = bytesToLock; // 0 is to lock all bytes
    curr.l_pid = getpid();
    fcntl(fd,F_SETLK,&curr);

    int status = fcntl(fd,F_SETLKW,&curr);
    if(status!=-1){
      printf("Now accessing record # %d\n",ch);
      curr.l_type = F_UNLCK;
      fcntl(fd,F_SETLK,&curr);
      close(fd);
    }
    else{
      printf("Error in locking\n");
    }
  }
  else{
    printf("Error in opening the file\n");
  }
  }
  else{
    printf("Enter correct arguments\n");
  }
}
