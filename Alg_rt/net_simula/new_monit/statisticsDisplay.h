/**********************************************************************
*
*       C Header:               statisticsDisplay.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:46:37 1997 %
*
**********************************************************************/


/*******************************************************************************
       statisticsDisplay.h
       This header file is included by statisticsDisplay.c

*******************************************************************************/

#ifndef	_STATISTICSDISPLAY_INCLUDED
#define	_STATISTICSDISPLAY_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/DrawingA.h>
#include <Xm/Form.h>

/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxstatisticsDisplay;
	Widget	UxdrawingArea1;
	Widget	Uxmenu7;
	Widget	Uxmenu7_p1;
	Widget	UxstatDisplayMenuQuitpb;
	Widget	Uxmenu7_top_b1;
	Widget	Uxframe20;
	Widget	Uxform47;
	Widget	UxpreviewQuitpb1;
	Window	Uxdwg;
	Widget	UxUxParent;
} _UxCstatisticsDisplay;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCstatisticsDisplay   *UxStatisticsDisplayContext;
#define statisticsDisplay       UxStatisticsDisplayContext->UxstatisticsDisplay
#define drawingArea1            UxStatisticsDisplayContext->UxdrawingArea1
#define menu7                   UxStatisticsDisplayContext->Uxmenu7
#define menu7_p1                UxStatisticsDisplayContext->Uxmenu7_p1
#define statDisplayMenuQuitpb   UxStatisticsDisplayContext->UxstatDisplayMenuQuitpb
#define menu7_top_b1            UxStatisticsDisplayContext->Uxmenu7_top_b1
#define frame20                 UxStatisticsDisplayContext->Uxframe20
#define form47                  UxStatisticsDisplayContext->Uxform47
#define previewQuitpb1          UxStatisticsDisplayContext->UxpreviewQuitpb1
#define dwg                     UxStatisticsDisplayContext->Uxdwg
#define UxParent                UxStatisticsDisplayContext->UxUxParent

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_statisticsDisplay( Widget _UxUxParent );

#endif	/* _STATISTICSDISPLAY_INCLUDED */
