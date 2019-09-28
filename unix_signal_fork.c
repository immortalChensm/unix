#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>


int main()
{

	pid_t pid;
	int status;

	if(!(pid=fork())){
		printf("Hi I am child process!\n");
		sleep(10);
		printf("Hi I am child process,again!\n");
		//return ;
		exit(3);
	}else{
		printf("send signal to child process (%d) \n");
		sleep(1);
		//if(kill(pid,SIGABRT)==-1){
		//	perror("kill failed!\n");
		//}

		
		
		wait(&status);

		if(WIFSIGNALED(status)){
			printf("child process receive signal %d\n",WTERMSIG(status));
		}

		if(WIFEXITED(status)){
			printf("child process 退出状态码 %d\n",WEXITSTATUS(status));
		}
	}
	return 0;
}

