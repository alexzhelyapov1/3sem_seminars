#include <stdio.h>
#include <time.h>
#include "smphr.h"

extern const char* path_sem;

int main() {
    long int ttime = time(NULL);
    printf ("Proccess 2 started at %s\n", ctime(&ttime));
    int d_sem = open_sem(path_sem);

    struct sembuf buf = {0, 1, 0};
    semop(d_sem, &buf, 1);

    printf("I am 2 proc, ended at time = %s\n", ctime(&ttime));
    return 0;
}