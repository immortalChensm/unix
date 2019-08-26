#include <stdio.h>
#include <string.h>
#include <unistd.h>
int gvar=2;
int main()
{
	
	pid_t pid;
	int var = 5;
	printf("process id:%d\n",getpid());

	printf("gvar=%d,var=%d\n",gvar,var);

	if((pid=fork())<0){
		perror("error!");
		return 1;
	}else if(pid == 0){
		gvar--;
		var++;
		printf("the child process id:%d\n,gvar=%d\n,var=%d\n",getpid(),gvar,var);
		_exit(0);
	}else{
		printf("the parent process id:%d\ngvar=%d\n,var=%d\n",getpid(),gvar,var);
		return 0;
	}
	return 0;
}
