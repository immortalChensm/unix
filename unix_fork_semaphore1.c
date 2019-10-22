#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
void printer(sem_t *sem,char *str)
{
	sem_wait(sem);
	while(*str!='\0'){
		putchar(*str);
		fflush(stdout);
		str++;
		sleep(1);
	}

	printf("\n");
	sem_post(sem);
}

int main(int argc,char *argv[])
{
	pid_t pid;

	sem_t *sem = NULL;

	pid = fork();

	if(pid<0){
		perror("fork error");
	}else if(pid == 0){
		
		sem = sem_open("name_sem",O_CREAT|O_RDWR,0666,1);
		if(sem == SEM_FAILED){
			perror("sem_open");
			return -1;
		}
		char *str1 = "hello";
		printer(sem,str1);
		sem_close(sem);

		_exit(1);
	}else if(pid>0){
		
		sem = sem_open("name_sem",O_CREAT|O_RDWR,0666,1);
		if(sem == SEM_FAILED){
			perror("sem_open");
			return -1;
		}

		char *str2 = "world";
		printer(sem,str2);

		sem_close(sem);
	}

	sem_unlink("name_sem");

	return 0;
}
