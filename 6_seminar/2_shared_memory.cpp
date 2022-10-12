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
    int descriptor = shmget(key, sizeof(int) * 6, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor > 0) {
        mem = (int*) shmat(descriptor, NULL, 0);
        for (int i = 0; i < 6; i++) {
            mem[i] = 0;
        }
    }
    else {
        descriptor = shmget(key, sizeof(int) * 6, 0);
        mem = (int*) shmat(descriptor, NULL, 0);
    }

    mem[1] += 1;
    mem[2] += 1;
    mem[4]++;
    mem[5]++;
    for (int i = 0; i < 6; i++) {
        printf("%d ", mem[i]);
    }

    shmdt(mem);
    return 0;
}



// ----------------------------------------------------------------------------
// Theory, using functions:
// ftok();
// shmget();
// shmat();
// shmdt();