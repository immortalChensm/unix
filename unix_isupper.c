#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char c;

	while((c=getchar())!='\n'){
		if(isupper(c)){
			printf("[%c is an uppercase char \n]",c);
		}
		if(isalnum(c)){
			printf("是字母或是数字");
		}

		if(isdigit(c)){
			printf("是数字");
		}

		if(islower(c)){
			printf("是小写字母");
		}
	}
}
