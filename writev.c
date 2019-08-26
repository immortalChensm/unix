#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <unistd.h>
int main()
{
	char *data="hello";
	char *data1="word";

	struct iovec iov[2];
	iov[0].iov_base=data;
	iov[0].iov_len = strlen(data);

	iov[1].iov_base = data1;
	iov[1].iov_len = strlen(data1);

	int size = writev(STDOUT_FILENO,iov,2);

	printf("iov size %d\n",size);
	return 0;
}
