
/*******************************************************************************
       XlCurve_dialog.h
       This header file is included by XlCurve_dialog.c

*******************************************************************************/

#ifndef	_XLCURVE_DIALOG_INCLUDED
#define	_XLCURVE_DIALOG_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/ToggleB.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/DialogS.h>

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
	Widget	UxdialogShell1;
	Widget	Uxform1;
	Widget	Uxlabel78;
	Widget	UxrowColumn1;
	Widget	UxtoggleButton1;
	Widget	UxtoggleButton2;
	Widget	UxtoggleButton3;
	Widget	UxpushButOk;
	Widget	UxpushButExit;
	swidget	UxUxParent;
	int	*Uxtoggle;
} _UxCdialogShell1;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCdialogShell1        *UxDialogShell1Context;
#define dialogShell1            UxDialogShell1Context->UxdialogShell1
#define form1                   UxDialogShell1Context->Uxform1
#define label78                 UxDialogShell1Context->Uxlabel78
#define rowColumn1              UxDialogShell1Context->UxrowColumn1
#define toggleButton1           UxDialogShell1Context->UxtoggleButton1
#define toggleButton2           UxDialogShell1Context->UxtoggleButton2
#define toggleButton3           UxDialogShell1Context->UxtoggleButton3
#define pushButOk               UxDialogShell1Context->UxpushButOk
#define pushButExit             UxDialogShell1Context->UxpushButExit
#define UxParent                UxDialogShell1Context->UxUxParent
#define toggle                  UxDialogShell1Context->Uxtoggle

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_dialogShell1();

#endif	/* _XLCURVE_DIALOG_INCLUDED */
