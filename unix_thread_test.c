#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int key;

void *num(void *arg)
{

	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	key+=10;

	printf("thread 1 pid=%d,tid=%d key=%d\n",pid,tid,key);

	pthread_exit((void*)1);
}

void *number(void *arg)
{
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	printf("thread 2 pid=%d,tid=%d key=%d\n",pid,tid,key);
	key+=20;

	printf("thread 2 pid=%d,tid=%d,key=%d\n",pid,tid,key);

	pthread_exit((void*)2);
}
int main()
{
	
	pthread_t thread1,thread2;
	key = 0;
	pthread_create(&thread1,NULL,(void*)num,(void*)&key);
	pthread_create(&thread2,NULL,(void*)number,(void*)&key);

	void *retval1;
	void *retval2;

	pthread_join(thread1,&retval1);
	pthread_join(thread2,&retval2);

	printf("main thread exit key=%d\n",key);

	return 0;
	
}
