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
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_ingressi.c	5.2\t3/8/96";
/*
   modulo sked_ingressi.c
   tipo 
   release 5.2
   data 3/8/96
   reserved @(#)sked_ingressi.c	5.2
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
# include "sim_param.h"		/* parametri generali LEGO       */
# include "sim_types.h"		/* parametri generali LEGO       */
# include "sim_ipc.h"		/* parametri generali LEGO       */
# include "comandi.h"
# include "sked.h"
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

extern S02      s02_;
extern COLLEGAMENTO collegamento[MAX_MODEL][MAX_MODEL];
extern SCAMBIO  scambio[MAX_MODEL][MAX_DT_DEC];
extern int      ricezione_dati[MAX_MODEL];
extern int      pacchetto_anticipo[MAX_MODEL][MAX_MODEL];
extern int      fp_com[MAX_MODEL];
char           *fp_app[MAX_MODEL];
int            *fp_size[MAX_MODEL];
extern int      id_msg_sked;	/* id coda messaggi  da processi read */
extern int      id_msg_pert;	/* id coda messaggi pert */
extern int      id_msg_buffer;	/* id coda tampone per messaggi da net_read 
                                   non relativi al modello trattato (usata in
                                   sked_riceve */
extern int      nmod;
HEADER_NET      header_net;	/* struttura di header per spedizione
				 * ricezione in rete */
extern PACCHETTO_NET pacchetto_net;


void            sked_ingressi();
void            sked_trasmette();
void            sked_riceve();
void            scoda_buffer();
extern          costruisci_pacchetto();
extern RtDbPuntiOggetto dbpunti;


void
sked_ingressi(tab)
   int             tab;
{
   int             i, j, k, jping, jpusc;
   int             r_mod, w_mod;
   static int      prima_volta = 1;

   /* riceve le perturbazioni */
   pert_rcv(id_msg_pert);


   for (i = 0; i < nmod; i++)
      if (fp_com[i] == 0)
      {
	 if (s02_.tabel[i].inst[tab] == 1)
	 {
	    /* riceve i dati */
	    sked_riceve(i, tab);
	    for (w_mod = 0; w_mod < nmod; w_mod++)
	       if (((scambio[i][tab].read[w_mod]) || (s02_.tabel[i].forzatura == 1)) &&
		   (i != w_mod))
	       {
		  for (k = 0; k < collegamento[i][w_mod].numero_collegamenti; k++)
		  {
		float valore;

		     jpusc = collegamento[i][w_mod].uscita[k];
		     jping = collegamento[i][w_mod].ingresso[k];
		     RtDbPCopyValue(dbpunti,jping,jpusc);
		  }
	       }
	    /*
	     * vecchia chiamata
	     * sked_perturba(i+1,NUM_VAR_TOT_MOD,s02_.model[i].dt); 
	     */
	    /*
	     * procedura spostata in sveglia task
	     * gest_area_pert(i,s02_.model[i].dt); 
	     */
	 }
      }
}


