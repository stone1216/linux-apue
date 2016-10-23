#include"apue.h"

#include<pthread.h>

void cleanup(void *arg)
{
    printf("clean up: %s\n",(char*)arg);
}


static void * thr_fn1(void *arg)
{
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup,"thread 1 frist handler");
    pthread_cleanup_push(cleanup,"thread 1 second handler");
    printf("thread 1 complete\n");
//    if(arg)
//       return (void *)1;
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    return (void *)1;

}

static void * thr_fn2(void *arg)
{
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup,"thread 2 frist handler");
    pthread_cleanup_push(cleanup,"thread 2 second handler");
    printf("thread 2 complete\n");
    if(arg)
       pthread_exit( (void *)2);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_exit( (void *)2);

}

int main115()
{
    int err;
    pthread_t tid1,tid2;
    void *tret;

    err=pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err!=0)
        err_exit(err,"can't create thread 1");



    err=pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err!=0)
        err_exit(err,"can't create thread 2");
    err=pthread_join(tid1,&tret);
    if(err!=0)
        err_exit(err,"can't join with thread 1");

    printf("thread 1 exit code %ld\n", (int  )tret);

    err=pthread_join(tid2,&tret);
    if(err!=0)
        err_exit(err,"can't join with thread 2");
    printf("thread 2 exit code %ld\n", (int  )tret);
    exit(0);

}
