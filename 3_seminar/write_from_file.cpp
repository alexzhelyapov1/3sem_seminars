#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main () {
    char data[] = "Hello world!\nThis is my file!\n";
    char file_name[] = "input.txt";

    umask (0);
    int descriptor = open (file_name, O_WRONLY | O_CREAT, 0777);
    write (descriptor, data, strlen (data) + 1);
    printf ("Writen information: \n%sLength of message = %d\n", data, strlen (data) + 1);
    close (descriptor);
    return 0;
}