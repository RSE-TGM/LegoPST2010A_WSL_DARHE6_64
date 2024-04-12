/**********************************************************************
*
*       C Source:               sked_backtrack_piac.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Apr  2 15:00:03 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_backtrack_piac.c-12 %  (%full_filespec: sked_backtrack_piac.c-12:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_backtrack_piac.c	5.1\t11/7/95";
/*
   modulo sked_backtrack_piac.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_backtrack_piac.c	5.1
*/
#if defined BACKTRACK
# include <stdio.h>
# include <errno.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/shm.h>
# include <stdlib.h>
#endif
#if defined VMS
# include"vmsipc.h"
#endif
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "sked.h"
# include "comandi.h"
# include "dispatcher.h"
# include "libnet.h"
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

#define TESTO_PROVA "Maurizio Zanetta prova dell'area spare in backtrack"
#define MAX_DATI_NET2 1

/*
   Variabili esterne
*/
extern HEADER_REGISTRAZIONI hreg_snap;
extern RtDbPuntiOggetto dbpunti;
extern RtDbPuntiOggetto dbpunti_ext;
extern int    id_msg_sked;	/* id coda messaggi  da processi read */
extern int    id_msg_snap;	/* id coda messaggi  da processi ausiliari */
extern int    id_msg_monit;	/* id coda messaggi  da monit */
extern int    id_msg_banco;	/* id coda messaggi  da banco */
extern int    _MAX_SNAP_SHOT;
extern int    _MAX_BACK_TRACK;
extern int    _MAX_CAMPIONI;
extern int    _NUM_VAR;
extern int    _MAX_PERTUR;
extern int    _SPARE_SNAP;
extern int    _PERT_CLEAR;

extern int    tipo_sked;
extern int    stato_sked;
extern int    nmod;           /* numero dei modelli */
extern int    numero_slave;   /* numero di nodi SLAVE, solo per MASTER  */
extern BKTAB *backtrack_hea;  /* area shm per tabella dei backtrack */
extern int    size_area_dati; /* size area dati di tutte le task */
extern float *area_dati;
extern double tempo_sim;      /* tempo della simulazione */
extern int    slot_bktk[MAX_VAL_SNAP];	/* indirizzi delle variabili
					 * caratteristiche dei
					 * backtrack */
/*
   Puntatori :
   fp_ordini : dei socket a cui spedire i comandi, solo per sked master.
   fp_com    : 0 -> task sulla stessa macchina 1 -> task
               su macchine diverse fp -> socket scrittura.
   fp_master : al socket del MAIN (solo per slave).
*/
extern int      fp_ordini[MAX_MODEL];
extern int      fp_com[MAX_MODEL];
int             fp_master;
/*
    Variabili globali
*/
HEADER_REGISTRAZIONI hreg_bktk;
int          tot_bktk;       /* numero dei backtrack registrati */
int          id_sh;		/* identificatore sh_var */
VARIABILI   *variabili;	/* database variabili di tutti i modelli */
char        *ind_sh_top;	/* puntatore inizio shared memory sh_var */
FILE        *fp_bktk, *fp_bktk2;	/* descrittore del file backtrack.dat */
STATO_CR     stato_cr;
SNAP_SKED    sommari_backtrack;
int   size_area_spare;
int   size_blocco_bktk;
int   size_parte1_bktk;
int   dati_scritti;

extern int modo_backtrack;
extern int attiva_listaci;
extern sked_raccogli_datisnap(int , int , PACCHETTO_NET *, int );

