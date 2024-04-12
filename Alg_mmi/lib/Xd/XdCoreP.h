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
   modulo XdCoreP.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdCoreP.h	5.1
*/
/* XdCoreP.h
 *         oggetto base per draw
 */
#ifndef XdCoreP_h
#define XdCoreP_h
#include <Xd/XdP.h>
#include <Xd/XdCore.h>
/******************************************************
 * Draget Class Structure
 ******************************************************/

typedef struct _DragetClassPartRec {
		Boolean initialized;     /* indica se la classe e' stata
					    inizializzata */
		String class_name;
		DragetClass superclass;
		GC gcxor;                /* gc per disegno in costruzione */
		GC gcsel;                /* gc per disegno in selezione */
		float zoom;		 /* zoom corrente */
		Cardinal draget_size;    /* dimensione record del draget */
		XdProc class_initialize;
		XdDragetProc initialize;  /* creazione del draget */
		XdDragetProc destroy;     /* distruzione del draget */
		XdMouseFunc resize;       /* ridimensionamento */
		XdMouseFunc end_resize;   /* fine ridimensionamento */
		XdMouseFunc move;         /* spostamento */
		XdMouseFunc end_move;     /* fine spostamento */
		XdDragetProc expose;      /* ridisegno */
		XdMouseFunc first_point;  /* inizio primo disegno */
		XdMouseFunc last_point;   /* fine primo disegno */
		XdMouseFunc first_draw;   /* esecuzione primo disegno */
		XdPickFunc pick;         /* True se mouse click su draget */
		XdSelectProc select;      /* seleziona il draget */
		XdDragetProc clear;     /* forza un clear area relativo 
					   all'oggetto (e comprendente la
					   zona utilizzata per visualizzare
					   la selezione) */
		XdDragetProc crea_regions; /* creazione delle regions per
                			     selezioni e spostamenti */
		XdDragetProc delete_regions; /* cancellazione delle regions */
		XdReadFunc read;        /* lettura da file */
		XdWriteFunc write;       /* scrittura su file */
		XdGetSizeProc get_size;  /* restituisce le dimensioni dello
					   oggetto in termine degli estremi
					   del minimo rettangolo circoscritto
					  */
		XdModifyProc modify;     /* sposta e modifica l'oggetto */
		XdCopyProc copy;         /* copia un draget in memoria */
#ifdef XPRINTER_USED
		XdDragetProc print;      /* stampa con xprinter */
#endif
		} DragetClassPart;

typedef struct _DragetClassRec {
		DragetClassPart xdcore_class;
		} DragetClassRec, XdCoreClassRec;

extern XdCoreClassRec xdCoreClassRec;
/*****************************************************
 * Draget data structures
 *****************************************************/

typedef struct _XdCorePart {
	DragetClass draget_class;
	Widget wid;  /* widget su cui disegnare */
	int step;                /* per snap */
	Position x,y;
	Region select_region; /* Region di selezione */
	Cardinal num_resize_regions;
	Region *resize_regions;
	Cardinal num_move_regions;
	Region *move_regions;
	Boolean is_first; /* True se primo disegno oggetto */
	Boolean managed; /* se True l'oggetto e' stato completato */
	Boolean moving; /* l'oggetto e' in fase di move */
	Cardinal num_move; /* indice della regione che ha provocato
      				il move */
	Boolean resizing;  /* l'oggetto e' in fase di resizing */
	Cardinal num_resize; /* indice della regione che ha provocato il 
				resizing */
	Boolean sensitive;
	Boolean selected;
	Boolean filled;
        GC gc;
	GC gc_bg;
        GC gcxor;
	} XdCorePart;

typedef struct _DragetRec {
		XdCorePart xdcore;
		} DragetRec,XdCoreRec;

#endif /* XdCoreP_h */
