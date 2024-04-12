/*
 * CaiVarP.h - definizioni private per l'oggetto CaiVar
 */ 
#ifndef _XlCaiVarP_h
#define _XlCaiVarP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Xl/XlCaiVar.h>
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int empty;
	} XlCaiVarClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlCaiVarClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlCaiVarClassPart    xlcaiVar_class;
	} XlCaiVarClassRec;

extern XlCaiVarClassRec xlCaiVarClassRec;

/*
 Nuovi campi per il record del widget XlCaiVar
 */
typedef struct {
	/* risorse  */
	int tipo_caiVar;   /* tipo di caiVar */
	int alterna;    /* per la gestione del blink */
	Pixel color_bord; /*colore lettera su CaiVar off*/
	Pixel color_A_FG; /*colore foreground allarmi di tipo A   */
	Pixel color_A_BG; /*colore background allarmi di tipo A  */
	Pixel color_W_FG; /*colore foreground allarmi di tipo W   */
	Pixel color_W_BG; /*colore background allarmi di tipo W  */
	Pixel color_T_FG; /*colore foreground allarmi di tipo T   */
	Pixel color_T_BG; /*colore background allarmi di tipo T  */
	Pixel color_S_FG; /*colore foreground allarmi di tipo S   */
	Pixel color_S_BG; /*colore background allarmi di tipo S  */
	Pixel color_M_FG; /*colore foreground allarmi di tipo M   */
	Pixel color_M_BG; /*colore background allarmi di tipo M  */
	Pixel color_F_FG; /*colore foreground allarmi di tipo F   */
	Pixel color_F_BG; /*colore background allarmi di tipo F  */
	float frequenza1; /*frequenza1 di blink */	
	float frequenza2; /*frequenza2 di blink */
        
        /*
          risorse connesse con sistema di simulazione
          da usarsi per la compilazione
        */

        char *str_allarm_A; /* label per lettera che determina all A */
        char *str_allarm_W; /* label per lettera che determina all W */
        char *str_allarm_T; /* label per lettera che determina all T */
        char *str_allarm_S; /* label per lettera che determina all S */
        char *str_allarm_M; /* label per lettera che determina all M */
        char *str_allarm_F; /* label per lettera che determina all F */

	char * normalfont;  /* nome del font utilizzato per visualizzare
			       il tipo di allarme */
        /*
          variabili di stato (privato)
        */
	XtIntervalId time_id; 
        GC norm_gc;           /* GC normal per font  */
        GC clear_gc;          /* GC sbiancamento iniziale pixmap */
        GC blink_gc;          /* GC blink */
	GC for_gc;		/* GC per foreground CAIVAR */
	XFontStruct *font_info;
        XmFontList font_list;
        /*
          variabili (private) che definiscono il tipo di 
	  allarme (A,W,T,S,M,N)
        */
	char tipo_all;
	char tipo_all_old; /* tipo di allarme al penultimo refresh*/
/*
Introduco array di input (Struttura INPUT_ALL dichiarata in XlP.h)
*/
	INPUT_ALL input_all[MAXNUMINPUT];

	} XlCaiVarPart;

typedef struct _XlCaiVarRec {
	CorePart   core;
	XlCorePart xlcore;
	XlCaiVarPart  caiVar;
	} XlCaiVarRec;

#endif /* _XlCaiVarP_h */
