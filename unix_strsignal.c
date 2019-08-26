#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void signalhandler(int sig)
{
//	char *sigstr = strsignal(sig);
//
	char *sigstr = (char*)malloc(100*sizeof(char));
	sigstr = strsignal(sig);
	printf("sig=%d,sigstr=%s\n",sig,sigstr);

	if(sig==2){
		printf("马上退出了哦\n");
		exit(EXIT_SUCCESS);
	}
}
int main()
{
	printf("hello,world\n");

	signal(SIGINT,signalhandler);
	pid_t pid = getpid();

	int uid = getuid();

	printf("pid=%d,uid=%d\n",pid,uid);

	int i;
	for(i=0;;i++){
		printf("i=%d\n",i++);
	}

	return EXIT_SUCCESS;
}


