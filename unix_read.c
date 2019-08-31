#include <stdio.h>
#include <fcntl.h>

#define PERMS 0666
#define DUMMY 0
#define MAXSIZE 1024

int main(int argc,char *argv[])
{
	int sourceFileId,targetFileId;

	int readNo = 0;

	char wbuf[MAXSIZE];

	if (argc!=3){
		printf("run error\n");
		return 1;
	}

	if ((sourceFileId = open(argv[1],O_RDONLY,DUMMY))==-1){
		printf("source file open error!\n");
		return 2;
	}

	if ((targetFileId=open(argv[2],O_RDWR|O_CREAT,PERMS))==-1){
		printf("target file open error\n");
		return 3;
	}

	while((readNo=read(sourceFileId,wbuf,MAXSIZE))>0){
		if(write(targetFileId,wbuf,readNo)!=readNo){
			printf("targe file write error!\n");

			return 4;
		}
	}

	close(sourceFileId);
	close(targetFileId);

	return 0;
}
