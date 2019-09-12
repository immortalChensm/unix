#include <stdio.h>
#include <pthread.h>

#include <stdlib.h>

pthread_t ntid;

void printfids(const char *s)
{
	pid_t pid;

	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %u tid %u (0x%x)\n",s,pid,tid,tid);
}

void *thr_fn(void *arg)
{
	printfids("new thread:");
	return ((void*)0);
}
int main(void)
{
	int err;

	err = pthread_create(&ntid,NULL,thr_fn,NULL);

	if(err!=0){
		printf("can not create thread:%s\n",strerror(err));
	}

	printfids("main thread:");
	sleep(1);
	exit(0);
}
