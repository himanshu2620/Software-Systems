#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

unsigned long long rdtsc(){
  unsigned long long res;
  __asm__ __volatile__ ("rdtsc" : "=A"(res));
  return res;
}

void main(){
  long long int start,end;
  start = rdtsc();
  printf("Starting executing 100 getpid system calls now....\n");
  for(int i=1;i<=100;i++){
    getpid();
  }
  printf("Finishing now....\n");
  end = rdtsc();
  float res = (end-start)/2.4;
  printf("Time taken to execute 100 getpid() system call is %f nano seconds\n", res);
}
