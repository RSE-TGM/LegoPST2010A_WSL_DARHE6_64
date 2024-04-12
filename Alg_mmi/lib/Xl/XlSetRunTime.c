/**********************************************************************
*
*       C Source:               XlSetRunTime.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 16 17:17:18 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XlSetRunTime.c,2 %  (%full_filespec: 1,csrc,XlSetRunTime.c,2 %)";
#endif
/*
   modulo XlSetRunTime.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlSetRunTime.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XlSetRunTime.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*----------------------------------------------------------------------
 *       							       *
 *  XlSetConfigOff				    		               *
 *   								       * 
 *---------------------------------------------------------------------*/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xl/XlCoreP.h>
#include <Xl/XlManagerP.h>

Boolean XlSetConfigOff(WidgetList widget,Cardinal num_widgets)
{
   WidgetList widget_figli;
   Cardinal num_figli;
   int i;
   Arg arg[1];



	
   for(i=0;i<num_widgets;i++)
   {
      if( XlIsXlCore(widget[i]) )
      {
        XtSetArg(arg[0],XlNconfig,False);
	XtSetValues(widget[i],arg,1);
      }
      else
      {
        XtSetArg(arg[0],XlNconfig,False);
	XtSetValues(widget[i],arg,1);
	if(XlIsXlComposite(widget[i]))
		{
		XtVaGetValues( widget[i],
               		XmNnumChildren, &num_figli,
               		XmNchildren, &widget_figli, NULL );
		XlSetConfigOff(widget_figli,num_figli);
		}
      }
   }
return(True);
}


Boolean XlSetConfigOn(WidgetList widget,Cardinal num_widgets)
{
   WidgetList widget_figli;
   Cardinal num_figli;
   int i;
   Arg arg[1];



   for(i=0;i<num_widgets;i++)
   {
      if( XlIsXlCore(widget[i]) )
      {
        XtSetArg(arg[0],XlNconfig,True);
        XtSetValues(widget[i],arg,1);
      }
      else
      {
        XtSetArg(arg[0],XlNconfig,True);
        XtSetValues(widget[i],arg,1);
        if(XlIsXlComposite(widget[i]))
                {
                XtVaGetValues( widget[i],
                        XmNnumChildren, &num_figli,
                        XmNchildren, &widget_figli, NULL );
                XlSetConfigOff(widget_figli,num_figli);
                }
      }
   }
return(True);
}

/*
	setta la risorsa resource al valore value a tutti gli
	oggetti contenuti nella lista, e nei loro figli, se sono
	della classe specificata.
	Se la classe e' uguale a NULL la risorsa viene settata 
	in tutti gli oggetti.
*/
Boolean XlSetSomething(WidgetList widget,Cardinal num_widgets,
		char * ClassName, char * resource, char * value)
{
   WidgetList widget_figli;
   Cardinal num_figli;
   int i;
   Arg arg[1];

   for(i=0;i<num_widgets;i++)
   {
      if(XlIsXlCore(widget[i]))
      {
      if(ClassName!=NULL)
	if(strcmp(ClassName,XlGetClassName(XtClass(widget[i])))!=0)
             continue;
      XtSetArg(arg[0],resource,value);
      XtSetValues(widget[i],arg,1);
      }
      else
      {
      if(XlIsXlComposite(widget[i]))
          {
          XtVaGetValues( widget[i],
                         XmNnumChildren, &num_figli,
                         XmNchildren, &widget_figli, NULL );
          XlSetSomething(widget_figli,num_figli,
				ClassName,resource,value);
          }

      if(ClassName!=NULL)
	if(strcmp(ClassName,XlGetClassName(XtClass(widget[i])))!=0)
		continue;
      XtSetArg(arg[0],resource,value);
      XtSetValues(widget[i],arg,1);
      }
   }
return(True);
}
