#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <error.h>
//https://www.cnblogs.com/kele-dad/p/10301066.html
struct my_msg{
	long int my_msg_type;
	char text[BUFSIZ];
}msgbuf;

int main(void)
{
	int runningFlg = 1;

	int msgid;

	msgid = msgget((key_t)1234,0666|IPC_CREAT);

	if(msgid==-1){
		perror("msgget failed!\n");
		exit(1);
	}

	while(runningFlg == 1){
		printf("type data:");
		fgets(msgbuf.text,BUFSIZ,stdin);

		msgbuf.my_msg_type = 1;

		if(msgsnd(msgid,(void*)&msgbuf,BUFSIZ,0)==-1){//0阻塞，IPC_NOWAIT非阻塞
			perror("msgsnd failed!\n");
			exit(1);
		}

		if(strncmp(msgbuf.text,"end",3)==0){
			runningFlg = 0;
		}
	}

	return 0;
}
