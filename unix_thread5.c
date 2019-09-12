#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void print_msg(char *msg);
int show(char );
int main()
{
	
	pthread_t thread1,thread2;
	int i,j;

	void *retval;
	char *msg1 = "this is first thraed!\n";
	char *msg2 = "this is second thread!\n";
	pthread_create(&thread1,NULL,(void*)(&print_msg),(void*)msg1);
	pthread_create(&thread2,NULL,(void*)(&print_msg),(void*)msg2);

	//sleep(1);
	pthread_join(thread1,&retval);
	pthread_join(thread2,&retval);


	printf("thread1=%d,thread2=%d,retval1=%d,retval2=%d\n",thread1,thread2,retval,retval);

	pthread_t thread3;
	char *num="10";
	pthread_create(&thread3,NULL,(void*)(&show),(void*)&num);

	//sleep(1);
	//
	pthread_join(thread3,&retval);

	printf("thread3=%d\n",retval);
	
	return EXIT_SUCCESS;	
}

int show(char num)
{
	printf("pid=%d,threadId=%d,num=%d\n",getpid(),pthread_self(),num);

	return 100;
}
void print_msg(char *msg)
{
	int i;
	for(i=0;i<10;i++){
		printf("pid=%d,tid=%d,i=%d,%s\n",getpid(),pthread_self(),i,msg);
	}
}
