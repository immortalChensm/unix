#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	struct stat statbuf;

	if(stat("foo")<0){
		printf("stat error for foo");
	}

	if(chmod("foo",(statbuf.st_mode&~S_IXGRP|S_ISGID)<0)){
		printf("chod error for foo");
	}

	if(chmod("bar",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0){
		printf("chmod error for bar");
	}

	return 0;
}
