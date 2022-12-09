#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Open file
    int fd = open("1.txt", O_RDWR, 0777);
    if (fd < 0) {printf("Error! Can't open file!\n"); return 1;}

    // Get len of file
    int len = lseek(fd, 0, SEEK_END);
    //lseek(fd, 0, 0);
    printf("Len of file is %d\n", len);

    // Map file
    void* display_memory = NULL;
    display_memory = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (display_memory == MAP_FAILED) {printf("Can't map the file!\n"); return 1;}

    // Add msg to display memory
    char new_msg[] = "\n\nNew part of msg!";
    memcpy((void*)((char*)display_memory + len - strlen(new_msg)), (const void*)new_msg, strlen(new_msg));

    // Sync and close
    munmap(display_memory, len);
    close(fd);

    // Check file

    char* args[] = {{(char*)"cat"}, {(char*)"1.txt"}, NULL};
    execvp("cat", args);

    return 0;
}