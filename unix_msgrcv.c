#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>
struct my_msg
{
	long int my_msg_type;

	char text[BUFSIZ];
}msgbuf;

int main(void)
{
	int runningFlg = 1;

	int msgid;

	long int msg_to_receive = 0;

	msgid = msgget((key_t)1234,0666|IPC_CREAT);

	if(msgid==-1){
		printf("msgget failed!\n");
		exit(1);
	}

	while(runningFlg==1){
		if(msgrcv(msgid,(void*)&msgbuf,BUFSIZ,msg_to_receive,0)==-1){
			perror("msgrcv failed!\n");
			exit(1);
		}

		printf("receive content :%s\n",msgbuf.text);

		if(strncmp(msgbuf.text,"end",3)==0){
			runningFlg = 0;
		}
	}

	if(msgctl(msgid,IPC_RMID,0)==-1){
		perror("msgctl IPC_RMID failed!\n");
		exit(1);
	}

	return 0;
}
