#include <signal.h>
#include <stdio.h>
#include <unistd.h>

sigset_t s,p,old;
//static struct sigaction act;
//sigemptyset(&act.sa_mask);

int flag=0;
void printsigset(const sigset_t *set)
{
	int i;
	for(i=1;i<32;i++){
		if(sigismember(set,i)==1){
			putchar('1');
		}else{
			putchar('0');
		}
	}
	puts("\n");
}

void sigHandler(int sig)
{
	printf("抓住某个信号：%d\n",sig);
}

static void alarmHandler(int sig)
{
	printf("时间到了，准备解除阻塞\n");
	//sigprocmask(SIG_UNBLOCK,&s,NULL);
	//sigprocmask(SIG_SETMASK,&s,)i
	//sigdelset(&act.sa_mask,SIGINT);
	flag = 1;
}
int main(void)
{
	//sigset_t s,p;

	sigemptyset(&s);

	sigaddset(&s,SIGINT);
	signal(SIGINT,sigHandler);
	signal(SIGALRM,alarmHandler);
	sigprocmask(SIG_BLOCK,&s,NULL);//阻塞信号
	//
	static struct sigaction act;
//sigemptyset(&act.sa_mask);
//	sigaddset(&act.sa_mask,SIGINT);
//	act.sa_handler = sigHandler;
//	sigaction(SIGINT,&act,NULL);
	alarm(20);
	while(1){
		sigpending(&p);//获取未决信号集

		printsigset(&p);

		//printf("打印了未决信号集\n");
		sleep(1);
		//printf("时间到了，解除阻塞操作\n");

		//sigprocmask(SIG_UNBLOCK,&s,NULL);//解除阻塞集
		if(flag){
			//sigdelset(&act.sa_mask,SIGINT);
			sigprocmask(SIG_SETMASK,&old,NULL);
		}
	}

	return 0;
}
