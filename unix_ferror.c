#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int i;
	
	FILE *fp;

	if(argc<=1){
		printf("useage:%s file \n",argv[0]);
		exit(0);
	}

	fp = fopen(argv[1],"w");

	fgetc(fp);

	printf("%d\n",ferror(fp));

	fputs("abcdefgh",fp);

	fclose(fp);

	fp = fopen(argv[1],"r");

	fseek(fp,0,SEEK_END);

	fgetc(fp);

	if(feof(fp)){
		printf("file end\n");
	}

	clearerr(fp);

	printf("%d %d\n",ferror(fp),feof(fp));
	fclose(fp);
	return 0;
}
