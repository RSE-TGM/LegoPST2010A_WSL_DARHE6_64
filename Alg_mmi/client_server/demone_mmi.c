/**********************************************************************
*
*       C Source:               demone_mmi.c
*       Subsystem:              2
*       Description:
*       %created_by:    lopez %
*       %date_created:  Thu Oct 24 16:48:48 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: demone_mmi.c-5.2.7 %  (%full_filespec: demone_mmi.c-5.2.7:csrc:2 %)";
#endif

/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)demone_mmi.c	1.10\t4/12/96";
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#if defined UNIX || SCO_UNIX
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#else
#include <iodef.h>
#include <types.h>
#include <socket.h>
#include <in.h>
#include <netdb.h>
#include <inet.h>
#include <ucx$inetdef.h>
#include "vmsipc.h"
#endif



#include <Cs/Cs.h>
#include "sim_param.h"
#include "sim_types.h"
#include "sim_ipc.h"
#include "libnet.h"
#include "demone_mmi.h"


#if defined VMS
#define pid_t int
#endif

#define errore(stringa)         exit(fprintf(stderr,"Attention !!!\n      Error in process demone_mmi[%d]: %s\n",getpid(),stringa))

static int scoda_comandi(int);
static int connessione_porta(int);
static int genera_server(char *, int);/* creazione processo server stream e 
				ricezione del numero porta di quest'ultimo */

void fineFIGLIO();                  /* gestione dello stop di un processo server
					 figlio */

int offset_daemon=0 ;    /* offset per porta e msg con server */

int main(argc,argv)
int argc;
char **argv;
{
int fp;
FILE *fp_port;
/* 
Setto all' inizio, la porta al valore di DEMONE_PORT 
*/
int demone_port=DEMONE_PORT;  


#if defined UNIX || SCO_UNIX
/*
	cambio gruppo di appartenza
*/
#if defined SCO_UNIX || LINUX
if(setpgrp() == -1)
	errore("change group");

#else
if(setpgrp(0, getpid()) == -1)
	errore("change group");
#endif
/*
	ignora lo stato dei figli
*/
if(signal(SIGCHLD,fineFIGLIO)==SIG_ERR)
    {
        errore("Fallita cattura di SIGCHLD");
        exit(1);
    }
#endif

/*
Provo fino a NUMDAEMONCONN connessioni
*/
if((fp=connessione_porta(demone_port)) == -1)
        {
        printf("demone_mmi: 1st connection ko !!!\n");

        while( ( fp <0 )  &&  ( offset_daemon < NUMDAEMONCONN)  ) 
           {
           offset_daemon++;
           printf("WARNING: trying with offset_daemon=%d\n",offset_daemon);
           demone_port=DEMONE_PORT + offset_daemon;
           fp=connessione_porta(demone_port);
           }

        }

if( offset_daemon == NUMDAEMONCONN )
	errore("error during connection");


printf("Process demone_mmi pid = %d is waiting on port = %d\n",
		getpid(),demone_port);

/*
Scrive file con numero porta demone per demone_mmi
*/
if(!(fp_port=fopen("demone_mmi_port","w")))
   errore("Impossible to create file demone_mmi_port");
fprintf(fp_port,"%d",demone_port);
fclose(fp_port);


while(1)
	{
	if(scoda_comandi(fp)<0)
		exit(1);
	}
}
/*
    fineFIGLIO(
        routine per la  gestione dello stop dei processi server figli
        attivata dalla cattura di SIGCHLD
*/

void fineFIGLIO(dummy)
int dummy;
{
 pid_t pid_def=0;   /* id del processo defunct */
 int coderr;        /* codice d'uscita */

    while((pid_def=waitpid(-1,&coderr,WNOHANG))>0);
    printf("\tServer_mmi (pid:%d) terminato, codice d'uscita:%d\n",pid_def,coderr);

}

/*
    scoda_comandi()
         ricezione messaggio DATAGRAM da socket

    Parametri:
        int fp: descrittore del socket

    Ritorno:
        -1 se KO
        0 se OK
*/

