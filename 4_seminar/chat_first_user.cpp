// ####################################################################################################################
// # Okay, just look at this! I parsed the fork_fifo.cpp into two files (first and second user) and it doesn't work.    #
// # At the same time, fork_fifo.cpp is work successfully.                                                            #
// # I tryed really hard, even ask for your help. So, I'll realise chat in shared memory. Fifo is too bad.            #
// ####################################################################################################################

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd, result;
    size_t size;
    char resstring[14]; 
    char name[] = "aaa.fifo";

    (void)umask(0); 
    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
	    printf("Can\'t create FIFO\n");
	    return(-1); 
    } 

    if ((fd = open(name, O_WRONLY)) < 0) {
            printf("Can\'t open FIFO for writting\n");
            return(-1); 
    }
    size = write(fd, "Hello, world!", 14);

    // ERROR. This text should be printed, but it does not!
    // ----------------------------------------------------
    printf("The text is written\n");
    // ----------------------------------------------------
    if (size != 14) {
        printf("Can\'t write all string to FIFO\n"); 
        return(-1); 
    } 
    // while(1);
    close(fd);

    return 0;
}