#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void say(int sig)
{
	printf("ctrl+c=%d\n",sig);

	return ;
}
int main(void)
{
	signal(SIGINT,SIG_IGN);



	int k;
	for(k;;k++){
		printf("k=%d\n",k);

		sleep(2);
	}

	return EXIT_SUCCESS;
}
