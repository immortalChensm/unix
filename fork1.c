#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("start master process pid:%d,parent pid:%d\n",getpid(),getppid());

	int rc = fork();
	if(rc<0){
		fprintf(stderr,"fork fail");
	}else if(rc==0){
		
		printf("child process of pid:%d,parent process of pid:%d\n",getpid(),getppid());	
	}else{
		//exit(0);
		int pid = wait(NULL);
		printf("parent process of pid:%d,parent process of pid:%d,waitpid:%d\n",getpid(),getppid(),pid);

		printf("parent show hello,world\n");
	}

	printf("end master process pid:%d,parent pid:%d\n,rc:%d",getpid(),getppid(),rc);

	int i=0;
	for(i;i<5;i++){
		printf("i=%d\n",i);
	}
	return 0;
}
