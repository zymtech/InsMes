#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

//创建互斥量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//公共资源
int num = 0;

/*
	num++;
	memory:num
	cpu

	1.memory--->cpu
	2.cpu ++
	3.cpu----->memory
*/

//线程函数 当创建好线程后 这个函数就会被执行
void *thread1_handler(void *data)
{
	//while (1) {
	//	printf("我是线程1\n");
	//	sleep(1);
	//}

	int i, j;
	for (i = 0; i < 1000; i++) {
		for (j = 0; j < 3000; j++) {
			pthread_mutex_lock(&mutex);
			num++;//临界区
			pthread_mutex_unlock(&mutex);
		}
		usleep(50000);
	}
	

	return NULL;
}

void *thread2_handler(void *data)
{
	//while (1) {
	//	printf("我是线程2\n");
	//	sleep(1);
	//}

	int i, j;
	for (i = 0; i < 1000; i++) {
		for (j = 0; j < 3000; j++) {
			pthread_mutex_lock(&mutex);
			num++;//临界区
			pthread_mutex_unlock(&mutex);
		}
		usleep(50000);
	}

	return NULL;
}
/*
	应用程序启动后就是一个进程，在这个进程中默认就有一个线程（主线成）main函数有主线成执行
	main函数的return标志这进程的结束，进程结束了所有线程立即结束
*/
int main(void)
{
	pthread_t tid1, tid2;
	//创建一个线程
	pthread_create(&tid1, NULL, thread1_handler, (void *)123);	
	pthread_create(&tid2, NULL, thread2_handler, (void *)123);	

	//等待线程结束
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("num = %d\n", num);
	
	return 0;
}


