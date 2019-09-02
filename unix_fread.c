#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc,char *argv[])
{
	FILE *fp1,*fp2;

	char buf[1024];

	int n;

	if(argc<2){
		perror("the arg error\n");
	}

	if((fp1 = fopen(argv[1],"rb"))==NULL){
		perror("fail to pen source file\n");
		exit(1);
	}

	if((fp2 = fopen(argv[2],"wb"))==NULL){
		perror("fail to pen des file\n");
		exit(2);
	}

	while((n=fread(buf,sizeof(char),1024,fp1))>0){

		if(fwrite(buf,sizeof(char),n,fp2)==-1){
			perror("fail to write\n");
			exit(3);
		}
	}

	if(n==-1){
		perror("fail to read\n");
		exit(4);
	}

	fclose(fp1);
	fclose(fp2);
	
	return 0;
}
