#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "smphr.h"

extern const char* path_shm;


int main() {
    const char* path = path_shm;
    umask(0);
    int* mem;
    int key = ftok(path, 0);
    int descriptor = shmget(key, sizeof(int) * size_of_bufer, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor < 0) {
        printf("Memory exists. Deleting...\n");
        descriptor = shmget(key, sizeof(int) * size_of_bufer, 0);
        shmctl(descriptor, IPC_RMID, NULL);
        printf("Deleted successfully!\n");
    }
    return 0;
}



// ----------------------------------------------------------------------------
// Theory, using functions:
// ftok();
// shmget();
// shmat();
// shmdt();