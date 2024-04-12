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
/*
   modulo OlSetRes.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlSetRes.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)OlSetRes.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*----------------------------------------------------------------------
 *       							       *
 *  OlSetPert				    		               *
 *  OlSetCompiler           		    		               *
 *  OlSetDatabasePunti			    		               *
 *  OlSetDatabaseTopologia		    		               *
 *   								       * 
 *---------------------------------------------------------------------*/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xl/XlCoreP.h>
#include <Xl/XlManagerP.h>

Boolean OlSetPert(WidgetList widget,Cardinal num_widgets,OlPertObject pert)
{
   XlCoreClassRec *wCoreClass;
   XlManagerClassRec *wManagerClass;
   WidgetList widget_figli;
   Cardinal num_figli;
   int i;

	
   for(i=0;i<num_widgets;i++)
   {
      if( XlIsXlCore(widget[i]) )
      {
         wCoreClass=(XlCoreClassRec *)XtClass(widget[i]);
         wCoreClass->xlcore_class.pert=pert;
      }
      else
      {
         wManagerClass=(XlManagerClassRec *)XtClass(widget[i]);
         wManagerClass->xlmanager_class.pert=pert;
	 if(XlIsXlComposite(widget[i]))
		{
		XtVaGetValues( widget[i],
               		XmNnumChildren, &num_figli,
               		XmNchildren, &widget_figli, NULL );
		OlSetPert(widget_figli,num_figli,pert);
		}
      }
   }
return(True);
}

Boolean OlSetDatabasePunti(WidgetList widget,Cardinal num_widgets,
				OlDatabasePuntiObject database)
{
   XlCoreClassRec *wCoreClass;
   XlManagerClassRec *wManagerClass;
   WidgetList widget_figli;
   Cardinal num_figli;
   int i;

	
   for(i=0;i<num_widgets;i++)
   {
      if( XlIsXlCore(widget[i]) )
      {
         wCoreClass=(XlCoreClassRec *)XtClass(widget[i]);
         wCoreClass->xlcore_class.database=database;
      }
      else
      {
         wManagerClass=(XlManagerClassRec *)XtClass(widget[i]);
         wManagerClass->xlmanager_class.database=database;
	 if(XlIsXlComposite(widget[i]))
		{
		XtVaGetValues( widget[i],
               		XmNnumChildren, &num_figli,
               		XmNchildren, &widget_figli, NULL );
		OlSetDatabasePunti(widget_figli,num_figli,database);
		}
      }
   }
return(True);
}

Boolean OlSetDatabaseTopologia(WidgetList widget,Cardinal num_widgets,
                                OlDatabaseTopologiaObject database)
{
   XlCoreClassRec *wCoreClass;
   XlManagerClassRec *wManagerClass;
   WidgetList widget_figli;
   Cardinal num_figli;
   int i;


   for(i=0;i<num_widgets;i++)
   {
      if( XlIsXlCore(widget[i]) )
      {
         wCoreClass=(XlCoreClassRec *)XtClass(widget[i]);
         wCoreClass->xlcore_class.database_topologia=database;
      }
      else
      {
         wManagerClass=(XlManagerClassRec *)XtClass(widget[i]);
         wManagerClass->xlmanager_class.database_topologia=database;
         if(XlIsXlComposite(widget[i]))
                {
                XtVaGetValues( widget[i],
                        XmNnumChildren, &num_figli,
                        XmNchildren, &widget_figli, NULL );
                OlSetDatabaseTopologia(widget_figli,num_figli,database);
                }
      }
   }
return(True);
}


Boolean OlSetCompiler(WidgetList widget,Cardinal num_widgets,
				OlCompilerObject compilatore)
{
   XlCoreClassRec *wCoreClass;
   XlManagerClassRec *wManagerClass;
   WidgetList widget_figli;
   Cardinal num_figli;
   int i;

	
   for(i=0;i<num_widgets;i++)
   {
      if( XlIsXlCore(widget[i]) )
      {
         wCoreClass=(XlCoreClassRec *)XtClass(widget[i]);
         wCoreClass->xlcore_class.compilatore=compilatore;
      }
      else
      {
         wManagerClass=(XlManagerClassRec *)XtClass(widget[i]);
         wManagerClass->xlmanager_class.compilatore=compilatore;
	 if(XlIsXlComposite(widget[i]))
		{
		XtVaGetValues( widget[i],
               		XmNnumChildren, &num_figli,
               		XmNchildren, &widget_figli, NULL );
		OlSetCompiler(widget_figli,num_figli,compilatore);
		}
      }
   }
return(True);
}

Boolean OlSetConn(WidgetList widget,Cardinal num_widgets,OlConnObject conn)
{
   XlCoreClassRec *wCoreClass;
   XlManagerClassRec *wManagerClass;
   WidgetList widget_figli;
   Cardinal num_figli;
   int i;

	
   for(i=0;i<num_widgets;i++)
   {
      if( XlIsXlCore(widget[i]) )
      {
         wCoreClass=(XlCoreClassRec *)XtClass(widget[i]);
	 OlCompilerSetConn(wCoreClass->xlcore_class.compilatore,conn);
      }
      else
      {
         wManagerClass=(XlManagerClassRec *)XtClass(widget[i]);
	 OlCompilerSetConn(wManagerClass->xlmanager_class.compilatore,conn);
	 if(XlIsXlComposite(widget[i]))
		{
		XtVaGetValues( widget[i],
               		XmNnumChildren, &num_figli,
               		XmNchildren, &widget_figli, NULL );
		OlSetConn(widget_figli,num_figli,conn);
		}
      }
   }
return(True);
}
