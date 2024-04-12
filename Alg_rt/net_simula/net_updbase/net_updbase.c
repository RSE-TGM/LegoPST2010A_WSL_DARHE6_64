/**********************************************************************
*
*       C Source:               net_updbase.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 12:28:20 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: net_updbase.c-5 %  (%full_filespec: net_updbase.c-5:csrc:1 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)net_updbase.c	5.2\t3/4/96";
/*
   modulo net_updbase.c
   tipo 
   release 5.2
   data 3/4/96
   reserved @(#)net_updbase.c	5.2
*/
# include <stdio.h>
# include <errno.h>
# include <string.h>
#include <signal.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/shm.h>
#endif
#if defined VMS
# include"vmsipc.h"
#endif
#include "sim_param.h"
#include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
# include "libnet.h"
#include <Rt/RtDbPunti.h>
#include <Rt/RtErrore.h>
# include <Rt/RtMemory.h>

int id_msg_sked;                  /* id coda messaggi  da processi read */

int id_msg_leg;                  /* id coda messaggi  da processi aus. */

int id_msg_pert;                  /* id coda messaggi  perturbazioni  */

extern int shmvid;                   /* identificativo shm  varabili */

void fine_net();

int fp;                              /* id socket */

int tipo;

RtDbPuntiOggetto dbpunti;
RtDbPuntiOggetto dbpunti_ext;
RtErroreOggetto errore;

float *area_dati;        /* puntatore all'inizio dell'area dati delle task */
int numero_modelli;

