/**********************************************************************
*
*       C Source:               UxXt.c
*       Subsystem:              28
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 16 18:34:51 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: UxXt.c,2 %  (%full_filespec: 28,csrc,UxXt.c,2 %)";
#endif
static char sccsid[] = "@(#)39	1.8  com/config/UxXt.c, aic, aic322, 9319320 4/15/93 15:16:57";
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

 /*------------------------------------------------------------------------
 *				UxXt.c                                    
 *------------------------------------------------------------------------*/

#include <stdio.h>

#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>
#include <X11/Xutil.h>
#include <X11/X.h>
#include <X11/Xmd.h>
#include <X11/Xlib.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>

#include "UxXt.h"

static	XContext	xcontext_id = 0;

/******************************************************************************
NAME:		GetTrueToplevel( wgt )

INPUT:		Widget	wgt		- the top user-created widget 

RETURN:		Widget			- the shell widget

DESCRIPTION:	Returns the true toplevel of that interface.
		This is needed for implicit shells where the widget passed to
		one of the Ux functions is not always the shell.

CREATION:	Visual Edge Software		April 6 1991
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
static	Widget 	GetTrueToplevel( wgt )
	Widget 	wgt;
#else
static	Widget 	GetTrueToplevel( Widget wgt )
#endif
{
	if (wgt && !XtIsShell(wgt)) 
	{
		wgt = XtParent(wgt);
	}
	return wgt;
}

/******************************************************************************
NAME:		handle_dialog_child( wgt, manage_func )

INPUT:		Widget	wgt			- the dialogShellWidget
		void	(*manage_func)()	- either XtManageChild
						  or XtUnmanageChild

RETURN:		int				- UX_NO_ERROR if successfull
						  UX_ERROR otherwise

DESCRIPTION:	Handles the popping up or popping down of dialog shells
		by managing or unmanaging their children.

CREATION:	Visual Edge Software		Sept 19/91   
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
static	int	handle_dialog_child( wgt, manage_func )
	Widget	wgt;
	void    (*manage_func)();
#else
static	int	handle_dialog_child( Widget wgt, void (*manage_func)() )
#endif
{
	int	i, num_children;
	Widget	*children;
	int	error_flag = UX_ERROR;

	XtVaGetValues( wgt,
		       XmNnumChildren, &num_children,
		       XmNchildren, &children,
		       NULL );

	/* We manage/unmanage the first rectObj child in the list.
	 * Note that the check for rectObjClass is necessary since some
	 * implementations of Motif add protocol children to the dialogShell.
	 */

	for (i = 0; i < num_children; i++)
	{
		if ( XtIsSubclass( children[i], rectObjClass ) )
		{
			(*manage_func)(children[i]);
			error_flag = UX_NO_ERROR;
			break;
		}
	}

	return ( error_flag );
}

