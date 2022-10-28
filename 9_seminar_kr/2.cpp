// This programm prints env to file env.txt

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv, char **envp) {

    // Open file for writing
    //------------------------------------------------------------------------------------------------------------------

    // umask(0);
    int fd = open("env.txt", O_WRONLY | O_CREAT, 0777);
    if (fd < 0) printf("Error to open writing file\n");
    printf("fd = %d\n", fd);

    //------------------------------------------------------------------------------------------------------------------


    // Envp - array of ptrs to strings
    // Env - ptr to string
    //------------------------------------------------------------------------------------------------------------------

    for (char **env = envp; *env != 0; env++) {
        const void *thisEnv = *env;

        write(fd, thisEnv, strlen(*env));
        write(fd, "\n", 1);
    }

    //------------------------------------------------------------------------------------------------------------------

    return 0;
}