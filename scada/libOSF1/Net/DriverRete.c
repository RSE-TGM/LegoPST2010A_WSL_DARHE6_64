/**********************************************************************
*
*       C Source:               DriverRete.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 24 11:49:03 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: DriverRete.c-3 %  (%full_filespec: DriverRete.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "g2ptrdb.inc"
#include <comunic.inc>
#include "diagnoan.inc"
#include <mesqueue.h>
#include <netstr.h>
#include <switch.inc>
#include <Net/TaskRete.h>
#include <Util/code.h>

static void Connessione(pthread_addr_t );
static void ConnessioneInput(pthread_addr_t );
static void ConnessioneOutput(pthread_addr_t );
static void OpenFileLog(int);
static void WriteFileLog(int, int, int, int, int);
static void ConnFileLog(int, int, int);

void p_sospendi(int time)
{
struct timespec interval;
float ftime;

ftime = (float)time * 1000000;

interval.tv_sec = ftime/1000000000;
interval.tv_nsec = ftime - interval.tv_sec*1000000000;
pthread_delay_np(&interval);
}

ELE_TASK_RETE_TH  rete_th[NUM_ELE_TASK_RETE];

#define check(status,string) \
        if(status == -1) perror(string)

DriverRete()
{
int i,j;
int offset;
char *off = NULL;



/*
	preleva dall'environment l'eventuale offset delle porte
	di comunicazione
*/
if((off=getenv("OFFSET_SCADA_PORT"))==NULL)
	offset = 0;
else
	offset = atoi(off);


/*
	setta il numero di video collegabili
*/
ele_task_rete[TASK_RETE_MMI].numero_conn = num_video;

printf("Attivazione Driver Rete\n");

for(i=0;i<NUM_ELE_TASK_RETE;i++)
	{
	int status;

	OpenFileLog(i);
	ele_task_rete[i].port += offset;
	SetRootPriv();
	for(j=0;j<ele_task_rete[i].numero_conn;j++)
		{
		rete_th[i].fp[j] = -1;
		rete_th[i].fp_in[j] = -1;
                status=pthread_create (&(rete_th[i].input[j]),pthread_attr_default,
                        (pthread_startroutine_t)ConnessioneInput,
			(pthread_addr_t)(i*10000+j));
		check(status,"pthread create ConnessioneInput\n");
		}
        status=pthread_create (&(rete_th[i].output),pthread_attr_default,
                        (pthread_startroutine_t)ConnessioneOutput,
			(pthread_addr_t)i);
		check(status,"pthread create ConnessioneOutput\n");
	UnSetRootPriv();
	}

while(1)
	{
/**
	printf("Verifica stato task di rete\n");
	for(i=0;i<NUM_ELE_TASK_RETE;i++)
		if(!ele_task_rete[i].stato)
			printf("%s non attiva\n",ele_task_rete[i].descr);
**/
	wai(18);
	}
}

static void ConnessioneInput(pthread_addr_t arg)
{
pthread_addr_t status;
short size;
QUEUE_PACKET messaggio;
QUEUE_PACKET messaggio_diagno;
SPO_STATO diagno_porta;
short numConn,progConn;

numConn = (int)arg/10000;
progConn = (int)arg - numConn*10000;

printf("connessione input [%s]   numConn = %d progConn = %d prio = %d\n",
	ele_task_rete[numConn].descr,numConn,progConn,pthread_getprio(pthread_self()));	

messaggio.que = ele_task_rete[numConn].coda_input;
messaggio.flg = MSG_WAIT;
messaggio.wto = 0;
messaggio.amsg = malloc(cd[numConn].dim);

while(1)
{
while((rete_th[numConn].fp[progConn] = 
	socketserver(ele_task_rete[numConn].port+progConn,
	&(rete_th[numConn].fp_in[progConn])))<0)
   	{
	p_sospendi(500);p_sospendi(500);p_sospendi(500);p_sospendi(500);
   	}
/*
	invio il messaggio di porta ONLINE
*/
ConnFileLog(numConn,progConn,1);
diagno_porta.nodo = progConn;
diagno_porta.mess = STATOPORTA;
diagno_porta.porta = progConn;
diagno_porta.stato = ONLINE;
messaggio_diagno.que = ele_task_rete[numConn].coda_input;
messaggio_diagno.flg = MSG_WAIT;
messaggio_diagno.wto = 0;
messaggio_diagno.lmsg = sizeof(SPO_STATO);
messaggio_diagno.amsg = (char*)&diagno_porta;
enqueue(&messaggio_diagno);
printf("Inviato messaggio porta ONLINE connessione %d\n",diagno_porta.nodo);

while(1)
   {
	int ret;
   /*
	   leggo il primo short contenente la dimensione del messaggio
   */
   //printf("Leggo la size dalla rete [%d]\n",rete_th[(int)arg].fp[progConn]);
   if(readn(rete_th[numConn].fp[progConn],&size,sizeof(short))!=sizeof(short))
   	{
	break;
	}
   
   /*
	   leggo il messaggio
   */
   if(readn(rete_th[numConn].fp[progConn],&messaggio.amsg[sizeof(short)],
					size-sizeof(short))!=size-sizeof(short))
   	{
	break;
	}
   memcpy(messaggio.amsg,&progConn,sizeof(short));
   messaggio.lmsg = size;
   enqueue(&messaggio);
   WriteFileLog(numConn,progConn,1,(int)messaggio.amsg[sizeof(short)],size);
   //printf("letto messaggio size = %d\n",size);
   }
/*
	termino la connessione
*/
shutdown(rete_th[numConn].fp[progConn],2);
rete_th[numConn].fp[progConn] = -1;
ConnFileLog(numConn,progConn,0);
/*
	invio il messaggio di porta OFFLINE
*/
diagno_porta.nodo = progConn;
diagno_porta.mess = STATOPORTA;
diagno_porta.porta = progConn;
diagno_porta.stato = OFFLINE;
messaggio_diagno.que = ele_task_rete[numConn].coda_input;
messaggio_diagno.flg = MSG_WAIT;
messaggio_diagno.wto = 0;
messaggio_diagno.lmsg = sizeof(SPO_STATO);
messaggio_diagno.amsg = (char *)&diagno_porta;
enqueue(&messaggio_diagno);
printf("Inviato messaggio porta progConn connessione %d\n",diagno_porta.nodo);
}

}