sked_backtrack_piac(azione, numero)
   int             azione;
   short           numero;
{
   int             i, ret;
   MSG_NET         messaggio_net;
   MSG_AUS         messaggio_aus;
   PACCHETTO_NET  *p_bktk;
   FILE           *fp;
   int size_task;
   int ini_task;
   int ii,jj;
   int nleft;
   int nwrite;
   int dati_complessivi;
   int numero_spedizioni;
   div_t  num_sped;
TIPO_PERT *pert_tmp;

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

/*
   Allocazione delle variabili per la trasmissione in rete:
   non viene piu' effettuata dinamicamente.
*/
   p_bktk = (PACCHETTO_NET *) malloc(sizeof(PACCHETTO_NET));

/* Manda il messaggio di BACKTRACK alle macchine SLAVE  */
   if (tipo_sked == MASTER)
   {
      messaggio_net.header_net.tipo = COMSIM;
      messaggio_net.header_net.codice = azione;
      messaggio_net.header_net.lun = 0;
      for (i = 0; i < nmod; i++)
	 if (fp_ordini[i] > 0)
	 {
	    if (writen(fp_ordini[i], &messaggio_net.header_net,
		       sizeof(HEADER_NET)) < 0)
	    {
	       sked_stato(STATO_ERRORE);
	       fprintf(stderr, "Impossibile com %d\n", i);
	       sked_errore();
	    }
	 }
   }


/* 
   Calcolo dimensioni di alcuni blocchi del file di backtrack 
   1) blocco iniziale  2) corpo del backtrack  3) area_spare
*/
   size_area_spare  =  _SPARE_SNAP * AREA_SPARE;
   size_parte1_bktk =  _MAX_BACK_TRACK * sizeof(BKTAB) +
                       sizeof(HEADER_REGISTRAZIONI);
   size_blocco_bktk =  size_area_dati    +  sizeof(float)        +
                       sizeof(SNAP_SKED) +  DIM_SNAP_AUS         +
                       size_area_spare  * sizeof(char)           +
                       2*_MAX_PERTUR * sizeof(TIPO_PERT);
/*
   printf("\t size_parte1_bktk=%d size_blocco_bktk=%d size_area_spare=%d\n",
              size_parte1_bktk,size_blocco_bktk,size_area_spare);
*/
   switch (azione)
   {
   case LOADBKTK:
      {
      if (tipo_sked == MASTER)
         {
         /* lettura del file snap.dat */
         ret = bktk_load_piac(numero);
         sprintf(messaggio_aus.ausiliario.messaggio, "%d", ret);
         if (atoi(messaggio_aus.ausiliario.messaggio) == (-1))
            fprintf(stderr, "Impossibile caricare il BACKTRACK\n");
         }
/*    Master trasmette i dati e le pert dei modelli non residenti agli slave */
      sked_raccogli_datisnap(MASTER, SLAVE, p_bktk,modo_backtrack);
/*
      rimozione pert remote in fase di LOADBT: il master lo fa al termine
      della fase VALIDATEBT mentre lo slave dopo il LOADIC.
*/
      break;
      }
   case SAVEBKTK:
      {
/*
      IMPORTANTE: lo slave in caso di backtrack usa la funzione
      sked_snapshot_piac per cui non usa tale funzione.
      SAREBBE MEGLIO USARE LA STRESSA FUNZIONE
*/
/*    Gli slave trasmettono dati e pert dei modelli residenti al master */
      sked_raccogli_datisnap(SLAVE, MASTER, p_bktk, modo_backtrack);
      if (tipo_sked == MASTER)
         {
/*       Scrittura del file snap.dat */
         ret = bktk_save_piac(numero);
         sprintf(messaggio_aus.ausiliario.messaggio, "%d", ret);
         if (atoi(messaggio_aus.ausiliario.messaggio) == (-1))
	       fprintf(stderr, "Impossibile salvare il BACKTRACK\n");
         else
	       tot_bktk++;
/*
         rimozione pert remote in fase di SAVEBT: riguarda solo il master
         che ha ricevuto le pert degli slave.
*/
         rm_pert_remote();
         }
      break;
      }
   case DELBKTK:
      {
      if (backtrack_hea[numero - 1].stat == 1)
          ret = bktk_del_piac(numero);
      sprintf(messaggio_aus.ausiliario.messaggio, "%d", ret);
     /*
      * banco_snd(id_msg_monit,SKDIS_REMOVE_ACK+MONIT*SKDIS_OFFSET,0,
      * messaggio_aus.ausiliario.messaggio); 
      */
      if (atoi(messaggio_aus.ausiliario.messaggio) == (-1))
        fprintf(stderr, "Impossibile eliminare il BACKTRACK\n");
      }
   }				/* switch */

   /* libera la memoria */
   free(p_bktk);
}


