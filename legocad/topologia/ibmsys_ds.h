/**********************************************************************
*
*       C Header:               ibmsys_ds.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:06:15 1996 %
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

#ifndef	_UX_IBMSYS_DS_H_
#define	_UX_IBMSYS_DS_H_
#ifdef	XOPEN_CATALOG
#include	"ibmsys_msg.h"
#endif
#define	DS_MS_SYS_U_TASKNAME	"AIC"
#define	DS_MS_SYS_RSRC_NAME	"Aic"
#define	DS_MS_SYS_TASKNAME		"aic"
#define	DS_MS_SYS_U_TASKDIR	"AICDIR"
#define	DS_MS_SYS_U_TASKDIR_ENV	"AICDIR="
#define	DS_MS_SYS_TASKDIR		"aicdir"
#define	DS_MS_SYS_RESOURCE_VAR	"Aic.aicdir"
#define	DS_MS_SYS_BINDIR		"bindir"
#define	DS_MS_SYS_CONFIGDIR	"configdir"
#define	DS_MS_SYS_RUNTIME_RSRC_NAME	"Aicdemo"
#define	DS_MS_SYS_PREFIX	"AIC: "
#define	DS_MS_SYS_FULL_NAME        "AIC"
#define	DS_MS_SYS_SCCS_VERSION_NUM_UNUSED1	"@(#) AIC: 1.0 / UIM/X 2.0"
#define	DS_MS_SYS_SCCS_VERSION_NUM          "@(#) AIXwindows Interface Composer: 1.1.1 / UIM/X: 2.0.1 (aic) - User Interface Management System"
#define	DS_MS_SYS_CGEN_SCCS_VERSION_NUM     "@(#) AIXwindows Interface Composer: 1.1.1 / UIM/X: 2.0.1 (uxcgen) - C Code Generator"
#define	DS_MS_SYS_READUIL_SCCS_VERSION_NUM  "@(#) AIXwindows Interface Composer: 1.1.1 / UIM/X: 2.0.1 (uxreaduil) - UIL translator"
#define	DS_MS_SYS_KEYGEN_SCCS_VERSION_NUM   "@(#) AIXwindows Interface Composer: 1.1.1 / UIM/X: 2.0.1 (uxkeygen) - Key Generator"
#define	DS_MS_SYS_SERVERD_SCCS_VERSION_NUM  "@(#) AIXwindows Interface Composer: 1.1.1 / UIM/X: 2.0.1 (uxserverd) - Server Daemon"
#define	DS_MS_MD_USAGE1	"Usage: %s import-source source [target]\n"
#define	DS_MS_MD_USAGE2	"        import-source: binary from which runtime symbols are to be resolved\n"
#define	DS_MS_MD_USAGE3	"        source:        a non-dynamic loadable module\n"
#define	DS_MS_MD_USAGE4	"        target:        the name of the new module to create\n"
#define	DS_MS_MD_USAGE5	"    by default the new module will be named source.dyn\n"
#define	DS_MS_MD_USAGE6	"    if target is a directory, the new module name will be target/source.dyn\n"
#define	DS_MS_MD_NO_READ		"%s: 841 The file %s cannot be read.\n"
#define	DS_MS_MD_IS_A_DIR		"%s: 842 %s is a directory, specify a regular file.\n"
#define	DS_MS_MD_NO_DIR		"%s: 843 The directory %s does not exist.\n"
#define	DS_MS_MD_DIR_NO_WRITE	"%s: 844 The directory %s cannot be written to.\n"
#define	DS_MS_MD_FAILED_COMM	"%s: 845 The nm command failed.  The error code is %s.\n"
#define	DS_MS_MD_NO_SYMS		"%s: 846 No exported symbols were found in the file %s.\n"
#define	DS_MS_MD_TMP_FULL		"%s: 847 The directory /tmp is full.\n"
#define	DS_MS_MD_FAILED_BIND	"%s: 848 The bind command failed for file %s.  The error code is %s.\n"
#define	DS_MS_MD_FILE_NO_WRITE	"%s: 849 The directory %s cannot be written to.\n"
#define	DS_MS_MD_FAILED_MV		"%s: 850 Renaming file %s to %s failed.  The error code is %s.\n"
#define	DS_MS_UDL_SYM_NO_REPLACE	"The symbol %s already exists, it will not be replaced.\n"
#define	DS_MS_UDL_SYM_REPLACE	"The symbol %s already exists, it will be replaced.\n"
#define	DS_MS_UDL_SYM_BAD_STORAGE	"186 The storage class %d, for the symbol %s is not known.\n"
#define	DS_MS_UDL_SYM_FOUND	"The following symbols were found:\n"
#define	DS_MS_UDL_SYM_NAME		"    %s\n"
#define	DS_MS_UDL_SYM_ELLIPSIS	"    ..."
#define	DS_MS_UDL_FILE_PROMPT	"Enter the name of the object file to load."
#define	DS_MS_UDL_FILE_STATUS	"Loading symbols from the file %s ...\n"
#define	DS_MS_UDL_NO_SYMS		"No symbols were found, creating a loadable object.\n"
#define	DS_MS_UDL_RESULT_ERROR	"Result: ERROR\n"
#define	DS_MS_UDL_RESULT_OK	"Result: OK\n"
#define	DS_MS_UDL_LQ_TOOMANY	"187 Too many errors occurred when loading the file.\n"
#define	DS_MS_UDL_LQ_NOLIB	"188 Cannot load library %s.\n"
#define	DS_MS_UDL_LQ_UNDEF		"189 Cannot find the symbol %s in the file %s.\n"
#define	DS_MS_UDL_LQ_RLDBAD	"190 A bad relocation type %s was found when loading the file.\n"
#define	DS_MS_UDL_LQ_FORMAT	"191 The file %s has a bad format.\n"
#define	DS_MS_UDL_LQ_ERRNO		"%s"
#define	DS_MS_UDL_LQ_MEMBER	"192 The object member %s is bad or missing.\n"
#define	DS_MS_UDL_LQ_TYPE		"193 A type mismatch was found for the symbol %s in the file %s\n."
#define	DS_MS_UDL_LQ_ALIGN		"194 The text section was badly aligned.\n"
#define	DS_MS_UDL_LQ_UNKNOWN	"195 Unknown error number %d occurred when loading the file.\n"
#endif
