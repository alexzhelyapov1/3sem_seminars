#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main () {
    int pipefd[2];
    char data[1000];
    
    pipe(pipefd);
    int id = fork();

    //-----------------------------------------------------------------------------------------------------------------------------------------------
    if (id == 0) {
        // printf ("----------PROC 2 started-----------\n");
        int id_2 = fork();

        //--------------------------------------------------------------------------------------
        if (id_2 == 0) {
            // printf ("----------PROC 3 started-----------\n");
            int id_3 = fork();

            //--------------------------------------------------
            if (id_3 == 0) {
                // printf ("----------PROC 4 started-----------\n");
                strcpy (data, "4 Do you");
                write (pipefd[1], data, strlen (data) + 1);
                strcpy (data, "4 want");
                write (pipefd[1], data, strlen (data) + 1);
                strcpy (data, "4 new car?");
                write (pipefd[1], data, strlen (data) + 1);
                strcpy (data, "4 END");
                write (pipefd[1], data, strlen (data) + 1);
            }
            else if (id_3 > 0) {
                strcpy (data, "3 I ");
                write (pipefd[1], data, strlen (data) + 1);
                strcpy (data, "3 am the");
                write (pipefd[1], data, strlen (data) + 1);
                strcpy (data, "3 third proccess!");
                write (pipefd[1], data, strlen (data) + 1);
            }
            else {
                printf ("Could not to fork new proccess\n");
            }
            //--------------------------------------------------

        }
        else if (id_2 > 0) {
            strcpy (data, "2 Hello");
            write (pipefd[1], data, strlen (data) + 1);
            strcpy (data, "2 world");
            write (pipefd[1], data, strlen (data) + 1);
            strcpy (data, "2 of all");
            write (pipefd[1], data, strlen (data) + 1);
        }
        else {
            printf ("Could not to fork new proccess\n");
        }
        //--------------------------------------------------------------------------------------
    }
    else if (id > 0) {
        strcpy (data, "");
        char bufer[] = "0\0";
        while (strcmp (data + 2, "END") != 0) {
            read (pipefd[0], bufer, 1);
            if (bufer[0] > '1' && bufer[0] < '9' && strlen (data) != 0) {
                printf ("MESSAGE from proccess %c: \"%s\"\n", data[0], data + 2);
                strcpy (data, bufer);
                continue;
            }
            strcat (data, bufer);
        }
    }
    else {
        printf ("Could not to fork new proccess\n");
    }
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    return 0;
}