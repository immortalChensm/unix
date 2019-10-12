#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#define DEF_PAGER "/bin/more"
#define MAXLINE 4096

int main(int argc,char *argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char *pager,*argv0;

	char line[MAXLINE];

	FILE *fp;

	if(argc!=2){
		perror("useage:pathname \n");
		exit(1);
	}
printf("argv[1]=%s\n",argv[1]);
	if((fp = fopen(argv[1],"r"))==NULL){
		printf("can't open %s\n",argv[1]);
		exit(1);
	}

	if(pipe(fd)<0){
		perror("pipe error");
		exit(0);
	}

	if((pid = fork())<0){
		perror("fork error");
		exit(0);
	}
	else if(pid>0){
		close(fd[0]);
		while(fgets(line,MAXLINE,fp)!=NULL){
			n = strlen(line);
			printf("读取的内容:%s\n",line);
			if(write(fd[1],line,n)!=n){
				perror("write error to pipe");
				exit(1);
			}
		}
		if(ferror(fp)){
			perror("fgets error");
			exit(1);
		}
		close(fd[1]);
		printf("父进程从文件里读取内容并写入管道中\n");
		if(waitpid(pid,NULL,0)<0){
			perror("waitpid error");
			exit(1);
		}
		exit(0);
	}else{
		close(fd[1]);

		//dup2(fd[0],STDOUT_FILENO);
		//

		char *bufs;
		int len1 = read(fd[0],bufs,MAXLINE);
		printf("read from fd[0] %s\n",bufs);

		if(fd[0]!=STDIN_FILENO){
			if(dup2(fd[0],STDIN_FILENO)!=STDIN_FILENO){
				perror("dup2 error to stdin");
				exit(1);
			}
			close(fd[0]);
		}

		printf("子进程把管道内容复制到标准输入描述符中\n");

		//fgets(line,MAXLINE,STDIN_FILENO);
		char *buf;
		int len = read(STDIN_FILENO,buf,MAXLINE);

		printf("line=%s\n",buf);

		char *msg;
		scanf("%s",msg);	

		printf("msg=%s\n",msg);
		if((pager = getenv("PAGER"))==NULL)
			pager = DEF_PAGER;
		if((argv0=strrchr(pager,'/'))!=NULL){
			argv0++;
		}else{
			argv0 = pager;

			printf("pager=%s,argv0=%s\n",pager,argv0);
			if(execl(pager,argv0,(char*)0)<0){
				printf("execl error for %s",pager);
				exit(1);
			}
		}
	}

	printf("end\n");

	exit(0);
}
