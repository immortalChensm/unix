#include <stdio.h>
#include <stdlib.h>

int main()
{
	char temp[] = "template-XXXXXX";

	int fd = mkstemp(temp);

	printf("fd=%d\n",fd);	

	write(fd,"hello,world",20);
	return 0;
}
