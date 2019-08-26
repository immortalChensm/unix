#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main()
{
	struct utsname name;
	uname(&name);

	printf("systemname:%s\n",name.sysname);
	printf("nodename:%s\n",name.nodename);
	printf("release:%s\n",name.release);
	printf("version:%s\n",name.version);
	printf("machine:%s\n",name.machine);
	return 0;
}
