#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int count=0;

	pid_t pid;

	printf("start process id is %d,count is %d\n",getpid(),count);
	pid = fork();

	if(pid<0){
		printf("error in fork!");
		exit(1);
	}

	else if(pid == 0){
		printf("i am the child process,the count is %d,my process id is %d\n",count,getpid());
	}
	else{
		printf("i am the parent process,the count is %d,my process id is %d\n",++count,getpid());
	}


	printf("end process id is %d\n",getpid());
	return 0;
}
