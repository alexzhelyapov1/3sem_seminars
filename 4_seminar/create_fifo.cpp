#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    (void)umask(0); 
    if (mknod("aaa.fifo", S_IFIFO | 0666, 0) < 0) {
	    printf("Can\'t create FIFO\n");
	    return(-1); 
    } 
    printf("Fifo created successfully!\n");
    return 0;
}