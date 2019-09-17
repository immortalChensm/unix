#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *talk()
{
	int k=0;
	while(1){
		printf("[%d,%lu]i am talking %d\n",getpid(),pthread_self(),k++);
		sleep(1);
	}
}

void *say()
{
	int m=0;
	while(1){
		printf("[%d,%lu]i am saying %d\n",getpid(),pthread_self(),m++);
		sleep(1);
	}
}
int main()
{
	pthread_t t1,t2;

	pthread_create(&t1,NULL,talk,NULL);
	pthread_create(&t2,NULL,say,NULL);
	void *retval1,*retval2;
	pthread_join(t1,&retval1);
	pthread_join(t2,&retval2);


	printf("main thread:%d,%lu\n",getpid(),pthread_self());

	return 0;
	
}
