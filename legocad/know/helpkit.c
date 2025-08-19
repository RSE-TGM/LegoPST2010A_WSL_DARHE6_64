/**********************************************************************
*
*       C Source:               helpkit.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Feb 26 18:27:27 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: helpkit.c-4 %  (%full_filespec: helpkit.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)helpkit.c	1.15\t11/13/95";
/*
        Fine sezione per SCCS
*/


/* "helpkit.c"
* Scopo: un semplice sotto-sistema di aiuti in linea.
* Accesso: vedi "helpkit.h"
* Autore: C.Lusso (CISE) 1995/01/...
*/

#include <stdio.h>
#include <ctype.h>
#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Xm/SelectioB.h>
#include <Xm/List.h>

#include "helpkit.h"

/* prototipi di funzioni pubbliche:
* ---------------------------------
* - helpkit_propInfo
*	(vedi descrizione in "helpkit.h").
* ---------------------------------
* - helpkit_readInfo
*	Scopo: legge da un file ASCII una pagina di informazioni
*		(vedi Nota 1 sotto), oppure genera una pagina assunta.
*	Argomenti:	(I=input, O=output, W=work)
* String zHfile,	(I) nome del file ove reperire la pagina
* String zHname)	(I) nome identificativo della pagina
*	Ritorna:
* HELPKIT_INFO *pInfo	puntatore alla pagina letta
*
*	Nota 1: il file e' organizzato in linee di testo (max 80 caratteri),
*		miste a 'direttive' di controllo (':' in col. 1):
*			:page	zHname	inizio pagina di nome 'zHname'
*			:d	title	inizio dettaglio di nome 'title'
*			:epage		fine pagina
*			:(blank)	commento
*		(linee con direttive non riconosciute sono ignorate)
* ---------------------------------
* - helpkit_assocInfo
*	Scopo: associa ad un Widget una SelectionBox(Dialog)
*		con i titoli (e descrizioni) disponibili della pagina.
*	Argomenti:	(I=input, O=output, W=work)
* Widget parent,	(I) Motif widget genitore cui associare la pagina
* HELPKIT_INFO *pInfo)	(I) puntatore alla pagina (se NULL, nulla avviene)
*	Ritorna:
* Widget wInfo		utile per XtManageChild()
*
*	Nota 1: usare 'helpkit_assocInfo()' alla creazione della finestra,
*		indi usare XtManageChild(wInfo) dove appropriato.
*	Nota 2: dopo la chiamata, la pagina non e' piu' necessaria.
* ---------------------------------
* - helpkit_freeInfo
*       Scopo: libera la memoria impegnata da una pagina di informazioni.
*       Argomenti:      (I=input, O=output, W=work)
* HELPKIT_INFO *pInfo)	(I) puntatore alla pagina (se NULL, nulla avviene)
*       Ritorna:
* - (void)
*
*       Nota 1: usare 'helpkit_freeInfo()' dopo 'helpkit_assocInfo()'.
* ---------------------------------
*/

/* tipi di dati privati:
* ----------------------
*/
#define HELPKIT_MAXLINE	80
enum {
 eH_comment,
 eH_page,
 eH_d,
 eH_epage,
 enHctl,
};
typedef struct s_line {
 String line;
 struct s_line *prev;
} HELPKIT_WLINE;
typedef struct s_descr {
 String head;
 String *descr;
 int cLines;
 struct s_descr *prev;
} HELPKIT_WDESCR;

/* dati privati:
* --------------
*/
static char
 hDirective	= ':';
static String
 sazHctl[enHctl] = {
  " ",
  "page",
  "d",
  "epage",
 };
static String
 sazHelpInfo[] = {
  "helpkit* Information sub-system",
  "",
  "Help Info shows as a page of a book, with text",
  "split in one or more detailed descriptions.",
  "The list shows all available titles.",
  "",
  "Buttons       Usage",
  " OK        display the selected description",
  " Apply     like OK, the Info Dialog remains",
  " Cancel    close the Info Dialog",
 },
 azNoDescr[] = {
  "No information was associated to this Motif widget.",
  "",
  "Contact your Application Administrator for details.",
 },
 azNoLines[] = {
  "(No description available under this title)",
 };

/* funzioni ausiliarie (private):
* -------------------------------
*/
static XtCallbackProc
 helpkit_InfoCB(),
 helpkit_freeDataCB(),
 helpkit_autoDestroyCB();

/* corpo delle funzioni pubbliche:
* --------------------------------
*/

Widget helpkit_propInfo(
 Widget parent,
 String zHfile,
 String zHname)
{
 HELPKIT_INFO *pInfo;
 Widget wInfo;
   pInfo = helpkit_readInfo( zHfile, zHname);
   wInfo = helpkit_assocInfo( parent, pInfo);
   helpkit_freeInfo( pInfo);
   return wInfo;
}

