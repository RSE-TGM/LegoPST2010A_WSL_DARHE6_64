/**********************************************************************
*
*       C Source:               ns_backtrack.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Tue Apr  7 10:26:34 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ns_backtrack.c-4 %  (%full_filespec: ns_backtrack.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)ns_backtrack.c	1.8\t2/5/96";
/*
   modulo ns_backtrack.c
   tipo 
   release 1.8
   data 2/5/96
   reserved @(#)ns_backtrack.c	1.8
*/
/*  Copiato da sked_pf22.c */
# include <stdio.h>
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
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
# include "sked.h"
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

#include "ns_macro.h"


/* Variabili esterne */
   extern RtErroreOggetto  fserrore;
   extern char *dir_archive;

   int _MAX_BACK_TRACK;
   int _MAX_CAMPIONI;
   int _NUM_VAR;
   int _SPARE_SNAP;
   int _MAX_PERTUR;
   int SIZE_AREA_DATI;


/* Variabili globali */
   HEADER_REGISTRAZIONI hreg_bktk;
   BKTAB  	*bk_hea;
   STATO_CR	stato_cr;

   int 		*bk_trasfer;

   int		contatore_sessioni=0;
   int		contatore_back_n=0;

   int  	size_area_spare;
   int   	size_blocco_bktk;
   int   	size_parte1_bktk;

/* Prototyping funzioni */
   int ns_backtrack(float, float);
   int leggi_info_backtrack(int, float, float );
   int crea_new_backtrack();
   int bktk_tab_read_piac();

/* Funzioni esterne */
   extern Boolean nsRemove(char *);
   extern Boolean nsCopy(char *,char *);


/*
    Genera la nuova sessione di file di backtrack
    Input       backtrack.dat
                stato_cr.rtf
    Output      backtrackn.dat
                stato_crn.rtf
    Il file di backtrack che viene generato contiene solamente i
    backtrack che vengono trasferiti; la sua dimensione e' quindi
    normalmente inferiore a quella del file originale. Tale file deve 
    essere opportunamente ripristinato per essere utilizzato dal simulatore.
*/
int ns_backtrack(float ti, float tf)
{
int i,j;
int ret;

/*
   Lettura di alcune informazioni contenute nell'header del file
   backtrack.dat e lettura degli header di tutti i backtrack presenti.
*/
   ret = bktk_tab_read_piac();
   if ( ret<0 )
      return(-1);

/*
   Settaggio delle variabili per la lettura della parte 'dati' del file
   backtrack.dat.
*/
   size_area_spare  =  _SPARE_SNAP * AREA_SPARE;
   size_parte1_bktk =  _MAX_BACK_TRACK * sizeof(BKTAB) +
                       sizeof(HEADER_REGISTRAZIONI);
   size_blocco_bktk =  SIZE_AREA_DATI    +  sizeof(float)        +
                       sizeof(SNAP_SKED) +  DIM_SNAP_AUS         +
                       size_area_spare  * sizeof(char)           +
                       2*_MAX_PERTUR * sizeof(TIPO_PERT);
/*
   Lettura dal file stato_cr.rtf in particolare della posizione dello
   ultimo backtrack salvato nel file backtrack.dat corrispondente.
*/
   load_stato_cr(&stato_cr);
/*
   printf("Ssave=%d Sload=%d  Bsave=%d Bload=%d\n",
           stato_cr.last_snap_save,stato_cr.last_snap_load,
           stato_cr.last_bktk_save,stato_cr.last_bktk_load);
*/

/* Allocazione della struttura contenente le posizioni dei backtrack
   che devono essere trasferiti nel file backtrackn.dat.
*/
   if((bk_trasfer=(int*)XtCalloc(_MAX_BACK_TRACK,sizeof(int)))==NULL) {
      fprintf(stderr,
      "Errore nella XtCalloc di bk_trasfer\n");
      return(-1);
   }
/*
   In base alla finestra temporale specificata viene caricata la struttura
   bk_trasfer con le posizioni dei backtrack che devono essere trasferiti.
*/ 
   leggi_info_backtrack(stato_cr.last_bktk_save,ti,tf);

/* Creazione e caricamento del file backtrackn.dat */
   crea_new_backtrack();

   XtFree(bk_trasfer);

return(1);
}