/******************************************************************************
NAME:		popup_dialog( wgt, grab_flag )

INPUT:		Widget		wgt		- dialogShell to pop up
		XtGrabKind	grab_flag	- the grab flag

RETURN:		void

DESCRIPTION:	Pops up a dialogShell.

CREATION:	Visual Edge Software		Sept 19/91   
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
static	void	popup_dialog( wgt, grab_flag )
	Widget		wgt;
	XtGrabKind	grab_flag;
#else
static	void	popup_dialog( Widget wgt, XtGrabKind grab_flag )
#endif
{
	if ( handle_dialog_child( wgt, XtManageChild ) == UX_ERROR )
		XtPopup( wgt, grab_flag );
}

/******************************************************************************
NAME:		UxPopupInterface( wgt, grab_flag )

INPUT:		Widget		wgt		- Widget to popup
		XtGrabKind	grab_flag	- grab flag 

RETURN:		int			UX_ERROR or UX_NO_ERROR

DESCRIPTION:	Popups up an interface. The widget should be a toplevel widget.
		Note that special handling is required for dialogShells since
		those are popped up by managing their children if they have
		some.
		The grab_flag could be any of:
				no_grab	(XtGrabNone)
				nonexclusive_grab (XtGrabNonexclusive)
				exclusive_grab (XtGrabExclusive)

CREATION:	Visual Edge Software		April 6 1991
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
int	UxPopupInterface( wgt, grab_flag )
	Widget		wgt;
	XtGrabKind	grab_flag;
#else
int	UxPopupInterface( Widget wgt, XtGrabKind grab_flag )
#endif
{
	if (!(wgt = GetTrueToplevel(wgt)))
		return ( UX_ERROR );

	if ( XtIsSubclass( wgt, xmDialogShellWidgetClass ) )
	{
		popup_dialog( wgt, grab_flag );
	}
	else
	{
		XtPopup( wgt, grab_flag );
	}

	return ( UX_NO_ERROR );
}

/******************************************************************************
NAME:		popdown_dialog( wgt )

INPUT:		Widget	wgt		- dialogShell to popdown

RETURN:		void

DESCRIPTION:	Pops down a dialogShell.

CREATION:	Visual Edge Software		Sept 19/91   
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
static	void	popdown_dialog( wgt )
	Widget	wgt;
#else
static	void	popdown_dialog( Widget wgt )
#endif
{
	if ( handle_dialog_child( wgt, XtUnmanageChild ) == UX_ERROR )
		XtPopdown( wgt );
}

/******************************************************************************
NAME:		UxPopdownInterface( wgt )

INPUT:		Widget	wgt		- Widget to popdown

RETURN:		int			UX_ERROR / UX_NO_ERROR

DESCRIPTION:	Pops down an interface. The widget should be a toplevel widget.
		Note that special handling is required for dialogShells since
		those are popped down by unmanaging their children if they have
		some.

CREATION:	Visual Edge Software		April 6 1991
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
int	UxPopdownInterface( wgt )
	Widget	wgt;
#else
int	UxPopdownInterface( Widget wgt )
#endif
{
	if (!(wgt = GetTrueToplevel(wgt)))
		return ( UX_ERROR );

	if ( XtIsSubclass( wgt, xmDialogShellWidgetClass ) )
	{
		popdown_dialog( wgt );
	}
	else
	{
		XtPopdown( wgt );
	}

	return ( UX_NO_ERROR );
}

/******************************************************************************
NAME:		UxDestroyInterface( wgt )

INPUT:		Widget	wgt		- Widget to destroy

RETURN:		int			UX_ERROR / UX_NO_ERROR

DESCRIPTION:	Destroys an interface.  The widget should be a toplevel widget.
		
CREATION:	Visual Edge Software		April 6 1991
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
int	UxDestroyInterface( wgt )
	Widget	wgt;
#else
int	UxDestroyInterface( Widget wgt )
#endif
{
	if (!(wgt = GetTrueToplevel(wgt)))
		return ( UX_ERROR );

	XtDestroyWidget (wgt);

	return ( UX_NO_ERROR );
}

/******************************************************************************
NAME:		DeleteContextCB( wgt, client_data, call_data )

INPUT:		Widget		wgt		- widget causing the callback
		XtPointer       client_data	- not used
		XtPointer	call_data	- not used

RETURN:		void

DESCRIPTION:	Deletes the X context entry.

EXT REFERENCES:	UxTopLevel, xcontext_id

CREATION:	Visual Edge Software		April 6 1991
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
static	void    DeleteContextCB( wgt, client_data, call_data )
	Widget          wgt;
	XtPointer       client_data, call_data;
#else
static	void    DeleteContextCB( Widget wgt, XtPointer client_data,
						XtPointer call_data )
#endif
{
	(void) XDeleteContext( XtDisplay( UxTopLevel ),
			       (Window) wgt,
			       xcontext_id );
}

/******************************************************************************
NAME:		UxPutContext( wgt, context )

INPUT:		Widget	wgt		- Widget
		caddr_t	context		- context pointer

RETURN:		int			UX_ERROR / UX_NO_ERROR

DESCRIPTION:	Uses the X Context manager to store the given context pointer
		in a memory location that is indexed by the given widget id.
		Also adds a destroyCallback to delete that context when the
		widget is destroyed.

EXT REFERENCES:	UxTopLevel, xcontext_id
EXT EFFECTS:	xcontext_id

CREATION:	Visual Edge Software		April 6 1991
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
int	UxPutContext( wgt, context )
	Widget	wgt;
	caddr_t	context;
#else
int	UxPutContext( Widget wgt, caddr_t context )
#endif
{
	int		status;

	if ( xcontext_id == 0 )
		xcontext_id = XUniqueContext();

	if ( wgt == NULL )
		return ( UX_ERROR );

	status = XSaveContext( XtDisplay( UxTopLevel ), 
			       (Window) wgt, 
			       xcontext_id, 
			       context );
	if ( status != 0 )
		return ( UX_ERROR );

	XtAddCallback (wgt, XmNdestroyCallback, DeleteContextCB, NULL);

	return ( UX_NO_ERROR );
}

/******************************************************************************
NAME:		UxGetContext( wgt )

INPUT:		Widget	wgt		- widget

RETURN:		caddr_t			- the context pointer

DESCRIPTION:	Uses the X Context manager to find the context pointer
		stored in a memory location indexed by the given widget id.

EXT REFERENCES:	UxTopLevel, xcontext_id

CREATION:	Visual Edge Software		April 6 1991
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
caddr_t	UxGetContext( wgt )
	Widget	wgt;
#else
caddr_t	UxGetContext( Widget wgt )
#endif
{
	int	status;
	caddr_t	context;

	if ( wgt == NULL )
		return ( (caddr_t) NULL );

	status = XFindContext( XtDisplay( UxTopLevel ), 
			       (Window) wgt, 
			       xcontext_id, 
			       &context );

	if ( status != 0 )
		return	( (caddr_t) NULL );

	return ( context );
}

/******************************************************************************
NAME:		UxFreeClientDataCB( wgt, client_data, call_data )

INPUT:		Widget		wgt		- widget
		XtPointer       client_data	- pointer to be freed
		XtPointer	call_data	- not used

RETURN:		void

DESCRIPTION:	This callback function simply frees the client data.

CREATION:	Visual Edge Software		April 6 1991
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
void    UxFreeClientDataCB( wgt, client_data, call_data )
	Widget          wgt;
	XtPointer       client_data, call_data;
#else
void    UxFreeClientDataCB( Widget wgt, XtPointer client_data,
				XtPointer call_data )
#endif
{
	if (client_data != NULL)
		XtFree(client_data);
}

/******************************************************************************
NAME:		UxLoadResources( fname )

INPUT:		char	*fname          - name of resource file

RETURN:		void

DESCRIPTION:	This function is provided as a stub function to load the
		resource file that was generated by the C Code Generator
		into the current toolkit resource database.
		A call to this function is automatically generated with the
		appropriate resource filename when resources are set to Public.

CREATION:	Visual Edge Software		April 6 1991
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
void    UxLoadResources( fname )
	char	*fname;
#else
void    UxLoadResources( char *fname )
#endif
{
}

/******************************************************************************
NAME:		UxConvertFontList( fontlist_str )

INPUT:		char	*fontlist_str		- string form of fontlist

RETURN:		XmFontList			- fontlist

DESCRIPTION:	Converts a fontlist from the resource-file string format
		to the XmFontList type expected in C code.
		The conversion is done by a call to the built-in Motif convertor
		and the return value points into Xt's resource cache
		and so the return value should NOT be XmFontListFree'd.

CREATION:	Visual Edge Software		June 17 1992
-----------------------------------------------------------------------------*/
#ifdef _NO_PROTO
XmFontList    UxConvertFontList( fontlist_str )
	char	*fontlist_str;
#else
XmFontList    UxConvertFontList( char *fontlist_str )
#endif
{
	XrmValue	from, to;
	XmFontList	fontlist = NULL;
	Boolean		status;

	from.size = strlen( fontlist_str ) + 1;
	from.addr = fontlist_str;

	to.size = sizeof(XmFontList);
	to.addr = (caddr_t) &fontlist;

	status = XtConvertAndStore( UxTopLevel,
				    XmRString, &from,
				    XmRFontList, &to );

	return ( fontlist );
}

/***END*OF*FILE****************************************************************/

