/**********************************************************************
*
*       C Source:               SynSim.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Oct 15 11:41:42 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: SynSim.c-2.1.1 %  (%full_filespec: SynSim.c-2.1.1:csrc:1 %)";
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

#include <Marte/MarteP.h>
#include <Marte/TaskMarte.h>

#define OFFSET_TIME_SIM 	1000

static int app_syssim();

extern int clear_operation;

int synsim(int tcb,int periodo, int attesa)
{
int pos_ele;
printf("synsim codice_tcb %d periodo %d attesa attivazione %d\n",
	tcb,periodo,attesa);

PuntTcb[tcb].periodo = periodo;
PuntTcb[tcb].rit_attivazione = attesa;
for(pos_ele=0;pos_ele<NUM_ELE_TASK_MARTE;pos_ele++)
	if(ele_task_marte[pos_ele].codice == tcb)
		break;
if(pos_ele == NUM_ELE_TASK_MARTE)
	return(-1);
ActivateThread((pthread_startroutine_t)app_syssim, 
			ele_task_marte[pos_ele].nome, 
			ele_task_marte[pos_ele].prio,tcb);
SetTaskState(tcb,DORMANT_STATE);
return(0);
}

app_syssim(pthread_addr_t arg)
{
int i = (int)arg;
pthread_t self;
int pos_ele;
int offset_time_sim=0;
char offset_time_sim_ascii[256];

/* 
	attende la registrazione
*/
self = pthread_self();
while(pthread_equal(self, PuntTcb[i].id)!= 1)
        wai(10);

if(!getenv("OFFSETTIMESIM"))
   {
   offset_time_sim=OFFSET_TIME_SIM;
   }
else
   {
   strcpy(offset_time_sim_ascii,getenv("OFFSETTIMESIM"));
   offset_time_sim=atoi(offset_time_sim_ascii);
   }


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
	int attesa;
	long t1,t2;

	GetOra(&ora_i,&minuti_i,&secondi_i,&milli_i);
#ifdef SCADA_DEBUG
        printf("DEBUG: ora_i =%d minuti_i=%d secondi_i=%d milli_i=%d\n",ora_i,minuti_i,secondi_i,milli_i);
#endif
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
                {
		SetTaskState(i,DORMANT_STATE);
                }
#ifdef OLD_SCADA
	milli_i = milli_i + PuntTcb[i].periodo*REAL_TIME_CLOCK;
#endif
	if(milli_i> 999)
		{
		milli_i -= 1000;
		++ secondi_i;
		}
	if(secondi_i > 59)
		{
                secondi_i -= 60;
                ++ minuti_i;
                }
	if(minuti_i > 59)
		{
                minuti_i -= 60;
                ++ ora_i;
                }
	t1 = ora_i*3600000 + minuti_i*60000+secondi_i*1000+milli_i;
#ifdef SCADA_DEBUG
        printf("DEBUG2: t1=%ld ora_i =%d minuti_i=%d secondi_i=%d milli_i=%d\n",t1,ora_i,minuti_i,secondi_i,milli_i);
#endif
	while(1)
		{
                if(clear_operation)
                    {
                    t1=0;
                    clear_operation=0;
                    }
		GetOra(&ora_f,&minuti_f,&secondi_f,&milli_f);
		if(ora_f<ora_i)
			ora_f = 24;
		t2 = ora_f*3600000 + minuti_f*60000+secondi_f*1000+milli_f;
                        if((secondi_f==1) || (secondi_f==2))
                           {
#ifdef SCADA_DEBUG
                           printf("DEGUG: t1=%ld t2=%ld\n",t1,t2);

                           printf("DEBUG: ora_f =%d minuti_f=%d secondi_f=%d milli_f=%d\n",ora_f,minuti_f,secondi_f,milli_f);
#endif
                           }
		if( (t2 - t1) >= offset_time_sim  ) 
                        {
#ifdef SCADA_DEBUG
                        printf("DEBUG: t1=%ld t2=%ld\n",t1,t2);
#endif
			break;
                        }
		wai(2);
		}
	}
}
