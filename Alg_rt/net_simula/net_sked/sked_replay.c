/**********************************************************************
*
*       C Source:               sked_replay.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Apr  3 12:27:00 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_replay.c-7 %  (%full_filespec: sked_replay.c-7:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_replay.c	5.2\t1/19/96";
/*
   modulo sked_replay.c
   tipo 
   release 5.2
   data 1/19/96
   reserved @(#)sked_replay.c	5.2
*/
#if defined SAVEPERT
#include <stdio.h>
#include <string.h>
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

#define DELTA_REPLAY	10

FILE           *fp_pert;	/* puntatore file perturbazioni */

extern RtDbPuntiOggetto dbpunti;

extern int      stato_sked;

extern int      id_msg_pert;

extern int      id_msg_sked;

extern int      tipo_sked;

int             fp_master;	/* puntatore al socket del MAIN solo per
				 * slave  */

extern int      fp_ordini[MAX_MODEL];	/* puntatori dei socket a cui spedire
					 * i comandi , solo per sked master */

extern int      nmod;


/*
 * 0 chiude il file perturbazioni.dat e lo riapre in lettura 1 legge le
 * perturbazioni e le inserisce nella coda di messaggi 2 chiude il file
 * perturbazioni.dat e lo riapre in append 3 apre il file in append-mode e
 * verifica il contenuto 4 Pulisce le aree di perturbazioni e sulle macchine
 * master resetta i file di registrazione 5 apre il file in append-mode e
 * carica le perturbazioni 
 */
