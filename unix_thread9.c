#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int age=0;
void *talk()
{
	int k=0;
	
	while(k<20){
		printf("[%d,%lu]i am talking %d,age=%d\n",getpid(),pthread_self(),k++,age++);
		sleep(1);
	}
}

void *say()
{
	int m=0;
	while(m<10){
		printf("[%d,%lu]i am saying %d,age=%d\n",getpid(),pthread_self(),m++,age++);
		sleep(1);
	}
}
int main()
{
	pthread_t t1,t2;

	pthread_create(&t1,NULL,talk,NULL);
	pthread_create(&t2,NULL,say,NULL);
	void *retval1,*retval2;
	//pthread_join(t1,&retval1);
	//pthread_join(t2,&retval2);


	printf("main thread:%d,%lu\n",getpid(),pthread_self());

	pthread_join(t1,&retval1);

	pthread_join(t2,&retval2);

	return 0;
	
}
