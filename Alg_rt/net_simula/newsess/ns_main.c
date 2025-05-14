/**********************************************************************
*
*       C Source:               ns_main.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Tue Oct 22 13:58:43 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ns_main.c-6 %  (%full_filespec: ns_main.c-6:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)ns_main.c	1.13\t2/5/96";
/*
   modulo ns_main.c
   tipo 
   release 1.13
   data 2/5/96
   reserved @(#)ns_main.c	1.13
*/
/*  Copiato da sked_pf22.c */
# include <stdio.h>
# include <string.h>
# include <errno.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/shm.h>
#endif
#if defined VMS
# include"vmsipc.h"
#endif
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
# include "sked.h"
# include <Rt/RtDbPunti.h>
# include <Rt/Rt.h>
# include <Rt/RtMemory.h>

#define separatore printf("********************************************************\n");


/* Variabili globali */
   RtDbPuntiOggetto fsdbpunti;
   RtDbPuntiOggetto fsdbpunti_ext;
   RtErroreOggetto  fserrore;
   float tem_i;
   float tem_f;
   char  *dir_archive;
   char  *f22_ascii="f22circ.asc";
   FILE *f22_ascii_id;

/* Variabili per la lettura della SHM */
#if defined BACKTRACK
   BKTAB *backtrack_hea;
#endif
   SNTAB *snapshot_hea;            /* area shm tabella snapshot (non serve) */
   int   shr_usr_key;              /* chiave utente per shared  */
   int   size_area_dati;           /* size (byte) area dati tutte le task */
   float *area_dati;               /* puntatore inizio area dati delle task */
   float *area_dati_ext;           /* puntatore inizio area dati delle task */


/* Prototyping funzioni */
   int ns_prolog();
   extern int ns_backtrack(float, float);
   extern int ns_f22(float, float);
   extern int ns_pert(float, float);
   extern int bktk_tab_read_piac();




int main(argc, argv)
int argc;
char *argv[];
{
int caso=-1;
int fine=0;
int ret;
int no_backtrack=0;
int no_f22circ=0;
int no_perturbazioni=0;


    if(argc != 5)
      {
      fprintf(stderr,
         "<nsession> <tempo_iniziale> <tempo_finale> <0 backtrack 1 f22>\n");
      fprintf(stderr,
         "<  0) all\n  1) f22\n  2) backtrack\n  3) perturbazioni.dat\n");
      fprintf(stderr,
         "<  4) scrive f22 ascii 9) bktk_tab_read>\n");
      tem_i=80600.0; 
      tem_f=84000.0;
      fprintf(stderr,"  Sessione di prova fisso Ti=%f   Tf=%f\n",tem_i,tem_f);
      caso=1;
      }
    else
      {
      tem_i=(double)atof(argv[1]);
      tem_f=(double)atof(argv[2]);
      caso = (int)atoi(argv[3]);
      if((dir_archive=(char *)XtCalloc(strlen(argv[4]),sizeof(char)))==NULL)
         exit(fprintf(stderr,"XtCalloc error: dir_archive"));
      strcpy(dir_archive,argv[4]);

printf("\n\n********************************************************\n\n");
printf("Process:	nsession\n\n");       
printf("********************************************************\n\n");
printf("Time range          ---> Tf=%f   Ti=%f\n",tem_f,tem_i);
printf("Archiving directory ---> %s\n",dir_archive);
      }
   if (tem_f<=tem_i)
      {
      exit(fprintf(stderr,"Finestra temporale scorretta ---> Tf=%f   Ti=%f\n",
           tem_f,tem_i));
      }

/*
   Gestione operazioni
*/
   if (caso==9)
      {
      }


   switch (caso)
      {
      case 1:
         {
         ret = ns_f22(tem_i,tem_f);
         if( ret<0 )
            no_f22circ = 1;
         fine = 1;
         break;
         }
      case 2:
         {
         fine=1;
/*       Crea nuovo file di backtrack */
         ret = ns_backtrack(tem_i,tem_f);
         if ( ret<0 )
            no_backtrack = 1;
         break;
         }
      case 3:
         {
         fine=1;
/*       Crea nuovo file delle perturbazioni */
         ret = ns_pert(tem_i,tem_f);
         if ( ret<0 )
            no_perturbazioni = 1;
         break;
         }
      case 4:
         {
         ret = ns_f22(tem_i,tem_f);
         if( ret<0 )
            no_f22circ = 1;
         fine = 1;
         break;
         }
      case 9:
         {
         fine=1;
         printf("Esegue la lettura della tabella dei backtrack\n");
/*       Esegue la lettura della tabella dei backtrack */
         ret = bktk_tab_read_piac();
         break;
         }
      default :
         printf("		Caso esecuzioni in sequenza\n");
      }

      if ( fine==1 )
         exit(0);

      separatore;
/*
      NUOVI FILE backtrack.dat e stato_cr.rtf
*/
printf("\n********************************************************\n");
printf("Archiving:\n");       
printf("\tbacktrack.dat ---> backtrackn.dat\n");       
printf("\tstato_cr.rtf  ---> stato_crn.rtf\n");       
printf("********************************************************\n");
      ret = ns_backtrack(tem_i,tem_f);
      if( ret<0 )
          no_backtrack = 1;
printf("\nCOMPLETED\n\n");       

/*
      NUOVI FILE f22circ
*/
printf("********************************************************\n");
printf("Archiving:\n");       
printf("\tf22circ.dat   ---> f22circn.dat\n");       
printf("\trecorder.edf  ---> recordern.edf\n");       
printf("********************************************************\n");
      ret = ns_f22(tem_i,tem_f);
      if( ret<0 )
          no_f22circ = 1;
printf("\nCOMPLETED\n\n");       

/*
      NUOVO FILE perturbazioni.dat
*/
printf("********************************************************\n");
printf("Archiving:\n");       
printf("\tperturbazioni.dat   ---> perturbazionin.dat\n");       
printf("********************************************************\n");
      ret = ns_pert(tem_i,tem_f);
      if ( ret<0 )
           no_perturbazioni = 1;
printf("\nCOMPLETED\n\n");       
      separatore;

/*
      STATISTICHE FINALI 
*/
      if( (no_backtrack!=0) || (no_f22circ!=0) || (no_perturbazioni!=0) )
          fprintf(stderr,"    ATTENZIONE : \n");
      else {
          fprintf(stderr,"    Fine regolare\n");
          separatore;
      }

      if( no_backtrack!=0 )
          fprintf(stderr,"    NON PRODOTTI backtrackn.dat e stato_crn.dat\n");
      if( no_f22circ!=0 )
          fprintf(stderr,"    NON PRODOTTI f22circn.dat e f22circn.hd\n");
      if( no_perturbazioni!=0 )
          fprintf(stderr,"    NON PRODOTTI perturbazionin.dat\n");

      XtFree(dir_archive);
}




