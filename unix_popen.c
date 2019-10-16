#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fp = NULL;
	char buf[1024]= "";

	fp = popen("ls -al","r");

	if(fp==NULL){
		perror("popen error!\n");
		return -1;
	}

	while(fgets(buf,sizeof(buf),fp)!=0){
		printf("%s\n",buf);
		memset(buf,'\0',sizeof(buf));
	}

	pclose(fp);

	return 0;
}
