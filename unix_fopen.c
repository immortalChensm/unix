#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	FILE *fp;

	int flag;

	perror("hello,world");
	if(argc<=1){
		printf("useage:%s filename\n",argv[0]);
		return 1;
	}

	fp = fopen(argv[1],"ab");

	if(fp = NULL){
		printf("open file %s failed!\n",argv[1]);
		return 2;
	}

	printf("open file %s successed!\n",argv[1]);

	flag = fclose(fp);

	if(flag==0){
		printf("close file %s successed!\n",argv[1]);
		return 0;
	}else{
		printf("close file %s failed!\n",argv[1]);
		return 3;
	}
	return 0;
}
