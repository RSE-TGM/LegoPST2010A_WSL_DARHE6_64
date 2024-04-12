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
   modulo XlBitmap.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlBitmap.h	5.1
*/
/*
 * XlBitmap.h - file di include pubblico per l'utilizzo del widget
 *             bitmap
 */
#ifndef _XlBitmap_h
#define _XlBitmap_h

/*
 nomi di risorse utilizzate internamente al bitmap
 */
#define XlNbitmap  "bitmap"
#define XlCBitmap  "Bitmap"
#define XlDbitmap  "Bitmap file"
#define XlNnomeFile "nomeFile"
#define XlCNomeFile "NomeFile"
#define XlDnomeFile "Nome del file"



/* costanti utilizzabili per settare il tipo di XlIndic */


/* declare the class constant */
extern WidgetClass xlBitmapWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Bitmap */
typedef struct _XlBitmapClassRec *XlBitmapWidgetClass;
typedef struct _XlBitmapRec *XlBitmapWidget;

#endif /* _XlBitmap_h */

