/**********************************************************************
*
*       C Header:               archiveSavereq.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:33:14 1997 %
*
**********************************************************************/

/*******************************************************************************
       archiveSavereq.h
       This header file is included by archiveSavereq.c

*******************************************************************************/

#ifndef	_ARCHIVESAVEREQ_INCLUDED
#define	_ARCHIVESAVEREQ_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/CascadeB.h>
#include <Xm/RowColumn.h>
#include <Xm/TextF.h>
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
	Widget	Uxform14;
	Widget	Uxframe5;
	Widget	Uxform15;
	Widget	UxarchSaveReqQuitpb;
	Widget	UxarchSaveReqpb;
	Widget	Uxframe6;
	Widget	Uxform13;
	Widget	Uxlabel13;
	Widget	UxarchSaveReqCommText;
	Widget	UxarchSaveReqMenu;
	Widget	UxarchSaveMenuFile;
	Widget	UxarchSaveMenuFileQuit;
	Widget	UxarchSaveReqMenuFilecb;
	Widget	UxarchSaveReqMenuHelp;
	Widget	UxarchSaveReqMenuHelpComm;
	Widget	UxarchSaveReqMenuHelpcb;
	Widget	UxrowColumn2;
	Widget	Uxform16;
	Widget	Uxlabel15;
	Widget	UxarchSaveReqTinitText;
	Widget	Uxform17;
	Widget	Uxlabel16;
	Widget	UxarchSaveReqTfinText;
	Widget	Uxform18;
	Widget	Uxlabel17;
	Widget	UxarchSaveReqDiskText;
	Widget	Uxform19;
	Widget	Uxlabel18;
	Widget	UxarchSaveReqDiskavailText;
} _UxCarchiveSavereq;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCarchiveSavereq      *UxArchiveSavereqContext;
#define form14                  UxArchiveSavereqContext->Uxform14
#define frame5                  UxArchiveSavereqContext->Uxframe5
#define form15                  UxArchiveSavereqContext->Uxform15
#define archSaveReqQuitpb       UxArchiveSavereqContext->UxarchSaveReqQuitpb
#define archSaveReqpb           UxArchiveSavereqContext->UxarchSaveReqpb
#define frame6                  UxArchiveSavereqContext->Uxframe6
#define form13                  UxArchiveSavereqContext->Uxform13
#define label13                 UxArchiveSavereqContext->Uxlabel13
#define archSaveReqCommText     UxArchiveSavereqContext->UxarchSaveReqCommText
#define archSaveReqMenu         UxArchiveSavereqContext->UxarchSaveReqMenu
#define archSaveMenuFile        UxArchiveSavereqContext->UxarchSaveMenuFile
#define archSaveMenuFileQuit    UxArchiveSavereqContext->UxarchSaveMenuFileQuit
#define archSaveReqMenuFilecb   UxArchiveSavereqContext->UxarchSaveReqMenuFilecb
#define archSaveReqMenuHelp     UxArchiveSavereqContext->UxarchSaveReqMenuHelp
#define archSaveReqMenuHelpComm UxArchiveSavereqContext->UxarchSaveReqMenuHelpComm
#define archSaveReqMenuHelpcb   UxArchiveSavereqContext->UxarchSaveReqMenuHelpcb
#define rowColumn2              UxArchiveSavereqContext->UxrowColumn2
#define form16                  UxArchiveSavereqContext->Uxform16
#define label15                 UxArchiveSavereqContext->Uxlabel15
#define archSaveReqTinitText    UxArchiveSavereqContext->UxarchSaveReqTinitText
#define form17                  UxArchiveSavereqContext->Uxform17
#define label16                 UxArchiveSavereqContext->Uxlabel16
#define archSaveReqTfinText     UxArchiveSavereqContext->UxarchSaveReqTfinText
#define form18                  UxArchiveSavereqContext->Uxform18
#define label17                 UxArchiveSavereqContext->Uxlabel17
#define archSaveReqDiskText     UxArchiveSavereqContext->UxarchSaveReqDiskText
#define form19                  UxArchiveSavereqContext->Uxform19
#define label18                 UxArchiveSavereqContext->Uxlabel18
#define archSaveReqDiskavailText UxArchiveSavereqContext->UxarchSaveReqDiskavailText

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	archiveSavereq;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_archiveSavereq( void );

#endif	/* _ARCHIVESAVEREQ_INCLUDED */
