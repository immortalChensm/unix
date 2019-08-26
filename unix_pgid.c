#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
	int i;

	for(i=0;;i++){
		
		printf("i=%d\n",i);
		int pgid = getpgid();

		pid_t pid = getpid();

		printf("当前进程号:%d,我属哪个进程组：%d\n",pid,pgid);

		
	}

	return 0;
}
