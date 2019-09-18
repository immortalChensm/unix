#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_key_t key;

void echomsg(int t)
{
	printf("desctuctor excuted in thread %d,param=%d\n",pthread_self(),t);
}

void *child1(void *arg)
{
	pthread_t tid = pthread_self();

	printf("thread %d enter \n",tid);
	pthread_setspecific(key,(void*)&tid);

	sleep(1);

	printf("thread %d retuns %d\n",tid,pthread_getspecific(key));

	sleep(2);
}
void *child2(void *arg)
{
	pthread_t tid = pthread_self();
	printf("thread %d enter\n",tid);
	char *msg = "hello,world";
	pthread_setspecific(key,(void*)msg);
	sleep(1);

	printf("thread %d returns %s\n",tid,pthread_getspecific(key));

	sleep(3);
}
int main()
{
	pthread_t tid1,tid2;

	printf("hi\n");

	pthread_key_create(&key,(void*)(&echomsg));

	pthread_create(&tid1,NULL,(void*)child1,NULL);
	pthread_create(&tid2,NULL,(void*)child2,NULL);

	sleep(10);

	pthread_key_delete(key);

	printf("main thread exit\n");

	return 0;
}
