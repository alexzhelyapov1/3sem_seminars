#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
    const char* path = "~/Desktop/root/infa/3sem_seminars/5_seminar/1_shared_memory.cpp";
    umask(0);
    int* mem;
    int key = ftok(path, 0);
    int descriptor = shmget(key, sizeof(int) * 3, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor < 0) {
        printf("Memory exists\n");
        descriptor = shmget(key, sizeof(int) * 3, 0);
        mem = (int*) shmat(descriptor, NULL, 0);
        shmctl(descriptor, IPC_RMID, NULL);
        shmdt(mem);
    }
    return 0;
}



// ----------------------------------------------------------------------------
// Theory, using functions:
// ftok();
// shmget();
// shmat();
// shmdt();