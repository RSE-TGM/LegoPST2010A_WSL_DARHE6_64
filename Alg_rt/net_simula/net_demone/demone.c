/**********************************************************************
*
*       C Source:               demone.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 12:27:15 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: demone.c-5 %  (%full_filespec: demone.c-5:csrc:1 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)demone.c	2.5\t1/19/96";
/*
   modulo demone.c
   tipo 
   release 2.5
   data 1/19/96
   reserved @(#)demone.c	2.5
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <signal.h>


#if defined UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif
#if defined VMS
# include <iodef.h>
#include <types.h>
#include <socket.h>
#include <in.h>
#include <netdb.h>
#include <inet.h>
#include <ucx$inetdef.h>
#endif
#include <Rt/RtMemory.h>
#include "sim_param.h"
#include "sim_types.h"
#include "demone.h"
#include "libnet.h"
#include "comandi.h"
//#include "net_compi_fun.h"


#define  NUMPAR         25         /* numero parametri per execve (old=11)*/
#define  LUN_ENV        FILENAME_MAX         /* lunghezza massima delle var.
                                       di environment passate */

char task_name[LUN_ENV];
char *task_argv[NUMPAR];
char *task_envp[NUMPAR];
char *path;
char *getenv();
int tipo_demone;

void scoda_ordini();

void sig_child();

extern void testata(char *, char *);
int  genera_demone();

MSG_DEMONE messaggio;
int socd;

int main(argc, argv)
int argc;
char *argv[];
{
int ordine;
int ndati;
int checksum;
int i;
int rval;
int ls;
struct sockaddr_in server,client;
char *app_server;
struct hostent *hp, *gethostbyname();
short port;
int pid;
char formato_dati[10];
char sistema_operativo[10];
/* VARIABILI PER output.txt e output.err */
FILE *txt;
FILE *err;


/* redirezione output  e stampa versione */
testata("demone",SccsID);

printf("Inizio demone\n");

tipo_demone=SLAVE;

if(argc<=1) argv[1]=NULL;

if((argc>=1)&&(argv[1]!=NULL))
if(strcmp(argv[1],"MASTER")!=0)
      {
#if defined SCO_UNIX

         sighold(SIGTERM);
#else
	 sigblock(1 <<(SIGTERM-1));      /*  blocca il segnale  */
#endif
      }
else
      {
#if defined SCO_UNIX

      sigrelse(SIGTERM);               /* sblocca il segnale*/
#else

      sigsetmask(0);                    /* sblocca tutti i segnali  */
#endif
      tipo_demone=MASTER;
      }
	  

/* decodifica sistema operativo per conversione dati */
printf("Sistema operativo %s formato dati %s\n",
                (char *)getenv("OS"),(char *)getenv("FORMATO_DATI"));


/*sig_child();*/

/*signal(SIGCLD,SIG_IGN);*/

        path=(char*)malloc(FILENAME_MAX);
        for(i=0;i<NUMPAR;i++)
          {
          task_argv[i]=(char*)malloc(FILENAME_MAX);
          task_envp[i]=(char*)malloc(FILENAME_MAX);
          }

        if(argc>1)
          sprintf(task_argv[1],"%s",argv[1]);

        if(argc==1)
          {
          genera_demone();
          }
	


        socd = socket( AF_INET, SOCK_DGRAM, 0);
        if (socd < 0)
           {
           perror("opening datagram socket");
           exit(1);
           }

#if defined UNIX
	bzero((char*) &server,sizeof(server));
#endif
#if defined VMS
	app_server=(char*)( &server);
	for(i=0;i<sizeof(server);i++)
		app_server[i]=0;
#endif
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	port = SERVER_PORT+tipo_demone;
	server.sin_port = htons(port);

        if (bind(socd, (struct sockaddr*)&server, sizeof(server)) < 0)
           {
           printf("\nDEMONE SLAVE GIA' CARICATO\n");
           exit(1);
           }
        printf("\nDEMONE SLAVE CARICATO\n");


        while(1)
           {
           ls = sizeof(server);
           if(( rval=recvfrom(socd, &messaggio,sizeof(MSG_DEMONE),
                              0, (struct sockaddr * restrict)&client /*server*/, &ls))<= 0)
               {
               perror("reading datagram message");
               exit(1);
               }
           if( rval > 0)
               {
/*             Conversione parametri ricevuti */
               memcpy(&messaggio.tipo,converti_int
                      (&messaggio.tipo,RICEZIONE),sizeof(int));

               memcpy(&messaggio.simul.max_snap_shot,converti_int
                      (&messaggio.simul.max_snap_shot,RICEZIONE),
                      sizeof(int));
               memcpy(&messaggio.simul.max_back_track,converti_int
                      (&messaggio.simul.max_back_track,RICEZIONE),
                      sizeof(int));
               memcpy(&messaggio.simul.max_campioni,converti_int
                      (&messaggio.simul.max_campioni,RICEZIONE),
                      sizeof(int));
               memcpy(&messaggio.simul.num_var,converti_int
                      (&messaggio.simul.num_var,RICEZIONE),
                      sizeof(int));
               memcpy(&messaggio.simul.max_pertur,converti_int
                      (&messaggio.simul.max_pertur,RICEZIONE),
                      sizeof(int));
               memcpy(&messaggio.simul.spare_snap,converti_int
                      (&messaggio.simul.spare_snap,RICEZIONE),
                      sizeof(int));
               memcpy(&messaggio.simul.pert_clear,converti_int
                      (&messaggio.simul.pert_clear,RICEZIONE),
                      sizeof(int));
/*
               printf("client = %s\n",messaggio.host);
               printf("tipo = %d\n",messaggio.tipo);
               printf("messaggio_1= %s\n",messaggio.comando_1);
               printf("messaggio_2= %s\n",messaggio.comando_2);
               printf("\t demone snap=%d\n",messaggio.simul.max_snap_shot);
               printf("\t demone bktk=%d\n",messaggio.simul.max_back_track);
               printf("\t demone camp=%d\n",messaggio.simul.max_campioni);
               printf("\t demone nvar=%d\n",messaggio.simul.num_var);
               printf("\t demone pert=%d\n",messaggio.simul.max_pertur);
               printf("\t demone spar=%d\n",messaggio.simul.spare_snap);
               printf("\t demone pert=%d\n",messaggio.simul.pert_clear);
*/
               scoda_ordini();
               }
           else
	       {
               perror("connection closed");
               }
           }
        exit(0);
}

