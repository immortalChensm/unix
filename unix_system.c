#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
int main(void)
{
	int status;

	if((status=system("date"))>0){
		perror("system error.\n");
		exit(0);
	}

	return 0;

	
}
