
/*******************************************************************************
       attenzioneDialog.h
       This header file is included by attenzioneDialog.c

*******************************************************************************/

#ifndef	_ATTENZIONEDIALOG_INCLUDED
#define	_ATTENZIONEDIALOG_INCLUDED


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
	Widget	Uxpadre_warn;
	unsigned char	*Uxwarning_message;
	int	Uxmodo;
} _UxCattenzioneDialog;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCattenzioneDialog    *UxAttenzioneDialogContext;
#define padre_warn              UxAttenzioneDialogContext->Uxpadre_warn
#define warning_message         UxAttenzioneDialogContext->Uxwarning_message
#define modo                    UxAttenzioneDialogContext->Uxmodo

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	attenzioneDialog;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

int	create_attenzioneDialog( Widget _Uxpadre_warn, unsigned char *_Uxwarning_message, int _Uxmodo );

#endif	/* _ATTENZIONEDIALOG_INCLUDED */
