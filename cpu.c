//
// Created by 1655664358@qq.com on 2019/7/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

//#include "common.h"
#include <unistd.h>
int main(int argc,char *argv[])
{
    if (argc!=2){
        fprintf(stderr,"usage:cpu <string>\n");
        exit(1);
    }

    char *str = argv[1];
    //while(1){
        //Spin(1);
        //
        sleep(2);
        printf("%s\n",str);
    //}
    return 0;
}

