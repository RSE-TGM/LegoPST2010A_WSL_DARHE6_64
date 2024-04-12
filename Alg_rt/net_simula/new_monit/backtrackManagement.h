
/*******************************************************************************
       backtrackManagement.h
       This header file is included by backtrackManagement.c

*******************************************************************************/

#ifndef	_BACKTRACKMANAGEMENT_INCLUDED
#define	_BACKTRACKMANAGEMENT_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/ScrolledW.h>
#include <Xm/Label.h>
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>
#include <Xm/Separator.h>
#include <Xm/ToggleB.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
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
	Widget	Uxframe15;
	Widget	Uxform22;
	Widget	UxbtQuitpb;
	Widget	UxbtLoadpb;
	Widget	UxbtInitpb;
	Widget	UxbtViewpb;
	Widget	UxbtMenu;
	Widget	UxbtMenuFile;
	Widget	UxbtMenuFilepb;
	Widget	Uxbt_menu_file;
	Widget	UxbtMenuReplay;
	Widget	UxbtMenuReplayOntb;
	Widget	UxbtMenuReplay_b3;
	Widget	UxbtMenuReplayOfftb;
	Widget	Uxbt_menu_replay;
	Widget	UxbtMenuModi;
	Widget	UxbtMenuModiAvind;
	Widget	UxbtMenuModiAvindForwtb;
	Widget	UxbtMenuModiAvindBacktb;
	Widget	UxbtMenuModiFbcb;
	Widget	UxbtMenuModiAutoman;
	Widget	UxbtMenuModiAutomanAutotb;
	Widget	UxbtMenuModiAutomanMan;
	Widget	UxbtMenuModiAmcb;
	Widget	Uxbt_menu_mode;
	Widget	UxbtMenuEdit;
	Widget	UxbtMenuEditRecpb;
	Widget	UxbtMenuEditPrespb;
	Widget	Uxbt_menu_edit;
	Widget	UxbtMenuHelp;
	Widget	UxbtMenuHelppb;
	Widget	Uxbt_menu_help;
	Widget	UxbulletinBoard2;
	Widget	UxreplaySelectionbt;
	Widget	UxreplaySelectionLabel;
	Widget	UxbtLoadLabel;
	Widget	UxbtLoadNumber;
	Widget	UxbacktrackScrollW;
	Widget	UxBtRc;
	Widget	Uxmenu5;
	Widget	UxBtRcPopupView;
	Widget	Uxmenu5_p1_b5;
	Widget	UxBtRcPopupLoad;
	Widget	UxBtRcPopupInit;
	Widget	Uxmenu5_p1_b6;
	Widget	UxBtRcPopupQuit;
	Widget	Uxpadre_bt;
} _UxCbacktrackManagement;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCbacktrackManagement *UxBacktrackManagementContext;
#define frame15                 UxBacktrackManagementContext->Uxframe15
#define form22                  UxBacktrackManagementContext->Uxform22
#define btQuitpb                UxBacktrackManagementContext->UxbtQuitpb
#define btLoadpb                UxBacktrackManagementContext->UxbtLoadpb
#define btInitpb                UxBacktrackManagementContext->UxbtInitpb
#define btViewpb                UxBacktrackManagementContext->UxbtViewpb
#define btMenu                  UxBacktrackManagementContext->UxbtMenu
#define btMenuFile              UxBacktrackManagementContext->UxbtMenuFile
#define btMenuFilepb            UxBacktrackManagementContext->UxbtMenuFilepb
#define bt_menu_file            UxBacktrackManagementContext->Uxbt_menu_file
#define btMenuReplay            UxBacktrackManagementContext->UxbtMenuReplay
#define btMenuReplayOntb        UxBacktrackManagementContext->UxbtMenuReplayOntb
#define btMenuReplay_b3         UxBacktrackManagementContext->UxbtMenuReplay_b3
#define btMenuReplayOfftb       UxBacktrackManagementContext->UxbtMenuReplayOfftb
#define bt_menu_replay          UxBacktrackManagementContext->Uxbt_menu_replay
#define btMenuModi              UxBacktrackManagementContext->UxbtMenuModi
#define btMenuModiAvind         UxBacktrackManagementContext->UxbtMenuModiAvind
#define btMenuModiAvindForwtb   UxBacktrackManagementContext->UxbtMenuModiAvindForwtb
#define btMenuModiAvindBacktb   UxBacktrackManagementContext->UxbtMenuModiAvindBacktb
#define btMenuModiFbcb          UxBacktrackManagementContext->UxbtMenuModiFbcb
#define btMenuModiAutoman       UxBacktrackManagementContext->UxbtMenuModiAutoman
#define btMenuModiAutomanAutotb UxBacktrackManagementContext->UxbtMenuModiAutomanAutotb
#define btMenuModiAutomanMan    UxBacktrackManagementContext->UxbtMenuModiAutomanMan
#define btMenuModiAmcb          UxBacktrackManagementContext->UxbtMenuModiAmcb
#define bt_menu_mode            UxBacktrackManagementContext->Uxbt_menu_mode
#define btMenuEdit              UxBacktrackManagementContext->UxbtMenuEdit
#define btMenuEditRecpb         UxBacktrackManagementContext->UxbtMenuEditRecpb
#define btMenuEditPrespb        UxBacktrackManagementContext->UxbtMenuEditPrespb
#define bt_menu_edit            UxBacktrackManagementContext->Uxbt_menu_edit
#define btMenuHelp              UxBacktrackManagementContext->UxbtMenuHelp
#define btMenuHelppb            UxBacktrackManagementContext->UxbtMenuHelppb
#define bt_menu_help            UxBacktrackManagementContext->Uxbt_menu_help
#define bulletinBoard2          UxBacktrackManagementContext->UxbulletinBoard2
#define replaySelectionbt       UxBacktrackManagementContext->UxreplaySelectionbt
#define replaySelectionLabel    UxBacktrackManagementContext->UxreplaySelectionLabel
#define btLoadLabel             UxBacktrackManagementContext->UxbtLoadLabel
#define btLoadNumber            UxBacktrackManagementContext->UxbtLoadNumber
#define backtrackScrollW        UxBacktrackManagementContext->UxbacktrackScrollW
#define BtRc                    UxBacktrackManagementContext->UxBtRc
#define menu5                   UxBacktrackManagementContext->Uxmenu5
#define BtRcPopupView           UxBacktrackManagementContext->UxBtRcPopupView
#define menu5_p1_b5             UxBacktrackManagementContext->Uxmenu5_p1_b5
#define BtRcPopupLoad           UxBacktrackManagementContext->UxBtRcPopupLoad
#define BtRcPopupInit           UxBacktrackManagementContext->UxBtRcPopupInit
#define menu5_p1_b6             UxBacktrackManagementContext->Uxmenu5_p1_b6
#define BtRcPopupQuit           UxBacktrackManagementContext->UxBtRcPopupQuit
#define padre_bt                UxBacktrackManagementContext->Uxpadre_bt

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	backtrackManagement;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_backtrackManagement( Widget _Uxpadre_bt );

#endif	/* _BACKTRACKMANAGEMENT_INCLUDED */
