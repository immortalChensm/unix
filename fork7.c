#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	pid_t pid= fork();

	printf("master process %d\n",pid);

	if(pid==0){
		printf("father process %d\n",getpid());
	}
	else if(pid>0){
		printf("child process %d\n",getppid());
	}

	printf("end %d\n",getpid());

	printf("pid max %d\n",PID_MAX);

	return EXIT_SUCCESS;
}
