#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
void sighandler(int sig)
{
	printf("进程即将终止\n");
	exit(EXIT_SUCCESS);
}
int main()
{
	if(signal(SIGINT,sighandler)==SIG_ERR){
		exit(EXIT_FAILURE);
	}

	//char *filePid = "/proc/";
	//char pid = getpid();
	//strcat(filePid,(char*)&pid);
	//printf("filePid:%s\n",filePid);
	//int fd = open(filePid);
	int i;
	for(i=0;;i++){

	//	if(fd>0){
	//		char content[1024];
	//		int len = read(fd,content,1024);
	//		printf("进程状态：%s,%d\n",content,len);
//
//		}else{
//			printf("open file error fd=%d\n",fd);
//		}
		
		int ret = kill(9325325,0);
		printf("进程状态：ret=%d\n",ret);
		printf("i=%d\n",i);
	}

	//close(fd);

	return EXIT_SUCCESS;
}
