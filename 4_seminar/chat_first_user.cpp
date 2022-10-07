// ####################################################################################################################
// Writing message
// ####################################################################################################################

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd, result;
    size_t size;
    char msg[1000]; 
    char name[] = "aaa.fifo";

    if ((fd = open(name, O_WRONLY)) < 0) {
        printf("Can\'t open FIFO for writting\n");
        return(-1); 
    }

    while (1) {
        scanf("%s", msg);
        write(fd, msg, strlen(msg));
        write(fd, " ", 1);
        printf("The text is written: %s\n", msg);
    }
    close(fd);

    return 0;
}