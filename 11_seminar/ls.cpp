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

#define test_print(...) printf(__VA_ARGS__)

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

    DIR* dir = opendir(path);
    if (!dir) printf("Error! Can't open dir\n");

    struct dirent* temp = readdir(dir);
    while (temp) {
        printf("%s\n", temp->d_name);
        temp = readdir(dir);
    }
    return 0;
}