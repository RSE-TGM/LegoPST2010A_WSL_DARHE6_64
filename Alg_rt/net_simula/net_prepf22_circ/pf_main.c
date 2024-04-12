/**********************************************************************
*
*       C Source:               pf_main.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Feb 28 13:36:18 2006 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: pf_main.c-13 %  (%full_filespec: pf_main.c-13:csrc:1 %)";
#endif
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include "sim_param.h"
# include "sim_types.h"
# include "comandi.h"
# include "sim_ipc.h"
# include "f22_circ.h"
# include "pf_macro.h"
#include <sys/types.h>
#include "dispatcher.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>		/* definition of OPEN_MAX */
# include <Rt/RtDbPunti.h>
# include <Rt/RtErrore.h>
#include <sqlite3.h>

RtDbPuntiOggetto dbpunti;



extern int     *iout_graf;
extern VARIABILI *variabili;
extern int      tot_variabili;
extern int      num_var_graf;
extern 
leggi_header(F22CIRC_HD *, int);

extern int      id_sh;		/* identificatore sh_var */
extern int      id_msg_prep;
extern float   *variabili_grafiche;
extern          append_mode;
extern int      variabili_registrate; /* numero delle variabili effettivamente
                                     registrate     */

/*
 * Dichiarazione files 
 */
FILE           *fpdat;		/* f22 registrazione dei dati  */
FILE           *fpda;		/* f22circ.dat file dati       */

extern int      prima_volta_wr;
extern int      file_full;
extern F22CIRC_HD header;	/* Struttura degli header       */

int   num_campioni=0;  /* numero dei campioni registrati */
int   num_var=0;       /* numero massimo variabili registrate in f22 */
int   offset=sizeof(HEADER_REGISTRAZIONI);


int _MAX_SNAP_SHOT=NOPARAM;
int _MAX_BACK_TRACK=NOPARAM;
int _MAX_CAMPIONI=NOPARAM;
int _NUM_VAR=NOPARAM;
int _MAX_PERTUR=NOPARAM;
int _SPARE_SNAP=NOPARAM;
int _PERT_CLEAR=NOPARAM;

sqlite3 *db;

int  scrivi_f22_ascii=0;