/*
 * Legge da file la tabella dei backtrack e la carica in shared memory. Se il
 * file non esiste lo crea. 
 */

bktk_tab_read_piac()
{
   int             i, ret, offset;
   int             size_bktk, size_file;
   char            zero = '0';
   int             dim_zero;
   div_t           dim_bktk;

   /* Caricamento shared memory sezione backtrack */
   tot_bktk = 0;
   if (!(fp_bktk = fopen("backtrack.dat", "r")))
   {
      /* Il file di backtrack non esiste e viene creato vuoto */
      fprintf(stderr, "Creazione del nuovo file backtrack.dat\n");
      fp_bktk = fopen("backtrack.dat", "w");
/*
      Prima di scrivere l'area tabellare dei backtrack si aggiunge un header
      gia' caricato durante la costruzione dei file di snapshot.
*/
/*
      NON E' MOLTO BELLO alla creazione del file COPIARE DA SNAP A BK forse
      conviene rifarne la lettura dal momento che viene effettuato alla
      sola creazione del file.
*/
      memcpy(&hreg_bktk,&hreg_snap,sizeof(HEADER_REGISTRAZIONI));
      fwrite(&hreg_bktk,sizeof(HEADER_REGISTRAZIONI),1,fp_bktk);
      for (i = 1; i <= _MAX_BACK_TRACK; i++)
      {
	 backtrack_hea[i - 1].stat    = 0;
	 backtrack_hea[i - 1].prog    = i;
	 backtrack_hea[i - 1].pos     = 0;
	 backtrack_hea[i - 1].forzato = 0;
	 backtrack_hea[i - 1].tempo   = 0.;
	 backtrack_hea[i - 1].mod     = 0.;
         strcpy(backtrack_hea[i - 1].val,"0\00");
	 strcpy(backtrack_hea[i - 1].descr, " >>>>    BACKTRACK FREE    <<<<\00");
	 strcpy(backtrack_hea[i - 1].datasn, "00/00/00\00");
	 strcpy(backtrack_hea[i - 1].temposn, "0\00");
	 fwrite(&backtrack_hea[i - 1], sizeof(BKTAB), 1, fp_bktk);
      }
/*
      Dimensione relativa all'area dati di un bktk. Contiene:
         1) area effettiva variabili     2) tempo effettuazione baktrack
         3) DIM_SNAP_AUS                 4) SNAP_SKED 
         5) vettori ind e val updown     6) Area complessiva pert
*/
      size_area_spare  = _SPARE_SNAP * AREA_SPARE;
      size_bktk = _MAX_BACK_TRACK * (size_area_dati +  sizeof(float)  +
				    sizeof(SNAP_SKED) + DIM_SNAP_AUS +
                                    size_area_spare * sizeof(char)   +
                                    2*_MAX_PERTUR*sizeof(TIPO_PERT) );
/*
      printf("\n\t Parametri creazione file backtrack.dat\n");
      printf("\t header=%d+BKTAB=%d+size_parte_bktk=%d ==> sizefile=%d \n\n",
         sizeof(HEADER_REGISTRAZIONI),
         _MAX_BACK_TRACK*sizeof(BKTAB),
         size_bktk,
         sizeof(HEADER_REGISTRAZIONI)+_MAX_BACK_TRACK*sizeof(BKTAB)+size_bktk);
*/
      printf("\t ==> size file=%d\n",
         sizeof(HEADER_REGISTRAZIONI)+_MAX_BACK_TRACK*sizeof(BKTAB)+size_bktk);

      dim_bktk = div(size_bktk, sizeof(float));
      if (dim_bktk.rem == 0)
      {
	 size_file = size_bktk / sizeof(float);
	 dim_zero = sizeof(float);
      } else
      {
	 size_file = size_bktk;
	 dim_zero = sizeof(char);
      }
      for (i = 0; i < size_file; i++)
	 fwrite(&zero, dim_zero, 1, fp_bktk);
      load_stato_cr(&stato_cr);
      stato_cr.last_bktk_save = 0;
      stato_cr.last_bktk_load = 0;
      save_stato_cr(&stato_cr);
   } else
   {
      /* Il file esiste */
/*    Il file esiste, viene letto l'header */
      fread(&hreg_bktk,sizeof(HEADER_REGISTRAZIONI),1,fp_bktk);
      for (i = 1; i <= _MAX_BACK_TRACK; i++)
          {
          fread(&backtrack_hea[i - 1], sizeof(BKTAB), 1, fp_bktk);
          /*
          printf("bktk_share [%d] ", i-1);
          printf("prog=%d stat=%d pos=%d forz=%d <%s> dat=%s t=%f\n", 
                  backtrack_hea[i - 1].prog, 
                  backtrack_hea[i - 1].stat, 
                  backtrack_hea[i -  1].pos, 
                  backtrack_hea[i - 1].forzato, 
                  backtrack_hea[i - 1].descr, 
                  backtrack_hea[i - 1].datasn, 
                  backtrack_hea[i - 1].tempo);
         */
	 if (backtrack_hea[i - 1].stat == 1)
	    ++tot_bktk;
      }
   }
   fclose(fp_bktk);

   /*
    * fopen ("backtrack.dat", "r+"); 
    */
}


