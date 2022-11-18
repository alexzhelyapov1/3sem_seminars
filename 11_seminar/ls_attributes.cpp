// ---------------------------------------------------------------------------------------------------------------------
// opendir()
// readdir()
// rewinddir() - возвращает указатель каретки в начало
// closedir()
//
// Task:
// 1) ls of current folder
// 2) ls -l (with attributes)
// 3) ls recursive
// ---------------------------------------------------------------------------------------------------------------------

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define test_print(...) printf(__VA_ARGS__)

void print_info(struct dirent* temp);

int main(int argc, char* argv[]) {

    // Make path to dir
    // ------------------------------------------------------------------------

    char path[1000] = {};
    if (argc < 2)
        strcpy(path, "./");
    else 
        strcpy(path, argv[1]);

    test_print("Path = \"%s\"\n", path);

    // ------------------------------------------------------------------------


    // Open dir
    // ------------------------------------------------------------------------

    DIR* dir = opendir(path);
    if (!dir) printf("Error! Can't open dir\n");

    // ------------------------------------------------------------------------


    // Look for files in dir
    // ------------------------------------------------------------------------

    struct dirent* temp = readdir(dir);
    while (temp) {
        print_info(temp);
        temp = readdir(dir);
    }

    // ------------------------------------------------------------------------
    return 0;
}


// Functions
// ------------------------------------------------------------------------------------------------------------------------------------------------

void print_info(struct dirent* temp) {

    struct stat my_struct = {};
    stat(temp->d_name, &my_struct);
         
    printf("Mode = %X ", my_struct.st_mode);                   
    printf("UID = %d ", my_struct.st_uid);           
    printf("GID = %d ", my_struct.st_gid);                    
    printf("size = %5lld ", my_struct.st_size);            
    // printf("LET = %d ", my_struct.st_mtimespec);     
    printf("%s ", temp->d_name);
    printf("\n");
}