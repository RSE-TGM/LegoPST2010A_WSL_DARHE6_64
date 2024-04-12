
/*******************************************************************************
       topLevelShell1.h
       This header file is included by topLevelShell1.c

*******************************************************************************/

#ifndef	_TOPLEVELSHELL1_INCLUDED
#define	_TOPLEVELSHELL1_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>
#include <Xm/RowColumn.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>
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
	Widget	Uxform1;
	Widget	Uxform34;
	Widget	UxshutdownButton2;
	Widget	UxstartupButton;
	Widget	Uxseparator1;
	Widget	Uxmenu9;
	Widget	UxmasterMonitMenu;
	Widget	UxmasterMonitMenuQuitpb;
	Widget	Uxmenu9_top_b1;
	Widget	UxbulletinBoard1;
	Widget	UxsimulatorPathLabel;
	Widget	UxsimulatorPathText;
	Widget	UxsimulatorPathName;
	Widget	UxsimulatorNameText;
} _UxCtopLevelShell1;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCtopLevelShell1      *UxTopLevelShell1Context;
#define form1                   UxTopLevelShell1Context->Uxform1
#define form34                  UxTopLevelShell1Context->Uxform34
#define shutdownButton2         UxTopLevelShell1Context->UxshutdownButton2
#define startupButton           UxTopLevelShell1Context->UxstartupButton
#define separator1              UxTopLevelShell1Context->Uxseparator1
#define menu9                   UxTopLevelShell1Context->Uxmenu9
#define masterMonitMenu         UxTopLevelShell1Context->UxmasterMonitMenu
#define masterMonitMenuQuitpb   UxTopLevelShell1Context->UxmasterMonitMenuQuitpb
#define menu9_top_b1            UxTopLevelShell1Context->Uxmenu9_top_b1
#define bulletinBoard1          UxTopLevelShell1Context->UxbulletinBoard1
#define simulatorPathLabel      UxTopLevelShell1Context->UxsimulatorPathLabel
#define simulatorPathText       UxTopLevelShell1Context->UxsimulatorPathText
#define simulatorPathName       UxTopLevelShell1Context->UxsimulatorPathName
#define simulatorNameText       UxTopLevelShell1Context->UxsimulatorNameText

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	topLevelShell1;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_topLevelShell1( void );

#endif	/* _TOPLEVELSHELL1_INCLUDED */
