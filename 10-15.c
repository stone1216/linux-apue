#include "apue.h"

static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if(signal(SIGQUIT,SIG_DFL)==SIG_ERR)
        err_sys("can't reset SIGQUIT\n");
}

int main1015()
{
    sigset_t newmask,oldmask,pendmask;

    if(signal(SIGQUIT,sig_quit)==SIG_ERR)
        err_sys("can't catch SIGQUIT\n");
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGQUIT);

    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
        err_sys("SIG_BLOCK error");

    sleep(5);

    if(sigpending(&pendmask)<0)
        err_sys("sigpending error");
    if(sigismember(&pendmask,SIGQUIT))
        printf("\n SIGQUIT pending\n");

    if(sigprocmask(SIG_SETMASK,&oldmask,NULL))
        err_sys("SIG_SETMASK error");

    printf("SIGQUIT unblock\n");
    sleep(5);
    exit(0);



}
