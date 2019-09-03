#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("hello,world\n");

	fprintf(stdout,"hello,world\n");

	char s[100];

	sprintf(s,"age=%d\n",100);


	fputs(s,stdout);

	return 0;
}
