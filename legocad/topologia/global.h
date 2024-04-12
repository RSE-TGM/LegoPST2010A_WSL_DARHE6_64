/**********************************************************************
*
*       C Header:               global.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:06:00 1996 %
*
**********************************************************************/
/* @(#)93	1.4  com/include/global.h, aic, aic322, 9238322 4/27/92 19:12:44 */
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
/* $Date: 92/02/07 21:52:13 $
/* $Revision: 1.4.37.1 $
/*
/**********************************************************************/

/* ---------------------------------------------------------------------------

Globals that are used through out the program

---------------------------------------------------------------------------*/

#ifndef _GLOBAL_INCLUDED
#define _GLOBAL_INCLUDED

#include "vhandle.h"

/* The following variables have storage defined for them in init_uimx.c
   by means of the dubious practice of defining 'extern' to be nothing */

extern Window	UxRootWindow;
extern Widget	UxTopLevel;	/* The top level shell */
extern Widget	UxSystemParent;	/* parent of all of UIM/X's own interfaces */
extern Display	*UxDisplay;
extern int	UxScreen;
extern XtAppContext   UxAppContext;
extern GC 	UxDrawGC, UxUimxBlackGC, UxUimxWhiteGC;
extern vhandle	UxVh_shells, UxVh_widgets;
extern XEvent   *UxEvent;
extern vhandle  UxCurrent_env;
extern char	*UxUserShell;
extern vhandle	UxActionTable;

#ifdef OL_WIDGETS
/* these are added back in for the purpose of getting the beta OL version */
extern vhandle	Ux_trsl_list;
extern vhandle	Ux_action_tab;
extern vhandle	UxActionList;
#endif /* OL_WIDGETS */

#ifdef MOTIF_WIDGETS
#define	WINDOW_MANAGER	"mwm"	/*for when reading from resource files*/
#endif /* MOTIF_WIDGETS */

#ifdef OL_WIDGETS
#define WINDOW_MANAGER "olwm"	/* not currently used: just for consistency */
#endif /* OL_WIDGETS */

#endif /* _GLOBAL_INCLUDED */
