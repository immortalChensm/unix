#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void DealTime(int sig)
{
	struct timeval tp;
	struct tm *tm;

	gettimeofday(&tp,NULL);
	tm = localtime(&tp.tv_sec);

	printf("sec=%ld\n",tp.tv_sec);

	printf("usec=%ld\n",tp.tv_usec);

	printf("%d-%d-%d%d:%d:%d\n",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
}
static void InitTime(int tv_sec,int tv_usec)
{
	struct itimerval value;
	signal(SIGALRM,DealTime);
	value.it_value.tv_sec = tv_sec;
	value.it_value.tv_usec = tv_usec;
	value.it_interval.tv_sec = tv_sec;
	value.it_interval.tv_usec = tv_usec;

	setitimer(ITIMER_REAL,&value,NULL);
}
int main()
{
	InitTime(1,0);

	while(1){};
	exit(0);
}
