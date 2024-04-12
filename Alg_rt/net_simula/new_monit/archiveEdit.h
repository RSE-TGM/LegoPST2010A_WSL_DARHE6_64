/**********************************************************************
*
*       C Header:               archiveEdit.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:32:56 1997 %
*
**********************************************************************/

/*******************************************************************************
       archiveEdit.h
       This header file is included by archiveEdit.c

*******************************************************************************/

#ifndef	_ARCHIVEEDIT_INCLUDED
#define	_ARCHIVEEDIT_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/RowColumn.h>
#include <Xm/ScrolledW.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
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
	Widget	Uxform24;
	Widget	Uxframe9;
	Widget	Uxform25;
	Widget	UxpushButton16;
	Widget	UxpushButton17;
	Widget	UxpushButton18;
	Widget	Uxlabel19;
	Widget	Uxform26;
	Widget	UxscrolledWindow2;
	Widget	UxrowColumn3;
	Widget	Uxform20;
	Widget	Uxlabel20;
	Widget	Uxlabel21;
	Widget	Uxlabel22;
	Widget	Uxlabel23;
} _UxCarchiveEdit;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCarchiveEdit         *UxArchiveEditContext;
#define form24                  UxArchiveEditContext->Uxform24
#define frame9                  UxArchiveEditContext->Uxframe9
#define form25                  UxArchiveEditContext->Uxform25
#define pushButton16            UxArchiveEditContext->UxpushButton16
#define pushButton17            UxArchiveEditContext->UxpushButton17
#define pushButton18            UxArchiveEditContext->UxpushButton18
#define label19                 UxArchiveEditContext->Uxlabel19
#define form26                  UxArchiveEditContext->Uxform26
#define scrolledWindow2         UxArchiveEditContext->UxscrolledWindow2
#define rowColumn3              UxArchiveEditContext->UxrowColumn3
#define form20                  UxArchiveEditContext->Uxform20
#define label20                 UxArchiveEditContext->Uxlabel20
#define label21                 UxArchiveEditContext->Uxlabel21
#define label22                 UxArchiveEditContext->Uxlabel22
#define label23                 UxArchiveEditContext->Uxlabel23

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	archiveEdit;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_archiveEdit( void );

#endif	/* _ARCHIVEEDIT_INCLUDED */
