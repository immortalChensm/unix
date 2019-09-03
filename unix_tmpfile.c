#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	FILE *tempfp;

	char line[256];

	tempfp = tmpfile();

	if(tempfp == NULL){
		perror("tmpfile error!\n");
		return 1;
	}

	printf("opened a temporary file OK!\n");
	fputs("one line of output \n",tempfp);

	rewind(tempfp);

	if(fgets(line,sizeof(line),tempfp)==NULL){
		printf("fgets error!\n");
		return 2;
	}

	fputs(line,stdout);

	return 0;
}
