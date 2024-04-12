
/*******************************************************************************
       XlCurve_warningBox.h
       This header file is included by XlCurve_warningBox.c

*******************************************************************************/

#ifndef	_XLCURVE_WARNINGBOX_INCLUDED
#define	_XLCURVE_WARNINGBOX_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/MessageB.h>

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
	Widget	UxwarningDialog1;
	swidget	UxUxParent;
	int	Uxparametro;
} _UxCwarningDialog1;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCwarningDialog1      *UxWarningDialog1Context;
#define warningDialog1          UxWarningDialog1Context->UxwarningDialog1
#define UxParent                UxWarningDialog1Context->UxUxParent
#define parametro               UxWarningDialog1Context->Uxparametro

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_warningDialog1();

#endif	/* _XLCURVE_WARNINGBOX_INCLUDED */
