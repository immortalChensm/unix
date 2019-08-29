#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t timetemp;

	char *wday[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

	struct tm *p;

	time(&timetemp);

	printf("%s",asctime(gmtime(&timetemp)));

	p = localtime(&timetemp);

	printf("%d:%d:%d\n",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday);

	printf("%s %d:%d:%d\n",wday[p->tm_wday],p->tm_hour,p->tm_min,p->tm_sec);

	printf("%d\n",timetemp);

	printf("%d",gmtime(&timetemp));
	return 0;
}
