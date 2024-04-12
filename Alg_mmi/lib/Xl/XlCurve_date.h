
/*******************************************************************************
       XlCurve_date.h
       This header file is included by XlCurve_date.c

*******************************************************************************/

#ifndef	_XLCURVE_DATE_INCLUDED
#define	_XLCURVE_DATE_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/ArrowB.h>
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
	Widget	UxdateShell;
	Widget	Uxformdate;
	Widget	Uxformlab;
	Widget	Uxlabeldd;
	Widget	Uxlabelmm;
	Widget	Uxlabelyy;
	Widget	Uxlabelhr;
	Widget	Uxlabelmn;
	Widget	Uxformarrow;
	Widget	Uxformarrow1;
	Widget	UxarrowButUp1;
	Widget	UxarrowButUp2;
	Widget	Uxlabelval;
	Widget	UxarrowButDown1;
	Widget	UxarrowButDown2;
	Widget	Uxformarrow2;
	Widget	UxarrowButUp3;
	Widget	UxarrowButUp4;
	Widget	Uxlabelval1;
	Widget	UxarrowButDown3;
	Widget	UxarrowButDown4;
	Widget	Uxformarrow3;
	Widget	UxarrowButUp5;
	Widget	UxarrowButUp6;
	Widget	Uxlabelval2;
	Widget	UxarrowButDown5;
	Widget	UxarrowButDown6;
	Widget	Uxformarrow4;
	Widget	UxarrowButUp7;
	Widget	UxarrowButUp8;
	Widget	Uxlabelval3;
	Widget	UxarrowButDown7;
	Widget	UxarrowButDown8;
	Widget	Uxformarrow5;
	Widget	UxarrowButUp9;
	Widget	UxarrowButUp10;
	Widget	Uxlabelval4;
	Widget	UxarrowButDown9;
	Widget	UxarrowButDown10;
	Widget	UxpushButOK;
	Widget	UxpushButCanc;
	swidget	UxUxParent;
} _UxCdateShell;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCdateShell           *UxDateShellContext;
#define dateShell               UxDateShellContext->UxdateShell
#define formdate                UxDateShellContext->Uxformdate
#define formlab                 UxDateShellContext->Uxformlab
#define labeldd                 UxDateShellContext->Uxlabeldd
#define labelmm                 UxDateShellContext->Uxlabelmm
#define labelyy                 UxDateShellContext->Uxlabelyy
#define labelhr                 UxDateShellContext->Uxlabelhr
#define labelmn                 UxDateShellContext->Uxlabelmn
#define formarrow               UxDateShellContext->Uxformarrow
#define formarrow1              UxDateShellContext->Uxformarrow1
#define arrowButUp1             UxDateShellContext->UxarrowButUp1
#define arrowButUp2             UxDateShellContext->UxarrowButUp2
#define labelval                UxDateShellContext->Uxlabelval
#define arrowButDown1           UxDateShellContext->UxarrowButDown1
#define arrowButDown2           UxDateShellContext->UxarrowButDown2
#define formarrow2              UxDateShellContext->Uxformarrow2
#define arrowButUp3             UxDateShellContext->UxarrowButUp3
#define arrowButUp4             UxDateShellContext->UxarrowButUp4
#define labelval1               UxDateShellContext->Uxlabelval1
#define arrowButDown3           UxDateShellContext->UxarrowButDown3
#define arrowButDown4           UxDateShellContext->UxarrowButDown4
#define formarrow3              UxDateShellContext->Uxformarrow3
#define arrowButUp5             UxDateShellContext->UxarrowButUp5
#define arrowButUp6             UxDateShellContext->UxarrowButUp6
#define labelval2               UxDateShellContext->Uxlabelval2
#define arrowButDown5           UxDateShellContext->UxarrowButDown5
#define arrowButDown6           UxDateShellContext->UxarrowButDown6
#define formarrow4              UxDateShellContext->Uxformarrow4
#define arrowButUp7             UxDateShellContext->UxarrowButUp7
#define arrowButUp8             UxDateShellContext->UxarrowButUp8
#define labelval3               UxDateShellContext->Uxlabelval3
#define arrowButDown7           UxDateShellContext->UxarrowButDown7
#define arrowButDown8           UxDateShellContext->UxarrowButDown8
#define formarrow5              UxDateShellContext->Uxformarrow5
#define arrowButUp9             UxDateShellContext->UxarrowButUp9
#define arrowButUp10            UxDateShellContext->UxarrowButUp10
#define labelval4               UxDateShellContext->Uxlabelval4
#define arrowButDown9           UxDateShellContext->UxarrowButDown9
#define arrowButDown10          UxDateShellContext->UxarrowButDown10
#define pushButOK               UxDateShellContext->UxpushButOK
#define pushButCanc             UxDateShellContext->UxpushButCanc
#define UxParent                UxDateShellContext->UxUxParent

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_dateShell();

#endif	/* _XLCURVE_DATE_INCLUDED */
