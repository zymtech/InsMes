#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//network  
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

//inet_nota()
#include <arpa/inet.h>

int main(void)
{
	//1.create socket
	//man 7 ip
	//              ipv4      dgram      udp
	int sd =  socket(PF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket");
		exit(1);
	}

	//2.bind socket_addr
	struct sockaddr_in server_addr;
	server_addr.sin_family = PF_INET;//v4
	server_addr.sin_port = htons(2345);
	//any netcard 
	//INADDR_ANY
	server_addr.sin_addr.s_addr = inet_addr("172.17.6.6");

	//sendto data to server
	sendto(sd, "ok", 3, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

	char buf[1024];
	recvfrom(sd, buf, sizeof(buf), 0, NULL, NULL);
	printf("resp:%s\n", buf);

	close(sd);

	return 0;
}






