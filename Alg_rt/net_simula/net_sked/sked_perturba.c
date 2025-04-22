/**********************************************************************
*
*       C Source:               sked_perturba.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Thu Feb  6 17:05:40 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sked_perturba.c-9 %  (%full_filespec: sked_perturba.c-9:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "%W%\t%G%";
/*
   modulo %M%
   tipo %Y%
   release %I%  (5.4 in edit)
   data %G%
   reserved %W%
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sim_param.h"
#include "sim_types.h"
# include "sked.h"
# include "comandi.h"
#include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

extern RtDbPuntiOggetto dbpunti;
extern RtDbPuntiOggetto dbpunti_ext;

extern int      stato_sked;

extern int      tipo_sked;
extern int    fp_com[MAX_MODEL];
extern float    fattore_step;	/* fattore moltiplicativo passo di tempo */
int NextIns;

float funz_periodic();
float funz_whitenoise();
int ControlPert (TIPO_PERT *p, int , int , float , float *, 
                 float , float , float , float , float , float , float);
int modi_periodic(TIPO_PERT *p, int , int , float ,
                  float *, float , float , float,
                  float, float, float , float );
int agg_filepert(TIPO_PERT , float , float , FILE *);
int ResettaMalf(float );


#if defined SAVEPERT
FILE           *fp_pert;
#endif


#if defined VMS
#define M_PI  3.14159265358979323846
#endif

extern int    _MAX_SNAP_SHOT;
extern int    _MAX_BACK_TRACK;
extern int    _MAX_CAMPIONI;
extern int    _NUM_VAR;
extern int    _MAX_PERTUR;
extern int    _SPARE_SNAP;


/*
    Si si usa in fase di snapshot (non mette in memoria il nuovo valore).
    Chiamata da save_snap_piac.
    1) Perturbazioni attive:
       Nega il valore, elimina la perturbazione dal vettore delle
       perturbazioni passato.
    1) Perturbazioni in attesa:
       Elimina semplicemente la pert senza negare la variabile.
*/
int remove_updown_file_snap(float *punt, TIPO_PERT *pert, TIPO_PERT *pert_att)
{
int             k;
  

   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert[k].tipo == PERT_UP)
         {
	 punt[pert[k].indirizzo] =
	    nega(punt[pert[k].indirizzo]);
         printf("\t remove_updown_file_snap nega-elimina la pert=%d tipo=%d ind=%d\n",
                k,pert_att[k].tipo,pert[k].indirizzo);
         pert[k].tipo = -1;
         }

   for (k = 0; k < _MAX_PERTUR; k++)
      if (     
          (pert_att[k].tipo == PERT_UP)   ||
          (pert_att[k].tipo == PERT_DOWN)
         )
         {
         printf("\t remove_updown_file_snap elimina la pert_att=%d tipo=%d ind=%d\n",
                k,pert_att[k].tipo,pert_att[k].indirizzo);
         pert_att[k].tipo = -1;
         }
     
}

/*
    Nega il valore, non elimina la perturbazione, non mette in memoria
    il nuovo valore tanto si usa in fase di snapshot.
*/
remove_updown(punt)
   float          *punt;
{
   int             k;
   TIPO_PERT *pert;
  
   if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		return;

   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert[k].tipo == PERT_UP)
            {
	 punt[pert[k].indirizzo] =
	    nega(punt[pert[k].indirizzo]);
	    printf("\t remove_updown UP n.%d indirizzo=%d e nego\n",
                       k,pert[k].indirizzo);
            }
}



/*
    Elimina gli updown dalle perturbazioni e nega il relativo valore
    della variabile che era sotttoposta alla perturbazione PERT_UP a
    quell'istante.
    Nega il valore, non elimina la perturbazione, non mette in memoria
    il nuovo valore tanto si usa in fase di snapshot.
    Chiamata da sked_banco (se non e' entrato in replay).
*/
int rm_updown_from_pert()
{
int        k;
TIPO_PERT *pert,*pert_att;
float valore;

   if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		return;

   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert[k].tipo == PERT_UP)
         {
         valore = nega(RtDbPGetValueD(dbpunti,pert[k].indirizzo));
         RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
         RtDbPPutValue(dbpunti_ext,pert[k].indirizzo,valore);
	 pert[k].tipo = -1;
	 printf("\t rm_updown_from_pert UP n.%d indirizzo=%d\n",
                    k,pert[k].indirizzo);
         }

   if((pert_att=RtDbPGetPuntPert(dbpunti))==NULL)
		return;

   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert_att[k].tipo == PERT_UP)
         {
	 pert_att[k].tipo = -1;
	 printf("\t rm_updown_from_pert UP n.%d indirizzo=%d in attesa\n",
                    k,pert_att[k].indirizzo);
         }
}




  
/*
   Vecchia gestione updown
*/
remove_backtrack_updown(int *ind_updown, float *val_updown)
{
   int             i;
   float valore;

   for (i = 0; i < MAX_UPDOWN; i++)
   {
      if (ind_updown[i] == -1)
	 break;

      valore = nega(val_updown[i]);
      printf("\t remove_backtrack_updown  n.%d nego a indirizzo=%d\n",
                 i,ind_updown[i]);
      RtDbPPutValue(dbpunti,ind_updown[i],valore);
      RtDbPPutValue(dbpunti_ext,ind_updown[i],valore);
   }
}



/*
    Dalla shared memory della macchina si leggono le pereturbazioni
    attive sulle task residenti. Identificati gli updown si caricano
    i vettori con gli indirizzi e i relativi valori della variabile.
*/
/*
    Vecchia gestione updown.
*/
int prepara_lista_updown(int *ind, float *val)
{
   int             i, k;
   TIPO_PERT *pert;
  
   if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		return;

   printf("prepara_lista_updown\n");
   for (k = 0; k < MAX_UPDOWN; k++)
   {
      ind[k] = -1;
      val[k] = 0.;
   }

   i = 0;
   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert[k].tipo == PERT_UP)
      {
	 ind[i] = pert[k].indirizzo;
	 val[i] = RtDbPGetValueD(dbpunti,pert[k].indirizzo);
	 printf("trovata PERT_UP addr %d val %f\n", ind[i], val[i]);
	 ++i;
      }
}