int ns_prolog()
{

SIMULATOR simulpar;
/* Decodifica SHR_USR_KEY */
   shr_usr_key = atoi((char *) getenv("SHR_USR_KEY"));

/* Aggancio al database dei punti */
   printf(" aggancio al database dei punti \n");
   fserrore = RtCreateErrore(RT_ERRORE_TERMINALE,"filesave");
#if defined SCO_UNIX
   fsdbpunti = RtCreateDbPunti(fserrore,"S02_SCO",DB_PUNTI_INT,&simulpar);
   fsdbpunti_ext = RtCreateDbPunti(fserrore,"S02_SCO",DB_PUNTI_SHARED,&simulpar);
#endif
#if defined OSF1
   fsdbpunti = RtCreateDbPunti(fserrore,"S02_OSF1",DB_PUNTI_INT,&simulpar);
   fsdbpunti_ext = RtCreateDbPunti(fserrore,"S02_OSF1",DB_PUNTI_SHARED,&simulpar);
/*
   fsdbpunti = RtCreateDbPunti(fserrore,NULL,DB_PUNTI_INT,&simulpar);
   fsdbpunti_ext = RtCreateDbPunti(fserrore,NULL,DB_PUNTI_SHARED,&simulpar);
*/
#endif
#if defined LINUX
   fsdbpunti = RtCreateDbPunti(fserrore,"S02_LINUX",DB_PUNTI_INT,&simulpar);
   fsdbpunti_ext = RtCreateDbPunti(fserrore,"S02_LINUX",DB_PUNTI_SHARED,&simulpar);
#endif
#if defined AIX
   fsdbpunti = RtCreateDbPunti(fserrore,"S02_AIX",DB_PUNTI_INT,&simulpar);
   fsdbpunti_ext = RtCreateDbPunti(fserrore,"S02_AIX",DB_PUNTI_SHARED,&simulpar);
#endif
#if defined VMS
   fsdbpunti = RtCreateDbPunti(fserrore,"S02_VMS",DB_PUNTI_INT,&simulpar);
   fsdbpunti_ext = RtCreateDbPunti(fserrore,"S02_VMS",DB_PUNTI_SHARED,&simulpar);
#endif


/* Recupero il puntatore all'area degli header degli snapshot e backtrack*/
   snapshot_hea = RtDbPGetPuntSnapshot(fsdbpunti);
   size_area_dati = RtDbPSizeData(fsdbpunti);
   area_dati = RtDbPPuntData(fsdbpunti);
   area_dati_ext = RtDbPPuntData(fsdbpunti_ext);
#if defined BACKTRACK
   backtrack_hea = RtDbPGetPuntBacktrack(fsdbpunti);
#endif

   printf("size_area_dati=%d\n",size_area_dati);

   bktk_tab_read_piac();

   printf("Fine\n");
}
/* Fine File */
