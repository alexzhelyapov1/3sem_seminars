#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
	int pid = fork();
	if (pid < 0)
		printf ("Proccess didn't create(\n");
	else if (pid == 0)
		printf ("I am a child. My id = %d, my parent id = %d\n", getpid(), getppid());
	else
		printf ("I am a parent. My id = %d, my child id = %d\n", getpid(), pid);
	return 0;
}
