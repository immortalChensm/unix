#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void signal_interrupt(int sig)
{
	printf("sig=%d\n",sig);

	printf("will exit\n");

	exit(0);
}
int main()
{
	if(signal(SIGINT,signal_interrupt)==SIG_ERR){
		exit(EXIT_SUCCESS);
	}

	int i;
	for(i=0;;i++){
		printf("i=%d\n",i);
		sleep(1);
	}
}
