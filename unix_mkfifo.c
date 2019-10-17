#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <pthread.h>
pthread_mutex_t mutex;

pthread_key_t key;

struct keyData{
	pid_t pid;
	pthread_t tid;
	void *data;
} keyData;
void *talk(void *parm)
{

	pthread_mutex_lock(&mutex);
	pthread_t tid;
	tid = pthread_self();
	pid_t pid;
	pid = getpid();
	while(1){
	
		printf("pid=%d tid=%d they talk %s\n",pid,tid,(char*)parm);
		
		keyData.pid = pid;
		keyData.tid = tid;
		keyData.data = parm;	
		pthread_setspecific(key,(struct keyData*)(&keyData));
		pthread_getspecific(key);
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
}

void *say(void *word)
{
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	pthread_mutex_lock(&mutex);
	while(1){
		printf("pid=%d tid=%d say %s\n",pid,tid,(char*)word);
		

		keyData.pid = pid;
		keyData.tid = tid;
		keyData.data = word;
		pthread_setspecific(key,(struct keyData*)(&keyData));
		pthread_getspecific(key);

		sleep(1);
		pthread_mutex_unlock(&mutex);
	}

}

void doing(struct keyData *data)
{
	//data = (struct keyData*)data;
	printf("pid %d tid %d doing %s\n",data->pid,data->tid,data->data);
}
int main(int argc,char *argv[])
{
	int fd;

	if(argc<2){
		fprintf(stderr,"useage:%s argv[1]\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if(mkfifo(argv[1],0666)<0 && errno!=EEXIST){
		fprintf(stderr,"fail to mkfifo %s:%s\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}

	pthread_key_create(&key,(void*)(&doing));
	pthread_t tid1,tid2;
	pthread_mutex_init(&mutex,NULL);
	int ret = pthread_create(&tid1,NULL,talk,(char*)("hello,world"));
	
	printf("ret=%d\n",ret);
	pthread_create(&tid2,NULL,say,(void*)("php is best"));

	
	if((fd = open(argv[1],O_WRONLY))<0){
		fprintf(stderr,"fail to open %s:%s\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("open for write success\n");
	pthread_mutex_destroy(&mutex);
	pthread_key_delete(key);
	return 0;
}
