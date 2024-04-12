/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#include <stdio.h>
#include "maxpar.inc"
#include "g1tipdb.inc"
/*
	l'include comunic.inc contiene tutte le variabili
	e le strutture per la scada

        13 Luglio 1992
        Modificato numero file pointer
        agosto 93 mp porting a 32 bit

        16 Marzo 1995
        Inserito flag flag_ordi abilita il ricalcolo di tutti
        i digitali e gli organi in seguito ad una situazione
        di coda c_digor piena (impossibile per calcdi auto-
        accodamento) vedi anche attiper
*/
#ifndef FILEOP_INCL
#include "fileop.inc"
#endif
#include "defpub.h"
/*
	il vettore fpp contiene i canali dei file necessari a
	Scada
	I file sono aperti dalla function init.
*/
#define num_scada 5	 /* numero file descrittori per scada  */

#define fnomi 0		/*	ricerca punto		*/
#define fdde  1		/*	decrittore punti	*/
#define ftab  2		/*	tabulati		*/
#define fdcom 3		/*	comandi	 digitali	*/
#define fdeao 4		/*	comandi analogici	*/

pub FILE *fpp[num_scada];	      /* tabella dei files pointer  */

	
pub S_FSTATO storg[g0dimtip] ;  		/* tabella tipi organi */
pub char stat_diz[rec_fdizst]; 		/* tabella stati organi */	
/*
	variabili contenti i seguenti timer :
	.	acquisizione analogica ( si accettano i valori
		solo dopo un certo intervallo di tempo )
	.	calcolo organi e digitali calcolati ( dopo un
		un certo intervallo vengono calcolati tutti gli
		organi ed i digitali (si presume che sia gia'
		stata effettuata l'acquisizione dei digitali
		acquisiti)
	Se il sistema e' slave il timer per gli analogici viene
	annullato dal task  mcacol, il secondo timer viene invece
	attivato sempre dallo stesso task terminata la fase di
	inizializzazione
*/
#define  tval_aa   0
#define  tval_ordi 10
#define  tval_as   (tval_aa+10)  /* aspetto che siano stati acqui. */
				 /* tutti gli analogici		   */
pub short time_aa ;           /* timer acquisizione analogica		    */
pub short time_as ;           /* timer calcolo analogici calcolati stand. */
pub short time_ordi ;		/* timer calcolo iniziale organo e digitali */
pub short flag_ordi ;		/* flag ricalcolo digitali ed organi (coda c_digor piena) */
                                /* vedi modulo calcdi */
/*
        definizione tabella per raggruppamento armadi di acquisizione
        in sezioni in particolare per la gestione RCE (vedi SEPA)
*/
#define c_gacq_nome 16
#define max_group   max_zone
typedef struct s_group_acq {
                short def;                 // flag di gruppo definito
                char nome[c_gacq_nome];
                char arm[max_zone];       // indici armadi associati
                short Rce_timeout;        // timeout su Rce
    
                           } S_GROUP_ACQ;
                        
pub S_GROUP_ACQ bGroupAcq[max_group];
        
pub S_FSTATO storg[g0dimtip] ;  		/* tabella tipi organi */
/*
	definizione dei canali utilizzati
*/
extern short c_digor, c_visall, c_stamp, c_tabul, c_cval, c_ut_rx, c_ut_tx;
extern short c_dua_tx, c_dua_rx;
extern short c_mmii, c_mmio;
extern short c_aggcfgi, c_aggcfgo;
extern short CHPERIF_00;
extern short c_acquii, c_acquio;
extern short mbox_inet;
extern short mbox_dua;
/*
        definizione mail box utilitzzate
*/
extern short mbox_archiv;

pub    short sys_master;		// sistema master o slave ?
/*
	coefficienti per la generazione della fuori attendibilita'
	delle calcolate standard
        valore reset calcolate definito da utente
*/
pub float coef_media;
pub float coef_filtro;
pub float coef_scarto;
pub float coef_mist;
pub float coef_integrale;
pub float coef_somma;
pub int reset_ut;
