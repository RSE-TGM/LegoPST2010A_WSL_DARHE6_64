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
 * OlCompilerP.h - definizioni private per l'oggetto OlCompiler
 */
#ifndef _OlCompilerP_h
#define _OlCompilerP_h
/*
 Inclusione degli heder file privati delle classi superiori
	per il momento nessuna
*/


#include <Xm/XmP.h>
#include <Xl/XlP.h>
	
/*
 Inclusione dell'header file pubblico
*/
#include "OlCompiler.h"

/*
 Inclusione dell'header file privato del database e dell'oggetto connessioni
*/
#include "OlDatabaseTopologiaP.h"
#include "OlConnP.h"

typedef Boolean (*OlInitializeCompilerProc) (
#if NeedFunctionPrototypes
#endif
);


typedef Boolean (*OlCompileVarProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlCompileConfinfoProc) (
#if NeedFunctionPrototypes
#endif
);



/*
 Strutture relative alla nuova Classe
 */
typedef struct {
        OlInitializeCompilerProc initialize_compiler;     /* metodo 
						di inizializzazione */
        OlCompileVarProc compilevar;    /* metodo di compilazione 
					         di una variabile   */
	OlCompileConfinfoProc compileconfinfo;
					/* metodo di compilazione
					delle confinfo     */
        } OlCompilerClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _OlCompilerClassRec {
         OlCompilerClassPart    olcompiler_class;
        } OlCompilerClassRec;

extern OlCompilerClassRec olCompilerClassRec;

/*
 Nuovi campi per il record del widget OlCompiler
 */
typedef struct {
        /* risorse  */
        char *nome_compilatore;      /* nome del compilatore */
	int tipo_comp;		     /* tipo di compilatore  */
	OlDatabaseTopologiaObject database;
	OlConnObject     connessioni;
        } OlCompilerPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _OlCompilerRec {
        OlCompilerPart olcompiler;
        } OlCompilerRec;

#endif /* _OlCompilerP_h */
