/**********************************************************************
*
*       C Source:               sked_backtrack.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Wed Mar 25 17:42:25 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_backtrack.c-4 %  (%full_filespec: sked_backtrack.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_backtrack.c	5.1\t11/7/95";
/*
   modulo sked_backtrack.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_backtrack.c	5.1
*/
#if defined BACKTRACK
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
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "sked.h"
# include "sked_fun.h"
# include "comandi.h"
# include "dispatcher.h"
# include "libnet.h"

/*
    PER COMPATIBILITA CON LA NUOVA STRUTTURA CHE HA ELIMINATO
    DAI FILE DI INCLUDE LE DEFINE MAX_SNAP_SHOT MAX_BACK_TRACK 
    E PER NON ELIMINARE TALI FILE RELATIVI ALLA VECCHIA GESTIONE DI
    backtrack.dat E snapshot.dat (file non allocato staticamente allo startup) 
    SI INTRODUCE:
*/
#define MAX_BACK_TRACK 60

extern RtDbPuntiOggetto dbpunti;
extern RtDbPuntiOggetto dbpunti_ext;

extern int      tipo_sked;

extern int      stato_sked;

int             tot_bktk;	/* numero dei backtrack registrati */

extern int      nmod;		/* numero dei modelli */

extern
BKTAB *backtrack_hea;			/* area shm per tabella dei backtrack */
extern
int size_area_dati;     /* size in byte dell'area dati di tutte le task */
extern
float *area_dati;

extern double   tempo_sim;	/* tempo della simulazione */

extern int      fp_ordini[MAX_MODEL];	/* puntatori dei socket a cui spedire
					 * i comandi, solo per sked master */

extern int      id_msg_sked;	/* id coda messaggi  da processi read */

extern int      id_msg_snap;	/* id coda messaggi  da processi ausiliari */

extern int      id_msg_monit;	/* id coda messaggi  da monit */
extern int      id_msg_banco;	/* id coda messaggi  da banco */

extern int      numero_slave;	/* numero di nodi SLAVE, solo per MASTER  */

int             fp_master;	/* puntatore al socket del MAIN solo per
				 * slave  */

extern int      fp_com[MAX_MODEL];	/* 0 -> task sulla stessa macchina 1
					 * -> task su macchine diverse fp ->
					 * socket scrittura */

int             id_sh;		/* identificatore sh_var */
VARIABILI      *variabili;	/* database variabili di tutti i modelli */
char           *ind_sh_top;	/* puntatore inizio shared memory sh_var */

FILE           *fp_bktk;	/* descrittore del file backtrack.dat */

extern int      slot_bktk[MAX_VAL_SNAP];	/* indirizzi delle variabili
						 * caratteristiche dei
						 * backtrack */
STATO_CR        stato_cr;

SNAP_SKED       sommari_backtrack;


