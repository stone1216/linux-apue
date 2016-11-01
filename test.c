
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h>
#include"apue.h"
#include<unistd.h>
#include<fcntl.h>
#define BUFLEN 4
int main(){

    int n;
    char buf[BUFLEN];

    //int fd0=open("./test0.txt",O_RDWR);
    //int fd=open("./test.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
    while((n=read(STDIN_FILENO,buf,BUFLEN))>0)
    {
        printf("\nread %d\n",n);
        if(write(STDOUT_FILENO,buf,n)!=n)
            err_sys("write error");
    }

    if(n<0)
        err_sys("read error");

    exit(0);

    return 0;
}
