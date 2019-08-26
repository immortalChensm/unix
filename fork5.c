#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int rc = fork();

	if(rc <0){
		fprintf(stderr,"fork faild\n");
		exit(1);
	}else if(rc ==0){
		close(STDOUT_FILENO);
		open("fork5s.txt",O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);

		char *args[3];
		args[0] = strdup("wc");
		args[1] = strdup("test.txt");
		args[2] = NULL;

		execvp(args[0],args);

		
	}else{
		int wc = wait(NULL);
	}

	return 0;
}
