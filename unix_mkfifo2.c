#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc,char *argv[])
{
	if(argc<2){
		fprintf(stderr,"useage:%s fileName and mode\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	int fd;

	if((fd = open(argv[1],O_RDONLY))<0){
		fprintf(stderr,"open failure\n");
		exit(EXIT_FAILURE);
	}

	char msg[1024];
	for(;;){
	while(read(fd,msg,strlen(msg))>0){
		printf("read content is %s\n",msg);
		memset(msg,'\0',sizeof(msg));
	}
	}

	close(fd);
	return 0;
}
