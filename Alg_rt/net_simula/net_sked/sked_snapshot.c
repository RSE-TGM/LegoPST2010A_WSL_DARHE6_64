/**********************************************************************
*
*       C Source:               sked_snapshot.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Wed Mar 25 17:37:37 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_snapshot.c-4 %  (%full_filespec: sked_snapshot.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_snapshot.c	5.2\t2/20/96";
/*
   modulo sked_snapshot.c
   tipo 
   release 5.2
   data 2/20/96
   reserved @(#)sked_snapshot.c	5.2
*/
# include <stdio.h>
# include <errno.h>
# include <string.h>
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
#define MAX_SNAP_SHOT 60


extern RtDbPuntiOggetto dbpunti;
extern RtDbPuntiOggetto dbpunti_ext;

extern int      tipo_sked;

extern int      stato_sked;

int             tot_snap;	/* numero degli snapshot registrati */

extern int      nmod;		/* numero dei modelli */

extern
SNTAB *snapshot_hea;			/* area shm per tabella snapshot */
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


extern int      slot_snap[MAX_VAL_SNAP];	/* indirizzi delle variabili
						 * caratteristiche degli
						 * snapshot */
STATO_CR        stato_cr;

#if defined MFFR
SNAP_SKED       sommari_snapshot;
#endif
#if defined BACKTRACK
extern int      ins_tacca_bktk();
//extern int      del_tacca_bktk();
#endif

int snap_load(int);

