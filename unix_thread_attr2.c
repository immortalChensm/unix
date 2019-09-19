#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_key_t key;
pthread_attr_t attr1,attr2;

void msg(void *arg)
{
	printf("线程私有数据TSD退出时：%s\n",(char*)arg);

}

void *talk(void *word)
{
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	pthread_setspecific(key,(void*)"i am talking");
	int policy;
	char *policyStr;
	pthread_attr_getschedpolicy(&attr1,&policy);
	if(policy == SCHED_FIFO){
		policyStr = "SCHED_FIFO";
	}
	if(policy == SCHED_RR){
		policyStr = "SCHED_RR";
	}else{
		policyStr = "SHCED_OTHER";
	}

	printf("uid=%d,euid=%d,pid=%d,tid=%d 的私有数据是:%s,调度策略是：%s,说的话是:%s\n",getuid(),geteuid(),pid,tid,pthread_getspecific(key),policyStr,(char*)word);
	int retval = 0;
	pthread_exit((void*)1);
}

void *say(void *word)
{
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();

	pthread_setspecific(key,(void*)"i am saying");
	int policy;
	char *policyStr;
	pthread_attr_getschedpolicy(&attr2,&policy);
	if(policy == SCHED_FIFO){
		policyStr = "SCHED_FIFO";
	}
	if(policy == SCHED_RR){
		policyStr = "SCHED_RR";
	}else{
		policyStr = "SCHED_OTHER";
	}

	printf("uid=%d,euid=%d,pid=%d,tid=%d 的私有数据是:%s，调度策略是：%s,说的话是:%s\n",getuid(),geteuid(),pid,tid,pthread_getspecific(key),policyStr,(char*)word);

	int retval = 0;

	pthread_exit((void*)2);
}
int main(void)
{
	pthread_t thread1,thread2;

	struct sched_param param1,param2;

	param1.sched_priority = 1;
	param2.sched_priority = 2;

	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

	pthread_key_create(&key,(void*)(&msg));

	pthread_attr_setschedparam(&attr1,&param1);
	pthread_attr_setschedparam(&attr2,&param2);

	int ret = pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);
	pthread_attr_setschedpolicy(&attr2,SCHED_FIFO);
	printf("线程调度设置结果：%d\n",ret);

	pthread_create(&thread1,&attr1,(void*)talk,(void*)"hello,talk");
	pthread_create(&thread2,&attr2,(void*)say,(void*)"hello,say");

	void *ret1;
	void *ret2;
	pthread_join(thread1,&ret1);

	pthread_join(thread2,&ret2);

	printf("线程1的退出状态码：%d\n",(int*)ret1);
	printf("线程2的退出状态码：%d\n",(int*)ret2);

	printf("主线程退出\n");
	pthread_attr_destroy(&attr1);
	pthread_attr_destroy(&attr2);
	pthread_key_delete(key);
	return 0;
	
}