static void ConnessioneOutput(pthread_addr_t arg)
{
QUEUE_PACKET messaggio;
short size;
short progConn;
short numConn = (short)arg;


printf("routine ConnessioneOutput [%s] prio = %d\n",ele_task_rete[numConn].descr,pthread_getprio(pthread_self()));

messaggio.que = ele_task_rete[numConn].coda_output;
messaggio.flg = MSG_WAIT;
messaggio.wto = 0;
messaggio.amsg = malloc(cd[numConn].dim);

while(1)
	{
	dequeue(&messaggio);
	memcpy(&progConn,messaggio.amsg,sizeof(short));
	if(rete_th[numConn].fp[progConn]<0)
		continue;  // manca la connessione in rete
	size=messaggio.lmsg;
        WriteFileLog(numConn,progConn,0,messaggio.amsg[sizeof(short)],size);
/*
	printf("====> ConnessioneOutput:Prelevato mess size %d write %d - %d\n",
			size,rete_th[numConn].fp[progConn],progConn);
*/
	if(writen(rete_th[numConn].fp[progConn],&size,sizeof(short))!=
			sizeof(short))
   		{
		continue;
		}
	if(writen(rete_th[numConn].fp[progConn],
			&messaggio.amsg[sizeof(short)],size-
			sizeof(short))!= size-sizeof(short))
   		{
		continue;
		}
	}

}



static void OpenFileLog(int p)
{
char file_log[FILENAME_MAX+1];
char *app;

rete_th[p].fp_log = NULL;

if((app=getenv("DEBUG_NET"))==NULL)
	return;
if(strcmp(app,"YES")!=0)
	return;

	sprintf(file_log,"logRete_%d.log",p);
	rete_th[p].fp_log = fopen(file_log,"w");
	fprintf(rete_th[p].fp_log, "%s\n\n",ele_task_rete[p].descr);

fflush(rete_th[p].fp_log);
}

static void WriteFileLog(int p,int c,int ricez,int mess, int size)
{

if(rete_th[p].fp_log == NULL)
	return;

if(ricez == 1)
	fprintf(rete_th[p].fp_log,
"%2.0f:%2.0f:%2.0f %2.0f-%2.0f-%4.0f prog [%d] ric. mess. tipo [%d] size [%d]\n",
		dbadv[db_ora],dbadv[db_minuti],dbadv[db_secondi],
		dbadv[db_giorno],dbadv[db_mese],dbadv[db_anno],
			c,mess,size);
else
	fprintf(rete_th[p].fp_log,
"%2.0f:%2.0f:%2.0f %2.0f-%2.0f-%4.0f prog [%d] inv. mess. tipo [%d] size [%d]\n",
		dbadv[db_ora],dbadv[db_minuti],dbadv[db_secondi],
		dbadv[db_giorno],dbadv[db_mese],dbadv[db_anno],
			c,mess,size);

fflush(rete_th[p].fp_log);
}

static void ConnFileLog(int p,int c,int stato)
{

if(rete_th[p].fp_log == NULL)
	return;

if(stato == 1)
	fprintf(rete_th[p].fp_log,
	"%2.0f:%2.0f:%2.0f %2.0f-%2.0f-%4.0f Attivata connessione prog %d\n",
		dbadv[db_ora],dbadv[db_minuti],dbadv[db_secondi],
		dbadv[db_giorno],dbadv[db_mese],dbadv[db_anno],c);
else
	fprintf(rete_th[p].fp_log,
	"%2.0f:%2.0f:%2.0f %2.0f-%2.0f-%4.0f Terminata connessione prog %d\n",
		dbadv[db_ora],dbadv[db_minuti],dbadv[db_secondi],
		dbadv[db_giorno],dbadv[db_mese],dbadv[db_anno],c);

fflush(rete_th[p].fp_log);
}
