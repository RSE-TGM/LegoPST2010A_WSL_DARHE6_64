/**********************************************************************
*
*       C Source:               net_read.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Tue Oct 22 12:10:30 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: net_read.c-8.1.1.1.1 %  (%full_filespec: net_read.c-8.1.1.1.1:csrc:1 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)net_read.c	5.2\t2/7/96";
/*
   modulo net_read.c
   tipo 
   release 5.2
   data 2/7/96
   reserved @(#)net_read.c	5.2
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
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
#include "sim_ipc.h"
#include "comandi.h"
#include "libnet.h"
#include <Rt/RtDbPunti.h>
#include <Rt/RtErrore.h>
#include <Rt/RtMemory.h>

#define MAXHOSTNAMELEN 256


int id_msg_sked;                  /* id coda messaggi  da processi read */

int id_msg_pert;                  /* id coda messaggi  perturbazioni  */

void fine_net();

int fp; 			     /* id socket */

RtDbPuntiOggetto dbpunti;
RtDbPuntiOggetto dbpunti_ext;
RtErroreOggetto errore;

float *area_dati;        /* puntatore all'inizio dell'area dati delle task */
int ini_task;

#if defined UNIX
struct msqid_ds  buf;
#endif

#if defined AIX
#define MAX_MSG_QUEUE 60
#else
#define MAX_MSG_QUEUE 30
#endif

int        _MAX_SNAP_SHOT;
int        _MAX_BACK_TRACK;
int        _MAX_CAMPIONI;
int        _NUM_VAR;
int        _MAX_PERTUR;
int        _SPARE_SNAP;
int        _PERT_CLEAR;
SIMULATOR *simpar;


extern void testata(char *, char *);
extern int socketlettura(char*,int);
extern int socketscrittura(char*,int);
int ConvFloatPert(float *, TIPO_PERT *, int , int );
int ConvertiPert(TIPO_PERT *,int );
int InserisciPert(TIPO_PERT *, int );


