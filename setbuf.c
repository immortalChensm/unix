#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char buf[2];
int main()
{
	
	setbuf(stdout,NULL);

	puts("test-test-test-test");
	puts(buf);
	fflush(stdout);

	puts(buf);

	return 0;
}
