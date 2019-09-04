#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

void pr_exit(int status)
{
	if(WIFEXITED(status)){//正规停止
		printf("normal termination,exit status=%d\n",WEXITSTATUS(status));//打印终止状态
	}
	else if(WIFSIGNALED(status)){//异步停止
		printf("abnormal termination,signal number=%d%s\n",WTERMSIG(status),
	#ifdef WCOREDUMP
		WCOREDUMP(status)?"(core file generated)":"");
	#else
	"");
	#endif
	}
	else if(WIFSTOPPED(status)){
		printf("child stopped,signal number=%d\n",WSTOPSIG(status));
	}
}
int main()
{
	pid_t pid;

	int status;

	if((pid=fork())<0){
		perror("fork error");
	}
	else if(pid==0){
		exit(7);
	}

	if(wait(&status)!=pid){
		perror("wait error");
	}

	pr_exit(status);

	if((pid=fork())<0){
		perror("fork error");
	}

	else if(pid==0){
		abort();
	}

	if(wait(&status)!=pid){
		perror("wait error");
	}

	pr_exit(status);

	if((pid=fork())<0){
		perror("fork error");
	}
	else if(pid==0){
		status/=0;
	}
	if(wait(&status)!=pid){
		perror("wait error");
	}

	pr_exit(status);

	exit(0);
}
