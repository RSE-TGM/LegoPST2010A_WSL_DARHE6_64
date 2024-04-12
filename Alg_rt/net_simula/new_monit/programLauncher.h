/**********************************************************************
*
*       C Header:               programLauncher.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:43:10 1997 %
*
**********************************************************************/

/*******************************************************************************
       programLauncher.h
       This header file is included by programLauncher.c

*******************************************************************************/

#ifndef	_PROGRAMLAUNCHER_INCLUDED
#define	_PROGRAMLAUNCHER_INCLUDED


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
	Widget	UxprogramLauncher;
	Widget	Uxmenu8;
	Widget	Uxmenu8_p1;
	Widget	UxprogLaunchFileQuitpb;
	Widget	Uxmenu8_top_b1;
	Widget	Uxframe22;
	Widget	Uxform29;
	Widget	UxprogLaunchExecpb;
	Widget	UxprogLaunchQuitpb;
	Widget	UxrowColumn4;
	Widget	UxprogLaunchText[8];
	unsigned char	Uxcomandi[8][100];
	swidget	UxUxParent;
} _UxCprogramLauncher;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCprogramLauncher     *UxProgramLauncherContext;
#define programLauncher         UxProgramLauncherContext->UxprogramLauncher
#define menu8                   UxProgramLauncherContext->Uxmenu8
#define menu8_p1                UxProgramLauncherContext->Uxmenu8_p1
#define progLaunchFileQuitpb    UxProgramLauncherContext->UxprogLaunchFileQuitpb
#define menu8_top_b1            UxProgramLauncherContext->Uxmenu8_top_b1
#define frame22                 UxProgramLauncherContext->Uxframe22
#define form29                  UxProgramLauncherContext->Uxform29
#define progLaunchExecpb        UxProgramLauncherContext->UxprogLaunchExecpb
#define progLaunchQuitpb        UxProgramLauncherContext->UxprogLaunchQuitpb
#define rowColumn4              UxProgramLauncherContext->UxrowColumn4
#define progLaunchText          UxProgramLauncherContext->UxprogLaunchText
#define comandi                 UxProgramLauncherContext->Uxcomandi
#define UxParent                UxProgramLauncherContext->UxUxParent

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_programLauncher( swidget _UxUxParent );

#endif	/* _PROGRAMLAUNCHER_INCLUDED */
