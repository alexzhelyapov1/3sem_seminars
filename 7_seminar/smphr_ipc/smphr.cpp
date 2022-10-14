#include "smphr.h"

const char* path_sem = "~/Desktop/root/infa/3sem_seminars/7_seminar/my_smphr/main.cpp";

int open_sem(const char* path) {    
    umask(0);
    int key = ftok(path_sem, 0);
    int descriptor = semget(key, size_of_bufer, 0666 | IPC_CREAT);

    printf("Returned descriptor = %d\n", descriptor);
    return descriptor;
}