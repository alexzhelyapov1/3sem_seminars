#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main() {
    const char* path = "~/Desktop/root/infa/3sem_seminars/5_seminar/send_msg.cpp";
    int size_of_mem = 1000;
    umask(0);
    char* mem;
    int key = ftok(path, 0);
    int descriptor = shmget(key, sizeof(char) * size_of_mem, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor > 0) {
        mem = (char*) shmat(descriptor, NULL, 0);
        for (int i = 0; i < size_of_mem; i++) {
            mem[i] = 0;
        }
    }
    else {
        descriptor = shmget(key, sizeof(char) * size_of_mem, 0);
        mem = (char*) shmat(descriptor, NULL, 0);
    }

    char msg[1000];
    strcpy(msg, mem);
    shmdt(mem);
    int result = shmctl(descriptor, IPC_RMID, NULL);
    printf("result of delete memory = %d\n", result);
    printf("Message:\n%s\n", msg);
    return 0;
}



// ----------------------------------------------------------------------------
// Theory, using functions:
// ftok();
// shmget(); 
// shmat();
// shmdt();
// shmctl();