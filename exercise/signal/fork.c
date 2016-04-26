#include <stdio.h>
#include <unistd.h>

/*
 *程序--->进程（正在运行的程序）

 kernel---->linux
	进程管理
	--->   ---->
	    struct task_struct 1K
	    struct task_struct 1K
	<---   <----
 -------高 4G
       kenerl
 -------   3G
       桟   	用来存放局部变量 a=4
       堆  	malloc  free
       动态库
       数据段 	全局变量
       代码段	可执行代码
 -------低

  -------高 4G
	kenerl
  -------   3G
	桟   	用来存放局部变量 a=4
	堆  	malloc  free
	动态库
	数据段 	全局变量
	代码段	可执行代码
  -------低
 */

/*
 *进程间通信
 *pipe
 *
 * p[0]        p[1] father
 *   [=========]
 * p[0]        p[1] child
 *
 */

int main(void)
{
	int a = 4;
	pid_t pid;

	int p[2];
	//创建管道
	int ret = pipe(p);

	pid = fork();
	if (pid == 0) {
		//child
		close(p[0]);
		write(p[1], "hello", 6);
		close(p[1]);
		exit(1);
	}

	sleep(2);
	//father
	close(p[1]);
	char buf[64];
	read(p[0], buf, 20);
	printf("read ok %s\n", buf);
	
	return 0;
}









