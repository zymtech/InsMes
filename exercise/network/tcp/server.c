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

	//2.绑定地址  man 7 ip
	struct sockaddr_in server_addr;
	server_addr.sin_family = PF_INET;//ipv4
	server_addr.sin_port = htons(1234);
	//代表不管哪个网卡收到的包都接收
	server_addr.sin_addr.s_addr = INADDR_ANY;


	int ret;
	//把server_addr绑定到sd
	ret = bind(sd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		perror("bind");
		exit(1);
	}

	//3.设置socket为监听状态
	ret = listen(sd, 20);
	if (ret < 0) {
		perror("listen");
		exit(1);
	}

	int new_sd;
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	//4.等待客户端连接
	while (1) {
		new_sd = accept(sd, (struct sockaddr *)&client_addr, &addr_len);
		if (new_sd < 0) {
			perror("accept");
			continue;
		}

		//接收客户端的数据
		char buf[1024];
		read(new_sd, buf, sizeof(buf));
		printf("收到客户端的数据是:%s\n", buf);
		//给客户发送数据
		write(new_sd, "ok", 3);

		close(new_sd);
	}

	close(sd);

	return 0;
}




