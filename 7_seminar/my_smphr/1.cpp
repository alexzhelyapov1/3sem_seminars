#include <stdio.h>
#include <time.h>
#include "smphr.h"

extern const char* path_shm;

int main() {
    long int ttime = time(NULL);
    printf ("Process 1 started at %s\n", ctime(&ttime));
    int* S = open_shm(path_shm);
    S[0] = 0;

    ttime = time(NULL);
    printf("I am waiting second programm... Time = %s\n", ctime(&ttime));

    probieren(S);

    ttime = time(NULL);
    printf("I waited! Proccess 2 ended. Time = %s\n", ctime(&ttime));
    
    close_shm(S);
    return 0;
}