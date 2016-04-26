#include <stdio.h>
#include <unistd.h>
#include <signal.h>

//信号：linux系统的一种异步的通知机制
//进程收到信号的三种方式：
//1.忽略信号
//2.默认响应
//3.捕捉信号（安排一个信号处理函数）
//发送信号的方式：
//1.命令行 ctrl+c
//2.kill 命令
//3.kill 函数

void sig_handler(int no)
{
	printf("收到了信号\n");
}

int main(void)
{
	//进程收到SIGINT信号后的默认行为是结束当前进程
	//忽略SIGINT信号
	//signal(SIGINT, SIG_IGN);
	//捕捉信号SIGINT
	signal(SIGINT, sig_handler);
	while (1) {
		sleep(1);
		printf("time over\n");
	}	
	return 0;
}


