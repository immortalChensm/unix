#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
void print_message(char *ptr);

int main()
{
	pthread_t thread1,thread2;

	char *msg1 = "this is the first thead!\n";
	char *msg2 = "this is the second thead!\n";

	pthread_create(&thread1,NULL,(void*)(&print_message),(void *)msg1);


	pthread_create(&thread2,NULL,(void*)(&print_message),(void *)msg2);

	sleep(1);
	return 0;
}

void print_message(char *ptr)
{
	int retval;

	printf("Thread ID:%lx\n",pthread_self());
	printf("%s",ptr);
	int j=0;
	while(j<20)
	{
		j++;
		printf("pid=%d,tid=%lx,%d\n",getpid(),pthread_self(),time(NULL));
	}
	pthread_exit(&retval);
}