int main(argc,argv)
int argc;
char **argv;
{
int formato_dati;
float i;
MSG_NET messaggio;
MSG_PERT messaggio_pert;
int shr_usr_key;                   /* chiave utente per shared  */
struct msqid_ds *msg_stat;
int dati_letti;
int j,k,num_var_graf;
FILE *fp_s02;
char *appoggio;
int indice_net_read;   /* indice del processo net_read */
int legge_s02 = 0;     /* se 1 e' slave e non legge S02 */
int macchina_slave;

int numero_ricezioni;
int nread;
int ii,jj;
TIPO_PERT *pert_tmp;
TIPO_PERT Pert_Tmp[50];
int nblocchiread;
static int prima_volta=1;
float *pert_float;
char iosono[FILENAME_MAX];
static int PrimaVolta=1;
char ptr[MAXHOSTNAMELEN];


/* redirezione output  e stampa versione */
testata("net_read",SccsID);

 /*   installazione signal    */
signal(SIGTERM,fine_net);

formato_dati=atoi(argv[2]);
indice_net_read=atoi(argv[3]);
legge_s02=atoi(argv[4]);
macchina_slave = legge_s02;
printf("processo read da %s  indice %d formato_dati %d slave=%d\n",
		argv[1],indice_net_read,formato_dati,macchina_slave);

shr_usr_key = atoi((char *)getenv("SHR_USR_KEY"));

/* creazione o aggancio coda messaggi read->sked */
msg_create_fam(shr_usr_key,0);

/*
   Se la macchina e' master non legge S02 e si aggancia alle SHM esistenti,
   altrimenti lo riceve e poi si aggancia alla SHM leggendolo. In questo caso
   legge anche i parametri del file Simulator che vengono passati come 
   parametri da net_sked (in sked_S02).
*/
   simpar = (SIMULATOR*)calloc(1,sizeof(SIMULATOR));
   if(legge_s02 == 0)   /* MASTER */
	{
	errore = RtCreateErrore(RT_ERRORE_TERMINALE,"net_read");
	dbpunti = RtCreateDbPunti(errore,NULL,DB_PUNTI_INT,simpar);
	}
   for(ii=0;ii<argc-1;ii++)
           {
           if(strcmp(argv[ii],ARGV_N_SNAP)==0)
               _MAX_SNAP_SHOT     = atoi(argv[ii+1]);
           if(strcmp(argv[ii],ARGV_N_BKTK)==0)
               _MAX_BACK_TRACK    = atoi(argv[ii+1]);
           if(strcmp(argv[ii],ARGV_N_CAMP_CR)==0)
               _MAX_CAMPIONI      = atoi(argv[ii+1]);
           if(strcmp(argv[ii],ARGV_N_VAR_CR)==0)
               _NUM_VAR           = atoi(argv[ii+1]);
           if(strcmp(argv[ii],ARGV_N_PERT_ACTIVE)==0)
               _MAX_PERTUR        = atoi(argv[ii+1]);
           if(strcmp(argv[ii],ARGV_N_SPARE)==0)
               _SPARE_SNAP        = atoi(argv[ii+1]);
           if(strcmp(argv[ii],ARGV_N_PERTCL)==0)
               _PERT_CLEAR        = atoi(argv[ii+1]);
           }
   simpar->max_snap_shot  = _MAX_SNAP_SHOT;
   simpar->max_back_track = _MAX_BACK_TRACK;
   simpar->max_campioni   = _MAX_CAMPIONI;
   simpar->num_var        = _NUM_VAR;
   simpar->max_pertur     = _MAX_PERTUR;
   simpar->spare_snap     = _SPARE_SNAP;
   simpar->pert_clear     = _PERT_CLEAR;
   printf("\t net_read: [%d] [%d] [%d] [%d] [%d] [%d] [%d]\n",
                _MAX_SNAP_SHOT,_MAX_BACK_TRACK,_MAX_CAMPIONI,_NUM_VAR,
                _MAX_PERTUR,_SPARE_SNAP,_PERT_CLEAR);
   printf("coda di messaggi di net_read=%d\n",shr_usr_key+ID_MSG_SKED);

/* manda la conferma di creazione sked */
messaggio.mtype=ACKOWNLEDGE;
msg_snd(id_msg_sked,&messaggio,sizeof(HEADER_NET),!IPC_NOWAIT);

/* creazione socket */
fp=socketlettura(argv[1],0);

while(1)
{
	/* legge dalla rete */
	dati_letti=readn(fp,(char *)&messaggio.header_net,sizeof(HEADER_NET));
	memcpy(&messaggio.header_net.lun,converti_int_f
			(&(messaggio.header_net.lun),RICEZIONE,formato_dati),
			sizeof(int));
	memcpy(&messaggio.header_net.codice,converti_short_f
			(&(messaggio.header_net.codice),RICEZIONE,
			formato_dati),sizeof(short));
if( (dati_letti!=sizeof(HEADER_NET)) && (dati_letti!=0) )
	{
        printf("\t dati_letti=%d\n",dati_letti);
        gethostname(ptr,MAXHOSTNAMELEN);
        strcpy(iosono,ptr);
        printf("\t iosono=[%s]\n",iosono);
	if(shutdown(fp,2)!=0)
		perror("net_read");
	messaggio.header_net.tasksorg=(-1);
	messaggio.header_net.taskdest=(-1);
	messaggio.header_net.dest=getindbyname(iosono);
	messaggio.header_net.sorg=getindbyname(argv[1]);
	messaggio.header_net.tipo=ERRORE;
	messaggio.header_net.lun=0;
	messaggio.header_net.codice=CONNESSIONE_CHIUSA;

	/* trasmette a sked attendendo che si liberi lo spazio
	   per il messaggio nella coda */
	if(msg_snd(id_msg_sked,&messaggio,
		sizeof(HEADER_NET)+messaggio.header_net.lun,!IPC_NOWAIT)<0)
		{
		perror("trasmissione su coda sked");
		exit(0);
		}
	exit(0);
	}
/**********
if( (dati_letti==0) )
     printf("\t\t\t DATI LETTI==0 [%d]\n",dati_letti);
**********/

if(dati_letti==sizeof(HEADER_NET))
   {
   /* assegna all'interno dell'header l'indice del processo net_read */
	messaggio.header_net.sorg=indice_net_read;

   if( (messaggio.header_net.tipo==DATISNAP)||
       (messaggio.header_net.tipo==DATIPERT)||
       (messaggio.header_net.tipo==DATISTARTUP) )
     {
     if (messaggio.header_net.tipo==DATISNAP)
        {
        pert_tmp = (TIPO_PERT*)calloc(2*_MAX_PERTUR,sizeof(TIPO_PERT));
/* 
        Ciclo delle letture dai dati dello snapshot .
        Avendo gia' letto la parte header si legge dapprima la parte dati
        del primo pacchetto che e' sempre presente e successivamente i
        messaggi nelle parti Header e dati.
        ATTENZIONE, se si trattasse di spedizioni da diversi slave
        ciascun processo net_read master riceverebbe dallo slave a
        cui e' dedicato.
*/
/*      1) Puntatore e area dati */
	ini_task=RtDbPInizioModelli(dbpunti,messaggio.header_net.tasksorg);
        area_dati=RtDbPPuntData(dbpunti);
        numero_ricezioni = messaggio.header_net.codice;

/*      2) Lettura primo pacchetto dati */
        dati_letti=readn(fp, (char*)(&area_dati[ini_task]),
                            messaggio.header_net.lun);
        if( dati_letti!=messaggio.header_net.lun )
            fprintf(stderr,"net_read: errore lettura n. %d dati_snap\n", ii+1);
#if defined DEBUG_RICEZIONE
        else
            printf("net_read: Lettura primo pacch. dati letti=attesi=%d\n", 
                    dati_letti);
#endif
        nread = messaggio.header_net.lun;
#if defined DEBUG_VALORI
/*      Stampa dati letti */
        for(k=0;k<nread/sizeof(float);k++)
           {
           printf("\t area_dati_ricevuta[%d]=%f\n",
                     ini_task+k,area_dati[ini_task+k] );
           }
#endif
/*      3) Lettura degli eventuali successivi n-1 pacchetti */
        for(ii=1;ii<numero_ricezioni;ii++)
           {
/*         3.1) Lettura header */
	   dati_letti=readn(fp,(char*)&messaggio.header_net,sizeof(HEADER_NET));
           if(dati_letti!=sizeof(HEADER_NET))
	       {
               fprintf(stderr,"net_read: errore lettura n. %d header_snap\n",
                       ii+1);
	       }
/*         3.2) Lettura parte dati */
#if defined DEBUG_RICEZIONE
           printf("net_read: Ricevo in posizione %d attendendo=%d dati\n",
                   ini_task+nread/sizeof(float),messaggio.header_net.lun);
#endif
           dati_letti=readn(fp,
                            (char*)(&area_dati[ini_task+nread/sizeof(float)]),
                            messaggio.header_net.lun);
           if( dati_letti!=messaggio.header_net.lun )
             fprintf(stderr,"net_read: errore lettura n. %d dati_snap\n", ii+1);
#if defined DEBUG_RICEZIONE
           else
             fprintf(stderr,"net_read: Lettura n.%d dati_letti=attesi=%d\n",
                       ii+1, dati_letti);
#endif
#if defined DEBUG_VALORI
/*         Stampa dati letti */
           for(k=nread/sizeof(float);
               k<nread/sizeof(float)+dati_letti/sizeof(float);k++)
              printf("\t Area_Dati_Ricevuta[%d]=%f\n",
                     ini_task+k,
                     area_dati[ini_task+k]);
#endif
           nread += messaggio.header_net.lun;
           } /* Fine ciclo letture pacchetti successivi */

/*      4) Conversione globale dati ricevuti */
        for(k=0;k<nread/sizeof(float);k++)
           {
           memcpy(&area_dati[ini_task+k],
                     converti_float_f(&area_dati[ini_task+k],
                     RICEZIONE,formato_dati),
                     sizeof(float));
#if defined DEBUG_VALORI
/*
           printf("\t area_dati_ricevuta[%d]=%f\n",
                     ini_task+k,area_dati[ini_task+k] );
*/
#endif
           }

/* 
        5) RICEZIONE DELLE PERTURBAZIONI 
        Ciclo delle letture delle perturbazioni come parte header e
        parte dati organizzati a blocchi di TIPO_PERT..
*/
/*      5.1) Lettura header */
	dati_letti=readn(fp,(char*)&messaggio.header_net,sizeof(HEADER_NET));
        if(dati_letti!=sizeof(HEADER_NET))
	   {
           fprintf(stderr,"net_read: errore lettura perturbazioni\n",
                   ii+1);
	   }
#if defined DEBUG_RICEZIONE
        else
           printf("net_read: Letto header pert; num. ricezioni=%d\n",
                    messaggio.header_net.codice);
#endif
        numero_ricezioni = messaggio.header_net.codice;
        nblocchiread = 0;
        for(ii=0;ii<numero_ricezioni;ii++)
           {
/*         5.2) Lettura parte dati */
#if defined DEBUG_RICEZIONE
           printf("net_read: Attendendo=%d pert (%d TIPO_PERT), lette=%d\n",
                   messaggio.header_net.lun,
                   messaggio.header_net.lun/sizeof(TIPO_PERT),
                   nblocchiread);
#endif
           pert_float = (float*)calloc(messaggio.header_net.lun,sizeof(float));
           dati_letti=readn(fp, (char*)pert_float,
                            messaggio.header_net.lun);

/*         5.3) Conversione globale dati ricevuti */
           for(k=0;k<messaggio.header_net.lun/sizeof(float);k++)
              memcpy(&pert_float[k], converti_float_f(&pert_float[k],
                     RICEZIONE,formato_dati), sizeof(float));

/*         Le perturbazioni, lette (float) si convertono a TIPO_PERT */
           ConvFloatPert(pert_float,&pert_tmp[nblocchiread],
                         messaggio.header_net.lun,formato_dati);
           if( dati_letti!=messaggio.header_net.lun )
             fprintf(stderr,"net_read: errore lettura n. %d datipert\n", ii+1);
#if defined DEBUG_RICEZIONE
           else
             fprintf(stderr,"net_read: Lettura n.%d dati_letti=attesi=%d\n",
                       ii+1, dati_letti,formato_dati);
#endif
#if defined DEBUG_PERTURBAZIONI
/*         Stampa perturbazioni lette */
           for(k=nblocchiread;
               k<nblocchiread+messaggio.header_net.lun/sizeof(TIPO_PERT);k++)
                 if(pert_tmp[k].tipo!=1)
                   printf("%2d) pos=%2d tipo=%2d ind=%2d rat=%9f t=%9f p=%9f\n",
                         k,
                         pert_tmp[k].posizione,
                         pert_tmp[k].tipo,
                         pert_tmp[k].indirizzo,
                         pert_tmp[k].rateo_durata,
                         pert_tmp[k].t,
                         pert_tmp[k].post);
#endif
           nblocchiread += messaggio.header_net.lun/sizeof(TIPO_PERT);

/*         5.4) Lettura header eseguita numero_ricezioni-1 volte */
           if ( ii<numero_ricezioni-1 )
              {
              dati_letti=readn(fp,(char*)&messaggio.header_net,sizeof(HEADER_NET));
              if(dati_letti!=sizeof(HEADER_NET))
                  fprintf(stderr,"net_read: errore lettura n. %d header_snap\n",
                          ii+1);
              } /* Fine ciclo letture */
           free(pert_float);
                    PrimaVolta=1;
           } /* Fine ciclo letture */

/*      6) Conversione globale perturbazioni ricevute */
        ConvertiPert(pert_tmp,formato_dati);
        InserisciPert(pert_tmp,macchina_slave);

	/*libera_shr();*/
	dati_letti=0;
	messaggio.header_net.lun=0;
        free(pert_tmp);
        }

     if (messaggio.header_net.tipo==DATIPERT)
	{
	dati_letti=readn(fp,(char*)&messaggio_pert,
			messaggio.header_net.lun);
/*      Convert eventualmente i dati */
#if defined REPLAY
	memcpy(&messaggio_pert.perturbazione.runtime_replay,converti_int_f(
		 &(messaggio_pert.perturbazione.runtime_replay),
			RICEZIONE,formato_dati),sizeof(int));
#endif
	memcpy(&messaggio_pert.perturbazione.posizione,converti_int_f(
		 &(messaggio_pert.perturbazione.posizione),
			RICEZIONE,formato_dati),sizeof(int));
	memcpy(&messaggio_pert.perturbazione.tipo,converti_int_f(
		 &(messaggio_pert.perturbazione.tipo),
			RICEZIONE,formato_dati),sizeof(int));
	memcpy(&messaggio_pert.perturbazione.indirizzo,converti_int_f(
		 &(messaggio_pert.perturbazione.indirizzo),
			RICEZIONE,formato_dati),sizeof(int));
	memcpy(&messaggio_pert.perturbazione.valore_delta,converti_float_f(
		 &(messaggio_pert.perturbazione.valore_delta),
			RICEZIONE,formato_dati),sizeof(float));
	memcpy(&messaggio_pert.perturbazione.rateo_durata,converti_float_f(
		 &(messaggio_pert.perturbazione.rateo_durata),
			RICEZIONE,formato_dati),sizeof(float));
	memcpy(&messaggio_pert.perturbazione.t,converti_float_f(
		 &(messaggio_pert.perturbazione.t),
			RICEZIONE,formato_dati),sizeof(float));
	memcpy(&messaggio_pert.perturbazione.period,converti_float_f(
		 &(messaggio_pert.perturbazione.period),
			RICEZIONE,formato_dati),sizeof(float));
	memcpy(&messaggio_pert.perturbazione.phase,converti_float_f(
		 &(messaggio_pert.perturbazione.phase),
			RICEZIONE,formato_dati),sizeof(float));
	memcpy(&messaggio_pert.perturbazione.meanvalue,converti_float_f(
		 &(messaggio_pert.perturbazione.meanvalue),
			RICEZIONE,formato_dati),sizeof(float));
	memcpy(&messaggio_pert.perturbazione.wide,converti_float_f(
		 &(messaggio_pert.perturbazione.wide),
			RICEZIONE,formato_dati),sizeof(float));
	memcpy(&messaggio_pert.perturbazione.t_null_var,converti_float_f(
		 &(messaggio_pert.perturbazione.t_null_var),
			RICEZIONE,formato_dati),sizeof(float));
/*      Trasmette a sked attendendo che si liberi lo spazio
                per il messaggio nella coda */

printf("RICEVUTA PERTURBAZIONE tipo=%d %f\n", 
        messaggio_pert.perturbazione.tipo,
        messaggio_pert.perturbazione.rateo_durata);


        messaggio_pert.mtype=1;
        if(msg_snd(id_msg_pert,&messaggio_pert,
		   sizeof(TIPO_PERT),!IPC_NOWAIT)<0)
           {
           perror("trasmissione su coda sked perturbazioni");
           exit(0);
           }
	dati_letti=0;
	messaggio.header_net.lun=0;
	}

     if (messaggio.header_net.tipo==DATISTARTUP)
	{
	appoggio=(char*)malloc(messaggio.header_net.lun);
        dati_letti=readn(fp,appoggio,
                         messaggio.header_net.lun);
/*      Qui non fa nessuna conversione */
#if defined SCO_UNIX
        fp_s02=fopen("S02_SCO","w");
#endif
#if defined AIX
        fp_s02=fopen("S02_AIX","w");
#endif
#if defined ULTRIX
        fp_s02=fopen("S02_ULTRIX","w");
#endif
#if defined OSF1
        fp_s02=fopen("S02_OSF1","w");
#endif
#if defined LINUX
        fp_s02=fopen("S02_LINUX","w");
#endif
#if defined VMS
        fp_s02=fopen("S02_VMS","w");
#endif
        fwrite(appoggio,messaggio.header_net.lun, 1,fp_s02);
        fclose(fp_s02);
	free(appoggio);
	messaggio.header_net.lun=0;
	dati_letti=0;
        if(legge_s02 == 1)
           {
/*         Creazione o aggancio shared-memory   */
           errore = RtCreateErrore(RT_ERRORE_TERMINALE,"net_read");
#if defined SCO_UNIX
           dbpunti = RtCreateDbPunti(errore,"S02_SCO",DB_PUNTI_INT,simpar);
#endif
#if defined AIX
           dbpunti = RtCreateDbPunti(errore,"S02_AIX",DB_PUNTI_INT,simpar);
#endif
#if defined ULTRIX
           dbpunti = RtCreateDbPunti(errore,"S02_ULTRIX",DB_PUNTI_INT,simpar);
#endif
#if defined OSF1
           dbpunti = RtCreateDbPunti(errore,"S02_OSF1",DB_PUNTI_INT,simpar);
#endif
#if defined LINUX
           dbpunti = RtCreateDbPunti(errore,"S02_LINUX",DB_PUNTI_INT,simpar);
#endif
#if defined VMS
           dbpunti = RtCreateDbPunti(errore,"S02_VMS",DB_PUNTI_INT,simpar);
#endif
           free(simpar);
           }
        }
     }
  else
     {
     dati_letti=readn(fp,(char*)&messaggio.dato[0],messaggio.header_net.lun);
     for(j=0;j<(messaggio.header_net.lun/sizeof(float));j++)
         {
         memcpy(&messaggio.dato[j],converti_float_f(&messaggio.dato[j],
                RICEZIONE,formato_dati),sizeof(float));
         }
     }

	if(dati_letti!=messaggio.header_net.lun)
	{
		if(shutdown(fp,2)!=0)
			perror("net_read");
        gethostname(ptr,MAXHOSTNAMELEN);
        strcpy(iosono,ptr);
        printf("\t iosono=[%s]\n",iosono);
		messaggio.header_net.tasksorg=(-1);
		messaggio.header_net.taskdest=(-1);
		messaggio.header_net.dest=getindbyname(iosono);
		messaggio.header_net.sorg=getindbyname(argv[1]);
		messaggio.header_net.tipo=ERRORE;
		messaggio.header_net.lun=0;
		messaggio.header_net.codice=CONNESSIONE_CHIUSA;

		/* trasmette a sked attendendo che si liberi lo spazio
	   	per il messaggio nella coda */
		if(msg_snd(id_msg_sked,&messaggio,
		  sizeof(HEADER_NET)+messaggio.header_net.lun,!IPC_NOWAIT)<0)
		  {
		  perror("trasmissione su coda sked");
		  exit(0);
		  }
	        exit(0);
	}

	messaggio.mtype=messaggio.header_net.tipo;

	if((messaggio.mtype==DATIGRAF)&&(messaggio.header_net.flag==(-1)))
		{
		/* trasmette a sked attendendo che si liberi lo spazio
                   per il messaggio nella coda */
                if(msg_snd(id_msg_sked,&messaggio,
		  sizeof(HEADER_NET),!IPC_NOWAIT)<0)
                  {
                  perror("trasmissione su coda sked");
                  exit(0);
                  }
		/* copia nella shared memory i valori ricevuti */
		num_var_graf=messaggio.header_net.lun/(sizeof(float)*2);
		/*blocca_shr();*/
                 for(k=0;k<num_var_graf*2;k=k+2)
                    {
                    j=messaggio.dato[k];
/****
                    (*var)[j]=messaggio.dato[k+1];
***/
                    }
		/*libera_shr();*/
		messaggio.header_net.lun=0;
		}
	else
	  if(messaggio.mtype!=DATIPERT)
		{
/*
                Trasmette a sked attendendo che si liberi lo spazio
                per il messaggio nella coda 
*/
 		/*
                printf("Ricevuto pacchetto da %s\n",argv[1]);
		printf("\n net_read : Spedisco su coda %d byte (type=%d)\n",
			sizeof(HEADER_NET)+messaggio.header_net.lun,
                        messaggio.mtype);
                */
#if defined UNIX
		msgctl(id_msg_sked,IPC_STAT,&buf);
		while(buf.msg_qnum>MAX_MSG_QUEUE)
			{
			fprintf(stderr,
       "WARNING NET_READ: eccesso di carico code messaggi con NET_SKED (%d)\n",
                                buf.msg_qnum);
			sospendi(50);
			msgctl(id_msg_sked,IPC_STAT,&buf);
			}
#endif
		/*printf("msg_cbytes %d   msg_qnum  %d  msg_qbytes  %d\n",
			buf.msg_cbytes,buf.msg_qnum,buf.msg_qbytes);*/

                if(msg_snd(id_msg_sked,&messaggio,
                           sizeof(HEADER_NET)+messaggio.header_net.lun,
                           !IPC_NOWAIT)<0)
                   {
                   perror("trasmissione su coda sked");
                   exit(0);
                   }
                }

   } /* Fine dati_letti==sizeof(HEADER_NET) */
} /* Fine while */
} /* Fine main */