/*
    IMPORTANTE: l'area delle perturbazioni in SHM per ciascuna macchina
               e' relativa alle sole perturbazioni delle task residenti.
               Ad esempio perturbazioni possono essere inviate dal banco
               agli slave e nel caso che una perturbazione giunga al master
               per uno slave, a questo e' spedita senza che sia memorizzata
               nell'area del master. 
               Quindi dovranno essere le singole macchine ad eliminare
               gli updown.
remove_updown_slave()
    In un pacchetto di dati passato (corrispondente ai dati di una
    task residente in un macchina slave) nega il valore della relativa 
    variabile nel pacchetto individuandone l'indirizzo relativo al pacchetto
    in funzione del numero del modello.
    Non elimina invece gli updown in corso. 
*/
remove_updown_slave(punt, modello)
   float          *punt;
   int             modello;
{
   int             k;
   int             addr;
   TIPO_PERT *pert;
  
   if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		return;

   printf("remove updown slave\n");
   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert[k].tipo == PERT_UP)
      {
/*       Indirizzo relativo al puntatore passato */
	 addr = pert[k].indirizzo - RtDbPInizioModelli(dbpunti,modello);
	 printf("trovata PERT_UP slave ind %d addr %d\n",
		pert[k].indirizzo, addr);

	 if (addr >= 0) 
	 {
	    printf("modello %d addr rel. %d : rimozione pert_up\n",
		   modello, addr);
	    printf("prima %f\n", *(punt + addr));
	    *(punt + addr) = nega(*(punt + addr));
	    printf("dopo  %f\n", *(punt + addr));
	 }
      }
}


/* 
    Chiamata da tutti gli sked dopo una fase di LOAD (snap o bktk), si
    occupa di eliminare le perturbazioni che non sono dei modelli residenti 
    sulla macchina. E' chiamata per lo stesso motivo dopo l'effettuazione
    di un SAVE (snap o bktk) dallo sked MASTER. 
*/
int rm_pert_remote()
{
TIPO_PERT *pert[2];
int i,h,mod;

    if( (pert[0]=RtDbPGetPuntPert(dbpunti))==NULL)
       {
       printf("\t InDisponibilita' delle pert\n");
       return(-1);
       }
    if( (pert[1]=RtDbPGetPuntPertAtt(dbpunti))==NULL)
       {
       printf("\t InDisponibilita' delle pert in attesa\n");
       return(-1);
       }

    for(h=0;h<2;h++)
       for(i=0;i<_MAX_PERTUR;i++)
          {
          mod= RtDbPGetModelFromInd(dbpunti, pert[h][i].indirizzo);
          if( mod== -1)
            printf("ERRORE pert_locale[h=%d][i=%d].indirizzo=%d\n",
                    h,i,pert[h][i].indirizzo);
          if( (fp_com[mod]!=0) && (pert[h][i].tipo!=-1) )
             {
             printf("Elimino pert remota %d (in attesa=%d) tipo=%2d ind=%2d\n",
                    i, h, pert[h][i].tipo,pert[h][i].indirizzo);
             pert[h][i].tipo = -1;
             }
          }
    return(0);
}

remove_pert(pos)
   int             pos;
{
   TIPO_PERT *pert_att;
  
   if((pert_att=RtDbPGetPuntPertAtt(dbpunti))==NULL)
		return;

   printf("remove_pert in attesa (%d) (tipo[pos-1]=%d)\n", 
           pos,pert_att[pos - 1].tipo);
   if (pert_att[pos - 1].tipo == -1)
      return (-1);
   else
   {
      pert_att[pos - 1].tipo = -1;
      return (1);
   }
}


init_area_pert()
{
   int             k;
   extern int      id_msg_pert;
   TIPO_PERT *pert, *pert_att;
  
   if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		return;
   if((pert_att=RtDbPGetPuntPertAtt(dbpunti))==NULL)
		return;

   pert_rcv_null(id_msg_pert);

   for (k = 0; k < _MAX_PERTUR; k++)
   {
      pert[k].tipo = -1;
      pert[k].posizione = k + 1;
   }
   for (k = 0; k < _MAX_PERTUR; k++)
   {
      pert_att[k].tipo = -1;
      pert_att[k].posizione = k + 1;
   }
}

int ins_area_pert_att(tipo, indirizzo, valore_delta, rateo_durata,
		  period, phase, meanvalue, wide, t_null_var, t)
   int      tipo, indirizzo;
   float    valore_delta, rateo_durata, period, phase, meanvalue, 
            wide, t_null_var, t;
{
   int             k;
   float tempo;
   TIPO_PERT *pert_att;
  
   if((pert_att=RtDbPGetPuntPertAtt(dbpunti))==NULL)
		return;
/*
    fprintf(stderr,"\t SKED: tp=%d ind=%d val=%f rt=%f t=%f\n",
      tipo,indirizzo,valore_delta,rateo_durata,t); 
*/
   /*
    * cerca una posizione libera 
    */
   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert_att[k].tipo == -1)
	 break;
   if (k == _MAX_PERTUR)
   {
      fprintf(stderr,"Raggiunto massimo numero di perturbazioni in attesa\n");
      return (-1);
   }
   /*
    * gestisce il tempo della perturbazione 
    * t indichera' (se positivo) il tempo da trascorrere per attivare
    * la perturbazione.
    */
   RtDbPGetTime(dbpunti,&tempo);
   if (t > 0)
   {
      t = t - tempo;
      if (t < 0)
	 t = 0;
   }
   if (t < 0)
      t = (-1) * t;

   printf("Perturbazione inserita in attesa nello slot %d (t=%f) tempo=%f\n",
           k,t,tempo);

/*
   Se si tratta di una perturbazione di tipo PERT_TO viene ora memorizzato
   ma la differenza rispetto all'istante di invio (il deltat) per avere una 
   gestione senza l'esigenza di traslazioni temporali nel caso di caricamento
   di tale perturbazione da un file delle registrazioni attive e per avere in
   rateo sempre valori omogenei.
*/
   if(tipo==PERT_TO)
      {
      if ( rateo_durata > 0 )
         {
         if (tempo >= rateo_durata)
            rateo_durata = -0.0000001;
         else
            rateo_durata = rateo_durata - tempo - t;
         rateo_durata = ((int) (rateo_durata / 0.1)) * 0.1;
         }
      rateo_durata = (float) fabs((double) rateo_durata);
      }

/* Inserisce la perturbazione nella posizione k */
   pert_att[k].tipo         = tipo;
   pert_att[k].indirizzo    = indirizzo;
   pert_att[k].esaminata    = 0;
   pert_att[k].valore_delta = valore_delta;
   pert_att[k].rateo_durata = rateo_durata;
   pert_att[k].period       = period;
   pert_att[k].phase        = phase;
   pert_att[k].meanvalue    = meanvalue;
   pert_att[k].wide         = wide;
   pert_att[k].t_null_var   = t_null_var;
   pert_att[k].t            = t;
   return (k);
}

