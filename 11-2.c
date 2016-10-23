#include"apue.h"
#include<pthread.h>

pthread_t ntid;

void printid(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid=getpid();
    tid=pthread_self();
    printf("%s pid: %lu tid: %lu (0x%lx)\n",s,(unsigned long)pid,(unsigned long)tid);
}

void* thr_fn(void *arg)
{
    printf("arg: %d\n",*((int *)arg));
    printid("new threand:");
    return (void *)0;
}


int main112()
{
    int err;
    int x=10;
    err=pthread_create(&ntid,NULL,thr_fn,&x);
    if(err!=0)
        err_exit(err,"can't create thread");

    sleep(1);
    printid("main thread:");
    exit(0);
}
