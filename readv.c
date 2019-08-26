#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/uio.h>
#include <stdlib.h>

int main()
{
	char data1[10];
	char data2[10];

	struct iovec iov[2];
	iov[0].iov_base = data1;
	iov[0].iov_len = sizeof(data1)-1;
	iov[1].iov_base = data2;
	iov[1].iov_len = sizeof(data1)-1;

	int size = readv(STDIN_FILENO,iov,2);

	printf("size=%d\n",size);
	printf("data1=%s\n",data1);
	printf("data2=%s\n",data2);
	return 0;
}
