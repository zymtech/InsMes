#include <stdio.h>
#include <stdlib.h>

//process
#include <unistd.h>

int main(void)
{
	//1
	fork();//create process
	//1 2
	fork();
	//1 11 2 22
	fork();
	//1 111 11  1111 2 222 22 2222
	//-------
	printf("helloword %d\n", getpid());

	return 0;
}



