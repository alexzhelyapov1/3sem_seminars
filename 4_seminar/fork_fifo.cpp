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

    if ((result = fork()) < 0) { 
	    printf("Can\'t fork child\n");
	    return(-1);
    }
    // Parent part
    // ----------------------------------------------------------------------------------------------------------------
    else if (result > 0) {
        if ((fd = open(name, O_WRONLY)) < 0) {
            printf("Can\'t open FIFO for writting\n");
            return(-1); 
        }
        size = write(fd, "Hello, world!", 14);
        if (size != 14) {
            printf("Can\'t write all string to FIFO\n"); 
            return(-1); 
        } 
        close(fd);
        printf("Parent exit\n");
    } 
    // ----------------------------------------------------------------------------------------------------------------
    // Child part
    // ----------------------------------------------------------------------------------------------------------------
    else {
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
    }
    // ----------------------------------------------------------------------------------------------------------------

    return 0;
}