/*
    -1 : non inserisce, poi inserira' tra quelle in attesa
*/
ins_area_pert(tipo, indirizzo, valore_delta, rateo_durata,
	      period, phase, meanvalue, wide, t_null_var, t, dt)
   int     tipo, indirizzo;
   float   valore_delta, rateo_durata, period, phase, meanvalue, 
           wide, t_null_var, t, dt;
{
   TIPO_PERT       app_pert;
   int             k;
   float           app_rateo;
   TIPO_PERT *pert;
   float app_valore,tempo;
int ret;
float app_rateo_cont;
  
   if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		return(-1);

   /* printf("ins_area_pert: arrivata perturbazione tipo %d\n",tipo); */

/*
   Controlla compatibilita' di tipo, se esistono perturbazioni preesistenti,
   se la perturbazione periodica e' subito sostituibile.
   Se nuova perturbazione la inserisce. 
*/
   app_rateo_cont=rateo_durata;
   ret = ControlPert (pert, tipo, indirizzo, valore_delta, 
                           &app_rateo_cont, period, phase,
                           meanvalue, wide, t_null_var, t, dt);
   switch ( ret)
      {
      case -1:
      case  0:
      case  2:
         {
         return(ret);
         break;
         }
      case  1:
         {
         break;
         }
      default :
         {
         printf("\t ControlPert ritorno non previsto=%d\n",ret);
         return(-1);
         break;
         }
      }




   /*
    * verifica se la perturbazione e' di tipo PERT_RAMPA_STOP che sia in
    * corso una perturbazione di tipo PERT_RAMPA altrimenti elimina la
    * perturbazione 
    */
   if (tipo == PERT_RAMPA_STOP)
   {
      for (k = 0; k < _MAX_PERTUR; k++)
	 if ((pert[k].indirizzo == indirizzo) &&
	     (pert[k].tipo == PERT_RAMPA))
	    break;
      if (k == _MAX_PERTUR)
      {
	 fprintf(stderr, "perturbazione tipo PERT_RAMPA non trovata\n");
	 /* la perturbazione non viene inserita */
	 return (-1);
      }
      if (pert[k].esaminata == 0)
	 return (2);
   }
   /*
    * verifica se la perturbazione e' di tipo PERT_TO_STOP che sia in corso
    * una perturbazione di tipo PERT_TO altrimenti elimina la perturbazione 
    */
   if (tipo == PERT_TO_STOP)
   {
      for (k = 0; k < _MAX_PERTUR; k++)
	 if ((pert[k].indirizzo == indirizzo) &&
	     (pert[k].tipo == PERT_TO))
	    break;
      if (k == _MAX_PERTUR)
      {
	 fprintf(stderr, "perturbazione tipo PERT_TO non trovata\n");
	 /* la perturbazione non viene inserita */
	 return (-1);
      }
      if (pert[k].esaminata == 0)
	 return (2);
   }
   /*
    * verifica se la perturbazione e' di tipo PERT_PERIODIC_STOP che sia in
    * corso una perturbazione di tipo PERT_PERIODIC altrimenti elimina la
    * perturbazione 
    */
   if (tipo == PERT_PERIODIC_STOP)
   {
      for (k = 0; k < _MAX_PERTUR; k++)
	 if ((pert[k].indirizzo == indirizzo) &&
	     (pert[k].tipo == PERT_PERIODIC))
	    break;
      if (k == _MAX_PERTUR)
      {
	 fprintf(stderr, "perturbazione tipo PERT_PERIODIC non trovata\n");
	 /* la perturbazione non viene inserita */
	 return (-1);
      }
      if (pert[k].esaminata == 0)
	 return (2);
   }
   /*
    * verifica se la perturbazione e' di tipo PERT_WHITENOISE_STOP che sia in
    * corso una perturbazione di tipo PERT_WHITENOISE altrimenti elimina la
    * perturbazione 
    */
   if (tipo == PERT_WHITENOISE_STOP)
   {
      for (k = 0; k < _MAX_PERTUR; k++)
	 if ((pert[k].indirizzo == indirizzo) &&
	     (pert[k].tipo == PERT_WHITENOISE))
	    break;
      if (k == _MAX_PERTUR)
      {
	 fprintf(stderr, "perturbazione tipo PERT_WHITENOISE non trovata\n");
	 /* la perturbazione non viene inserita */
	 return (-1);
      }
      if (pert[k].esaminata == 0)
	 return (2);
   }
   /*
    * verifica se la perturbazione e' di tipo PERT_MALFUNCTION_STOP che sia in
    * corso una perturbazione di tipo PERT_MALFUNCTION altrimenti elimina la
    * perturbazione 
    */
   if (tipo == PERT_MALFUNCTION_STOP)
   {
      for (k = 0; k < _MAX_PERTUR; k++)
         if ((pert[k].indirizzo == indirizzo) &&
             (pert[k].tipo == PERT_MALFUNCTION))
            break;
      if (k == _MAX_PERTUR)
      {
         fprintf(stderr, "perturbazione tipo PERT_MALFUNCTION non trovata\n");
         /* la perturbazione non viene inserita */
         return (-1);
      }
      if (pert[k].esaminata == 0)
         return (2);
   }
   /*
    * verifica se la perturbazione e' di tipo PERT_IMPULSO_STOP che sia in
    * corso una perturbazione di tipo PERT_IMPULSO altrimenti elimina la
    * perturbazione 
    */
   if (tipo == PERT_IMPULSO_STOP)
   {
      for (k = 0; k < _MAX_PERTUR; k++)
	 if ((pert[k].indirizzo == indirizzo) &&
	     (pert[k].tipo == PERT_IMPULSO))
	    break;
      if (k == _MAX_PERTUR)
      {
	 fprintf(stderr, "perturbazione tipo PERT_IMPULSO non trovato\n");
	 /* la perturbazione non viene inserita */
	 return (-1);
      }
      if (pert[k].esaminata == 0)
	 return (2);
   }
   /*
    * verifica se la perturbazione e' di tipo PERT_DOWN che sia in corso una
    * perturbazione di tipo PERT_UP altrimenti elimina la perturbazione 
    */
   if (tipo == PERT_DOWN)
   {
      for (k = 0; k < _MAX_PERTUR; k++)
	 if ((pert[k].indirizzo == indirizzo) &&
	     (pert[k].tipo == PERT_UP))
	    break;
      if (k == _MAX_PERTUR)
      {
	 fprintf(stderr, "perturbazione tipo PERT_UP non trovata\n");
	 /* la perturbazione non viene inserita */
	 return (-1);
      }
      if (pert[k].esaminata == 0)
	 return (2);

   }
   /*
    * cerca una posizione libera 
    */
   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert[k].tipo == -1)
	 break;
   if (k == _MAX_PERTUR)
   {
      fprintf(stderr, "Raggiunto il numero massimo di perturbazioni\n");
      return (-1);
   }

   /*
    * Se e' una PERT_RAMPA controlla il segno del valore rateo_durata 
    */
   if (tipo == PERT_RAMPA)
   {
      if (rateo_durata == 0)
	 return (-1);
      RtDbPGetValue(dbpunti,indirizzo,&app_valore);
      if (app_valore <= valore_delta)
	 rateo_durata = (float) fabs((double) rateo_durata);
      else
	 rateo_durata = -(float) fabs((double) rateo_durata);
   }
   /*
    * Se e' una PERT_TO controlla inserisce il rateo al posto del tempo 
    */
   if (tipo == PERT_TO)
   {
      app_rateo = rateo_durata;
#if defined OLD_PERT_TO
      app_rateo = rateo_durata;
      if (rateo_durata > 0)
      {
	 RtDbPGetTime(dbpunti,&tempo);
         printf("\t ins_area_pert app_rateo=%f tempo=%f\n",
                  app_rateo,tempo);
	 if (tempo >= rateo_durata)
            {
            printf("\t ins_area_pert rateo_durata annullato\n");
	    rateo_durata = -0.0000001;
            }
	 else
            {
	    rateo_durata = rateo_durata - tempo;
            printf("\t ins_area_pert rateo_durata diventa=%f",rateo_durata);
            }
	 rateo_durata = ((int) (rateo_durata / 0.1)) * 0.1;
      }
      rateo_durata = (float) fabs((double) rateo_durata);
      printf(" rateo_durata ===> %f\n",rateo_durata);
#endif
      if (rateo_durata == 0)
         {
         printf(" La scarto perche' rateo ==0\n");
	 return (-1);
         }
   }

   /*
    * pulisce l'area di perturbazioni interessata
    */
   memset(&pert[k], 0, sizeof(TIPO_PERT));
   pert[k].posizione = k + 1;


   /* inserisce la perturbazione nella posizione k */
   /* printf("Perturbazione %d inserita nello slot %d\n",tipo,k); */
   /*
    * se la perturbazione e' di tipo PERT_UP_REPLAY la inserisce come un
    * PERT_UP gia' esaminata.
    * Tale caso non si presenta nel caso di modifica per cui non lo inserisco
    * nella funzione ControlPert.
    */
   pert[k].esaminata = 0;
   if (tipo == PERT_UP_REPLAY)
   {
      tipo = PERT_UP;
      pert[k].esaminata = 1;
   }
   pert[k].tipo = tipo;
   pert[k].indirizzo = indirizzo;
   pert[k].valore_delta = valore_delta;
   pert[k].rateo_durata = rateo_durata;
   pert[k].period = period;
   pert[k].phase = phase;
   pert[k].meanvalue = meanvalue;
   pert[k].wide = wide;
   pert[k].t_null_var = t_null_var;
   pert[k].t = t;
   if ((stato_sked == STATO_RUN) || (stato_sked == STATO_FREEZE))
   {
      /* registro la perturbazione */
      memcpy(&app_pert, &pert[k], sizeof(TIPO_PERT));
      RtDbPGetTime(dbpunti,&tempo);
      app_pert.t = tempo;
      if (app_pert.tipo == PERT_TO)
	 app_pert.rateo_durata = app_rateo;
      /* marca la perturbazione come PERT_REPLAY */
#if defined SAVEPERT
#if defined REPLAY
      app_pert.runtime_replay = PERT_REPLAY;
#endif
      ret = fwrite(&app_pert, sizeof(TIPO_PERT), 1, fp_pert);
      if( ret!=1 )
        printf("\t ins_area_pert fallita scrittura pert sul file ret=%d\n",ret);
      fflush(fp_pert);
#endif
   }
   return (1);
}

