
/*******************************************************************************
       listaScenari.h
       This header file is included by listaScenari.c

*******************************************************************************/

#ifndef	_LISTASCENARI_INCLUDED
#define	_LISTASCENARI_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/CascadeB.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
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
	Widget	UxlistaScenari;
	Widget	Uxmenu2;
	Widget	UxmalfScenMenu;
	Widget	UxmalfScenMenuOpenpb;
	Widget	UxmalfScenMenuNewpb;
	Widget	UxmalfScenMenu_b2;
	Widget	UxmalfScenMenuExitpb;
	Widget	Uxmenu1_top_b1;
	Widget	Uxmenu2_p2;
	Widget	UxmalfScenEditCutpb;
	Widget	Uxmenu2_top_b1;
	Widget	Uxmenu2_p3;
	Widget	Uxmenu2_p3_b1;
	Widget	Uxmenu2_top_b2;
	Widget	Uxmenu2_p4;
	Widget	UxmalfScenMenuSummarypb;
	Widget	Uxmenu2_top_b3;
	Widget	Uxform30;
	Widget	Uxframe14;
	Widget	Uxform31;
	Widget	UxscenariMalfQuitpb1;
	Widget	UxscrolledWindow5;
	Widget	UxscrollListaScen;
	Widget	Uxmenu12;
	Widget	UxmfScenPopupOpen;
	Widget	UxmfScenPopupNew;
	Widget	Uxmenu12_p1_b4;
	Widget	UxmfScenPopupCut;
	Widget	Uxmenu12_p1_b5;
	Widget	UxmfScenPopupSummary;
	Widget	Uxmenu12_p1_b8;
	Widget	UxmfScenPopupQuit;
	int	UxscenarioSelect;
	XtIntervalId	Uxtimer_listaScenari;
	Widget	UxlistaScenariParent;
	int	Uxtipo;
} _UxClistaScenari;

#ifdef CONTEXT_MACRO_ACCESS
static _UxClistaScenari        *UxListaScenariContext;
#define listaScenari            UxListaScenariContext->UxlistaScenari
#define menu2                   UxListaScenariContext->Uxmenu2
#define malfScenMenu            UxListaScenariContext->UxmalfScenMenu
#define malfScenMenuOpenpb      UxListaScenariContext->UxmalfScenMenuOpenpb
#define malfScenMenuNewpb       UxListaScenariContext->UxmalfScenMenuNewpb
#define malfScenMenu_b2         UxListaScenariContext->UxmalfScenMenu_b2
#define malfScenMenuExitpb      UxListaScenariContext->UxmalfScenMenuExitpb
#define menu1_top_b1            UxListaScenariContext->Uxmenu1_top_b1
#define menu2_p2                UxListaScenariContext->Uxmenu2_p2
#define malfScenEditCutpb       UxListaScenariContext->UxmalfScenEditCutpb
#define menu2_top_b1            UxListaScenariContext->Uxmenu2_top_b1
#define menu2_p3                UxListaScenariContext->Uxmenu2_p3
#define menu2_p3_b1             UxListaScenariContext->Uxmenu2_p3_b1
#define menu2_top_b2            UxListaScenariContext->Uxmenu2_top_b2
#define menu2_p4                UxListaScenariContext->Uxmenu2_p4
#define malfScenMenuSummarypb   UxListaScenariContext->UxmalfScenMenuSummarypb
#define menu2_top_b3            UxListaScenariContext->Uxmenu2_top_b3
#define form30                  UxListaScenariContext->Uxform30
#define frame14                 UxListaScenariContext->Uxframe14
#define form31                  UxListaScenariContext->Uxform31
#define scenariMalfQuitpb1      UxListaScenariContext->UxscenariMalfQuitpb1
#define scrolledWindow5         UxListaScenariContext->UxscrolledWindow5
#define scrollListaScen         UxListaScenariContext->UxscrollListaScen
#define menu12                  UxListaScenariContext->Uxmenu12
#define mfScenPopupOpen         UxListaScenariContext->UxmfScenPopupOpen
#define mfScenPopupNew          UxListaScenariContext->UxmfScenPopupNew
#define menu12_p1_b4            UxListaScenariContext->Uxmenu12_p1_b4
#define mfScenPopupCut          UxListaScenariContext->UxmfScenPopupCut
#define menu12_p1_b5            UxListaScenariContext->Uxmenu12_p1_b5
#define mfScenPopupSummary      UxListaScenariContext->UxmfScenPopupSummary
#define menu12_p1_b8            UxListaScenariContext->Uxmenu12_p1_b8
#define mfScenPopupQuit         UxListaScenariContext->UxmfScenPopupQuit
#define scenarioSelect          UxListaScenariContext->UxscenarioSelect
#define timer_listaScenari      UxListaScenariContext->Uxtimer_listaScenari
#define listaScenariParent      UxListaScenariContext->UxlistaScenariParent
#define tipo                    UxListaScenariContext->Uxtipo

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_listaScenari( Widget _UxlistaScenariParent, int _Uxtipo );

#endif	/* _LISTASCENARI_INCLUDED */
