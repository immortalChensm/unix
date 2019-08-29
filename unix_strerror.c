#include <string.h>
#include <stdio.h>
#include <errno.h>
/**
 *linux 的出错处理  
  linux 把出错信息都定义为常量并放在了errno.h文件里
 * */
int main(int artc,char *argv[])
{
	fprintf(stderr,"EACCESS:%s\n",strerror(EACCES));

	errno = ENOSPC;
	perror(argv[0]);

	return 0;
}
