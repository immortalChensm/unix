#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void handler(int signum)
{
	printf("i am sigint of sig!!sig=%d\n",signum);
}
int main()
{
	while(1){
		struct sigaction new,old;
		new.sa_handler = handler;
		sigemptyset(&new.sa_mask);

	//	new.sa_flags = 0;
		//pause();
		sigaction(SIGINT,&new,NULL);
		pause();
	}

	return 0;
}
