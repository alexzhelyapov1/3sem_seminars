#include "chat.h"

void OpenSharedMemory(const char* path, char** mem_ret, int* descriptor_ret) {    
    umask(0);
    char* mem;
    int key = ftok(path, 0);
    int descriptor = shmget(key, sizeof(char) * size_of_bufer, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor > 0) {
        mem = (char*) shmat(descriptor, NULL, 0);
        for (int i = 0; i < size_of_bufer; i++) {
            mem[i] = 0;
        }
    }
    else {
        descriptor = shmget(key, sizeof(char) * size_of_bufer, 0);
        mem = (char*) shmat(descriptor, NULL, 0);
    }
    *mem_ret = mem;
    *descriptor_ret = descriptor;
}