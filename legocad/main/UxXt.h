/**********************************************************************
*
*       C Header:               UxXt.h
*       Subsystem:              3
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:01:31 1996 %
*
**********************************************************************/
/* @(#)40	1.8  com/config/UxXt.h, aic, aic322, 9239322 9/30/92 16:30:41 */
/*
 *  COMPONENT_NAME: AIC     AIXwindows Interface Composer
 *  
 *  ORIGINS: 58
 *  
 *  
 *                   Copyright IBM Corporation 1991, 1992
 *  
 *                         All Rights Reserved
 *  
 *   Permission to use, copy, modify, and distribute this software and its
 *   documentation for any purpose and without fee is hereby granted,
 *   provided that the above copyright notice appear in all copies and that
 *   both that copyright notice and this permission notice appear in
 *   supporting documentation, and that the name of IBM not be
 *   used in advertising or publicity pertaining to distribution of the
 *   software without specific, written prior permission.
 *  
*/

/*****************************************************************************/
/*				UxXt.h				             */
/*****************************************************************************/

#ifndef	_UX_XT_H_
#define	_UX_XT_H_

#include "UxXtPuts.h"
#include "UxXtGets.h"

#include <Xm/Xm.h>

/* The following macros are used in converting string values to the form
   required by the widgets */

#define	RES_CONVERT( res_name, res_value) \
	XtVaTypedArg, (res_name), XmRString, (res_value), strlen(res_value) + 1

#define	UxPutStrRes( wgt, res_name, res_value ) \
	XtVaSetValues( wgt, RES_CONVERT( res_name, res_value ), NULL )


#ifndef UX_INTERPRETER	/* Omit this section when interpreting the code */

/* The following macros are supplied for compatibility with swidget code */
#define	swidget			Widget
#define	UxWidgetToSwidget(w)	(w)
#define	UxGetWidget(sw)		(sw)
#define	UxIsValidSwidget(sw)	((sw) != NULL)

#define	no_grab			XtGrabNone
#define	nonexclusive_grab	XtGrabNonexclusive
#define	exclusive_grab		XtGrabExclusive


/* The following global variables are defined in the main() function */
extern  XtAppContext	UxAppContext;
extern  Widget		UxTopLevel;
extern  Display		*UxDisplay;
extern  int		UxScreen;


/* The following are error codes returned by the functions in UxXt.c */
#define UX_ERROR           -1
#define UX_NO_ERROR        0


/* The following are declarations of the functions in UxXt.c */

#ifdef _NO_PROTO

extern  int		UxPopupInterface();
extern  int		UxPopdownInterface();
extern  int		UxDestroyInterface();
extern  int		UxPutContext();
extern  caddr_t		UxGetContext();
extern  void		UxFreeClientDataCB();
extern  void		UxLoadResources();
extern  XmFontList	UxConvertFontList();

#else

extern  int		UxPopupInterface( Widget wgt, XtGrabKind grab_flag );
extern  int		UxPopdownInterface( Widget wgt );
extern  int		UxDestroyInterface( Widget wgt);
extern  int		UxPutContext( Widget wgt, caddr_t context );
extern  caddr_t		UxGetContext( Widget wgt );
extern  void		UxFreeClientDataCB( Widget wgt, XtPointer client_data,
						 XtPointer call_data );
extern  void		UxLoadResources( char *fname );
extern  XmFontList	UxConvertFontList( char *fontlist_str );

#endif /* _NO_PROTO */

#endif /* ! UX_INTERPRETER */

#endif /* ! _UX_XT_H_ */

