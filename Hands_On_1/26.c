#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// compile as gcc 26.c
// run as ./a.out

void main(int argc, char *argv[]) {
  char* srcFile = "temp/a.out"; // this is an executable of a program that prints the arguments supplied to it
  execl(srcFile,srcFile,"there","world",NULL);
}
