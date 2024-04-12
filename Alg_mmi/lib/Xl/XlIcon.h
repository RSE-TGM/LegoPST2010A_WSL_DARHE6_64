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
   modulo XlIcon.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlIcon.h	5.1
*/
/*
 * XlIcon.h - file di include pubblico per l'utilizzo del widget
 *             icon
 */
#ifndef _XlIcon_h
#define _XlIcon_h

/*
 nomi di risorse utilizzate internamente al icon
 */
#define XlNicon  "icon"
#define XlCIcon  "Icon"
#define XlDicon  "Icon file"
#define XlNnomeFile "nomeFile"
#define XlCNomeFile "NomeFile"
#define XlDnomeFile "Nome del file"



/* costanti utilizzabili per settare il tipo di XlIndic */


/* declare the class constant */
extern WidgetClass xlIconWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Icon */
typedef struct _XlIconClassRec *XlIconWidgetClass;
typedef struct _XlIconRec *XlIconWidget;

#endif /* _XlIcon_h */

