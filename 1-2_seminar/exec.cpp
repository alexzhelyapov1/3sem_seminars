#include <unistd.h>
#include <stdio.h>

int main (int argc, char* argv[]) {
    int pid = fork();
	if (pid < 0)
		printf ("Proccess didn't create(\n");
	else if (pid == 0) 
        execvp (argv[1], argv + 1);
	else 
        for (int i = 0; i < 1200; i++) printf ("%d\n", i);

    return 0;
}