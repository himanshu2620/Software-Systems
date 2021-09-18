#include<stdio.h>
#include<time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// compile as gcc 09.c
// run the program as ./a.out srcfile

void main(int argc, char *argv[]) {
    if(argc==2){
        char* srcFile = argv[1];
        struct stat sb;
        int status = stat(srcFile,&sb);
        if(status!=-1){
          printf("inode for source file is %ld \n", (long)sb.st_ino);
          printf("number of hardlinks for source file is %ld \n", (long)sb.st_nlink);
          printf("uid is %d \n", sb.st_uid);
          printf("gid is %d \n", sb.st_gid);
          printf("size of file is %ld \n", (long)sb.st_size);
          printf("block size is %ld \n", (long)sb.st_blksize);
          printf("number of blocks are %ld\n", (long)sb.st_blocks);
          printf("time of last access: %s", ctime(&sb.st_atime));
          printf("time of last modification: %s", ctime(&sb.st_mtime));
          printf("time of last change: %s", ctime(&sb.st_ctime));
        }
        else{
          printf("error occured while executing the source file\n");
        }
    }
    else{
      printf("specify correct arguments\n");
    }

}
