/**********************************************************************
*
*       C Header:               OlCompiler.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Jan 10 13:50:36 1997 %
*
**********************************************************************/
/*
   modulo OlCompiler.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlCompiler.h	5.1
*/
/*
 * OlCompiler.h - file di include pubblico per l'utilizzo del compilatore
		  di oggetti figli di XlCore
 */
#ifndef _OlCompiler_h
#define _OlCompiler_h

#include <Rt/RtMemory.h>

/* costanti utilizzabili per settare i tipi di XlDatabase */
#define COMP_WARN	  1       /* compila producendo una lista di warning:
				     la procedura non si interrompe */
#define COMP_CHECK        2       /* verifica che siano state setta le
				     risorse necessarie alla compilazione:
				     non e' necessario specificare il database
				     la procedura si interrompe se non sono 
				     state specificate tutte le risorse 
			             necessarie */
#define COMP_SEVERE	  3       /* compilazione definitiva                  */
				  
#define SUPERVIS        "SUPERVIS" 
/* dichiarazione tipi per Classe e Instanziazione di OlCompiler */
typedef struct _OlCompilerClassRec *OlCompilerObjectClass;
typedef struct _OlCompilerRec *OlCompilerObject;

/*
	procedure utilizzabili per la creazione e la distruzione
	dell'oggetto OlCompiler
*/
OlCompilerObject OlCreateCompiler();
Boolean OlDestroyCompiler();
Boolean OlCompilerSetConn();


#endif /* _OlCompiler_h */

