#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
int main()
{
	struct stat st;
	
	stat("file.c",&st);

	printf("uid=%d,gid=%d\n",st.st_uid,st.st_gid);
	printf("st_size=%d,atime=%d,mtime=%d,ctime=%d\n",st.st_size,st.st_atime,st.st_mtime,st.st_ctime);

	struct tm *now_tm;
	now_tm = localtime(&st.st_mtime);
	printf("m_time=%d-%d-%d\n",1900+now_tm->tm_year,now_tm->tm_mon+1,now_tm->tm_mday);

	if(S_ISREG(st.st_mode)){
		printf("常规文件\n");
	}
	return 0;
}
