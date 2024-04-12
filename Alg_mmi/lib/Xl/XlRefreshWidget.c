/**********************************************************************
*
*       C Source:               XlRefreshWidget.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Jun 18 11:48:22 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XlRefreshWidget.c-5 %  (%full_filespec: XlRefreshWidget.c-5:csrc:1 %)";
#endif
/*
   modulo XlRefreshWidget.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlRefreshWidget.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XlRefreshWidget.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*----------------------------------------------------------------------
 *       							       *
 *  XlRefreshWidget.c						       *
 *   								       * 
 *---------------------------------------------------------------------*/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xl/XlCoreP.h>
#include <Xl/XlManagerP.h>
#include <Ol/OlDatabasePunti.h>

/*
Funzione che richiama il metodo di Refresh dei singoli oggetti Xl.
Viene passato la lista dei widget ed il loro numero.
N.B.
La routine di Refresh di ogni singolo oggetto e' nella classe dello
oggetto stesso: ecco perche' viene invocato wCoreClass->xlcore_class.refresh
*/

int XlRefreshWidget(WidgetList widget,Cardinal num_widgets)
{
   XlCoreClassRec *wCoreClass;
   XlManagerClassRec *wManagerClass;
   int i;

   for(i=0;i<num_widgets;i++)
   {
      if( XlIsXlCore(widget[i]) )
      {
         wCoreClass=(XlCoreClassRec *)XtClass(widget[i]);
         if(!((wCoreClass->xlcore_class.refresh)(widget[i])))
         {
            printf("Errore in compilazione \n");
            return(-1);
         }
      }
      else
      {
         wManagerClass=(XlManagerClassRec *)XtClass(widget[i]);
         if(!((wManagerClass->xlmanager_class.refresh)(widget[i])))
         {
            printf("Errore in refresh \n");
            return(-1);
         }
      }
   }
   return(1);
}
