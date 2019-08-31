#include <stdio.h>
#include <fcntl.h>
#include <utime.h>

int main(int argc,char *argv[])
{
	int i,fd;

	struct stat statbuf;

	struct utimbuf timebuf;

	if(stat(argv[1],&statbuf)<0){
		printf("stat error\n");
		return 1;
	}
	
	if((fd = open(argv[1],O_RDWR|O_TRUNC))<0){
		printf("open error\n");
		return 2;
	}

	close(fd);

	timebuf.actime = statbuf.st_atime;

	timebuf.modtime = statbuf.st_mtime;

	if(utime(argv[1],&timebuf)<0){
		printf("reset time error\n");
	}
	return 0;
}
