#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>

void *my_func(void *arg) {
    printf("I am new thread = %ld\n", pthread_self());
    sleep(1);
    return NULL;
}


int main() {
    const char* path = "~/Desktop/root/infa/3sem_seminars/6_seminar/1_shared_memory.cpp";
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
    mem[4] += 1;
    mem[5] += 1;

    printf("I am first thread = %ld\n", pthread_self());
    pthread_t thread[10];
    for (int i = 0; i < 5; i++) {
        if (pthread_create(thread + i, NULL, my_func, NULL)) {
            printf("Error! Thread did not create\n");
        }
        else {
            mem[4]++;
            mem[5]++;
        }
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(thread[i], NULL);
        printf("Thread %ld synchronized\n", thread[i]);
    }
    
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