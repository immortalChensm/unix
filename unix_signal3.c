#include <stdio.h>
#include <signal.h>
#include <error.h>

static void sigDeal(int );
int main(void)
{
	if(signal(SIGUSR1,sigDeal)==SIG_ERR){
		perror("can't catch SIGUSR1");
	}

	if(signal(SIGUSR2,sigDeal)==SIG_ERR){
		perror("can't catch SIGUSR2");
	}

	printf("pid of this process:%d\n",getpid());

	while(1);
	pause();
}

static void sigDeal(int sig)
{
	if(sig == SIGUSR1){
		printf("received SIGUSR1\n");
	}

	else if(sig == SIGUSR2){
		printf("received SIGUSR2\n");
	}
	else{
		printf("received signal %d\n",sig);
	}
}
