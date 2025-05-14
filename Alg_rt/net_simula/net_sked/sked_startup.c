/**********************************************************************
*
*       C Source:               sked_startup.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Dec  3 18:47:16 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_startup.c-6.1.1 %  (%full_filespec: sked_startup.c-6.1.1:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_startup.c	5.2\t2/7/96";
/*
   modulo sked_startup.c
   tipo 
   release 5.2
   data 2/7/96
   reserved @(#)sked_startup.c	5.2
*/
#include <stdio.h>
#include <string.h>
# include <errno.h>
#include <unistd.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/shm.h>
#endif
#if defined VMS
# include"vmsipc.h"
#endif
#include <Rt/RtMemory.h>
#include "sim_param.h"
#include "sim_types.h"
#include "sim_ipc.h"
#include "comandi.h"
#include "sked.h"
#include "sked_fun.h"

#if defined SCO_UNIX
#define vfork() fork()
#endif


extern S02      s02_;
extern COLLEGAMENTO collegamento[MAX_MODEL][MAX_MODEL];
extern char     host[MAX_LUN_HOST];
extern int      nmod;
extern int      id_msg_sked;	/* id coda messaggi  da processi read */

int             fp_com[MAX_MODEL];

char           *fp_app[MAX_MODEL];

char           *fp_app_master;

int            *fp_size[MAX_MODEL];

int            *fp_size_master;

int             fp_read[MAX_MODEL];	/* 0 -> task sulla stessa macchina 1
					 * -> task su macchine diverse pid ->
					 * processo lettura */

int             fp_ordini[MAX_MODEL];	/* puntatori dei socket a cui spedire
					 * i comandi, solo per sked master */

int             fp_master;	/* puntatore al socket del MAIN solo per
				 * slave  */

extern int      fp_read_master;

extern int      fp_slave[MAX_MODEL];

extern int      tipo_sked;	/* definisce il tipo di sked SLAVE=0 MASTER=1          */

int             numero_slave;	/* numero di nodi SLAVE, solo per MASTER  */

char            nodi_slave[MAX_SLAVE][MAX_LUN_HOST];
/*
 * nome degli schedulatori slave , solo per MASTER                 
 */

int             numero_macchine;/* numero di nodi SKED, solo per MASTER  */

int             numero_sked;	/* numero nodi SKED disponibili */

int             indice_macchina;/* indice della macchina */

extern char     nodo_master[MAX_LUN_HOST];	/* nome del nodo MASTER */

extern char     host_locale[30];

extern int    _MAX_SNAP_SHOT;
extern int    _MAX_BACK_TRACK;
extern int    _MAX_CAMPIONI;
extern int    _NUM_VAR;
extern int    _MAX_PERTUR;
extern int    _SPARE_SNAP;
extern int    _PERT_CLEAR;

#define MAXARGV 22
#define MAXHOSTNAMELEN 256

