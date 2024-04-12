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
   modulo OlForm.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlForm.h	5.1
*/
/*
 * OlForm.h - file di include pubblico per l'utilizzo delle form
 */
#ifndef _OlForm_h
#define _OlForm_h

#include <Rt/RtMemory.h>
/*
 nomi di risorse utilizzate internamente a OlForm
 */


/* dichiarazione tipi per Classe e Instanziazione di OlForm */
typedef struct _OlFormClassRec *OlFormObjectClass;
typedef struct _OlFormRec *OlFormObject;

/*
 Definizioni di uso generale riguardanti le form
*/
#define MAX_LUN_FORMTAG	80 /* dimensione massima di una singola tag */

/*
        tipi di form
*/
#define OL_FORM_INPUT_VALUE     0
#define OL_FORM_INPUT_DATA      1
                                       

/*
 tipi di linea (per line_type)
*/
#define LINE_INP        0
#define LINE_DESCR      1
#define MAX_L_DESCR   100
#define MAX_L_TAGS     15

typedef struct _linea_input {
                char tag[MAX_L_TAGS];
                char format[MAX_L_TAGS];
                char value[MAX_L_TAGS];
                char descr[MAX_L_DESCR];
                } LINEA_INPUT;

typedef struct _linea_descr {
                char descr[MAX_L_DESCR];
                } LINEA_DESCR;

typedef union {  LINEA_INPUT input;
                 LINEA_DESCR descr;
                } UNION_LINE;

typedef struct _descr_line {
                int line_type;
                UNION_LINE u;
                } DESCR_LINE;

/*
	procedure utilizzabili per la creazione e la distruzione
	dell'oggetto OlForm
*/
OlFormObject OlCreateForm();
OlFormObject OlReadForm();
int OlGetNumForms();
int OlGetNumLines();
int OlGetNumTags();
char *OlGetTags();
char *OlReadStrInp();
char *OlWriteStrInp();
char *OlGetValForm();
Boolean OlSetValForm();
char *OlGetTitle();
DESCR_LINE *OlGetLineForm();
Boolean OlDestroyForm();
char *OlGetDescr();

#endif /* _OlForm_h */

