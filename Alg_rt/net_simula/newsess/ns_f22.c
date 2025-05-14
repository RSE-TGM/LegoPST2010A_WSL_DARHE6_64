/**********************************************************************
*
*       C Source:               ns_f22.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Feb 15 14:57:35 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ns_f22.c-12 %  (%full_filespec: ns_f22.c-12:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)ns_f22.c	1.16\t2/5/96";
/*
   modulo ns_f22.c
   tipo 
   release 1.16
   data 2/5/96
   reserved @(#)ns_f22.c	1.16
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>
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
   int ns_f22(float, float);
   int nomif22();

/* 
   Prototyping funzioni esterne
*/
   extern int FinestreTemporali(PUNT_FILE_F22, F22CIRC_HD header,
                                float ti, float tf);
   extern int EstrazioneRecorder(PUNT_FILE_F22);
   extern int EstrazioneF22(PUNT_FILE_F22, PUNT_FILE_F22, F22CIRC_HD,
                             float , float , int );
   extern int f22_leggi_camp(PUNT_FILE_F22 ,F22CIRC_HD , float *, 
                             SCIRC_SEL_DATI **, int , int , int , int );
/*
   Variabili esterne.
*/
   extern char *dir_archive;
   extern char *f22_ascii;
   extern FILE *f22_ascii_id;
   int num_var_eff=0;
   F22CIRC_VAR *var_eff;

/*
   Variabili per la lettura dei file f22 
*/
   F22CIRC_T  istante;      /* Istante del campione salvato */
   F22CIRC_HD header;       /* Struttura degli header       */

/*
   Variabili relative ai file (puntatori)
*/
   PUNT_FILE_F22 file_f22;
   PUNT_FILE_F22 file_new_f22;

/*
   Nomi dei file in gioco
*/
   char *nome_file_f22;
   char *nome_file_f22n;


   int *selezione;

