#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
pthread_t ntid;
void printids(const char *s)
{
	pid_t pid;

	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %u tid %u (0x%x)\n",s,pid,tid,tid);
}
void *thr_fn(void *arg)
{
	printids("new thread:");
	printf("num=%s\n",arg);
	return ((void*)0);
}
int main()
{
	int err;

	err = pthread_create(&ntid,NULL,thr_fn,"1");

	if(err!=0){
		printf("can not create thread:%s\n",strerror(errno));
	}

	printids("main thread:");
	
	pthread_t ntid1;

	pthread_create(&ntid1,NULL,thr_fn,"2");
	pthread_t ntid2;

	
	pthread_create(&ntid2,NULL,thr_fn,"3");
	sleep(1);
	return 0;
}
