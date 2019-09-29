#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define MAXLINE 4096

static void sigalrm(int);

int main(void)
{
	int n;
	char line[MAXLINE];

	if(signal(SIGALRM,sigalrm)==SIG_ERR){
		perror("signal sigalrm error");
	}

	alarm(1);

	if((n=read(STDIN_FILENO,line,MAXLINE))<0){
		perror("read error");
	}

	alarm(0);

	write(STDOUT_FILENO,line,n);

	exit(0);
}

static void sigalrm(int sig)
{
	time_t now;
	time(&now);
	struct tm *tm;
	tm = localtime(&now);
	system("clear");
	printf("定时时间到:%d\n",sig);
	printf("现在时间是：%d年%d月%d日 %d时%d分%d秒",1900+tm->tm_year,1+tm->tm_mon,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
	alarm(1);
}
