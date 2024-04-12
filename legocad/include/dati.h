/**********************************************************************
*
*       C Header:               dati.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:02:36 1996 %
*
**********************************************************************/
/*
 dati.h
	contiene le definizioni utilizzate localmente
	dal programma dati
*/
#include <libutilx.h>
/*
 valori che puo' assumere la variabile stato che indica lo stato del 
 programma 
*/
#define NON_SCELTO	0  /* non e' stato ancora selezionato un modello
                              corretto su cui operare */
#define SCELTO		1  /* e' stato scelto un modello su cui operare */
/*
 valori che puo' assumere la variabile tipo_lista che indica il tipo
 di lista richiesta dall'utente
*/
#define ALL_VAR   0  
#define INP_VAR   1
#define OUT_VAR   2 
#define ALL_DATA  3
