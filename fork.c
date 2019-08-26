#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("hello,world pid:%d,ppid:%d\n",getpid(),getppid());

	int rc = fork();

	if(rc<0){
		fprintf(stderr,"fork fail");
	}else if(rc==0){
		//printf("i am child pid:%d,ppid:%d\n",getpid(),getppid());
		 int i=0;
		 printf("child process start pid:%d\n",getpid());
		 while(i<10){
			i++;
			printf("child process pid:%d,i=%d\n",getpid(),i);
		 }
	}else{
		int wc = wait(NULL);

		printf("parent process start pid:%d\n",getpid());
                int j=0;
                while(j<10){
			j++;
			printf("parent process of pid=%d,wc=%d,rc=%d,j=%d\n",getpid(),wc,rc,j);
		}
	}

	printf("main process end pid:%d\n",getpid());

	exit(0);
}
