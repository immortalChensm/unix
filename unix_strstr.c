#include <stdio.h>
#include <string.h>

int main()
{
	char *temp = "hello,world";

	char *temps;

	temps = strstr(temp,"hello");

	if(temps){
		printf("%s\n",temps);
	}else{
		printf("not found\n");
	}

	return 0;
}
