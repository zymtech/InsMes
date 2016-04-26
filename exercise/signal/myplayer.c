#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		execl("/usr/local/bin/mplayer", "xxx", argv[1], NULL);
	}
		
	return 0;
}
