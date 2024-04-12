/**********************************************************************
*
*       C Header:               messaggi.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:01:16 1996 %
*
**********************************************************************/
/* messaggi.h */

/* Buffo Massimo, Calleri Nicola 11/06/1992 */

/* Codici dei messaggi di errore */
#define ECOPYF14	0 /* copia del file f14.dat fallita */
#define	ECREAPIPE	1 /* creazione named pipe fallita */
#define EOPENHIER	2 /* errore apertura gerarchia */
#define EFETCHMWIN	3 /* errore fetching main window */
#define EFETCHDBOX	4 /* errore fetching dialog box */
#define EMEMALLOC	5 /* errore di allocazione della memoria */
#define EOPENF14	6 /* errore apertura file f14.dat */
#define EOPENF03	7 /* errore apertura file f03.dat */

/* Codici dei messaggi di informazione */
#define IWELCOME	0 /* Messaggio di "benvenuto" */
#define IERROPENF11	1 /* Errore apertura file f11.dat */
#define IPRVDATALOAD	2 /* risultati caricati in f14.dat */
#define ILASTDATALOAD	3 /* rilettura del file f14.dat originale */
#define IERROPENPIPE	4 /* Errore apertura del canale di comunicazione */
#define ICALCULATING	5 /* calcolo in corso ... */
#define ICALCNOTEND	6 /* calcolo non terminato */
#define ICALCOK		7 /* calcolo non convergente */
#define ICALCNOTOK	8 /* calcolo terminato a convergenza */
/* fine messaggi.h */
