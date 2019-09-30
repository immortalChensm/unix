#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static void sig_quit(int);

int main()
{
	sigset_t newmask,oldmask,pendmask;

	signal(SIGQUIT,sig_quit);

	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);

	sigprocmask(SIG_BLOCK,&newmask,&oldmask);

	sleep(5);

	sigpending(&pendmask);

	if(sigismember(&pendmask,SIGQUIT)){
		printf("当前sigquit信号阻塞存于未决集");
	}

	sigprocmask(SIG_SETMASK,&oldmask,NULL);

	printf("SIGQUIT unblocked\n");
	sleep(5);
	exit(0);
}

static void sig_quit(int sig)
{
	printf("catch SIGQUIT\n");
	if(signal(SIGQUIT,SIG_DFL)==SIG_ERR){
		perror("can't reset SIGQUIT");
	}
}
