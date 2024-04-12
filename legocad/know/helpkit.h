/**********************************************************************
*
*       C Header:               helpkit.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:07:45 1996 %
*
**********************************************************************/

/* "helpkit.h"
* Scopo: dichiarazioni pubbliche per accedere a "helpkit".c,
*	un semplice sotto-sistema di Aiuti in linea in ambiente X-Motif.
* Note: far precedere '#include <Xm/...>';
*	per ulteriori dettagli vedi sotto.
* Autore: C.Lusso (CISE) 1995/01/...
*/

#ifndef _HELPKIT_H_
#define _HELPKIT_H_

/* norme generali:
* ----------------
* 1: le informazioni di Aiuto si basano su testi esponibili (residenti
*	in un file ASCII esterno all'applicazione), e su un meccanismo di
*	accesso (fornito da questo "helpkit");
* 2. il file ASCII contiene 'direttive' (marcate con ':' in col. 1) che
*	organizzano il testo in 'pagine', suddivise in una descrizione
*	'generale' seguita da descrizioni di 'dettaglio';
* 3: una 'pagina' si associa a una finestra Motif di classe Manager (o sue
*	sotto-classi) fin dalla creazione, e compare a video pigiando il
*	tasto F1 (vedi 'helpCallback') oppure una voce di menu o bottone
*	dedicati (vedi 'activateCallback') chiamando XtManageChild.
*/

/* dichiarazioni riservate a main():
* ----------------------------------
*/
#ifdef  HELPKIT_MAIN
#define HELPKIT_OPTION		"-hfile"
#define HELPKIT_OPTIONSPEC	"*hfile"
/* esempio:
*	static XrmOptionDescRec options[] = {
*	 { HELPKIT_OPTION, HELPKIT_OPTIONSPEC, XrmoptionSepArg, NULL },
*	 { ... },
*	};
*/
#define HELPKIT_RESNAME		"hfile"
#define HELPKIT_RESCLASS	"Hfile"
/* esempio:
*	static XtResource resources[] = {
*	 { HELPKIT_RESNAME, HELPKIT_RESCLASS, XtRString, sizeof(String),
*	    XtOffset( ApplicationDataPtr, zHfile), XtRString, NULL },
*	 { ... },
*	};
*/
/* fine dichiarazioni riservate a main().
* ---------------------------------------
*/
/* esempio:
*	typedef struct {
*	   String zHfile;
*	   ...
*	} ApplicationDataStruct, *ApplicationDataPtr;
*       static XrmOptionDescRec options[] = ...
*       static XtResource resources[] = ...
*	main( argc, argv)
*	{
*	 ApplicationDataStruct appData;
*	   ...
*	   UxTopLevel = XtAppInitialize(&UxAppContext, "program",
*	    options, XtNumber( options), &argc, argv, NULL, NULL, 0);
*	   XtGetApplicationResources( UxTopLevel, &appData,
*	    resources, XtNumber( resources), NULL, 0);
*	   ...
*	}
*/
#endif/*HELPKIT_MAIN*/


/* tipi di dati pubblici:
* -----------------------
* HELPKIT_INFO		contenitore delle informazioni testuali
*	Struttura:
* int cDescr;		conta descrizioni (=array di 'linee') della pagina
* String *azHeads;	titoli delle descrizioni, il 1. e' '(general)'
* String **aazPage;	'pagina' (=array di 'sezioni') di informazioni
* int *acLines;		(array di) conta linee (=stringhe) delle descrizioni
* -----------------------
*/

typedef struct {
 int cDescr;
 String *azHeads;
 String **aazPage;
 int *acLines;
} HELPKIT_INFO;

/* prototipi di funzioni pubbliche:
* ---------------------------------
* - helpkit_propInfo
*	Scopo: legge da un file ASCII una pagina di informazioni
*		e la associa al Motif widget chiamante (vedi Nota 1).
*	Argomenti:	(I=input, O=output, W=work)
* Widget parent,	(I) Motif widget genitore a cui associare la pagina
* String zHfile,	(I) nome del file ove reperire la pagina
* String zHname)	(I) nome identificativo della pagina
*	Ritorna:
* Widget wInfo		utile per XtManageChild()
*
*	Nota 1: chiama in successione le seguenti funzioni pubbliche:
*		helpkit_readInfo(),
*		helpkit_assocInfo(),
*		helpkit_freeInfo(),
*		sollevando il chiamante da impegni di dati in memoria etc.
* ---------------------------------
* - helpkit_readInfo
*	(vedi descrizione in "helpkit.c").
* ---------------------------------
* - helpkit_assocInfo
*	(vedi descrizione in "helpkit.c").
* ---------------------------------
* - helpkit_freeInfo
*	(vedi descrizione in "helpkit.c").
* ---------------------------------
* - helpkit_buildString
*	(utilita): costruire una Stringa Motif da un array di stringhe
*	Argomenti:	(I=input, O=output, W=work)
* String *azDescr,	array di stringhe
* int cLines)		numero di elementi dell'array
*	Ritorna:
* XmString xsTot	stringa Motif risultante
* ---------------------------------
* - helpkit_displayMsg
*	(utilita): costruire un InformationDialog (solo bottone OK)
*	Argomenti:	(I=input, O=output, W=work)
* Widget parent,	(I) Motif widget genitore
* XmString xsTitle,	(I) titolo del Dialogo
* XmString xsMsg,	(I) testo del messaggio
* Boolean noResize,	(I) opzione: cornice sottile o normale
* Boolean autoDestroy)	(I) opzione: auto-distruggi (anche DialogShell) o no
*	Ritorna:
* Widget wgtMsg		widget ritornato da XmCreate...()
* ---------------------------------
*/

Widget helpkit_propInfo(
 Widget parent,
 String zHfile,
 String zHname)
;
HELPKIT_INFO *helpkit_readInfo(
 String zHfile,
 String zHname)
;
Widget helpkit_assocInfo(
 Widget parent,
 HELPKIT_INFO *pInfo)
;
void helpkit_freeInfo(
 HELPKIT_INFO *pInfo)
;
XmString helpkit_buildString(
 String *azDescr,
 int cLines)
;
Widget helpkit_displayMsg(
 Widget parent,
 XmString xsTitle,
 XmString xsMsg,
 Boolean noResize,
 Boolean autoDestroy)
;

/* fine "helpkit.h" */
#endif/*_HELPKIT_H_*/
