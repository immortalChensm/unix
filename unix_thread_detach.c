#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *func(void *arg)
{
	int i = *(int*)(arg);

	printf("i am worker:%d\n",i);

}
int main()
{
	pthread_t tid;

	int j;
	int count = 1000;

	for(j=0;j<count;j++){
		int *p = &(j);

		int ret = pthread_create(&tid,NULL,func,(void*)p);

		if(ret){
			printf("create thread error:%d\n",ret);
		}else{
			pthread_detach(tid);
		}
	}

	return 0;
}