int sked_replay(modo)
   int             modo;
{
   TIPO_PERT       perturbazione;
   int             k = 0;
   int             pos;
   float           tempo;
   int             ret;
fpos_t posizione;
int conta=0;

/* DEBUG
   printf("sked_replay: %d\n", modo);
*/
   switch (modo)
   {
   case 0:
      {
	 printf("\t Chiudo e apro in READONLY\n");
	 fclose(fp_pert);
	 if (!(fp_pert = fopen("perturbazioni.dat", "r")))
	    return (-1);
	 break;
      }
   case 1:
      {
	 if (stato_sked != STATO_REPLAY)
	    return (-1);
	 RtDbPGetTime(dbpunti,&tempo);
	 while (fread(&perturbazione, sizeof(TIPO_PERT), 1, fp_pert))
	 {
	    if ((perturbazione.t == -1) || (perturbazione.t < tempo))
               {
	       printf("Esamino e scarto  pert a t=%f\n", perturbazione.t);
	       continue;
               }
	    if (perturbazione.t < tempo + DELTA_REPLAY)
	    {
	       printf("\t pert_snd_replay a t=%f la pert.t=%f tipo=%d\n",
		      tempo, perturbazione.t,perturbazione.tipo);
	       printf("tipo=%d ind=%d valore_delta=%f rateo_durata=%f t=%f\n",
		      perturbazione.tipo, perturbazione.indirizzo,
		      perturbazione.valore_delta,
		      perturbazione.rateo_durata, perturbazione.t);

	       pert_snd_replay(id_msg_pert, 
		     perturbazione.tipo, perturbazione.indirizzo,
		     perturbazione.valore_delta, perturbazione.rateo_durata,
		     perturbazione.period, perturbazione.phase, 
		     perturbazione.meanvalue, perturbazione.wide, 
		     perturbazione.t_null_var, perturbazione.t);
	    } else
	    {
	       pos = ftell(fp_pert);
	       fseek(fp_pert, pos - sizeof(TIPO_PERT), 0);
	       pos = ftell(fp_pert);
	       printf("\t Next pert [%d]  pos = %d\n",
                       pos/sizeof(TIPO_PERT), pos);
	       break;
	    }
	 }
	 break;
      }
   case 2:
      {

	 printf("\t Chiudo e apro in append\n");

//	 fclose(fp_pert); 
//
// Commentata la fclose tutto funziona. Mistero. Villa e Ciccotelli Aprile 2003
//
	 if (!(fp_pert = fopen("perturbazioni.dat", "a")))
	    return (-1);

	 break;
      }
   case 3:
      {
         if (fp_pert != NULL)
            fclose(fp_pert);
         if (!(fp_pert = fopen("perturbazioni.dat", "r+")))
            {
            if (!(fp_pert = fopen("perturbazioni.dat", "a")))
               return (-1);
            else
               return (1);
            }

         k = 0;
         fgetpos(fp_pert,&posizione);
         while ( (ret=fread(&perturbazione, sizeof(TIPO_PERT), 1, fp_pert))>0)
            {
            RtDbPGetTime(dbpunti,&tempo);
            printf ("sked_replay: 3 [%d] legge pert.t=%f (%d item) tempo=%f\n",
                     k,perturbazione.t,ret,tempo);
            if (perturbazione.t > tempo)
               {
               fsetpos(fp_pert,&posizione);
               perturbazione.t = -1;
               if (fwrite(&perturbazione, sizeof(TIPO_PERT), 1, fp_pert) == 0)
                  {
                  printf("sked_replay[3]: Errore scrittura perturbazioni\n");
                  }
               else
                  printf("\t\t ----> Perturbazione modificata\n");
               }
            k++;
            fgetpos(fp_pert,&posizione);
            }
         fclose(fp_pert);
         if (!(fp_pert = fopen("perturbazioni.dat", "a")))
            return (-1);
	 break;
      }
   case 4:
      {
	 printf("\t init_area_pert e reset perturbazioni.dat per SLAVE\n");
	 init_area_pert();
	 if (tipo_sked != MASTER)
	    /* reset file perturbazioni.dat */
	 {
	    fclose(fp_pert);
	    if (!(fp_pert = fopen("perturbazioni.dat", "w")))
	       return (-1);
	 }
	 break;
      }
   case 5:
      {
	 if (fp_pert != NULL)
	    fclose(fp_pert);
	 if (!(fp_pert = fopen("perturbazioni.dat", "r")))
	    if (!(fp_pert = fopen("perturbazioni.dat", "w")))
	       return (-1);
	    else
	       return (1);
	 while (fread(&perturbazione, sizeof(TIPO_PERT), 1, fp_pert))
		{
printf("sked_replay[5]: pert_snd -> tipo = %d\n",perturbazione.tipo);
	    pert_snd(id_msg_pert, 
		     perturbazione.tipo, perturbazione.indirizzo,
		     perturbazione.valore_delta, perturbazione.rateo_durata,
		     perturbazione.period, perturbazione.phase, 
		     perturbazione.meanvalue, perturbazione.wide, 
		     perturbazione.t_null_var, perturbazione.t);
printf("sked_replay[5]: dopo pert_snd\n");
		}
	 fclose(fp_pert);
	 if (!(fp_pert = fopen("perturbazioni.dat", "w")))
	    return (-1);
	 break;
      }
   case 6:
      {
      printf("\t Apro in modalita' w il file perturbazioni.dat\n");
      fp_pert = fopen("perturbazioni.dat", "w");
      fclose(fp_pert);
      break;
      }
   }
   return (1);
}