void fine_net(signum,code,scp)
   int signum, code;
   struct sigcontext *scp;
{
printf("-----------------------NET_READ------------ ricevuto segnale\n");
   if( signum == SIGTERM )
     {
      printf("NET_READ operazioni di chiusura\n");
      msg_close_fam();
      if(shutdown(fp,2)!=0)
        {
	perror("net_read");
        printf("\t\t errno=%d\n",errno);
        if ( errno == EBADF )
           printf("\t\t errno=EBADF\n");
        if ( errno == ENOTSOCK )
           printf("\t\t errno=ENOTSOCK\n");
        }
      exit(0);
     }
}





/*
    Converte il vettore di strutture TIPO_PERT composto 
    da interi (5) e da float.
*/
int ConvertiPert(TIPO_PERT *pert,int formato)
{
int k;

    for(k=0;k<2*_MAX_PERTUR;k++)
       {
#if defined REPLAY
       memcpy(&pert[k].runtime_replay,
              converti_int_f(&pert[k].runtime_replay, RICEZIONE,formato), 
              sizeof(int));
#endif
       memcpy(&pert[k].posizione,
              converti_int_f(&pert[k].posizione, RICEZIONE,formato), 
              sizeof(int));
       memcpy(&pert[k].tipo,
              converti_int_f(&pert[k].tipo, RICEZIONE,formato), 
              sizeof(int));
       memcpy(&pert[k].indirizzo,
              converti_int_f(&pert[k].indirizzo, RICEZIONE,formato), 
              sizeof(int));
       memcpy(&pert[k].esaminata,
              converti_int_f(&pert[k].esaminata, RICEZIONE,formato), 
              sizeof(int));

       memcpy(&pert[k].valore_delta,
              converti_float_f(&pert[k].valore_delta,RICEZIONE,formato),
              sizeof(float));
       memcpy(&pert[k].rateo_durata,
              converti_float_f(&pert[k].rateo_durata,RICEZIONE,formato),
              sizeof(float));
       memcpy(&pert[k].t,
              converti_float_f(&pert[k].t,RICEZIONE,formato),
              sizeof(float));
       memcpy(&pert[k].period,
              converti_float_f(&pert[k].period,RICEZIONE,formato),
              sizeof(float));
       memcpy(&pert[k].phase,
              converti_float_f(&pert[k].phase,RICEZIONE,formato),
              sizeof(float));
       memcpy(&pert[k].meanvalue,
              converti_float_f(&pert[k].meanvalue,RICEZIONE,formato),
              sizeof(float));
       memcpy(&pert[k].wide,
              converti_float_f(&pert[k].wide,RICEZIONE,formato),
              sizeof(float));
       memcpy(&pert[k].t_null_var,
              converti_float_f(&pert[k].t_null_var,RICEZIONE,formato),
              sizeof(float));
       memcpy(&pert[k].post,
              converti_float_f(&pert[k].post,RICEZIONE,formato),
              sizeof(float));
       }
}

