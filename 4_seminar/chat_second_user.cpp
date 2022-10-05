#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main () {
    const char* path2 = "./1.fifo";
    umask(0);
    // printf("%d", mkfifo(path2, 0777));
    int fd_rd = open(path2, O_RDONLY | 0777);
    char msg[1000];
    printf("Started\n");
    int i = 1;
    while (i--) {

        int i = 0;
        int res = 0;
        res = read(fd_rd, msg, 5);
        printf("Res of reading number = %d, fd_rf = %d\n", res, fd_rd);
        msg[6] = '\0';
        // while ((read(fd_rd, msg + i, 1)) > 1) {
        //     printf("Try to read from file\n");
        //     printf("%c", msg[i]);
        //     i++;
        // }
        // msg[i] = '\0';
        printf("%s", msg);
    }

    printf("Hello! Your proc id = %d\n", getpid());
    return 0;
}