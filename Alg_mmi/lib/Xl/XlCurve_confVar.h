
/*******************************************************************************
       XlCurve_confVar.h
       This header file is included by XlCurve_confVar.c

*******************************************************************************/

#ifndef	_XLCURVE_CONFVAR_INCLUDED
#define	_XLCURVE_CONFVAR_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
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
	Widget	UxconfVar;
	Widget	Uxform4;
	Widget	Uxform5;
	Widget	UxpushButok;
	Widget	UxpushButcancel;
	Widget	Uxform6;
	Widget	Uxlabel1;
	Widget	UxpushButton1;
	Widget	UxtextField1;
	Widget	Uxform7;
	Widget	Uxlabel2;
	Widget	UxpushButton2;
	Widget	UxtextField2;
	Widget	Uxlabel3;
	Widget	UxtextField3;
	Widget	Uxform8;
	Widget	Uxlabel4;
	Widget	Uxlabel5;
	Widget	Uxlabel6;
	Widget	UxtextField4;
	Widget	UxtextField5;
	Widget	UxtextField6;
	Widget	Uxlabel7;
	swidget	UxUxParent;
	int	Uxpos_var;
	unsigned char	*Uxstr_curr;
} _UxCconfVar;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCconfVar             *UxConfVarContext;
#define confVar                 UxConfVarContext->UxconfVar
#define form4                   UxConfVarContext->Uxform4
#define form5                   UxConfVarContext->Uxform5
#define pushButok               UxConfVarContext->UxpushButok
#define pushButcancel           UxConfVarContext->UxpushButcancel
#define form6                   UxConfVarContext->Uxform6
#define label1                  UxConfVarContext->Uxlabel1
#define pushButton1             UxConfVarContext->UxpushButton1
#define textField1              UxConfVarContext->UxtextField1
#define form7                   UxConfVarContext->Uxform7
#define label2                  UxConfVarContext->Uxlabel2
#define pushButton2             UxConfVarContext->UxpushButton2
#define textField2              UxConfVarContext->UxtextField2
#define label3                  UxConfVarContext->Uxlabel3
#define textField3              UxConfVarContext->UxtextField3
#define form8                   UxConfVarContext->Uxform8
#define label4                  UxConfVarContext->Uxlabel4
#define label5                  UxConfVarContext->Uxlabel5
#define label6                  UxConfVarContext->Uxlabel6
#define textField4              UxConfVarContext->UxtextField4
#define textField5              UxConfVarContext->UxtextField5
#define textField6              UxConfVarContext->UxtextField6
#define label7                  UxConfVarContext->Uxlabel7
#define UxParent                UxConfVarContext->UxUxParent
#define pos_var                 UxConfVarContext->Uxpos_var
#define str_curr                UxConfVarContext->Uxstr_curr

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_confVar();

#endif	/* _XLCURVE_CONFVAR_INCLUDED */