show_area_pert(int attesa)
{
   int        k;
   TIPO_PERT *pert;
   float      tempo,valore=-9;
  
   if( attesa==0 )
      if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		return;
   else
      if((pert=RtDbPGetPuntPertAtt(dbpunti))==NULL)
		return;

   RtDbPGetTime(dbpunti,&tempo);

   for (k = 0; k < _MAX_PERTUR; k++)
      {
      if ( ((pert[k].tipo > 0)&&(pert[k].tipo < MAX_PERT)) || 
           (pert[k].tipo == -1) )
	{
         printf("Elenco perturbazioni t=%f (in attesa=%d)\n", tempo,attesa);
         if( attesa!=1 )
            {
            RtDbPGetValue(dbpunti,pert[k].indirizzo,&valore);
	    printf("Pos = %d tipo = %d ind= %d val= %f rt= %f t= %f ->%f\n",
		k, pert[k].tipo,
		pert[k].indirizzo,
		pert[k].valore_delta,
		pert[k].rateo_durata,
	        pert[k].t, valore);
	    }
         else
	    {
	     printf("Pos = %d tipo = %d ind= %d val= %f rt= %f t= %f ->%f\n",
		k, pert[k].tipo,
		pert[k].indirizzo,
		pert[k].valore_delta,
		pert[k].rateo_durata,
	        pert[k].t, valore);
	    }
	}
      }

}

