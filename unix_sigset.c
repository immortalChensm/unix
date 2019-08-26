#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void printsigset(sigset_t *sig)
{
	int i;
	for(i=0;i<32;i++){
	
		if(sigismember(sig,i)){
			printf("1");
		}else{
			printf("0");
		}
	}

	printf("\n");
}

void handler(int sig)
{
	printf("SIGINT信号到达并处理了\n");
	exit(0);
}
int main()
{
	sigset_t s,p;//定义信号集

	sigemptyset(&s);
	sigemptyset(&p);

	sigaddset(&s,SIGTSTP);
//	sigaddset(&s,SIGINT);

	sigprocmask(SIG_BLOCK,&s,NULL);
	signal(SIGINT,handler);
	while(1){
		sigpending(&p);
		printsigset(&p);
		sleep(1);
	}

	return 0;
}
