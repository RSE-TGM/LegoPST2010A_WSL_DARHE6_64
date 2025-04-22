/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/* FIND_IN_A_TEXT.C	funzione di libreria UtilX per la ricerca
			di stringhe all'interno di un Text widget   */
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)find_in_text.c	5.1\t11/10/95";
/*
   modulo find_in_text.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)find_in_text.c	5.1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/ArrowB.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/Form.h> // <--- AGGIUNGI QUESTO HEADER

#include "libutilx.h"

#define INDIETRO        0
#define AVANTI          1

/* CALLBACKS */
void cerca_stringa_text();

Widget find_in_a_text (padre,args,n,parametri)
Widget padre;
ArgList args;
int n;
Text_find_struct *parametri;
{
   int i;
   XmString cstring;
   Widget find_form;
   Widget label, find_previous, find_next;
   Widget find_text,found_label;

/* Creazione della "utility-contenitore" XmForm */
   find_form = XmCreateForm(padre,"Find",args,n);

/* Creazione della label "FIND"  */
   cstring = XmStringCreateLtoR("FIND:",XmSTRING_DEFAULT_CHARSET);
   n = 0;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNlabelString, cstring); n++;
   label = XmCreateLabel(find_form,"Find",args,n);
   XtManageChild(label);
   XmStringFree(cstring);

/* Creazione del campo editabile */
   n = 0;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNleftWidget, label); n++;
   XtSetArg(args[n], XmNleftOffset, 10); n++;
   XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNeditMode,XmSINGLE_LINE_EDIT); n++;
   XtSetArg(args[n], XmNmaxLength,50); n++;
   XtSetArg(args[n], XmNcolumns,20); n++;
   XtSetArg(args[n], XmNtraversalOn,True); n++;
   find_text = XmCreateText(find_form,"Text",args,n);
   XtManageChild(find_text);

/* Arrow button di ricerca INDIETRO */
   n = 0;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNleftWidget, find_text); n++;
   XtSetArg(args[n], XmNleftOffset, 10); n++;
   XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNarrowDirection,XmARROW_UP); n++;
   XtSetArg(args[n], XmNtraversalOn,True); n++;
   XtSetArg(args[n], XmNwidth,35); n++;
   XtSetArg(args[n], XmNuserData, INDIETRO); n++;
   find_previous = XmCreateArrowButton(find_form,"Find",args,n);
   XtManageChild(find_previous);
   XtAddCallback (find_previous,XmNactivateCallback,cerca_stringa_text,
                  parametri);

/* Arrow button di ricerca AVANTI */
   n = 0;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNleftWidget, find_previous); n++;
   XtSetArg(args[n], XmNleftOffset, 10); n++;
   XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNarrowDirection,XmARROW_DOWN); n++;
   XtSetArg(args[n], XmNtraversalOn,True); n++;
   XtSetArg(args[n], XmNwidth,35); n++;
   XtSetArg(args[n], XmNuserData, AVANTI); n++;
   find_next = XmCreateArrowButton(find_form,"Find",args,n);
   XtManageChild(find_next);
   XtAddCallback(find_next,XmNactivateCallback,cerca_stringa_text, parametri);

/* Creazione della label sull'esito della ricerca  */
   cstring = XmStringCreateLtoR
             ("                             ",XmSTRING_DEFAULT_CHARSET);
   n = 0;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNleftOffset, 10); n++;
   XtSetArg(args[n], XmNleftWidget, find_next); n++;
   XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNlabelString, cstring); n++;
   XtSetArg(args[n], XmNrecomputeSize, False); n++;
   XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING); n++;
   found_label = XmCreateLabel(find_form,"Find",args,n);
   XtManageChild(found_label);

   parametri->ID_pattern = find_text;
   parametri->ID_label   = found_label;
   parametri->ID_fnext   = find_next;
   parametri->ID_fprev   = find_previous;

   XtManageChild(find_form);
   return( find_form );
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void cerca_stringa_text(w,user,data)
Widget w;
Text_find_struct *user;
XmAnyCallbackStruct *data;
{
   int i, pos_trovato;
   XmTextPosition ins_pos;
   char *stringa, *testo, *iniz_testo, *testo_trovato;
   XmStringTable c_strings;
   static XmString notfound, nulla;
   int verso_ricerca;

   if ( notfound == NULL || nulla == NULL )
   {
      nulla    = XmStringCreateLtoR("         ",XmSTRING_DEFAULT_CHARSET);
      notfound = XmStringCreateLtoR("NOT FOUND",XmSTRING_DEFAULT_CHARSET);
   }

   stringa = XmTextGetString(user->ID_pattern);
   if (stringa == NULL || strlen(stringa) == 0)
       return;
   iniz_testo = testo = XmTextGetString (user->ID_text);
   ins_pos = XmTextGetInsertionPosition (user->ID_text);
   get_something( w, XmNuserData, (void*) &verso_ricerca);

   switch (verso_ricerca)
   {
     case INDIETRO:
          pos_trovato = 0;
          iniz_testo[ins_pos] = '\0';
          testo = NULL;
          while ( (testo_trovato = Utstrstr(iniz_testo+pos_trovato,stringa))
                  != NULL)
          {
             testo = testo_trovato;
             pos_trovato = testo_trovato - iniz_testo + strlen(stringa);
          }
     break;

     case AVANTI:
          testo = Utstrstr (iniz_testo+ins_pos,stringa);
     break;
   }

   if (testo == NULL)
       set_something(user->ID_label,XmNlabelString,(void*) notfound);
   else
   {
   /* Evidenziare con XmTextSetSelection la stringa trovata */
      XmTextSetSelection(user->ID_text,testo-iniz_testo,
                         testo-iniz_testo+strlen(stringa),CurrentTime);

   /* Se si sta effettuando la ricerca indietro, setta la posizione */
   /* del cursore all'inizio della stringa trovata */
      if (verso_ricerca == INDIETRO)
         XmTextSetInsertionPosition(user->ID_text,testo-iniz_testo);

      set_something(user->ID_label,XmNlabelString,(void*) nulla);
   }
   XtFree (stringa);
   XtFree (iniz_testo);
}

