/**********************************************************************
*
*       C Source:               agg_scada_db.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 16:04:52 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: agg_scada_db.c-6 %  (%full_filespec: agg_scada_db.c-6:csrc:1 %)";
#endif

/* 

	Processo di 
	
		AGGIORNAMENTO VERSO SUPERVISIONE

	Ver. 1.0		7/1/'93

*/
#define MAX_ALLOC_MODEL 100000000

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sim_param.h" 
#include "sim_types.h"
#include "libnet.h"
#include "dispatcher.h" 
#include "agg_scada.h"	/* include lato supervisione */
#include <Rt/RtDbPunti.h>
#include <Rt/RtErrore.h>
# include <Rt/RtMemory.h>
#include <statistics.h>

/*  #define NUM_TRANCE_ANALOGICI            4 (originale 4-6-93) */
#define NUM_TRANCE_ANALOGICI            1

#define PER_VARIAZIONE	0
#define SINGOLA_TRANCE	0
#define INVIO_TOTALE	1

#define MAX_DIGITALI		10000
#define MAX_ANALOGICI		1000


extern int  ack_send ();

struct val_dig_st
{
    int     ind_scada;
    int     ind_sked;
    float   old_value;
};

typedef struct val_dig_st   VAL_DIG;

VAL_DIG val_dig[MAX_DIGITALI];

struct val_ana_st
{
    int     ind_scada;
    int     ind_sked;
};

typedef struct val_ana_st   VAL_ANA;


VAL_ANA val_ana[MAX_ANALOGICI];

struct val_dbupd_st
{
    float   val;
    int     punt;
};

typedef struct val_dbupd_st VAL_DBUPD;

VAL_DBUPD dati_analogici[MAX_ANALOGICI];
VAL_DBUPD dati_digitali[MAX_DIGITALI];
int     num_analogici_da_spedire;
int     num_digitali_da_spedire;

int     num_digitali;
int     num_analogici;
int     num_trance;

extern VARIABILISLIM * variabili;	/* database variabili di tutti i modelli */
char   *ind_sh_top;	/* puntatore inizio shared memory sh_var */
int     id_sh;		/* identificatore sh_var */
int     nmod;
int     tot_variabili;


extern RtDbPuntiOggetto dbpunti;
extern RtDbPuntiOggetto dbpunti_ext;
extern RtErroreOggetto errore;

extern int task_residente[MAX_MODEL];


float app_val;

int     ricevi_cfg ();
int     cerca_indirizzo ();
int     scada_to_sked ();
int     costruzione_pacchetti_analogici ();
int     costruzione_pacchetti_digitali ();
int     invia_dbupd ();




int     costruzione_pacchetti_analogici (fp, modo, trance)
int     fp;
int     modo;
int     trance;
{
int     inizio;
int     dimensione;
int     k;

    switch (modo)
    {
	case INVIO_TOTALE: 
	    {
		inizio = 0;
		dimensione = num_analogici;
		break;
	    }
	case SINGOLA_TRANCE: 
	    {
		k = num_trance;
		inizio = ((int) (num_analogici / NUM_TRANCE_ANALOGICI)) * num_trance;
		++num_trance;
		if (num_trance == NUM_TRANCE_ANALOGICI)
		{
		    dimensione = num_analogici -
			((int) (num_analogici / NUM_TRANCE_ANALOGICI)) *
			(NUM_TRANCE_ANALOGICI - 1);
		    num_trance = 0;
		}
		else
		    dimensione = num_analogici / NUM_TRANCE_ANALOGICI;
		break;
	    }
    }
/* 
	costruzione pacchetto dati analogici
*/
    num_analogici_da_spedire = dimensione;
    for (k = inizio; k < (inizio + dimensione); k++)
    {
   if(task_residente[val_ana[k].ind_sked/MAX_ALLOC_MODEL]==1)
		{
		app_val=RtDbPGetValueD(dbpunti,val_ana[k].ind_sked);
		memcpy (&dati_analogici[k - inizio].val,
			converti_float_f (&app_val,
		    	TRASMISSIONE, FORM_DATI), sizeof (float));
		}
	else
		{
		app_val=RtDbPGetValueD(dbpunti_ext,val_ana[k].ind_sked);
		memcpy (&dati_analogici[k - inizio].val,
			converti_float_f (&app_val,
		    	TRASMISSIONE, FORM_DATI), sizeof (float));
		}
	memcpy (&dati_analogici[k - inizio].punt,
		converti_int_f (&val_ana[k].ind_scada,
		    TRASMISSIONE, FORM_DATI), sizeof (int));
    }


}

