#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	printf("the current process id is %d\n",getpid());
	printf("the father process id is %d\n",getppid());

	printf("the user true id is %d\n",getuid());
	printf("the valid user id is %d\n",geteuid());

	printf("the group id is %d\n",getgid());
	printf("the valid group id is %d\n",getegid());

	return 0;
}