main(argc,argv)
int argc;
char **argv[];
{
MSG_NET messaggio_net;
MSG_LEGOGRAF messaggio_legograf;
TIPO_LEGOGRAF conf_lego;
int shr_usr_key;                   /* chiave utente per shared  */
char *app;
int i,k,j;
int sezione;
int dimensione_pacchetto=0;
static int prima_volta=1;
float app_float;
int ini_task;
int ii;
float appoggio;
TIPO_PERT *pert;
SIMULATOR *sim;                    /* Parametro per RtCreateDbPunti */


/* redirezione output  e stampa versione */
testata("net_updbase",SccsID);

 /*   installazione signal    */
#if defined SCO_UNIX 		/*se SCO*/
sigrelse(0);			/*sblocca i segnali*/
#else
sigsetmask(0);                    /* sblocca tutti i segnali */
#endif
signal(SIGTERM,fine_net);

printf("processo net_updbase da %s  %s OK\n",argv[1],argv[2]);

tipo=atoi(argv[2]);

shr_usr_key = atoi((char *)getenv("SHR_USR_KEY"));

/* creazione o aggancio coda messaggi read->sked */
msg_create_fam(shr_usr_key,0);

errore = RtCreateErrore(RT_ERRORE_TERMINALE,"net_updbase");
/* creazione o aggancio shared-memory   */
sim = (SIMULATOR*)calloc(1,sizeof(SIMULATOR));
dbpunti = RtCreateDbPunti(errore,NULL,DB_PUNTI_INT,sim);
if(tipo!=0)
   dbpunti_ext = RtCreateDbPunti(errore,NULL,DB_PUNTI_SHARED,sim);
free(sim);

numero_modelli = RtDbPNumeroModelli(dbpunti);

printf("coda di messaggi di net_updbase=%d\n",shr_usr_key+ID_MSG_SKED);


/* creazione socket */
/* tipo = 0 per lo SLAVE */
if(tipo!=0)
	fp=socketlettura(argv[1],1);
else
	fp=socketscrittura(argv[1],1);


/* manda la conferma di creazione sked */
messaggio_net.mtype=ACKOWNLEDGE;
msg_snd(id_msg_sked,&messaggio_net,sizeof(HEADER_NET),IPC_NOWAIT);

/*
   Attende messaggio da sked con sezione e dimensione dei
   modelli locali.
*/
msg_rcv(id_msg_leg,&messaggio_legograf,sizeof(TIPO_LEGOGRAF),(long)LEGOGRAF,
        !IPC_NOWAIT,TIMEOUT_INF);

memcpy(&conf_lego,&messaggio_legograf.dati,sizeof(TIPO_LEGOGRAF));

printf("---------------------RICEVUTA CONF. NET_UPDBASE\n");
for(i=0;i<numero_modelli;i++)
	{
	if(conf_lego.sezione[i]==1)
		{
		printf("dimensione sezone mod %d=%d\n",
                        i, conf_lego.dimensione[i]);
		dimensione_pacchetto+=conf_lego.dimensione[i];
		}
	}
	

app=(char*)malloc(dimensione_pacchetto);

while(1)
{
if(tipo!=0)
	{
	readn(fp,app,dimensione_pacchetto);
	k=0;
	for(i=0;i<numero_modelli;i++)
		{
		ini_task = RtDbPInizioModelli(dbpunti_ext,i);
		area_dati = RtDbPPuntData(dbpunti_ext);
		if(conf_lego.sezione[i]==1)
		    for(j=0;j<(conf_lego.dimensione[i]/4);j++)
			{
			memcpy(&app_float,&app[k+j*sizeof(float)],
					sizeof(float));
			memcpy(&area_dati[ini_task+j],
			   converti_float_f(&app_float,RICEZIONE,tipo),
				sizeof(float));
/*
                        printf("net_updbase master riceve (ini=%d) %f\n",
                                   ini_task,area_dati[ini_task+j]);
*/
/**
			memcpy(&(*var_lego)[MAX_ALLOC_MODEL*i+j],
			   converti_float_f(&app_float,RICEZIONE,tipo),
				sizeof(float));
**/
			}
		k+=conf_lego.dimensione[i];
		}
	}
else
	{
	/* attende messaggio da sked (sked_legograf) */
  	msg_rcv(id_msg_leg,&messaggio_legograf,sizeof(TIPO_LEGOGRAF),(long)LEGOGRAF,
                !IPC_NOWAIT,TIMEOUT_INF);
	k=0;
/*      Invia i dati a net_updbase master */
	for(i=0;i<numero_modelli;i++)
	   {
		if(conf_lego.sezione[i]==1)
		{
		ini_task = RtDbPInizioModelli(dbpunti,i);
		area_dati = RtDbPPuntData(dbpunti);
                if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		   {
                   fprintf(stderr,
                           "net_updbase slave: indisponibili area pert\n");
		   }
                /*
                else
                  MostraPert(pert,1);
                */


		memcpy(&app[k],&area_dati[ini_task],
			conf_lego.dimensione[i]);
/**
		memcpy(&app[k],&(*var)[MAX_ALLOC_MODEL*i],
			conf_lego.dimensione[i]);
**/

/*              Stampe valori inviati */
/*
                printf("k=%d ini_task=%d dim=%d\n",
                        k,ini_task,conf_lego.dimensione[i]/sizeof(float));
                for(ii=0;ii<conf_lego.dimensione[i]/4;ii++)
                   {
                   memcpy(&appoggio,&app[ii*sizeof(float)],sizeof(float));
                   printf("net_updbase slave invia ii=%d)  %f\n",
                              ii,appoggio);
                   }
                printf("ii=%d\n",ii);
*/
		k+=conf_lego.dimensione[i];
		}

	   }
	writen(fp,&app[0],dimensione_pacchetto);
	}
}
}

#if defined SCO_UNIX
void fine_net(signum)
   int signum;
{
printf("-----------------------NET_UPDBASE--------- ricevuto segnale\n");
   if( signum == SIGTERM )
     {
      printf("NET_UPDBASE operazioni di chiusura\n");
      msg_close_fam();
      if(close(fp)!=0)
        perror("net_read");
      exit(0);
     }
}

#else
void fine_net(signum,code,scp)
   int signum, code;
   struct sigcontext *scp;
{
printf("-----------------------NET_UPDBASE--------- ricevuto segnale\n");
   if( signum == SIGTERM )
     {
      printf("NET_UPDBASE operazioni di chiusura\n");
      msg_close_fam();
      if(close(fp)!=0)
	perror("net_read");
      exit(0);
     }
}
#endif
/* Fine file */

