#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	/* if error */

	pid = fork();
	if (pid == 0) {
		//把标准输入重定向到管道的读段
		dup2(fd[0], 0);
		//关闭管道的写端
		close(fd[1]);
		//child
		//启动mplayer，mplayer从标准输入读取数据
		execl("/usr/local/bin/mplayer", "player", "-", NULL);
		exit(0);
	}

	//father	
	char buf[512];
	int ret;
	int file;

	file = open("/root/桌面/video/arm5", O_RDONLY);
	/* if error */
	
	close(fd[0]);

	while (1) {
		ret = read(file, buf, sizeof(buf));
		/* if error */
		if (ret == 0) {
			break;
		}
		write(fd[1], buf, ret);
		
	}

	close(fd[1]);
	close(file);
	wait(NULL);
	
	return 0;
}