gest_area_pert(modello, dt)
   int             modello;
   float           dt;
{
   int             k, i, ind;
   float           rateo;
   TIPO_PERT *pert,*pert_att;
   float tempo,valore;
   int ret;
   float app_time;

  
   if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		return;
   if((pert_att=RtDbPGetPuntPertAtt(dbpunti))==NULL)
		return;


   dt = dt * fattore_step;


   /*
    * scoda prima le perturbazioni di tipo: PERT_SCALINO PERT_RAMPA
    * PERT_IMPULSO PERT_UP PERT_NOT PERT_TO PERT_PERIODIC PERT_WHITENOISE 
    * PERT_MALFUNCTION
    *
    * quindi quelle di tipo: PERT_RAMPA_STOP PERT_IMPULSO_STOP PERT_DOWN
    * PERT_TO_STOP PERT_PERIODIC_STOP PERT_WHITENOISE_STOP 
    * PERT_MALFUNCTION_STOP
    */
/*
   for (k = 0; k < _MAX_PERTUR; k++)
      if ( pert_att[k].tipo > 0 ) 
           printf("[A] %d) indirizzo=%d\n",pert_att[k].indirizzo);
*/

   for (k = 0; k < _MAX_PERTUR; k++)
      if ((pert_att[k].tipo > 0) &&
	  (RtDbPGetModelFromInd(dbpunti,pert_att[k].indirizzo)== modello) &&
	  ((pert_att[k].tipo == PERT_SCALINO)     ||
	   (pert_att[k].tipo == PERT_RAMPA)       ||
	   (pert_att[k].tipo == PERT_IMPULSO)     ||
	   (pert_att[k].tipo == PERT_UP)          ||
	   (pert_att[k].tipo == PERT_NOT)         ||
	   (pert_att[k].tipo == PERT_TO)          ||
	   (pert_att[k].tipo == PERT_WHITENOISE)  ||
	   (pert_att[k].tipo == PERT_MALFUNCTION) ||
	   (pert_att[k].tipo == PERT_PERIODIC)))
      {
	 pert_att[k].t -= dt;
	 if (pert_att[k].t < 0)
	 {
/*          Se inserita con successo la pert non e' piu' in attesa */
	    if (ret = ins_area_pert(
			      pert_att[k].tipo,
			      pert_att[k].indirizzo,
			      pert_att[k].valore_delta,
			      pert_att[k].rateo_durata,
			      pert_att[k].period,
			      pert_att[k].phase,
			      pert_att[k].meanvalue,
			      pert_att[k].wide,
			      pert_att[k].t_null_var, 0., dt) <= 1)
               {
	       pert_att[k].tipo = -1;
               } 
	 }
      }

/*
   for (k = 0; k < _MAX_PERTUR; k++)
      if ( pert_att[k].tipo > 0 ) 
           printf("[B] %d) indirizzo=%d\n",pert_att[k].indirizzo);
*/
   for (k = 0; k < _MAX_PERTUR; k++)
      if ((pert_att[k].tipo > 0) &&
	  (RtDbPGetModelFromInd(dbpunti,pert_att[k].indirizzo)== modello) &&
	  ((pert_att[k].tipo == PERT_RAMPA_STOP) ||
	   (pert_att[k].tipo == PERT_IMPULSO_STOP) ||
	   (pert_att[k].tipo == PERT_DOWN) ||
	   (pert_att[k].tipo == PERT_TO_STOP) ||
	   (pert_att[k].tipo == PERT_WHITENOISE_STOP) ||
	   (pert_att[k].tipo == PERT_MALFUNCTION_STOP) ||
	   (pert_att[k].tipo == PERT_PERIODIC_STOP)))
      {
	 pert_att[k].t -= dt;
	 if (pert_att[k].t < 0)
	 {
	    if (ins_area_pert(
			      pert_att[k].tipo,
			      pert_att[k].indirizzo,
			      pert_att[k].valore_delta,
			      pert_att[k].rateo_durata,
			      pert_att[k].period,
			      pert_att[k].phase,
			      pert_att[k].meanvalue,
			      pert_att[k].wide,
			      pert_att[k].t_null_var, 0.,dt) <= 1)
	       pert_att[k].tipo = -1;
	 }
      }

/*
   CICLO gestione delle perturbazioni
   for (k = 0; k < _MAX_PERTUR; k++)
      if ( pert[k].tipo > 0 ) 
           printf("[A] %d) indirizzo=%d\n",pert[k].indirizzo);
*/

   for (k = 0; k < _MAX_PERTUR; k++)
      if ((pert[k].tipo > 0) &&
	  (RtDbPGetModelFromInd(dbpunti,pert[k].indirizzo) == modello))
	 switch (pert[k].tipo)
	 {
         case PERT_MALFUNCTION:
            {
/*             Se nell'intorno di zero la MALFUNCTION si autoelimina */
               if ( ResettaMalf(pert[k].valore_delta) )
                  {
                  printf("PERT_MALFUNCTION: AUTOELIMINAZIONE (%f)\n",
                         pert[k].valore_delta);
                  pert[k].valore_delta = 0.0;
                  RtDbPPutValue(dbpunti,pert[k].indirizzo,
                           pert[k].valore_delta);
                  pert[k].tipo = -1;
                  break;
                  }
               else
                  {
                  RtDbPPutValue(dbpunti,pert[k].indirizzo,
                           pert[k].valore_delta);
/*                Non eliminandola resa attiva */
                  /* pert[k].tipo = -1; */
                  pert[k].esaminata = 1; 
                  break;
                  }
            }
         case PERT_MALFUNCTION_STOP:
            {
/*
               fprintf(stderr,
                    "\t Sono in PERT_MALFUNCTION_STOP (ind=%d delta=%f)\n",
                    pert[k].indirizzo,pert[k].valore_delta);
*/
               RtDbPPutValue(dbpunti,pert[k].indirizzo,
                        pert[k].valore_delta);

               /* cerca la malfunzione da eliminare */
               for (i = 0; i < _MAX_PERTUR; i++)
                  if ((i != k) &&
                      (pert[k].indirizzo ==
                       pert[i].indirizzo) &&
                      (pert[i].tipo == PERT_MALFUNCTION) &&
                      (pert[k].t <= 0))
                     break;
               if (i == _MAX_PERTUR)
               {
                  fprintf(stderr, "Impossibile eseguire MALFUNCTION_STOP\n");
                  pert[k].tipo = -1;
                  return (-1);
               }
               /* elimina le PERT_MALFUNCTION e PERT_MALFUNCTION_STOP */
               pert[k].tipo = -1;
               pert[i].tipo = -1;

               break;
            }
	 case PERT_SCALINO:
	    {
	       RtDbPPutValue(dbpunti,pert[k].indirizzo,
			pert[k].valore_delta);
	       pert[k].tipo = -1;
	       pert[k].esaminata = 1;
	       break;
	    }
	 case PERT_RAMPA:
	    {
	       valore = RtDbPGetValueD(dbpunti,pert[k].indirizzo) +
			pert[k].rateo_durata * dt;
               /*
	       printf("RAMPA: rateo=%f (tipo=%d ind=%d) valore=%f\n",
                       pert[k].rateo_durata,pert[k].tipo,
                       pert[k].indirizzo,valore);
               */
	       RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
	       if (pert[k].rateo_durata > 0)
	       {
		  if (valore >= pert[k].valore_delta)
		  {
		     RtDbPPutValue(dbpunti,pert[k].indirizzo,
					pert[k].valore_delta);
		     pert[k].tipo = -1;
		  }
	       } else
	       {
		  if (valore <= pert[k].valore_delta)
		  {
		     RtDbPPutValue(dbpunti,pert[k].indirizzo,
					pert[k].valore_delta);
		     pert[k].tipo = -1;
		  }
	       }
	       pert[k].esaminata = 1;
	       break;
	    }
	 case PERT_RAMPA_STOP:
	    {
	       /* cerca la perturbazione a rampa da eliminare */
	       for (i = 0; i < _MAX_PERTUR; i++)
		  if ((i != k) &&
		      (pert[k].indirizzo ==
		       pert[i].indirizzo) &&
		      (pert[i].tipo == PERT_RAMPA) &&
		      (pert[k].t <= 0))
		     break;
	       if (i == _MAX_PERTUR)
	       {
		  fprintf(stderr, "Impossibile eseguire RAMPA_STOP\n");
		  pert[k].tipo = -1;
		  return (-1);
	       }
	       /* elimina le perturbazioni di RAMPA e di RAMPA_STOP */
	       pert[k].tipo = -1;
	       pert[i].tipo = -1;

	       break;
	    }
	 case PERT_TO:
	    {
               RtDbPGetTime(dbpunti,&app_time);
               rateo = (pert[k].valore_delta -
                        RtDbPGetValueD(dbpunti,pert[k].indirizzo)) /
                  (pert[k].rateo_durata - dt);
	       pert[k].rateo_durata -= dt;
	       valore = RtDbPGetValueD(dbpunti,pert[k].indirizzo) + rateo * dt;
	       RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
               /*
                * printf("PERT_TO:rateo=%f rateo_durata=%f v=%f time=%f\n",
                *         rateo,pert[k].rateo_durata,valore,app_time);
                */
	       if (rateo > 0)
	       {
/*                Rampa crescente, si ha raggiunto il target */
		  if (valore >= pert[k].valore_delta)
		  {
		     RtDbPPutValue(dbpunti,pert[k].indirizzo,
				pert[k].valore_delta);
		     pert[k].tipo = -1;
		  }
	       } else
	       {
/*                Rampa decrescente, si e' scesi al valore di target */
		  if (valore <= pert[k].valore_delta)
		  {
		     RtDbPPutValue(dbpunti,pert[k].indirizzo,
                                pert[k].valore_delta);
		     pert[k].tipo = -1;
		  }
	       }
	       pert[k].esaminata = 1;
	       break;
	    }
	 case PERT_TO_STOP:
	    {
	       /* cerca la perturbazione a rampa da eliminare */
	       for (i = 0; i < _MAX_PERTUR; i++)
		  if ((i != k) &&
		      (pert[k].indirizzo ==
		       pert[i].indirizzo) &&
		      (pert[i].tipo == PERT_TO) &&
		      (pert[k].t <= 0))
		     break;
	       if (i == _MAX_PERTUR)
	       {
		  pert[k].tipo = -1;
		  fprintf(stderr, "Impossibile eseguire RAMPA_TO\n");
		  return (-1);
	       }
	       /* elimina le perturbazioni di TO e di TO_STOP */
	       pert[k].tipo = -1;
	       pert[i].tipo = -1;

	       break;
	    }
	 case PERT_IMPULSO:
	    {
	       if ( pert[k].esaminata != 1 )
	          {
/*                
                  All'attivazione della perturbazione viene salvato in 
                  period il valore originario per consentire il recupero del
                  valore di partenza originario anche in caso di successive 
                  modifiche della perturbazione.
*/
                  if( !pert[k].esaminata )
		     pert[k].period = RtDbPGetValueD(dbpunti,pert[k].indirizzo);

		  pert[k].valore_delta =
		     pert[k].valore_delta - 
			RtDbPGetValueD(dbpunti,pert[k].indirizzo);
		  valore = RtDbPGetValueD(dbpunti,pert[k].indirizzo)+
			pert[k].valore_delta;
		  RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
		  pert[k].esaminata = 1;
		  if (pert[k].rateo_durata == 0)
		     pert[k].rateo_durata = dt;
	          }
/*
 * debug
 *             printf("\t IMPULSO rt=%f\n",pert[k].rateo_durata);
 */
	       if (pert[k].rateo_durata <= 0)
	          {
/*
		  valore = RtDbPGetValueD(dbpunti,pert[k].indirizzo)-
			pert[k].valore_delta;
		  RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
*/
/*
                  Al termine ripristino il valore originario della
                  variabile perturbata.
*/
		  RtDbPPutValue(dbpunti,pert[k].indirizzo,pert[k].period);
		  pert[k].tipo = -1;
	          }
	       pert[k].rateo_durata -= dt;
	       break;
	    }
	 case PERT_IMPULSO_STOP:
	    {
	       /* cerca la perturbazione impulso da eliminare */
	       for (i = 0; i < _MAX_PERTUR; i++)
		  if ((i != k) &&
		      (pert[k].indirizzo ==
		       pert[i].indirizzo) &&
		      (pert[i].tipo == PERT_IMPULSO) &&
		      (pert[k].t <= 0))
		     break;
	       if (i == _MAX_PERTUR)
	       {
		  pert[k].tipo = -1;
		  fprintf(stderr, "Impossibile eseguire PERT_IMPULSO_STOP\n");
		  return (-1);
	       }
	       /*
	        * elimina le pert di PERT_IMPULSO e di
	        * PERT_IMPULSO_STOP 
	        */
	       pert[k].tipo = -1;
	       pert[i].tipo = -1;
	       /* resetta il valore secondo la nuova modalita' */
/*
		valore = RtDbPGetValueD(dbpunti,pert[i].indirizzo) -
			pert[i].valore_delta;
*/
		valore = pert[i].period;
		RtDbPPutValue(dbpunti,pert[i].indirizzo,valore);
	       break;
	    }
	 case PERT_UP:
	    {
	       if (!pert[k].esaminata)
	       {
		  valore = (float)nega(
			RtDbPGetValueD(dbpunti,pert[k].indirizzo));
		  RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
		  pert[k].esaminata = 1;
	       }
	       break;
	    }
	 case PERT_DOWN:
	    {
	       /* cerca la perturbazione up da eliminare */
	       for (i = 0; i < _MAX_PERTUR; i++)
		  if ((pert[k].indirizzo ==
		       pert[i].indirizzo) &&
		      (pert[i].tipo == PERT_UP))
		     break;
	       if (i == _MAX_PERTUR)
	       {
		  pert[k].tipo = -1;
		  fprintf(stderr, "Pert(%d): Impossibile eseguire DOWN\n",
			  k);
		  return (-1);
	       }
	       /* elimina le pert di PERT_UP e di PERT_DOWN */
	       pert[k].tipo = -1;
	       pert[i].tipo = -1;
	       /* resetta il valore */
	       valore = (float)nega(
			RtDbPGetValueD(dbpunti,pert[k].indirizzo));
	       RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
	       break;
	    }
	 case PERT_NOT:
	    {
	       valore = (float)nega(
			RtDbPGetValueD(dbpunti,pert[k].indirizzo));
	       RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
	       pert[k].tipo = -1;
	       break;
	    }
	 case PERT_PERIODIC:
	    {
	       valore =
		  funz_periodic(RtDbPGetValueD(dbpunti,pert[k].indirizzo),
				pert[k].period,
				&(pert[k].phase),
				pert[k].meanvalue,
				pert[k].wide,
				pert[k].valore_delta,
				pert[k].rateo_durata,
				pert[k].t_null_var, dt,
				&(pert[k].esaminata));
		RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
	       break;
	    }
	 case PERT_PERIODIC_STOP:
	    {
	       /* cerca la perturbazione periodica da eliminare */
	       for (i = 0; i < _MAX_PERTUR; i++)
		  if ((i != k) &&
		      (pert[k].indirizzo ==
		       pert[i].indirizzo) &&
		      (pert[i].tipo == PERT_PERIODIC) &&
		      (pert[k].t <= 0))
		     break;
	       if (i == _MAX_PERTUR)
	       {
		  fprintf(stderr, "Impossibile eseguire PERIODIC_STOP\n");
		  pert[k].tipo = -1;
		  return (-1);
	       }
	       /* elimina le perturbazioni di PERIODIC e di PERIODIC_STOP */
	       pert[k].tipo = -1;
	       pert[i].tipo = -1;

	       break;
	    }
	 case PERT_WHITENOISE:
	    {
	       valore =
		  funz_whitenoise(RtDbPGetValueD(dbpunti,pert[k].indirizzo),
				  pert[k].wide,
				  pert[k].meanvalue,
				  pert[k].t_null_var,
				  (&pert[k].esaminata));
		RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
	       break;
	    }
	 case PERT_WHITENOISE_STOP:
	    {
	       /* cerca la perturbazione periodica da eliminare */
	       for (i = 0; i < _MAX_PERTUR; i++)
		  if ((i != k) &&
		      (pert[k].indirizzo ==
		       pert[i].indirizzo) &&
		      (pert[i].tipo == PERT_WHITENOISE) &&
		      (pert[k].t <= 0))
		     break;
	       if (i == _MAX_PERTUR)
	       {
		  fprintf(stderr, "Impossibile eseguire WHITENOISE_STOP\n");
		  pert[k].tipo = -1;
		  return (-1);
	       }
	       /* elimina le perturbazioni di WHITENOISE e di WHITENOISE_STOP */
	       pert[k].tipo = -1;
	       pert[i].tipo = -1;

	       break;
	    }
	 }

   /* ritorno corretto */
   return (1);
}


