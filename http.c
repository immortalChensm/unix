#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <assert.h>
#include <errno.h>
#include <mysql.h>
#include <libgen.h>
MYSQL mysql;
MYSQL_RES *result;
MYSQL_ROW row;
void DB(int );
int main(int argc,char *argv[])
{
	if(argc<2){
		printf("useage:%s ip and port\n",basename(argv[0]));
	}

	const char *ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));

	address.sin_family = AF_INET;

	address.sin_port = htons(port);
	inet_pton(AF_INET,ip,&address.sin_addr);

	int sockfd = socket(PF_INET,SOCK_STREAM,0);
	assert(sockfd>=0);

	int ret = bind(sockfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret = listen(sockfd,5);

	assert(ret!=-1);

	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	socklen_t client_len = sizeof(client);

	mysql_init(&mysql);

	if(!mysql_real_connect(&mysql,"localhost","root","1jackCsm*","laravel",3306,NULL,0)){
		printf("mysql connect faild\n");
		printf(mysql_error(&mysql));

		exit(0);
	}else{
		printf("connect success\n");
		int ret = mysql_query(&mysql,"SET NAMES UTF8");
	}

	while(1){

	 int connfd = accept(sockfd,(struct sockaddr*)&client,&client_len);
	 if(connfd>0){
		
		char response[256]="HTTP/1.1\0200\0OK\r\n";
		char header[256] = "Content-Type:text/html\r\nServer:最吊的服务器\r\n";

		write(connfd,response,strlen(response),0);
		write(connfd,header,strlen(header),0);

		char *line = "\r\n\r\n";
		write(connfd,line,strlen(line),0);
		
		DB(connfd);

		close(connfd);
	 }
	}
	
	mysql_free_result(result);
	mysql_close(&mysql);

	close(sockfd);
	return EXIT_SUCCESS;
}

void DB(int connfd)
{
	int ret = mysql_query(&mysql,"SELECT name,email FROM users");
	printf("res=%d\n",ret);
	printf(mysql_error(&mysql));

	result = mysql_store_result(&mysql);
	int num = mysql_num_rows(result);
	if(num){
		char data[1024*4];
		strcpy(data,"<html><meta charset='utf8'><body>");
		while((row=mysql_fetch_row(result))){
			strcat(data,row[0]);
			strcat(data,row[1]);
			//write(connfd,data,strlen(data),0);
			
		}

	
		strcat(data,"</body></html>");

		write(connfd,data,strlen(data),0);
	
}	}
