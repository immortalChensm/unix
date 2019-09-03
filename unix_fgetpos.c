#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int temp,seektemp,i,j;

	FILE *fp;

	fpos_t ps;

	char wbuf[17] = "this is a test!\r\n";

	if(argc!=2){
		printf("run error!\n");
		return 1;
	}

	fp = fopen(argv[1],"ab");
	for(i=0;i<10;i++){
		j = sizeof(wbuf)*(i+1);
		fseek(fp,j,SEEK_SET);
		temp = fputs(wbuf,fp);
		fgetpos(fp,&ps);

		printf("current file end position is %ld\n",ps);
	}

	fclose(fp);

	return 0;
}