void scoda_ordini()
{
char app[FILENAME_MAX];
int pid;
int pid_agg_pert;
int stato_figlio;
int fp;

        printf("Chiudo il socket del demone\n");
        if(close(socd)!=0)
           perror("Chiusura socket:");
        shutdown(socd,0);

        switch(messaggio.tipo) 
           {
           case (DEMONE_START_SKED):
		{
		path = getenv("LEGORT_BIN");
#if defined UNIX
   		sprintf(task_name,"%s/net_sked\00",path);
#endif
#if defined VMS
                sprintf(task_name,"%snet_sked\00",path);
#endif

                sprintf(task_argv[0],"net_sked\00");
                sprintf(task_argv[1],"%s\00",messaggio.host);
                sprintf(task_argv[2],"%s\00",messaggio.comando_2);
                sprintf(task_argv[3],"%s\00",ARGV_N_SNAP);
                sprintf(task_argv[4],"%d\00",messaggio.simul.max_snap_shot);
                sprintf(task_argv[5],"%s\00",ARGV_N_BKTK);
                sprintf(task_argv[6],"%d\00",messaggio.simul.max_back_track);
                sprintf(task_argv[7],"%s\00",ARGV_N_CAMP_CR);
                sprintf(task_argv[8],"%d\00",messaggio.simul.max_campioni);
                sprintf(task_argv[9],"%s\00",ARGV_N_VAR_CR);
                sprintf(task_argv[10],"%d\00",messaggio.simul.num_var);
                sprintf(task_argv[11],"%s\00",ARGV_N_PERT_ACTIVE);
                sprintf(task_argv[12],"%d\00",messaggio.simul.max_pertur);
                sprintf(task_argv[13],"%s\00",ARGV_N_SPARE);
                sprintf(task_argv[14],"%d\00",messaggio.simul.spare_snap);
                sprintf(task_argv[15],"%s\00",ARGV_N_PERTCL);
                sprintf(task_argv[16],"%d\00",messaggio.simul.pert_clear);
                task_argv[17] = NULL;

#if defined UNIX
		sprintf(task_envp[0],"LEGO=%s\00",getenv("LEGO"));
		sprintf(task_envp[1],"SHR_USR_KEY=%s\00",
			getenv("SHR_USR_KEY"));
		sprintf(task_envp[2],"SHR_TAV_KEY=%s\00",
			getenv("SHR_TAV_KEY"));
		sprintf(task_envp[3],"LEGORT_BIN=%s\00",
			getenv("LEGORT_BIN"));
		sprintf(task_envp[4],"OS=%s\00",
                        getenv("OS"));
                sprintf(task_envp[5],"FORMATO_DATI=%s\00",
                        getenv("FORMATO_DATI"));
                sprintf(task_envp[6],"DEBUG=%s\00",
                        getenv("DEBUG"));
                sprintf(task_envp[7],"HOME=%s\00",
                        getenv("HOME"));
/**** 18/12/95 ****/
                sprintf(task_envp[8],  "N000=%s\00", getenv("N000"));
                sprintf(task_envp[9],  "N001=%s\00", getenv("N001"));
                sprintf(task_envp[10], "N002=%s\00", getenv("N002"));
                sprintf(task_envp[11], "N003=%s\00", getenv("N003"));
                sprintf(task_envp[12], "N004=%s\00", getenv("N004"));
                sprintf(task_envp[13], "N005=%s\00", getenv("N005"));
                sprintf(task_envp[14], "N007=%s\00", getenv("N007"));
                sprintf(task_envp[15], "M001=%s\00", getenv("M001"));
                sprintf(task_envp[16], "M002=%s\00", getenv("M002"));
                sprintf(task_envp[17], "M003=%s\00", getenv("M003"));
                sprintf(task_envp[18], "M004=%s\00", getenv("M004"));
                sprintf(task_envp[19], "M005=%s\00", getenv("M005"));
                sprintf(task_envp[20], "LEGOMMI_BIN=%s\00",
                        getenv("LEGOMMI_BIN"));
/**** 18/12/95 ****/
                task_envp[21] = NULL;
#endif
#if defined VMS
                task_envp[0] = NULL;
#endif
	        pid=vfork();
		if(pid==0)
		  {
		   /*chdir(messaggio.comando_1);*/
#if defined SCO_UNIX
                   sigrelse(0);                        
#else
		    sigsetmask(0);  /* sblocca tutti i segnali  */
#endif
#if defined UNIX
		   setpgrp();
#endif
	       	   execve(task_name,task_argv,task_envp);
                         exit(0);
		  }
		genera_demone();
		break;
		}
           case (DEMONE_AGG_LEGOGRAF):
                {
                printf("lancio agg_perturba\n");
                path = getenv("LEGORT_BIN");
#if defined UNIX
                sprintf(task_name,"%s/agg_perturba\00",path);
#endif
#if defined VMS
                sprintf(task_name,"%sagg_perturba\00",path);
#endif
                sprintf(task_argv[0],"agg_perturba\00");
                sprintf(task_argv[1],"%s\00",messaggio.host);
                task_argv[2] = NULL;

                sprintf(task_envp[0],"LEGO=%s\00",getenv("LEGO"));
                sprintf(task_envp[1],"SHR_USR_KEY=%s\00",
                        getenv("SHR_USR_KEY"));
                sprintf(task_envp[2],"SHR_TAV_KEY=%s\00",
                        getenv("SHR_TAV_KEY"));
                sprintf(task_envp[3],"LEGORT_BIN=%s\00",
                        getenv("LEGORT_BIN"));
                sprintf(task_envp[4],"OS=%s\00",
                        getenv("OS"));
                sprintf(task_envp[5],"FORMATO_DATI=%s\00",
                        getenv("FORMATO_DATI"));
                sprintf(task_envp[6],"DEBUG=%s\00",
                        getenv("DEBUG"));
                task_envp[7] = NULL;

                pid_agg_pert=vfork();
                if(pid_agg_pert==0)
                   {
#if defined UNIX
                   setpgrp();
#endif
#if defined SCO_UNIX
                   sigrelse(0);
#else
                   sigsetmask(0);  /* sblocca tutti i segnali  */
#endif
                   execve(task_name,task_argv,task_envp);
                   exit(0);
                   }
                printf("lancio agg_legograf\n");
                path = getenv("LEGORT_BIN");
#if defined UNIX
                sprintf(task_name,"%s/agg_legograf\00",path);
#endif
#if defined VMS
                sprintf(task_name,"%sagg_legograf\00",path);
#endif
                sprintf(task_argv[0],"agg_legograf\00");
                sprintf(task_argv[1],"%s\00",messaggio.host);
                task_argv[2] = NULL;
/*              sprintf(task_argv[2],"%d\00",pid_agg_pert);
                        task_argv[3] = NULL;*/
                sprintf(task_envp[0],"LEGO=%s\00",getenv("LEGO"));
                sprintf(task_envp[1],"SHR_USR_KEY=%s\00",
                        getenv("SHR_USR_KEY"));
                sprintf(task_envp[2],"SHR_TAV_KEY=%s\00",
                        getenv("SHR_TAV_KEY"));
                sprintf(task_envp[3],"LEGORT_BIN=%s\00",
                        getenv("LEGORT_BIN"));
                sprintf(task_envp[4],"OS=%s\00",
                        getenv("OS"));
                sprintf(task_envp[5],"FORMATO_DATI=%s\00",
                        getenv("FORMATO_DATI"));
                sprintf(task_envp[6],"DEBUG=%s\00",
                        getenv("DEBUG"));
                task_envp[7] = NULL;

                pid=vfork();
                if(pid==0)
                   {
#if defined UNIX
                   setpgrp();
#endif
#if defined SCO_UNIX
                   sigrelse(0);
#else
                   sigsetmask(0);  /* sblocca tutti i segnali  */
#endif
                   execve(task_name,task_argv,task_envp);
                   exit(0);
                   }
                genera_demone();
                break;
                }
           case (DEMONE_FINESTRA):
                {
                sprintf(app,"dxterm -ls -display %s:0.0 &",
                messaggio.comando_1);
                system(app);
                genera_demone();
                break;
                }
	   case (DEMONE_FINE):
                {
                exit(0);
                break;
                }
           default:
                {
                printf("Comando inesistente\n");
                break;
                }
           }
}

