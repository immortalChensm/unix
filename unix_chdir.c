#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
int main(int argc,char *argv[])
{
	unsigned char temp;

	char npath[200];

	if(argc!=2){
		perror("argc is wrong\n");
		return 1;
	}

	temp = mkdir(argv[1],S_IRUSR|S_IWUSR|S_IXUSR);

	if(temp == -1){
		printf("create dir failed!\n");
	}

	temp = chdir(argv[1]);

	printf("%d\n",temp);

	if(getcwd(npath,200)==NULL){
		printf("getwd error\n");
	}
	else{
		printf("cwd=%s\n",npath);
	}

	temp = mkdir(argv[2],S_IRWXU|S_IRGRP|S_IXOTH);

	return 0;
}
