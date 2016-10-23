#include<apue.h>

volatile sig_atomic_t quitflag=0;

static void sig_int(int signo)
{
//    if(signal(SIGINT,sig_int)==SIG_ERR)
//        err_sys("signal error");
//    if(signal(SIGQUIT,sig_int)==SIG_ERR)
//        err_sys("signal error");
    if(signo==SIGINT)
        printf("\ninterrupt\n");
    else if(signo==SIGQUIT)
        quitflag=1;
}




int main1023()
{
    sigset_t newmask,oldmask,zeromask;

    if(signal(SIGINT,sig_int)==SIG_ERR)
        err_sys("signal error");
    if(signal(SIGQUIT,sig_int)==SIG_ERR)
        err_sys("signal error");

//    struct sigaction act;
//    act.sa_handler=sig_int;

//    if(sigaction( SIGINT, &act,NULL)==SIG_ERR)
//        err_sys("sigaction error");
//    if(sigaction( SIGQUIT, &act,NULL)==SIG_ERR)
//        err_sys("sigaction error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGQUIT);

    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
        err_sys("sig_block error");

    while(quitflag==0)
    {
        sigsuspend(&zeromask);

        //sleep(1);

    }


    printf("wake up\n");
    quitflag=0;
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
        err_sys("SIG_SETMASK error");

    exit(0);
}
