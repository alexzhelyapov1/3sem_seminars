#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main () {
    printf ("Hello world!\n");
    const char* path = "./1.fifo";
    mkfifo(path, 0777);

    int descriptor = open (path, O_WRONLY | O_CREAT, 0777);
    close (descriptor);

    if (fork()) {
        printf("First proccess started!\n");
        const char* data[] = "Hello, do you see this message?\n";
        int fd = open(path, O_WRONLY | O_CREAT, 0777);
        write (descriptor, data, strlen (data) + 1);
        close(fd);
    } 
    else {
        printf("Second proccess started!\n");
        int fd = open(path, O_RDONLY);
        char buffer[] = "1";
        char data[1000];

        read(fd, buffer, 1);
        while (buffer[0]) {
            
        }
        printf("Readed message: \"%s\"\n", buffer);
    }
    return 0;
}