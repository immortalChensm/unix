#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("master process (pid:%d)\n",getpid());

	int rc = fork();
	if(rc==0){
		printf("i am child process (pid:%d)\n",getpid());

		char *args[3];
		args[0] = strdup("wc");
		args[1] = strdup("test.txt");
		args[2] = NULL;

		//execvp(args[0],args);
		int i = 0;
		while(1){
			i++;
			printf("i am child now num is %d\n",i);
		}

		printf("end child\n");
	}else if(rc!=-1){
		//printf("i am parent process (pid:%d)\n",getpid());
		int i=20;
		while(1){
			i++;
			printf("i am parent process now num is %d\n",i);
		}
	}

	printf("end process (pid:%d)\n",getpid());

	return 0;
}