sked_raccogli_pert()
{
   PACCHETTO_NET   pacchetto_net;
   MSG_NET         messaggio_net;
   int             i, n;
   TIPO_PERT       app_pert;
   TIPO_PERT      *punt_pert;
   int             size;
   int             pert_totali;
   int             pert_da_spedire;
   int             pert_massime = 100;




   if (tipo_sked == MASTER)
   {
      /*printf("Attendo le perturbazioni dagli slave\n");*/
      for (i = 0; i < nmod; i++)
	 if (fp_ordini[i] != 0)
	 {
	    while (1)
	    {
	       if ((size = msg_rcv(id_msg_sked, &messaggio_net, sizeof(HEADER_NET) +
				   sizeof(float) * MAX_DATI_NET, (long)DATIREPLAY,
			     !IPC_NOWAIT, TIMEOUT_SKED)) == TIMEOUT_SCADUTO)
	       {
		  if (stato_sked < STATO_ERRORE)
		  {
		     sked_stato(STATO_ERRORE);
		     sked_errore();
		  }
	       }
	       /*printf("\t\t Arrivate %d perturbazioni size pacchetto= %d\n",
		    messaggio_net.header_net.lun / sizeof(TIPO_PERT), size);*/
	       if (messaggio_net.header_net.lun)
	       {
		  /* creo il buffer temporaneo */
		  punt_pert = (TIPO_PERT *) malloc(messaggio_net.header_net.lun);
		  memcpy(punt_pert, &messaggio_net.dato[0], messaggio_net.header_net.lun);
		  if (ins_file_replay(punt_pert,
		    messaggio_net.header_net.lun / sizeof(TIPO_PERT)) == -1)
		  {
		     printf("raccogli_pert: Errore scrittura perturbazioni\n");
		     suono_errore();
		  }
		  free(punt_pert);
	       } else
		  break;	/* arrivato il pacchetto con zero pert */
	    }
	 }
   } else
   {
      /* chiudo il file e lo riapro in lettura */
      /*printf("SLAVE: chiude fp_pert\n");*/
      fclose(fp_pert);
      /*printf("SLAVE: apre fp_pert in lettura \n");*/
      if (!(fp_pert = fopen("perturbazioni.dat", "r")))
      {
	 perror("open read file pert slave -->");
	 return (-1);
      }
      printf("lettura file pert\n");
      n = 0;
      while (fread(&app_pert, sizeof(TIPO_PERT), 1, fp_pert))
	 n++;

      /*printf("Invio %d perturbazioni al master\n", n);*/

      pert_totali = n;

      fseek(fp_pert, 0, 0);

      while (1)
      {
	 if (pert_totali > pert_massime)
	 {
	    pert_da_spedire = pert_massime;
	    pert_totali -= pert_massime;
	 } else
	 {
	    pert_da_spedire = pert_totali;
	    pert_totali = 0;
	 }

	 if ((pert_da_spedire * sizeof(TIPO_PERT)) !=
	     (size = fread(&pacchetto_net.dato[0], 1, sizeof(TIPO_PERT) * pert_da_spedire, fp_pert)))
	    printf(
	     "sked_raccogli_pert: errore lettura file perturbazioni.dat\n");

	 /* calcolo il numero delle perturbazioni contenute */
	 pacchetto_net.header_net.dest = (-1);
	 pacchetto_net.header_net.tasksorg = i;
	 pacchetto_net.header_net.taskdest = (-1);
	 pacchetto_net.header_net.tipo = DATIREPLAY;
	 pacchetto_net.header_net.flag = (-1);
	 pacchetto_net.header_net.lun = pert_da_spedire * sizeof(TIPO_PERT);
	 if (writen(fp_master, &pacchetto_net,
		    sizeof(HEADER_NET) + pacchetto_net.header_net.lun) < 0)
	 {
	    printf("Errore impossibile scrivere su nodo MASTER\n");
	    perror("--> ");
	    if (stato_sked < STATO_ERRORE)
	    {
	       sked_stato(STATO_ERRORE);
	       sked_errore();
	    }
	 }
	 printf("\t\t Spedite %d perturbazioni\n", pert_da_spedire);
	 if (pert_da_spedire == 0)
	    break;
      }

      /* chiudo il file e lo riapro in scrittura */
      printf("richiudo fp_pert\n");
      fclose(fp_pert);
      printf("riapro fp_pert\n");
      if (!(fp_pert = fopen("perturbazioni.dat", "w")))
	 return (-1);
   }
}


int
ins_file_replay(pert, num)
   TIPO_PERT      *pert;
   int             num;
{
   int             i, n;
   FILE           *fp_app;
   TIPO_PERT       perturbazione;


   printf("inserisco %d registrazioni nel file perturbazioni.dat\n", num);
   fflush(fp_pert);
   fclose(fp_pert);
   rename("perturbazioni.dat", "perturbazioni.old");
   if (!(fp_pert = fopen("perturbazioni.dat", "w")))
      return (-1);
   if (!(fp_app = fopen("perturbazioni.old", "r")))
      return (-1);
   i = 0;
   while (fread(&perturbazione, sizeof(TIPO_PERT), 1, fp_app))
   {
      if (perturbazione.t == -1)
	 continue;
      if (i < num)
	 while ((pert[i].t <= perturbazione.t) && (i < num))
	 {
	    if ((pert[i].t != -1) &&
		(pert[i].tipo >= MIN_PERT) &&
		(pert[i].tipo <= MAX_PERT))
	    {
	       if (fwrite(&pert[i], sizeof(TIPO_PERT), 1, fp_pert) == 0)
	       {
		  printf(
			  "ins_file_replay: Errore scrittura pert.\n");
		  suono_errore();
	       }
	    }
	    i++;
	 }
      if ((perturbazione.t != -1) &&
       (perturbazione.tipo >= MIN_PERT) && (perturbazione.tipo <= MAX_PERT))
	 if (fwrite(&perturbazione, sizeof(TIPO_PERT), 1, fp_pert) == 0)
	 {
	   printf("ins_file_replay: Errore scrittura perturbazioni\n");
	    suono_errore();
	 }
   }
   for (n = i; n < num; n++)
      if ((pert[n].t != -1) &&
	  (pert[n].tipo >= MIN_PERT) && (pert[n].tipo <= MAX_PERT))
	 if (fwrite(&pert[n], sizeof(TIPO_PERT), 1, fp_pert) == 0)
	 {
	    printf("ins_file_replay: Errore scrittura perturbazioni\n");
	    suono_errore();
	 }
   fclose(fp_app);
   fclose(fp_pert);
   if (!(fp_pert = fopen("perturbazioni.dat", "a")))
      return (-1);
   return (1);
}
#endif