/*
 * Salva la copia della shared memory in "posizione" nel coda al file. La
 * posizione va conteggiata da 1 a _MAX_BACK_TRACK ma viene passato come
 * parametro in notazione C per cui da 0 a _MAX_BACK_TRACK. 
 */
int bktk_save_piac(int posizione)
{
char *app;
int   offset,offset_tab;
int   i, k;
char  prova[30];
float tempo;
char *area_spare;
TIPO_PERT *pert_tmp,*pert_tmp_att;   /* perturbazioni attive e in attesa */
TIPO_PERT *pert_file,*pert_file_att; /* perturbazioni salvate su file    */

   if (posizione >= _MAX_BACK_TRACK)
      {
      fprintf(stderr, "bktk_save:gia' stati salvati _MAX_BACK_TRACK\n");
      return (-1);
      }
/*
   printf("sked_backtrack_piac, SAVE: Salvataggio back [%s] [num %d]\n",
	  backtrack_hea[posizione].descr, posizione + 1);
*/
   pert_file     = (TIPO_PERT*)calloc(_MAX_PERTUR,sizeof(TIPO_PERT));
   pert_file_att = (TIPO_PERT*)calloc(_MAX_PERTUR,sizeof(TIPO_PERT));

   if((pert_tmp=RtDbPGetPuntPert(dbpunti))==NULL)
       {
       printf("bktk_save: non riesco ad agganciare le perturbazioni\n");
       return(-1);
       }
   else
       {
       memcpy(pert_file,pert_tmp,_MAX_PERTUR*sizeof(TIPO_PERT));
       }
   if((pert_tmp_att=RtDbPGetPuntPertAtt(dbpunti))==NULL)
       {
       printf("bktk_save: non aggancio le perturbazioni in attesa\n");
       return(-1);
       }
   else
       {
       memcpy(pert_file_att,pert_tmp_att,_MAX_PERTUR*sizeof(TIPO_PERT));
       }

   if (!(fp_bktk2 = fopen("backtrack.dat", "r+")))
   {
      fprintf(stderr, "Il file di backtrack non esiste\n");
      exit(0);
   }

/* 0) Registrazione tabelle  del backtrack */
   offset = sizeof(HEADER_REGISTRAZIONI) + posizione * sizeof(BKTAB);
   fseek(fp_bktk2, offset, 0);
   offset_tab = offset;
   fwrite(&backtrack_hea[posizione], sizeof(BKTAB), 1, fp_bktk2);

/* 1) Area dati */
   offset = size_parte1_bktk + posizione * size_blocco_bktk; 
   fseek(fp_bktk2, offset, 0);
   fwrite(area_dati, size_area_dati, 1 , fp_bktk2);

/* 2) Registra il tempo */
   RtDbPGetTime(dbpunti,&tempo);
   fwrite(&tempo, 1,sizeof(float) , fp_bktk2);

/* 3) DIM_SNAP_AUS */
   app = (char *) calloc(DIM_SNAP_AUS,sizeof(char));
   fwrite(app, DIM_SNAP_AUS, 1, fp_bktk2);

/* 4) Sommari  */
   fwrite(&sommari_backtrack, sizeof(SNAP_SKED), 1, fp_bktk2);

/* 5) Area libera */
   if ( size_area_spare>0 )
      {
      area_spare = (char*)calloc(size_area_spare,sizeof(char));
      memcpy(area_spare,TESTO_PROVA,strlen(TESTO_PROVA)*sizeof(char));
      }
   fwrite(area_spare, sizeof(char), size_area_spare, fp_bktk2);
   if ( size_area_spare>0 )
      free(area_spare);

/* 6) Area pert che comprende gli updown */
/* In realta' non sarebbe necessario fare un fseek */
   offset = size_parte1_bktk  + (posizione + 1) * size_blocco_bktk -
            2*_MAX_PERTUR * sizeof(TIPO_PERT) ;
   fseek(fp_bktk2, offset, 0);
   fwrite(pert_file,     sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk2);
   fwrite(pert_file_att, sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk2);
   /*
    * MostraPert(pert_file,1,_MAX_PERTUR);
    * MostraPert(pert_file_att,1,_MAX_PERTUR);
    */
   StampePertFile(pert_file, pert_file_att, 1, 1);

   fclose(fp_bktk2);

   memcpy(&prova[0], &sommari_backtrack, 30);
   prova[29] = 0;
   /*
    * memcpy(app,&sommari_backtrack,DIM_SNAP_AUS); app[DIM_SNAP_AUS-1]=0;
    * printf("--------------------------> <%s>\n",app); 
    */
   free(app);

/* Carica i valori caratteristici degli slot */
   if ( attiva_listaci==1 )
      {
      for (i = 0; i < MAX_VAL_SNAP; i++)
         if (slot_bktk[i] >= 0)
            bktk_slot_piac(i + 1, slot_bktk[i], posizione + 1);
      fseek(fp_bktk, offset_tab, 0);
      fwrite(&backtrack_hea[posizione], sizeof(BKTAB), 1, fp_bktk);
      }

/* Aggiornamenti */
   stato_cr.last_bktk_save = posizione + 1;
   save_stato_cr(&stato_cr);

   free(pert_file);
   free(pert_file_att);
   return (posizione);
}


