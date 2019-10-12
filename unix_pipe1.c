#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	int n,fd[2];

	pid_t pid;

	char buffer[BUFSIZ+1];

	if(pipe(fd)<0){
		perror("pipe failed!\n");
		exit(0);
	}

	if((pid=fork())<0){
		printf("fork failed!\n");
		exit(0);
	}else if(pid>0){
		close(fd[0]);
		write(fd[1],"this is a pipe test!\n",22);
	}else{
		close(fd[1]);
		n = read(fd[0],buffer,BUFSIZ);
		write(STDOUT_FILENO,buffer,n);
	}
	exit(0);
}
