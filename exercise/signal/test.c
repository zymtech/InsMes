#include <stdio.h>

int main(void)
{
	//printf("helloworld\n");
	//write(1, "helloworld\n", 11);
	//写文件 0 1 2 3 4 5 6..
	char buf[1024];
	int ret = read(0, buf, 20);
	buf[ret] = 0;
	printf("%s\n", buf);
	
	return 0;
}
