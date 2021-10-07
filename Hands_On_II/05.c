#include <unistd.h>
#include <stdio.h>
// use man sysconf
void main(){
    printf("Maximum length of the arguments to the exec family of functions is %ld \n", sysconf(_SC_ARG_MAX));
    printf("Maximum number of simultaneous process per user id is %ld \n", sysconf(_SC_CHILD_MAX));
    printf("Number of clock ticks (jiffy) per second is %ld \n", sysconf(_SC_CLK_TCK));
    printf("Maximum number of open files are %ld \n", sysconf(_SC_OPEN_MAX));
    printf("Size of a page is %ld \n", sysconf(_SC_PAGESIZE));
    printf("Total number of pages in the physical memory are %ld \n", sysconf(_SC_PHYS_PAGES));
    printf("Number of currently available pages in the physical memory are %ld \n", sysconf(_SC_AVPHYS_PAGES));
}
