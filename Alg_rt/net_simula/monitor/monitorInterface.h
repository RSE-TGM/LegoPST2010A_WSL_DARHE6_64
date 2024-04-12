
/*******************************************************************************
       monitorInterface.h
       This header file is included by monitorInterface.c

*******************************************************************************/

#ifndef	_MONITORINTERFACE_INCLUDED
#define	_MONITORINTERFACE_INCLUDED


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
} _UxCmonitorInterface;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCmonitorInterface    *UxMonitorInterfaceContext;
#define form1                   UxMonitorInterfaceContext->Uxform1
#define form34                  UxMonitorInterfaceContext->Uxform34
#define shutdownButton2         UxMonitorInterfaceContext->UxshutdownButton2
#define startupButton           UxMonitorInterfaceContext->UxstartupButton
#define separator1              UxMonitorInterfaceContext->Uxseparator1
#define menu9                   UxMonitorInterfaceContext->Uxmenu9
#define masterMonitMenu         UxMonitorInterfaceContext->UxmasterMonitMenu
#define masterMonitMenuQuitpb   UxMonitorInterfaceContext->UxmasterMonitMenuQuitpb
#define menu9_top_b1            UxMonitorInterfaceContext->Uxmenu9_top_b1
#define bulletinBoard1          UxMonitorInterfaceContext->UxbulletinBoard1
#define simulatorPathLabel      UxMonitorInterfaceContext->UxsimulatorPathLabel
#define simulatorPathText       UxMonitorInterfaceContext->UxsimulatorPathText
#define simulatorPathName       UxMonitorInterfaceContext->UxsimulatorPathName
#define simulatorNameText       UxMonitorInterfaceContext->UxsimulatorNameText

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	monitorInterface;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_monitorInterface( void );

#endif	/* _MONITORINTERFACE_INCLUDED */