int main(int argc, char **argv)
{
int      i, ret;	/* interi spare */
float    tempo;	        /* variabile tempo di simulazione */
MSG_AUS  messaggio;
int      ore,minuti,secondi,giorno,mese,anno;
int      errpf22;

  /* redirezione output  e stampa versione */
  /*
   * testata("net_prepf22",SccsID); 
   */

/* Lettura parametri */
   for(i=1;i<argc-1;i++)
        {
        if(strcmp(argv[i],ARGV_N_CAMP_CR)==0)
                num_campioni = atoi(argv[i+1]);
        if(strcmp(argv[i],ARGV_N_VAR_CR)==0)
                num_var = atoi(argv[i+1]);
        }

  if( (num_campioni== 0)||(num_var==0) )
     exit(fprintf(stderr,"Errore nei %d parametri di net_prepf22_circ\n",
                  argc));
  _MAX_CAMPIONI = num_campioni;
  _NUM_VAR      = num_var;
  errpf22 = ControlParam(NET_PREPF22_CIRC);
  if( errpf22>0 )
      exit(fprintf(stderr,"Errore parametri startup di net_prepf22\n"));
  pf_prolog();	         /* operazioni iniziali  generiche          */
  pf_selcirc();	         /* operazioni iniziali di selezione variabili  */
/* mauric */
  fclose(fpda);

// Verifica se la variabile d'ambiente F22_ASCII è = YES per attivare la scrittura file accessorio
   if (getenv("F22_ASCII")!=NULL)
   {
        if (!strcmp(getenv("F22_ASCII"),"YES"))
        {
	   scrivi_f22_ascii=1;
        }
   }


  /* manda allo sked il messaggio di esecuzione dello start-up */
  messaggio.mtype = PREP_F22 + OFFSET_AUS;
  msg_snd(id_msg_prep, &messaggio, sizeof(TIPO_AUS), !IPC_NOWAIT);

  /* attende messaggio da sked */
  msg_rcv(id_msg_prep, &messaggio, sizeof(MSG_AUS), (long)PREP_F22,
	  !IPC_NOWAIT, TIMEOUT_INF);

  while (messaggio.ausiliario.comando != STOP_AUS)	/* ciclo              */
  {
    RtDbPGetTime(dbpunti,&tempo);
    fpda = (FILE *) fopen("f22circ.dat", "r+");
    pf_wrif22circ();
    fclose(fpda);
    msg_rcv(id_msg_prep, &messaggio, sizeof(MSG_AUS), (long)PREP_F22,
	    !IPC_NOWAIT, TIMEOUT_INF);
    if (messaggio.ausiliario.comando == RELOAD_AUS)
    {
      printf("net_prepf22_circ: ricevuto mess. RELOAD\n");
      ora(&ore,&minuti,&secondi);
      header.ore = ore;
      header.minuti = minuti;
      header.secondi = secondi;
      data(&giorno,&mese,&anno);
      header.giorno = giorno;
      header.mese = mese;
      header.anno = anno;

      fpda = (FILE *) fopen("f22circ.dat", "r+");
      sposta(fpda, offset);
      scrivi(&header, sizeof(F22CIRC_HD), 1, fpda);
      risel_indici();
      fclose(fpda);

    }
    if (messaggio.ausiliario.comando == RESET_AUS)
    {
      printf("Ricevuto comando reset\n");
      prima_volta_wr = 1;
      file_full = 0;
      append_mode = 0;
      header.p_iniz = 0;
      header.p_fine = 0;
      ora(&ore,&minuti,&secondi);
      header.ore = ore;
      header.minuti = minuti;
      header.secondi = secondi;
      data(&giorno,&mese,&anno);
      header.giorno = giorno;
      header.mese = mese;
      header.anno = anno;
    fpda = (FILE *) fopen("f22circ.dat", "r+");
      sposta(fpda, offset);
      scrivi(&header, sizeof(F22CIRC_HD), 1, fpda);
    fclose(fpda);
    if(variabili_grafiche != NULL)
      free(variabili_grafiche);

      /* fine RESET_AUS   */
    }
  }
  if (variabili_grafiche != NULL)
  {
    free(variabili_grafiche);
  }
  /* Chiusura file */
  fclose(fpdat);

  /* Sgancio dalla shared memory sh_var */
  distruggi_var(id_sh);

  /* Risposta allo sked */
  messaggio.mtype = PREP_F22 + OFFSET_AUS;
  msg_snd(id_msg_prep, &messaggio, sizeof(TIPO_AUS), !IPC_NOWAIT);

  /* Sgancio code messaggi */
  msg_close_fam();
  return(0);
}

/*
 * Sostituisce alle vecchie le nuove variabili per la grafica. 
 * Caso particolare : num_var < num_var_graf (new_var)  ====>
 *                    - in caso di aggiunta non aggiunge nulla,
 *                    - in caso di eliminazione al posto della var eliminata
 *                      aggiunge la successiva selezionata.
 */
