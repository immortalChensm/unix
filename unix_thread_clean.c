#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

线程清理：  
当使用pthread_cleanup_push时必须加上thread_clean_pop否则报错   
当调用pthread_exit时才会执行【且只能在pthread_clean_pop之前调用】  


void *clean(void *arg)
{
	printf("cleanup:%s \n",(char *)arg);
	return (void*)0;
}
void *thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push((void*)clean,"thread 1 first handler");
	pthread_cleanup_push((void*)clean,"thread 1 second handler");

	printf("thread 1 push complte\n");
	if(arg){
		return ((void*)1);
	}
	pthread_cleanup_pop(0);

	pthread_cleanup_pop(0);

	return (void*)1;
	//pthread_exit((void*)1);
}

void *thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push((void*)clean,"thread 2 first handler");
	pthread_cleanup_push((void*)clean,"thread 2 second handler");

	printf("thread 2 push complete\n");

	if(arg){
		pthread_exit((void*)2);
	}

	
	pthread_exit((void*)2);	
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	printf("thread 2 haha");
	//pthread_exit((void*)2);
	
	
}

int main(void)
{
	int err;
	pthread_t tid1,tid2;

	void *tret;

	err = pthread_create(&tid1,NULL,thr_fn1,(void*)1);

	if(err!=0){
		perror("create thread 1 error\n");
		return -1;
	}

	err = pthread_create(&tid2,NULL,thr_fn2,NULL);

	if(err!=0){
		perror("create pthread 2 error\n");
		return -1;
	}

	err = pthread_join(tid1,&tret);
	if(err!=0){
		perror("join thread1 error!\n");
		return -1;
	}

	printf("thread 1 exit code %d\n",(int*)tret);

	err = pthread_join(tid2,&tret);

	if(err!=0){
		perror("join thread2 error");
		return -1;
	}

	printf("thread 2 exit code %d\n",(int*)tret);

	return 1;
}
