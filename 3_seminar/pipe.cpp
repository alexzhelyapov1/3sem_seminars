#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main () {
    int pipefd[2];
    char data[1000];
    
    pipe(pipefd);
    int id = fork();
    if (id == 0) {
        for (int i = 0; i < 100; i++) {
        read (pipefd[0], data, 19);
        printf ("Readed info from pipe: \"%s\"\n\n", data);
        }
    }
    else if (id > 0) {
        for (int i = 10; i < 100; i++) {
            strcpy (data, "New line number");
            sprintf (data + strlen(data), " %d\0", i);
            write (pipefd[1], data, strlen (data) + 1);
            printf ("WRITEN info to pipe: \"%s\"\n", data);
        }
    }
    else {
        printf ("Could not to fork new proccess\n");
    }
    return 0;
}