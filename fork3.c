#include <stdio.h>
#include <string.h>

int main()
{
	

	printf("master process of pid:%d\n",getpid());
	int i=0;
	for(i;i<1;i++){
		int wc = fork();

		if(wc==0){
			printf("i am %d child process (pid:%d)\n",i,getpid());
		}else if(wc<0){

		}else{
			printf("i am %d parent (pid:%d)\n",i,wc);
		}
	}

	printf("master process of end (pid:%d)\n",getpid());

	return 0;
}
