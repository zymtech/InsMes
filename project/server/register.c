#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sqlite3.h>

#include "../protocol/protocol.h"

static sqlite3 *db;

int is_user_exists(char *account)
{
	int ret;
	sqlite3_stmt *stmt;
	char *sql = "select * from userTable where account=?";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);	
	if (ret != SQLITE_OK) {
		fprintf(stderr, "select error\n");
		return 1;
	} 

	sqlite3_bind_text(stmt, 1, account, -1, NULL);

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE && ret != SQLITE_ROW) {
		fprintf(stderr, "select error\n");
		return 1;
	} else if (ret == SQLITE_DONE) {
		return 0;
	} else {
		return 1;	
	}
}

int add_user(char *account, char *passwd)
{
	char *sql = "insert into userTable(account, passwd) values(?, ?)";
	sqlite3_stmt *stmt;
	int ret;
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);	
	if (ret != SQLITE_OK) {
		fprintf(stderr, "select error\n");
		return 1;
	} 
	sqlite3_bind_text(stmt, 1, account, -1, NULL);
	sqlite3_bind_text(stmt, 2, passwd, -1, NULL);
	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		fprintf(stderr, "insert error\n");
		return 1;
	} else {
		return 0;	
	}
}


int main(void)
{
	int sd;
	pid_t pid;	
	struct sockaddr_in server_addr, client_addr;
	int ret;
	struct register_st rst;
	struct respond_st dst;
	socklen_t addr_len = sizeof(client_addr);

	sd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket");
		exit(1);
	}
	
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(2222);
	server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");

	ret = bind(sd, (struct sockaddr *)&server_addr, sizeof(server_addr));	
	if (ret < 0) {
		perror("bind");
		exit(1);
	}

	ret = sqlite3_open("./userDatabase", &db);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_open\n");
		exit(1);
	}

	char *create_table_sql = "create table if not exists userTable(id integer not null primary key autoincrement, account text not null, passwd text not null)";
	ret = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "create table error\n");
		exit(1);
	}
	
	while (1) {
		ret = recvfrom(sd, &rst, sizeof(rst), 0, (struct sockaddr *)&client_addr, &addr_len);
		if (ret < 0) {
			perror("recvfrom");
			continue;
		}
		pid = fork();
		if (pid == 0){
			//1.判断用户是否存在
			ret = is_user_exists(rst.account);
			//2.如果存在发送错误给客户端
			if (ret) {
				dst.result = RESPOND_RESUTL_ERROR;
				dst.errno = ERROR_RESION_USER_EXISTS;
			//3.如果不存则发送注册成功给客户端
			} else {
				add_user(rst.account, rst.passwd);
				dst.result = RESPOND_RESUTL_OK;
			}
			
			sendto(sd, &dst, sizeof(dst), 0, (void *)&client_addr, sizeof(client_addr));
			exit(1);
		}	
	}

	sqlite3_close(db);
		
    return 0;
}






