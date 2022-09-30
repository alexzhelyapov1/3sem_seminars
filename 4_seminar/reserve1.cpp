// #include "chat.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main () {
    // printf("aksubd\n");
    const char* path1 = "./1.fifo";
    const char* path2 = "./2.fifo";
    // umask(0);
    // mkfifo(path1, 0);
    // mkfifo(path2, 0);
    int fd_wr = open(path2, O_WRONLY);
    int fd_rd = open(path1, O_RDONLY);
    char msg[1000];

    while (true) {
        // printf("hello");    
        char command = '\0';
        if ((scanf ("%c", &command)) > 0){
            printf("Scanned command = %c\n", command);
            if (command == 's') {       //send
                printf("Sending message...\n");
                scanf("%s", msg);
                write(fd_wr, msg, strlen(msg));
            }
            else if (command == 'r') {
                printf("Receiving message:\n");
                int i = 0;
                while ((read(fd_rd, msg + i, 0)) > 1) i++;
                msg[i] = '\0';
                printf("%s", msg);
            }
            else if (command == 'q') break;
            else {
                printf("Command can't be interpretated\n");
                    //    printf("Hi %c\n", command);.\n");
            }

        }
    }

    printf("Hello! Your proc id = %d\n", getpid());
    return 0;
}