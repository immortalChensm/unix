//
// Created by 1655664358@qq.com on 2019/9/23.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex;
pthread_cond_t wait1;
pthread_cond_t wait2;
void *test1(void *data)
{
    pthread_mutex_lock(&mutex);//锁定线程，其它线程阻塞

    int n = 10;
    n++;
    printf("test1 n=%d\n",n);
    //pthread_cond_wait(&wait2,&mutex);//等待其它线程发送通知，并阻塞当前线程
    n++;
    printf("test1 n=%d\n",n);
    pthread_cond_signal(&wait1);//给其它线程发送通知
    pthread_mutex_unlock(&mutex);
}
void *test2(void *data)
{
    pthread_mutex_lock(&mutex);

    int n = 100;
    n++;
    printf("test2 n=%d\n",n);
    pthread_cond_signal(&wait2);
    //pthread_cond_wait(&wait1,&mutex);
    n++;
    printf("test2 n=%d\n",n);
    pthread_mutex_unlock(&mutex);
}
int main(void)
{
    void *retval;
    pthread_t tid;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&wait1,NULL);
    pthread_cond_init(&wait2,NULL);
    pthread_create(&tid,NULL,test1,0);
    pthread_create(&tid,NULL,test2,0);
    pthread_join(tid,&retval);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&wait1);
    pthread_cond_destroy(&wait2);

    return 0;
}
