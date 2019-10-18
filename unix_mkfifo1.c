#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
int main(int argc,char *argv[])
{
	if(argc<2){
		fprintf(stderr,"useage:%s argv[1]\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if(mkfifo(argv[1],0666)<0 && errno!=EEXIST){
		fprintf(stderr,"fail to mkfifo\n");
		exit(EXIT_FAILURE);
	}

	int fd;
	if((fd = open(argv[1],O_WRONLY))<0){
		fprintf(stderr,"fail to pen %s:%s\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	printf("open for read success.\n");
	int ret=0;

	for(;;){
		char *msg = "hi,i am a phper\n";
		ret = write(fd,msg,strlen(msg));
		printf("write %d bytes\n",ret);
	}

	return 0;

	
}
