/**********************************************************************
*
*       C Source:               get_colors.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 14:19:33 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: get_colors.c-6 %  (%full_filespec: get_colors.c-6:csrc:1 %)";
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <Xm/Xm.h>

#include <stdio.h>

#include "parametri.h"

extern Display *UxDisplay;

int get_colors()
{
int i;
Colormap default_cmap;
XColor exdef;
int screen_num;
	screen_num = DefaultScreen (UxDisplay);
	default_cmap = DefaultColormap (UxDisplay,screen_num);

	for (i=0; i<MAX_COLORS; i++)
		{
		if (!strcmp(nomi_colori[i],"NULL"))
			break;
		if (!XParseColor (UxDisplay, default_cmap, nomi_colori[i], &exdef))
			{
			fprintf (stderr,"#####  Colour %s not in database!!!\n",nomi_colori[i]);
			return (-1);
			}
		if (!XAllocColor (UxDisplay, default_cmap, &exdef))
			{
			fprintf (stderr,"#####  Colour %s not allocable!!!\n",nomi_colori[i]);
			return(-1);
			}
		colore_app[i] = exdef.pixel;
//		printf ("%s = %d %d %d\n",nomi_colori[i],
//			 exdef.red, exdef.green, exdef.blue);
		}
	return(0);
}
/*********************************************************************/
int get_colore_sfondo (w)
Widget w;
{
int c;
extern int colore_sfondo;

	XtVaGetValues (w, XmNbackground, &c, NULL);
	colore_sfondo = c;
	return(0);
}
/*********************************************************************/
int read_background_color (w)
Widget w;
{
int c;
int bgcolor;

	XtVaGetValues (w, XmNbackground, &c, NULL);
        bgcolor=c;
	return(bgcolor);
}
/*********************************************************************/
int read_foreground_color (w)
Widget w;
{
unsigned int c;

   XtVaGetValues (w, XmNforeground, &c, NULL);
   return(c);
}
