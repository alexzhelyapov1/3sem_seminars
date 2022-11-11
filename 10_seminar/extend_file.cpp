// ---------------------------------------------------------------------------------------------------------------------
// ftruncate
// lseek
// ---------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 2) printf("Error, please enter filename as parametr!\n");
    struct stat my_struct = {};
    stat(argv[1], &my_struct);
    printf("Start len of file = %lld\n", my_struct.st_size);

    int fd = 0;
    if ((fd = open(argv[1], O_WRONLY)) < 0) printf("Error in opening file\n");
    int add_size = 20;
    ftruncate(fd, my_struct.st_size + add_size);    // Make file wider for add_size
    lseek(fd, my_struct.st_size, SEEK_SET);         // Move to old end
    char msg[] = "This is msg"; 
    write(fd, msg, strlen(msg));                    // Print msg to the end

    stat(argv[1], &my_struct);
    printf("End len of file = %lld\n", my_struct.st_size);
    return 0;
}