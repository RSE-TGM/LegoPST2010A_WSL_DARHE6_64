/**********************************************************************
*
*       C Header:               processStart.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Mon May 18 17:59:59 1998 %
*
**********************************************************************/


/*******************************************************************************
       processStart.h
       This header file is included by processStart.c

*******************************************************************************/

#ifndef	_PROCESSSTART_INCLUDED
#define	_PROCESSSTART_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Label.h>
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
	Widget	UxprocessStart;
	Widget	Uxframe21;
	Widget	Uxform48;
	Widget	UxprocessStartOkpb;
	Widget	UxprocessStartQuitpb;
	Widget	UxdisplaySelectForm;
	Widget	Uxlabel1;
	Widget	UxstartProcessLabel;
	Widget	UxMenuShellDisplay;
	Widget	Uxmenu8_p1;
	Widget	UxdisplayMenu;
	Widget	UxdisplaySelectionButton[5];
	int	UxcloseRequest;
	unsigned char	UxselectedDisplay[100];
	swidget	UxUxParent;
	unsigned char	*Uxtesto;
} _UxCprocessStart;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCprocessStart        *UxProcessStartContext;
#define processStart            UxProcessStartContext->UxprocessStart
#define frame21                 UxProcessStartContext->Uxframe21
#define form48                  UxProcessStartContext->Uxform48
#define processStartOkpb        UxProcessStartContext->UxprocessStartOkpb
#define processStartQuitpb      UxProcessStartContext->UxprocessStartQuitpb
#define displaySelectForm       UxProcessStartContext->UxdisplaySelectForm
#define label1                  UxProcessStartContext->Uxlabel1
#define startProcessLabel       UxProcessStartContext->UxstartProcessLabel
#define MenuShellDisplay        UxProcessStartContext->UxMenuShellDisplay
#define menu8_p1                UxProcessStartContext->Uxmenu8_p1
#define displayMenu             UxProcessStartContext->UxdisplayMenu
#define displaySelectionButton  UxProcessStartContext->UxdisplaySelectionButton
#define closeRequest            UxProcessStartContext->UxcloseRequest
#define selectedDisplay         UxProcessStartContext->UxselectedDisplay
#define UxParent                UxProcessStartContext->UxUxParent
#define testo                   UxProcessStartContext->Uxtesto

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

unsigned char	*create_processStart( swidget _UxUxParent, unsigned char *_Uxtesto );

#endif	/* _PROCESSSTART_INCLUDED */
