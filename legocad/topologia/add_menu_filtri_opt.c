/**********************************************************************
*
*       C Source:               add_menu_filtri_opt.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 13:57:14 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: add_menu_filtri_opt.c,2 %  (%full_filespec: 1,csrc,add_menu_filtri_opt.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)add_menu_filtri_opt.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include "lg1.h"
/*
#include "UxLib.h"
*/
#include "UxXt.h"
#include <UxPushBG.h>

swidget Opt3Filter;
extern swidget filterPane;

Opt3FilterCB()
{
   printf("Callback della opzione 3 dei filtri\n");
}

void add_opt_butt()
{
/*creo il push button */
   Opt3Filter = UxCreatePushButtonGadget("Filtro 3",filterPane);
   UxPutMnemonic(Opt3Filter,"3");
   UxPutLabelString(Opt3Filter,"Filtro n.3");
   XtAddCallback(UxGetWidget(Opt3Filter),XmNactivateCallback,Opt3FilterCB,NULL);
   UxCreateWidget(Opt3Filter);
}