/*
    In base alla finestra temporale richiesta produce un vettore
    bk_trasfer che vale 0 se il backtrack non deve essere trasferito 
    e 1 nel caso in cui sia da trasferire
*/
int leggi_info_backtrack(int last_backtrack, float tem_i, float tem_f)
{
int i,j,k;
int ksuc;
int posizione=0;
char appoggio[10];
char testo[500];
char path_rel[200];
char flag[2];
char *str;
int ultimo_save;


    i=0;
    ultimo_save = last_backtrack;
    strcpy(flag,"*");
/*
    printf("last_backtrack=%d  ti=%f  tf=%f last_save=%d  last_load=%d\n",
            last_backtrack,tem_i,tem_f,
            stato_cr.last_bktk_save,stato_cr.last_bktk_load);
*/

/*  
    Ciclo su tutti i backtrack a partire dall'ultimo salvato 
*/
    k=last_backtrack + 1;
    if (k > _MAX_BACK_TRACK)
       k = 1;
    ksuc=k + 1;
    if (k > _MAX_BACK_TRACK)
       ksuc = 1;
    for (j=0,k=last_backtrack+1;j<_MAX_BACK_TRACK ;k++,j++,ksuc++)
        {
/*      Controllo indici */
        if (ksuc > _MAX_BACK_TRACK)
          ksuc = 1;
        if (k > _MAX_BACK_TRACK)
            k = 1;
       
/*      Solo per i backtrack esistenti */
        if(bk_hea[k-1].stat==1)
           {
           /*
              Stampa debug
           printf("\n(%d) Analisi tempok[k=%d]=%f tempok1[ksuc=%d]=%f\n",
                  j,k,bk_hea[k-1].tempo/1000,ksuc,bk_hea[ksuc-1].tempo/1000);
              Stampa debug
           */
           if(((int)(bk_hea[k-1].tempo/1000)>=(int)tem_i)&&((int)(bk_hea[k-1].tempo/1000)<(int)tem_f)) {
               bk_trasfer[contatore_back_n]=k;
               contatore_back_n++;

               ++posizione;
               sprintf(appoggio,"%3d ",posizione);
               strcat (appoggio,flag);
               sprintf(testo,"%s - %s - %s - %8.1f",
                       appoggio,bk_hea[k-1].datasn,
                       bk_hea[k-1].temposn,bk_hea[k-1].tempo/1000);
/*             Se e' stato forzato */

               /*
                  Stampa debug
               printf("<%3d> ",bk_hea[k-1].prog);
                  Stampa debug
               */

                if (bk_hea[k-1].forzato != 0)
                   {
                   contatore_sessioni++;
                   if (!strcmp(flag," "))
                      strcpy(flag,"*");
                   else
                      strcpy(flag," ");
                   }

                str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
                strcpy(str,testo);
                /*
                   Stampa per debug
                printf("%s\n",str);
                   Stampa per debug
                */
                XtFree(str);
                ultimo_save = contatore_back_n;
             }
          else
             {
             /*
                Stampa per debug
             printf("Cond_i=%d  cond_f=%d k=%d  t=%f   bk_trasfer=%d\n",
                     condizione_tini,condizione_tfin,k,
                     bk_hea[k-1].tempo/1000,bk_trasfer[k-1]);
                Stampa per debug
             */
             }
          }
       }  /* Fine ciclo for */

/*     
       Aggiornamento del file stato_cr.rtf 
       Si crea una copia momentanea e poi si trasferiscono le modifiche sul
       nuovo file ripristinando infine quello originale.
*/
/*
printf("ultimo_save = %d\tcontatore_back_n = %d\n",ultimo_save,contatore_back_n); 
*/
       nsCopy(NAME_STATO,NAME_STATO_MOM);
       load_stato_cr(&stato_cr);
       stato_cr.last_bktk_save = ultimo_save;
       stato_cr.last_bktk_load = 0;
       save_stato_cr(&stato_cr);
       strcpy(path_rel, "./");
       strcat(path_rel, dir_archive);
       strcat(path_rel, "/");
       strcat(path_rel, NAME_STATON);
       nsCopy(NAME_STATO, path_rel);
       nsCopy(NAME_STATO_MOM,NAME_STATO);
       nsRemove(NAME_STATO_MOM);
       printf("Ssave=%d Sload=%d  Bsave=%d Bload=%d\n\n",
               stato_cr.last_snap_save,stato_cr.last_snap_load,
               stato_cr.last_bktk_save,stato_cr.last_bktk_load);
/*
       printf("\n___________\n");
       for( j=0;j<_MAX_BACK_TRACK;j++ )
         if( bk_trasfer[j]!=0 )
           printf("%d) bk_trasfer=%d  ",j,bk_trasfer[j]);
       printf("\n___________\n");
*/
       return(0);
}



