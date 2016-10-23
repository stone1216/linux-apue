
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h>
#include"apue.h"
int maintest(){

//    pid_t pid;
//    if((pid=fork())<0)
//        err_sys("fork error");
//    else if(pid==0)
//    {
//        chdir("/etc");
//        if(execl("/bin/ls","ls","-l",NULL))
//            err_sys("execl error");
//    }


//    if(waitpid(pid,NULL,0)<0)
//        err_sys("wait error");

    char *ptr;
    ptr=getenv("PAGER");
    printf("%s\n",ptr);

    return 0;
}
