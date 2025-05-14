/**********************************************************************
*
*       C Source:               sked_tempo_iniziale.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 14:28:47 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_tempo_iniziale.c-7 %  (%full_filespec: sked_tempo_iniziale.c-7:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_tempo_iniziale.c	5.1\t11/7/95";
/*
   modulo sked_tempo_iniziale.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_tempo_iniziale.c	5.1
*/
#include <stdio.h>
#if defined UNIX
#include <sys/types.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#endif
#if defined VMS
#include <types.h>
#include <stat.h>
#include <unixio.h>
#include <file.h>
#endif

#include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "sked.h"
# include "comandi.h"
# include "dispatcher.h"
# include "f22_circ.h"
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

#if defined BACKTRACK
extern BKTAB *backtrack;  /* area shm per tabella dei backtrack */
#endif

extern int size_area_dati;     /* size in byte area dati di tutte le task */
extern double   tempo_sim;	/* tempo della simulazione */
extern double   tempo_reale;	/* tempo reale   */
extern double   tempo_iniziale;	/* tempo iniziale della simulazione */
extern double   tempo_freeze;	/* tempo per conteggio freeze  */
extern double   ritardo_sim;	/* ritardo accumulato */
extern float    velocita;
extern float    passo_grafica;	/* passo registrazione grafica */
extern float    passo_legograf;	/* passo aggiornamento legograf su macchina
				 * MASTER   */

extern STATO_CR stato_cr;

extern RtDbPuntiOggetto dbpunti;
extern RtDbPuntiOggetto dbpunti_ext;

double          gettim();

extern int _MAX_SNAP_SHOT;
extern int _MAX_BACK_TRACK;
extern int _MAX_CAMPIONI;
extern int _NUM_VAR;
extern int _MAX_PERTUR;
extern int _SPARE_SNAP;

int sked_tempo_iniziale()
{
   FILE           *fp;
   float           tempo_app;
   float           tempo_f22;
   float           tempo_bktk;
   int             num;
   int             posizione, offset;
   float           tempo_append;
   float           zero = 0;
   int app_passo_grafica;
   int app_passo_legograf;


   /* Assegnamento valori iniziali */
   app_passo_grafica=passo_grafica;
   app_passo_legograf=passo_legograf;

   RtDbPPutTime(dbpunti,0.0);
   RtDbPPutDelay(dbpunti,0.0);
   RtDbPPutTimeScaling(dbpunti,velocita);
   RtDbPPutStepCr(dbpunti,app_passo_grafica);
   RtDbPPutStepDb(dbpunti,app_passo_legograf);


#if defined PIACENZA
   /*
    * Legge: tempo di simulazione 
    */
   tempo_sim = 0;
   tempo_f22 = 0;
   tempo_bktk = 0;
#if defined F22_APPEND
   /* Legge se esiste il file circolare oppure f22 */
   tempo_f22 = f22_last_t("f22circ");

// printf("tempo del file f22circ = %f\n",tempo_f22);
#endif
#if defined BACKTRACK
   if (stato_cr.last_bktk_save != 0)
      {
//      printf("Ultimo backtrack salvato = %d\n",stato_cr.last_bktk_save);
      posizione = stato_cr.last_bktk_save;
#if defined SNAP_PIAC
      offset = sizeof(HEADER_REGISTRAZIONI)                                   + 
               _MAX_BACK_TRACK * sizeof(BKTAB)                                +
               (posizione - 1) * 
                                ( size_area_dati + sizeof(float)         +
#if defined MFFR
                                  sizeof(SNAP_SKED)                      + 
#endif
                                  DIM_SNAP_AUS                           +
                                  _SPARE_SNAP*AREA_SPARE  * sizeof(char) +
                                  2*_MAX_PERTUR * sizeof(TIPO_PERT)        )  +
               size_area_dati;
#else
      offset = _MAX_BACK_TRACK * sizeof(BKTAB)              +
               (backtrack[posizione - 1].pos - 1) * 
                (size_area_dati+  sizeof(float)            +
               sizeof(SNAP_SKED) + DIM_SNAP_AUS            +
               _MAX_UPDOWN * (sizeof(float) + sizeof(int))) +
               size_area_dati;
#endif
      fp = fopen("backtrack.dat", "r");
      fseek(fp, offset, 0);
      fread(&tempo_bktk, sizeof(float), 1, fp);
      fclose(fp);
//      printf("\t    tempo_bktk=%f\n", tempo_bktk);
      }
   if (tempo_bktk > tempo_f22)
      tempo_sim = tempo_bktk * 1000;
   else
      tempo_sim = tempo_f22 * 1000;
#else
   tempo_sim = tempo_f22 * 1000;
#endif

   RtDbPPutTime(dbpunti,(float)(tempo_sim / 1000));
   RtDbPPutTime(dbpunti_ext,(float)(tempo_sim / 1000));

   tempo_iniziale = gettim();
   tempo_reale = tempo_iniziale;
   return(1);
#endif
#if defined F22_APPEND && !defined PIACENZA
   /* Legge se esiste il file circolare oppure f22 */
   tempo_sim = tempo_sim_append_circ();
   if (tempo_sim == -1)
      tempo_sim = tempo_sim_append();
   RtDbPPutTime(dbpunti,tempo_sim);
   RtDbPPutTime(dbpunti_ext,tempo_sim);
   tempo_sim = tempo_sim * 1000;

   tempo_iniziale = gettim();
   tempo_reale = tempo_iniziale;
   return (1);
#endif

   tempo_iniziale = gettim();
   tempo_reale = tempo_iniziale;
}
