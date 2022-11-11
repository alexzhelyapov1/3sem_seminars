// ---------------------------------------------------------------------------------------------------------------------
// link - make new hard link (ln - system call)
// symlink - soft link (ln -s)
// unlink - remove link (only soft)
// ---------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 2) printf("Error, please enter filename as parametr!\n");
    printf("Name of file = %s\n", argv[1]);

    char s[100];

    strcpy(s, argv[1]);
    strcat(s, ".hlink");
    printf("Hard link name = %s\n", s);
    link(argv[1], s);

    strcpy(s, argv[1]);
    strcat(s, ".slink");
    printf("Soft link name = %s\n", s);
    symlink(argv[1], s);
    return 0;
}