int sked_backtrack(azione, numero)
   int             azione;
   short           numero;
{
   int             i, ret;
   MSG_NET         messaggio_net;
   MSG_AUS         messaggio_aus;
   PACCHETTO_SNAP *pacchetto_bktk;
   FILE           *fp;
   int size_task;
   int ini_task;
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

   /* allocazione dinamica delle variabili */
   pacchetto_bktk = (PACCHETTO_SNAP *) malloc(sizeof(PACCHETTO_SNAP));
#if defined UNIX
   pacchetto_bktk->dato = (float*)malloc((_N005+_N007)*sizeof(float));
#else
   pacchetto_bktk->dato = (float*)malloc((N005+N007)*sizeof(float));
#endif

   /* manda il messaggio di BACKTRACK alle macchine SLAVE  */
   if (tipo_sked == MASTER)
   {
      messaggio_net.header_net.tipo = COMSIM;
      messaggio_net.header_net.codice = azione;
      messaggio_net.header_net.lun = 0;
      for (i = 0; i < nmod; i++)
	 if (fp_ordini[i] > 0)
	 {
	    if (writen(fp_ordini[i], (char*)&messaggio_net.header_net,
		       sizeof(HEADER_NET)) < 0)
	    {
	       sked_stato(STATO_ERRORE);
	       fprintf(stderr, "Impossibile com %d\n", i);
	       sked_errore();
	    }
	 }
   }
   switch (azione)
   {
   case LOADBKTK:
      {
	 if (tipo_sked == MASTER)
	 {
	    /* lettura del file snap.dat */
	    ret = bktk_load(numero);
	    sprintf(messaggio_aus.ausiliario.messaggio, "%d", ret);
	    if (atoi(messaggio_aus.ausiliario.messaggio) == (-1))
	       fprintf(stderr, "Impossibile caricare il BACKTRACK");
	    for (i = 0; i < nmod; i++)
	       if (fp_com[i] != 0)
	       {
		  pacchetto_bktk->header_net.sorg = (-1);	/* momentaneamente a -1 */
		  pacchetto_bktk->header_net.dest = (-1);	/* momentaneamente a -1 */
		  pacchetto_bktk->header_net.tasksorg = i;
		  pacchetto_bktk->header_net.taskdest = (-1);
		  pacchetto_bktk->header_net.tipo = DATISNAP;
		  pacchetto_bktk->header_net.flag = (-1);
		  size_task = RtDbPSizeModelli(dbpunti,i);
		  pacchetto_bktk->header_net.lun = size_task;
		  pacchetto_bktk->header_net.codice = (-1);
		  ini_task = RtDbPInizioModelli(dbpunti,i);
		  memcpy(&(pacchetto_bktk->dato[0]),
			&area_dati[ini_task],size_task);
		  if (writen(fp_com[i], (char*)pacchetto_bktk,
		   sizeof(HEADER_NET) + pacchetto_bktk->header_net.lun) < 0)
		  {
		     fprintf(stderr, "Errore impossibile scrivere su nodo MASTER\n");
		     perror("--> ");
		     if (stato_sked < STATO_ERRORE)
		     {
			sked_stato(STATO_ERRORE);
			sked_errore();
		     }
		  }
	       }
	 } else
	 {
	    for (i = 0; i < nmod; i++)
	       if (fp_com[i] == 0)
	       {
		  if (msg_rcv(id_msg_sked, &messaggio_net, sizeof(HEADER_NET) +
			      sizeof(float) * MAX_DATI_NET, (long)DATISNAP,
			      !IPC_NOWAIT, TIMEOUT_SKED) == TIMEOUT_SCADUTO)
		  {
		     if (stato_sked < STATO_ERRORE)
		     {
			sked_stato(STATO_ERRORE);
			sked_errore();
		     }
		  }
	       }
	 }
	 break;
      }
   case SAVEBKTK:
      {
	 if (tipo_sked == MASTER)
	 {
	    for (i = 0; i < nmod; i++)
	       if (fp_com[i] != 0)
	       {
		  if (msg_rcv(id_msg_sked, &messaggio_net, sizeof(HEADER_NET) +
			      sizeof(float) * MAX_DATI_NET, (long)DATISNAP,
			      !IPC_NOWAIT, TIMEOUT_SKED) == TIMEOUT_SCADUTO)
		  {
		     if (stato_sked < STATO_ERRORE)
		     {
			sked_stato(STATO_ERRORE);
			sked_errore();
		     }
		  }
	       }
	    /* scrittura del file snap.dat */
	    ret = bktk_save(numero);
	    sprintf(messaggio_aus.ausiliario.messaggio, "%d", ret);
	    if (atoi(messaggio_aus.ausiliario.messaggio) == (-1))
	       fprintf(stderr, "Impossibile salvare il BACKTRACK");
	    else
	       tot_bktk++;
	 } else
	 {
	    for (i = 0; i < nmod; i++)
	       if (fp_com[i] == 0)
	       {
		  pacchetto_bktk->header_net.sorg = (-1);	/* momentaneamente a -1 */
		  pacchetto_bktk->header_net.dest = (-1);	/* momentaneamente a -1 */
		  pacchetto_bktk->header_net.tasksorg = i;
		  pacchetto_bktk->header_net.taskdest = (-1);
		  pacchetto_bktk->header_net.tipo = DATISNAP;
		  pacchetto_bktk->header_net.flag = (-1);
		  size_task = RtDbPSizeModelli(dbpunti,i);
		  pacchetto_bktk->header_net.lun = size_task;
		  pacchetto_bktk->header_net.codice = (-1);
		  ini_task = RtDbPInizioModelli(dbpunti,i);
		  memcpy(&(pacchetto_bktk->dato[0]),
			&area_dati[ini_task],size_task);
		  if (writen(fp_master, (char*)pacchetto_bktk,
		   sizeof(HEADER_NET) + pacchetto_bktk->header_net.lun) < 0)
		  {
		     fprintf(stderr, "Errore impossibile scrivere su nodo MASTER\n");
		     perror("--> ");
		     if (stato_sked < STATO_ERRORE)
		     {
			sked_stato(STATO_ERRORE);
			sked_errore();
		     }
		  }
	       }
	 }
	 break;
      }
   case DELBKTK:
      {
	 if (backtrack_hea[numero - 1].stat == 1)
	    ret = bktk_del(numero);
	 sprintf(messaggio_aus.ausiliario.messaggio, "%d", ret);
	 /*
	  * banco_snd(id_msg_monit,SKDIS_REMOVE_ACK+MONIT*SKDIS_OFFSET,0,
	  * messaggio_aus.ausiliario.messaggio); 
	  */
	 if (atoi(messaggio_aus.ausiliario.messaggio) == (-1))
	    fprintf(stderr, "Impossibile eliminare il BACKTRACK");
      }
   }				/* switch */

   /* libera la memoria */
   free(pacchetto_bktk->dato);
   free(pacchetto_bktk);

}


