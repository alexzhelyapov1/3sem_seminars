#include <stdio.h>
#include <time.h>
#include "smphr.h"

extern const char* path_shm;

int main() {
    long int ttime = time(NULL);
    printf ("Proccess 2 started at %s\n", ctime(&ttime));
    int* S = open_shm(path_shm);

    verhogen(S);

    printf("I am 2 proc, ended at time = %s\n", ctime(&ttime));
    
    close_shm(S);
    return 0;
}