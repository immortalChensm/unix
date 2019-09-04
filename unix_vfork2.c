#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int count=1;

	int child;

	printf("before create son,the father's count is %d\n",count);

	if(!(child=vfork())){
		int i;

		for(i=0;i<100;i++){
			printf("this is son,the i is %d\n",i);
			if(i == 70){
				exit(0);
			}
		}
		printf("this is son,his pid is:%d,and the count is :%d\n",getpid(),++count);
		exit(1);
	}else{
		printf("fater son,this is father,his pid is :%d and the count is :%d and the child is:%d\n",getpid(),count,child);
	}

	return 0;
}
