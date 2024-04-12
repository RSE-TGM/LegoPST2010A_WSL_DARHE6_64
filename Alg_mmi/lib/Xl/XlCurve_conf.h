
/*******************************************************************************
       XlCurve_conf.h
       This header file is included by XlCurve_conf.c

*******************************************************************************/

#ifndef	_XLCURVE_CONF_INCLUDED
#define	_XLCURVE_CONF_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
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
	Widget	UxconfRunTime;
	Widget	Uxform2;
	Widget	UxlabTitle;
	Widget	UxrowColumn2;
	Widget	UxpushBut1;
	Widget	UxpushBut6;
	Widget	UxpushBut2;
	Widget	UxpushBut7;
	Widget	UxpushBut3;
	Widget	UxpushBut8;
	Widget	UxpushBut4;
	Widget	UxpushBut9;
	Widget	UxpushBut5;
	Widget	UxpushBut10;
	Widget	Uxform3;
	Widget	UxokBut;
	Widget	UxcancelBut;
	swidget	UxUxParent;
	int	UxnumCurveConf;
} _UxCconfRunTime;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCconfRunTime         *UxConfRunTimeContext;
#define confRunTime             UxConfRunTimeContext->UxconfRunTime
#define form2                   UxConfRunTimeContext->Uxform2
#define labTitle                UxConfRunTimeContext->UxlabTitle
#define rowColumn2              UxConfRunTimeContext->UxrowColumn2
#define pushBut1                UxConfRunTimeContext->UxpushBut1
#define pushBut6                UxConfRunTimeContext->UxpushBut6
#define pushBut2                UxConfRunTimeContext->UxpushBut2
#define pushBut7                UxConfRunTimeContext->UxpushBut7
#define pushBut3                UxConfRunTimeContext->UxpushBut3
#define pushBut8                UxConfRunTimeContext->UxpushBut8
#define pushBut4                UxConfRunTimeContext->UxpushBut4
#define pushBut9                UxConfRunTimeContext->UxpushBut9
#define pushBut5                UxConfRunTimeContext->UxpushBut5
#define pushBut10               UxConfRunTimeContext->UxpushBut10
#define form3                   UxConfRunTimeContext->Uxform3
#define okBut                   UxConfRunTimeContext->UxokBut
#define cancelBut               UxConfRunTimeContext->UxcancelBut
#define UxParent                UxConfRunTimeContext->UxUxParent
#define numCurveConf            UxConfRunTimeContext->UxnumCurveConf

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_confRunTime();

#endif	/* _XLCURVE_CONF_INCLUDED */
