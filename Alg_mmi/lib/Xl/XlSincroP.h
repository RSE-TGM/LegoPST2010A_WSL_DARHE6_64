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
   modulo XlSincroP.h
   tipo 
   release 1.5
   data 1/9/96
   reserved @(#)XlSincroP.h	1.5
*/
/*
 * SincroP.h - definizioni private per l'oggetto Sincro
 */ 
#ifndef _XlSincroP_h
#define _XlSincroP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>

/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlSincro.h>
/*
 Strutture relative alla nuova Classe
 */




typedef struct {
	int empty;
	} XlSincroClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlSincroClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlSincroClassPart    xlsincro_class;
	} XlSincroClassRec;

extern XlSincroClassRec xlSincroClassRec;

/*
 Nuovi campi per il record del widget XlSincro
 */
typedef struct {
	/* risorse  */
	

        /*
          risorse connesse con sistema di simulazione
          da usarsi per la compilazione
        */
       
	char *str_input_1;	/*nome per input1*/			  
	
	
	char *str_input_5;	/*nome per input5*/
	char *str_input_6;	/*nome per input6*/
	
	

	/*altre risorse*/

	Pixel norm_fg;  /* foreground  */
        Pixel ago_fg;   /* ago  */
	
	
	
	
	


        /*
          variabili di stato (privato)
        */
        GC norm_gc;           /* GC sfondo  */
	GC clear_gc;          /* GC sbiancamento iniziale pixmap */
        GC ago_gc;            /* GC ago indicatore */
	
	float old_posizione;	/*posizione precedente ago indicatore*/
	
	
	
	
	
	FLAG_MMI OldFlag;
	Pixel OldPixel;
	Position starting_x;  /* posizione x iniziale indicatore istogr. */
	Position starting_y;  /* posizione y iniziale indicatore istogr. */

        /*
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata
        */

	
	
        PUNT_VARINP input_1;
	
	
	PUNT_VARINP input_5;
	PUNT_VARINP input_6;
	
	
	} XlSincroPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlSincroRec {
	CorePart   core;
	XlCorePart xlcore;
	XlSincroPart  sincro;
	} XlSincroRec;

#endif /* _XlSincroP_h */
