#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int fileId,temp;

	char wbuf[15] = "this is a test!";

	//printf("%s",argv[1]);
	//
	fileId = open(argv[1],O_RDWR|O_CREAT,S_IRWXU);

	printf("%d\n",fileId);

	temp = write(fileId,wbuf,15);

	printf("%d\n",temp);

	close(fileId);

	return 0;
}
