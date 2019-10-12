#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#define BUFSIZE 4096


int main(void)
{
	int fd[2];

	char buf[BUFSIZE]= "hello! I am your brother!\n";
	pid_t pid;
	int len;

	if((pipe(fd))<0){
		perror("pipe failed\n");
	}

	if((pid = fork())<0){
		perror("fork failed\n");
	}else if(pid==0){
		close(fd[0]);
		write(fd[1],buf,strlen(buf));
		printf("pid=%d write %s\n",getpid(),buf);
		exit(2);
	}
	
	if((pid=fork())<0){
		perror("fork failed\n");
	}else if(pid>0){
		close(fd[0]);
		close(fd[1]);
	//	exit(0);
	}else{
		close(fd[1]);
	
		len = read(fd[0],buf,BUFSIZE);
		printf("pid=%d content %s\n",getpid(),buf);
		write(STDOUT_FILENO,buf,len);
		exit(1);
	}

	//sleep(5);
	int status;
	pid = wait(&status);
	if(pid){
		if(WIFEXITED(status)){
			printf("pid %d 正常退出%d,%d\n",pid,WEXITSTATUS(status),status);
		}
		if(WIFSIGNALED(status)){
			printf("异步退出%d\n",WTERMSIG(status));
		}
	}

	printf("master %d process begin\n",getpid());
	int i;
	for(i=0;i<10;i++){
		printf("i=%d\n",i);
	}
	printf("master %d process end\n",getpid());
	return 0;
}