/*
 * Copia nella shared memory il backtrack identificato da posizione. La
 * posizione va conteggiata da 1 a _MAX_BACK_TRACK. 
 */
int bktk_load_piac(int posizione)
{
int    offset;
int    i, k;
char  *app;
float  tempo;
char *area_spare;
TIPO_PERT *pert_tmp,*pert_tmp_att;
TIPO_PERT *pert_mem;

   printf("sked_backtrack_piac, LOAD: Caricamento backt. %s [num %d]\n",
           backtrack_hea[posizione - 1].descr, posizione);

   pert_tmp     = (TIPO_PERT*)calloc(_MAX_PERTUR,sizeof(TIPO_PERT));
   pert_tmp_att = (TIPO_PERT*)calloc(_MAX_PERTUR,sizeof(TIPO_PERT));

   if (!(fp_bktk = fopen("backtrack.dat", "r")))
   {
      fprintf(stderr, "Il file di backtrack non esiste\n");
      exit(0);
   }

/* 1) Area dati */
   offset = size_parte1_bktk + (posizione - 1) * size_blocco_bktk;
   fseek(fp_bktk, offset, 0);
   fread(area_dati, size_area_dati,1, fp_bktk);

/* 2) Lettura e setting del Tempo */
   fread(&tempo, 1,sizeof(float), fp_bktk);
   RtDbPPutTime(dbpunti,tempo);

/* 3) DIM_SNAP_AUS */
   app = (char *) malloc(DIM_SNAP_AUS);
   fread(app, DIM_SNAP_AUS, 1, fp_bktk);
   free(app);

/* 4) Sommari */
   fread(&sommari_backtrack, sizeof(SNAP_SKED), 1, fp_bktk);

/* 5) Area libera */
   area_spare = (char*)calloc(size_area_spare,sizeof(char));
   fread(area_spare, sizeof(char), size_area_spare, fp_bktk);
   if ( size_area_spare > 0 )
      {
      /*printf("\t Letto area spare=%s\n",area_spare);*/
      free(area_spare);
      }

/* 6) Area pert che comprende anche gli updown */
   fread(pert_tmp,     sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk);
   fread(pert_tmp_att, sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk);
   /* 
    * MostraPert(pert_tmp,1,_MAX_PERTUR);
    * MostraPert(pert_tmp_att,1,_MAX_PERTUR);
    */
   StampePertFile(pert_tmp, pert_tmp_att, 0, 1);

/* Copio l'area letta (potrei leggerla direttamente) */
   if((pert_mem=RtDbPGetPuntPert(dbpunti))==NULL)
       {
       printf("\t L'area PERT letta non la posso copiare\n");
       return(-1);
       }
   else
       memcpy(pert_mem,pert_tmp,_MAX_PERTUR*sizeof(TIPO_PERT));

   if((pert_mem=RtDbPGetPuntPertAtt(dbpunti))==NULL)
       {
       printf("\t L'area PERT att letta non la posso copiare\n");
       return(-1);
       }
   else
       memcpy(pert_mem,pert_tmp_att,_MAX_PERTUR*sizeof(TIPO_PERT));

   fclose(fp_bktk);

   /* Copia il database nel database di LEGOGRAF */
   RtDbPCopyDb(dbpunti_ext,dbpunti);
   stato_cr.last_bktk_load = posizione;
   save_stato_cr(&stato_cr);

   free(pert_tmp);
   free(pert_tmp_att);
   return (posizione);
}


