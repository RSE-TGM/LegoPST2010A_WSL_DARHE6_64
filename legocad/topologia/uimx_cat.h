/**********************************************************************
*
*       C Header:               uimx_cat.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:05:55 1996 %
*
**********************************************************************/

/* @(#)28	1.2  com/catalog/uimx_cat.h.m4, aic, aic322, 9238322 4/27/92 18:27:43 */
/*
 *  COMPONENT_NAME: AIC     AIXwindows Interface Composer
 *  
 *  ORIGINS: 58
 *  
 *  Licensed Materials - Property of IBM
 *  5756-027 (C) Copyright International Business Machines Corp. 1991, 1992.
 *  All Rights Reserved.
 *  
 *  US Government Users Restricted Rights - Use, duplication or
 *  disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*/
/**********************************************************************/
/*
* $Date: 92/02/07 21:12:05 $
* $Revision: 1.13.37.1 $
*/
/**********************************************************************/

/*****************************************************************************/
/***                                                                       ***/
/***             Copyright (c) 1990, Visual Edge Software Ltd.             ***/
/***                                                                       ***/
/***   ALL RIGHTS RESERVED.  This notice is  intended  as  a  precaution   ***/
/***   against  inadvertent publication, and shall not be deemed to con-   ***/
/***   stitute an acknowledgment that publication has  occurred  nor  to   ***/
/***   imply  any  waiver  of confidentiality.  The year included in the   ***/
/***   notice is the year of the creation of the work.                     ***/
/***                                                                       ***/
/*****************************************************************************/

#ifndef	_UIMXCAT_H_
#define	_UIMXCAT_H_

#include "uxproto.h"

#ifdef  XOPEN_CATALOG
/* If XOPEN_CATALOG is defined, we use the message catalog */

#ifdef DESIGN_TIME
#define CAT_FILE	"aic.cat"
#endif
#ifdef RUNTIME
#define	CAT_FILE	"libaic.cat"
#endif
#ifdef UTILITIES
#define	CAT_FILE	"aicutils.cat"
#endif



extern int	UxCatOpen UXPROTO(( void ));
extern void	UxCatClose UXPROTO(( void ));
extern char	*UxCatGets UXPROTO(( int, int, char * ));

#define UxCatGetc(setnum,msgnum,default) *UxCatGets(setnum,msgnum,default)

#else /* not using message catalog */

#define UxCatOpen()	0
#define UxCatClose()
#define UxCatGets(setnum,msgnum,default) (default)
#define UxCatGetc(setnum,msgnum,default) *(default)

#endif /* XOPEN_CATALOG */

#if defined(__STDC__) && !defined(apollo)
#define PASTE(token1,token2)		token1##token2
#define PASTE3(token1,token2,token3)	token1##token2##token3
#else
#define PASTE(token1,token2)		token1/**/token2
#define PASTE3(token1,token2,token3)	token1/**/token2/**/token3
#endif

#define UXCATGETS(setnum,msg_prefix,msg) \
	UxCatGets(setnum,PASTE(msg_prefix,msg),PASTE3(DS_,msg_prefix,msg))

#ifdef CD_DEMO
#	include "ibmsysDM_ds.h"
#else /* CD_DEMO */
#	include "ibmsys_ds.h"
#endif /* CD_DEMO */


#endif /* _UIMXCAT_H_ */

