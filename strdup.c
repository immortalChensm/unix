#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char *str = "php is best language";
	char *dest;

	dest = strdup(str);
	
	char *argv[] = {"al",NULL};
	execvp("ls",argv);
	printf("s=%s\n",dest);
	return 0;
}
