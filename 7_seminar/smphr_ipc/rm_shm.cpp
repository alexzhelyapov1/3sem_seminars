#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "smphr.h"

extern const char* path_sem;


int main() {
    const char* path = path_sem;
    umask(0);
    int key = ftok(path, 0);
    int descriptor = semget(key, size_of_bufer, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor < 0) {
        printf("Memory exists. Deleting...\n");
        descriptor = semget(key, size_of_bufer, 0666);
        semctl(descriptor, size_of_bufer, IPC_RMID, NULL);
        printf("Deleted successfully!\n");
    }
    else {
        semctl(descriptor, size_of_bufer, IPC_RMID, NULL);
    }
    return 0;
}



// ----------------------------------------------------------------------------
// Theory, using functions:
// ftok();
// shmget();
// shmat();
// shmdt();