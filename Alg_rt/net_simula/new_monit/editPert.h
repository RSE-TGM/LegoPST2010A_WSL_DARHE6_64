
/*******************************************************************************
       editPert.h
       This header file is included by editPert.c

*******************************************************************************/

#ifndef	_EDITPERT_INCLUDED
#define	_EDITPERT_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Label.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/PanedW.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/CascadeB.h>
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
	Widget	UxeditPertMenu;
	Widget	UxeditPertMenuFile;
	Widget	UxeditPertMenuFileQuit;
	Widget	Uxmenu10_top_b1;
	Widget	UxeditPertMenuEdit;
	Widget	UxeditPertMenuEditTimer;
	Widget	Uxmenu10_top_b2;
	Widget	UxframeComm;
	Widget	Uxform53;
	Widget	UxeditPertQuitpb;
	Widget	UxpanedWindow3;
	Widget	Uxform54;
	Widget	UxeditPertAttScrollWin;
	Widget	UxeditPertAttScrollList;
	Widget	Uxlabel12;
	Widget	UxeditPertFreqUpdateLabel;
	Widget	Uxform55;
	Widget	UxeditPertUnattScrollWin;
	Widget	UxeditPertUnattScrollList;
	Widget	Uxlabel14;
	swidget	UxUxParent;
} _UxCeditPert;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCeditPert            *UxEditPertContext;
#define editPertMenu            UxEditPertContext->UxeditPertMenu
#define editPertMenuFile        UxEditPertContext->UxeditPertMenuFile
#define editPertMenuFileQuit    UxEditPertContext->UxeditPertMenuFileQuit
#define menu10_top_b1           UxEditPertContext->Uxmenu10_top_b1
#define editPertMenuEdit        UxEditPertContext->UxeditPertMenuEdit
#define editPertMenuEditTimer   UxEditPertContext->UxeditPertMenuEditTimer
#define menu10_top_b2           UxEditPertContext->Uxmenu10_top_b2
#define frameComm               UxEditPertContext->UxframeComm
#define form53                  UxEditPertContext->Uxform53
#define editPertQuitpb          UxEditPertContext->UxeditPertQuitpb
#define panedWindow3            UxEditPertContext->UxpanedWindow3
#define form54                  UxEditPertContext->Uxform54
#define editPertAttScrollWin    UxEditPertContext->UxeditPertAttScrollWin
#define editPertAttScrollList   UxEditPertContext->UxeditPertAttScrollList
#define label12                 UxEditPertContext->Uxlabel12
#define editPertFreqUpdateLabel UxEditPertContext->UxeditPertFreqUpdateLabel
#define form55                  UxEditPertContext->Uxform55
#define editPertUnattScrollWin  UxEditPertContext->UxeditPertUnattScrollWin
#define editPertUnattScrollList UxEditPertContext->UxeditPertUnattScrollList
#define label14                 UxEditPertContext->Uxlabel14
#define UxParent                UxEditPertContext->UxUxParent

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	editPert;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_editPert( swidget _UxUxParent );

#endif	/* _EDITPERT_INCLUDED */