/*
 * Elimina il backtrack identificato da posizione. La posizione va
 * conteggiata da 1 a _MAX_BACK_TRACK. 
 */
int bktk_del_piac(int posizione)
{
   int             pos, i;
   int             offset;

   printf("sked_backtrack_piac, bktk_del_piac: Eliminazione backt %s [num %d\n",
	  backtrack_hea[posizione - 1].descr, posizione);
   backtrack_hea[posizione - 1].stat = 0;
   backtrack_hea[posizione - 1].tempo = 0.;
   backtrack_hea[posizione - 1].mod = 0;
   memset(backtrack_hea[posizione - 1].descr, 0, SNAP_DESC);
   strcpy(backtrack_hea[posizione - 1].descr, " >>>>  BACKTRACK FREE    <<<<\00");
   memset(backtrack_hea[posizione - 1].datasn, 0, DATA_SNAP);
   strcpy(backtrack_hea[posizione - 1].datasn, "00/00/00\00");
   memset(backtrack_hea[posizione - 1].temposn, 0, TEMPO_SNAP);
   strcpy(backtrack_hea[posizione - 1].temposn, "0\00");
   if (!(fp_bktk = fopen("backtrack.dat", "r+")))
   {
      fprintf(stderr, "Il file di backtrack non esiste\n");
      exit(0);
   }
   /* Registra l'header del backtrack eliminato */
   offset = sizeof(HEADER_REGISTRAZIONI) + (posizione - 1) * sizeof(BKTAB);
   fseek(fp_bktk, offset, 0);
   fwrite(&backtrack_hea[posizione - 1], sizeof(BKTAB), 1, fp_bktk);
   fclose(fp_bktk);
   --tot_bktk;
   return (posizione);
}


/*
 * Riempie la tabella dei valori caratteristici di ogni singolo backtrack 
 */
bktk_slot_piac(pos, variabile, num_bktk)
   int             variabile, pos, num_bktk;
{
   int             i;
   FILE           *fp_bktk;
   int             offset;
   float           app;
   int             inizio, fine;

   if (num_bktk > 0)
   {
      inizio = num_bktk - 1;
      fine   = num_bktk;
   } else
   {
      inizio = 0;
      fine   = _MAX_BACK_TRACK;
   }

   if (!(fp_bktk = fopen("backtrack.dat", "r")))
   {
      fprintf(stderr, "Il file di backtrack non esiste\n");
      exit(0);
   }
   for (i = inizio; i < fine; i++)
      if (backtrack_hea[i].stat == 1)
      {
      offset = sizeof(HEADER_REGISTRAZIONI) + _MAX_BACK_TRACK * sizeof(BKTAB) +
	       i * ( size_area_dati       +  sizeof(float)  +
#if defined MFFR
	             sizeof(SNAP_SKED)                      +
#endif
                     DIM_SNAP_AUS                           + 
                     size_area_spare * sizeof(char)         +   
                     2*_MAX_PERTUR * sizeof(TIPO_PERT) )                      +
	       variabili[variabile].addr * sizeof(float);
      fseek(fp_bktk, offset, 0);
      fread(&app, 1, sizeof(float), fp_bktk);
      backtrack_hea[i].val[pos - 1] = app;
      }
   fclose(fp_bktk);
   return(0);
}


