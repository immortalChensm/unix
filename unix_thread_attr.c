#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *pthread_fun(void *arg)
{
	int n=3;

	while(n--){
		printf("------%d-----\n",n);
		sleep(1);
	}
	return ((void*)1);
}
int main()
{
	pthread_t tid;

	pthread_attr_t attr;

	void *ret;
	int err;

	pthread_attr_init(&attr);

	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	pthread_create(&tid,&attr,(void*)pthread_fun,NULL);

	while(1){
		err = pthread_join(tid,(void*)&ret);
		if(err!=0){
		//	fprintf(stderr,"use thread_join %s\n",strerror(err));
			printf("error %d\n",err);
		}else{

		}	printf("pthread_join success\n");
		sleep(1);

	}

	pthread_attr_destroy(&attr);

	return 0;
}
