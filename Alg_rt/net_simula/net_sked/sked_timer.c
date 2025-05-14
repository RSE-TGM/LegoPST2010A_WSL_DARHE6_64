/**********************************************************************
*
*       C Source:               sked_timer.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Tue Dec 15 18:12:41 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_timer.c-1.2.1 %  (%full_filespec: sked_timer.c-1.2.1:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sked_timer.c	5.1\t11/7/95";
/*
   modulo sked_timer.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_timer.c	5.1
*/
# include <stdio.h>
# include <errno.h>
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>
# include "sim_param.h"
# include "sim_types.h"
# include "comandi.h"
# include "sked.h"
# include "sked_fun.h"

extern double   tempo_sim;	/* tempo della simulazione */
extern double   tempo_reale;	/* tempo reale   */
extern double   tempo_iniziale;	/* tempo iniziale della simulazione */
extern double   tempo_freeze;	/* tempo per conteggio freeze  */
extern double   ritardo_sim;	/* ritardo accumulato */
extern float    fattore_step;	/* fattore moltiplicativo del passo di tempo                           */
extern float    velocita;
extern int      nmod;
extern int      nrip;
extern int      stato_sked;

extern int      tipo_sked;

extern RtDbPuntiOggetto dbpunti;


double          gettim();

void sked_timer(int agg_dbpunti)
{
   double          tempo_impiegato;
   int             nnrip;
   static unsigned int tempo_attesa;
   float app_tempo;


   /* legge il fattore moltiplicativo del passo di tempo */
   RtDbPGetStepScaling(dbpunti,&fattore_step);


   if (tipo_sked == MASTER)
   {

      nnrip = 1;

      tempo_sim = tempo_sim + ((float) nnrip) * 100.0 * fattore_step;
      /*
       * se la velocita e' minore di 0 la schedulazione procede alla velocita
       * massima 
       */
      if (velocita > 0)
      {

	 /* ritardo accumulato */
	 tempo_impiegato = gettim() - tempo_iniziale;
	 if ((stato_sked != STATO_RUN) && (stato_sked != STATO_REPLAY))
	    tempo_impiegato = ((float) nnrip / (velocita)) * 100 * fattore_step;


	 ritardo_sim = tempo_impiegato - ((float) nnrip / (velocita)) * 100 * fattore_step + (ritardo_sim);
	 /* printf("tempo impiegato =%f\n",tempo_impiegato); */

	 /* se il ritardo e' negativo attende */
	 if (ritardo_sim < 0)
	 {
	    tempo_attesa = (unsigned int) (ritardo_sim * (-1));
	    sospendi(tempo_attesa);
	    ritardo_sim = 0;
	 }
      }
/*
   Se il flag 'agg_dbpunti' e' <> 0 significa che il tempo di simulazione
   e' gia' stato caricato in dbpunti prima della chiamata a sked_pf22().
*/
      if(agg_dbpunti == 0)
         RtDbPPutTime(dbpunti,(float) (tempo_sim / 1000));

      if (ritardo_sim >= 0)
	RtDbPPutDelay(dbpunti,(ritardo_sim / 1000.0));
      else
	RtDbPPutDelay(dbpunti,0.0);

      /* legge la velocita' di simulazione */
      RtDbPGetTimeScaling(dbpunti,&velocita);


      tempo_iniziale = gettim();
   } else
   {
      RtDbPGetTime(dbpunti,&app_tempo);
      app_tempo = app_tempo + 0.1 * fattore_step;
      RtDbPPutTime(dbpunti,app_tempo);
   }
}