float funz_periodic(valore, periodo, phase, meanvalue, wide, t1, t2, t3,
                   dt, esaminata)
   float           valore;
   float           periodo;
   float          *phase;
   float           meanvalue;
   float           wide;
   float           dt;
   float           t1;
   float           t2;
   float           t3;
   float          *esaminata;
{
   float           valore_ret = valore;
   float           app_phase;

/*
printf("PERIODIC val=%f phase=%f per=%f \n\t\t MV=%f wide=%f es=%f \n",
        valore,*phase,periodo,meanvalue,wide,*esaminata);
*/

   if (*esaminata == 0)
      {
      if (*phase < 0)
	 *phase = -dt;
      *phase = -(*phase / 360) * periodo;
      *phase = *phase - fmod(*phase, dt);
      /* printf("\t Fase ricalcolata, vale %f\n",*phase); */
      }
   *phase += dt;
   if (*phase >= 0)
      if ((t1 == -1) && (t2 == -1))
         {
/*       Perturbazione sinusoidale */
	 valore_ret = sin((*phase / periodo) * 2 * M_PI) * wide + meanvalue;
         } 
      else
         {
/*       Perturbazione trapezoidale */
         app_phase = fmod(*phase, periodo);
         valore_ret = 0;
	 if (app_phase <= t1)
            {
	    valore_ret = app_phase * wide / t1;
/*
 *       debug
 *          printf("\t [1] app_phase=%f phase=%f wide=%f valore_ret=%f\n",
 *                 app_phase,*phase,wide,valore_ret);
 */
            }
	 if ((app_phase > t1) && (app_phase <= (t2 + t1)))
            {
	    valore_ret = wide;
/*
 *       debug
 *          printf("\t [2] app_phase=%f phase=%f wide=%f valore_ret=%f\n",
 *                 app_phase,*phase,wide,valore_ret);
 */
            }
	 if ((app_phase > (t1 + t2)) && (app_phase <= (t1 + t2 + t3)))
            {
	    valore_ret = (wide * (t1 + t2 + t3) - wide * app_phase) / (t3);
/*
 *       debug
 *          printf("\t [3] app_phase=%f phase=%f wide=%f valore_ret=%f\n",
 *                 app_phase,*phase,wide,valore_ret);
 */
            }
	 valore_ret += meanvalue;
      }
   *esaminata = 1;
   return (valore_ret);
}


