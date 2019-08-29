#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
int main(int argc,char *argv[])
{
	int numDead;
	pid_t childPid;

	int j;

	setbuf(stdout,NULL);

	for(j=1;j<argc;j++){
		switch(fork()){
			case -1:
			exit(0);
			case 0:
				printf("child %d\n",getpid());
				sleep(10);
				exit(1);
			default:
				break;
		}
	}

	numDead = 0;

	for(;;){
		childPid = wait(NULL);
		if(childPid == -1){
			if(errno == ECHILD){
				printf("no more child -bye!\n");
				exit(EXIT_SUCCESS);
			}else{
				exit(1);
			}
		}

		numDead++;

		printf("exit child=%d,numDead=%d,parentid=%d\n",childPid,numDead,getpid());
	}
}