/*
    Genera la nuova sessione di file di tipo f22circ.
    Input	f22circ.dat
		S01 e f01.dat delle task del simulatore
    Output	f22circn.dat
		recordern.edf
*/
int ns_f22(float tem_i, float tem_f)
{
int tipo_operazione;
int offset;
int i, jjj, ret;
static float tempo=-1;
F22CIRC_HD head;
SCIRC_DATI *dati_f22 = NULL;
SCIRC_SEL_DATI *dati_sel_f22 = NULL;
SIMULATOR simpar;
int caso;
FILE *file_elenco_variabili;
char nome_variabile[10];

/*  
    Caricamento pathname dei file circolari  
*/
    if(nomif22() < 0)
       return(-1);
/*  
    Apertura file circolari, lettura header e creazione nuovi file 
*/
    if(f22_open_file(nome_file_f22, &file_f22)==0)
        {
        fprintf(stderr,"    Manca file f22 circolare\n");
        return(-1);
        }
    if(f22_leggo_header(&head,file_f22,1,&simpar)==0)
        return(-1);
    if(f22_create_file_dat(nome_file_f22n, &file_new_f22)==0)
        return(-1);
/*
    printf("header: p_iniz=%d - p_fine=%d - num_campioni=%d num_var_graf=%d\n",
           head.p_iniz,head.p_fine,head.num_campioni,
           head.num_var_graf);
*/

/*
    Leggo la finestra temporale inclusa nel file e la confronto
    con quella richiesta
*/
    caso = FinestreTemporali(file_f22,head,tem_i,tem_f);
    f22_close_file(file_f22);
    f22_close_file(file_new_f22);
    if (caso<0)
       {
       fprintf(stderr,"Non e' possibile estrarre il nuovo file\n");
       return(-1);
       }

/*
    Estrazione nuovi file f22circn
*/
    if(f22_open_plus_file(nome_file_f22n, &file_new_f22)==0)
        {
        printf("Fallisce f22_open_file con %s|\n",nome_file_f22n);
        return(-1);
        }
    if(f22_open_file(nome_file_f22, &file_f22)==0)
        return(-1);
    if(f22_leggo_header(&head,file_f22,0,&simpar)==0)
        return(-1);
/*
    Recupero del numero di variabili effettivamente presenti nel file
    f22circ.dat
*/
    var_eff=(F22CIRC_VAR *)malloc(head.num_var_graf *sizeof(F22CIRC_VAR));
    sposta(file_f22.fp,sizeof(HEADER_REGISTRAZIONI)+sizeof(F22CIRC_HD));
    if(leggi(var_eff,sizeof(F22CIRC_VAR),head.num_var_graf,file_f22.fp)<=0)
        return(-1);

    f22_ascii_id=fopen(f22_ascii,"w");
    fprintf(f22_ascii_id,"TEMPO");
    for(i=0;i<head.num_var_graf;i++) 
    {
       if( strstr(var_eff[i].nomevar,"libera") )
          break;
       else
	  {
          num_var_eff++;
	  }
    } 
/*
    Inserimento del filtro per la selezione di alcune variabili 
    invece di tutte quelle registrate
*/
    selezione=(int *)calloc(num_var_eff, sizeof(int));
    bzero((char *)selezione,num_var_eff*sizeof(int));
    if (file_elenco_variabili=fopen("selezione_variabili.dat","r"))
       {
       int jjj=0;
       while (fscanf(file_elenco_variabili,"%s\n" , nome_variabile) != EOF)
          {
          for(jjj=0;jjj<num_var_eff;jjj++) 
             {
             if (!strncmp(nome_variabile,var_eff[jjj].nomevar,strlen(nome_variabile)))
                 {
                 selezione[jjj]=1;
                 }
             }
          }
       }
    else
       {
       printf("selezione_variabili.dat not found\n");
       for(jjj=0;jjj<num_var_eff;jjj++)
          {
          selezione[jjj]=1;
          }
       }

    for(jjj=0;jjj<num_var_eff;jjj++)
       {
       if(selezione[jjj]==1)
         {
         fprintf(f22_ascii_id,";%s",var_eff[jjj].nomevar);
         }
       }

    fprintf(f22_ascii_id,"\n");
/*
    Creazione del file f22circn.dat.
*/ 
    EstrazioneF22(file_f22,file_new_f22,head,
                   tem_i,tem_f,caso);
    f22_close_file(file_f22);
    f22_close_file(file_new_f22);
    if(f22_open_file(nome_file_f22, &file_f22)==0)
        return(-1);
    if(f22_leggo_header(&head,file_f22,0,&simpar)==0)
        return(-1);

/*  
    Estrazione nuovo file recordern.edf 
*/
    EstrazioneRecorder(file_new_f22);
    f22_close_file(file_f22);
//    fflush(file_new_f22.fp);
//    f22_close_file(file_new_f22);

/*
    Prova di funzionamento al termine delle operazioni
*/
/*
    printf("________________________________________________________\n");

    tempo=-1;
    if(f22_open_file(nome_file_f22n, &file_new_f22)==0)
        return(-1);
    if(f22_leggo_header(&head,file_new_f22,0,&simpar)==0)
        return(-1);
    f22_leggi_campioni(file_new_f22,head,&tempo,&dati_sel_f22,0,-1,-1,-1);
    f22_close_file(file_new_f22);

    printf("________________________________________________________\n");
*/
}




/*
    Prepara i nomi dei file f22 coinvolti in particolare
    del pathname relativo al nome f22circ.
*/
int nomif22()
{
char *punt;
char path_22dat[FILENAME_MAX+1];


    if(getcwd(path_22dat,sizeof(path_22dat)) == NULL) {
       fprintf(stderr,"    Errore getcwd in nomif22()!!!\n");
        return(-1);
    }
#if defined UNIX
    strcat(path_22dat,"/");
#endif

    nome_file_f22  = (char *)malloc(strlen(path_22dat)+20);
    if(nome_file_f22==NULL) {
        fprintf(stderr,"    Errore malloc di nome_file_f22!!!\n");
        return(-1);
    }
    nome_file_f22n = (char *)malloc(strlen(path_22dat)+60);
    if(nome_file_f22n==NULL) {
       fprintf(stderr,"    Errore malloc di nome_file_f22n!!!\n");
        return(-1);
    }
    strcpy(nome_file_f22 ,path_22dat);
    strcpy(nome_file_f22n,path_22dat);
    strcat(nome_file_f22n,dir_archive);
    strcat(nome_file_f22n,"/");
    strcat(nome_file_f22, NAME_F22CIRC);
    strcat(nome_file_f22n,NAME_F22CIRCN);
/*
    punt = strstr(nome_file_f22,".");
    if(punt!=NULL)
        *punt = 0;
    punt = strstr(nome_file_f22n,".");
    if(punt!=NULL)
        *punt = 0;
*/
/*
    printf("nome_file_f22 =%s\n",nome_file_f22);
    printf("nome_file_f22n=%s\n",nome_file_f22n);
*/

    return(0);
}
/* Fine File */
