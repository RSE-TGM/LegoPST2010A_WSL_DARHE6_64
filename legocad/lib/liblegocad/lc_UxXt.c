/**********************************************************************
*
*       C Source:               lc_UxXt.c
*       Subsystem:              1
*       Description:
*       %created_by:    lopez %
*       %date_created:  Wed Jun 19 13:45:20 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: lc_UxXt.c-3 %  (%full_filespec: lc_UxXt.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)lc_UxXt.c	2.2\t2/13/95";
/*
        Fine sezione per SCCS
*/
/*
 Contiene funzioni aggiuntive per il porting da routines Ux a
 routines Xt
*/
#include <Xm/Xm.h>
#include <Xm/List.h>
#include <Xm/RowColumn.h>
#include <Xm/MainW.h>

void lcDispatchEvent(event)
XEvent *event;
{
    XtDispatchEvent(event);
}

void lcNextEvent(event)
XEvent *event;
{
   XNextEvent(NULL, event);
}

Widget lcGetParent(wid)
Widget wid;
{
   return(XtParent(wid));
}

char * lcGetName(wid)
Widget wid;
{
   return(XtName(wid));
}

Widget lcCreateWidget(wid)
Widget wid;
{
   XtManageChild(wid);
   return(wid);
}

char * lcGetSelectedItems(wid)
Widget wid;
{
Arg arg[3];
char *text;
char *str=NULL;
int i,narg;
int num_selez;
XmString *lista;  /* lista che conterra' gli items selezionati */

narg = 0;
XtSetArg(arg[narg], XmNselectedItems, &lista );narg++;
XtSetArg(arg[narg], XmNselectedItemCount, &num_selez);narg++;
XtGetValues(wid,arg,narg);

/*
 trasforma le compound strings in stringhe e le inserisce in una
 unica stringa separate tra loro da virgole
*/
for(i=0; i<num_selez; i++)
	{
	XmStringGetLtoR(lista[i],XmSTRING_DEFAULT_CHARSET,&text);
	str=XtRealloc(str,(strlen(text)+2)*sizeof(char)*(i+1));
	if(i==0) str[0]=0;
	strcat(str,text);
	strcat(str,",");
	}
str[strlen(str)-1]=0;
printf("\n lista selezionati %s",str);
return(str);
}

Widget lcCreateMenuPulldown(name,parent)
char *name;
Widget parent;
{
Arg arg[3];
int narg;
narg = 0;
XtSetArg(arg[narg], XmNrowColumnType, XmMENU_PULLDOWN);narg++;
XtCreateWidget(name,xmRowColumnWidgetClass,parent,arg,narg);
}

Widget lcCreateMenuOption(name,parent)
char *name;
Widget parent;
{
Arg arg[3];
int narg;
narg = 0;
XtSetArg(arg[narg], XmNrowColumnType, XmMENU_OPTION);narg++;
XtCreateWidget(name,xmRowColumnWidgetClass,parent,arg,narg);
}

static Boolean CvtStrToPixel (Widget wgt,char *Stringa,Pixel *Pix)
{
        unsigned long piani[1];
        Colormap colmap;
        XColor xcol;


        colmap = DefaultColormap ( XtDisplay(wgt),
                        DefaultScreen (XtDisplay(wgt)) );
        if ( !XParseColor (XtDisplay(wgt) , colmap , Stringa , &xcol) )
        {
           printf("Errore XParseColor: colore inesistente\n");
           return(False);
        }
        if(!XAllocColor(XtDisplay(wgt),colmap,&xcol))
        {
           printf("Errore XAllocColor: impossibile allocare un nuovo colore\n");
           return(False);
        }
        *Pix = xcol.pixel;
        return(True);
}


static char *CvtPixToStr (wid, NomeRes)
Widget wid;
char *NomeRes;
{
        Arg args[3];
        XColor Colore;
        Colormap cmap;
        char *vstring;
        Display *Displ;

        /*  Ricavo il display dal widget passato come parametro */
        Displ = XtDisplay (wid);
        XtSetArg (args[0], NomeRes, &Colore.pixel);
        XtSetArg (args[1], XmNcolormap, &cmap);
        XtGetValues (wid, args, 2);
        XQueryColor (Displ, cmap, &Colore);
        vstring = (char *)XtCalloc (15, sizeof(char));
        sprintf (vstring,"#%04x%04x%04x",Colore.red,Colore.green,Colore.blue);
        return (vstring);
}

char *lcGetBackground(wgt)
Widget wgt;
{
   return(CvtPixToStr(wgt,XmNbackground));
}

char *lcGetForeground(wgt)
Widget wgt;
{
   return(CvtPixToStr(wgt,XmNforeground));
}

Widget lcCreateMainWindow(name,parent)
char *name;
Widget parent;
{
   XtCreateWidget(name,xmMainWindowWidgetClass,parent,NULL,0);
}

Widget lcCreateFrame(name,parent)
char *name;
Widget parent;
{
   XmCreateFrame(parent,name,NULL,0);
}

Widget lcCreateLabel(name,parent)
char *name;
Widget parent;
{
   XmCreateLabel(parent,name,NULL,0);
}

lcDestroySwidget(wgt)
Widget wgt;
{
XtDestroyWidget(wgt);
XSync(XtDisplay(wgt),False);
}

