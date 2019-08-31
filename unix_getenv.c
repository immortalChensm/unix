#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *p;

	if((p = getenv("USER"))){
		printf("user:%s\n",p);
	}

	return 0;
}
