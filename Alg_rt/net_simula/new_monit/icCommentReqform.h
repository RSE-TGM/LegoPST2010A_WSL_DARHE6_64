
/*******************************************************************************
       icCommentReqform.h
       This header file is included by icCommentReqform.c

*******************************************************************************/

#ifndef	_ICCOMMENTREQFORM_INCLUDED
#define	_ICCOMMENTREQFORM_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Label.h>
#include <Xm/TextF.h>
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
	Widget	Uxframe4;
	Widget	Uxform9;
	Widget	UxicCommantQuitpb;
	Widget	UxicCommentOkpb;
	Widget	UxicCommentText;
	Widget	UxicCommentTitle;
	int	Uxic_select;
	unsigned char	*UxprevComment;
} _UxCicCommentReqform;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCicCommentReqform    *UxIcCommentReqformContext;
#define frame4                  UxIcCommentReqformContext->Uxframe4
#define form9                   UxIcCommentReqformContext->Uxform9
#define icCommantQuitpb         UxIcCommentReqformContext->UxicCommantQuitpb
#define icCommentOkpb           UxIcCommentReqformContext->UxicCommentOkpb
#define icCommentText           UxIcCommentReqformContext->UxicCommentText
#define icCommentTitle          UxIcCommentReqformContext->UxicCommentTitle
#define ic_select               UxIcCommentReqformContext->Uxic_select
#define prevComment             UxIcCommentReqformContext->UxprevComment

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	icCommentReqform;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_icCommentReqform( int _Uxic_select, unsigned char *_UxprevComment );

#endif	/* _ICCOMMENTREQFORM_INCLUDED */
