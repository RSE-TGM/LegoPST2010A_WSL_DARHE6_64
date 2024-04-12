/**********************************************************************
*
*       C Header:               dataRequest.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Mon May 18 17:54:20 1998 %
*
**********************************************************************/

/*******************************************************************************
       dataRequest.h
       This header file is included by dataRequest.c

*******************************************************************************/

#ifndef	_DATAREQUEST_INCLUDED
#define	_DATAREQUEST_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
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
	Widget	UxdataRequest;
	Widget	Uxw;
	unsigned char	*Uxlabel_string;
	unsigned char	*Uxact;
} _UxCdataRequest;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCdataRequest         *UxDataRequestContext;
#define dataRequest             UxDataRequestContext->UxdataRequest
#define w                       UxDataRequestContext->Uxw
#define label_string            UxDataRequestContext->Uxlabel_string
#define act                     UxDataRequestContext->Uxact

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

unsigned char	*create_dataRequest( Widget _Uxw, unsigned char *_Uxlabel_string, unsigned char *_Uxact );

#endif	/* _DATAREQUEST_INCLUDED */
