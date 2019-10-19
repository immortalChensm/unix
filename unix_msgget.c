#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	key_t key;

	int msqid;

	printf("enter the desired key in hex=");

	scanf("%x",&key);
	
	printf("\nkey=0X%x",key);

	if((msqid = msgget(key,IPC_CREAT|0666))==-1){
		perror("the msgget failed\n");
		exit(1);
	}

	printf("the megget successed:msqid=%d\n",msqid);

	exit(0);
}