static int scoda_comandi(fp)
int fp;
{
char nomeHost[MAXHOSTNAMELUN];
int newsd; /* nuovo canale dalla accept */
struct sockaddr_in client;
int size_info_client=sizeof(client);
int ret;
MSG_DEMONE_MMI messaggio;
int port;
int abilitazione=0;
int randomNumberReceived;
char randomNumberSent[FILENAME_MAX];
char *path_pwd;
char buffer_pwd[FILENAME_MAX];

/*
 stabilisce un connessione per comunicare ad un client richiedente
 su quale canale deve creare la connessione definitiva per
 la coppia client-server
*/
memset((char*)&client,0,sizeof(client));
if((newsd=accept(fp,(struct sockaddr * restrict)&client,&size_info_client)) == -1)
	{
	perror("demone_mmi: scoda_comendi ");
	errore("accept in scoda_comandi"); 
	return(-1);
	}
/*
 legge il messaggio di richiesta connessione
*/
read(newsd,&messaggio,sizeof(MSG_DEMONE_MMI));
printf("ricevuto messaggio da %s\n",messaggio.host);

/* conversione campo richiesta */
CONVERTI_INT_R(messaggio.richiesta);

printf("demone_mmi:messaggio.richiesta=%d\n",messaggio.richiesta);

abilitazione = 0; /* per default il funzionamento è senza controlli */
if(messaggio.richiesta==REQ_ABILITAZIONE) /* verifico se req abilitazione */
  {
  if(strcmp(messaggio.path_sim,ABILITAZIONE))
     {
     printf("\nWARNING: Connection impossible Version demone_mmi=%s \
            Version client_mmi =%s \n",ABILITAZIONE,messaggio.path_sim);
     }
  abilitazione= 1;            /* spediro' dir simulatore corrente X verifica */
  }
if(messaggio.richiesta==REQ_ABILITAZIONE_OPC) /* verifico se req abilitazione */
  {
  randomNumberReceived = atoi(messaggio.path_sim);
  abilitazione = 2; /* spediro' al simulatore elaborazione del numero ricevuto */
  }

/*
Caso in  cui non verifico nome del simulatore 
ma genero i server
*/
if(abilitazione == 0)
   {
   /* 
   creazione del processo server stream (di tipo congruente alla richiesta del     client) e ricezione del numero porta del processo server stream 
   */
   if((port=genera_server(messaggio.host,messaggio.richiesta))<0)
	{
	errore("creating server");
	return(-1);
	}
/*
        preparazione messaggio del messaggio verso il client che contiene
        il numero della porta su cui effettuare la connessione definitiva
*/
   messaggio.port=port;
   }
else
   {
   messaggio.port=66;   /* nome dummy */
#if defined LINUX
   if(path_pwd=getcwd(buffer_pwd, FILENAME_MAX))
#else
   if(path_pwd=getenv("PWD"))
#endif
      if ( abilitazione == 1)
      {
         strcpy(messaggio.path_sim,path_pwd);
      }
      else
      {
         sprintf(randomNumberSent,"%d",randomNumberReceived*3 +77);
         strcpy(messaggio.path_sim, randomNumberSent);
      }
   else 
      errore(" Impossible to retrieve pwd_pathname");
   }
gethostname(nomeHost,MAXHOSTNAMELUN);
strcpy(messaggio.host,nomeHost);


/*
        trasmissione messaggio con numero porta verso il client
*/

/*
printf("DEBUG: messaggio.port=%d\n",messaggio.port);
*/

CONVERTI_INT_T(messaggio.port);

write(newsd,&messaggio,sizeof(MSG_DEMONE_MMI));
close(newsd);
}

/*
    connessione_porta()
        crea la connessione STREAM come server

    Parametri:
        int port:  porta del server per STREAM

    Ritorno:
        -1 se KO
        il descrittore del socket se OK
*/

