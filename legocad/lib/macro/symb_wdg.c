/**********************************************************************
*
*       C Source:               symb_wdg.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 12:17:14 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: symb_wdg.c,2 %  (%full_filespec: 1,csrc,symb_wdg.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)symb_wdg.c	2.7\t4/11/95";
/*
        Fine sezione per SCCS
*/

/* SYMB_WDG.C 		file di servizio per MACRO
			Crea gli widget dell'applicativo
			relativi alla finestra di visualizzazione
                        dei SIMBOLI
   Versione 0.1		18.12.92		Buffo & Calleri  */

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/cursorfont.h>
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/Text.h>
#include <Xm/SeparatoG.h>
#include <Xm/DialogS.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>
#include <Xm/ScrolledW.h>
#include <Xm/BulletinB.h>

#include "macro.h"
#include "ico_mesg.h"
#include "file_icone.h"
#include "libutilx.h"

/* Variabili esterne dichiarate in MACRO.C ... */
extern Widget top_level;
extern Widget dbx_simboli;
extern Widget tavola_simboli, scroll_simboli;

extern char *warning_mesg[];
extern Dialog_geometry geom_attention;

extern XmString cstring;

extern Display *display;
extern int screen;
extern GC iconGC;

extern Arg      args[];
extern Cardinal nargs;

extern Pixel apix[];

extern SymbolFileRec rec_symb;

/*------------------------------------------------------------------*/
/*** void dialog_simboli()
*** Crea la finestra di scelta dell'icona per un blocco.
***/
void dialog_simboli()
{
   Widget cancel_simboli;

   printf("dialog simboli...\n");

/* Creazione della finestra di inserimento nome nuovo blocco (FORM) */
   cstring = CREATE_CSTRING("SYMBOLS TABLE");
   nargs=0;
   XtSetArg(args[nargs],XmNdefaultPosition,False); nargs++;
   XtSetArg(args[nargs],XmNx,510); nargs++;
   XtSetArg(args[nargs],XmNy,10); nargs++;
   XtSetArg(args[nargs],XmNautoUnmanage,True); nargs++;
   XtSetArg(args[nargs],XmNnoResize,False); nargs++;
   XtSetArg(args[nargs],XmNdialogStyle,XmDIALOG_MODELESS); nargs++;
   XtSetArg(args[nargs],XmNdialogTitle, cstring); nargs++;
   XtSetArg(args[nargs], XmNwidth,600); nargs++;
   XtSetArg(args[nargs], XmNheight,500); nargs++;
   XtSetArg(args[nargs], XmNverticalSpacing, 10); nargs++;
   XtSetArg(args[nargs], XmNhorizontalSpacing, 10); nargs++;
   dbx_simboli = XmCreateFormDialog (top_level,"Simboli",args,nargs);
   XmStringFree(cstring);

   /* Creazione della scrolled window dei simboli */
   nargs=0;
   XtSetArg(args[nargs],XmNleftAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNrightAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNtopAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNbottomAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNbottomOffset,45); nargs++;
   XtSetArg(args[nargs],XmNheight,350); nargs++;
   XtSetArg(args[nargs],XmNscrollBarDisplayPolicy,XmAS_NEEDED); nargs++;
   XtSetArg(args[nargs],XmNscrollingPolicy,XmAUTOMATIC); nargs++;
   XtSetArg(args[nargs],XmNvisualPolicy,XmCONSTANT); nargs++;
   XtSetArg(args[nargs],XmNscrollBarPlacement,XmBOTTOM_RIGHT); nargs++;
   scroll_simboli = XmCreateScrolledWindow (dbx_simboli,"Scroll_simboli",
					    args,nargs);
   XtManageChild (scroll_simboli);

/* button 'Cancel' */
   nargs=0;
   XtSetArg(args[nargs],XmNrightAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNbottomAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNlabelString,CREATE_CSTRING("Cancel")); nargs++;
   cancel_simboli = XmCreatePushButton (dbx_simboli,"Simboli",args,nargs);
   XtManageChild (cancel_simboli);
   XtAddCallback (cancel_simboli,XmNactivateCallback,cancel_proc, dbx_simboli);
}

/*------------------------------------------------------------------*/
/*** carica_simboli()
*** Parametri:
***     'sta sacca di arelle
*** Carica i record dei simboli e li visualizza.
***/
void carica_simboli()
{
   int xx = 10, yy = 10, i, j;
   int max_height = 0;
   extern PixmapSymbolStruct pixmap_symbol;

   if ( tavola_simboli != NULL )
       XtDestroyWidget(tavola_simboli);

   nargs = 0;
   XtSetArg(args[nargs], XmNx, 0); nargs++;
   XtSetArg(args[nargs], XmNy, 0); nargs++;
   XtSetArg(args[nargs], XmNwidth, 680); nargs++;
   XtSetArg(args[nargs], XmNheight,350); nargs++;
   XtSetArg(args[nargs], XmNmarginWidth, 0); nargs++;
   XtSetArg(args[nargs], XmNmarginHeight,0); nargs++;
   XtSetArg(args[nargs], XmNnoResize,True); nargs++;
   XtSetArg(args[nargs], XmNresizePolicy, XmRESIZE_ANY); nargs++;
   XtSetArg(args[nargs], XmNuserData, TP_SYMBOL); nargs++;
   tavola_simboli = XmCreateBulletinBoard (scroll_simboli,
				             "Simboli",args,nargs);
   XtManageChild (tavola_simboli);

   if ( ! pixmap_symbol.num_icone )
       s_warning( top_level, &geom_attention, APPLICATION_NAME, 
                  warning_mesg, WNOSYMBDEF );
   else
       for ( i=0 ; i<pixmap_symbol.num_icone; i++ )
       {
           PixmapInfo *pixm_info;

           pixm_info = &pixmap_symbol.pixmap_info[i];
           crea_icona( tavola_simboli, pixm_info, "", xx, yy, FROM_ADD_BLOCK,
		       0, 0 );

           xx += pixm_info->width + 20;

       /* Trova l'altezza maggiore tra le icone che dovranno essere */
       /* essere visualizzate su un'unica riga */
           max_height = (max_height < pixm_info->height) ? pixm_info->height 
							 : max_height;
           if ((i+1) % MAX_SYMB_X_ROW == 0)
           {
               xx  = 10;
               yy += max_height + 30;
               max_height = 0;
           }
       }
}

/* fine symb_wdg.c */
