#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char **argv)
{
	struct stat stat1;

	if(argc!=2){
		printf("useage:ftok pathname");
		exit(1);
	}

	stat(argv[1],&stat1);

	printf("st_dev:%lx,st_ino:%lx,key:%x\n",stat1.st_dev,stat1.st_ino,ftok(argv[1],0x579));
	
	printf("st_dev:%lx,st_ino:%lx,key:%x\n",stat1.st_dev,stat1.st_ino,ftok(argv[1],0x118));

	printf("st_dev:%lx,st_ino:%lx,key:%x\n",stat1.st_dev,stat1.st_ino,ftok(argv[1],0x123));

	return 0;
}
