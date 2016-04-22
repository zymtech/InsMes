#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//man socket
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/ip.h>
#include <netinet/in.h>

int main(void)
{
	//1.创建socekt
	int sd;

	//         ipv4       stream      tcp
	//如果成功返回socket的编号，失败返回－1
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		perror("socket");
		exit(1);
	}

	//2.构建服务地址
	struct sockaddr_in server_addr;
	server_addr.sin_family = PF_INET;//ipv4
	server_addr.sin_port = htons(1234);
	//设定服务器的ip地址（要根据实际情况修改
	server_addr.sin_addr.s_addr = inet_addr("192.168.1.5");

	//3.建立连接
	int ret = connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		perror("connect");
		exit(1);
	}

	//4.数据通信
	char *s = "你好！我是客户端，请求服务器给予回应";
	write(sd, s, strlen(s) + 1);

	char buf[1024];
	read(sd, buf, sizeof(buf));

	printf("回应:%s\n", buf);

	close(sd);

	return 0;
}




