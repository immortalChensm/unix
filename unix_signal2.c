#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void intfunc(int signum);
void exitfunc(int signum);

int main()
{
	char buffer1[100],buffer2[100];

	int i;

	if((signal(SIGINT,intfunc))){
		printf("could't register signal handler for SIGINT!\n");
		exit(1);
	}

	if((signal(SIGTSTP,intfunc))){
		printf("could't register signal handler for SIGTSTP\n");
		exit(1);
	}

	if((signal(SIGTERM,exitfunc))){
		printf("could't register signal handler for SIGTEM!\n");
	}

	printf("pid of this process:%d\n",getpid());

	while(1){
		printf("please input:\n");

		fgets(buffer1,sizeof(buffer1),stdin);

		for(i=0;i<100;i++){
			if(buffer1[i]>=97&&buffer1[i]<=122){
				buffer2[i]= buffer1[i]-32;
			}else{
				buffer2[2] = buffer1[i];
			}
		}

		printf("your input is :%s\n",buffer2);
	}
	exit(0);
}

void intfunc(int sig){
	printf("catch signal %d\n",sig);
}

void exitfunc(int sig)
{
	printf("signal SIGTERM\n");
	exit(0);
}
