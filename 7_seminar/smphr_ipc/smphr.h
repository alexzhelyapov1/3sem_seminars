#ifndef SMPHR_H
#define SMPHR_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>


const int size_of_bufer = 1;
// extern S;

int open_sem(const char* path);

#endif