/**********************************************************************
*
*       C Header:               nn.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:07:59 1996 %
*
**********************************************************************/

/* File: "nn.h"
 * Scopo:
 *   dichiarazioni utili per la pagina "nn".
 *     La pagina "nn", invocata dalla fase "calcstaz" del sistema "LEGOCAD",
 *   consente di marcare "note" o "non-note" le variabili di un modello "LEGO".
 *     La pagina "nn" si basa sui seguenti sorgenti C:
 *   .  nnEdit.c
 *   .  nnFilter.c
 *   .  nnGraph.c
 *   .  nnValues.c
 *   .  nnWorks.c
 * Autore: C.Lusso (CISE) 1994/12/..
 */

#ifndef _NN_H
#define _NN_H

/* definizioni: */
/* (queste potrebbero essere definite in 'f03.h' ...  */
#define LEN_NOBLC	8
#define LEN_NOM_BLOC	80
#define LEN_SIVARI	8
#define LEN_NOM_SIVARI	100
typedef char (*ARY_NOBLC)	[LEN_NOBLC+1];
typedef char (*ARY_NOM_BLOC)	[LEN_NOM_BLOC+1];
typedef char (*ARY_SIVARI)	[LEN_SIVARI+1];
typedef char (*ARY_NOM_SIVARI)	[LEN_NOM_SIVARI+1];

/* variabili:
 *   int
 *	cVars   conta tutte le variabili (= neqsis+nu)
 *	cMark   conta le Marcature (out-var "note", inp-var "non-note")
 *   char
 *	*aMark  array [cVars] di Marcature (=1 var Marcata, =0 no)
 * Nota: le var "note" consistono di out-var Marcate + inp-var non-Marcate;
 *	il sistema risulta bilanciato sse cMark == nu.
 */
/*
     int
	cVars,
	cMark;
     char
	*aMark;
*/

/* prototipi di funzioni (in nnWorks.c) */

#endif/*_NN_H*/
