#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd, result;
    size_t size;
    char resstring[14]; 
    char name[]="aaa.fifo";

    (void)umask(0); 

    if(mknod(name, S_IFIFO | 0666, 0) < 0)
    {
	printf("Can\'t create FIFO\n");
	return(-1); 
    } 

    if((result = fork()) < 0)
    { 
	printf("Can\'t fork child\n");
	return(-1);
    }
    else if (result > 0) 
    {
	if((fd = open(name, O_WRONLY)) < 0)
	{
	    printf("Can\'t open FIFO for writting\n");
	    return(-1); 
	} 
	
	size = write(fd, "Hello, world!", 14);

	if(size != 14)
	{
	    printf("Can\'t write all string to FIFO\n"); 
	    return(-1); 
	} 

	close(fd);
	printf("Parent exit\n");

    } 
    else 
    {
        if((fd = open(name, O_RDONLY)) < 0)
	{
	    printf("Can\'t open FIFO for reading\n");
	    return(-1);
	} 

	size = read(fd, resstring, 14);

	if(size < 0)
	{
	    printf("Can\'t read string\n"); 
	    return(-1); 
	} 

	printf("%s\n",resstring);

	close(fd);

    }

    return 0;
}


// My chat 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main () {
    char path[] = "./1.fifo";
    umask(0);   
    mknod(path, S_IFIFO | 0777, 0);
    int fd_wr = open(path, O_WRONLY, 0777);
    printf("open descriptor = %d\n", fd_wr);
    char msg[1000];

    while (true) {
        printf("hello\n");    
        scanf("%s", msg);
        write(fd_wr, msg, strlen(msg));
    }

    printf("Hello! Your proc id = %d\n", getpid());
    close(fd_wr);
    return 0;
}


// Если другая прога узнает дескр пайпа сможет меняться?
// как закрыть фифо
