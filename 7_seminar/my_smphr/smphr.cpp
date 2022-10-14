#include "smphr.h"

const char* path_shm = "~/Desktop/root/infa/3sem_seminars/7_seminar/my_smphr/main.cpp";

int* open_shm(const char* path) {    
    umask(0);
    int* mem;
    int key = ftok(path, 0);
    int descriptor = shmget(key, sizeof(int) * size_of_bufer, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor >= 0) {                                                              // New shared memory
        mem = (int*) shmat(descriptor, NULL, 0);
        for (int i = 0; i < size_of_bufer; i++) {
            mem[i] = 0;
        }
    }
    else {                                                                              // If shared memory exists  
        descriptor = shmget(key, sizeof(int) * size_of_bufer, 0);
        mem = (int*) shmat(descriptor, NULL, 0);
    }
    // *mem_ret = mem;
    // *descriptor_ret = descriptor;
    // printf("Returned descryptor = %d, mem = %x\n", descriptor, mem);
    return mem;
}

void close_shm(int* mem) {
    shmdt(mem);
}

void rm_shm() {
    umask(0);
    int key = ftok(path_shm, 0);
    int descriptor = shmget(key, sizeof(int) * size_of_bufer, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor < 0) {
        printf("Memory exists. Deleting...\n");
        descriptor = shmget(key, sizeof(int) * 3, 0);
        shmctl(descriptor, IPC_RMID, NULL);
        printf("Deleted successfully!\n");
    }
}

void probieren(int* S) {
    // printf("Probieren, s_begin = %d\n", S[0]);
    while (S[0] == 0) ;
    S[0]--;
    // printf("Probieren, s_end = %d\n", S[0]);
}

void verhogen(int* S) {
    S[0]++;
    // printf("Verhogen, s_end = %d\n", S[0]);
}