#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

typedef unsigned int u8;
typedef unsigned long int u16;

#define SIZE_NAME_NORMAL 100
#define SIZE_NAME_LONG 100
#define FAILURE 0
#define SUCCESS 1


static u8 g_enable;
typedef struct process
{
	char name[SIZE_NAME_NORMAL];
	pid_t pid;
	int pipefd[2];
	size_t score;
}process_t;

typedef struct instance
{
	char prg_name[SIZE_NAME_LONG];	
	char cfg_name[SIZE_NAME_LONG];
	
	u16 process_num;
	u16 process_idx;

	struct process *proc;
}instance_t;

static int master(instance_t *pinst);
static int worker(instance_t *pinst);

static void __sig_quit(int sig)
{
	g_enable = 0;
}
int process_poll(instance_t *pinst,u16 process_num)
{
	int ret = FAILURE;
	int ix = 0;
	int status = 0;

	if(!pinst || !process_num){
		printf("null\n");
		goto _E1;
	}

	signal(SIGINT,__sig_quit);
	signal(SIGTERM,__sig_quit);

	pinst->process_idx = 0;
	pinst->process_num = process_num;
	pinst->proc = (process_t*)calloc(process_num+1,sizeof(process_t));
	if(!pinst->proc){
		printf("alloc process poll struct failed\n");
		goto _E1;
	}

	for(ix=1;ix<=process_num;ix++){
		int bufsize = 1;
		ret = pipe(pinst->proc[ix].pipefd);
		if(ret<0){
			printf("socketpair %s \n",strerror(errno));
			goto _E2;
		}
		printf("setup worker#%u\n",ix);

		pinst->proc[ix].pid = fork();

		if(pinst->proc[ix].pid <0){
			printf("fork\n");
			goto _E2;
		}
		else if(pinst->proc[ix].pid>0){
			close(pinst->proc[ix].pipefd[0]);
			continue;
		}else{
			close(pinst->proc[ix].pipefd[1]);
			pinst->process_idx = ix;
			ret = worker(pinst);
			goto _E2;
		}
	}

	ret = master(pinst);
	//回收释放子进程所占的内容
	for(ix=1;ix<=pinst->process_num;ix++){
		waitpid(pinst->proc[ix].pid,&status,WNOHANG);
	}
	printf("主进程结束\n");
_E2:
	for(ix=1;ix<=pinst->process_num;ix++){
		close(pinst->proc[ix].pipefd[1]);
		close(pinst->proc[ix].pipefd[0]);
	}
	printf("子进程结束，释放资源");
	free(pinst->proc);
_E1:
	return ret;
	
}

static int master(instance_t *pinst)
{
	int ret = 0;
	int fd = 0;
	int ix = 0;
	int roll = 0;
	char c = 0;

	#define __offset(pinst) ((pinst)->proc[(pinst)->process_idx])
	#define __round_robin(pinst,roll) ((pinst)->proc[((roll)%(pinst)->process_num)+1].pipefd[1])
	
	printf("master#%u setup\n",pinst->process_idx);

	for(g_enable =1;g_enable;){
		fd = __round_robin(pinst,++roll);
		c = 'A'+roll % 3;
		ret = write(fd,&c,1);
		if(ret <=0){
			return FAILURE;
		}
		printf("master 进程轮访进程池 %d\n",fd);
		
		sleep(1);//主进程轮询并向某个工作子进程发送任务，同时阻塞当前父进程，子进程工作 进程调度策略：即使是多个进程工作，cpu也是不断的给每个进程时间片轮运行的
	}

	//当主进程接受了中断停止信号后，轮访发送Q字符

	for(ix=1;ix<=pinst->process_num;ix++){
		c = 'Q';
		write(__round_robin(pinst,++roll),&c,1);
	}

	printf("master$%u shutdown\n",pinst->process_idx);

	return SUCCESS;
	
}

static int worker(instance_t *pinst)
{
	//子进程工作  当主进程轮访进程池的时候是选择某个进程发送数据的，然后它阻塞主进程，子进程运行	
	int fd = __offset(pinst).pipefd[0];

	int ix = 0;
	size_t read_byte = FAILURE;

	char buffer[1024] = {0};

	printf("worker#%u setup\n",pinst->process_idx);

	for(g_enable=1;g_enable;){
		read_byte = read(fd,buffer,sizeof(buffer));
		if(read_byte<=0){
			if(errno == EAGAIN||errno == EINTR){
				continue;
			}
		}

		for(ix=0;ix<read_byte;ix++){
			switch(buffer[ix]){
				case 'A':
				case 'B':
				case 'C':
					__offset(pinst).score+=buffer[ix];
					//子进程工作，不断的打印内容

					printf("子进程工作：worker#%u recv comand:%c,score:%llu\n",pinst->process_idx,buffer[ix],__offset(pinst).score);
			//		printf("子进程工作完成，切换到master主进程了");

				break;
				case 'Q':
					printf("quit\n");
					g_enable = 0;
					break;
				default:
					break;
			
			}
		}
	}
	//子进程退出  当主进程接受中断信号以后
	printf("worker#%u shutdown \n",pinst->process_idx);
	return SUCCESS;
}
int main(int argc,char *argv[])
{

	instance_t inst = {0};
	if(argc<2){
		printf("useage:\n\t%s<process number>\n",argv[0]);
		return EXIT_FAILURE;
	}
	process_poll(&inst,atoi(argv[1]));

	return 0;
}
