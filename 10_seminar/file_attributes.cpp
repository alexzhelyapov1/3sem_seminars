// ---------------------------------------------------------------------------------------------------------------------
// We need to out all stat information of file
// ---------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) printf("Error, please enter filename as parametr!\n");

    struct stat my_struct = {};
    stat(argv[1], &my_struct);

    printf("------------------File information-----------------------\n");
    printf("Name = %s\n", argv[1]);
    printf("ID of device containing file    = %d\n", my_struct.st_dev);           
    printf("Mode of file (see below)        = %d\n", my_struct.st_mode);          
    printf("Number of hard links            = %d\n", my_struct.st_nlink);         
    printf("File serial number              = %llu\n", my_struct.st_ino);           
    printf("User ID of the file             = %d\n", my_struct.st_uid);           
    printf("Group ID of the file            = %d\n", my_struct.st_gid);           
    printf("Device ID                       = %d\n", my_struct.st_rdev);          
    printf("file size, in bytes             = %lld\n", my_struct.st_size);          
    printf("blocks allocated for file       = %lld\n", my_struct.st_blocks);        
    printf("optimal blocksize for I/O       = %d\n", my_struct.st_blksize);       
    printf("user defined flags for file     = %d\n", my_struct.st_flags);         
    printf("file generation number          = %d\n", my_struct.st_gen);           
    printf("time of last access             = %d\n", my_struct.st_atimespec);     
    printf("time of last data modification  = %d\n", my_struct.st_mtimespec);     
    printf("time of last status change      = %d\n", my_struct.st_ctimespec);     
    printf("time of file creation(birth)    = %d\n", my_struct.st_birthtimespec); 

    return 0;
}