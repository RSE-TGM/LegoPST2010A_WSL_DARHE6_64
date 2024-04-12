/**********************************************************************
*
*       C Source:               cursore.c
*       Subsystem:              2
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:35:28 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: cursore.c-4 %  (%full_filespec: cursore.c-4:csrc:2 %)";
#endif

/*
 * cursore.c
 */
#include <stdio.h>
#include <X11/Xlib.h>
#include <Xm/Xm.h>

#include "cursore.h"

void set_cursor (parent, shape)
Widget parent;
int shape;
{
Cursor cursore;
	if (shape == NORMALE)
		{
		XUndefineCursor (XtDisplay(parent),XtWindow(parent));
		return;
		}
	cursore = XCreateFontCursor (XtDisplay(parent),shape);
	XDefineCursor (XtDisplay(parent),XtWindow(parent),cursore);
	XSync(XtDisplay(parent),False);
	return;
}
