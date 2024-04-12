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
   modulo res_edit.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)res_edit.h	5.1
*/
/*******************************************************
		file: res_edit.h
********************************************************
          File contenente parametri utilizzati 
		all'interno delle interfacce
		o delle routine
*******************************************************/

#ifndef RES_EDIT_H
#define RES_EDIT_H

#include <Rt/RtMemory.h>

/****************************************
    Definizione uscite da funzioni    
****************************************/
#define NON_ALLOCATA	1      /* Errore dalla chiamata alla calloc  */
#define OK		0      /* Ritorno giusto dalle sobroutine    */

/****************************************
    Definizione spiazzamento delle interfacce rispetto alla interfaccia 
	parent
****************************************/
#define SPIAZZAMENTO    20

/****************************************
	Definizione massimo numero di Font di default presenti
	uguale al numero di ToggleButton per la selezione dei font di default
****************************************/
#define MAX_FONTS_DEF   5

/****************************************
	Gestione del ColorViewer in base al Parent chiamante
****************************************/
#define DRAW_VER	1   /*  Gestione Draw come parent               */
#define EDITOR_VER	2   /*  Gestione Resource come parent  */
#define CONFIG_VER      3   /*  Gestione Config come parent  */

/****************************************
	Definizione delle costanti passate come ingresso alla finestra
	dei messaggi per individuare il tipo di operazione da
	effettuare in seguito alla pressione dei bottoni di OK o 
	di CANCEL
****************************************/
#define LOAD	    1	/*  Visualizzazione sulla richiesta di Load      */
#define GENERICA    2	/*  Visualizzazione Messaggio generico           */
#define BITMAP      3   /*  Visualizzazione su un Bitmap gia' presente   */ 
#define CLOSE	    4	/*  Visualizzazione sulla richiesta di Close     */
#define ICONA	    5   /*  Visualizzazione su una icona gia' presente   */

/****************************************    
	Definizione costanti per la visualizzazione della Selection Box
	per la seleziona dei bitmap,delle icone animate,dei SubSystem o
	dei Component
****************************************/
#define SEL_BITMAP	10	/*  Selezione di un bitmap     */
#define SEL_ICONA	11	/*  Selezione di una icona     */
#define SEL_SUBS 	12      /*  Selezione di un subsystem  */
#define SEL_COMP	13	/*  Selezione di un component  */

/***************************************
	Definizione costanti per la visualizzazione della lista 
	delle variabili per le icone di regolazione
***************************************/
#define ALL_VAR		20	/*  Visione di tutte le variabili  */

/*
   struttura utilizzata in VMS
   per la gestione dei processi draw e bitmap editor
*/
typedef struct {
                  Widget ogg;  /* Widget da cui ricavare l'Application Context*/
                  int ppid;    /* pid del processo padre */
                  int fpid;    /* pid del processo children */
                  XtIntervalId Itimer; /* ID del timer */
               } PROG_DATA;

#endif
