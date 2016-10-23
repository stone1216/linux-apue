#include"apue.h"


static void sig_usr(int signo)
{

    if(signal(SIGUSR1,sig_usr)==SIG_ERR)
        err_sys("signal sigusr1 error");
    if(signal(SIGUSR2,sig_usr)==SIG_ERR)
        err_sys("signal sigusr2 error");
    if(signo==SIGUSR1)
        printf("receive SIGUSR1\n");
    else if(signo==SIGUSR2)
        printf("receive SIGUSR2\n");
    else
        err_dump("receive signal %d\n",signo);
}

int main102()
{
    if(signal(SIGUSR1,sig_usr)==SIG_ERR)
        err_sys("signal sigusr1 error");
    if(signal(SIGUSR2,sig_usr)==SIG_ERR)
        err_sys("signal sigusr2 error");

    for(;;)
        pause();
}
