/**********************************************************************
*
*       C Source:               nnWorks.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 12:09:47 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: nnWorks.c,2 %  (%full_filespec: 1,csrc,nnWorks.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)nnWorks.c	1.13\t11/13/95";
/*
        Fine sezione per SCCS
*/

/* nnWorks.c
 * - routines di lavoro per i sorgenti C della pagina "nn".
 *   Le interfacce di "nn" sono prodotte con 'aic' vers. 1.1.1 in formato Xt.
 */

#include <stdio.h>

#ifdef XOPEN_CATALOG
#include <locale.h>
#endif

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <Xm/Xm.h>

/*---------------------------------------------------- 
 * UxXt.h needs to be included only when compiling a 
 * stand-alone application. 
 *---------------------------------------------------*/
#ifndef DESIGN_TIME
#include "UxXt.h"
#endif /* DESIGN_TIME */

/*----------------------------------------------
 * Insert application global declarations here
 *---------------------------------------------*/

#include "f03.h"
#include "f14.h"
 extern VAL_VAR *valout;
 extern VAL_VAR *valinp;
#include "uni_mis.h"
 extern S_UNI_MIS uni_mis[];

/*----------------------------------------------
 * Application specific functions follow ...
 *---------------------------------------------*/

/* ----------
 * nnValues.c
 * ---------- */
S_UNI_MIS *nnVget_uni_mis( unsigned char ind_umis )
{
   return &uni_mis[ind_umis];
}
