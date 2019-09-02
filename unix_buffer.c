#include <stdio.h>
#include <stdlib.h>

#if defined(MACOS)

#define _IO_UNBUFFERED __SNBF
#define _IO_LINE_BUF __SLBF
#define _IO_file_flags _flags

#define BUFFERSZ(fp) (fp)->_bf._size
#else
#define BUFFERSZ(fp) ((fp)->_IO_buf_end-(fp)->_IO_buf_base)
#endif  

void pr_stdio(const char *,FILE *);

int main(void)
{
	FILE *fp;

	printf("pls enter some str\n");
	if (getchar()==EOF){
		perror("getchar error");
	}

	fputs("one line to standard error\n",stderr);
	pr_stdio("stdin",stdin);
	pr_stdio("stdout",stdout);
	pr_stdio("stderr",stderr);

	if(getc(fp)==EOF){
		perror("getc error");
	}
	pr_stdio("/home/demo.php",fp);
	return 0;
}

void pr_stdio(const char *name,FILE *fp)
{
	printf("stream =%s,",name);

	if(fp->_IO_file_flags&_IO_UNBUFFERED){
		printf("unbuffered");
	}
	else if(fp->_IO_file_flags&_IO_LINE_BUF){
		printf("line buffered");
	}else{
		printf("fully buffered");
	}
	printf(",buffer size=%d\n",BUFFERSZ(fp));
}
