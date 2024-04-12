/**********************************************************************
*
*       C Header:               vhandle.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:06:21 1996 %
*
**********************************************************************/
/* @(#)71	1.5  com/include/vhandle.h, aic, aic322, 9238322 4/27/92 19:17:18 */
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
 * $Date: 91/08/29 13:06:35 $ 		        $Revision: 1.6 $
 *
 * Copyright 1990, Visual Edge Software Ltd.
 * -----------------------------------------
 * ALL RIGHTS RESERVED.  This notice is intended as a precaution against
 * inadvertent publication, and shall not be deemed to constitute an 
 * acknowledgment that publication has  occurred nor to imply any waiver  
 * of confidentiality.	The year included in the notice is the year 
 * of the creation of the work.			   
 *------------------------------------------------------------------------*/

/** Internal definitions for vhandle structure manipulation **/

#ifndef VHANDLE_DEFINED
#define VHANDLE_DEFINED

#include "uxproto.h"
#include "vh_layout.h"
#include "bin.h"

/* Need this if vh is a function return (compiler problem?)
 */

#if defined(sun)  && defined(mc68020)
#define GETMEMB(vh) (&(vh))->
#else
#define GETMEMB(vh) (vh).
#endif

#define NULL_VH_TYPE -1
#define NULL_VH_FLAG -1

#define	UxVh_i(vh)	      (GETMEMB(vh)id.i)
#define UxVh_f(vh)            (GETMEMB(vh)id.f)
#define UxVh_p(vh)            (GETMEMB(vh)id.p)
#define UxVh_func(vh)         (GETMEMB(vh)id.func)
#define UxVh_bin(vh)          (GETMEMB(vh)id.binp)
#define UxVh_type(vh)         (GETMEMB(vh)type)
#define UxVh_in_place(vh)     (GETMEMB(vh)u.vflag.in_place)
#define UxVh_netdata(vh)      (GETMEMB(vh)u.vflag.netdata)
#define UxVh_aggregate(vh)    (GETMEMB(vh)u.vflag.aggregate)
#define UxVh_class(vh)        (GETMEMB(vh)u.vflag.class)
#define UxVh_fixed(vh)        (GETMEMB(vh)u.vflag.fixed)
#define UxVh_method(vh)       (GETMEMB(vh)u.vflag.method)
#define UxVh_flag(vh)	      (GETMEMB(vh)u.iflag)
#define vh_eval_flag(vh)      (GETMEMB(vh)u.eval_flag.lflag)
#define vh_eval_flag_uimx(vh) (GETMEMB(vh)u.eval_flag.hflag)

#define vh_bits(vh)  (GETMEMB(vh)id.i&255)
#define vh_shift(vh) ((GETMEMB(vh)id.i)>>8)
#define MAXBITS	255	/* max number of bits in any single bitfield */

/* We replaced macros by function calls because of a bug in AT&T sysV i386
   C compiler version 4.15.
   (The bug is related to improper allocation of space in the caller frame
    where to copy the returned value when return type is a structure.)
 */
extern short	Ux_i386_fvh_flag UXPROTO(( vhandle ));
extern short	Ux_i386_fvh_type UXPROTO(( vhandle ));
#define fvh_flag(vh) Ux_i386_fvh_flag(vh)
#define fvh_type(vh) Ux_i386_fvh_type(vh)

/*  The former macros
 *  #define fvh_flag(vh)	    (GETMEMB(vh)u.iflag)
 *  #define fvh_type(vh)	    (GETMEMB(vh)type)
 */

#define UxPutVhI(vh,d)         (UxVh_i(vh) = (d))
#define UxPutVhF(vh,d)         (UxVh_f(vh) = (d))
#define UxPutVhP(vh,d)         (UxVh_p(vh) = (char *)(d))
#define UxPutVhFunc(vh,d)      (UxVh_func(vh) = (d))
#define UxPutVhBin(vh,d)       (UxVh_bin(vh) = (d))
#define UxPutVhType(vh,d)      (UxVh_type(vh) = (d))
#define UxPutVhInPlace(vh,d)   (UxVh_in_place(vh) = (d))
#define UxPutVhNetdata(vh,d)   (UxVh_netdata(vh) = (d))
#define UxPutVhAggregate(vh,d) (UxVh_aggregate(vh) = (d))
#define UxPutVhClass(vh,d)     (UxVh_class(vh) = (d))
#define UxPutVhFixed(vh,d)     (UxVh_fixed(vh) = (d))
#define UxPutVhMethod(vh,d)    (UxVh_method(vh) = (d))
#define UxPutVhFlag(vh,d)      (UxVh_flag(vh) = (d))
#define UxPutVhEvalFlag(vh,d)  (vh_eval_flag(vh) = (d))
#define UxPutVhEvalFlagUimx(vh,d) (vh_eval_flag_uimx(vh) = (d))

#define UxPutVhBits(vh,bits) ((vh).id.i = (vh.id.i & ~255) | (bits))
#define UxPutVhShift(vh,shift) ((vh).id.i = ((shift) << 8 ) | ((vh).id.i & 255))
#define UxPutVhShiftBits(vh,shift,bits) ((vh).id.i = ((shift) << 8 ) | (bits))

/* put given a pointer, used to modify a field within an existing vhandle */

#define pput_vh_i(vp, val) ( (vp)->id.i= (val) )
#define pput_vh_f(vp, val)        ( (vp)->id.f= (val) )
#define pput_vh_p(vp, val)        ( (vp)->id.p= (char *)(val) )
#define pput_vh_bin(vp, val)        ( (vp)->id.binp= (val) )
#define pput_vh_type(vp, val)       ( (vp)->type= (val) )
#define pput_vh_flag(vp, val)       ( (vp)->u.iflag= (val) )


#ifdef VE_OPT
#define undefined_vhandle(v) (UxVh_type(v)==NULL_VH_TYPE)
#else
extern int	undefined_vhandle UXPROTO(( vhandle ));
#endif

#define vh_lookup(vh)  UxVh_lookup (vh)

extern char	*UxVh_lookup UXPROTO(( vhandle ));
extern int	UxVh_cmp UXPROTO(( vhandle, vhandle ));
extern int	UxVh_all_cmp UXPROTO(( vhandle, vhandle ));

extern vhandle UxNULL_VHANDLE;

#define vherr(vh)	 (GETMEMB(vh)u.iflag == ERROR)
#define mkvh_err(e)  UxMkvh_flag(ERROR,ERROR,e)

extern vhandle	UxMkvh_flag UXPROTO(( int, int, int ));
extern vhandle	UxMkfvh_flag UXPROTO(( int, int, float ));
extern vhandle	UxMkbvh_flag UXPROTO(( int, int, binptr ));
extern vhandle	UxMkpvh_flag UXPROTO(( int, int, char * ));
extern void	UxPrint_error UXPROTO(( vhandle ));

#endif  /* VHANDLE_DEFINED */
