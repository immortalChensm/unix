#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	if(argc<2){
		printf("参数错误\n");
		return EXIT_SUCCESS;
	}

	int pid = atoi(argv[1]);
	int sig = atoi(argv[2]);

	if(pid&&sig){
		int ret = kill(pid,sig);

		printf("ret=%d\n",ret);
	}else{
		printf("error\n");
	}

	return 0;
}
