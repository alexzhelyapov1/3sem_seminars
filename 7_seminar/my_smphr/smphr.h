#ifndef SMPHR_H
#define SMPHR_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>

const int size_of_bufer = 1;
// extern S;

int* open_shm(const char* path);
void close_shm(int* mem);
void probieren(int* S);
void verhogen(int* S);

#endif