void sked_snapshot(azione, numero)
   int             azione;
   short           numero;
{
   int             i, ret;
   MSG_NET         messaggio_net;
   MSG_AUS         messaggio_aus;
   PACCHETTO_SNAP *pacchetto_snap;
   FILE           *fp;
   FILE           *fp_snap;	/* descrittore del file snapshot.dat */
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
   pacchetto_snap = (PACCHETTO_SNAP *) malloc(sizeof(PACCHETTO_SNAP));
#if defined UNIX
   pacchetto_snap->dato = (float*)malloc((_N005+_N007)*sizeof(float));
#else
   pacchetto_snap->dato = (float*)malloc((N005+N007)*sizeof(float));
#endif

   /* manda il messaggio di SNAPSHOT alle macchine SLAVE  */
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
   case LOADSNAP:
      {
	 if (tipo_sked == MASTER)
	 {
	    /* lettura del file snap.dat */
	    ret = snap_load(numero);
	    sprintf(messaggio_aus.ausiliario.messaggio, "%d", ret);
	    if (atoi(messaggio_aus.ausiliario.messaggio) == (-1))
	       fprintf(stderr, "Impossibile caricare lo SNAPSHOT");
	    for (i = 0; i < nmod; i++)
	       if (fp_com[i] != 0)
	       {
		  pacchetto_snap->header_net.sorg = (-1);	/* momentaneamente a -1 */
		  pacchetto_snap->header_net.dest = (-1);	/* momentaneamente a -1 */
		  pacchetto_snap->header_net.tasksorg = i;
		  pacchetto_snap->header_net.taskdest = (-1);
		  pacchetto_snap->header_net.tipo = DATISNAP;
		  pacchetto_snap->header_net.flag = (-1);
		  size_task = RtDbPSizeModelli(dbpunti,i);
		  pacchetto_snap->header_net.lun = size_task;
		  pacchetto_snap->header_net.codice = (-1);
		  ini_task = RtDbPInizioModelli(dbpunti,i);
		  memcpy(&(pacchetto_snap->dato[0]),
			 &area_dati[ini_task],size_task);
		  if (writen(fp_com[i], (char*)pacchetto_snap,
		   sizeof(HEADER_NET) + pacchetto_snap->header_net.lun) < 0)
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
   case SAVESNAP:
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
	    ret = snap_save(numero);
	    sprintf(messaggio_aus.ausiliario.messaggio, "%d", ret);
	    if (atoi(messaggio_aus.ausiliario.messaggio) == (-1))
	       fprintf(stderr, "Impossibile salvare lo SNAPSHOT");
	    else
	       tot_snap++;
	 } else
	 {
	    for (i = 0; i < nmod; i++)
	       if (fp_com[i] == 0)
	       {
		  pacchetto_snap->header_net.sorg = (-1);	/* momentaneamente a -1 */
		  pacchetto_snap->header_net.dest = (-1);	/* momentaneamente a -1 */
		  pacchetto_snap->header_net.tasksorg = i;
		  pacchetto_snap->header_net.taskdest = (-1);
		  pacchetto_snap->header_net.tipo = DATISNAP;
		  pacchetto_snap->header_net.flag = (-1);
		  size_task = RtDbPSizeModelli(dbpunti,i);
		  pacchetto_snap->header_net.lun = size_task;
		  pacchetto_snap->header_net.codice = (-1);
		  ini_task = RtDbPInizioModelli(dbpunti,i);
		  memcpy(&(pacchetto_snap->dato[0]),
			 &area_dati[ini_task],size_task);
		  if (writen(fp_master, (char*)pacchetto_snap,
		   sizeof(HEADER_NET) + pacchetto_snap->header_net.lun) < 0)
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
   case DELSNAP:
      {
	 if (snapshot_hea[numero - 1].stat == 1)
	    ret = snap_del(numero);
	 sprintf(messaggio_aus.ausiliario.messaggio, "%d", ret);
	 if (atoi(messaggio_aus.ausiliario.messaggio) == (-1))
	    fprintf(stderr, "Impossibile eliminare lo SNAPSHOT");
      }
   }				/* switch */

   /* libera la memoria */
   free(pacchetto_snap->dato);
   free(pacchetto_snap);

}


/*
 * legge da file la tabella degli snapshot e la carica in shared memory Se il
 * file non esiste lo crea 
 */

void snap_tab_read()
{
   int             i, ret, offset;
   FILE           *fp_snap;	/* descrittore del file snapshot.dat */

   /* caricamento shared memory sezione snapshot */
   tot_snap = 0;
   if (!(fp_snap = fopen("snapshot.dat", "r")))
   {
      /* il file di snapshot non esiste e viene creato vuoto */
      fp_snap = fopen("snapshot.dat", "w");
      for (i = 1; i <= MAX_SNAP_SHOT; i++)
      {
	 snapshot_hea[i - 1].stat = 0;
	 snapshot_hea[i - 1].prog = i;
	 snapshot_hea[i - 1].pos = -1;
         snapshot_hea[i - 1].forzato = 0;
         snapshot_hea[i - 1].tempo = 0;
         strcpy((char*)snapshot_hea[i - 1].val, "0\00");
	 strcpy(snapshot_hea[i - 1].descr, " >>>>    SNAPSHOT FREE    <<<<\00");
	 strcpy(snapshot_hea[i - 1].datasn, "00/00/00\00");
	 strcpy(snapshot_hea[i - 1].temposn, "0\00");
	 fwrite(&snapshot_hea[i - 1], sizeof(SNTAB), 1, fp_snap);
      }
      load_stato_cr(&stato_cr);
      stato_cr.last_snap_save = 0;
      stato_cr.last_snap_load = 0;
      save_stato_cr(&stato_cr);
   } else
   {
      /* il file esiste */
      for (i = 1; i <= MAX_SNAP_SHOT; i++)
      {
	 fread(&snapshot_hea[i - 1], sizeof(SNTAB), 1, fp_snap);
	 /*
	  * printf ("snap_shared prog=%d stat=%d pos=%d mod=%d %s data=%s
	  * t=%s\n", snapshot_hea[i - 1].prog, snapshot_hea[i - 1].stat, snapshot_hea[i -
	  * 1].pos, snapshot_hea[i - 1].mod, snapshot_hea[i - 1].descr, snapshot_hea[i -
	  * 1].datasn, snapshot_hea[i - 1].temposn); 
	  */
	 if (snapshot_hea[i - 1].stat == 1)
	    ++tot_snap;
      }
   }
   fclose(fp_snap);

}

/*
 * salva la copia della shared memory in coda al file La posizione va
 * conteggiata da 1 a MAX_SNAPSHOT 
 */
int snap_save(posizione)
   int             posizione;
{
   char           *app;
   char           *punt;
   int             offset;
   int             i;
   char            prova[30];
   FILE           *fp_snap;	/* descrittore del file snapshot.dat */

   printf("sked_snapshot: snapshot %s [%d] salvato in posizione %d \n",
    snapshot_hea[posizione].descr, snapshot_hea[posizione].prog, snapshot_hea[posizione].pos);

   /* apertura file di snapshot */
   fp_snap = fopen("snapshot.dat", "r+");

   /* registra l'header dello snapshot */
   offset = posizione * sizeof(SNTAB);
   fseek(fp_snap, offset, 0);
   fwrite(&snapshot_hea[posizione], sizeof(SNTAB), 1, fp_snap);

   /* registra lo snapshot */
   offset = MAX_SNAP_SHOT * sizeof(SNTAB) +
      (snapshot_hea[posizione].pos - 1) * (size_area_dati +
#if defined MFFR
				     sizeof(SNAP_SKED) +
#endif
				     DIM_SNAP_AUS);
   fseek(fp_snap, offset, 0);
   /* elimina gli up down */
   punt = (char *) malloc(size_area_dati);
   memcpy(punt, area_dati, size_area_dati);
   remove_updown((float *) punt);
   fwrite(punt, size_area_dati, 1, fp_snap);
   free(punt);
   app = (char *) calloc(DIM_SNAP_AUS, sizeof(char));
   fwrite(app, DIM_SNAP_AUS, 1, fp_snap);
#if defined MFFR
   fwrite(&sommari_snapshot, sizeof(SNAP_SKED), 1, fp_snap);
   memcpy(&prova[0], &sommari_snapshot, 30);
   prova[29] = 0;
   /*
    * memcpy(app,&sommari_snapshot,DIM_SNAP_AUS); app[DIM_SNAP_AUS-1]=0;
    * printf("--------------------------> <%s>\n",app); 
    */
#endif
   free(app);
   fclose(fp_snap);
   /*
    * carica i valori caratteristici degli slot 
    */
   for (i = 0; i < MAX_VAL_SNAP; i++)
      if (slot_snap[i] >= 0)
	 snap_slot(i + 1, slot_snap[i], posizione + 1);

   stato_cr.last_snap_save = posizione + 1;
   save_stato_cr(&stato_cr);
   return (posizione);
}

/*
 * Copia nella shared memory lo snapshot La posizione va conteggiata da 1 a
 * MAX_SNAPSHOT 
 */
int snap_load(posizione)
   int             posizione;
{
   int             offset;
   int             i;
   char            tempo[TEMPO_SNAP];
   int             ore = 0;
   int             minuti = 0;
   int             secondi = 0;
   int             giorno = 1;
   int             mese = 1;
   int             anno = 2000;
   FILE           *fp_snap;	/* descrittore del file snapshot.dat */

   printf("sked_snapshot: Caricamento snapshot %s\n", snapshot_hea[posizione - 1].descr);

   /* apertura file di snapshot */
   fp_snap = fopen("snapshot.dat", "r");

   offset = MAX_SNAP_SHOT * sizeof(SNTAB) +
      (snapshot_hea[posizione - 1].pos - 1) * ( size_area_dati +
#if defined MFFR
					 sizeof(SNAP_SKED) +
#endif
					 DIM_SNAP_AUS);
   fseek(fp_snap, offset, 0);
   fread(area_dati, size_area_dati, 1, fp_snap);
   /* copia il database nel database di LEGOGRAF */
   RtDbPCopyDb(dbpunti_ext,dbpunti);
#if defined MFFR
   fread(&sommari_snapshot, sizeof(SNAP_SKED), 1, fp_snap);
#endif
   stato_cr.last_snap_load = posizione;
   save_stato_cr(&stato_cr);
#if defined BACKTRACK
   /* inserisce la tacca nell'ultimo backtrack registrato */
   converti_tempo((float) (tempo_sim / 1000),
		  (long*)&ore, (long*)&minuti, (long*)&secondi, 
                  (long*)&giorno, (long*)&mese, (long*)&anno);
   sprintf(tempo, "%2d:%2d:%2d", ore, minuti, secondi);
   if (!strncmp(tempo, snapshot_hea[posizione - 1].temposn, 8))
      del_tacca_bktk();
   else
      ins_tacca_bktk(1);
#endif
   fclose(fp_snap);
   return (posizione);
}

/*
 * Elimina lo snapshot identificato da posizione La posizione va conteggiata
 * da 1 a MAX_SNAPSHOT 
 */
int snap_del(posizione)
   int             posizione;
{
   int             pos, i;
   int             offset, size_snap;
   FILE           *fp_app;
   FILE           *fp_snap;	/* descrittore del file snapshot.dat */
   char           *app;

   printf("sked_snapshot: Eliminazione snapshot %s\n", snapshot_hea[posizione - 1].descr);
   pos = snapshot_hea[posizione - 1].pos;
   snapshot_hea[posizione - 1].stat = 0;
   snapshot_hea[posizione - 1].mod = 0;
#if defined COMPRESS_SNAPSHOT
   snapshot_hea[posizione - 1].pos = -1;
#endif
   memset(snapshot_hea[posizione - 1].descr, 0, SNAP_DESC);
   strcpy(snapshot_hea[posizione - 1].descr, " >>>>    SNAPSHOT FREE    <<<<\00");
   memset(snapshot_hea[posizione - 1].datasn, 0, DATA_SNAP);
   strcpy(snapshot_hea[posizione - 1].datasn, "00/00/00\00");
   memset(snapshot_hea[posizione - 1].temposn, 0, TEMPO_SNAP);
   strcpy(snapshot_hea[posizione - 1].temposn, "0\00");
#if defined COMPRESS_SNAPSHOT
   for (i = 0; i < MAX_SNAP_SHOT; i++)
      if ((snapshot_hea[i].pos != (-1)) && (snapshot_hea[i].pos > pos))
	 --snapshot_hea[i].pos;
   /* chiusura file snapshot, rename e riapertura dei due file */
   rename("snapshot.dat", "snapshot.bak");
   fp_snap = fopen("snapshot.dat", "w");
   fp_app = fopen("snapshot.bak", "r");
#else
   fp_snap = fopen("snapshot.dat", "r+");
#endif
   /* registra gli header degli snapshot */
   for (i = 0; i < MAX_SNAP_SHOT; i++)
   {
      fwrite(&snapshot_hea[i], sizeof(SNTAB), 1, fp_snap);
   }

#if defined COMPRESS_SNAPSHOT
   /* skip degli header sul vecchio file */
   fseek(fp_app, sizeof(SNTAB) * MAX_SNAP_SHOT, 0);

   size_snap = (size_area_dati
#if defined MFFR
		+ sizeof(SNAP_SKED)
#endif
		+ DIM_SNAP_AUS);
   app = (char *) malloc(size_snap);
   for (i = 0; i < tot_snap; i++)
   {
      fread(app, size_snap, 1, fp_app);
      if ((pos - 1) != i)
	 fwrite(app, size_snap, 1, fp_snap);
   }
   free(app);

   fclose(fp_app);
   fclose(fp_snap);
   remove("snapshot.bak");
#else
   fclose(fp_snap);
#endif

   --tot_snap;

   return (posizione);
}


/*
 * riempie la tabella dei valori caratteristici di ogni singolo snapshot 
 */
void snap_slot(pos, variabile, num_snap)
   int             variabile, pos, num_snap;
{
   int             i;
   FILE           *fp_snap;
   int             offset;
   float           app;
   int             inizio, fine;


   if (num_snap > 0)
   {
      inizio = num_snap - 1;
      fine = num_snap;
   } else
   {
      inizio = 0;
      fine = MAX_SNAP_SHOT;
   }

   if (!(fp_snap = fopen("snapshot.dat", "r")))
   {
      fprintf(stderr, "Il file di snapshot non esiste\n");
      exit(0);
   }
   for (i = inizio; i < fine; i++)
      if (snapshot_hea[i].stat == 1)
      {
	 offset = MAX_SNAP_SHOT * sizeof(SNTAB) +
	    (snapshot_hea[i].pos - 1) *
	    ( size_area_dati +
#if defined MFFR
	     sizeof(SNAP_SKED) +
#endif
	     DIM_SNAP_AUS) + variabili[variabile].addr * sizeof(float);
	 fseek(fp_snap, offset, 0);
	 fread(&app, 1, sizeof(float), fp_snap);
	 snapshot_hea[i].val[pos - 1] = app;
      }
   fclose(fp_snap);
}

void sked_snap_mod_descr(int pos, char *descr)
{
   FILE           *fp_snap;	/* descrittore del file snapshot.dat */
   int             offset;

   /* apertura file di snapshot */
   fp_snap = fopen("snapshot.dat", "r+");

   strcpy(snapshot_hea[pos - 1].descr, descr);

   /* registra l'header dello snapshot */
   offset = (pos - 1) * sizeof(SNTAB);
   fseek(fp_snap, offset, 0);
   fwrite(&snapshot_hea[pos - 1], sizeof(SNTAB), 1, fp_snap);
   fclose(fp_snap);
}