/*
 * legge da file la tabella dei backtrack e la carica in shared memory Se il
 * file non esiste lo crea 
 */

void bktk_tab_read()
{
   int             i, ret, offset;

   /* caricamento shared memory sezione backtrack */
   tot_bktk = 0;
   if (!(fp_bktk = fopen("backtrack.dat", "r")))
   {
      /* il file di backtrack non esiste e viene creato vuoto */
      fp_bktk = fopen("backtrack.dat", "w");
      for (i = 1; i <= MAX_BACK_TRACK; i++)
      {
	 backtrack_hea[i - 1].stat = 0;
	 backtrack_hea[i - 1].prog = i;
	 backtrack_hea[i - 1].pos = -1;
	 backtrack_hea[i - 1].forzato = 0;
         backtrack_hea[i - 1].tempo   = 0.;
         strcpy((char*)backtrack_hea[i - 1].val,"0\00");
	 strcpy(backtrack_hea[i - 1].descr, " >>>>    BACKTRACK FREE    <<<<\00");
	 strcpy(backtrack_hea[i - 1].datasn, "00/00/00\00");
	 strcpy(backtrack_hea[i - 1].temposn, "0\00");
	 fwrite(&backtrack_hea[i - 1], sizeof(BKTAB), 1, fp_bktk);
      }
      load_stato_cr(&stato_cr);
      stato_cr.last_bktk_save = 0;
      stato_cr.last_bktk_load = 0;
      save_stato_cr(&stato_cr);
   } else
   {
      /* il file esiste */
      for (i = 1; i <= MAX_BACK_TRACK; i++)
      {
	 fread(&backtrack_hea[i - 1], sizeof(BKTAB), 1, fp_bktk);
	 /*
	  * printf ("bktk_shared prog=%d stat=%d pos=%d forzato=%d %s data=%s
	  * t=%s\n", backtrack_hea[i - 1].prog, backtrack_hea[i - 1].stat, backtrack_hea[i -
	  * 1].pos, backtrack_hea[i - 1].forzato, backtrack_hea[i - 1].descr, backtrack_hea[i -
	  * 1].datasn, backtrack_hea[i - 1].temposn); 
	  */
	 if (backtrack_hea[i - 1].stat == 1)
	    ++tot_bktk;
      }
   }
   fclose(fp_bktk);
   fopen("backtrack.dat", "r+");

}

/*
 * salva la copia della shared memory in coda al file La posizione va
 * conteggiata da 1 a MAX_BACK_TRACK 
 */
