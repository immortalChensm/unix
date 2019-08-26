#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	
	printf("master process (pid:%d)\n",getpid());
	int fd[2];
	int ret = pipe(fd);

//	write(stdout,ret,strlen(ret));
	printf("ret=%d\n",ret);
	char buffer[128];
	int rc = fork();

	if(rc<0){
		printf("fork error\n");
	}else if(rc==0){
		
		int size = read(fd[0],buffer,128);
		printf("我是子进程 %d 接受父进程的数据为 %s,size=%d\n",getpid(),buffer,size);

		printf("尝试向父进程写数据:\n");
		char *data = "我是儿子";
		write(fd[1],data,strlen(data));
	}else{

		printf("parent process %d write data:hello,world\n",getpid());
		write(fd[1],"hello,world",strlen("hello,world"));

		wait();

		printf("尝试从子进程接受数据:\n");
		char data[100];
		int size = read(fd[0],data,100);
		if(size){
			printf("读取到子进程的数据啦：\n");
			printf("%s\n",data);
		}else{
			printf("没有读取到子进程的数据\n");
		}
	}

	printf("end process (pid:%d)\n",getpid());

	return EXIT_SUCCESS;
}
