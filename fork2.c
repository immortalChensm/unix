#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
int main()
{
	printf("hello,world (pid:%d)\n",getpid());

	int rc = fork();
	if(rc<0){
		fprintf(stderr,"fork failied\n");
		exit(1);
	}else if(rc == 0){
		printf("hello,i am child (pid:%d),(ppid:%d)\n",getpid(),getppid());	

		char *myargs[3];

		myargs[0] = strdup("wc");
		myargs[1] = strdup("test.txt");
		myargs[2] = NULL;

		//execvp(myargs[0],myargs);

		int rc1 = fork();

		if(rc1==0){
			printf("hello,i am child child (pid:%d),(ppid:%d)",getpid(),getppid());

			
		}else if(rc1<0){
			fprintf(stderr,"fork child faild\n");
		}else{
			printf("hello,i am child parent (pid:%d),(ppid:%d)",getpid(),getppid());
		}

		printf("this should't print out\n");
	}else{
		int wc = wait(NULL);
		//int wc = 1;
		//exit(1);
		printf("hello,i am parent of %d(wc:%d) (pid:%d),(ppid:%d)\n",rc,wc,(int)getpid(),getppid());
	}

	printf("end pid:%d,(ppid:%d)\n",getpid(),getppid());

	return 0;
}
