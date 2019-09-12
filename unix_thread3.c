#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

void requestHandler(void *argv);
int main(int argc,char *argv[])
{

	if(argc<4){
		perror("useage:ip port method url");
		return 1;
	}
	const char *ip = argv[1];
	int port = atoi(argv[2]);
	pthread_t tid;
	struct sockaddr_in client;
	bzero(&client,sizeof(client));	
	inet_pton(AF_INET,ip,&client.sin_addr);
	client.sin_family = AF_INET;
	client.sin_port = htons(port);

	int sockfd = socket(PF_INET,SOCK_STREAM,0);
	
	char *url = argv[3];
	char *method = argv[4];	
	char start = atoi(argv[5]);
	char count = atoi(argv[6]);
	if(connect(sockfd,(struct sockaddr*)&client,sizeof(client))==0){
		printf("连接成功\n");
		int len=0;
		int ret;
		char request[2048];
		ret = snprintf(request,2048-1,"%s %s %s",method,url," HTTP/1.1\r\n");
		len+=ret;

		ret = snprintf(request+len,2048-len,"%s","accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n");
		len+=ret;

		ret = snprintf(request+len,2048-len,"%s","user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.86 Safari/537.36\r\n");

		len+=ret;

		ret = snprintf(request+len,2048-len,"%s","Content-Type: application/x-www-form-urlencoded\r\n");
		len+=ret;
		
		//ret = snprintf(request+len,2048-len,"Content-Length:%d\r\n",2048);
		//len+=ret;
		
		ret = snprintf(request+len,2048-len,"\r\n");
		len+=ret;

		
		snprintf(request+len,2048-len,"start=%d&count=%d&name=jack",start,count);


		printf("请求数据：%s\n",request);
		send(sockfd,request,strlen(request),0);

		char response[1024*4];

		recv(sockfd,response,sizeof(response),0);

	//	printf("%s\n",response);
	//
		pthread_create(&tid,NULL,(void *)(&requestHandler),response);
		sleep(1);
		
		
	}else{
		perror("连接失败");
	}

	close(sockfd);

	return 0;
}

void requestHandler(void *argv)
{
	pid_t pid;
	pthread_t tid;

	printf("pid %lu,tid %lx\n",getpid(),pthread_self());
	printf("%s\n",argv);

//	return ((void*)0);
}
