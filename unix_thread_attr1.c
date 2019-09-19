#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *my_thread(void *arg)
{
	int retval = 0;

	pthread_attr_t attr;

	struct sched_param param;

	size_t stacksize;

	int detachstate;

	int scope;
	
	int inherit;

	int policy;

	pthread_attr_init(&attr);

	pthread_attr_getstacksize(&attr,&stacksize);

	printf("stacksize:%d\n",stacksize);

	pthread_attr_getdetachstate(&attr,&detachstate);

	if(detachstate == PTHREAD_CREATE_JOINABLE){
		printf("detachestate:PTHRED_CREATE_JOINABLE\n");
	}
	if(detachstate == PTHREAD_CREATE_DETACHED){
		printf("detachedstate:PTHREAD_CREATE_DETACHED\n");
	}

	pthread_attr_getscope(&attr,&scope);

	if(scope == PTHREAD_SCOPE_PROCESS){
		printf("scope:PTHREAD_SCOPE_PROCESS\n");
	}
	if(scope == PTHREAD_SCOPE_SYSTEM){
		printf("scope:PTHREAD_SCOPE_SYSTEM");
	}

	pthread_attr_getinheritsched(&attr,&inherit);

	if(inherit == PTHREAD_INHERIT_SCHED){
		printf("inheritsched:PTHREAD_INHERIT_SCHED\n");
	}

	if(inherit == PTHREAD_EXPLICIT_SCHED){
		printf("inheritsched:PTHREAD_EXPLICIT_SCHED\n");
	}

	pthread_attr_getschedpolicy(&attr,&policy);

	if(policy == SCHED_FIFO){
		printf("policy:SCHED_FIFO\n");
	}
	if(policy == SCHED_RR){
		printf("policy:SCHED_RR\n");
	}else{
		printf("policy:SCHED_OTHER\n");
	}

	pthread_attr_getschedparam(&attr,&param);

	printf("schedpriority:%d\n",param.sched_priority);

	pthread_attr_destroy(&attr);

	pthread_exit(&retval);
}
int main(void)
{
	int count;

	pthread_t thread;

	int *retval;

	pthread_create(&thread,NULL,my_thread,(void*)NULL);

	pthread_join(thread,(void**)(&retval));

	printf("thread exit %d\n",*retval);

	return 0;
}