int     costruzione_pacchetti_digitali (fp, modo)
int     fp;
int     modo;
{
int     k;
int     dimensione = 0;
FILE *fp_log;

    switch (modo)
    {
	case INVIO_TOTALE: 
	    {
		for (k = 0; k < num_digitali; k++)
		{
   	if(task_residente[val_dig[k].ind_sked/MAX_ALLOC_MODEL]==1)
			{
		        app_val=RtDbPGetValueD(dbpunti,val_dig[k].ind_sked);
		    memcpy (&dati_digitali[k].val,
			    converti_float_f (&app_val,
				TRASMISSIONE, FORM_DATI), sizeof (float));
		    memcpy (&dati_digitali[k].punt,
			    converti_int_f (&val_dig[k].ind_scada,
				TRASMISSIONE, FORM_DATI), sizeof (int));
		    val_dig[k].old_value = RtDbPGetValueD(dbpunti,
					val_dig[k].ind_sked);
			}
		else
			{
		        app_val=RtDbPGetValueD(dbpunti_ext,val_dig[k].ind_sked);
		    memcpy (&dati_digitali[k].val,
			    converti_float_f (&app_val,
				TRASMISSIONE, FORM_DATI), sizeof (float));
		    memcpy (&dati_digitali[k].punt,
			    converti_int_f (&val_dig[k].ind_scada,
				TRASMISSIONE, FORM_DATI), sizeof (int));
		    val_dig[k].old_value = RtDbPGetValueD(dbpunti_ext,
					val_dig[k].ind_sked);
			}
		}
		dimensione = num_digitali;
		break;
	    }
	case PER_VARIAZIONE: 
	    {
		for (k = 0; k < num_digitali; k++)
		{
   	if(task_residente[val_dig[k].ind_sked/MAX_ALLOC_MODEL]==1)
         {
	  app_val=RtDbPGetValueD(dbpunti,val_dig[k].ind_sked);
		    if (val_dig[k].old_value != app_val)
		    {
			memcpy (&dati_digitali[dimensione].val,
				converti_float_f (&app_val,
				    TRASMISSIONE, FORM_DATI), sizeof (float));
			memcpy (&dati_digitali[dimensione].punt,
				converti_int_f (&val_dig[k].ind_scada,
				    TRASMISSIONE, FORM_DATI), sizeof (int));
			val_dig[k].old_value = app_val;
			++dimensione;
		    }
         }
		else
         {
	  app_val=RtDbPGetValueD(dbpunti_ext,val_dig[k].ind_sked);
		    if (val_dig[k].old_value != app_val)
		    {
			memcpy (&dati_digitali[dimensione].val,
				converti_float_f (&app_val,
				    TRASMISSIONE, FORM_DATI), sizeof (float));
			memcpy (&dati_digitali[dimensione].punt,
				converti_int_f (&val_dig[k].ind_scada,
				    TRASMISSIONE, FORM_DATI), sizeof (int));
			val_dig[k].old_value = app_val;
			++dimensione;
		    }
         }
		}
/*********			
   fp_log = fopen ("agg_scada.log", "a");
	fprintf (fp_log,"SPEDITI %d digitali\n",dimensione);
	fclose (fp_log);
************/
		break;
	    }
    }
    num_digitali_da_spedire = dimensione;
}

