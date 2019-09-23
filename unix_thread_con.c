//
// Created by 1655664358@qq.com on 2019/9/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 4
#define OVER (-1)
struct producers
{
    int buffer[BUFFER_SIZE];
    pthread_mutex_t lock;
    int readpos,writepos;
    pthread_cond_t notempty;
    pthread_cond_t notfull;
};

struct producers buffer;

void init(struct producers *b)
{
    pthread_mutex_init(b->lock,NULL);
    pthread_cond_init(b->notempty,NULL);
    pthread_cond_init(b->notfull,NULL);
    b->readpos=0;
    b->writepos=0;
}

void put(struct producers *b,int data)
{
    pthread_mutex_lock(&b->lock);
    while ((b->writepos+1)%BUFFER_SIZE==b->readpos){//[0] [2==1] [3==2] [4==2]
        pthread_cond_wait(&b->notfull,&b->lock);
        printf("put equall writespos=%d,readpos=%d\n",b->writepos,b->readpos);
    }
    b->buffer[b->writepos] = data;
    b->writepos++;
    if (b->writepos>=BUFFER_SIZE){
        b->writepos=0;//0
    }
    pthread_cond_signal(&b->notempty);
    pthread_mutex_unlock(&b->lock);
}
void *producer(void *data)
{
    int n;
    for (n = 0; n < 10; ++n) {
        printf("producer:%d->\n",n);
        put(&buffer,n);
    }

    put(&buffer,OVER);
    return NULL;
}
int get(struct producers *b)
{
    int data;
    pthread_mutex_lock(b->lock);
    while (b->writepos==b->readpos){//[1==0]  [2==1] [3==2] [0==3]
        pthread_cond_wait(&b->notempty,&b->lock);
        printf("get equall writespos=%d,readpos=%d\n",b->writepos,b->readpos);
    }
    data = b->buffer[b->readpos];
    b->readpos++;
    if (b->readpos>=BUFFER_SIZE){
        b->readpos=0;//0
    }
    pthread_cond_signal(&b->notfull);
    pthread_mutex_unlock(&b->lock);
    return data;
}
void *consumer(void *data)
{
    int d;
    while (1){
        d = get(&buffer);
        if (d == OVER){
            break;
        }
        printf("consumer:-->%d\n",d);
    }
    return NULL;
}
int main(void)
{
    pthread_t tha,thb;
    void *retval;

    init(&buffer);

    pthread_create(&tha,NULL,producer,0);
    pthread_create(&thb,NULL,consumer,0);

    pthread_join(tha,&retval);
    pthread_join(thb,&retval);

    return 0;
}
