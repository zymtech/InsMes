#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>

struct student_st {
	char name[32];
	int age;
	int english;
	int math;
	int chiness;
};

int read_all_student(void)
{
	//1.打开文件
	//2.把所有学生都出来（循环）
	//3.关闭文件

	int fd;
	
	fd = open("sm", O_RDONLY);

	struct student_st s;
	int ret;
	while(1) {
		//如果返回值是０，代表文件已经读到了结尾
		ret = read(fd, &s, sizeof(s));
		if (ret == 0) {
			break;
		}
		printf("===============\n");
		printf("[%s %d %d %d %d]\n", s.name, s.age, s.english, s.chiness, s.math);
	}

	close(fd);
	
	return 0;
}

int write_student_to_file(void)
{
	char name[32];
	int age, english, chiness, math;
	
	printf("姓名:");
	scanf("%s", name);
	printf("年龄:");
	scanf("%d", &age);
	printf("英语成绩:");
	scanf("%d", &english);
	printf("语文成绩:");
	scanf("%d", &chiness);
	printf("数学成绩:");
	scanf("%d", &math);

	//1.打开文件
	//2.定位到文件的结尾
	//3.写入学生数据
	//4.关闭文件
	
	int fd;
	
	//O_APPEND代表打开文件后文件指针（光标）定位到文件结尾
	fd = open("sm", O_RDWR | O_CREAT | O_APPEND);

	//构建一个学生
	struct student_st s;
	strcpy(s.name, name);
	s.age = age;
	s.english = english;
	s.chiness = chiness;
	s.math = math;

	//把学生写到文件
	write(fd, &s, sizeof(s));

	//关闭文件
	close(fd);	

	return 0;
}

int main(void)
{
	char *prompt = "软件使用方法:\n";
	char *fun1 = "1.添加一个学生\n";
	char *fun2 = "2.查看所有学生\n";
	char *fun3 = "3.退出\n";
	int id;//1/2/3

	printf("%s%s%s%s", prompt, fun1, fun2, fun3);	

	while (1) {
		//printf会把字符串放到缓存（如果字符串中有\n则会刷新缓存）
		printf("请输入功能id:");
		//刷缓存
		fflush(NULL);
		scanf("%d", &id);
		switch(id) {
		case 1:
			write_student_to_file();
			break;
		case 2:
			read_all_student();
			break;
		case 3:
			//程序退出
			exit(0);
		default:
			break;
		} 
	}

	return 0;
}




