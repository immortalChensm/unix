#include <fcntl.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	int temp;

	if(argc!=2){
		printf("run error\n");
		return 1;
	}

	temp = access(argv[1],F_OK);

	if(temp == -1){
		printf("file is not exist!\n");
		return 2;
	}
	temp = access(argv[1],R_OK);

	if(temp==0){
		printf("file can be read!\n");
	}else{
		printf("file can not be read!\n");
	}

	temp = access(argv[1],W_OK);

	if(temp == 0){
		printf("file can be write!\n");
	}else{
		printf("file can not be write!\n");
	}

	temp = access(argv[1],X_OK);

	if(temp==0){
		printf("file can be run!\n");
	}else{
		printf("file can not be run!\n");
	}

	return 0;
}
