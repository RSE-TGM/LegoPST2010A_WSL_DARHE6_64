/**********************************************************************
*
*       C Source:               OnceLibMarte.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jun  1 15:57:03 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: OnceLibMarte.c-4.1.1 %  (%full_filespec: OnceLibMarte.c-4.1.1:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include <Marte/MarteP.h>
#include <Marte/TaskMarte.h>

#include <dconf.inc>

int osf1_print_debug_1 = 0;
int osf1_print_debug_2 = 0;

void dprinti(int tipo,char * testo,int val)
{
if(((tipo == 1)&&(!osf1_print_debug_1))||((tipo == 2)&&(!osf1_print_debug_2)))
        return;
printf("%d:%s %d\n",tipo,testo,val);
}

#ifndef LINUX
void dprintf(int tipo,char * testo,float val)
{
if(((tipo == 1)&&(!osf1_print_debug_1))||((tipo == 2)&&(!osf1_print_debug_2)))
        return;
printf("%d:%s %f\n",tipo,testo,val);
}
#endif

void dprint(int tipo,char * testo)
{
if(((tipo == 1)&&(!osf1_print_debug_1))||((tipo == 2)&&(!osf1_print_debug_2)))
        return;
printf("%d:%s\n",tipo,testo);
}

int start_debug_1()
{
osf1_print_debug_1 = !osf1_print_debug_1;
if(osf1_print_debug_1)
        printf("start debug tipo 1\n");
else
        printf("stop debug tipo 1\n");
return(0);
}

int start_debug_2()
{
osf1_print_debug_2 = !osf1_print_debug_2;
if(osf1_print_debug_2)
        printf("start debug tipo 2\n");
else
        printf("stop debug tipo 2\n");
return(0);
}
               
/*
        dichiarazione delle mail box utilitzzate
*/
short mbox_archiv = MBOX_ARCHIV;
short mbox_all_0 = MBOX_ALL_0;
short mbox_lbg = MBOX_LBG;
short mbox_disk = MBOX_DISK;
short mbox_pag1 = MBOX_PAG1;
short mbox_pag2 = MBOX_PAG2;
short mbox_pag3 = MBOX_PAG3;
short mbox_pag4 = MBOX_PAG4;
short mbox_pag5 = MBOX_PAG5;
short mbox_pagres1 = MBOX_PAGRES1;
short mbox_pagres2 = MBOX_PAGRES2;
short mbox_pagres3 = MBOX_PAGRES3;
short mbox_pagres4 = MBOX_PAGRES4;
short mbox_pagres5 = MBOX_PAGRES5;
short mbox_scgev = MBOX_SCGEV;
short mbox_abilger = MBOX_ABILGER;

/*
	dichiarazione delle tcb
*/
int pscsini_tcb =  PSCSINI_TCB;
int pscswd_tcb =  PSCSWD_TCB;
int pccom_tcb = PCCOM_TCB;
int asinct_tcb = ASINCT_TCB ;
int _call_tcb =  _CALL_TCB ;
int stampe_tcb =  STAMPE_TCB ;
int scgev_tcb =  SCGEV_TCB ;
int tcval_tcb = TCVAL_TCB ;
int attiper_tcb =  ATTIPER_TCB ;
int gdac_tcb = GDAC_TCB ;
int monitor_tcb =  MONITOR_TCB ;
int taggcfg_tcb =  TAGGCFG_TCB ;
int schc_tcb =  SCHC_TCB ;
int thcwin_tcb = THCWIN_TCB ;
int tcte3_tcb =  TCTE3_TCB ;
int tcte4_tcb = TCTE4_TCB ;
int reptask_tcb = REPTASK_TCB ;
int idle_tcb =   IDLE_TCB ;
int gps_tcb = GPS_TCB ;
int acqui_tcb = ACQUI_TCB ;
int _tabulati_tcb = _TABULATI_TCB ;
int tabper_tcb = TABPER_TCB ;
int arcwai_tcb = ARCWAI_TCB ;
int _isa_tcb = _ISA_TCB ;
int rxpio_tcb = RXPIO_TCB ;
int txpio_tcb = TXPIO_TCB ;
int duatask_tcb = DUATASK_TCB ;
int pag1_tcb = PAG1_TCB ;
int pag2_tcb = PAG2_TCB ;
int pag3_tcb = PAG3_TCB ;
int pag4_tcb = PAG4_TCB ;
int pag5_tcb = PAG5_TCB ;
int statistics_tcb = STATISTICS_TCB ;
int print_00_tcb = PRINT_00_TCB ;
int print_01_tcb = PRINT_01_TCB ;
int print_02_tcb = PRINT_02_TCB ;
int print_03_tcb = PRINT_03_TCB ;
int print_04_tcb = PRINT_04_TCB ;
int print_05_tcb = PRINT_05_TCB ;
int print_06_tcb = PRINT_06_TCB ;
int print_07_tcb = PRINT_07_TCB ;

