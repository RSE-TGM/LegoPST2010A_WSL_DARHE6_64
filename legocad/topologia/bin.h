/**********************************************************************
*
*       C Header:               bin.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:06:05 1996 %
*
**********************************************************************/
/* @(#)77	1.6  com/include/bin.h, aic, aic322, 9238322 4/27/92 19:12:02 */
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
 * $Date: 91/08/29 13:05:33 $ 		        $Revision: 1.6 $
 *
 * Copyright 1990, Visual Edge Software Ltd.
 * -----------------------------------------
 * ALL RIGHTS RESERVED.  This notice is intended as a precaution against
 * inadvertent publication, and shall not be deemed to constitute an 
 * acknowledgment that publication has  occurred nor to imply any waiver  
 * of confidentiality.	The year included in the notice is the year 
 * of the creation of the work.			   
 *------------------------------------------------------------------------*/

/** Private definitions for binptr structure. **/

#ifndef BIN_DEFINED
#define BIN_DEFINED

#include "uxproto.h"
#include <vh_layout.h>

#define TOTAL_BINS 255
#define TOTAL_COLUMNS 4095
#define TOTAL_ROWS 4095 

#define bp_bin(bp)     (bp).bin
#define bp_row(bp)     (bp).row
#define bp_column(bp)  (bp).column

#define UxPutBpBin(bp, d)     bp_bin(bp) = d
#define UxPutBpRow(bp, d)     bp_row(bp) = d
#define UxPutBpColumn(bp, d)  bp_column(bp) = d

/* set and test for an invalid binpointer */

#define set_null_bin(bp) (UxPutBpBin(bp, TOTAL_BINS), \
			  UxPutBpColumn(bp, TOTAL_COLUMNS), \
			  UxPutBpRow(bp, TOTAL_ROWS))
#define is_null_bin(bp) ((bp_bin(bp)  == TOTAL_BINS) && \
			 (bp_column(bp)  == TOTAL_COLUMNS) && \
			 (bp_row(bp)  == TOTAL_ROWS))
#define set_null_bin2(bp, n) (UxPutBpBin(bp, TOTAL_BINS), \
			      UxPutBpColumn(bp, TOTAL_COLUMNS), \
			      UxPutBpRow(bp, n))
#define is_null_bin2(bp) (((bp_bin(bp)  == TOTAL_BINS)  && \
			   (bp_column(bp)  == TOTAL_COLUMNS)) \
			  ? (int)bp_row(bp) : -1)
#define is_zero_bin(bp) (((bp).bin  == 0) && \
			 ((bp).column  == 0) && \
			 ((bp).row  == 0))

#define obj_lookup(b, obj) ((obj *)UxBin_lookup(b))

#define make_obj(ibin, retbp, obj) ((obj *)UxVm_pcr(ibin, retbp))

#define vm_alloc(size) UxVm_cr(UxVm_find_bin(size, 0))
#define vm_more(bp)    UxVm_cr(bp_bin(bp))


typedef struct mem_block_struct {
  int        element_size,
             ncolumns, nrows,
             ncolumns_inc,	/* Increment to add on overflow */
             key,		/* = 1 means only for objects   */
             manage_history,	/* = 1 means manage history     */
             excess;
  binptr     freelist,new;	/* free list and new pointers to id's */
  int        next;		/* next item in vm's free list */
  char       **data;		/* points to data */
} bin;

#define NULL_BIN ((bin *) 0)

extern char	*UxBin_lookup UXPROTO(( binptr ));
extern char	*UxItem_lookup UXPROTO(( bin *, int, int ));


#ifdef IN_VMEM

    /* use as error case*/

    binptr UxNULL_BINPTR = {TOTAL_BINS, TOTAL_COLUMNS, TOTAL_ROWS};
    bin *Ux_vm = NULL_BIN; /* Array of memblocks */
    bin *Ux_vbin;
    binptr Ux_tbin;

#else

    extern bin *Ux_vm, *Ux_vbin;
    extern binptr UxNULL_BINPTR, Ux_tbin;

    extern int		UxVm_bin_cmp UXPROTO(( binptr, binptr ));
    extern int 		UxVm_undefined_binptr UXPROTO(( binptr ));
    extern binptr	UxVm_cr UXPROTO(( int ));
    extern void		UxVm_free UXPROTO(( binptr ));
    extern void		UxVm_free_bin UXPROTO(( int ));
    extern int		UxVm_find_bin UXPROTO(( int, int ));
    extern int		UxVm_new_bin_spec UXPROTO(( int, int, int, int,
							int, int, int ));
    extern int		UxVm_new_bin UXPROTO(( int, int ));
    
#endif
    
/* bin keys */
    
#define GENERAL_KEY	0	/* general use - will not be saved */
#define OBJECT_KEY	1	/* reserved for use by UIMX */
#define SYMBOL_KEY	2	/* reserved for use by the symbol handler */
#define INTERP_KEY	3	/* reserved for use by the interpreter */

#endif  /* BIN_DEFINED */
