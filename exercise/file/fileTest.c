#include <stdio.h>
#include <stdlib.h>
//strlen
#include <string.h>
//文件
#include <sys/types.h>
#include <sys/fcntl.h>

int main(void)
{
	int fd;
	//以可读可写的方式打开文件
	//返回文件描述符（文件编号）
	//O_CREAT 如果文件不存在则创建
	//0666代表任何用户都可以对这个文件读写操作
	fd = open("student.txt", O_RDWR |O_CREAT, 0666);
	if (fd < 0) {
		//出了打印open之外还会打印出错信息
		perror("open");
	}

	//字符串:字符字符字符0
	char *content = "hello linux i am here";
	//strlen计算字符串长度的时候不算0
	write(fd, content, strlen(content) + 1);

	/*		     |
	hello linux i am here---------
	*/

	//设置文件偏移（关标）
	lseek(fd, 0, SEEK_SET);

	char buf[256];
	//从文件指针（光标）处开始读
	//从fd文件读取256个字节到buf中
	read(fd, buf, 256);

	printf("文件内容是:%s\n", buf);

	close(fd);
	
	return 0;
}