void
sked_riceve(modello, tab)
   int             modello;
   int             tab;
{
   int             r_mod, w_mod;
   MSG_NET         messaggio;
   int             k, jpusc;
   int             ret;
   int             j;

   /*
    * calcolo delle task che la task "modello" deve ricevere
    * da net_read (percio' su altra macchina) all'istante tab 
    */
   ricezione_dati[0] = 0;
   if (fp_com[modello] == 0)
      for (r_mod = 0; r_mod < nmod; r_mod++)
	 if ((scambio[modello][tab].read[r_mod]) && (fp_com[r_mod] != 0))
	    ricezione_dati[modello]++;
   /* 
    * printf("-----------------------------------------------------------------
    * \nitab = %d modello = %d   num_pacchetti= %d\n",
    * tab,modello,ricezione_dati[modello]); 
    */


/*
   Ricezione dati task altre macchine da net_read
*/
   while (ricezione_dati[modello] > 0)
   {
      /* riceve messaggi tipo DATISIM e ERRORE  */
      ret = msg_rcv(id_msg_sked, &messaggio, sizeof(HEADER_NET) +
	   sizeof(float) * MAX_COLL, (long)(-DATISIM), !IPC_NOWAIT, TIMEOUT_SKED);

      if ((messaggio.header_net.tipo == ERRORE) || (ret == TIMEOUT_SCADUTO))
      {
	 printf("\n\n\nSKED_INGRESSI: ERRORE READ da coda %d\n\n\n",
		id_msg_sked);
	 sked_stato(STATO_ERRORE);
	 sked_errore();
      }
/*    
      Test di accettazione messaggio ricevuto :
      -> se la task a cui e' destinata e' il modello trattato
      -> se relativo ad istante di tempo tab corrente
      -> se il modello all'istante tab deve leggere dalla task sorgente
*/
      if ((messaggio.header_net.taskdest == modello) &&
	  (messaggio.header_net.flag == tab) &&
	  (scambio[messaggio.header_net.taskdest][tab].
	   read[messaggio.header_net.tasksorg]))
      {

	 /*
	  * printf("%d scodato messaggio da %d tab = %d per %d\n", tab,
	  * messaggio.header_net.tasksorg,messaggio.header_net.flag,
	  * essaggio.header_net.taskdest); 
	  */
	 ricezione_dati[messaggio.header_net.taskdest]--;
	 /* trascrizione dati su shared memory  */
	 for (k = 0; k < collegamento[messaggio.header_net.taskdest]
	      [messaggio.header_net.tasksorg].numero_collegamenti; k++)
	 {
	    jpusc = collegamento[messaggio.header_net.taskdest]
	       [messaggio.header_net.tasksorg].uscita[k];
	    RtDbPPutValue(dbpunti,jpusc,messaggio.dato[k]);
	 }
      } else
      {
	 /*
	  * inserisce il messaggio nella coda di attesa 
	  */
	 msg_snd(id_msg_buffer, &messaggio,
		 sizeof(HEADER_NET) + messaggio.header_net.lun, !IPC_NOWAIT);
	 /*
	  * printf("*** %d accantonato messaggio da %d tab = %d per %d\n",
	  * tab, messaggio.header_net.tasksorg,messaggio.header_net.flag,
	  * messaggio.header_net.taskdest);  
	  */
      }
   }   /* FINE CICLO RICEZIONE DATI PER TASK modello ad ISTANTE tab */
   /*
    * Reinserisce i messaggi nella coda, in VMS sara' necessario gestire
    * questa fase in maniera diversa. 
    */
   while (msg_rcv(id_msg_buffer, &messaggio, sizeof(HEADER_NET) +
		  sizeof(float) * MAX_COLL, (long)(-DATISIM), IPC_NOWAIT, 0) > 0)
   {
      msg_snd(id_msg_sked, &messaggio,
	      sizeof(HEADER_NET) + messaggio.header_net.lun, !IPC_NOWAIT);
      /*
       * printf("*** %d ricircolato messaggio da %d tab = %d per %d\n", tab,
       * messaggio.header_net.tasksorg,messaggio.header_net.flag,
       * messaggio.header_net.taskdest); 
       */
   }
}

void
sked_trasmette(modello, tab)
   int             modello;
   int             tab;
{
   int             w_mod;

   /* 
    * printf("-----------------------------------------------------------\n"); */
   for (w_mod = 0; w_mod < nmod; w_mod++)
      if ((scambio[modello][tab].write[w_mod]) && (fp_com[w_mod] != 0))
      {
	 /*
	  * printf("trasmetto i dati della task %d tab=%d alla task %d\n",
	  * modello,tab,w_mod); 
	  */
	 costruisci_pacchetto(modello, w_mod, tab);
	 /* scrive il pacchetto nel buffer di rete  */

	 memcpy(&fp_app[w_mod][(*(fp_size[w_mod]))], &pacchetto_net,
		sizeof(HEADER_NET) + pacchetto_net.header_net.lun);

	 *fp_size[w_mod] = *fp_size[w_mod] + sizeof(HEADER_NET) +
	    pacchetto_net.header_net.lun;
      }
}


void
scoda_buffer(tab)
   int             tab;
{
   int             i;

   for (i = 0; i < nmod; i++)
      if (fp_com[i] != 0)
	 if ((*(fp_size[i])) > 0)
	 {
	    if ((writen(fp_com[i], fp_app[i], (*(fp_size[i])))) < 0)
	    {
	       printf("\n\n\n ERRORE WRITE \n\n\n");
	       perror("writen --> ");
	       sked_stato(STATO_ERRORE);
	       sked_errore();
	    }
	    *fp_size[i] = 0;
	 }
}