void sked_startup()
{
   int             i, j, k;
   int		   kk;
   char            appoggio[10];
   char           *path;
   char           *getenv();
   char           *argv[MAXARGV];
   char           *comando;
   char           *comando_rcp;
   MSG_NET         messaggio;
   int             formato;
   char            ptr[MAXHOSTNAMELEN];

   /* Identificazione macchina host */
   for (i = 0; i < nmod; i++)
       {
       if ( strcmp(s02_.model[i].host,host_locale)!=0 )
         break;
       }
    if( i==nmod ) {
       strcpy(host, host_locale);
    }
    else {
       gethostname(ptr,MAXHOSTNAMELEN);
       strcpy(host, ptr);
    }
   numero_sked = 1;
   if (tipo_sked == MASTER)
      numero_slave = 0;
   else
      numero_slave = 1;
   numero_macchine = 1;


   /* apertura processi di read */

   for (i = 0; i < nmod; i++)
      if (conf_host(s02_.model[i].host, host) == 0)
	 fp_read[i] = 0;
      else
	 fp_read[i] = 1;

   for (i = 0; i < nmod; i++)
      if (fp_read[i] == 1)
      {
	 for (j = 0; j <= i; j++)
	    if (conf_host(s02_.model[i].host, s02_.model[j].host) == 0)
	       break;
	 if (i == j)
	 {
	    if (
                (conf_host(s02_.model[i].host, nodo_master) != 0)
               )
	    {
#if defined AIX
	       formato = 1;
#endif
#if defined ULTRIX
	       formato = 4;
#endif
#if defined OSF1
	       formato = 4;
#endif
#if defined VMS
	       formato = 7;
#endif
#if defined LINUX
	       formato = 4;
#endif
	       if (strcmp(s02_.model[i].sistema_operativo, "AIX") == 0)
		  formato += 0;
	       if (strcmp(s02_.model[i].sistema_operativo, "ULTRIX") == 0)
		  formato += 1;
	       if (strcmp(s02_.model[i].sistema_operativo, "OSF1") == 0)
		  formato += 1;
	       if (strcmp(s02_.model[i].sistema_operativo, "VMS") == 0)
		  formato += 2;
	       if (strcmp(s02_.model[i].sistema_operativo, "LINUX") == 0)
		  formato += 1;
	       if (tipo_sked == MASTER)
		  strncpy(nodi_slave[numero_slave],
			  s02_.model[i].host, MAX_LUN_HOST);
	       numero_slave++;
	       numero_sked++;
	       numero_macchine++;
	       for(kk=0; kk<MAXARGV; kk++)
			argv[kk]= (char *)malloc(FILENAME_MAX+1);
	       comando = (char *) malloc(FILENAME_MAX+1);
	       sprintf(argv[0], "net_read\00");
	       sprintf(argv[1], "%s\00", s02_.model[i].host);
	       sprintf(argv[2], "%d\00", formato);
	       sprintf(argv[3], "%d\00", numero_slave - 1);
	       sprintf(argv[4], "%d\00", 0);
               sprintf(argv[5], "%s\00", ARGV_N_SNAP);
               sprintf(argv[6], "%d\00",_MAX_SNAP_SHOT);
               sprintf(argv[7], "%s\00", ARGV_N_BKTK);
               sprintf(argv[8], "%d\00",_MAX_BACK_TRACK);
               sprintf(argv[9], "%s\00", ARGV_N_CAMP_CR);
               sprintf(argv[10], "%d\00",_MAX_CAMPIONI);
               sprintf(argv[11], "%s\00", ARGV_N_VAR_CR);
               sprintf(argv[12], "%d\00",_NUM_VAR);
               sprintf(argv[13], "%s\00", ARGV_N_PERT_ACTIVE);
               sprintf(argv[14], "%d\00",_MAX_PERTUR);
               sprintf(argv[15], "%s\00", ARGV_N_SPARE);
               sprintf(argv[16], "%d\00",_SPARE_SNAP);
               sprintf(argv[17], "%s\00", ARGV_N_PERTCL);
               sprintf(argv[18], "%d\00",_PERT_CLEAR);
               argv[19] = NULL;
#if defined UNIX
	       sprintf(comando, "%s/net_read\00", getenv("LEGORT_BIN"));
#endif
#if defined VMS
	       sprintf(comando, "%snet_read\00", getenv("LEGORT_BIN"));
#endif
	       printf("sked_startup: attivazione processo net_read da %s formato_dati %d\n",
		      s02_.model[i].host, formato);
	       fp_read[j] = vfork();
	       if (fp_read[i] == 0)
	       {
               execv(comando, argv);
               exit(0);
	       }
	       for(kk=0; kk<MAXARGV; kk++)
			free(argv[kk]);
	       free(comando);	
	       msg_rcv(id_msg_sked, &messaggio, sizeof(HEADER_NET),
		       (long)(ACKOWNLEDGE), !IPC_NOWAIT, TIMEOUT_AUS);
	    } else
	    {
	       fp_read[i] = fp_read_master;
	    }
	 } else
	    fp_read[i] = fp_read[j];
      }
   /* verifica la necessita' di aprire un socket in scrittura */

   for (i = 0; i < nmod; i++)
   {
      fp_size[i] = (int *) malloc(sizeof(int));
      *(fp_size[i]) = 0;
      if (conf_host(s02_.model[i].host, host) == 0)
	 fp_com[i] = 0;
      else
	 fp_com[i] = 1;
   }

   fp_size_master = (int *) malloc(sizeof(int));
   *fp_size_master = 0;

/*
 * for (i = 0; i < nmod; i++)
 *     {
 *     printf("fp_com[i]=%d fp_read[i]=%d fp_slave[i]=%d *(fp_size[i])=%d\n",
 *             fp_com[i],fp_read[i],fp_slave[i],*(fp_size[i]));
 *     }
 */
   for (i = 0; i < nmod; i++)
      if (fp_com[i] == 1)
      {
	 for (j = 0; j <= i; j++)
	 {
	    if (conf_host(s02_.model[i].host, s02_.model[j].host) == 0)
	       break;
	 }
	 if (i == j)
	 {
	 /*   
	  *  printf("%d) Apertura socket verso %s sulla porta %d\n",
	  *         i,s02_.model[i].host,
          *         WRITE_PORT+getindbyname(s02_.model[i].host)); 
	  */    
	    if (fp_slave[j] == 0)
	       fp_com[j] = socketscrittura(s02_.model[j].host, 0);
	    else
	       fp_com[j] = fp_slave[j];
/*
 Allocazione buffer per la comunicazione in rete dei dati tasks.
 viene creato un buffer per macchina (manca un controllo su
 eventuale sforamento dimensionale)
*/ 
	    /* printf("\t\t ALLOCO j=%d 60000byte\n",j); */
	    fp_app[j] = (char *) malloc(60000);
	    /*
	     *
	     * setsockopt(fp_com[j],IPPROTO_TCP,TCP_NODELAY,(char*)0,(int*)0); 
	     */
	    if (tipo_sked == MASTER)
	    {
	       fp_ordini[j] = fp_com[j];
	    } else
	    {
	       if (  
                   (conf_host(s02_.model[j].host, nodo_master)==0)
                  )
	       {
                  /*printf("\t\t fp_master = fp_com[j=%d]\n\n",j);*/
		  fp_master = fp_com[j];
		  fp_app_master = fp_app[j];
		  fp_size_master = fp_size[j]; 
	       }
	    }
	 } else
	 {
	    fp_com[i] = fp_com[j];
	    fp_app[i] = fp_app[j];
	    fp_size[i] = fp_size[j];
	 }
      }
   /* stampa tabella riassuntiva di fp_com 
    * for(i=0;i<nmod;i++) 
    *     if(fp_com[i]>0) 
    *        printf("task %d -> fp_com=%d fp_size=%d\n",
    *                i,fp_com[i], *(fp_size[i])); 
    */ 

   /*
    * attesa task di read for(i=0;i<nmod;i++) if(fp_read[i]==1) {
    * for(j=0;j<=i;j++)
    * if(conf_host(s02_.model[i].host,s02_.model[j].host)==0) break; if(i==j)
    * { if(fp_slave!=0) msg_rcv(id_msg_sked,&messaggio,sizeof(HEADER_NET),
    * (long)ACKOWNLEDGE,!IPC_NOWAIT,TIMEOUT_AUS); } } 
    */

}
