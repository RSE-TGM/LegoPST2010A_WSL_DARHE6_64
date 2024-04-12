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
   modulo OlFormP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlFormP.h	5.1
*/
/*
 * OlFormP.h - definizioni private per l'oggetto OlForm
 */
#ifndef _OlFormP_h
#define _OlFormP_h
/*
 Inclusione degli heder file privati delle classi superiori
	per il momento nessuna
*/


#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include <Ol/OlForm.h>

typedef Boolean (*OlInitializeProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlReadFormProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlWriteFormProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlNumFormsProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlNumLinesProc) (
#if NeedFunctionPrototypes
#endif
);

typedef int (*OlNumTagsProc) (
#if NeedFunctionPrototypes
#endif
);

typedef char * (*OlTagsProc) (
#if NeedFunctionPrototypes
#endif
);

typedef char * (*OlGetValFormProc)(
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlSetValFormProc) (
#if NeedFunctionPrototypes
#endif
);

typedef Boolean (*OlReadStrValProc) (
#if NeedFunctionPrototypes
#endif
);

typedef char * (*OlWriteStrValProc) (
#if NeedFunctionPrototypes
#endif
);

typedef char * (*OlGetTitleFormProc) (
#if NeedFunctionPrototypes
#endif
);

typedef char * (*OlGetDescrFormProc) (
#if NeedFunctionPrototypes
#endif
);

typedef DESCR_LINE * (*OlGetLineFormProc) (
#if NeedFunctionPrototypes
#endif
);

/*
 Strutture relative alla nuova Classe
 */
typedef struct {
        OlInitializeProc initialize;    /* metodo di inizializzazione DB  */
	OlReadFormProc read;		/* metodo di lettura della form dal file
					  <nome form>.FRM  */
	OlWriteFormProc write;          /* metodo di scrittura della form 
					   su file .FRM    */
	OlNumFormsProc get_num_forms;   /* restituisce il numero di forms
					   presenti */
	OlNumLinesProc get_num_lines;   /* restituisce il numero di linee 
					   che costituiscono la form
					   di indice specificato  */
	OlNumTagsProc  get_num_tags;    /* restituisce il numero di tags che 
					   costituiscono la form precisata */
	OlTagsProc     get_tags;	/* fornisce l'elenco delle tags per la
					   form precisata */
	OlReadStrValProc read_str_inp;	/* lettura dal una stringa dei valori
					   in input e corrispondente carica-
					   mento all'interno della form in
					   memoria    */
	OlWriteStrValProc write_str_inp; /* scrittura della stringa dei valori
					   in input in base a quanto contenuto
					   nella form in memoria */
	OlGetValFormProc get_val_form;  /* estrae un valore da una particolare
					   form in corrispondenza di una
					   particolare tag */
	OlSetValFormProc set_val_form;  /* setta un valore in una particolare
					   form in corrispondenza di una
					   particolare tag */
	OlGetTitleFormProc get_title;   /* restituisce il titolo della form
                                           precisata */
	OlGetDescrFormProc get_descr;   /* fornisce l'elenco delle descrizioni 
                                           analogamente a get_tags */
        OlGetLineFormProc  get_line;    /* restituisce il formato della singola
                                           linea della form */
        } OlFormClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _OlFormClassRec {
         OlFormClassPart    olform_class;
        } OlFormClassRec;

extern OlFormClassRec olFormClassRec;

/*
 Nuovi campi per il record del widget OlForm
 */

typedef struct _descr_forms {
		char title[MAX_L_DESCR+1];
		int num_lines; /* numero di linee costituenti la form */
		DESCR_LINE *pdescr_line; /* descrittori di linea */
		} DESCR_FORMS;

typedef struct {
        /* risorse  */
        char *path_name;      /* pathname del file di forms             */
	int num_forms;	      /* numero delle forms */
	DESCR_FORMS *pdescr_forms;  /* vettore dei descrittori delle singole
				       forms  */
        } OlFormPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _OlFormRec {
        OlFormPart olform;
        } OlFormRec;

#endif /* _OlFormP_h */
