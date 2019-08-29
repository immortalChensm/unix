#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
	pid_t pid = fork();
	int status;

	printf("[%d] master\n",getpid());
	if(pid<0){
		exit(0);
	}else if(pid==0){
		printf("[%d]child\n",getpid());
		exit(5);
	}else if(pid>0){
		
		pid_t cpid = wait(&status);
		printf("[%d]parent\n",getpid());
		printf("退出的子进程是:%d,status=%d\n",cpid,status);
	}

	return 0;
}
