#include "apue.h"

#include<netdb.h>
#include<errno.h>
#include<syslog.h>
#include<sys/socket.h>
#include<syslog.h>
#include<fcntl.h>
#include<sys/resource.h>


#define BUFLEN 128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int type,const struct sockaddr *addr,socklen_t alen,int qlen);
extern void daemonize(const char *);





void serve(int sockfd)
{
    int clfd;
    FILE *fp;
    char buf[BUFLEN];

    set_cloexec(sockfd);

    for(;;)
    {
        if((clfd=accept(sockfd,NULL,NULL))<0)
        {
            syslog(LOG_ERR,"ruptime : accept error: %s",strerror(errno));
            exit(1);
        }
        set_cloexec(clfd);
        if((fp=popen("/usr/bin/uptime","r"))==NULL)
        {
            sprintf(buf,"error : %s\n",strerror(errno));
            send(clfd,buf,strlen(buf),0);
        }
        else
        {
            while(fgets(buf,BUFLEN,fp)!=NULL)
                send(clfd,buf,strlen(buf),0);
            pclose(fp);
        }
        close(clfd);
    }

}

int main1617(int argc,int *argv[])
{
    struct addrinfo *ailist,*aip;
    struct addrinfo hint;
    int sockfd ,err,n;
    char   *host;

    if(argc!=1)
        err_quit("input argments error");
    if((n=sysconf(_SC_HOST_NAME_MAX))<0)
        n = HOST_NAME_MAX;

    if((host=malloc(n))==NULL)
        err_sys("malloc error");
    if(gethostname(host,n)<0)
        err_sys("gethostname error");
    daemonize("ruptime");
    memset(&hint,0,sizeof(hint));
    hint.ai_addr=NULL;
    hint.ai_canonname=NULL;
    hint.ai_next=NULL;
    hint.ai_flags=AI_CANONNAME;
    hint.ai_socktype=SOCK_STREAM;

    if((err=getaddrinfo(host,"ruptime",&hint,&ailist))!=0)
    {
        syslog(LOG_ERR,"ruptime getaddrinfo error : %s",gai_strerror(err));
        exit(1);
    }
    for(aip=ailist;aip!=NULL;aip=aip->ai_next)
    {
        if((sockfd=initserver(SOCK_STREAM,aip->ai_addr,aip->ai_addrlen,QLEN)))
        {
            serve(sockfd);
            exit(0);
        }
    }

    exit(1);
}