int     ricevi_cfg (fp)
int     fp;
{
    SM_CONFIG msg_config;
short   codice_msg;
int     tipopunti;
int     numpunti;
int     indpack;
int     lastpack;
    SVINREC svinrec;
int     k;
int     indirizzo;
    FILE * fp_log;
    FILE * fp_err;
int qq = 0;


/* apertura file di error */
    fp_err = fopen ("agg_scada.err", "w");
/* apertura file di log */
    fp_log = fopen ("agg_scada.log", "w");

    while (1)
    {
        ++qq;
// printf("sizeof(SM_CONFIG) = %d\n",sizeof(SM_CONFIG));
	readn (fp, &msg_config, sizeof (SM_CONFIG));
	/* converte i campi del messaggio */
	memcpy (&codice_msg,
		converti_short_f (&msg_config.hea.mess, RICEZIONE, FORM_DATI),
		sizeof (short));
// printf("ricevimento config codice_msg = %d\n",codice_msg);
	if (codice_msg != CONFIG)
	{
	    printf ("AGG_SCADA:attesa config, ricevuto mess. indesiderato\n");
	    break;
	}
	memcpy (&tipopunti,
		converti_int_f (&msg_config.tipopunti, RICEZIONE, FORM_DATI),
		sizeof (int));
	memcpy (&numpunti,
		converti_int_f (&msg_config.numpunti, RICEZIONE, FORM_DATI),
		sizeof (int));
	memcpy (&indpack,
		converti_int_f (&msg_config.indpack, RICEZIONE, FORM_DATI),
		sizeof (int));
	memcpy (&lastpack,
		converti_int_f (&msg_config.lastpack, RICEZIONE, FORM_DATI),
		sizeof (int));
	if (tipopunti == ANA)
	{
	    for (k = 0; k < numpunti; k++)
	    {
		memcpy (&val_ana[num_analogici].ind_scada,
			converti_int_f (&msg_config.rec[k].punt,
			    RICEZIONE, FORM_DATI), sizeof (int));
		val_ana[num_analogici].ind_sked =
		    cerca_indirizzo (msg_config.rec[k].sigla);
		if (val_ana[num_analogici].ind_sked < 0)
		{
		    fprintf (fp_err, "Il punto analogico %s non esiste\n",
			    msg_config.rec[k].sigla);
		}
		else
		{
		    fprintf (fp_log, "analogici %s ind_scada=%d ind_sked=%d\n",
			    msg_config.rec[k].sigla,
			    val_ana[num_analogici].ind_scada,
			    val_ana[num_analogici].ind_sked);
		    ++num_analogici;
		    if (num_analogici > MAX_ANALOGICI)
			errore ("AGG_SCADA : Superato max numero punti analogici configurati");
		}
	    }
	}
	if (tipopunti == DIG)
	{
	    for (k = 0; k < numpunti; k++)
	    {
		memcpy (&val_dig[num_digitali].ind_scada,
			converti_int_f (&msg_config.rec[k].punt,
			    RICEZIONE, FORM_DATI), sizeof (int));
		val_dig[num_digitali].ind_sked =
		    cerca_indirizzo (msg_config.rec[k].sigla);
		if (val_dig[num_digitali].ind_sked < 0)
		{
		    fprintf (fp_err, "Il punto digitale %s non esiste\n",
			    msg_config.rec[k].sigla);
		}
		else
		{
   	  if(task_residente[val_dig[k].ind_sked/MAX_ALLOC_MODEL]==1)
		    val_dig[num_digitali].old_value =
			RtDbPGetValueD(dbpunti,val_dig[num_digitali].ind_sked);
			else
		    val_dig[num_digitali].old_value =
		            RtDbPGetValueD(dbpunti_ext,
				val_dig[num_digitali].ind_sked);
		    fprintf (fp_log, "digitali %s ind_scada=%d ind_sked=%d %f\n",
			    msg_config.rec[k].sigla,
			    val_dig[num_digitali].ind_scada,
			    val_dig[num_digitali].ind_sked,
			    val_dig[num_digitali].old_value);
		    ++num_digitali;
		    if (num_digitali > MAX_DIGITALI)
			errore ("AGG_SCADA : Superato max numero punti digitali configurati");
		}
	    }
	}

/* invia ack all' ssc */
	ack_send (fp);
/****
   for(k=0;k<numpunti;k++)
	{
    	printf("%.*s %d\n",MAX_LUN_NOME_VAR-1,msg_config.rec[k].sigla,
 		cerca_indirizzo(msg_config.rec[k].sigla));
	}
****/
	if ((lastpack == indpack) && (tipopunti == DIG))
	{
//	    printf ("Ricezione configurazione terminata\n");
	    break;
	}
    }
    printf ("Sono stati configurati \n %d analogici\n %d digitali\n",
	    num_analogici, num_digitali);
    fprintf (fp_log, "Sono stati configurati \n %d analogici\n %d digitali\n",
	    num_analogici, num_digitali);
    fclose (fp_err);
    fclose (fp_log);
}