static pthread_once_t block = pthread_once_init;

/*
        questo mutex viene utilizzato per il lock dei diritti
        di root: solo un thread puo' attivare per se stesso i
        diritti di root e quindi toglierseli
*/
pthread_mutex_t RootPrivMutex;

static void OnceLibMarte()
{
extern MarteMailbox *PuntMarteMailbox;
int i;
int ret;

printf("Start-Up libMarte MAX_MAILBOX=%d, MAX_THREAD=%d\n",MAX_MAILBOX,MAX_THREAD);

/*
	inizializza le code
*/
initcod();

printf("DEBUG OnceLibMarte: dopo initcod!!!\n");

PuntMarteMailbox = (MarteMailbox*)malloc(MAX_MAILBOX * sizeof(MarteMailbox));

if(PuntMarteMailbox == NULL)
	{
	fprintf(stderr,"Errore OnceLibMarte: malloc\n");
	exit(0);
	}
for(i=0;i<MAX_MAILBOX;i++)
	{
	pthread_cond_init(&(PuntMarteMailbox[i].condition), pthread_condattr_default);
	pthread_mutex_init(&(PuntMarteMailbox[i].mutex), pthread_mutexattr_default);
	PuntMarteMailbox[i].valore = 0;
	}

/*
        definizione mail box utilitzzate
*/
mbox_archiv = 0;


PuntTcb = (TCB*)malloc(MAX_THREAD * sizeof(TCB));

if(PuntTcb == NULL)
        {
        fprintf(stderr,"Errore OnceLibMarte: malloc\n");
        exit(0);
        }

for(i=0;i<MAX_THREAD;i++)
	{
	PuntTcb[i].stato= INACTIVE_STATE;
	PuntTcb[i].nome_task[0] = 0;
	PuntTcb[i].prio= -1;
	PuntTcb[i].periodo= 0;
	PuntTcb[i].rit_attivazione= 0;
	pthread_cond_init(&(PuntTcb[i].condition),pthread_condattr_default);
	pthread_mutex_init(&(PuntTcb[i].mutex),pthread_mutexattr_default);
	pthread_cond_init(&(PuntTcb[i].condition_sus),pthread_condattr_default);
	pthread_mutex_init(&(PuntTcb[i].mutex_sus),pthread_mutexattr_default);
	}

/*
	inizializzazione del RootPrivMutex
*/
pthread_mutex_init(&RootPrivMutex,pthread_mutexattr_default);
}

void InitLibMarte()
{
pthread_once(&block,OnceLibMarte);
}

beg_marte()
{
int i;

signal(SIGUSR1,start_debug_1);
signal(SIGUSR2,start_debug_2);

InitLibMarte();
UnSetRootPriv();

for(i=0;i<NUM_ELE_TASK_MARTE;i++)
   if(ele_task_marte[i].auto_start)
	{
        printf("nome=%s - prio=%d - pos=%d\n", ele_task_marte[i].nome, ele_task_marte[i].prio, ele_task_marte[i].codice);
	ActivateThread((pthread_startroutine_t)ele_task_marte[i].procedura,
		ele_task_marte[i].nome,
		ele_task_marte[i].prio,
		ele_task_marte[i].codice);
	}
syn(statistics_tcb,50,10);
return(0);
}

QuitScada(int codice_uscita)
{
extern DB_HEADER h_db;
pid_t pidPadre;

printf("Quit scada\nScrittura del database su disco\n");
/*
	scrittura dela database su disco
*/
rwdbal(1,&h_db,&h_db);
system("rm -f apptty*");
pidPadre = getppid();
// kill(pidPadre,SIGKILL);
exit(0);
}

RestartScada()
{
system("rm -f apptty*");
exit(0);
}

QuitScadaNoWriteDBS(short errore)
{
pid_t pidPadre;

/* Cancella TTY */
system("rm -f apptty*");

/* Uccide il babbo */
pidPadre = getppid();
kill(pidPadre,SIGKILL);

exit(errore);
}
