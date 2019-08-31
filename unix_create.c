#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int temp;

	if(argc!=2){
		printf("error\n");
		return 1;
	}

	temp = creat(*(argv+1),S_IRWXU);

	printf("%d\n",temp);

	return 0;
}
