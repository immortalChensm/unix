#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int temp;

	if(argc!=3){
		perror("arg num is wrong\n");
		return 1;
	}

	temp = rename(argv[1],argv[2]);

	if(temp == -1){
		perror("rename error\n");
	}else{
		printf("rename ok\n");
	}

	return 0;
}
