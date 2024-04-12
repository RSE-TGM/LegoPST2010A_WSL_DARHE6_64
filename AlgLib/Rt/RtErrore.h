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
   modulo RtErrore.h
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)RtErrore.h	5.1
*/
/*
 * RtErrore.h - file di include pubblico 
 */
#ifndef _RtErrore_h
#define _RtErrore_h

#include <Rt/Rt.h>

/*
 nomi di risorse utilizzate internamente a RtErrore
 */


/* dichiarazione tipi per Classe e Instanziazione di RtErrore */
typedef struct _RtErroreClassRec *RtErroreOggettoClass;
typedef struct _RtErroreRec *RtErroreOggetto;

/*
 Definizioni di uso generale riguardanti l'oggetto 
*/

#define RT_ERRORE_TERMINALE	0
#define RT_ERRORE_FILE		1

#define RT_ERRORE_SEV_WARNING	0
#define RT_ERRORE_SEV_FATAL	1

#define RT_ERRORE_NO_EXIT	0
#define RT_ERRORE_EXIT		1

/*
 *	elenco codici di errore
 */

#define RT_ERRORE_UNKNOWN	 	 0
#define RT_ERRORE_GENERIC	 	 1
#define RT_ERRORE_MALLOC	 	 2
#define RT_ERRORE_NO_FILE_TOP	 	 3
#define RT_ERRORE_NO_DBP_LOAD	 	 4
#define RT_ERRORE_NO_DBT_LOAD	 	 5
#define RT_ERRORE_NO_MODEL	 	 6
#define RT_ERRORE_NO_ATTACH	 	 7
#define RT_ERRORE_DIFFERENT_DB	 	 8
#define RT_ERRORE_LOW_IND	 	 9
#define RT_ERRORE_HIGHT_IND		10
#define RT_ERRORE_MODEL_NOT_FOUND	11







/*
 *	fine elenco codici di errore
 */


typedef struct _RtInfoErrore{
	int codice;
	char *descr;
	char *solving;
	int severity;
	int exit_on_error;
	} RtErroreInfo, *RtErroreInfoList;


/*
	procedure utilizzabili per la creazione  la distruzione
	e in generale per la gestione dell'oggetto RtErrore
*/
RtErroreOggetto RtCreateErrore(int , char *);
Boolean RtDestroyErrore(RtErroreOggetto );
void RtShowErrore(RtErroreOggetto ,int, char *);

#endif /* _RtErrore_h */

