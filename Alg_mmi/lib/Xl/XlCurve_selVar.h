
/*******************************************************************************
       XlCurve_selVar.h
       This header file is included by XlCurve_selVar.c

*******************************************************************************/

#ifndef	_XLCURVE_SELVAR_INCLUDED
#define	_XLCURVE_SELVAR_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>

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
	Widget	UxselectVar;
	swidget	UxUxParent;
	swidget	UxtextName;
	swidget	UxtextDescr;
} _UxCselectVar;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCselectVar           *UxSelectVarContext;
#define selectVar               UxSelectVarContext->UxselectVar
#define UxParent                UxSelectVarContext->UxUxParent
#define textName                UxSelectVarContext->UxtextName
#define textDescr               UxSelectVarContext->UxtextDescr

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_selectVar();

#endif	/* _XLCURVE_SELVAR_INCLUDED */
