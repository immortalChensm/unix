#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
	pid_t child;
	int status,retval;
	child = fork();

	if(child<0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(child == 0){
		printf("i am child process\n");
		sleep(1000);
		exit(EXIT_SUCCESS);
	}
	else{
		printf("i am parent process\n");
		if((waitpid(child,&status,WNOHANG))==0){

			printf("i am parent process 1 \n");
			retval = kill(child,SIGKILL);
			if(retval){
				puts("kill failed\n");
				perror("kill");
				waitpid(child,&status,0);
			}else{
				printf("%d killed\n",child);
			}
		}
	}

	exit(EXIT_SUCCESS);
}
