/**********************************************************************
*
*       C Header:               uxproto.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:06:27 1996 %
*
**********************************************************************/
/* @(#)21	1.4  com/include/uxproto.h, aic, aic322, 9238322 4/27/92 19:16:45 */
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

/*------------------------------------------------------------------------
 * $Date: 91/08/29 13:25:43 $ 		        $Revision: 1.1 $
 *
 * Copyright 1991, Visual Edge Software Ltd.
 * -----------------------------------------
 * ALL RIGHTS RESERVED.  This notice is intended as a precaution against
 * inadvertent publication, and shall not be deemed to constitute an 
 * acknowledgment that publication has  occurred nor to imply any waiver  
 * of confidentiality.	The year included in the notice is the year 
 * of the creation of the work.			   
 *------------------------------------------------------------------------*/

#ifndef UXPROTO_H
#define UXPROTO_H

#ifdef _NO_PROTO
#define UXPROTO(x) ()
#else
#define UXPROTO(x) x
#endif

typedef struct UxObject       *Object_t;
typedef struct UxClass_st     *Class_t;

/*  DESIGN_TIME swidget definition */

#ifdef DESIGN_TIME
typedef struct UxShadowWidget *swidget;
#endif

#endif /* UXPROTO_H */

