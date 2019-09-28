#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void signalDeal(int signum);

int main(void)
{
	char buffer1[100],buffer2[100];

	int i;

	struct sigaction act;

	act.sa_handler = signalDeal;

	sigemptyset(&act.sa_mask);

	act.sa_flags = 0;

	sigaction(SIGTERM,&act,NULL);

	printf("pid of the process:%d\n",getpid());

	while(1){
		printf("please input:\n");
		fgets(buffer1,sizeof(buffer1),stdin);

		for(i=0;i<100;i++){
			if(buffer1[i]>=97&&buffer1[i]<=122){
				buffer2[i] = buffer1[i]-32;
			}else{
				buffer2[i] = buffer1[i];
			}
		}
		printf("your input is :%s\\n",buffer2);
	}

	exit(0);
}

void signalDeal(int sig)
{
	printf("catch signal SIGTERM \n");
	exit(0);
}
