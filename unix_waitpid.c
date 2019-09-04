#include <stdio.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;

	if((pid=fork())<0){
		perror("fork error.\n");
		exit(0);
	}
	else if(pid==0){
		if((pid=fork())<0){
			perror("fork error.\n");
			exit(0);
		}else if(pid>0){
			exit(0);
		}

		sleep(2);

		printf("second child,parent pid=%d\n",getpid());
		exit(0);
	}

	if(waitpid(pid,NULL,0)!=pid){
		perror("waitpid error.\n");
		exit(0);
	}

	exit(0);
}
