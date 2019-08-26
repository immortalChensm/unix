//
// Created by 1655664358@qq.com on 2019/7/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

//#include "common.h"

int main(int argc,char *argv[])
{
    int *p = malloc(sizeof(int));
    assert(p!=NULL);
    printf("(%d) memory of addrss p :%08x\n",getpid(),(unsigned)p);

    *p = 0; 
    int i=10;
    while(i--){
        *p = *p+1;
        printf("(%d) %d\n",getpid(),*p);
    }

    return 0;
}

