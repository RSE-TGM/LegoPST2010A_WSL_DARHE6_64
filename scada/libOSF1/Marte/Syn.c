/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <setjmp.h>

#include <Marte/MarteP.h>
#include <Marte/TaskMarte.h>

static int app_sys();

int syn(int tcb,int periodo, int attesa)
{
int pos_ele;
/**
printf("syn codice_tcb %d periodo %d attesa attivazione %d\n",
	tcb,periodo,attesa);
**/
PuntTcb[tcb].periodo = periodo;
PuntTcb[tcb].rit_attivazione = attesa;
for(pos_ele=0;pos_ele<NUM_ELE_TASK_MARTE;pos_ele++)
	if(ele_task_marte[pos_ele].codice == tcb)
		break;
if(pos_ele == NUM_ELE_TASK_MARTE)
	return(-1);
ActivateThread((pthread_startroutine_t)app_sys, 
			ele_task_marte[pos_ele].nome, 
			ele_task_marte[pos_ele].prio, 
			tcb);
SetTaskState(tcb,DORMANT_STATE);
return(0);
}

app_sys(pthread_addr_t arg)
{
int i = (int)arg;
pthread_t self;
int pos_ele;

/* 
	attende la registrazione
*/
self = pthread_self();
while(pthread_equal(self, PuntTcb[i].id)!= 1)
	wai(10);

for(pos_ele=0;pos_ele<NUM_ELE_TASK_MARTE;pos_ele++)
	if(ele_task_marte[pos_ele].codice == i)
		break;
if(pos_ele == NUM_ELE_TASK_MARTE)
	return(-1);

wai(PuntTcb[i].rit_attivazione);
while(1)
	{
	int ora_i,minuti_i,secondi_i,milli_i;
	int ora_f,minuti_f,secondi_f,milli_f;
	int delta;

	//GetOra(&ora_i,&minuti_i,&secondi_i,&milli_i);
	/*
	  se il ritorno della setjmp == 0 registra la posizione attuale
	  del program counter in jmp_syn e chiama la task periodica.
	  se setjmp == RETURN_JMP il flusso del programma proviene
	  dalla longjmp (modulo Ter.c)
	*/
	if(setjmp(PuntTcb[i].jmp_syn) != RETURN_JMP)
		{
		SetTaskState(i,RUNNING_STATE);
		(ele_task_marte[pos_ele].procedura)();
		SetTaskState(i,DORMANT_STATE);
		}
	else
		SetTaskState(i,DORMANT_STATE);
/*
	GetOra(&ora_f,&minuti_f,&secondi_f,&milli_f);
	if(secondi_f<secondi_i) secondi_f += 59;
	if(milli_f<milli_i) milli_f += 1000;
	delta = (secondi_f-secondi_i)*1000+milli_f-milli_i;
*/
	delta = 0;
	wai(PuntTcb[i].periodo-delta/REAL_TIME_CLOCK);
/***
	wai(PuntTcb[i].periodo-delta);
***/
	}
}

test_syn1()
{
int i;
	printf("test_sys1: procedura periodica inizio\n");
	for(i=0;i<600000;i++);
		{
		float a,b;

		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		b = 23.56;
		a = b /13.675;
		}
	printf("test_sys1: procedura periodica fine\n");
}

test_syn2()
{
	printf("test_sys2: procedura periodica\n");
}
