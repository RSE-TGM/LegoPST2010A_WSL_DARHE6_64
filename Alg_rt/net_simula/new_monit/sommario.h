/**********************************************************************
*
*       C Header:               sommario.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:46:13 1997 %
*
**********************************************************************/


/*******************************************************************************
       sommario.h
       This header file is included by sommario.c

*******************************************************************************/

#ifndef	_SOMMARIO_INCLUDED
#define	_SOMMARIO_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/ScrolledW.h>
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
	Widget	UxsommMenu;
	Widget	UxsommMenuFile;
	Widget	UxsommMenuFileQuitpb;
	Widget	UxsommMenu_top_b1;
	Widget	UxsommMenuHelp;
	Widget	UxsommMenuHelppb;
	Widget	UxsommMenu_top_b2;
	Widget	Uxframe17;
	Widget	Uxform33;
	Widget	UxquitMalfSommpb;
	Widget	UxsommarioScrollWin;
	Widget	UxsommRc;
	Widget	UxsommParent;
	int	Uxtipo;
} _UxCsommario;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCsommario            *UxSommarioContext;
#define sommMenu                UxSommarioContext->UxsommMenu
#define sommMenuFile            UxSommarioContext->UxsommMenuFile
#define sommMenuFileQuitpb      UxSommarioContext->UxsommMenuFileQuitpb
#define sommMenu_top_b1         UxSommarioContext->UxsommMenu_top_b1
#define sommMenuHelp            UxSommarioContext->UxsommMenuHelp
#define sommMenuHelppb          UxSommarioContext->UxsommMenuHelppb
#define sommMenu_top_b2         UxSommarioContext->UxsommMenu_top_b2
#define frame17                 UxSommarioContext->Uxframe17
#define form33                  UxSommarioContext->Uxform33
#define quitMalfSommpb          UxSommarioContext->UxquitMalfSommpb
#define sommarioScrollWin       UxSommarioContext->UxsommarioScrollWin
#define sommRc                  UxSommarioContext->UxsommRc
#define sommParent              UxSommarioContext->UxsommParent
#define tipo                    UxSommarioContext->Uxtipo

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	sommario;
extern Widget	actMalfSommpb;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_sommario( Widget _UxsommParent, int _Uxtipo );

#endif	/* _SOMMARIO_INCLUDED */
