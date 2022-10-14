#include <stdio.h>
#include <time.h>
#include "smphr.h"

extern const char* path_sem;

int main() {
    long int ttime = time(NULL);
    printf ("Process 1 started at %s\n", ctime(&ttime));
    int d_sem = open_sem(path_sem);

    ttime = time(NULL);
    printf("I am waiting second programm... Time = %s\n", ctime(&ttime));

    struct sembuf buf = {0, -1, 0};
    semop(d_sem, &buf, 1);

    ttime = time(NULL);
    printf("I waited! Proccess 2 ended. Time = %s\n", ctime(&ttime));
    return 0;
}