
/*******************************************************************************
       optionSet.h
       This header file is included by optionSet.c

*******************************************************************************/

#ifndef	_OPTIONSET_INCLUDED
#define	_OPTIONSET_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/CascadeB.h>
#include <Xm/Separator.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

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
	Widget	Uxform7;
	Widget	Uxform12;
	Widget	Uxframe12;
	Widget	Uxform21;
	Widget	UxpushButton6;
	Widget	Uxmenu6;
	Widget	UxoptionSetMenu;
	Widget	UxoptionSetMenuSavepb;
	Widget	UxoptionSetMenu_b2;
	Widget	UxoptionSetMenuLoadpb;
	Widget	UxoptionSetMenu_b4;
	Widget	UxoptionSetMenuQuitpb;
	Widget	Uxmenu6_top_b2;
	Widget	Uxframe11;
	Widget	Uxform11;
	Widget	UxoptSelectionMenu;
	Widget	UxoptSelMenuInitpb;
	Widget	UxoptSelMenuSnappb;
	Widget	UxoptSelMenuIcProtpb;
	Widget	UxoptSelMenuRecpb;
	Widget	UxoptSelMenuMffrpb;
	Widget	UxoptSelMenuArchivepb;
	Widget	UxoptSelMenuShowpb;
	Widget	UxoptSelectionMenu_b7;
	Widget	UxoptSelMenuDisplaypb;
	Widget	UxoptSelnMenuProgLaunchpb;
	Widget	UxoptionSelection;
	Widget	Uxframe10;
	Widget	UxoptionSetForm;
} _UxCoptionSet;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCoptionSet           *UxOptionSetContext;
#define form7                   UxOptionSetContext->Uxform7
#define form12                  UxOptionSetContext->Uxform12
#define frame12                 UxOptionSetContext->Uxframe12
#define form21                  UxOptionSetContext->Uxform21
#define pushButton6             UxOptionSetContext->UxpushButton6
#define menu6                   UxOptionSetContext->Uxmenu6
#define optionSetMenu           UxOptionSetContext->UxoptionSetMenu
#define optionSetMenuSavepb     UxOptionSetContext->UxoptionSetMenuSavepb
#define optionSetMenu_b2        UxOptionSetContext->UxoptionSetMenu_b2
#define optionSetMenuLoadpb     UxOptionSetContext->UxoptionSetMenuLoadpb
#define optionSetMenu_b4        UxOptionSetContext->UxoptionSetMenu_b4
#define optionSetMenuQuitpb     UxOptionSetContext->UxoptionSetMenuQuitpb
#define menu6_top_b2            UxOptionSetContext->Uxmenu6_top_b2
#define frame11                 UxOptionSetContext->Uxframe11
#define form11                  UxOptionSetContext->Uxform11
#define optSelectionMenu        UxOptionSetContext->UxoptSelectionMenu
#define optSelMenuInitpb        UxOptionSetContext->UxoptSelMenuInitpb
#define optSelMenuSnappb        UxOptionSetContext->UxoptSelMenuSnappb
#define optSelMenuIcProtpb      UxOptionSetContext->UxoptSelMenuIcProtpb
#define optSelMenuRecpb         UxOptionSetContext->UxoptSelMenuRecpb
#define optSelMenuMffrpb        UxOptionSetContext->UxoptSelMenuMffrpb
#define optSelMenuArchivepb     UxOptionSetContext->UxoptSelMenuArchivepb
#define optSelMenuShowpb        UxOptionSetContext->UxoptSelMenuShowpb
#define optSelectionMenu_b7     UxOptionSetContext->UxoptSelectionMenu_b7
#define optSelMenuDisplaypb     UxOptionSetContext->UxoptSelMenuDisplaypb
#define optSelnMenuProgLaunchpb UxOptionSetContext->UxoptSelnMenuProgLaunchpb
#define optionSelection         UxOptionSetContext->UxoptionSelection
#define frame10                 UxOptionSetContext->Uxframe10
#define optionSetForm           UxOptionSetContext->UxoptionSetForm

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	optionSet;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_optionSet( void );

#endif	/* _OPTIONSET_INCLUDED */
