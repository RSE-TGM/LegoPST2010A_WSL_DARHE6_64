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
   modulo XlBitmapP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlBitmapP.h	5.1
*/
/*
   modulo BitmapP.h
   tipo 
   release 1.1
   data 6/16/93
   reserved @(#)BitmapP.h	1.1
*/
/*
 * BitmapP.h - definizioni private per l'oggetto Bitmap
 */ 
#ifndef _XlBitmapP_h
#define _XlBitmapP_h
/*
 Inclusione degli heder file privati delle classi superiori
*/
#include <Xm/XmP.h>
#include <Xm/XmP.h>
#include <Xl/XlP.h>
/*
 Inclusione dell'header file pubblico
*/
#include "XlBitmap.h"
/*
 Strutture relative alla nuova Classe
 */
typedef struct {
	int empty;
	} XlBitmapClassPart;
/*
 Dichiarazione del record completo di classe
 */
typedef struct _XlBitmapClassRec {
	 CoreClassPart     core_class;
	 XlCoreClassPart   xlcore_class;
	 XlBitmapClassPart    xlbitmap_class;
	} XlBitmapClassRec;

extern XlBitmapClassRec xlBitmapClassRec;

/*
 Nuovi campi per il record del widget XlBitmap
 */
typedef struct {
	/* risorse  */
	Pixel color_norm;
	char * nome_file_bitmap; /* nome del file contenete il bitmap*/
	char * component;      /* nome del componente    */
        char * subsystem;       /* nome del sottosistema  */

	
	/*
		struttura per la gestione del cambio colore
	*/
	CAMBIO_COLORE cambio_colore;

        /*
          variabili di stato (privato)
        */
        GC norm_gc;           /* GC nuormal  */
        GC clear_gc;          /* GC sbiancamento iniziale bitmap */
        GC oldGC;             /* stato del GC visualizzato */
	Pixmap bitmap_norm;   /* pixmap a un piano */
	} XlBitmapPart;
/*
 Dichiarazione completa del record per instanziazione
 */
typedef struct _XlBitmapRec {
	CorePart   core;
	XlCorePart xlcore;
	XlBitmapPart  bitmap;
	} XlBitmapRec;


#endif /* _XlBitmap */
