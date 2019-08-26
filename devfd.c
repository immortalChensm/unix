#include <fcntl.h>
#include <string.h>
int main()
{
	//write(1,"hello",10);
	//int fd = open("/dev/fd/1",O_RDWR);
	int fd = open("/dev/stdout",O_RDWR);
	if(fd){
		write(fd,"hello,world",12);
	}else{
	//	write(1,"文件不存在",50);
	}


	//int input = open("/div/stdin",O_RDONLY);
	//int input = open();
	//if(input){

		char data[1024];
		int len = read(0,data,sizeof(data));
		write(1,data,len);
	//}else{
	//	char *data = "打印输入设备失败";
	//	write(1,data,strlen(data));
	//}
	return 0;
}
