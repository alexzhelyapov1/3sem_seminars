#ifndef CHAT_H
#define CHAT_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

const int size_of_bufer = 2000;


void OpenSharedMemory(const char* path, char** mem_ret, int* descriptor_ret);



#endif