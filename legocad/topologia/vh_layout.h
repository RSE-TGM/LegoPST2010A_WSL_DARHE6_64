/**********************************************************************
*
*       C Header:               vh_layout.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:06:11 1996 %
*
**********************************************************************/
/* @(#)72	1.4  com/include/vh_layout.h, aic, aic322, 9238322 4/27/92 19:17:21 */
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
 * $Date: 92/02/07 21:56:09 $ 		        $Revision: 1.2.37.1 $
 *
 * Copyright 1990, Visual Edge Software Ltd.
 * -----------------------------------------
 * ALL RIGHTS RESERVED.  This notice is intended as a precaution against
 * inadvertent publication, and shall not be deemed to constitute an 
 * acknowledgment that publication has  occurred nor to imply any waiver  
 * of confidentiality.	The year included in the notice is the year 
 * of the creation of the work.			   
 *------------------------------------------------------------------------*/

#ifndef VHLAYOUT_DEFINED
#define VHLAYOUT_DEFINED

typedef struct  binptr_struct
{	unsigned bin    : 8;
	unsigned row    :12;
	unsigned column :12;
} binptr;

#if defined(_IBMR2) || defined(__hpux) || defined(hpux)
	typedef unsigned int	Bitfield;
#else
	typedef	unsigned char	Bitfield;
#endif

typedef struct vhandle {
    short	type;
    union {
	struct {
	    Bitfield   in_place		:1; 
	    Bitfield   netdata		:1; 
	    Bitfield   aggregate	:1;
	    Bitfield   class		:1; 
	    Bitfield   fixed		:1;
	    Bitfield   method		:1;
	    Bitfield			:2;
	    Bitfield			:8;
	} vflag;
	short iflag;
	struct {
	    char hflag;	
	    char lflag;
	} eval_flag;
    } u;
    union {
	long	      i;
	float	      f;
	char	      *p;
	void        (*func)();
	binptr      binp;
    } id;
} vhandle;

#endif  /* VHLAYOUT_DEFINED */
