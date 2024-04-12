/**********************************************************************
*
*       C Header:               fileSelection.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:36:30 1997 %
*
**********************************************************************/

/*******************************************************************************
       fileSelection.h
       This header file is included by fileSelection.c

*******************************************************************************/

#ifndef	_FILESELECTION_INCLUDED
#define	_FILESELECTION_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/FileSB.h>

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
	unsigned char	Uxfile_target[100];
	int	Uxr;
	Widget	Uxw;
	int	Uxmodo;
	int	Uxapp;
} _UxCfileSelection;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCfileSelection       *UxFileSelectionContext;
#define file_target             UxFileSelectionContext->Uxfile_target
#define r                       UxFileSelectionContext->Uxr
#define w                       UxFileSelectionContext->Uxw
#define modo                    UxFileSelectionContext->Uxmodo
#define app                     UxFileSelectionContext->Uxapp

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	fileSelection;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

unsigned char	*create_fileSelection( Widget _Uxw, int _Uxmodo, int _Uxapp );

#endif	/* _FILESELECTION_INCLUDED */