int crea_new_backtrack()
{
FILE		*fp_bktk=NULL;
FILE		*fp_bktk_n=NULL;
float   	*area_dati;
float		tempo;
int		i,j;
int		pos_back_corr,offset;
char		path_rel[200];
char    	*app;
char		*area_spare;
TIPO_PERT	*pert_tmp,*pert_tmp_att; /* perturbazioni attive e in attesa */
SNAP_SKED	sommari_backtrack;


/* Nuovo file */
   strcpy(path_rel, "./");
   strcat(path_rel, dir_archive);
   strcat(path_rel, "/");
   strcat(path_rel, NAME_BACKN);
   if (!(fp_bktk_n = fopen(path_rel, "w")))
      {
      fprintf(" Non si puo' aprire il file:\n\t%s\n",path_rel);
      return(-1);
      }
   if (!(fp_bktk = fopen(NAME_BACK, "r")))
      {
      fprintf(" Non si puo' aprire il file:\n\t%s\n",NAME_BACK);
      return(-1);
      }
   /* Caricamento in backtrackn.dat della parte di header:         */
   /* HEADER_REGISTRAZIONI.                                        */ 
   fwrite(&hreg_bktk,sizeof(HEADER_REGISTRAZIONI),1,fp_bktk_n);
/*
   Caricamento in backtrackn.dat degli header dei backtrack
   selezionati: BKTAB. 
*/

printf("Backtrack archived:\n");
printf("POS\tTIME\t\tDESCRIPTION\n");

   for(i=0;i<contatore_back_n;i++) {
      pos_back_corr=bk_trasfer[i];

printf("%d\t%f\t%s\n",pos_back_corr,((bk_hea[pos_back_corr-1].tempo)/1000.0),
       bk_hea[pos_back_corr-1].descr);

      bk_hea[pos_back_corr-1].pos=i+1;
      bk_hea[pos_back_corr-1].prog=i+1;
      fwrite(&bk_hea[pos_back_corr-1],sizeof(BKTAB),1,fp_bktk_n);
   } 
/*
   Lettura dei dati relativi ai backtrack selezionati dal file
   backtrack.dat e caricamento di questi in backtrackn.dat. 
*/
   pert_tmp     = (TIPO_PERT *)calloc(_MAX_PERTUR,sizeof(TIPO_PERT));
   pert_tmp_att = (TIPO_PERT *)calloc(_MAX_PERTUR,sizeof(TIPO_PERT));
   app = (char *)malloc(DIM_SNAP_AUS);
   area_dati=(float *)XtCalloc(SIZE_AREA_DATI,sizeof(float));

   for(i=0;i<contatore_back_n;i++) {
      pos_back_corr=bk_trasfer[i];
/* 1) Area dati */
      offset=size_parte1_bktk + (pos_back_corr-1)*size_blocco_bktk;
      fseek(fp_bktk, offset, SEEK_SET);
      fread(area_dati, SIZE_AREA_DATI,1, fp_bktk);
      fwrite(area_dati, SIZE_AREA_DATI,1, fp_bktk_n);

/* 2) Lettura del tempo */
      fread(&tempo,1,sizeof(float), fp_bktk);
      fwrite(&tempo,1,sizeof(float),fp_bktk_n); 

/* 3) DIM_SNAP_AUS */
      fread(app, DIM_SNAP_AUS, 1, fp_bktk);
      fwrite(app,DIM_SNAP_AUS, 1, fp_bktk_n);

/* 4) Sommari */
      fread(&sommari_backtrack, sizeof(SNAP_SKED), 1, fp_bktk);
      fwrite(&sommari_backtrack, sizeof(SNAP_SKED), 1, fp_bktk_n);

/* 5) Area libera */
      area_spare = (char*)calloc(size_area_spare,sizeof(char));
      fread(area_spare, sizeof(char), size_area_spare, fp_bktk);
      if ( size_area_spare > 0 ) {
         fwrite(area_spare, sizeof(char), size_area_spare, fp_bktk_n);
         free(area_spare);
      }

/* 6) Area pert che comprende gli updown */
      fread(pert_tmp,     sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk);
      fread(pert_tmp_att, sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk);
      fwrite(pert_tmp,     sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk_n);
      fwrite(pert_tmp_att, sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk_n);
   }
 
   free(app);
   free(pert_tmp);
   free(pert_tmp_att);
   free(area_dati);

   fclose(fp_bktk);
   fclose(fp_bktk_n);

return(0);
}