HELPKIT_INFO *helpkit_readInfo(
 String zHfile,
 String zHname)
{
 static Boolean
  o1st = True;
 static int
  alHctl[enHctl];
 static char
  hNewline	= '\n',
  hNull		= '\0';
 Boolean ab[enHctl];
 char line[HELPKIT_MAXLINE], *z;
 String head;
 int kH, cDescr, cLines;
 HELPKIT_INFO *pInfo;
 FILE *pHfile;
 HELPKIT_WLINE
  *pline,
  *pl_prev;
 HELPKIT_WDESCR
  *pdescr,
  *pd_prev;
 int i;
   if (o1st) {
      for (kH=0; kH<enHctl; kH++)
         alHctl[kH] = strlen( sazHctl[kH]);
      o1st = False;
   };
   for (kH=0; kH<enHctl; kH++)
      ab[kH] = False;
   pInfo = (HELPKIT_INFO *) XtMalloc( sizeof(HELPKIT_INFO));
   pHfile = fopen( zHfile, "r");
   if (pHfile) {
      while (1) {
         fgets( line, HELPKIT_MAXLINE, pHfile);
         if (! feof( pHfile)) {
            if (z = strchr( line, hNewline))
               *z = hNull;
            else
               while (fgetc( pHfile) != hNewline)
                  ;
            if (line[0] == hDirective) {
               for (kH=0; kH<enHctl && line[1]; kH++)
                  if (strncmp( &line[1], sazHctl[kH], alHctl[kH]) == 0)
                     break;
            } else
               kH = enHctl +1;
            if (kH == eH_comment
             || !ab[eH_page] && kH != eH_page)
               continue;
         } else {
            if (ab[eH_page])
               kH = eH_epage;
            else
               break;
         }
         do {
            switch (kH) {
            case eH_comment:
               break;
            case eH_page:
               if (!ab[eH_page]) {
                  z = &line[1 + alHctl[kH]];
                  while (*z && isspace(*z))
                     z++;
                  if (strcmp( z, zHname) == 0) {
                     /* nome Ok, apre pagina, e anche 1a descrizione */
                     ab[eH_page] = True;
                     kH = eH_d;
                  } else
                     kH = eH_comment;
               } else
                  kH = eH_epage;
               break;
            case eH_d:
               if (ab[eH_d]) {
                  /* chiude descrizione corrente */
                  pdescr = (HELPKIT_WDESCR *) XtMalloc( sizeof(HELPKIT_WDESCR));
                  if (!cLines) {
                     cLines = XtNumber( azNoLines);
                     for (i=0; i<cLines; i++) {
                        pline = (HELPKIT_WLINE *) XtMalloc( sizeof(HELPKIT_WLINE));
                        pline->line = strdup( azNoLines[i]);
                        pline->prev = pl_prev;
                        pl_prev = pline;
                     }
                  }
                  pdescr->head = head;
                  pdescr->descr = (String *) XtCalloc( cLines, sizeof(String));
                  pdescr->cLines = cLines;
                  while (cLines--) {
                     pdescr->descr[cLines] = pline->line;
                     pl_prev = pline->prev;
                     XtFree( (char *) pline);
                     pline = pl_prev;
                  }
                  pdescr->prev = pd_prev;
                  pd_prev = pdescr;
                  cDescr++;
               }
               if (!ab[eH_epage]) {
                  /* apre nuova descrizione */
                  if (!ab[eH_d]) {
                     ab[eH_d] = True;
                     cDescr = 0;
                     head = strdup( zHname);
                     pd_prev = NULL;
                  } else {
                     z = &line[1 + alHctl[kH]];
                     while (*z && isspace(*z))
                        z++;
                     if (!*z)
                        sprintf( z = line, "(%d)", cDescr);
                     head = strdup( z);
                  }
                  cLines = 0;
                  pl_prev = NULL;
                  kH = eH_comment;
               } else {
                  ab[eH_d] = False;
                  kH = eH_epage;
               }
               break;
            case eH_epage:
               ab[eH_epage] = True;
               /* chiude descrizione ... */
               if (ab[eH_d]) {
                  kH = eH_d;
               } else {
               /* ... e chiude la pagina */
                  pInfo->cDescr = cDescr;
                  pInfo->azHeads = (String *) XtCalloc( cDescr, sizeof(String));
                  pInfo->aazPage = (String **) XtCalloc( cDescr, sizeof(String *));
                  pInfo->acLines = (int *) XtCalloc( cDescr, sizeof(int));
                  while (cDescr--) {
                     pInfo->azHeads[cDescr] = pdescr->head;
                     pInfo->aazPage[cDescr] = pdescr->descr;
                     pInfo->acLines[cDescr] = pdescr->cLines;
                     pd_prev = pdescr->prev;
                     XtFree( (char *) pdescr);
                     pdescr = pd_prev;
                  }
                  kH = eH_comment;
               }
               break;
            case enHctl:
               kH = eH_comment;
               break;
            default:
               pline = (HELPKIT_WLINE *) XtMalloc( sizeof(HELPKIT_WLINE));
               pline->line = strdup( line);
               cLines++;
               pline->prev = pl_prev;
               pl_prev = pline;
               kH = eH_comment;
              break;
            }
         } while (kH != eH_comment);
         if (ab[eH_epage])
            break;
      }
      fclose( pHfile);
   }
   if (!ab[eH_epage]) {
   /* carica una Info con 1 sola descrizione */
      pInfo->cDescr = 1;
      pInfo->azHeads = (String *) XtCalloc( 1, sizeof(String));
      pInfo->azHeads[0] = strdup( zHname);
      pInfo->aazPage = (String **) XtMalloc( sizeof(String *));
      cLines = XtNumber( azNoDescr);
      pInfo->aazPage[0] = (String *) XtCalloc( cLines, sizeof(String));
      for (i=0; i<cLines; i++)
         pInfo->aazPage[0][i] = strdup( azNoDescr[i]);
      pInfo->acLines = (int *) XtCalloc( 1, sizeof(int));
      pInfo->acLines[0] = cLines;
   }
   return pInfo;
}

