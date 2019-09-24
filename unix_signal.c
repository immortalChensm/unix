#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
void signalDeal(int sig)
{
	printf("信号中断处理程序:%d\n",sig);
	
}
int main()
{
	signal(SIGINT,signalDeal);
	time_t now;
	int k=0;
	for(k;;k++){
		//time(&now);
		printf("k=%d\n",k);
		sleep(1);
	}

	return 0;
}
