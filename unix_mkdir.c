#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int temp;

	if(argc!=2){
		perror("argc is wrong\n");
		return 2;
	}

	temp = mkdir(argv[1],S_IRWXU|S_IRGRP|S_IXOTH);
	if(temp == -1){
		printf("new dir error\n");
		return 3;
	}

	//temp = rmdir(argv[1]);
//
//	if(temp == 0){
//		printf("del done\n");
//	}

	return 0;
}
