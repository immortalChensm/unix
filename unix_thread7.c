#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void print_msg(char *msg);
int main()
{
	pthread_t thread1,thread2;

	int i,j;

	void *retval;

	char *msg1 = "this is the first thread\n";
	char *msg2 = "this is the second thread\n";

	pthread_create(&thread1,NULL,(void*)(&print_msg),(void*)msg1);

	//pthread_join(thread1,&retval);
	pthread_create(&thread2,NULL,(void*)(&print_msg),(void*)msg2);

	//pthread_join(thread1,&retval);
	//pthread_join(thread2,&retval);

	pthread_t main_t;
	//sleep(1);
	pid_t pid;

	pid = getpid();
	main_t = pthread_self();

	printf("主线程:pid=%d,tid=%d\n",pid,main_t);
	//pthread_join(thread1,&retval);
	pthread_join(thread2,&retval);
	pthread_join(thread1,&retval);
	//sleep(1);
	return 0;
}

void print_msg(char *msg)
{
	int i;
	for(i=0;i<10;i++){
		printf("%s\n",msg);
	}
}
