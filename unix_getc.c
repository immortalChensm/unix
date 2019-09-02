#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	int c;

	printf("pls enter some str,ctrl+d for stop\n");

	while((c=getc(stdin))!=EOF){
		if(putc(c,stdout)==EOF){
			perror("oupput error");
		}
	}

	if(ferror(stdin)){
		perror("input error");
	}

	return 0;
}
