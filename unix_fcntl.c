#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int val;

	if(argc!=2){
		printf("input argc error\n");
	}

	if((val = fcntl(atoi(argv[1]),F_GETFL,0))<0){
		printf("fcntl error for fd%d,",atoi(argv[1]));
	}
	switch(val &O_ACCMODE){
		case O_RDONLY:
			printf("read only\n");
		break;
		case O_WRONLY:
			printf("write only\n");
		break;

		case O_RDWR:
			printf("read write\n");
		break;
		default:
			printf("unknown access mode\n");
	}

	if(val&O_APPEND){
		printf(",append\n");
	}
	if(val &O_NONBLOCK){
		printf(",nonblocking\n");
	}

	#if defined(O_SYNC)
		if(val&O_SYNC){
			printf(",synchronous writes\n");
		}
	#endif  

	#if !defined(_POSIX_C_SOURCE)&&defined(O_FSYNC)  
		if(val&O_FSYNC){
			printf(",synchronous writes");
		}
	#endif  
		putchar('\n');
		return 0;
}
