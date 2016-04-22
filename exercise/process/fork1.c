#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int main(void)
{
	int pid;

	pid = fork();
	if (pid == 0) {
		while (1) {
			printf("child\n");
			sleep(1);
		}
	} else {
		while (1) {
			printf("father\n");
			sleep(1);
		}
	}

	printf("helloworld\n");

	return 0;
}
