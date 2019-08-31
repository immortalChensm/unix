#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int temp;

	temp = open("unix_open.txt",O_RDWR|O_CREAT,S_IRWXU);

	printf("%d\n",temp);
	temp = close(temp);

	printf("%d\n",temp);
	return 0;
}