int bktk_save(posizione)
   int             posizione;
{
   char           *app;
   int             offset;
   int             i;
   char            prova[30];
   float 	   tempo;

   printf("sked_backtrack: backtrack %s [%d] salvato in posizione %d \n",
    backtrack_hea[posizione].descr, backtrack_hea[posizione].prog, backtrack_hea[posizione].pos);

   /* registra l'header del backtrack */
   offset = posizione * sizeof(BKTAB);
   fseek(fp_bktk, offset, 0);
   fwrite(&backtrack_hea[posizione], sizeof(BKTAB), 1, fp_bktk);
   /* registra il backtrack */
   offset = MAX_BACK_TRACK * sizeof(BKTAB) +
      (backtrack_hea[posizione].pos - 1) * (size_area_dati + sizeof(float) +
     sizeof(SNAP_SKED) + DIM_SNAP_AUS + MAX_UPDOWN * (sizeof(float) + sizeof(int)));
   fseek(fp_bktk, offset, 0);
   fwrite(area_dati, size_area_dati, 1, fp_bktk);
   RtDbPGetTime(dbpunti,&tempo);
   fwrite(&tempo, 1, sizeof(float), fp_bktk);
   app = (char *) calloc(DIM_SNAP_AUS,sizeof(char));
   fwrite(app, DIM_SNAP_AUS, 1, fp_bktk);
   fwrite(&sommari_backtrack, sizeof(SNAP_SKED), 1, fp_bktk);
   memcpy(&prova[0], &sommari_backtrack, 30);
   prova[29] = 0;
   /*
    * memcpy(app,&sommari_backtrack,DIM_SNAP_AUS); app[DIM_SNAP_AUS-1]=0;
    * printf("--------------------------> <%s>\n",app); 
    */
   free(app);
   /*
    * carica i valori caratteristici degli slot 
    */
   for (i = 0; i < MAX_VAL_SNAP; i++)
      if (slot_bktk[i] >= 0)
	 bktk_slot(i + 1, slot_bktk[i], posizione + 1);

   stato_cr.last_bktk_save = posizione + 1;
   save_stato_cr(&stato_cr);
   return (posizione);
}

/*
 * Copia nella shared memory il backtrack La posizione va conteggiata da 1 a
 * MAX_BACK_TRACK 
 */
int bktk_load(posizione)
   int             posizione;
{
   int             offset;
   int             i;
   float           tempo;

   printf("sked_backtrack: Caricamento backtrack %s\n", backtrack_hea[posizione - 1].descr);
   offset = MAX_BACK_TRACK * sizeof(BKTAB) +
      (backtrack_hea[posizione - 1].pos - 1) * (size_area_dati + sizeof(float) +
	     sizeof(SNAP_SKED) + DIM_SNAP_AUS + MAX_UPDOWN * sizeof(float) +
					 MAX_UPDOWN * sizeof(int));
   fseek(fp_bktk, offset, 0);
   fread(area_dati, size_area_dati,1, fp_bktk);
   fread(&tempo, 1,sizeof(float), fp_bktk);
   RtDbPPutTime(dbpunti,tempo);
   fread(&sommari_backtrack, sizeof(SNAP_SKED), 1, fp_bktk);
   /* copia il database nel database di LEGOGRAF */
   RtDbPCopyDb(dbpunti_ext,dbpunti);

   stato_cr.last_bktk_load = posizione;
   save_stato_cr(&stato_cr);
   return (posizione);
}

/*
 * Elimina il backtrack identificato da posizione La posizione va conteggiata
 * da 1 a MAX_BACK_TRACK 
 */
