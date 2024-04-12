/**********************************************************************
*
*       C Header:               sessionName.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Mon May 18 17:47:55 1998 %
*
**********************************************************************/


/*******************************************************************************
       sessionName.h
       This header file is included by sessionName.c

*******************************************************************************/

#ifndef	_SESSIONNAME_INCLUDED
#define	_SESSIONNAME_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
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
	Widget	Uxform5;
	Widget	Uxframe7;
	Widget	Uxform6;
	Widget	UxsessionNameSavepb;
	Widget	Uxlabel2;
	Widget	Uxform8;
	Widget	Uxlabel3;
	Widget	UxsessionTitleEntrytext;
	unsigned char	*Uxtit;
} _UxCsessionName;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCsessionName         *UxSessionNameContext;
#define form5                   UxSessionNameContext->Uxform5
#define frame7                  UxSessionNameContext->Uxframe7
#define form6                   UxSessionNameContext->Uxform6
#define sessionNameSavepb       UxSessionNameContext->UxsessionNameSavepb
#define label2                  UxSessionNameContext->Uxlabel2
#define form8                   UxSessionNameContext->Uxform8
#define label3                  UxSessionNameContext->Uxlabel3
#define sessionTitleEntrytext   UxSessionNameContext->UxsessionTitleEntrytext
#define tit                     UxSessionNameContext->Uxtit

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	sessionName;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_sessionName( unsigned char *_Uxtit );

#endif	/* _SESSIONNAME_INCLUDED */
