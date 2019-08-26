#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//unix系统编程手册上 第456页代码测试示例  
//
//
static int idata = 111;//此变量放在全局数据库
int main()
{
	int istack = 222;//此变量放在栈区 

	pid_t childPid;

	switch(childPid = fork()){
		case -1:
			exit(0);
			break;
		case 0:
			idata*=3;
			istack*=3;
		break;
		default: 
			sleep(3);
			break;
		sleep(3);
	}

	printf("PID=%ld %s idata=%d,istack=%d\n",(long)getpid(),(childPid==0)?"child":"parent",idata,istack);

	exit(EXIT_SUCCESS);
}