static int connessione_porta(int p)
{
int socd;
struct sockaddr_in server;

/* 
 Apre un socket di tipo stream per comunicare ai client che lo richiedono
 un numero di porta per la connessione definitiva tra coppie client-server
*/
if((socd = socket( AF_INET, SOCK_STREAM, 0))<0)
	{
	printf("demone_mmi: Impossible opening datagram socket\n");
	return(-1);
	}

memset(&server,0,sizeof(server));
server.sin_family = AF_INET;
server.sin_addr.s_addr = htonl(INADDR_ANY);

/*
printf("\nDEBUG:Connessione port=%d\n \n",p);
*/

server.sin_port = htons(p);
/* server.sin_len = sizeof(server);  */
if (bind(socd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
	printf(" Impossible  bind  socket\n");
	return(-1);
	}

if(listen(socd,5) == -1)
	{
	printf("Impossible to listen \n");
	return(-1);
	}

return(socd);
}


/*
    genera_server()
        crea (con "vfork" e "execve") il processo server (stream) figlio
        e attende che quest'ultimo invii un messaggio contenente il numero di po
rta
        su cui si impostera' la connessione con il client

    Parametri:
        char *host:      nome dell'host;
        int tipo_server: tipo del server.

    Ritorno:
        -1 se KO
        0 se OK
*/

static int genera_server(char *host, int tipo_server)
{
char *path_bin;
char task_name[256];
char *task_argv[6];
char *task_envp[4];
pid_t pid_server;
int id_msg;
MSG_DEMONE_PORT messaggio_porta;
static int prog_server = 0;
int kk;


/*
	incrementa eventualmente il progressivo dei server,
	il promo server generato deve essere il SERVER_MMI_COMMAND
Alla richiesta del client di creazione del server per i comandi,
       viene incrementato il progressivo dei server;
       ==> la prima connessione richiesta dal client deve essere quella per i co
mandi;
       ==> la triade dei server ha lo stesso progressivo
*/

if(tipo_server == SERVER_MMI_COMMAND)
	++ prog_server;


/*
	creo la coda per il ricevimento
	dell'indice di porta
*/
id_msg=msg_create(DEMONE_MSG+offset_daemon,1);

task_argv[0]=(char*)malloc(FILENAME_MAX);
task_argv[1]=(char*)malloc(FILENAME_MAX);
task_argv[2]=(char*)malloc(FILENAME_MAX);
task_argv[3]=(char*)malloc(FILENAME_MAX);
task_argv[4]=(char*)malloc(FILENAME_MAX);
task_argv[5]=(char*)malloc(FILENAME_MAX);
task_envp[0]=(char*)malloc(FILENAME_MAX);
task_envp[1]=(char*)malloc(FILENAME_MAX);
task_envp[2]=(char*)malloc(FILENAME_MAX);
task_envp[3]=(char*)malloc(FILENAME_MAX);


printf("genera server host=%s tipo_server=%d prog_server=%d\n",host,tipo_server,prog_server);

path_bin = getenv("LEGOMMI_BIN");
#if defined UNIX || SCO_UNIX
sprintf(task_name,"%s/server_mmi\00",path_bin);
#else
sprintf(task_name,"%sserver_mmi\00",path_bin);
#endif
sprintf(task_argv[0],"server_mmi\00");
sprintf(task_argv[1],"%s\00",host);
sprintf(task_argv[2],"%d\00",tipo_server);
sprintf(task_argv[3],"%d\00",prog_server);
sprintf(task_argv[4],"%d\00",DEMONE_MSG + offset_daemon);
task_argv[5]=NULL;

sprintf(task_envp[0],"LEGOMMI_BIN=%s\n",path_bin);
sprintf(task_envp[1],"SHR_USR_KEY=%s\n",getenv("SHR_USR_KEY"));
sprintf(task_envp[2],"FORMATO_DATI=%s\n",getenv("FORMATO_DATI"));
task_envp[3]=NULL;

pid_server=vfork();
if(pid_server==0)
       {
#if defined SCO_UNIX
       setpgrp();
       sigrelse(0);
#else
       setpgrp();
       sigsetmask(0);  /* sblocca tutti i segnali  */
#endif
       execve(task_name,task_argv,task_envp);
       exit(0);
       }

/*
	attendo il messaggio contenete il numero di
	porta del server
*/
if((msg_rcv(id_msg,&messaggio_porta,sizeof(MSG_DEMONE_PORT)-sizeof(long),
	(long)MSG_PORT_SERVER, !IPC_NOWAIT,100)) == TIMEOUT_SCADUTO)
		{
		msg_close(id_msg);
		errore("receiving port number");
		}
printf("Ricevuto numero di porta = %d\n",messaggio_porta.port);

/*
	chiusura coda
*/
msg_close(id_msg);
return(messaggio_porta.port);
}

