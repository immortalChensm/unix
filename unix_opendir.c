#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
static int getFileTime(const char *fileName)
{
	struct stat statbuf;

	if(stat(fileName,&statbuf)==-1){
		printf("get stat error on%s\n",strerror(errno));
		//return -1;
	}
	if(S_ISDIR(statbuf.st_mode))return 1;
	if(S_ISREG(statbuf.st_mode)){
		printf("%s size:%ld bytes\tmodified at %s\n",fileName,statbuf.st_size,ctime(&statbuf.st_mtime));
	}
	return 1;
}
int main(int argc,char *argv[])
{
	DIR *dirp;
	struct dirent *direntp;

	char buf[1024];

	if(argc!=2){
		printf("usage:%s filename\n\a",argv[0]);
		return 1;
	}

	if((dirp = opendir(argv[1]))==NULL){
		printf("open directory %s error:%s\n",argv[1],strerror(errno));
		return 2;
	}

	while((direntp = readdir(dirp))!=NULL){
		printf("name=%s\n",direntp->d_name);
		sprintf(buf,"%s/%s",argv[1],direntp->d_name);
		int st = getFileTime(buf);
		printf("st=%d\n",st);
	}

	closedir(dirp);

	return 0;
}
