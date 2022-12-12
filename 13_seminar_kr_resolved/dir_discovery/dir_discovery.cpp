#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//#define test_print(...) printf(__VA_ARGS__)
#define test_print(...)  

void ls_one_dir_recursive (char* dirname);
void ls_one_dir (char* dirname);
bool have_hlinks(char* filename);

int number_of_files = 0;
int number_of_files_with_links = 0;

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

    ls_one_dir_recursive(path);
    printf("Totally number of files = %d\n", number_of_files);
    printf("Files with more than 1 hardlinks = %d\n", number_of_files_with_links);

    ls_one_dir(path);
    
    return 0;
}


// Functions
// ------------------------------------------------------------------------------------------------------------------------------------------------

void ls_one_dir_recursive (char* dirname) {
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
        if (temp->d_type == 4){     // If is_dir

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

            //printf("\nFolder %s\n", new_path);

            // Recursive descent
            // ------------------------------------------------------------------------
            ls_one_dir_recursive(new_path);
            // ------------------------------------------------------------------------
        }
        else {
            number_of_files += 1;

            // If file have 2 or more links
            // ------------------------------------------------------------------------
            char cur_file[1000];
            strcpy(cur_file, dirname);
            strcat(cur_file, "/");
            strcat(cur_file, temp->d_name);

            if (have_hlinks(cur_file)) {
                number_of_files_with_links += 1;
            }
            //printf("File   ");
            //printf("%s%s%s\n", dirname, "/", temp->d_name);
            // ------------------------------------------------------------------------
        }
        temp = readdir(dir);
    }
    test_print("\nEnd of while!!!!!!!!!!!!!!!!!!!!\n");
    // ------------------------------------------------------------------------
}


void ls_one_dir (char* dirname) {
    printf("\nList of directories:\n");

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
        if (temp->d_type == 4){     // If is_dir

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

            //printf("\nFolder %s\n", new_path);

            // Print dirname
            // ------------------------------------------------------------------------
            printf("%s\n", new_path);
            // ------------------------------------------------------------------------
        }
        temp = readdir(dir);
    }
    test_print("\nEnd of while!!!!!!!!!!!!!!!!!!!!\n");
    // ------------------------------------------------------------------------
}


bool have_hlinks(char* filename) {

    struct stat my_struct = {};
    stat(filename, &my_struct);
         
    if (my_struct.st_nlink > 1) return true;
    
    //printf("Name = %s, n_hlinks = %d, size = %5lld\n", filename, my_struct.st_nlink, my_struct.st_size);
    return false;

}