int risel_indici()
{
int          ret;
int          i, j, k;
int          new_num;
F22CIRC_VAR *descr = NULL;
int         *posizione = NULL;
float       *val = NULL;
int          inserimenti;
int          addr;

  /* Controllo sul nuovo numero di variabili */
  new_num = 0;
  for (i = 0; i < tot_variabili; i++)
    if (variabili[i].typ == GRAF_SEL)
    {
      new_num++;
    }
    printf("tot_variabili=%d num_var_graf=%d new_num=%d  variabili_regis=%d\n",
            tot_variabili,num_var_graf,new_num,variabili_registrate); 
  
   TipoDiRiselezione(num_var, new_num, num_var_graf);

  /* Alloco il vettore delle posizioni delle variabili sostituite */
  posizione = (int *) calloc(variabili_registrate, sizeof(int));

  /* Alloco il vettore dei valori da sostituire per ogni campione */
  val = (float *) calloc(variabili_registrate, sizeof(float));

  /* Alloco la struttura descrittiva delle variabili */
  descr = (F22CIRC_VAR *) calloc(variabili_registrate, sizeof(F22CIRC_VAR));

/* 
  Si liberano le locazioni occupate da variabili non piu' selezionate .
  Si hanno variabili_registrate iout_graf e tot_variabili variabili.
*/
  for (i = 0; i < variabili_registrate; i++)
  {
    for (j = 0; j < tot_variabili; j++)
      if ((iout_graf[i] == variabili[j].addr)
	  && (variabili[j].typ == GRAF_SEL))
      {
	break;
      }
    if (j == tot_variabili)
    {
      strcpy(descr[i].nomevar, "--none--");
      strcpy(descr[i].descvar, "--- not available ---");
      if (iout_graf[i] != -1)
      {
        /*
	 * printf("Eliminata la variabile di indice iout_graf[i=%d]=%d\n",
         *         i,iout_graf[i]); 
         */

	iout_graf[i] = -1;
      }
    }
  }

/* 
  Si inseriscono le nuove variabili. Carico nome e descrizione 
*/
  inserimenti = 0;
  for (j = 0; j < tot_variabili; j++)
  {
    if (variabili[j].typ == GRAF_SEL)
    {
/*
 *    printf(" j=%d VARIABILE GRAFICA addr=%d (%s)\n",
 *           j,variabili[j].addr,variabili[j].nome);
 */
      for (i = 0; i < variabili_registrate; i++)
      {
/*      Se e' gia' tra le iout devo solo caricare il nome */
	if (iout_graf[i] == variabili[j].addr)
	{
/*
 *        printf("\t Inserimento [%s] di iout_graf[pos=%d]=%d\n",
 *                variabili[j].nome,i,iout_graf[i]);
 */
	  strcpy(descr[i].nomevar, variabili[j].nome);
	  strncpy(descr[i].descvar, variabili[j].descr, 70);
	  break;
	}
/*
        La variabile da inserire non e' stata trovata, si cerca percio'
        una posizione libera per inserirla.
*/
	if (i == variabili_registrate - 1)
	{
	  for (k = 0; k < variabili_registrate; k++)
	    if (iout_graf[k] == -1)
	    {
/*
 *             printf("\t Nuovo inserimento addr=%d nome=[%s] posizione=%d\n",
 *                    variabili[j].addr,variabili[j].nome,k);
 */
	      iout_graf[k] = variabili[j].addr;
	      strcpy(descr[k].nomevar, variabili[j].nome);
	      strncpy(descr[k].descvar, variabili[j].descr, 70);
	      posizione[inserimenti] = k;
	      addr = iout_graf[k];
	      val[inserimenti]  = RtDbPGetValueD(dbpunti,addr);

	      inserimenti++;
	      break;
	    }
	}
      }
    }
  }

/* 
  Inserisco i campi delle locazioni libere 
  for (i = new_num; i < variabili_registrate; i++) 11-12-96
*/
  for (i = 0; i < variabili_registrate; i++)
    {
    if ( iout_graf[i]!=-1 )
       continue;
    strcpy(descr[i].nomevar, "libera  ");
    strcpy(descr[i].descvar, "   ---   ");
    }

  /* Riscrittura delle descrizioni delle variabili disponibili */
  sposta(fpda, sizeof(F22CIRC_HD)+offset);
  scrivi(descr, sizeof(F22CIRC_VAR), variabili_registrate, fpda);
  fluscia(fpda);

  /*
   * for(i=0;i<num_var_graf+5;i++) printf("nome=%s|  descr=%s|\n",
   * descr[i].nomevar,descr[i].descvar); 
   */

  /* printf("inserimenti=%d\n",inserimenti); */

  if (descr != NULL)
    free(descr);

  /* Si eliminano dal file i valori precedenti delle variabili eliminate */
  if (inserimenti > 0)
    pf_back(posizione, inserimenti, val);
  else
    fprintf(stderr, "Non e' stata inserita nessuna nuova variabile\n");

  if (val != NULL)
    free(val);
  if (posizione != NULL)
    free(posizione);

  /*
   * aggiorna il valore di num_var_graf e la locazione in shared-memory 
   */
  num_var_graf = new_num;
  if ( num_var_graf > num_var )
     {
     RtDbPPutNumCr(dbpunti,num_var);
     printf("NUM_VAR_GRAF=%d\n", num_var);
     }
  else
     {
     RtDbPPutNumCr(dbpunti,num_var_graf);
     printf("NUM_VAR_GRAF=%d\n", new_num);
     }
}


/*
 * Propagazione del primo valore delle variabile nei valori gia' salvati su
 * file dati. Viene letto tutto il file dei dati e assegnato il valore da
 * sostituire solo per i campioni relativi a tempi precedenti. 
 */
