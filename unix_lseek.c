#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int temp,seektemp,i,j;

	int fileId;

	char wbuf[17] = "this is a test!\r\n";

	if (argc!=2){
		printf("run error!\n");
		return 1;
	}

	fileId = open(argv[1],O_RDWR|O_CREAT,S_IRWXU);
	temp = write(fileId,wbuf,sizeof(wbuf));

	seektemp = lseek(fileId,0,SEEK_CUR);

	printf("seektemp=%d\n",seektemp);

	for(i=0;i<10;i++){
		j = sizeof(wbuf)*(i+1);

		seektemp = lseek(fileId,j,SEEK_SET);

		printf("seektemp=%d\n",seektemp);

		temp = write(fileId,wbuf,sizeof(wbuf));

		
	}

	seektemp = lseek(fileId,0,SEEK_END);
	printf("seektemp=%d\n",seektemp);
	close(fileId);

	return 0;
}
