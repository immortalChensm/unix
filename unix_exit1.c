#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	pid_t pid;

	if((pid=fork())==-1){
		perror("failed to create a new process\n");
		exit(0);
	}
	else if(pid==0){
		printf("this is child process,output begin\n");
		printf("this is child process,content in buffer");

		exit(0);
	}else{
		printf("\nparent process,output begin\n");
		printf("parent process,content in buffer");

		_exit(0);
	}

	return 0;
}
