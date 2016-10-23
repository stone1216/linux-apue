/* Our own header, to be included before all standard system headers */

#ifndef	_APUE_H
#define	_APUE_H

#include<setjmp.h>
#include<time.h>
#include <sys/types.h>		/* some systems still require this */
#include <sys/stat.h>
#include <sys/termios.h>	/* for winsize */
#include <stdio.h>		/* for convenience */
#include <stdlib.h>		/* for convenience */
#include <stddef.h>		/* for offsetof */
#include <string.h>		/* for convenience */
#include <unistd.h>		/* for convenience */
#include <signal.h>		/* for SIG_ERR */
#include<errno.h>

#define	MAXLINE	4096			/* max line length */



/*
 * Prototypes for our own functions.
 */
//char	*path_alloc(int *);				/* {Prog pathalloc} */
//long	 open_max(void);				/* {Prog openmax} */
void	 clr_fl(int, int);				/* {Prog setfl} */
void	 set_fl(int, int);				/* {Prog setfl} */
int      set_cloexec(int);
//void	 pr_exit(int);					/* {Prog prexit} */
//void	 pr_mask(const char *);			/* {Prog prmask} */
//Sigfunc	*signal_intr(int, Sigfunc *);	/* {Prog signal_intr_function} */

//int		 tty_cbreak(int);				/* {Prog raw} */
//int		 tty_raw(int);					/* {Prog raw} */
//int		 tty_reset(int);				/* {Prog raw} */
//void	 tty_atexit(void);				/* {Prog raw} */
//#ifdef	ECHO	/* only if <termios.h> has been included */
//struct termios	*tty_termios(void);		/* {Prog raw} */
//#endif

//void	 sleep_us(unsigned int);			/* {Ex sleepus} */
//ssize_t	 readn(int, void *, size_t);		/* {Prog readn_writen} */
//ssize_t	 writen(int, const void *, size_t);	/* {Prog readn_writen} */
//void	 daemonize(const char *);			/* {Prog daemoninit} */

//int		 s_pipe(int *);					/* {Progs streams_spipe sock_spipe} */
//int		 recv_fd(int, ssize_t (*func)(int,
//		         const void *, size_t));/* {Progs recvfd_streams recvfd_sockets} */
//int		 send_fd(int, int);				/* {Progs sendfd_streams sendfd_sockets} */
//int		 send_err(int, int,
//		          const char *);		/* {Prog senderr} */
//int		 serv_listen(const char *);		/* {Progs servlisten_streams servlisten_sockets} */
//int		 serv_accept(int, uid_t *);		/* {Progs servaccept_streams servaccept_sockets} */
//int		 cli_conn(const char *);		/* {Progs cliconn_streams cliconn_sockets} */
//int		 buf_args(char *, int (*func)(int,
//		          char **));			/* {Prog bufargs} */

//int		 ptym_open(char *, int);	/* {Progs3 ptyopen_streams ptyopen_bsd ptyopen_linux} */
//int		 ptys_open(char *);			/* {Progs3 ptyopen_streams ptyopen_bsd ptyopen_linux} */
//#ifdef	TIOCGWINSZ
//pid_t	 pty_fork(int *, char *, int, const struct termios *,
//		          const struct winsize *);		/* {Prog ptyfork} */
//#endif

//int		lock_reg(int, int, int, off_t, int, off_t); /* {Prog lockreg} */
//#define	read_lock(fd, offset, whence, len) \
//			lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
//#define	readw_lock(fd, offset, whence, len) \
//			lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
//#define	write_lock(fd, offset, whence, len) \
//			lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
//#define	writew_lock(fd, offset, whence, len) \
//			lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
//#define	un_lock(fd, offset, whence, len) \
//			lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

//pid_t	lock_test(int, int, off_t, int, off_t);		/* {Prog locktest} */

//#define	is_read_lockable(fd, offset, whence, len) \
//			(lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
//#define	is_write_lockable(fd, offset, whence, len) \
//			(lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

void	err_dump(const char *, ...);		/* {App misc_source} */
void	err_msg(const char *, ...);
void	err_quit(const char *, ...);
void	err_exit(int, const char *, ...);
void	err_ret(const char *, ...);
void	err_sys(const char *, ...);

//void	log_msg(const char *, ...);			/* {App misc_source} */
//void	log_open(const char *, int, int);
//void	log_quit(const char *, ...);
//void	log_ret(const char *, ...);
//void	log_sys(const char *, ...);

void	TELL_WAIT(void);		/* parent/child from {Sec race_conditions} */
void	TELL_PARENT(pid_t);
void	TELL_CHILD(pid_t);
void	WAIT_PARENT(void);
void	WAIT_CHILD(void);

#endif	/* _APUE_H */