Widget helpkit_assocInfo(
 Widget parent,
 HELPKIT_INFO *pInfo)
{
 static String
  szInfo = " - Info";
 String zTitle;
 XmStringTable
  axsHeads,
  axsDescr;
 XmString xsList;
 Arg a[5];
 Cardinal n;
 Widget wInfo, w;
 int cDescr=pInfo->cDescr, i;
   zTitle = (String) XtMalloc( strlen( pInfo->azHeads[0]) + strlen( szInfo) +1);
   strcpy( zTitle, pInfo->azHeads[0]);
   strcat( zTitle, szInfo);
   /* costruisce SelectionDialog */
   axsHeads = (XmStringTable) XtCalloc( cDescr, sizeof(XmString));
   axsDescr = (XmStringTable) XtCalloc( cDescr, sizeof(XmString));
   for (i=0; i<cDescr; i++) {
      axsHeads[i] = XmStringCreateSimple( pInfo->azHeads[i]);
      axsDescr[i] = helpkit_buildString( pInfo->aazPage[i], pInfo->acLines[i]);
   }
   xsList = XmStringCreateSimple( "Descriptions:");
   n=0;
   XtSetArg( a[n], XmNlistItemCount, cDescr); n++;
   XtSetArg( a[n], XmNlistItems, axsHeads); n++;
   XtSetArg( a[n], XmNlistLabelString, xsList); n++;
   XtSetArg( a[n], XmNuserData, axsDescr); n++;
   XtSetArg( a[n], XmNtitle, zTitle); n++;
   wInfo = XmCreateSelectionDialog( parent, zTitle, a, n);
   XtUnmanageChild( XmSelectionBoxGetChild( wInfo, XmDIALOG_SELECTION_LABEL));
   XtUnmanageChild( XmSelectionBoxGetChild( wInfo, XmDIALOG_TEXT));
   XtAddCallback( wInfo, XmNapplyCallback, (XtCallbackProc)helpkit_InfoCB,  NULL);
   XtAddCallback( wInfo, XmNcancelCallback, (XtCallbackProc)helpkit_InfoCB,  NULL);
   XtAddCallback( wInfo, XmNokCallback, (XtCallbackProc)helpkit_InfoCB,  NULL);
   XtAddCallback( wInfo, XmNhelpCallback, (XtCallbackProc)helpkit_InfoCB,  NULL);
   XtAddCallback( wInfo, XmNmapCallback, (XtCallbackProc)helpkit_InfoCB, NULL);
   XtAddCallback( wInfo, XmNdestroyCallback, (XtCallbackProc)helpkit_freeDataCB, NULL);
   XmListSelectPos( XmSelectionBoxGetChild( wInfo, XmDIALOG_LIST), 1, False);
   for (i=0; i<cDescr; i++)
      XmStringFree( axsHeads[i]);
   XtFree( (char *) axsHeads);
   XtFree( zTitle);
   return wInfo;
}

void helpkit_freeInfo(
 HELPKIT_INFO *pInfo)
{
   if (pInfo) {
    int iD, iL;
      for (iD=0; iD<pInfo->cDescr; iD++) {
         XtFree( pInfo->azHeads[iD]);
         for (iL=0; iL<pInfo->acLines[iD]; iL++)
            XtFree( pInfo->aazPage[iD][iL]);
         XtFree( (char *) pInfo->aazPage[iD]);
      }
      XtFree( (char *) pInfo->azHeads);
      XtFree( (char *) pInfo->aazPage);
      XtFree( (char *) pInfo->acLines);
      XtFree( (char *) pInfo);
   }
}

