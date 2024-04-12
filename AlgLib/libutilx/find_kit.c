/**********************************************************************
*
*       C Source:               find_kit.c
*       Subsystem:              2
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue May 30 16:03:25 2006 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: find_kit.c-2 %  (%full_filespec: find_kit.c-2:csrc:2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)find_kit.c	5.1\t11/10/95";
/*
   modulo find_kit.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)find_kit.c	5.1
*/
/*  FIND_KIT.C 		compone una serie di widget (1 Label, 1 Text,
			2 Arrow Button) per l'attivita' di ricerca di
			una stringa

		padre	widget all'interno del quale deve comparire
			il find
		args	array di tipo Arg per argomenti XToollkit
		nargs	numero di argomenti
	    parametri	puntatore ad una struttura Find_struct
***/

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <Mrm/MrmAppl.h>
#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Xm/Text.h>
#include <Xm/ArrowB.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/Label.h>

#include "libutilx.h"

#define AVANTI		1
#define INDIETRO	0

/* CALLBACKS */
void cerca_stringa_kit();

Widget find_kit (padre,args,n,parametri)
Widget padre;
Arg args[];
int n;
Find_struct *parametri;
{
   Arg largs[15];
   Cardinal narg;
   int i;
   XmString cstring;
   Widget find_form;
   Widget label, find_previous, find_next;
   Widget find_text,found_label;
              
   Pixel drawing_background;

/* Creazione della "utility-contenitore" XmForm */
   find_form = XmCreateForm(padre,"Find",args,n);
   XtManageChild(find_form);

/* Creazione della label "FIND"  */
   cstring = XmStringCreateLtoR("FIND:",XmSTRING_DEFAULT_CHARSET);
   narg = 0;
   XtSetArg(largs[narg], XmNleftAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNbottomAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNtopAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNlabelString, cstring); narg++;
   label = XmCreateLabel(find_form,"Find",largs,narg);
   XtManageChild(label);
   XmStringFree(cstring);

/* Creazione del campo editabile */
   narg = 0;
   XtSetArg(largs[narg], XmNleftAttachment, XmATTACH_WIDGET); narg++;
   XtSetArg(largs[narg], XmNleftWidget, label); narg++;
   XtSetArg(largs[narg], XmNleftOffset, 10); narg++;
   XtSetArg(largs[narg], XmNbottomAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNtopAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNeditMode,XmSINGLE_LINE_EDIT); narg++;
   XtSetArg(largs[narg], XmNmaxLength,50); narg++;
   XtSetArg(largs[narg], XmNcolumns,20); narg++;
   XtSetArg(largs[narg], XmNtraversalOn,True); narg++;
   find_text = XmCreateText(find_form,"Text",largs,narg);
   XtManageChild(find_text);

   drawing_background=0x277676;
   set_something(find_text,XmNbackground,drawing_background);


/* Arrow button di ricerca INDIETRO */
   narg = 0;
   XtSetArg(largs[narg], XmNleftAttachment, XmATTACH_WIDGET); narg++;
   XtSetArg(largs[narg], XmNleftWidget, find_text); narg++;
   XtSetArg(largs[narg], XmNleftOffset, 10); narg++;
   XtSetArg(largs[narg], XmNbottomAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNtopAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNarrowDirection,XmARROW_UP); narg++;
   XtSetArg(largs[narg], XmNtraversalOn,True); narg++;
   XtSetArg(largs[narg], XmNwidth,35); narg++;
   XtSetArg(largs[narg], XmNuserData, INDIETRO); narg++;
   find_previous = XmCreateArrowButton(find_form,"Find",largs,narg);
   XtManageChild(find_previous);
   XtAddCallback (find_previous,XmNactivateCallback,cerca_stringa_kit, parametri);
 
/* Arrow button di ricerca AVANTI */
   narg = 0;
   XtSetArg(largs[narg], XmNleftAttachment, XmATTACH_WIDGET); narg++;
   XtSetArg(largs[narg], XmNleftWidget, find_previous); narg++;
   XtSetArg(largs[narg], XmNleftOffset, 10); narg++;
   XtSetArg(largs[narg], XmNbottomAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNtopAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNarrowDirection,XmARROW_DOWN); narg++;
   XtSetArg(largs[narg], XmNtraversalOn,True); narg++;
   XtSetArg(largs[narg], XmNwidth,35); narg++;
   XtSetArg(largs[narg], XmNuserData, AVANTI); narg++;
   find_next = XmCreateArrowButton(find_form,"Find",largs,narg);
   XtManageChild(find_next);
   XtAddCallback(find_next,XmNactivateCallback,cerca_stringa_kit, parametri);

/* Creazione della label sull'esito della ricerca  */
   cstring = XmStringCreateLtoR
             ("                              ",XmSTRING_DEFAULT_CHARSET);
   narg = 0;
   XtSetArg(largs[narg], XmNleftAttachment, XmATTACH_WIDGET); narg++;
   XtSetArg(largs[narg], XmNleftOffset, 10); narg++;
   XtSetArg(largs[narg], XmNleftWidget, find_next); narg++;
   XtSetArg(largs[narg], XmNbottomAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNtopAttachment, XmATTACH_FORM); narg++;
   XtSetArg(largs[narg], XmNlabelString, cstring); narg++;
   XtSetArg(largs[narg], XmNrecomputeSize, False); narg++;
   XtSetArg(largs[narg], XmNalignment, XmALIGNMENT_BEGINNING); narg++;
   found_label = XmCreateLabel(find_form,"Find",largs,narg);
   XtManageChild(found_label);
   XmStringFree(cstring);

   parametri->ID_testo = find_text;
   parametri->ID_label = found_label;
   parametri->ID_fnext = find_next;
   parametri->ID_fprev = find_previous;

   return( find_form );
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void cerca_stringa_kit(w,user,data)
Widget w;
Find_struct *user;
XmAnyCallbackStruct *data;
{
   int i;
   char *stringa;
   XmStringTable c_strings;
   static XmString notfound, nulla;
   int verso_ricerca;

   if ( notfound == NULL || nulla == NULL )
   {
      nulla    = XmStringCreateLtoR("         ",XmSTRING_DEFAULT_CHARSET);
      notfound = XmStringCreateLtoR("NOT FOUND",XmSTRING_DEFAULT_CHARSET);
   }

   stringa = XmTextGetString(user->ID_testo);

   get_something (user->ID_lista,XmNitemCount,&(user->num_elem));

   get_something (user->ID_lista,XmNitems,&c_strings);

/* for (i=0; i<user->num_elem; i++)
     printf ("%s \n", extract_string(c_strings[i])); */

   get_something( w, XmNuserData, &verso_ricerca);

   switch (verso_ricerca) {
     case INDIETRO:
          i = user->pos;
          do
          {
             if( i > 0 )
               i--;
             else
             {
 	        set_something(user->ID_label,XmNlabelString,notfound);
                break;
             }

             if(Utstrstr(extract_string(c_strings[i]),stringa)!=NULL)
             {
                user->pos = i;
                set_something(user->ID_label,XmNlabelString,nulla);
                break;
             }
          }
          while(i != user->pos);
     break;

     case AVANTI:

          i = user->pos; 
          do
          {
             if (i < user->num_elem-1)
                i++;
             else
             {
                set_something(user->ID_label,XmNlabelString,notfound);
                break;
             }
 
             if(Utstrstr(extract_string(c_strings[i]),stringa)!=NULL)
             {
                user->pos = i;
                set_something(user->ID_label,XmNlabelString,nulla);
                break;
             }
          }
          while (i != user->pos);
     break;
   }

   UtListaScroll (user->ID_lista, user->num_elem, user->vis_elem, user->pos);

   XtFree (stringa);
}
