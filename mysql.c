#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include <errno.h>
MYSQL_RES *result;
MYSQL_ROW row;
int main()
{

	MYSQL mysql;
	mysql_init(&mysql);
	printf("begin mysql\n");
	if(!mysql_real_connect(&mysql,"127.0.0.1","root","1jackCsm*","laravel",3306,NULL,0)){
		printf("mysql connect faild %s,%d\n",strerror(errno),errno);
		printf(mysql_error(&mysql));
	}else{
		printf("connect success\n");

		printf("prepare execute sql\n");
		
		int res = mysql_query(&mysql,"SET NAMES UTF8");

		printf("res=%d\n",res);
		printf(mysql_error(&mysql));
		
		res = mysql_query(&mysql,"select id,name,email from users");
		printf("res=%d\n",res);
		printf(mysql_error(&mysql));
		result = mysql_store_result(&mysql);
		
		int num = mysql_num_rows(result);
		printf("num=%d\n",num);
		
		if(num){
			printf("--%3s--|--%8s--|--%20s--\n","id","name","email");
			while((row=mysql_fetch_row(result))){
				printf("%hd|%8s|%20s\n",*row[0],row[1],row[2]);
			}

		}else{
			printf("没有数据哦\n");
		}
		
		mysql_free_result(result);
		mysql_close(&mysql);
		
		
	}
	printf("hello\n");
	return 0;
}