int pf_back(int *pos, int nins, float *valore)
{
  int             i, k, j;
  int             ii;
  int             addr;
  int             ret;
  F22CIRC_HD      hdr;
  int             ret1, ret2, ret3, ret4;
  float           tempo_attuale;
  float          *variabili_gr;
  int             primo_zero = 0;
  int             opda;
  int             pos1, pos2, pos3;
  int             off,offheader;
  int             num_camp_iniz; /* numero campioni da inizializzare */




  /* 1. Lettura campione */
  ret = leggi_header(&hdr, sizeof(F22CIRC_HD));
  if (ret <= 0)
  {
    fprintf(stderr, "Errore lettura header\n");
    return (-1);
  }
  variabili_gr = (float *) calloc(variabili_registrate + 1, sizeof(float));
  fclose(fpda);
  fpda = fopen("f22circ.dat", "r+");

  /* Scrittura valori corretti in tutti i campioni */
  offheader = sizeof(HEADER_REGISTRAZIONI) + sizeof(F22CIRC_HD) +
              sizeof(F22CIRC_VAR) * variabili_registrate;

if(hdr.p_iniz <= hdr.p_fine)
	num_camp_iniz=hdr.p_fine;
else
	num_camp_iniz=num_campioni;
 i = 0;
 for (j = 0; j < num_camp_iniz; j++)
  {
    for (ii = 0; ii < nins; ii++)
    {
      ret1 = sposta(fpda, offheader + i * (variabili_registrate + 1) *
                          sizeof(float));
      off = (pos[ii] + 1) * sizeof(float);
      ret2 = sposta_rel(fpda, off, 1);
      ret3 = scrivi(&valore[ii], sizeof(float), 1, fpda);
      fluscia(fpda);
      if ((ret1 != 0) || (ret2 != 0) || (ret3 != 1))
        error_conditions(ret1, ret2, ret3, j, i);
    }
    i++;
    ret4 = fseek(fpda, offheader + i * (variabili_registrate + 1) *
                       sizeof(float), 0);
    if (ret4 != 0)
      fprintf(stderr, "Errore posizionamento inizio campione\n");
  }

  fclose(fpda);

  /* Provo la lettura per controllo */
  /*
   * fpda = fopen("f22circ.dat","r"); rewind(fpda);
   * sposta(fpda, offheader);
   * for(i=0;i<num_campioni;i++) { ret =
   * fread(variabili_gr,sizeof(float),hdr.num_var_graf+1,fpda);
   * printf("tempo=%f (ret=%d)  \n", variabili_gr[0],ret); printf("      ");
   * for(ii=0;ii<num_var_graf;ii++) printf(" %f  ", variabili_gr[ii+1]); }
   * fclose(fpda); 
   */

  fpda = fopen("f22circ.dat", "r+");
  if (hdr.p_fine == num_campioni)
    off = offheader;
  else
    off = offheader + hdr.p_fine * (variabili_registrate + 1) * sizeof(float);

  ret1 = fseek(fpda, off, 0);

  if(variabili_gr)
     free(variabili_gr);
  return (1);
}


/*
 * Condizioni di errore 
 */
int error_conditions(int r1, int r2, int r3, int r4, int camp, int ins)
{
  int             i;

  fprintf(stderr, "Errore inserimento num. %d del campione %d\n", ins, camp);
  if (r1 != 0)
    fprintf(stderr, "Errore su posizionamento inizio campione.\n");
  if (r2 != 0)
    fprintf(stderr, "Errore posizionamento su float.\n");
  if (r3 != 1)
    fprintf(stderr, "Errore nella scrittura.\n");
}




int TipoDiRiselezione(int num_var, int new_num, int num_var_graf)
{
int i;


     if ( new_num == num_var_graf )
          fprintf(stderr,"Non cambia il totale di variabili grafiche\n");
     if( num_var_graf <= num_var )
         {
         if ( new_num < num_var_graf )
            fprintf(stderr,"Elimina %d variabili dalle attuali %d\n",
                       num_var_graf-new_num,num_var_graf);
         else
            if ( new_num <= num_var )
               fprintf(stderr,"Inserisce %d variabili oltre alle attuali %d\n",
                        new_num-num_var_graf,num_var_graf);
            else
               fprintf(stderr,
       "Non supera il massimo numero (%d) di variabili: %d inserimenti\n",
                     num_var,num_var-num_var_graf);
         }
     else
         {
         if ( new_num < num_var )
            fprintf(stderr,"Elimina %d variabili dall'attuale massimo di %d\n",
                       num_var-new_num,num_var);
         else
            fprintf(stderr,
                    "Non modificato il totale (%d) delle variabili grafiche\n",
                     num_var);
         }
}