/*
    Se MASTER inserisce le perturbazioni ricevute dallo SLAVE nell'area
    delle perturbazioni, nella SHM.
    Nel caso in cui a ricevere le pert fosse lo slave (come nel caso di 
    un LOADIC) l'intera area delle pert presenti viene sostituita dalle
    pert ricevute.
    Il limite e' sempre _MAX_PERTUR.
*/
int InserisciPert(TIPO_PERT *pert_ricevute, int slave)
{
TIPO_PERT *pert_locali,*pert_locali_att;
TIPO_PERT *p;
int i,k,h,inserimenti=0;

   if((pert_locali=RtDbPGetPuntPert(dbpunti))==NULL)
      {
      fprintf(stderr,"net_read fallisce l'inserimento delle perturbazioni\n");
      return(-1);
      }
   if((pert_locali_att=RtDbPGetPuntPertAtt(dbpunti))==NULL)
      {
      fprintf(stderr,"net_read fallisce l'inserimento delle pert. att\n");
      return(-1);
      }
   if( slave==1 )
      {
      memcpy(pert_locali,&pert_ricevute[0],
             sizeof(TIPO_PERT)*_MAX_PERTUR);
      memcpy(pert_locali_att,&pert_ricevute[_MAX_PERTUR],
             sizeof(TIPO_PERT)*_MAX_PERTUR);
      return(0);
      }

  for(h=0;h<2;h++)
      {
      if( h==0 )
          {
          p = pert_locali;
          }
      else
          {
          p = pert_locali_att;
          }
      for(i=0;i<_MAX_PERTUR;i++)
         {
         if (pert_ricevute[i+h*_MAX_PERTUR].tipo == -1)
            {
            continue;
            }
         for(k=0;k<_MAX_PERTUR;k++)
            if (p[k].tipo == -1)
               break;
         if( k!=_MAX_PERTUR )
            {
            inserimenti++;
            printf("\t Ins pert n.%d (_att=%d): n.ric:[%d] pos. ins:[%d]\n",
                       inserimenti,h,i,k);
            memcpy(&p[k],&pert_ricevute[i+h*_MAX_PERTUR],sizeof(TIPO_PERT));
            } 
         else
            {
            printf("\t NON INSERISCO k=%d h=%d i=%d tipo=%d\n",
                    k,h,i,pert_ricevute[i+h*_MAX_PERTUR].tipo);
            break;
            }
         }
      }
}

int ConvFloatPert(float *p_float, TIPO_PERT *p, int size, int formato)
{
int i,k,cicli;
div_t rapp;


        cicli = size/sizeof(TIPO_PERT);
        k=0;
        for(i=0;i<cicli;i++)
           {
#if defined REPLAY
           p[i].runtime_replay = (int)p_float[k];k++;
#endif
           p[i].posizione      = (int)p_float[k];k++;
           p[i].tipo           = (int)p_float[k];k++;
           p[i].indirizzo      = (int)p_float[k];k++;
           p[i].esaminata      = (int)p_float[k];k++;
           p[i].valore_delta   = p_float[k];k++;
           p[i].rateo_durata   = p_float[k];k++;
           p[i].t              = p_float[k];k++;
           p[i].period         = p_float[k];k++;
           p[i].phase          = p_float[k];k++;
           p[i].meanvalue      = p_float[k];k++;
           p[i].wide           = p_float[k];k++;
           p[i].t_null_var     = p_float[k];k++;
           p[i].post           = p_float[k];k++;
/*
           printf("%d)   pos=%2d tipo=%2d ind=%2d\n",
                  i,
                  p[i].posizione,
                  p[i].tipo,
                  p[i].indirizzo);
*/
           }
}
/* Fine file */
