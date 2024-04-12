/**********************************************************************
*
*       C Header:               Marte.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jul 19 13:44:31 2005 %
*
**********************************************************************/
#ifndef _Marte_h
#define _Marte_h

# include <setjmp.h>
#define MAX_THREAD      100
#define MAX_LUN_NOME_TASK 80
#define RETURN_JMP	12 // basta diverso da zero
#define pthread_once_init              PTHREAD_ONCE_INIT


typedef struct _TCB {
        pthread_t  id;
        char nome_task[MAX_LUN_NOME_TASK];
	int stato;
	int prio;
	int periodo;
	int rit_attivazione;
        jmp_buf jmp_syn;
	pthread_cond_t  condition;
        pthread_mutex_t mutex;
	pthread_cond_t  condition_sus;
        pthread_mutex_t mutex_sus;
        int valore;
        } TCB;

TCB *PuntTcb;

#define INACTIVE_STATE	0
#define RUNNING_STATE	1
#define READY_STATE	2
#define SUSPENDED_STATE	4
#define DORMANT_STATE	8
#define RESUMED_STATE	16
#define BOOK_STATE	32

void InitLibMarte();
int PrinThreadState();
int gatto;
int ActivateThread(pthread_startroutine_t, char *, int ,int);
int SetTaskState(int, int);
int SetBookState(int, int);
int GetTaskState(int);
int SetRootPriv();
int UnSetRootPriv();

/*
	Chiamate Marte
*/
int rew(int, int , int*);
int tra(int, int);
int wai(int);
void ter();
void tas(int);
void res(int);
int pri(int, int);
int kil(int);
int esp(int);
int suw(int);
void sce();
void scd();
int syn(int,int,int);
int synsim(int,int,int);
int waisim(int);

#endif
