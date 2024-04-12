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

#include <stdio.h>
#include <string.h>
#include <errno.h>
#if defined AIX ||ULTRIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
#endif
# include <stdlib.h>
#if defined VMS
# include "vmsipc.h"
#endif
#include "sim_param.h"
#include "sim_types.h"
#include "libnet.h"
#include "mod_data.h"
#define NMAXDATI 500

/*
     parametri lego
*/
#if defined UNIX
   extern int _N000;
   extern int _N001;
   extern int _N002;
   extern int _N003;
   extern int _N004;
   extern int _N005;
   extern int _N007;
   extern int _M001;
   extern int _M002;
   extern int _M003;
   extern int _M004;
   extern int _M005;
#endif

main(argc,argv)
int argc;
char **argv;
{
VARIABILI *variabili;      /* database variabili di tutti i modelli  */
int shr_usr_key;           /* chiave utente per shared               */
char *ind_sh_top;          /* puntatore inizio shared memory sh_var  */
int id_sh;                 /* identificatore sh_var                  */
char pathf14[100];
int num_blo;
int num_mod;
int nmod;
int tot_variabili;
int ret;

     if(argc!=4)
	exit(printf("usa: refresh <numero modello> <numero blocco> <path f14.dat>\n"));

     num_mod=atoi(argv[1]);
     num_blo=atoi(argv[2]);
     strcpy(pathf14,argv[3]);

   /*
        prelega dall'environment i parametri caratteristici del lego
   */
#if defined UNIX
   if(!GetParLego())
        exit( fprintf(stderr,
                "ATTENZIONE: i parametri del LEGO non sono definiti"));
#endif

/*   Lettura numero modello, blocco, numero dati */
     shr_usr_key = atoi((char *)getenv("SHR_USR_KEY"));
     costruisci_var(&ind_sh_top,&variabili,&id_sh);
     nmod=numero_modelli(ind_sh_top);
     tot_variabili=numero_variabili(ind_sh_top);
     if ( num_mod <=0  )
        exit(printf("Attenzione refresh_dati, modello inesistente\n"));
     if ( num_blo<=0 )
        exit(printf("Attenzione refresh_dati, blocco inesistente\n"));
     ret  = refresh_dati_shm(ind_sh_top,variabili,num_mod,pathf14,num_blo);
/*   Caso di modulo di processo non trattato  */
     if ( ret == -2 )
        exit(4);
}