#if defined REPLAY
/*
     Vecchia gestione updown
*/
sked_raccogli_updown(int *ind_updown, float *val_updown)
{
   PACCHETTO_NET   pacchetto_net;
   MSG_NET         messaggio_net;
   int             i, n, k;
   TIPO_PERT       app_pert;
   TIPO_PERT      *punt_pert;
   int             size;
   int             num;
   float           app_ind[MAX_UPDOWN];
   float           app_val[MAX_UPDOWN];


   printf("sked_raccogli_updown\n");
   if (tipo_sked == MASTER)
   {
      /*
       * calcolo il numero di quelle residenti 
       */
      for (num = 0; num < MAX_UPDOWN; num++)
	 if (ind_updown[num] == -1)
	    break;

      /*printf("Attendo le perturbazioni dagli slave\n");*/
      for (i = 0; i < nmod; i++)
	 if (fp_ordini[i] != 0)
	 {
	    if ((size = msg_rcv(id_msg_sked, &messaggio_net, sizeof(HEADER_NET) +
				sizeof(float) * MAX_DATI_NET, (long)DATIREPLAY,
			     !IPC_NOWAIT, TIMEOUT_SKED)) == TIMEOUT_SCADUTO)
	    {
	       if (stato_sked < STATO_ERRORE)
	       {
		  sked_stato(STATO_ERRORE);
		  sked_errore();
	       }
	    }
	    if (messaggio_net.header_net.lun)
	    {
	       memcpy(&app_ind[0], &messaggio_net.dato[0],
		      MAX_UPDOWN * sizeof(float));
	       memcpy(&app_val[0], &messaggio_net.dato[MAX_UPDOWN],
		      sizeof(float) * MAX_UPDOWN);
	       for (k = 0; k < MAX_UPDOWN; k++)
	       {
		  if (app_ind[k] == -1.)
		     break;
		  ind_updown[num] = app_ind[k];
		  val_updown[num] = app_val[k];
		  printf("raccogli Master %d %f\n", ind_updown[num]
			 ,val_updown[num]);
		  num++;
	       }
	    }
	 }
   } else
   {
      for (k = 0; k < MAX_UPDOWN; k++)
      {
	 pacchetto_net.dato[k] = ind_updown[k];
	 pacchetto_net.dato[k + MAX_UPDOWN] = val_updown[k];
      }
      /* calcolo il numero delle perturbazioni contenute */
      pacchetto_net.header_net.dest = (-1);
      pacchetto_net.header_net.tasksorg = i;
      pacchetto_net.header_net.taskdest = (-1);
      pacchetto_net.header_net.tipo = DATIREPLAY;
      pacchetto_net.header_net.flag = (-1);
      pacchetto_net.header_net.lun = MAX_UPDOWN * (sizeof(float) + sizeof(int));
      printf("Invio le perturbazioni al master\n");
      if (writen(fp_master, &pacchetto_net,
		 sizeof(HEADER_NET) + pacchetto_net.header_net.lun) < 0)
      {
	 printf("Errore impossibile scrivere su nodo MASTER\n");
	 perror("--> ");
	 if (stato_sked < STATO_ERRORE)
	 {
	    sked_stato(STATO_ERRORE);
	    sked_errore();
	 }
      }
   }
}
#endif
