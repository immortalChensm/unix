#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_g,sem_p;

char ch = 'a';

void *pthread_g(void *arg)
{
	while(1){
		sem_wait(&sem_g);
		ch++;
//		putchar(ch);
		sleep(1);
		sem_post(&sem_p);
	}
}
void *pthread_p(void *arg)
{
	while(1){
		sem_wait(&sem_p);
		printf("%c",ch);
		fflush(stdout);
		sem_post(&sem_g);
	}
}
int main(int argc,char *argv[])
{
	pthread_t tid1,tid2;

	sem_init(&sem_g,0,0);
	sem_init(&sem_p,0,1);

	pthread_create(&tid1,NULL,pthread_g,NULL);

	pthread_create(&tid2,NULL,pthread_p,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	return 0;
}