float
funz_whitenoise(valore, wide, meanvalue, variance, esaminata)
   float           valore, wide, meanvalue, variance;
   float          *esaminata;
{
   float           app_valore;

   if (*esaminata == 0)
   {
#if defined VMS || defined SCO_UNIX
      srand(1);
#else
      srandom(1);
#endif
      *esaminata = 1;
   }
   if (variance > 0)
#if defined VMS || defined SCO_UNIX
      app_valore = sin(rand()) * sqrt(variance) + meanvalue;
#else
      app_valore = sin((double)random()) * sqrt(variance) + meanvalue;
#endif
   else
      app_valore = meanvalue;

   return (app_valore);
}


int
reinserisci_updown(int indirizzo)
{
   extern int      id_msg_pert;

   printf("reinserisci_updown: ind = %d\n", indirizzo);
   pert_snd_replay(id_msg_pert, PERT_UP_REPLAY, indirizzo, 0., 0., 0., 0., 0., 0., 0., 0.);
   scoda_buffer(0);
}

/*
   Elimina l'eventuale updown anche dalle pert in attesa
*/
cut_updown()
{
   int             k;
   TIPO_PERT *pert,*pert_att;
   float valore;
  
   if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
		return;

   printf("cut updown\n");
   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert[k].tipo == PERT_UP)
      {
	 printf("trovata PERT_UP addr %d\n", pert[k].indirizzo);
	 valore = nega(RtDbPGetValueD(dbpunti,pert[k].indirizzo));
	 RtDbPPutValue(dbpunti,pert[k].indirizzo,valore);
	 pert[k].tipo = -1;
      }

   if((pert_att=RtDbPGetPuntPertAtt(dbpunti))==NULL)
		return;

   for (k = 0; k < _MAX_PERTUR; k++)
      if (pert_att[k].tipo == PERT_UP)
      {
	 printf("trovata PERT_UP addr %d in attesa\n", pert_att[k].indirizzo);
	 pert_att[k].tipo = -1;
      }
}


