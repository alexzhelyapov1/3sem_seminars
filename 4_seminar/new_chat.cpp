#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    int fd, result;
    size_t size;
    char resstring[14]; 
    char name[]="./aaa.fifo";

    (void)umask(0); 
    result = mknod(name, S_IFIFO | 0666, 0);
    printf("result of mknod = %d, errno = %d\n", result, errno);
    fd = open(name, O_WRONLY | 0666);
    printf("result of open = %d\n", fd);
    printf("YESSSS\n");

    close(fd);
    return 0;
}