#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc,char *argv[])
{
	int numChild,j;
	pid_t childPid;
	numChild = atoi(argv[1]);

	setbuf(stdout,NULL);
	int status;
	for(j=0;j<numChild;j++){
		switch(childPid=fork()){
			case -1:
				exit(0);
			break;
			case 0:
				printf("%d [%d]child\n",j,getpid());
			//	_exit(EXIT_SUCCESS);
				exit(2);
			break;
			default:
			printf("%d [%d]parent\n",j,getpid());
			
			pid_t pid = wait(&status);
			printf("退出的子进程id=%d,状态:%d\n",pid,status);

			break;
		}
	}
	exit(EXIT_SUCCESS);
}