int bktk_del(posizione)
   int             posizione;
{
   int             pos, i;
   int             offset, size_bktk;
   FILE           *fp_app;
   char           *app;

   printf("sked_backtrack: Eliminazione backtrack %s\n", backtrack_hea[posizione - 1].descr);
   pos = backtrack_hea[posizione - 1].pos;
   backtrack_hea[posizione - 1].stat = 0;
   backtrack_hea[posizione - 1].mod = 0;
   backtrack_hea[posizione - 1].pos = -1;
   memset(backtrack_hea[posizione - 1].descr, 0, SNAP_DESC);
   strcpy(backtrack_hea[posizione - 1].descr, " >>>>  BACKTRACK FREE    <<<<\00");
   memset(backtrack_hea[posizione - 1].datasn, 0, DATA_SNAP);
   strcpy(backtrack_hea[posizione - 1].datasn, "00/00/00\00");
   memset(backtrack_hea[posizione - 1].temposn, 0, TEMPO_SNAP);
   strcpy(backtrack_hea[posizione - 1].temposn, "0\00");
   for (i = 0; i < MAX_BACK_TRACK; i++)
      if ((backtrack_hea[i].pos != (-1)) && (backtrack_hea[i].pos > pos))
	 --backtrack_hea[i].pos;
   /* chiusura file backtrack, rename e riapertura dei due file */
   fclose(fp_bktk);
   rename("backtrack.dat", "backtrack.bak");
   fp_bktk = fopen("backtrack.dat", "w");
   fp_app = fopen("backtrack.bak", "r");

   /* registra gli header degli backtrack */
   for (i = 0; i < MAX_BACK_TRACK; i++)
   {
      fwrite(&backtrack_hea[i], sizeof(BKTAB), 1, fp_bktk);
   }

   /* skip degli header sul vecchio file */
   fseek(fp_app, sizeof(BKTAB) * MAX_BACK_TRACK, 0);

   size_bktk = (size_area_dati + sizeof(float)
		+ sizeof(SNAP_SKED) + DIM_SNAP_AUS +
		MAX_UPDOWN * sizeof(float) + MAX_UPDOWN * sizeof(int));
   app = (char *) malloc(size_bktk);
   for (i = 0; i < tot_bktk; i++)
   {
      fread(app, size_bktk, 1, fp_app);
      if ((pos - 1) != i)
	 fwrite(app, size_bktk, 1, fp_bktk);
   }
   free(app);

   fclose(fp_app);
   fclose(fp_bktk);
   remove("backtrack.bak");
   fp_bktk = fopen("backtrack.dat", "r+");
   --tot_bktk;

   return (posizione);
}


/*
 * riempie la tabella dei valori caratteristici di ogni singolo backtrack 
 */
int bktk_slot(pos, variabile, num_bktk)
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
      fine = num_bktk;
   } else
   {
      inizio = 0;
      fine = MAX_BACK_TRACK;
   }

   if (!(fp_bktk = fopen("backtrack.dat", "r")))
   {
      fprintf(stderr, "Il file di backtrack non esiste\n");
      exit(0);
   }
   for (i = inizio; i < fine; i++)
      if (backtrack_hea[i].stat == 1)
      {
	 offset = MAX_BACK_TRACK * sizeof(BKTAB) +
	    (backtrack_hea[i].pos - 1) *
	    (size_area_dati + sizeof(float) + sizeof(SNAP_SKED) +
	     DIM_SNAP_AUS + MAX_UPDOWN * (sizeof(float) + sizeof(int))) +
	    variabili[variabile].addr * sizeof(float);
	 fseek(fp_bktk, offset, 0);
	 fread(&app, 1, sizeof(float), fp_bktk);
	 backtrack_hea[i].val[pos - 1] = app;
      }
   fclose(fp_bktk);
}


int ins_tacca_bktk(valore)
   int             valore;
{
   FILE           *fp;

   if (stato_cr.last_bktk_save > 0)
   {
      printf("ins_tacca_bktk: inserita tacca tipo %d nel backtrack %d\n", valore, stato_cr.last_bktk_save);
      if (backtrack_hea[stato_cr.last_bktk_save - 1].forzato < valore)
	 backtrack_hea[stato_cr.last_bktk_save - 1].forzato = valore;
      fp = fopen("backtrack.dat", "r+");
      fwrite(&backtrack_hea[0], sizeof(BKTAB), MAX_BACK_TRACK, fp);
      fclose(fp);
   }
}

void del_tacca_bktk()
{
   FILE           *fp;

   if ((stato_cr.last_bktk_save > 0) &&
       (backtrack_hea[stato_cr.last_bktk_save - 1].forzato != 2))
   {
      printf("del_tacca_bktk: eliminazione tacca tipo %d dal backtrack %d -> %d\n",
      backtrack_hea[stato_cr.last_bktk_save - 1].forzato, stato_cr.last_bktk_save);
      backtrack_hea[stato_cr.last_bktk_save - 1].forzato = 0;
      fp = fopen("backtrack.dat", "r+");
      fwrite(&backtrack_hea[0], sizeof(BKTAB), MAX_BACK_TRACK, fp);
      fclose(fp);
   }
}
#endif
