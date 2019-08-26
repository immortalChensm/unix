#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	int num=3;
	
	switch(vfork()){

		case -1:
			exit(0);
		case 0:
			sleep(3);
			write(STDOUT_FILENO,"child executeing\n",20);
			num*=3;
			_exit(EXIT_SUCCESS);
		break;
		default:
			write(STDOUT_FILENO,"parent executeing\n",20);
			printf("num=%d\n",num);
			exit(EXIT_SUCCESS);
		break;
	}

	return EXIT_SUCCESS;
}
