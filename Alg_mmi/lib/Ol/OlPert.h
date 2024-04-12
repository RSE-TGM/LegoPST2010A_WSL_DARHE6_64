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
   modulo OlPert.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlPert.h	5.1
*/
/*
 * OlPert.h - file di include pubblico per l'utilizzo delle perturbazioni
		  degli oggetti figli di XlCore e XlManager
 */
#ifndef _OlPert_h
#define _OlPert_h

#include <Rt/RtMemory.h>

/* dichiarazione tipi per Classe e Instanziazione di OlPert */
typedef struct _OlPertClassRec *OlPertObjectClass;
typedef struct _OlPertRec *OlPertObject;

/*
	procedure utilizzabili per la creazione e la distruzione
	dell'oggetto OlPert
*/
OlPertObject XlCreatePert();
Boolean XlDestroyPert();


#endif /* _OlPert_h */
