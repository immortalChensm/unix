#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	struct timeval time1,time2;

	struct timezone timez;

	gettimeofday(&time1,&timez);

	printf("tv_sec:%d\n",time1.tv_sec);

	printf("tv_usec:%d\n",time1.tv_usec);

	printf("tz_minuteswest:%d\n",timez.tz_minuteswest);

	printf("tz_dsttime:%d\n",timez.tz_dsttime);

	gettimeofday(&time2,&timez);

	printf("time2_usec-time1.usec:%d\n",(time1.tv_usec-time2.tv_usec));

	return 0;
}
