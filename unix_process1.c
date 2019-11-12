#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid = fork();

	if(pid==0){
		printf("child worker %d\n",getpid());
		//return 0;	
		exit(1);
	}else if(pid>0){
		int status;	
		int pid = wait(&status);
		printf("退出的子进程号为:%d,退出状态码为：%d\n",pid,status);
			
		printf("parent worker %d\n",getpid());


	}
	printf("end process %d\n",getpid());
	return 0;
}
