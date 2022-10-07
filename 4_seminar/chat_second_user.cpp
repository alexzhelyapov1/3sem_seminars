// ####################################################################################################################
// Reading text
// ####################################################################################################################


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd, result;
    size_t size;
    char msg[1000]; 
    char name[] = "aaa.fifo";

    (void)umask(0);
    if ((fd = open(name, O_RDONLY)) < 0) {
            printf("Can\'t open FIFO for reading\n");
            return(-1);
    } 
    while (1) {
        size = read(fd, msg, 1000);
        if (size > 0) {
            msg[size] = '\0';
            printf("%s\n", msg);
        } 
    }
    close(fd);

    return 0;
}