XmString helpkit_buildString(
 String *azDescr,
 int cLinee)
{
/* costruisce una Stringa-Motif composta da molte linee */
 XmString xsTot, xs1, xs2, xsSep = XmStringSeparatorCreate();
 int i;
   xsTot = XmStringCreateSimple( (cLinee>0) ? azDescr[0] : "");
   for (i=1; i<cLinee; i++) {
      xs1 = XmStringConcat( xsTot, xsSep);
      XmStringFree( xsTot);
      xs2 = XmStringCreateSimple( azDescr[i]);
      xsTot = XmStringConcat( xs1, xs2);
      XmStringFree( xs1);
      XmStringFree( xs2);
   }
   XmStringFree( xsSep);
   return xsTot;
}

Widget helpkit_displayMsg(
 Widget parent,
 XmString xsTitle,
 XmString xsMsg,
 Boolean noResize,
 Boolean autoDestroy)
{
/* crea un InformationDialog che espone un messaggio (descrizione, o help) */
 Arg a[3];
 Cardinal n;
 Widget wDlg;
   n=0;
   XtSetArg( a[n], XmNmessageString, xsMsg); n++;
   XtSetArg( a[n], XmNdialogTitle, xsTitle); n++;
   XtSetArg( a[n], XmNnoResize, noResize); n++;
   wDlg = XmCreateInformationDialog( parent, "Dlg", a, n);
   XtUnmanageChild( XmMessageBoxGetChild( wDlg, XmDIALOG_CANCEL_BUTTON));
   XtUnmanageChild( XmMessageBoxGetChild( wDlg, XmDIALOG_HELP_BUTTON));
   if (autoDestroy)
      XtAddCallback( wDlg, XmNunmapCallback, (XtCallbackProc)helpkit_autoDestroyCB, NULL);
   XtManageChild( wDlg);
   return wDlg;
}

/* corpo delle funzioni private:
* ------------------------------
*/

static XtCallbackProc helpkit_InfoCB(
 Widget w_,
 XtPointer pC,
 XmAnyCallbackStruct *pA)
{
/* risponde ai bottoni del SelectionDialog */
 static String
  szHelp = "Help for Info";
 XmString
  xsTitle,
  xsMsg;
 XmStringTable
  axsSel,
  axsDescr;
 Arg a[4];
 Cardinal n;
 Widget wList;
 int cDescr, *aiPos, cPos;
   switch (pA->reason) {
   case XmCR_MAP:
      n=0;
      XtSetArg( a[n], XmNlistItemCount, &cDescr); n++;
      XtGetValues( w_, a, n);
      if (cDescr > 1)
         break;
      else
         ;
   case XmCR_OK:
   case XmCR_APPLY:
      wList = XmSelectionBoxGetChild( w_, XmDIALOG_LIST);
      if (XmListGetSelectedPos( wList, &aiPos, &cPos)) {
         n=0;
         XtSetArg( a[n], XmNselectedItems, &axsSel); n++;
         XtGetValues( wList, a, n);
         n=0;
         XtSetArg( a[n], XmNuserData, &axsDescr); n++;
         XtGetValues( w_, a, n);
         helpkit_displayMsg( w_, axsSel[0], axsDescr[aiPos[0]-1], True, True);
         XtFree( (char *) aiPos);
      }
      break;
   case XmCR_CANCEL:
      break;
   case XmCR_HELP:
      xsTitle = XmStringCreateSimple( szHelp);
      xsMsg = helpkit_buildString( sazHelpInfo, XtNumber( sazHelpInfo));
      helpkit_displayMsg( w_, xsTitle, xsMsg, True, True);
      XmStringFree( xsTitle);
      XmStringFree( xsMsg);
      break;
   default:
     break;
   }
}

static XtCallbackProc helpkit_freeDataCB(
 Widget w_,
 XtPointer pC,
 XtPointer pA)
{
/* libera userData del SelectionDialog distrutto */
 XmStringTable axsDescr;
 Dimension cDescr;
 Arg a[2];
 Cardinal n;
   n=0;
   XtSetArg( a[n], XmNuserData, &axsDescr); n++;
   XtSetArg( a[n], XmNlistItemCount, &cDescr); n++;
   XtGetValues( w_, a, n);
   for (n=0; n<cDescr; n++)
      XmStringFree( axsDescr[n]);
   XtFree( (char *) axsDescr);
}

static XtCallbackProc helpkit_autoDestroyCB(
 Widget w_,
 XtPointer pC,
 XtPointer pA)
{
/* auto-distrugge un Widget (figlio di una Shell ...) */
   XtDestroyWidget( XtParent( w_));
}


/* fine "helpkit.c" */
