#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

void intHandler(int sig);
void continueHandler(int sig);
void terminateHandler(int sig);

int main(void)
{
	char buffer[100];

	signal(SIGINT,&intHandler);
	signal(SIGTSTP,&intHandler);
	signal(SIGCONT,&continueHandler);

	signal(SIGTERM,&terminateHandler);

	printf("pid of this process:%d\n",getpid());

	while(1){
		printf("please input:\n");
		fgets(buffer,sizeof(buffer),stdin);

		if(strcmp(buffer,"int\n")==0){
			raise(SIGINT);
		}
		else if(strcmp(buffer,"stop\n")==0){
			raise(SIGTSTP);
		}
		else if(strcmp(buffer,"continue\n")==0){
			raise(SIGCONT);
		}
		else if(strcmp(buffer,"quit\n")==0){
			raise(SIGTERM);
		}
		else{
			printf("your input is:%s\n",buffer);
		}
	}

	exit(0);
}

void intHandler(int sig)
{
	printf("catch signal:%d\n",sig);
}

void continueHandler(int sig)
{
	printf("continue code:%d\n",sig);
}

void terminateHandler(int sig)
{
	printf("signal:%d\n",sig);
	exit(0);
}
