#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int pid;

	pid = fork();	
	if (pid == 0) {
		//man 3 execl
		//ok no return 
		//err return
		execl("./register", "register", NULL);
		perror("execl");
		exit(1);
	}

	//father
	pid = fork();	
	if (pid == 0) {
		execl("./login", "login", NULL);
		perror("execl");
		exit(1);
	}

	pid = fork();
	if (pid == 0) {
		execl("./talk", "talk", NULL);
		perror("execl");
		exit(1);
	}

	//father
	//wait
	
	int ret;
	while (1) {
		ret = wait(NULL);
		if (ret < 0) {	
			printf("all child exit\n");
			break;
		}
	}

	return 0;
}




