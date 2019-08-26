#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	
	char a[10];
	int size = snprintf(a,10,"%s","china");
	int i;
	for(i=0;i<10;i++){
		printf("%c,%d\n",a[i],size);
	}
	printf("写了%d个内存,还剩%d个\n",size,10-size);
	int len=0;
	len+=size;
	size = snprintf(a+len,10-size,"%s","ok");
	
	for(i=0;i<10;i++){
		printf("%c\n",a[i]);
	}
	len+=size;
	printf("写了%d个内存，还剩下%d个\n",len,10-len);
	return 0;
}