ins_tacca_bktk_piac(valore)
   int             valore;
{
FILE *fp;
int  offset=0;

   if (stato_cr.last_bktk_save > 0)
      {
      printf("ins_tacca_bktk_piac: inserita tacca tipo %d nel backtrack %d\n", 
              valore, stato_cr.last_bktk_save);
      if (backtrack_hea[stato_cr.last_bktk_save - 1].forzato < valore)
	 backtrack_hea[stato_cr.last_bktk_save - 1].forzato = valore;
      if (!(fp = fopen("backtrack.dat", "r+")))
      {
         fprintf(stderr, "Il file di backtrack non esiste\n");
         exit(0);
      }
      offset = sizeof(HEADER_REGISTRAZIONI);
      fseek(fp, offset, 0);
      fwrite(&backtrack_hea[0], sizeof(BKTAB), _MAX_BACK_TRACK, fp);
      fclose(fp);
      }
}


del_tacca_bktk_piac()
{
FILE *fp;
int  offset=0;

if (stato_cr.last_bktk_save > 0)
   printf("del_tacca_bktk_piac: eliminaz. tacca tipo %d dal backt. %d -> %d\n",
           backtrack_hea[stato_cr.last_bktk_save - 1].forzato, 
           stato_cr.last_bktk_save);

   if ((stato_cr.last_bktk_save > 0) &&
       (backtrack_hea[stato_cr.last_bktk_save - 1].forzato != 2))
      {
      backtrack_hea[stato_cr.last_bktk_save - 1].forzato = 0;
      if (!(fp = fopen("backtrack.dat", "r+")))
      {
         fprintf(stderr, "Il file di backtrack non esiste\n");
         exit(0);
      }
      offset = sizeof(HEADER_REGISTRAZIONI);
      fseek(fp, offset, 0);
      fwrite(&backtrack_hea[0], sizeof(BKTAB), _MAX_BACK_TRACK, fp);
      fclose(fp);
      }
}

bktk_clear_piac()
{
   int             pos, i;
   int             offset;
   int             posizione;

   if (!(fp_bktk = fopen("backtrack.dat", "r+")))
   {
      fprintf(stderr, "Il file di backtrack non esiste\n");
      exit(0);
   }
   for (posizione = 0; posizione < _MAX_BACK_TRACK; posizione++)
   {
      backtrack_hea[posizione].stat = 0;
      backtrack_hea[posizione].tempo = 0.;
      backtrack_hea[posizione].mod = 0;
      memset(backtrack_hea[posizione].descr, 0, SNAP_DESC);
      strcpy(backtrack_hea[posizione].descr, " >>>>  BACKTRACK FREE    <<<<\00");
      memset(backtrack_hea[posizione].datasn, 0, DATA_SNAP);
      strcpy(backtrack_hea[posizione].datasn, "00/00/00\00");
      memset(backtrack_hea[posizione].temposn, 0, TEMPO_SNAP);
      strcpy(backtrack_hea[posizione].temposn, "0\00");
      /* Registra l'header del backtrack eliminato */
      offset = sizeof(HEADER_REGISTRAZIONI) + (posizione) * sizeof(BKTAB);
      fseek(fp_bktk, offset, 0);
      fwrite(&backtrack_hea[posizione], sizeof(BKTAB), 1, fp_bktk);
   }
   fclose(fp_bktk);
   stato_cr.last_bktk_save = 0;
   stato_cr.last_bktk_load = 0;
   save_stato_cr(&stato_cr);
}

#endif
