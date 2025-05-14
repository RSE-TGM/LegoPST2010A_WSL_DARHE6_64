/**********************************************************************
*
*       C Source:               ns_pert.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Tue Oct 22 13:58:53 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ns_pert.c-5 %  (%full_filespec: ns_pert.c-5:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)ns_pert.c	1.3\t9/12/96";
/*
   modulo ns_pert.c
   tipo 
   release 1.3
   data 9/12/96
   reserved @(#)ns_pert.c	1.3
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#if defined UNIX
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#endif
#if defined VMS
#include"vmsipc.h"
#include <unixio.h>
#include <file.h>
#endif
#include "sim_param.h"
#include "sim_types.h"
#include "sim_ipc.h"
#include "comandi.h"
#include "sked.h"
#include "f22_circ.h"
#include "grsf22.h"
#include <Rt/RtDbPunti.h>
#include <Rt/RtMemory.h>
#include "ns_macro.h"




/* 
   Prototyping funzioni contenute nel file
*/
   int ns_pert(float, float);
   int nomipert();

/*
   Variabili esterne.
*/
   extern char *dir_archive;

/*
   Nomi dei file in gioco
*/
   char *nome_file_pert;
   char *nome_file_pertn;





/*
    Genera la nuova sessione di file di tipo perturbazioni.
    Input	perturbazioni.dat
    Output	perturbazionin.dat
*/
int ns_pert(float tem_i, float tem_f)
{
FILE *fp_pert;
FILE *fp_pertn;
TIPO_PERT pert;
int pert_scritte;
int pert_originali;


#if defined  UNIX
    printf(" DEfinito UNIX\n");
#endif
#if defined  AIX
    printf(" DEfinito AIX\n");
#endif
#if defined  OSF1
    printf(" DEfinito OSF1\n");
#endif
#if defined  LINUX
    printf(" DEfinito LINUX\n");
#endif
#if defined  OS
    printf(" Definito OS\n");
#endif

    nomipert();

/*
    Apertura file delle perturbazioni
*/
    if ( !(fp_pert = fopen(nome_file_pert, "r")) )
       {
       fprintf(stderr,"    Non esiste il file [%s]\n",nome_file_pert);
          return (-1);
       }
    if ( !(fp_pertn = fopen(nome_file_pertn, "w")) )
       {
       fprintf(stderr,"    Non esiste il file [%s]\n",nome_file_pertn);
          return (-1);
       }


/*
    Lettura del vecchio file e scrittura del nuovo.
*/
    pert_scritte=0;
    pert_originali=0;
    while( leggi(&pert, sizeof(TIPO_PERT), 1, fp_pert) )
       {
       pert_originali++;
       if ( (pert.t >= tem_i) && (pert.t <= tem_f) )
          {
          if (scrivi(&pert, sizeof(TIPO_PERT), 1, fp_pertn) == 0)
               fprintf(stderr,"    ns_pert errore scrittura perturbazioni\n");
          fprintf(stderr,"    %2.2d) tipo=%d ind=%2.2d  tempo=%f\n",
                  pert_scritte,pert.tipo,pert.indirizzo,pert.t);
          pert_scritte++;
          }
       else
          fprintf(stderr,"    Scarto %d) tipo=%d ind=%2.2d  tempo=%f\n",
                  pert_originali,pert.tipo,pert.indirizzo,pert.t);
       }
    fclose(fp_pert);
    fclose(fp_pertn);
    fprintf(stderr,"    Scritte %d perturbazioni su un totale di %d\n",
            pert_scritte,pert_originali);
    return(0);
}




/*
    Prepara i nomi dei file delle perturbazioni in particolare
    del pathname relativo al nome perturbazioni.
*/
int nomipert()
{
char *punt;
char path_22dat[FILENAME_MAX+1];

    getcwd(path_22dat,sizeof(path_22dat));
#if defined UNIX
    strcat(path_22dat,"/");
#endif
    nome_file_pert  = malloc(strlen(path_22dat)+20);
    nome_file_pertn = malloc(strlen(path_22dat)+60);
    strcpy(nome_file_pert ,path_22dat);
    strcpy(nome_file_pertn,path_22dat);
    strcat(nome_file_pertn,dir_archive);
    strcat(nome_file_pertn,"/");
    strcat(nome_file_pert, PERTURBAZIONI);
    strcat(nome_file_pertn,PERTURBAZIONIN);
/*
    printf(" [%s]\n [%s]\n",nome_file_pert,nome_file_pertn);
*/
    return(0);
}
/* Fine File */
