#include<apue.h>

static void sig_int(int);

int main1022()
{
    sigset_t newmask,oldmask,waitmask;
    pr_mask("program start: ");

    if(signal(SIGINT,sig_int)==SIG_ERR)
        err_sys("signal error");

    sigemptyset(&waitmask);
    sigaddset(&waitmask,SIGUSR2);
    sigaddset(&waitmask,SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGINT);

    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
        err_sys("sig_block error");

    pr_mask("in critical region: ");

    if(sigsuspend(&waitmask)!=-1)
        err_sys("sigsuspend error");

    pr_mask("after sigsuspend : ");

    if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
        err_sys("SIG_SETMASK error");

    pr_mask("program exit: ");
    exit(0);
}

static void  sig_int(int signo)
{
    pr_mask("in sig_int: ");
}
