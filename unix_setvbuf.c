#include <stdio.h>
#include <stdlib.h>

#define SIZE 512

int main(void)
{
	char buf[SIZE];
设置流的缓冲区，大小，类型_IOFBF _IOLBF _IONBF
	if(setvbuf(stdin,buf,_IONBF,SIZE)!=0){
		perror("stt stdin error!\n");
		exit(1);
	}

	printf("set stdin successful!\n");
	printf("stdin is");

	检测流的缓冲区类型
	if(stdin->_flags&_IO_UNBUFFERED){
		printf("unbuffered\n");
	}else if(stdin->_flags&_IO_LINE_BUF){
		printf("line-buffered\n");
	}else{
		printf("fully-buffered\n");
	}

	得到缓冲区的大小

	printf("buffer size is %d\n",stdin->_IO_buf_end-stdin->_IO_buf_base);

	printf("file discriptor is %d\n",fileno(stdin));

	if(setvbuf(stdin,buf,_IOFBF,SIZE)!=0){
		perror("error!\n");
		exit(1);
	}

	printf("ok,change successful!\n");
	printf("stdin is");

	if(stdin->_flags&_IO_UNBUFFERED){
		printf("unbuffered\n");
	}
	else if(stdin->_flags&_IO_LINE_BUF){
		printf("line-buffered\n");
	}else{
		printf("fully-buffered\n");
	}

	printf("buffer size is %d\n",stdin->_IO_buf_end-stdin->_IO_buf_base);

	printf("file discriptor is %d\n",fileno(stdin));

	return 0;
}
