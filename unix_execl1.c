#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;

	printf("this is a test for exec series function\n");

	if(fork()==0){
	//	execl("/bin/date","/bin/date",(char*)0);
	
		//execl("/bin/ls","/bin/ls","-al");
		//execl("/home/soft/php/bin/php","/home/soft/php/bin/php","-v");
		execl("/bin/curl","/bin/curl","http://www.baidu.com");

		exit(0);
	}else{
		sleep(2);
	}
	exit(0);
}
