// ####################################################################################################################
// # Okay, just look at this! I parsed the fork_fifo.cpp to two files (first and second user) and it doesn't work.    #
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
    if ((fd = open(name, O_RDONLY)) < 0) {
            printf("Can\'t open FIFO for reading\n");
            return(-1);
    } 
    size = read(fd, resstring, 14);
    if (size < 0) {
        printf("Can\'t read string\n"); 
        return(-1); 
    } 
    printf("%s\n",resstring);
    close(fd);

    return 0;
}