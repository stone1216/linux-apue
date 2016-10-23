#include "apue.h"

static void charactatime(char *);

int main812()
{
    //err_sys("123");
    pid_t pid;

    TELL_WAIT();
    if((pid=fork())<0)
        err_sys("fork error");
    else if(pid==0)
    {
        charactatime("output from child\n");
        TELL_PARENT(pid);
    }
    else
    {
        WAIT_CHILD();
        charactatime("output from parent\n");
    }


    exit(0);
}


static void charactatime(char *str)
{
    char *ptr;
    int c;
    setbuf(stdout,NULL);
    for(ptr=str;(*ptr)!=0;ptr++)
        putc(*ptr,stdout);
}
