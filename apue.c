#include "apue.h"
#include<fcntl.h>

void  set_fl(int fd, int flags)
{
    int val;
    if((val=fcntl(fd,F_GETFD,0))<0)
        err_sys("F_GETFD error");

    val|=flags;


    if(fcntl(fd,F_SETFL,val))
        err_sys("F_SET error");
}

void  clr_fl(int fd, int flags)
{
    int val;
    if((val=fcntl(fd,F_GETFD,0))<0)
        err_sys("F_GETFD error");

    val&=~flags;

    if(fcntl(fd,F_SETFL,val))
        err_sys("F_SET error");
}



static volatile sig_atomic_t sigflags;
static sigset_t newmask, oldmask,zeromask;

static void sig_usr(int signo)
{
    sigflags=1;
}

void TELL_WAIT(void)
{
    if(signal(SIGUSR1,sig_usr)==SIG_ERR)
        err_sys("signal(sigusr1) error");
    if(signal(SIGUSR2,sig_usr)==SIG_ERR)
        err_sys("signal(sigusr2) error");
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGUSR1);
    sigaddset(&newmask,SIGUSR2);

    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
        err_sys("SIG_BLOCK error");


}
void TELL_PARENT(pid_t pid)
{
    kill(pid,SIGUSR2);
}
void TELL_CHILD(pid_t pid)
{
    kill(pid,SIGUSR1);
}
void	WAIT_PARENT(void)
{
    while(sigflags==0)
        sigsuspend(&zeromask);
    sigflags=0;
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
        err_sys("SIG_SETMASK error");
}
void	WAIT_CHILD(void)
{
    while(sigflags==0)
        sigsuspend(&zeromask);
    sigflags=0;
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
        err_sys("SIG_SETMASK error");
}

void pr_mask(const char *str)//打印当前被阻塞的信号
{
sigset_t sigset;
int errno_save;

errno_save = errno; /* we can be called by signal handlers */
if (sigprocmask(0, NULL, &sigset) < 0)
perror("sigprocmask error");
printf("%s",str);
if (sigismember(&sigset, SIGHUP)) printf("SIGHUP ");
if (sigismember(&sigset, SIGINT)) printf("SIGINT ");
if (sigismember(&sigset, SIGQUIT)) printf("SIGQUIT ");
if (sigismember(&sigset, SIGILL)) printf("SIGILL ");
if (sigismember(&sigset, SIGTRAP)) printf("SIGTRAP ");
if (sigismember(&sigset, SIGABRT)) printf("SIGABRT ");
if (sigismember(&sigset, SIGBUS)) printf("SIGBUS ");
if (sigismember(&sigset, SIGFPE)) printf("SIGFPE ");
if (sigismember(&sigset, SIGKILL)) printf("SIGKILL ");
if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
if (sigismember(&sigset, SIGSEGV)) printf("SIGSEGV ");
if (sigismember(&sigset, SIGUSR2)) printf("SIGUSR2 ");
if (sigismember(&sigset, SIGPIPE)) printf("SIGPIPE ");
if (sigismember(&sigset, SIGALRM)) printf("SIGALRM ");
if (sigismember(&sigset, SIGTERM)) printf("SIGTERM ");

if (sigismember(&sigset, SIGSTKFLT)) printf("SIGSTKFLT ");
if (sigismember(&sigset, SIGCHLD)) printf("SIGCHLD ");
if (sigismember(&sigset, SIGCONT)) printf("SIGCONT ");
if (sigismember(&sigset, SIGSTOP)) printf("SIGSTOP ");
if (sigismember(&sigset, SIGTSTP)) printf("SIGTSTP ");
if (sigismember(&sigset, SIGTTIN)) printf("SIGTTIN ");
if (sigismember(&sigset, SIGTTOU)) printf("SIGTTOU ");
if (sigismember(&sigset, SIGURG)) printf("SIGURG ");
if (sigismember(&sigset, SIGXCPU)) printf("SIGXCPU ");
if (sigismember(&sigset, SIGXFSZ)) printf("SIGXFSZ ");
if (sigismember(&sigset, SIGVTALRM)) printf("SIGVTALRM ");
if (sigismember(&sigset, SIGPROF)) printf("SIGPROF ");
if (sigismember(&sigset, SIGWINCH)) printf("SIGWINCH ");
if (sigismember(&sigset, SIGIO)) printf("SIGIO ");
if (sigismember(&sigset, SIGPWR)) printf("SIGPWR ");
if (sigismember(&sigset, SIGSYS)) printf("SIGSYS ");

/* remaining signals can go here */

printf("\n");
errno = errno_save;
}



int set_cloexec(int fd)
{
    int val;
    if((val=fcntl(fd,F_GETFD,0))<0)
        return -1;
    val |= FD_CLOEXEC;

    return fcntl(fd,F_SETFD,val);





}
