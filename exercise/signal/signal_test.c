#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t pid;

void sig_handler(int no)
{
	//任何进程都不能忽略或者捕捉SIGKILL信号，SIGKILL信号的默认行为是结束进程
	kill(pid, SIGKILL);
	exit(0);
}

int main(void)
{
	struct sigaction action;
	action.sa_handler = sig_handler;
	sigaction(SIGINT, &action, NULL);

	//fork  子进程  父进程
	//通过信号实现子进程结束后不变成僵尸进程
	struct sigaction ac;
	ac.sa_handler = SIG_IGN;
	ac.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &ac, NULL);

	pid = fork();
	if (pid == 0) {
		execl("./dup2", "haha", NULL);
	}	

	int i = 0;
	while (1) {
		printf("i = %d\n", i++);
		sleep(1);
	}	

	return 0;
}