/*
   Legge dal file backtrack.dat l'header (HEADER_REGISTRAZIONI) e la
   tabella (BKTAB) con le informazioni sui singoli backtrack.
*/
int bktk_tab_read_piac()
{
FILE *fp_bktk=NULL;
int  i,ret ;
int  size_bktk;
int  tot_bktk;


   if (!(fp_bktk = fopen("backtrack.dat", "r")))
      {
      fprintf(stderr,"    Il file di backtrack non esiste\n");
      return(-1);
      }
   else
      {
/* Il file esiste.
   Lettura header del file di backtrack corrente */
      fread(&hreg_bktk,sizeof(HEADER_REGISTRAZIONI),1,fp_bktk);

/* Recupero delle variabili di interesse da HEADER_REGISTRAZIONI */
      _MAX_BACK_TRACK = hreg_bktk.simulator.max_back_track;
      _MAX_CAMPIONI = hreg_bktk.simulator.max_campioni;
      _NUM_VAR = hreg_bktk.simulator.num_var;
      _SPARE_SNAP = hreg_bktk.simulator.spare_snap;
      _MAX_PERTUR = hreg_bktk.simulator.max_pertur;
      SIZE_AREA_DATI = hreg_bktk.size_area_dati;      

/* Allocazione tabella backtrack */
   bk_hea = (BKTAB*)XtCalloc(_MAX_BACK_TRACK,sizeof(BKTAB));

/* Caricamento nella struttura 'bk_hea' degli header dei backtrack */
   tot_bktk = 0;

printf("\nBacktrack in the original backtrack.dat:\n");

   for (i = 1; i <= _MAX_BACK_TRACK; i++) {
      fread(&bk_hea[i - 1], sizeof(BKTAB), 1, fp_bktk);
      if (bk_hea[i-1].stat == 1)
         ++tot_bktk;
      /* 
          Stampa di debug
      */
      if (bk_hea[i-1].stat != 0)
         printf("%d) tempo=%f (forzato=%d)\n",
                i,bk_hea[i-1].tempo/1000.0,bk_hea[i-1].forzato);
      /* 
          Stampa di debug 
      */
      }
   } 
   printf("\n");
   fclose(fp_bktk);
/*
   for (i=0; i<tot_bktk;i++)
      {
      printf("pos=%d \n",bk_hea[i].pos);
      printf("%3d)  prog=%d stat=%d pos=%d forz=%d mod=%d %s dat=%s t=%f\n",
              i,bk_hea[i].prog,bk_hea[i].stat,bk_hea[i].pos,bk_hea[i].forzato,
              bk_hea[i].mod,bk_hea[i].descr,bk_hea[i].datasn,bk_hea[i].tempo);
      }
*/
   return(0);
}
/* Fine File */

