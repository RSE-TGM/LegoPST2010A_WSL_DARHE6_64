/**********************************************************************
*
*       C Header:               libipc.h
*       Subsystem:              3
*       Description:
*       %created_by:    mauric %
*       %date_created:  Thu Feb 12 15:08:08 1998 %
*
**********************************************************************/
/*
   modulo libipc.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)libipc.h	5.1
*/
# include <stdio.h>
# include <setjmp.h>
# include <errno.h>
#if defined UNIX
# include <sys/signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <sys/msg.h>
#endif

#if defined VMS
# include <signal.h>
#endif

# define BIGCOUNT 10000

/* prototyping */
int sem_create(int,int);
int sem_open(int);
void sem_wait(int);
void sem_wait_disp(int);
void sem_signal(int);
void sem_signal_disp(int);
void sem_op(int,int);
void sem_op_dispatcher(int,int);
void sem_close(int);
void sem_rm(int);

#if defined UNIX

static struct sembuf op_lock[2]={
			2, 0, 0,
			2, 1, SEM_UNDO};

static struct sembuf op_endcreate[2]={
			1, -1, SEM_UNDO,
			2, -1, SEM_UNDO};

static struct sembuf op_open[1]={
			1, -1, SEM_UNDO};

static struct sembuf op_close[3]={
			2, 0, 0,
			2, 1, SEM_UNDO,
			1, 1, SEM_UNDO};

static struct sembuf op_unlock[1]={
			2, -1, SEM_UNDO};

static struct sembuf op_op[1]={
			0, 99, SEM_UNDO};

static struct sembuf op_op_disp[1]={
			0, 99, !IPC_NOWAIT};
			
#endif
/* per timeout */
#define TIMEOUT_INFINITO 	0
