/**********************************************************************
*
*       C Header:               misc1_ds.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:05:36 1996 %
*
**********************************************************************/
/*
 * COMPONENT_NAME: AIC     AIXwindows Interface Composer
 *
 * ORIGINS: 58
 *
 * Licensed Materials - Property of IBM
 * 5756-027 (C) Copyright International Business Machines Corp. 1991, 1992.
 * All Rights Reserved.
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */
/***   stitute an acknowledgment that publication has  occurred  nor  to   ***/
/***   imply  any  waiver  of confidentiality.  The year included in the   ***/
/***   notice is the year of the creation of the work.                     ***/
/***                                                                       ***/
/*****************************************************************************/

#ifndef	_UX_MISC1_DS_H_
#define	_UX_MISC1_DS_H_
#ifdef	XOPEN_CATALOG
#include	"misc1_msg.h"
#endif
#define	DS_MS_MISC_NO_COLORMAP	"151 Cannot convert string name to a color. No colormap\n\
was found.\n"
#define	DS_MS_MISC_NO_COLORNAME	"152 The color name %s does not exist.\n"
#define	DS_MS_MISC_COLORMAP_ALLOC	"153 Cannot allocate colormap entry for %s\n."
#define	DS_MS_MISC_MAX_PROCS	"154 The maximum number of active subprocesses is %d.\n\
Use UxDelete() to remove subprocesses which are no longer required.\n"
#define	DS_MS_MISC_CALLOC_ERR	"155 calloc() failed.\n"
#define	DS_MS_MISC_INV_HNDL	"156 The subprocess handle is not valid.\n"
#define	DS_MS_MISC_NOT_HNDL	"157 The entry is not a handle."
#define	DS_MS_MISC_MALLOC_ERR	"158 malloc() failed.\n"
#define	DS_MS_MISC_SYS_ERR		"A system error occurred.\n"
#define	DS_MS_MISC_STREAM_DRV_ERR	"159 No stream drivers are available.\n"
#define	DS_MS_MISC_PTY_DRV_ERR	"160 No pty/tty drivers are available.\n"
#define	DS_MS_MISC_NO_SUBPROCS	"161 The subprocess functionality is not implemented.\n"
#define	DS_MS_MISC_PIPE_ERR	"162 Error on pipe.\n"
#define	DS_MS_MISC_SUBPROC_RUNNIN	"163 The subprocess is already active.\n"
#define	DS_MS_MISC_SUBPROC_NOACT	"164 The subprocess is not active.\n"
#define	DS_MS_MISC_W_SUBPROC_ERR	"165 Cannot write to subprocess.\n"
#define	DS_MS_MISC_INV_SPRC_STRUCT	"166 The subprocess structure is not valid.\n"
#define	DS_MS_MISC_INV_OUT_FNCTN	"167 The output function is not valid.\n"
#define	DS_MS_MISC_R_SUBPROC_ERR	"168 Cannot read from subprocess.\n"
#define	DS_MS_MISC_STAT_FAIL	"174 Cannot stat /dev/ptc\n"
#define	DS_MS_MISC_OPEN_FAIL	"175 Cannot open /dev/ptc\n"
#define	DS_MS_MISC_INTERNALERRORFORMAT	"169 An internal error occurred in the file %s\n\
on line number %d.\n"
#define	DS_MS_MISC_WRONG_FLAG	"170 The conversion flag is not valid.\n"
#define	DS_MS_MISC_NO_MATCH	"171 Cannot convert resource value.\n"
#define	DS_MS_MISC_ATTACHMENT_MSG1	"and an attachment widget must be specified\n\
if an attach_widget or attach_opposite_widget is specified."
#define	DS_MS_MISC_NUM_ELEM_SEL	"positive integer or 0 which is less than or equal\n\
to the number of elements in the selection array"
#define	DS_MS_MISC_NO_CONV_ROUTINE	"172 No conversion routine exists to convert %s to %s.\n"
#define	DS_MS_MISC_SELECTARRAY_ERR	"string containing selectionArrayCount items,\n\
separated by spaces, and selected from:"
#define	DS_MS_MISC_WDGT_PROMPT	"\n\nwidget:   "
#define	DS_MS_MISC1_PARM_ERR	"173 The second widget parameter in the call to\n\
UxCenterVisibly() is not an ancestor \n\
of the first widget parameter.\n"
#define	DS_MS_MISC1_NULL_PROC_ERR	"176 NULL process name in UxCreateSubProc().\n"
#define	DS_MS_MISC1_DIAG_STYLE_MSG	"dialog_work_area must be used for a widget that\n\
does not have a DialogShell as parent, but cannot\n\
be used for a widget that has a DialogShell as parent.\n"
#define	DS_MS_MISC1_LONG_FNAME_UNUSED "\
The specified filename length exceeds the limit of 14 characters \n\
allowed by your system. Please use a shorter name."
#define	DS_MS_MISC1_LONG_FNAME "\
The given filename exceeds the 14 characters allowed by your system.\n\
Use a shorter name instead."
#endif
