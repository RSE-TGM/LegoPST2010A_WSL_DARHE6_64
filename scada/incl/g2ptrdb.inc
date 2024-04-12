/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
        
        L'include g2ptrdb.inc descrive la struttura
        del data base di sistema a puntatori
	per poter allocare il data base con dimensionamenti
	variabili
*/
#include "defpub.h"
/*
        analogici acquisiti
*/
pub       S_DBAAV  *dbaav;        /* valori        */
pub       S_DBAAF  *dbaaf;        /* flag         */
pub       S_DBAAU  *dbaau ;        /* zona impianto*/
pub       S_DBALL  *dbaaal;        /* struttura allarmi */
pub       S_DBAAFA *dbaafa;        /* flag acquisizione */
#ifdef GERARC
pub       S_DBGERA *dbaag;         /* gerarchia allarmi*/
#endif

/*     
        analogici calcolati standard
*/
pub       S_DBASV   *dbasv ;        /* valori        */
pub       S_DBASF   *dbasf;        /* flag         */
pub       S_DBASU   *dbasu ;        /* zona impianto*/
pub       S_DBALL   *dbasal;        /* struttura allarmi */
pub       DES       *dbasde;        /* descrittore calcolata */
#ifdef GERARC
pub       S_DBGERA  *dbasg;         /* gerarchia allarmi*/
#endif

/*
        analogici calcolati non standard
*/
pub       S_DBACV  *dbacv ;        /* valori        */
pub       S_DBACF  *dbacf ;        /* flag         */
pub       S_DBACU  *dbacu;        /* zona impianto*/
pub       S_DBALL  *dbacal;        /* struttura allarmi */
#ifdef GERARC
pub       S_DBGERA *dbacg;         /* gerarchia allarmi*/
#endif

 /*
        analogici di diagnostica
*/
pub       S_DBADV  *dbadv ;        /* valori        */
pub       S_DBADF  *dbadf ;        /* flag         */
pub       S_DBADU  *dbadu ;        /* zona impianto*/
pub       S_DBALL  *dbadal;        /* struttura allarmi */
#ifdef GERARC
pub       S_DBGERA *dbadg;         /* gerarchia allarmi*/
#endif

/*
        analogici di uscita
*/
pub       S_DBAOF  *dbaof ;        /* flag         */
pub       S_DBAOU  *dbaou;        /* zona impianto*/
pub       S_DBAOM  *dbaom ;        /* indice star associata     */
#ifdef GERARC
pub       S_DBGERA *dbaog;         /* gerarchia allarmi*/
#endif
 
/*
       digitali acquisiti
*/
pub       S_DBDA    *dbda;          /* flag e trattamento        */
pub       S_DBDATR  *dbdatr;        /* trattamento               */
pub       S_DBDAU   *dbdau;        /* zona impianto             */
pub  	  S_CALIN   *dbdaco;        /* calc. e inbiz.            */
#ifdef GERARC
pub       S_DBGERA  *dbdag;         /* gerarchia allarmi*/
#endif
 
//MAX pub  	  S_CALIN_H *dbdaco;        /* calc. e inbiz.            */
/*
        digitali calcolati standard
*/
pub       S_DBDS     *dbds;          /* flag e trattamento */
pub       S_DBDSTR   *dbdstr;        /* trattamento */
pub       S_DBDSU    *dbdsu ;        /* zona impianto */
pub  	  S_CALIN    *dbdsco;        /* calc. e inbiz. */
pub       S_DCALC    *dbdsde;        /* descrittore calcolata */
#ifdef GERARC
pub       S_DBGERA   *dbdsg;         /* gerarchia allarmi*/
#endif
 
/*
        digitali calcolati non standard
*/
pub       S_DBDC   *dbdc;          /* flag e trattamento */
pub       S_DBDCTR *dbdctr;        /* trattamento */
pub       S_DBDCU  *dbdcu ;        /* zona impianto */
pub  	  S_CALIN  *dbdcco;        /* calc. e inbiz. */
#ifdef GERARC
pub       S_DBGERA *dbdcg;         /* gerarchia allarmi*/
#endif
 
/*
        digitali di diagnostica
*/
pub       S_DBDD    *dbdd;          /* flag e trattamento */
pub       S_DBDDTR  *dbddtr;        /* trattamento */
pub       S_DBDDU   *dbddu ;        /* zona impianto */
pub  	  S_CALIN   *dbddco;        /* calc. e inbiz. */
#ifdef GERARC
pub     S_DBGERA *dbddg;            /* gerarchia allarmi*/
#endif

/*
        digitali di uscita
*/
pub  	  S_DBDO	*dbdo;		/* flag comandi	 */
pub       S_DBDOU       *dbdou;        /* zona impianto */
pub  	  S_DBDOM	*dbdom;		/* indice star associata	*/
#ifdef GERARC
pub       S_DBGERA      *dbdog;         /* gerarchia allarmi*/
#endif

/*
        organi
*/
pub       S_DBOSC  *dbosc;         /* stato corr. e flag */
pub       S_DBOSA  *dbosa;         /* stato atteso       */
pub       S_DBOSP  *dbosp;         /* stato precedente   */
pub       S_DBTO   *dbto;          /* time out     */
pub       S_DBOU   *dbou;          /* zona impianto */
pub       S_DBOFT  *dboft;         /* flag time-out */
pub       S_DESORG *dbode;        /* descrittore        */
#ifdef GERARC
pub       S_DBGERA *dbog;          /* gerarchia allarmi*/
#endif

/*
	stringhe
*/
pub       S_DBSTTR   *dbsttr;        /* trattamento */
pub  	  S_DBSTU    *dbstu;		/* zona di impianto       */
pub  	  S_DBSTV    *dbstv;		/* valore	      */
#ifdef GERARC
pub     S_DBGERA     *dbstg;         /* gerarchia allarmi*/
#endif 
