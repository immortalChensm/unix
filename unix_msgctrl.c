#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>

#define TEXT_SIZE 512

struct msgbuf
{
	long mtype;
	char mtext[TEXT_SIZE];
};

int main(int argc,char **argv)
{
	int msqid;

	struct msqid_ds info;
	struct msgbuf buf;
	struct msgbuf buf1;

	int flag;

	int sendlength,recvlength;

	msqid = msgget(IPC_PRIVATE,0666);
	if(msqid<0){
		perror("get ipc_id error\n");
		exit(1);
	}

	buf.mtype = 1;

	strcpy(buf.mtext,"this is a test!");

	sendlength = sizeof(struct msgbuf)-sizeof(long);

	flag = msgsnd(msqid,&buf,sendlength,0);

	if(flag<0){
		perror("send message error");
		exit(1);
	}

	buf.mtype = 3;
	strcpy(buf.mtext,"this is a anothor test!");

	sendlength = sizeof(struct msgbuf)-sizeof(long);

	flag = msgsnd(msqid,&buf,sendlength,0);
	if(flag<0){
		perror("send message error");
		exit(1);
	}

	flag = msgctl(msqid,IPC_STAT,&info);

	if(flag<0){
		perror("get message status error");
		exit(1);
	}

	printf("uid:%d,gid=%d,cuid=%d,cgid=%d\n",info.msg_perm.uid,info.msg_perm.gid,info.msg_perm.cuid,info.msg_perm.cgid);

	system("ipcs -q");

	recvlength = sizeof(struct msgbuf)-sizeof(long);
	memset(&buf1,0x00,sizeof(struct msgbuf));

	flag = msgrcv(msqid,&buf1,recvlength,3,0);

	if(flag<3){
		perror("recv message error");
		exit(1);
	}

	printf("type=%d,message=%s\n",buf1.mtype,buf1.mtext);

	flag = msgctl(msqid,IPC_RMID,NULL);

	if(flag<0){
		perror("rm message queue error");
		exit(1);
	}

	system("ipcs -q");

	return 0;
}