/*
Funzione reimplementatata per velocizzare ricerca con bisezione
*/

int     cerca_indirizzo (sigla)
char   *sigla;
{
int     ret;
char    app_sigla[MAX_LUN_NOME_VAR];
VARIABILI varp;
int inizio=0;
int fine=tot_variabili;
int pos=0;

    memcpy (&app_sigla[0], sigla, 8);
    app_sigla[MAX_LUN_NOME_VAR - 1] = 0;

    while (inizio <= fine )
       {
       pos= (( fine - inizio ) /2 ) + inizio ;
       ret=memcmp (app_sigla, variabili[pos].nome, MAX_LUN_NOME_VAR);
       if(ret > 0)
          inizio=pos;
       else if ( ret <0 )
          fine=pos;
       else if (ret==0)
           {
	   return (variabili[pos].addr);
           }
       } 
return -1;  /* var not found */
}




int     invia_dbupd (fp)
int     fp;
{
    SM_DBUPD sm_dbupd;
short   mess_ssc;
int     i, j, k;
int     indice_pacchetto = 0;
int     num_pacchetti = 0;
int     num_pacchetti_analogici = 0;
int     num_pacchetti_digitali = 0;
int     tipopunti = 0;
int     numpunti = 0;
int     indpack = 0;
int     lastpack = 0;
int     app_short;
    div_t risult;


    /* calocolo dimensioni del pacchetto da spedire */
    app_short = sizeof (SM_DBUPD);
    memcpy (&sm_dbupd.hea.nodo,
	    converti_short_f (&app_short, TRASMISSIONE, FORM_DATI),
	    sizeof (short));
    /* calcolo numero pacchetti */
    risult = div (num_analogici_da_spedire, DBDIM);
    num_pacchetti += risult.quot;
    if (risult.rem)
	num_pacchetti += 1;
    num_pacchetti_analogici = num_pacchetti;
    risult = div (num_digitali_da_spedire, DBDIM);
    num_pacchetti += risult.quot;
    if (risult.rem)
	num_pacchetti += 1;
    num_pacchetti_digitali = num_pacchetti - num_pacchetti_analogici;
    /* 
     
     invio punti analogici 
     
     */
    tipopunti = ANA;
    numpunti = 0;
    for (k = 0; k < num_analogici_da_spedire; k++)
    {
	sm_dbupd.db[numpunti].val = dati_analogici[k].val;
	sm_dbupd.db[numpunti].punt = dati_analogici[k].punt;
	numpunti += 1;
	if (numpunti == DBDIM)
	{
	    indpack = indice_pacchetto;
	    indice_pacchetto += 1;
	    lastpack = num_pacchetti_analogici - 1;
	    mess_ssc = DBUPD;
	    memcpy (&sm_dbupd.hea.mess,
		    converti_short_f (&mess_ssc, TRASMISSIONE, FORM_DATI),
		    sizeof (short));
	    memcpy (&sm_dbupd.tipopunti,
		    converti_int_f (&tipopunti, TRASMISSIONE, FORM_DATI),
		    sizeof (int));
	    memcpy (&sm_dbupd.numpunti,
		    converti_int_f (&numpunti, TRASMISSIONE, FORM_DATI),
		    sizeof (int));
	    memcpy (&sm_dbupd.indpack,
		    converti_int_f (&indpack, TRASMISSIONE, FORM_DATI),
		    sizeof (int));
	    memcpy (&sm_dbupd.lastpack,
		    converti_int_f (&lastpack, TRASMISSIONE, FORM_DATI),
		    sizeof (int));
	    writen (fp, &sm_dbupd, sizeof (SM_DBUPD));
	    ack_ssc (fp);
	    numpunti = 0;
	}
    }
    if (numpunti != 0)
    {
	indpack = indice_pacchetto;
	indice_pacchetto += 1;
	lastpack = num_pacchetti_analogici - 1;
	mess_ssc = DBUPD;
	memcpy (&sm_dbupd.hea.mess,
		converti_short_f (&mess_ssc, TRASMISSIONE, FORM_DATI),
		sizeof (short));
	memcpy (&sm_dbupd.tipopunti,
		converti_int_f (&tipopunti, TRASMISSIONE, FORM_DATI),
		sizeof (int));
	memcpy (&sm_dbupd.numpunti,
		converti_int_f (&numpunti, TRASMISSIONE, FORM_DATI),
		sizeof (int));
	memcpy (&sm_dbupd.indpack,
		converti_int_f (&indpack, TRASMISSIONE, FORM_DATI),
		sizeof (int));
	memcpy (&sm_dbupd.lastpack,
		converti_int_f (&lastpack, TRASMISSIONE, FORM_DATI),
		sizeof (int));
	writen (fp, &sm_dbupd, sizeof (SM_DBUPD));
	ack_ssc (fp);
	numpunti = 0;
    }
    /* 
     
     invio punti digitali 
     
     */
    tipopunti = DIG;
    numpunti = 0;
    indice_pacchetto = 0;
    for (k = 0; k < num_digitali_da_spedire; k++)
    {
	sm_dbupd.db[numpunti].val = dati_digitali[k].val;
	sm_dbupd.db[numpunti].punt = dati_digitali[k].punt;
	numpunti += 1;
	if (numpunti == DBDIM)
	{
	    indpack = indice_pacchetto;
	    indice_pacchetto += 1;
	    lastpack = num_pacchetti_digitali - 1;
	    mess_ssc = DBUPD;
	    memcpy (&sm_dbupd.hea.mess,
		    converti_short_f (&mess_ssc, TRASMISSIONE, FORM_DATI),
		    sizeof (short));
	    memcpy (&sm_dbupd.tipopunti,
		    converti_int_f (&tipopunti, TRASMISSIONE, FORM_DATI),
		    sizeof (int));
	    memcpy (&sm_dbupd.numpunti,
		    converti_int_f (&numpunti, TRASMISSIONE, FORM_DATI),
		    sizeof (int));
	    memcpy (&sm_dbupd.indpack,
		    converti_int_f (&indpack, TRASMISSIONE, FORM_DATI),
		    sizeof (int));
	    memcpy (&sm_dbupd.lastpack,
		    converti_int_f (&lastpack, TRASMISSIONE, FORM_DATI),
		    sizeof (int));
	    writen (fp, &sm_dbupd, sizeof (SM_DBUPD));
	    ack_ssc (fp);
	    numpunti = 0;
	}
    }
    if (numpunti != 0)
    {
	indpack = indice_pacchetto;
	indice_pacchetto += 1;
	lastpack = num_pacchetti_digitali - 1;
	mess_ssc = DBUPD;
	memcpy (&sm_dbupd.hea.mess,
		converti_short_f (&mess_ssc, TRASMISSIONE, FORM_DATI),
		sizeof (short));
	memcpy (&sm_dbupd.tipopunti,
		converti_int_f (&tipopunti, TRASMISSIONE, FORM_DATI),
		sizeof (int));
	memcpy (&sm_dbupd.numpunti,
		converti_int_f (&numpunti, TRASMISSIONE, FORM_DATI),
		sizeof (int));
	memcpy (&sm_dbupd.indpack,
		converti_int_f (&indpack, TRASMISSIONE, FORM_DATI),
		sizeof (int));
	memcpy (&sm_dbupd.lastpack,
		converti_int_f (&lastpack, TRASMISSIONE, FORM_DATI),
		sizeof (int));
	writen (fp, &sm_dbupd, sizeof (SM_DBUPD));
	ack_ssc (fp);
	numpunti = 0;
    }
    num_analogici_da_spedire = 0;
    num_digitali_da_spedire = 0;
}


scada_to_sked (punt_scada, tipo)
int     punt_scada, tipo;
{
int     ret = -1;
int     k;

    if (tipo == ANA)
    {
	for (k = 0; k < num_analogici; k++)
	{
	    if (val_ana[k].ind_scada == punt_scada)
	    {
		return (val_ana[k].ind_sked);
	    }
	}
	return (ret);
    }
    else
    {
	for (k = 0; k < num_digitali; k++)
	{
	    if (val_dig[k].ind_scada == punt_scada)
	    {
		return (val_dig[k].ind_sked);
	    }
	}
	return (ret);
    }
}
