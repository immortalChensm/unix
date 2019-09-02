#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	if(argc!=2){
		printf("argc error\n");
		return 1;
	}

	int len = truncate(argv[1],3);

	printf("len=%d\n",len);

	return 0;
}
