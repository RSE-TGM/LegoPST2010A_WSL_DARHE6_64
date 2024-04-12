
/*******************************************************************************
       initialCondition.h
       This header file is included by initialCondition.c

*******************************************************************************/

#ifndef	_INITIALCONDITION_INCLUDED
#define	_INITIALCONDITION_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/ScrolledW.h>
#include <Xm/Frame.h>
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
	Widget	UxicMenu;
	Widget	UxicMenuFile;
	Widget	UxicMenuFilePrint;
	Widget	UxicMenuFile_b2;
	Widget	UxicMenuFileQuitpb;
	Widget	Uxic_menu_file;
	Widget	UxicMenuEdit;
	Widget	UxicMenuEditSep1;
	Widget	UxicMenuEdit_b5;
	Widget	UxicMenuEditCheck;
	Widget	UxicMenuEditCheckAll;
	Widget	Uxic_menu_edit;
	Widget	UxicMenuHelp;
	Widget	UxicMenuHelpCommand;
	Widget	Uxic_menu_help;
	Widget	Uxframe8;
	Widget	Uxform27;
	Widget	UxicQuitpb;
	Widget	UxicInitpb;
	Widget	UxicSavepb;
	Widget	UxicViewpb;
	Widget	UxinitialConditionScrollW;
	Widget	UxIcRc;
	Widget	UxIcRcPopupMenu;
	Widget	UxIcRcPopupView;
	Widget	UxIcRcPopupMenu_p1_b2;
	Widget	UxIcRcPopupLoad;
	Widget	UxIcRcPopupSave;
	Widget	UxIcRcPopupMenu_p1_b5;
	Widget	UxIcRcPopupMenuPrint;
	Widget	UxIcRcPopupMenu_p1_b7;
	Widget	UxIcRcPopupQuit;
	Widget	Uxpadre;
} _UxCinitialCondition;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCinitialCondition    *UxInitialConditionContext;
#define icMenu                  UxInitialConditionContext->UxicMenu
#define icMenuFile              UxInitialConditionContext->UxicMenuFile
#define icMenuFilePrint         UxInitialConditionContext->UxicMenuFilePrint
#define icMenuFile_b2           UxInitialConditionContext->UxicMenuFile_b2
#define icMenuFileQuitpb        UxInitialConditionContext->UxicMenuFileQuitpb
#define ic_menu_file            UxInitialConditionContext->Uxic_menu_file
#define icMenuEdit              UxInitialConditionContext->UxicMenuEdit
#define icMenuEditSep1          UxInitialConditionContext->UxicMenuEditSep1
#define icMenuEdit_b5           UxInitialConditionContext->UxicMenuEdit_b5
#define icMenuEditCheck         UxInitialConditionContext->UxicMenuEditCheck
#define icMenuEditCheckAll      UxInitialConditionContext->UxicMenuEditCheckAll
#define ic_menu_edit            UxInitialConditionContext->Uxic_menu_edit
#define icMenuHelp              UxInitialConditionContext->UxicMenuHelp
#define icMenuHelpCommand       UxInitialConditionContext->UxicMenuHelpCommand
#define ic_menu_help            UxInitialConditionContext->Uxic_menu_help
#define frame8                  UxInitialConditionContext->Uxframe8
#define form27                  UxInitialConditionContext->Uxform27
#define icQuitpb                UxInitialConditionContext->UxicQuitpb
#define icInitpb                UxInitialConditionContext->UxicInitpb
#define icSavepb                UxInitialConditionContext->UxicSavepb
#define icViewpb                UxInitialConditionContext->UxicViewpb
#define initialConditionScrollW UxInitialConditionContext->UxinitialConditionScrollW
#define IcRc                    UxInitialConditionContext->UxIcRc
#define IcRcPopupMenu           UxInitialConditionContext->UxIcRcPopupMenu
#define IcRcPopupView           UxInitialConditionContext->UxIcRcPopupView
#define IcRcPopupMenu_p1_b2     UxInitialConditionContext->UxIcRcPopupMenu_p1_b2
#define IcRcPopupLoad           UxInitialConditionContext->UxIcRcPopupLoad
#define IcRcPopupSave           UxInitialConditionContext->UxIcRcPopupSave
#define IcRcPopupMenu_p1_b5     UxInitialConditionContext->UxIcRcPopupMenu_p1_b5
#define IcRcPopupMenuPrint      UxInitialConditionContext->UxIcRcPopupMenuPrint
#define IcRcPopupMenu_p1_b7     UxInitialConditionContext->UxIcRcPopupMenu_p1_b7
#define IcRcPopupQuit           UxInitialConditionContext->UxIcRcPopupQuit
#define padre                   UxInitialConditionContext->Uxpadre

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	initialCondition;
extern Widget	icMenuEditCutPb;
extern Widget	icMenuEditCopy;
extern Widget	icMenuEditPaste;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_initialCondition( Widget _Uxpadre );

#endif	/* _INITIALCONDITION_INCLUDED */
