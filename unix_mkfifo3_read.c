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
		printf("useage:%s argv[1]\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if(mkfifo(argv[1],0666)<0&&errno!=EEXIST){
		fprintf(stderr,"mkfifo failure %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}

	if((fd = open(argv[1],O_RDONLY))<0){
		fprintf(stderr,"open %s failure %s\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("read success\n");

	while(1){
		//printf(">");

		//scanf("%d",&n);

		n = read(fd,buf,sizeof(buf));

		if(n){

			printf("read %d bytes %s\n",n,buf);

			memset(buf,'\0',sizeof(buf));
		}
	}
	
	exit(EXIT_SUCCESS);
	
}
