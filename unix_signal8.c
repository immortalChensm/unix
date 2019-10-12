#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int fd[2];
void sigHandler(int sig)
{
	printf("捕获到信号了，准备发给主程序处理了哦\n");
	write(fd[1],"1",1);
}
int main()
{
//	int fd[2];
	int p = pipe(fd);

	int old_option = fcntl(fd[0],F_GETFL);
	int new_option = old_option|O_NONBLOCK;

	fcntl(fd[0],F_SETFL,new_option);


	printf("管理创建结果：%d\n",p);
	char sig;
	signal(SIGUSR1,sigHandler);
	pid_t pid;
	pid = getpid();
	printf("pid=%d\n",pid);
	while(1){
		int len = read(fd[0],&sig,1);
		printf("len=%d\n",len);
		if(sig){
			printf("收到你发来的信号了\n");
		}

		sleep(1);

		printf("在这里睡觉\n");
	}

	return 0;
}
