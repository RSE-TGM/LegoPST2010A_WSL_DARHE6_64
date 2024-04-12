/**********************************************************************
*
*       C Header:               initSimulator.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:38:24 1997 %
*
**********************************************************************/

/*******************************************************************************
       initSimulator.h
       This header file is included by initSimulator.c

*******************************************************************************/

#ifndef	_INITSIMULATOR_INCLUDED
#define	_INITSIMULATOR_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/CascadeB.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Frame.h>
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
	Widget	Uxform4;
	Widget	Uxframe3;
	Widget	Uxform3;
	Widget	UxinitQuitpb;
	Widget	UxinitViewpb;
	Widget	Uxmenu1;
	Widget	UxinitMenu;
	Widget	UxinitMenuExitpb;
	Widget	Uxmenu1_top_b2;
	Widget	UxscrolledWindow3;
	Widget	UxscrollListaSnap;
	Widget	UxlistaSnapPopupMenu;
	Widget	UxlistaSnapPopupView;
	int	Uxitem_select;
	Widget	Uxpadre_init;
	int	Uxtipo;
} _UxCinitSimulator;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCinitSimulator       *UxInitSimulatorContext;
#define form4                   UxInitSimulatorContext->Uxform4
#define frame3                  UxInitSimulatorContext->Uxframe3
#define form3                   UxInitSimulatorContext->Uxform3
#define initQuitpb              UxInitSimulatorContext->UxinitQuitpb
#define initViewpb              UxInitSimulatorContext->UxinitViewpb
#define menu1                   UxInitSimulatorContext->Uxmenu1
#define initMenu                UxInitSimulatorContext->UxinitMenu
#define initMenuExitpb          UxInitSimulatorContext->UxinitMenuExitpb
#define menu1_top_b2            UxInitSimulatorContext->Uxmenu1_top_b2
#define scrolledWindow3         UxInitSimulatorContext->UxscrolledWindow3
#define scrollListaSnap         UxInitSimulatorContext->UxscrollListaSnap
#define listaSnapPopupMenu      UxInitSimulatorContext->UxlistaSnapPopupMenu
#define listaSnapPopupView      UxInitSimulatorContext->UxlistaSnapPopupView
#define item_select             UxInitSimulatorContext->Uxitem_select
#define padre_init              UxInitSimulatorContext->Uxpadre_init
#define tipo                    UxInitSimulatorContext->Uxtipo

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	initSimulator;
extern Widget	initLoadpb;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_initSimulator( Widget _Uxpadre_init, int _Uxtipo );

#endif	/* _INITSIMULATOR_INCLUDED */
