#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main () {
    char data[1000];
    char file_name[] = "input.txt";

    int descriptor = open (file_name, O_RDONLY);
    printf ("Number of readed elemenst = %d\n", read (descriptor, data, 31));
    close (descriptor);
    printf ("%s", data);
    return 0;
}