/*
    Controlla il tipo di perturbazione.
    Controlla che esista una perturbazione preesistente
    sulla medesima variabile.
    Output:
      -1 :  Si scarta la perturbazione
       0 :  Si ha sostituzione della perturbazione e l'aggiornamento del file
       1 :  Nuova perturbazione, verra' inserita
       2 :  Pert periodica che si trattiene in attesa
*/
int ControlPert (TIPO_PERT *p, int tipo, int ind, float valore_delta,
                 float *rateo_durata, float period, float phase,
                 float meanvalue, float wide, float t_null_var,
                 float t, float dt) 
{
int k;
float valore;
float app_valore;
TIPO_PERT app_pert;
float tempo;
float rateo,app_rateo;
int ret;

   if ( (tipo < PERT_SCALINO) || 
        (tipo > PERT_MALFUNCTION_STOP) )
      {
      fprintf(stderr, "Tipo perturbazione inesistente\n");
      return (-1);
      }

   if (
        (tipo == PERT_SCALINO)  || (tipo == PERT_RAMPA) || 
        (tipo == PERT_IMPULSO)  || (tipo == PERT_UP)    || 
        (tipo == PERT_NOT)      || (tipo == PERT_TO)    ||
        (tipo == PERT_PERIODIC) || (tipo == PERT_WHITENOISE) ||
        (tipo == PERT_MALFUNCTION) 
      )
      {
      for (k = 0; k < _MAX_PERTUR; k++)
	 if ((p[k].indirizzo == ind) &&
	     (p[k].tipo > 0))
	    {
            if( p[k].tipo == tipo )
               {
               RtDbPGetTime(dbpunti,&tempo);
/*
               PERT_RAMPA    controlla il segno di rateo_durata
               PERT_TO       idem  e lo inserisce al posto del tempo
               PERT_IMPULSO  modifica esaminata per riattivarla e non 
                             riassegna period che contiene il valore originario
*/
               if ( tipo==PERT_PERIODIC ) 
                  {
                  if ( (ret=modi_periodic(&p[k], tipo, ind, valore_delta,
                                          rateo_durata,period,phase,meanvalue,
                                          wide,t_null_var,t,dt) )==0 )
                       {
/*                     Perturbazione sostituita e scrittura su file */
                       printf("\t\t Perturbazione periodica sostituita \n");
                       agg_filepert(p[k],tempo,0,fp_pert);
                       }
                  return(ret);
                  }

               if (tipo == PERT_RAMPA)
                  {
                  if ( *rateo_durata == 0)
                      return (-1);
                  RtDbPGetValue(dbpunti,ind,&app_valore);
                  if (app_valore <= valore_delta)
                     (*rateo_durata) = (float) fabs((double) (*rateo_durata));
                  else
                     (*rateo_durata) = -(float) fabs((double) (*rateo_durata));
                  }
               if (tipo == PERT_TO)
                  {
                  app_rateo = *rateo_durata;
                  if ( *rateo_durata > 0)
                     {
                     if (tempo >= *rateo_durata)
                        *rateo_durata = -0.0000001;
                     else
                        *rateo_durata = *rateo_durata - tempo;
                     *rateo_durata = ((int) (*rateo_durata / 0.1)) * 0.1;
                     }
                  *rateo_durata = (float) fabs((double) *rateo_durata);
                  if ( *rateo_durata == 0)
                     return (-1);
                  }
/*
 * debug
 *             printf("\t MODI: perturbazione in pos=%d (rt=%f)\n",
 *                     k,*rateo_durata);
 *             printf("\t\t tipo=%d[%d]  ind=%d[%d] val=%f[%f] \n",
 *                     p[k].tipo,tipo,
 *                     p[k].indirizzo,ind,
 *                     p[k].valore_delta,valore_delta);
 *             printf("\t\t period=%f[%f] \n",
 *                     period,p[k].period);
 *             printf("\t\t rt=%f[%f] t=%f [%f]->shm=%f\n",
 *                     p[k].rateo_durata,*rateo_durata,
 *                     p[k].t,t, valore);
 */
/*             Assegno i nuovi parametri */
               p[k].tipo         = tipo;
               p[k].indirizzo    = ind;
               p[k].valore_delta = valore_delta;
               p[k].rateo_durata = *rateo_durata;
               p[k].t            = t;
               if ( tipo==PERT_IMPULSO )
                  p[k].esaminata = 2;
               else
                  p[k].period    = period;
               p[k].phase        = phase;
               p[k].meanvalue    = meanvalue;
               p[k].wide         = wide;
               p[k].t_null_var   = t_null_var;

/*             Registrazione su file come una nuova perturbazione */
               agg_filepert(p[k],tempo,app_rateo,fp_pert);
               fprintf(stderr,"\t Perturbazione modificata  (tipo=%d)\n",
                       tipo);
               return(0);
               }
            else
               {
               fprintf(stderr, 
                "\t\t Perturbazione scartata;tipo diverso (%d/%d) pos=%d\n",
                       tipo,p[k].tipo,k);
               }
            RtDbPGetValue(dbpunti,p[k].indirizzo,&valore);
	    return (-1);
	    }
      }
   else
      return(1);

   return (1);
}


/*
    Gestisce la perturbazione periodica, decidendo se deve sostituire
    quella corrente gia' esistente sulla medesima variabile oppure se
    lasciarla in attesa.
    La sostituzione avviene nell'ultimo passo di integrazione del periodo.
    Conseguenze dei ritorni:
             0  la perturbazione sostituira' quella preesistente
             2  la perturbazione rimrra'  tra quelle in attesa
*/
int modi_periodic(TIPO_PERT *p, int tipo, int ind, float valore_delta,
                  float *rateo_durata, float period, float phase,
                  float meanvalue,float wide, float t_null_var, 
                  float t, float dt)
{
float phase_modi;


/*  Calcolo quanto manca al termine del periodo */
    phase_modi = fmod(p->phase,p->period);
/*
 *   printf("\t\t\t  phase_modi=%f dt=%f p->post=%f peri=%f\n",
 *           phase_modi,dt,p->post,p->period);
 */
    p->post = phase_modi;

/*  Test di inserimento */
    if(
        ( p->post >= (p->period - dt) ) &&
        ( p->post <  p->period        )
      )
      {
/*    Inserimento */
      p->esaminata    = 0;
      p->tipo         = tipo;
      p->indirizzo    = ind;
      p->valore_delta = valore_delta;
      p->rateo_durata = *rateo_durata;
      p->t            = t;
      p->period       = period;
      p->phase        = phase;
      p->meanvalue    = meanvalue;
      p->wide         = wide;
      p->t_null_var   = t_null_var;
      p->post         = 0.0;
      return(0);
      }
    else
      {
/*    Rinvio inserimento */
      return(2);
      }
}




/*
    Registrazione su file come una nuova perturbazione 
*/
int agg_filepert(TIPO_PERT p, float tempo, float app_rateo, FILE *fpert)
{
TIPO_PERT app_pert;


    memcpy(&app_pert, &p, sizeof(TIPO_PERT));
    app_pert.t = tempo;
    if (app_pert.tipo == PERT_TO)
        app_pert.rateo_durata = app_rateo;
/*  Marca la perturbazione come PERT_REPLAY */
#if defined SAVEPERT
#if defined REPLAY
    app_pert.runtime_replay = PERT_REPLAY;
#endif
    fwrite(&app_pert, sizeof(TIPO_PERT), 1, fpert);
    fflush(fp_pert);
#endif
    return(0);
}


/*
    Se il valore proposto e' minore di un delta in valore
    assoluto ritorna 1 altrimenti zero.
*/
int ResettaMalf(float valore)
{
float delta=0.05;


    if( (valore < delta) && (valore > ((-1)*delta)) )
        return(1);
    else
        return(0);


}
