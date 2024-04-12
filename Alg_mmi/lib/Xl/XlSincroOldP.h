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
   modulo XlSincroOldP.h
   tipo 
   release 1.3
   data 1/9/96
   reserved @(#)XlSincroOldP.h	1.3
*/
/*
 * SincroOldP.h - definizioni private per l'oggetto SincroOld
 */ 
#ifndef _XlSincroOldP_h
#define _XlSincroOldP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>

/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlSincroOld.h>
/*
 Strutture relative alla nuova Classe
 */




typedef struct {
	int empty;
	} XlSincroOldClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlSincroOldClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlSincroOldClassPart    xlsincroOld_class;
	} XlSincroOldClassRec;

extern XlSincroOldClassRec xlSincroOldClassRec;

/*
 Nuovi campi per il record del widget XlSincroOld
 */
typedef struct {
	/* risorse  */
	

        /*
          risorse connesse con sistema di simulazione
          da usarsi per la compilazione
        */
       
	char *str_input_1;	/*nome per input1*/			  
	char *str_input_2;	/*nome per input2*/
	char *str_input_3;	/*nome per input3*/
	char *str_input_4;	/*nome per input4*/
	char *str_input_5;	/*nome per input5*/
	char *str_input_6;	/*nome per input6*/
	
	char *str_out_1;	/*nome per output1*/
	char *str_out_2;	/*nome per output2*/

	/*altre risorse*/

	Pixel norm_fg;  /* foreground  */
        Pixel ago_fg;   /* ago  */
	
	
	float delta_fase; /* differenza fasi */
	float delta_v; /* differenza tensioni*/
	float delta_f; /* differenza frequenze*/
	float time_agg; /* tempo di refresh (per Refresh_Fast)*/
	
	int primo_refresh;	/*indica se si deve fare il 1° refresh*/


        /*
          variabili di stato (privato)
        */
        GC norm_gc;           /* GC sfondo  */
	GC clear_gc;          /* GC sbiancamento iniziale pixmap */
        GC ago_gc;            /* GC ago indicatore */
	
	float old_posizione;	/*posizione precedente ago indicatore*/
	float old_valore;	/*old value sincro-speed*/
	int old_parallelo_ok;	/*old value parallelo*/
	int reset_output;		/*se=1 reset outputs */
	
	XtIntervalId	tempo_id;	/*Identificatore dell' evento di time_out*/
	
	FLAG_MMI OldFlag;
	Pixel OldPixel;
	Position starting_x;  /* posizione x iniziale indicatore istogr. */
	Position starting_y;  /* posizione y iniziale indicatore istogr. */

        /*
          variabili di stato (private) calcolate da compilazione
          o da lettura da file di pagina configurata
        */

	PUNT_VAROUT out_1;
	PUNT_VAROUT out_2;
        PUNT_VARINP input_1;
	PUNT_VARINP input_2;
	PUNT_VARINP input_3;
	PUNT_VARINP input_4;
	PUNT_VARINP input_5;
	PUNT_VARINP input_6;

	
	
	} XlSincroOldPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlSincroOldRec {
	CorePart   core;
	XlCorePart xlcore;
	XlSincroOldPart  sincroOld;
	} XlSincroOldRec;

#endif /* _XlSincroOldP_h */