int  genera_demone()
{
int pid;


path = getenv("LEGORT_BIN");
#if defined UNIX
sprintf(task_name,"%s/demone\00",path);
#endif
#if defined VMS
sprintf(task_name,"%sdemone\00",path);
#endif
sprintf(task_argv[0],"demone\00");
if(tipo_demone==MASTER)
	sprintf(task_argv[1],"MASTER\00");
  else
	sprintf(task_argv[1],"SLAVE\00");
task_argv[2] = NULL;

#if defined UNIX
sprintf(task_envp[0],"LEGO=%s\00",getenv("LEGO"));
sprintf(task_envp[1],"SHR_USR_KEY=%s\00",
                 getenv("SHR_USR_KEY"));
sprintf(task_envp[2],"SHR_TAV_KEY=%s\00",
                 getenv("SHR_TAV_KEY"));
sprintf(task_envp[3],"LEGORT_BIN=%s\00",
                 getenv("LEGORT_BIN"));
sprintf(task_envp[4],"OS=%s\00",
                 getenv("OS"));
sprintf(task_envp[5],"FORMATO_DATI=%s\00",
                 getenv("FORMATO_DATI"));
sprintf(task_envp[6],"DEBUG=%s\00",
                 getenv("DEBUG"));
sprintf(task_envp[7],"HOME=%s\00",
                 getenv("HOME"));
/**** 18/12/95 ****/
   sprintf(task_envp[8],  "N000=%s\00", getenv("N000"));
   sprintf(task_envp[9],  "N001=%s\00", getenv("N001"));
   sprintf(task_envp[10], "N002=%s\00", getenv("N002"));
   sprintf(task_envp[11], "N003=%s\00", getenv("N003"));
   sprintf(task_envp[12], "N004=%s\00", getenv("N004"));
   sprintf(task_envp[13], "N005=%s\00", getenv("N005"));
   sprintf(task_envp[14], "N007=%s\00", getenv("N007"));
   sprintf(task_envp[15], "M001=%s\00", getenv("M001"));
   sprintf(task_envp[16], "M002=%s\00", getenv("M002"));
   sprintf(task_envp[17], "M003=%s\00", getenv("M003"));
   sprintf(task_envp[18], "M004=%s\00", getenv("M004"));
   sprintf(task_envp[19], "M005=%s\00", getenv("M005"));
   sprintf(task_envp[20], "LEGOMMI_BIN=%s\00", getenv("LEGOMMI_BIN"));
/**** 18/12/95 ****/
task_envp[21] = NULL;
#endif
#if defined VMS
task_envp[0] = NULL;
#endif


pid=vfork();
if(pid==(-1)) 
      perror("vfork demone"); 
   if(pid==0)
         {
#if defined UNIX
                           setpgrp();
#endif
#if defined SCO_UNIX
         sigrelse(0);
#else
         sigsetmask(0);  /* sblocca tutti i segnali  */
#endif
         execve(task_name,task_argv,task_envp);
         exit(0);
  	}
#if defined VMS
printf("Prima di Wait\n");		
wait(&pid);
printf("Dopo Wait\n");
#endif
exit(0);
}
