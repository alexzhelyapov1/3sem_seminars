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

// #define test_print(...) printf(__VA_ARGS__)
#define test_print(...)  

void print_info(struct dirent* temp);
void ls_one_dir (char* dirname);

int main(int argc, char* argv[]) {

    // Make path for dir
    // ------------------------------------------------------------------------
    char path[1000] = {};
    if (argc < 2) {
        printf("\n*No arguments given*\n\n");
        strcpy(path, ".");
    }
    else 
        strcpy(path, argv[1]);

    test_print("Path = \"%s\"\n", path);
    // ------------------------------------------------------------------------

    ls_one_dir(path);
    
    return 0;
}


// Functions
// ------------------------------------------------------------------------------------------------------------------------------------------------

void ls_one_dir (char* dirname) {
    // Open dir
    // ------------------------------------------------------------------------
    DIR* dir = opendir(dirname);
    if (!dir) printf("Error! Can't open dir\n");
    // ------------------------------------------------------------------------

    // Look for files in dir
    // ------------------------------------------------------------------------
    struct dirent* temp = readdir(dir);
    while (temp) {
        test_print("Cur name = %s\n", temp->d_name);
        if (temp->d_type == 4){

            // Remove recursive infinity
            // ------------------------------------------------------------------------
            if (!strcmp(".", temp->d_name) || !strcmp("..", temp->d_name)) {
                temp = readdir(dir);
                continue;
            }    
            // ------------------------------------------------------------------------

            // Make new path
            // ------------------------------------------------------------------------
            char new_path[1000];
            strcpy(new_path, dirname);
            strcat(new_path, "/");
            strcat(new_path, temp->d_name);
            // ------------------------------------------------------------------------

            printf("\nFolder %s\n", new_path);

            // Recursive descent
            // ------------------------------------------------------------------------
            ls_one_dir(new_path);
            // ------------------------------------------------------------------------
        }
        if (temp->d_type == 8) {
            printf("File   ");
            printf("%s%s%s\n", dirname, "/", temp->d_name);
        }
        temp = readdir(dir);
    }
    printf("\n");
    test_print("End of while!!!!!!!!!!!!!!!!!!!!\n");
    // ------------------------------------------------------------------------
}