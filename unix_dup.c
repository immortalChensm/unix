#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int fileId;

	if(argc!=2){
		printf("arg error\n");
		return 1;
	}

	if((fileId = open(argv[1],O_WRONLY|O_CREAT|O_APPEND,0644))==-1){
		printf("open %s error\n",argv[1]);
		return 2;
	}

	printf("the old fileId is %d\n",fileId);
	write(fileId,"hello,world\n",12);
	if(fileId = dup(fileId)==-1){
		printf("dup error\n");
		return 3;
	}
	//lseek(fileId,12,SEEK_SET);
	write(fileId,"china\n",6);
	printf("dup call successed!\n");
	printf("the new fileId is %d\n",fileId);



	close(fileId);

	return 0;
}
