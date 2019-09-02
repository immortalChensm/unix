#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	if(argc!=2){
		printf("argc error\n");
	}

	int temp = access(argv[1],F_OK);	

	if(temp==0){
		int removeId = remove(argv[1]);
		printf("removeId=%d\n",removeId);
	}else{
		printf("file not exists\n");
	}

	return 0;
}
