#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define MAX 65536

int main(int argc,char *argv[])
{
	int fd,n;
	char buf[MAX];

	if(argc<2){
		fprintf(stderr,"useage:%s argv[1]\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if(mkfifo(argv[1],0666)<0&&!errno!=EEXIST){
		fprintf(stderr,"mkfifo failure %s \n",strerror(errno));
		exit(EXIT_FAILURE);
	}

	if((fd = open(argv[1],O_WRONLY))<0){
		fprintf(stderr,"open %s failure %s\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("open fifo success\n");
	
	while(1){
		printf(">");
		scanf("%s",buf);

		n = write(fd,buf,strlen(buf));

		printf("write %d bytes %s\n",n,buf);

		memset(buf,'\0',sizeof(buf));
	}

	exit(EXIT_SUCCESS);
}
