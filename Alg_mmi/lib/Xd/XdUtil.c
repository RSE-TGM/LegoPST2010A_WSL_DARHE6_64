/**********************************************************************
*
*       C Source:               XdUtil.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Fri Apr 10 12:01:18 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XdUtil.c-2.1.3 %  (%full_filespec: XdUtil.c-2.1.3:csrc:1 %)";
#endif

/* XdUtil.c
 * 	Routines di utilizzo generale per la manipolazione dei Draget
 */
#include <Xm/Xm.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <Xd/XdCoreP.h>
#include <Xd/XdLineP.h>
#include <Xd/XdRectP.h>
#include <Xd/XdCircleP.h>
#include <Xd/XdPoliP.h>
#include <Xd/XdConnP.h>
#include <Xd/XdGroupP.h>
#include <Rt/RtMemory.h>

/*
	dichiarazione funzione rint per VMS
*/
#if defined VMS
static double rint();
#endif


DragetClass XdClass(dr)
Draget dr;
{
return(dr->xdcore.draget_class);
}

Boolean XdIsSelected(dr)
Draget dr;
{
return(dr->xdcore.selected);
}

Boolean XdIsManaged(dr)
Draget dr;
{
return(dr->xdcore.managed);
}

/*
 Funzione che stabilisce se un Draget e' del tipo
 gruppo (Group)
*/
Boolean XdIsGroup(dr)
Draget dr;
{
DragetClass class;
class= XdClass(dr);
if(class == (DragetClass)&xdGroupClassRec )
	return(True);
else
	return(False);
}


XdStartMove(dr)
Draget dr;
{
dr->xdcore.moving=True;
dr->xdcore.resizing=False;
dr->xdcore.is_first=True;
dr->xdcore.num_move=0;
}

/*
 XdSetGC
  modifica il GC di un oggetto gia' esistente
*/
void XdSetGC(dr,gc,gc_bg)
Draget dr;
GC gc;
GC gc_bg;
{
DragetClass class;
class=dr->xdcore.draget_class;
dr->xdcore.gc=gc;
dr->xdcore.gc_bg=gc_bg;
class->xdcore_class.clear(dr);
}

XdSetSnap(dr,snap)
Draget dr;
int snap;
{
Draget drf;
XdLista dr_list;

if(XdIsGroup(dr))
	{
	dr_list=XdGroupGetList(dr);
	ListDragetRew(dr_list);
	while((drf=ListDragetNext(dr_list)) != NULL)
		XdSetSnap(drf,snap);
	}
dr->xdcore.step=snap;
}

/*
 setta a managed un draget
 questa funzione viene usata nella gestione delle connessioni
 in modo particolare. Infatti quando viene spostata una icona di
 regolazione connessa le sue connessioni devono essere modificate una ad una
 in modo che siano congruenti con lo spostamento. In questa fase
 le connessioni gia' trattate devono essere escluse nei trattamenti
 successivi. Per fare cio' il metodo di modify delle connessioni
 setta a false l'attributo di managed della connessioni. Gli attributi
 di managed vengono resettati a true una volta terminato il
 trattamento di tutte le connessioni che interessano l'icona di
 regolazione.
*/
XdSetManaged(dr,flag)
Draget dr;
Boolean flag;
{
dr->xdcore.managed= flag;
}

/*
 XdDestroyDraget(dr)
 distrugge l'oggetto selezionato
*/
void XdDestroyDraget(dr)
Draget dr;
{
DragetClass class;
Draget drf;
XdLista dr_list;

if(XdIsGroup(dr))
	{
	dr_list=XdGroupGetList(dr);
	ListDragetRew(dr_list);
	while((drf=ListDragetNext(dr_list)) != NULL)
		XdDestroyDraget(drf);
	}
class=dr->xdcore.draget_class;
class->xdcore_class.destroy(dr);
/*
 esclude nel caso di gestione in clipboard
 l'uso del metodo di clear
 in quanto il widget non e' realized e la window 
 corrispondente non esiste
*/
if(XtIsRealized(dr->xdcore.wid))
	{
	class->xdcore_class.clear(dr);
	}
class->xdcore_class.delete_regions(dr);
XtFree(dr);
}


/*
 XdDestroyDragetiNoClear(dr)
 distrugge l'oggetto selezionato senza eseguire la clear
*/
void XdDestroyDragetNoClear(dr)
Draget dr;
{
DragetClass class;
Draget drf;
XdLista dr_list;

if(XdIsGroup(dr))
        {
        dr_list=XdGroupGetList(dr);
        ListDragetRew(dr_list);
        while((drf=ListDragetNext(dr_list)) != NULL)
                XdDestroyDragetNoClear(drf);
        }
class=dr->xdcore.draget_class;
class->xdcore_class.destroy(dr);
class->xdcore_class.delete_regions(dr);
XtFree(dr);
}


/*
 XdRedrawDraget
	ridisegna l'oggetto senza generare eventi di redraw
*/
void XdRedrawDraget(dr)
Draget dr;
{
DragetClass class;
class=dr->xdcore.draget_class;
class->xdcore_class.expose(dr,NULL);
}

/*
 XdClearDraget(dr)
	ridisegna l'oggetto generando un evento di redraw
*/
void XdClearDraget(dr)
Draget dr;
{
DragetClass class;
class=dr->xdcore.draget_class;
class->xdcore_class.clear(dr);
}

/*
 XdSetZoom(dr,zoom)
	setta il fattore di zoom
*/
void XdSetZoom(dr,zoom, do_expose)
Draget dr;
float zoom;
Boolean do_expose;
{
DragetClass class;
Draget drf;
XdLista dr_list;
class=dr->xdcore.draget_class;

/*
printf("\n set zoom %f\n",zoom);
*/
if(XdIsGroup(dr))
	{
	dr_list=XdGroupGetList(dr);
	ListDragetRew(dr_list);
	while((drf=ListDragetNext(dr_list)) != NULL)
		XdSetZoom(drf,zoom,do_expose);
	}
if(do_expose) {
	if(dr->xdcore.managed == True)
		class->xdcore_class.clear(dr);
	}
class->xdcore_class.zoom=zoom;
if(dr->xdcore.managed == True)
	class->xdcore_class.crea_regions(dr);
}

/*
 XdChangeZoom(dr,zoom)
	modifica per un oggetto il fattore di zoom.
	Differisce dalla SetZoom perche' vengono
	liberate le regions dell'oggetto allo zoom
	precedente
*/
void XdChangeZoom(dr,zoom)
Draget dr;
float zoom;
{
DragetClass class;
Draget drf;
XdLista dr_list;
class=dr->xdcore.draget_class;

if(XdIsGroup(dr))
	{
	dr_list=XdGroupGetList(dr);
	ListDragetRew(dr_list);
	while((drf=ListDragetNext(dr_list)) != NULL)
		XdChangeZoom(drf,zoom);
	}

if(dr->xdcore.managed == True)
        class->xdcore_class.clear(dr);
class->xdcore_class.zoom=zoom;
if(dr->xdcore.managed == True)
	{
        class->xdcore_class.delete_regions(dr);
        class->xdcore_class.crea_regions(dr);
	}
}
/*
 XdSetFilled(dr,filled)
	setta l'attributo di fill per l'oggetto (specifica se
	l'oggetto deve essere riempito
*/
void XdSetFilled(dr,filled)
Draget dr;
Boolean filled;
{
DragetClass class;
class=dr->xdcore.draget_class;
/*
 Se l'attributo di fill e' modificato lo setta e forza il ridisegno
 dell'oggetto
*/
if(dr->xdcore.filled!=filled)
	{
	dr->xdcore.filled=filled;
	if(dr->xdcore.managed == True)
		class->xdcore_class.clear(dr);
	}
}

Boolean XdGetFilled(dr)
Draget dr;
{
return(dr->xdcore.filled);
}

Draget XdCreateDraget(wid,class,gc,gc_bg)
Widget wid;
DragetClass class;
GC gc;
GC gc_bg;
{
Draget dr;
dr=(Draget)XtCalloc(1,class->xdcore_class.draget_size);
if(dr==NULL)
        {
        printf("\n impossibile creare Draget");
        }
dr->xdcore.draget_class= class;
dr->xdcore.wid=wid;

dr->xdcore.gc=gc;
dr->xdcore.gc_bg=gc_bg;
/*
 richiama il metodo di inizializzazione
 di classe
 solo se non e' stato gia' chiamato
*/
if(class->xdcore_class.initialized == False)
	{
	class->xdcore_class.class_initialize(dr);
	class->xdcore_class.initialized= True;
        }

/*
 richiama il metodo di inizializzazione del
 draget
*/
class->xdcore_class.initialize(dr);
return(dr);
}

Draget XdDuplicateDraget(dr,wid)
Draget dr;
Widget wid; /* drawing area su cui portare il draget */
{
Draget drnew;
DragetClass class;
class=dr->xdcore.draget_class;

drnew=XdCreateDraget(wid,class,dr->xdcore.gc,dr->xdcore.gc_bg);
drnew->xdcore.wid=wid; /* setta la drawing area dell'oggetto destinazione */
/*
 richiama il metodo di inizializzazione
*/
class->xdcore_class.copy(dr,drnew);
return(drnew);
}

void XdManageDraget(dr)
Draget dr;
{
DragetClass class;
class=XdClass(dr);
class->xdcore_class.expose(dr,NULL);
dr->xdcore.managed=True;
}


void XdDrawDraget(dr,ev)
Draget dr;
XEvent *ev;
{
DragetClass class;
class = XdClass(dr);
class->xdcore_class.expose(dr,ev);
}

Boolean XdPickDraget(dr,ev)
Draget dr;
XEvent *ev;
{
DragetClass class;
class = XdClass(dr);
return(class->xdcore_class.pick(dr,ev,PICK_NORMAL));
}

Boolean XdMoveDraget(dr,ev)
Draget dr;
XEvent *ev;
{
DragetClass class;
class = XdClass(dr);
XdSnap(dr,ev);
if(dr->xdcore.resizing)
	return(class->xdcore_class.resize(dr,ev));
else if(dr->xdcore.moving)
	return(class->xdcore_class.move(dr,ev));
}

Boolean XdEndMoveDraget(dr,ev)
Draget dr;
XEvent *ev;
{
DragetClass class;
class = XdClass(dr);
XdSnap(dr,ev);
if(dr->xdcore.resizing)
        return(class->xdcore_class.end_resize(dr,ev));
else if(dr->xdcore.moving)
        return(class->xdcore_class.end_move(dr,ev));
}


Boolean XdPickExtDraget(dr,ev)
Draget dr;
XEvent *ev;
{
DragetClass class;
class = XdClass(dr);
return(class->xdcore_class.pick(dr,ev,PICK_EXTENDED));
}

void XdDeselectDraget(dr,do_expose)
Draget dr;
Boolean do_expose;
{
DragetClass class;
class = XdClass(dr);
class->xdcore_class.select(dr,False,do_expose);
}

void XdSelectDraget(dr,do_expose)
Draget dr;
Boolean do_expose;
{
DragetClass class;
class = XdClass(dr);
class->xdcore_class.select(dr,True,do_expose);
}

Boolean XdDragetInRect(dr,rect)
Draget dr;
XRectangle *rect;
{
XRectangle rect_dr;
XClipBox(dr->xdcore.select_region,&rect_dr);
if(rect_dr.x >= rect->x   && rect_dr.y >= rect->y &&
   (rect_dr.x+rect_dr.width) <= (rect->x+rect->width) && 
   (rect_dr.y+rect_dr.height) <= (rect->y+rect->height))
	return(True);
return(False);
}


void XdFirstDraw(dr,ev)
Draget dr;
XEvent *ev;
{
DragetClass class;
class = XdClass(dr);
XdSnap(dr,ev);
class->xdcore_class.first_draw(dr,ev);
}

void XdFirstPoint(dr,ev)
Draget dr;
XEvent *ev;
{
DragetClass class;
XdSnap(dr,ev);
class = XdClass(dr);
class->xdcore_class.first_point(dr,ev);
}

Boolean XdLastPoint(dr,ev)
Draget dr;
XEvent *ev;
{
Boolean retval;
DragetClass class;
XdSnap(dr,ev);
class = XdClass(dr);
retval=class->xdcore_class.last_point(dr,ev);
return(retval);
}

XdSnap(dr,eve)
Draget dr;
XEvent *eve;
{
Window root,child;
Display *display;
int x_root,y_root,wx,wy;
unsigned int mask;
int step;
DragetClass class;
class=dr->xdcore.draget_class;
step=dr->xdcore.step * class->xdcore_class.zoom;
display=XtDisplay(dr->xdcore.wid);
switch(eve->type)
 {
 case MotionNotify:
 case ButtonPress:
 case ButtonRelease:
	    wx= eve->xbutton.x;
            wy= eve->xbutton.y;
            eve->xbutton.x = (int)(rint((double)(wx/step)) * step);
            eve->xbutton.y = (int)(rint((double)(wy/step)) * step);
	    if(abs(wx%step) > step/2 )
		eve->xbutton.x += step;
	    if(abs(wy%step) > step/2 )
		eve->xbutton.y += step;
    break;
      otherwise:
      break;
   }

}

XdWriteDraget(dr,fp)
Draget dr;
FILE *fp;
{
extern DragetClass xdCoreDragetClass;
DragetClass class;
class = XdClass(dr);
/*
 richiama il metodo di write relativo a XdCore che
 si occupa della scrittura delle informazioni relative
 ai GC (gc e gc_fg)
*/
xdCoreDragetClass->xdcore_class.write(dr,fp);
/*
 richiama il metodo di write specifico per l'oggetto
*/
class->xdcore_class.write(dr,fp);
}

#ifdef XPRINTER_USED
XdPrintDraget(dr)
Draget dr;
{
extern DragetClass xdCoreDragetClass;
DragetClass class;
class = XdClass(dr);
/*
 richiama il metodo di print relativo a XdCore che
 si occupa del salvataggio
 dei GC (gc e gc_fg) (Flag settato a True).
*/
xdCoreDragetClass->xdcore_class.print(dr,True);
/*
 richiama il metodo di print specifico per l'oggetto
*/
class->xdcore_class.print(dr,True);
/*
 richiama il metodo di print relativo a XdCore che
 si occupa del ripristino
 dei GC (gc e gc_fg) (Flag settato a False).
*/
xdCoreDragetClass->xdcore_class.print(dr,False);
}
#endif

XdGetSize(dr,xmin,ymin,xmax,ymax)
Draget dr;
int *xmin,*ymin,*xmax,*ymax;
{
DragetClass class;
class = XdClass(dr);
class->xdcore_class.get_size(dr,xmin,ymin,xmax,ymax);
}

XdModify(dr,dx,dy,dw,dh,ev)
Draget dr;
int dx,dy,dw,dh;
XEvent *ev;
{
DragetClass class;
class = XdClass(dr);
class->xdcore_class.modify(dr,dx,dy,dw,dh,ev);
class->xdcore_class.expose(dr,NULL);
}

/*
 In base alla tag di descrizione contenuta nel file ASCII di descrizione
 del background ricava il puntatore alla classe
*/
DragetClass XdTagToClass(tag)
char *tag;
{
DragetClass class;
extern XdLineClassRec xdLineClassRec;
extern XdRectClassRec xdRectClassRec;
extern XdCircleClassRec xdCircleClassRec;
extern XdConnClassRec xdConnClassRec;
extern XdGroupClassRec xdGroupClassRec;
switch(tag[0])
	{
	case 'l':
	return(&xdLineClassRec);
	break;
	case 'r':
	return(&xdRectClassRec);
	break;
	case 'c':
	return(&xdCircleClassRec);
	break;
	case 'p':
	return(&xdPoliClassRec);
	case 'C':
	return(&xdConnClassRec);
	case 'g':
	return(&xdGroupClassRec);
	}
}
	
Draget XdReadRecord(wid,xdgc,fp)
Widget wid;  /* drawing area su cui disegnare */
XdGC *xdgc;
FILE *fp;
{
fpos_t pos;
Draget dr;
int x,y,xf,yf;
GC gc,gc_bg;
char buf[10];
extern DragetClass xdCoreDragetClass;
DragetClass class;
dr=NULL;
/*
 Richiama il metodo di read di core che si occupa di leggere
 i settaggi generali
*/
xdgc->wid=wid;
if(xdCoreDragetClass->xdcore_class.read(dr,xdgc,fp) == True)
	{
/*
 lettura del record proprio dell'oggetto e sua creazione
*/
	fscanf(fp,"%s",buf);
/*
 crea i gc utilizzati per gc e gc_bg
*/
	XdCreaGCs(wid,xdgc,&gc,&gc_bg);
/*
 il nome della classe corrisponde con la tag usata nel file
*/
	dr=XdCreateDraget(wid,XdTagToClass(buf),gc,gc_bg);
/*
richiama il metodo per la lettura dei parametri dell'oggetto
*/
	class=XdClass(dr);
	class->xdcore_class.zoom=1.0;
	class->xdcore_class.read(dr,xdgc,fp); 
	return(dr);
	}
else 
/*
 segnala che la lettura e' terminata
*/
	return(NULL);
}

XdCreaGCs(wid,xdgc,gc,gc_bg)
Widget wid;
XdGC *xdgc;
GC *gc;
GC *gc_bg;
{
unsigned long valuemask= GCForeground | GCBackground | GCLineWidth
                         | GCLineStyle | GCSubwindowMode;
XGCValues values;
values.foreground = xdgc->fg_contorno;
values.background = xdgc->bg_contorno;
values.line_width = xdgc->width_contorno;
values.line_style = xdgc->style_contorno;
values.subwindow_mode= IncludeInferiors;
*gc= XtGetGC (wid, valuemask, &values);
values.foreground = xdgc->fg_fill;
values.background = xdgc->bg_contorno;
*gc_bg = XtGetGC (wid, valuemask, &values);
}

Boolean _XdInheritPick(dr,ev,type)
Draget dr;
XEvent *ev;
Boolean type;
{
int iret;
DragetClass class,superclass;
Boolean selected;
class= XdClass(dr);
superclass=class->xdcore_class.superclass;
return(superclass->xdcore_class.pick(dr,ev,type));
}

void _XdInheritSelect(dr,flag,do_expose)
Draget dr;
Boolean flag;
Boolean do_expose;
{
DragetClass class,superclass;
class= XdClass(dr);
superclass=class->xdcore_class.superclass;
superclass->xdcore_class.select(dr,flag,do_expose);
}

void _XdInheritClassInitialize(dr)
Draget dr;
{
DragetClass class,superclass;
class= XdClass(dr);
superclass=class->xdcore_class.superclass;
if(class->xdcore_class.initialized == False)
	{
	superclass->xdcore_class.class_initialize(dr);
	class->xdcore_class.initialized=True;
	}
}

void _XdInheritDeleteRegions(dr)
Draget dr;
{
DragetClass class,superclass;
class= XdClass(dr);
superclass=class->xdcore_class.superclass;
superclass->xdcore_class.delete_regions(dr);
}

/*
 Funzione per settare alla classe XdConn il metodo esterno
 di cancellazione connessione
*/
Boolean XdSetDeleteConn(void * deleteConn)
{
xdConnClassRec.xdconn_class.deleteConn= deleteConn;
return(True);
}

/*
 Funzione che stabilisce se un Draget e' del tipo
 connessione (Conn)
*/
Boolean XdIsConn(dr)
Draget dr;
{
DragetClass class;
class= XdClass(dr);
if(class == (DragetClass)&xdConnClassRec )
	return(True);
else
	return(False);
}

/*
 Funzioni generiche utilizzate all'interno
 degli oggetti Xd
*/
char *XdPixelToString(wid,pixel)
Widget wid;
Pixel pixel;
{
Arg args[2];
XColor Colore;
Colormap cmap;
char *vstring;
Display *Displ;

/*  Ricavo il display dal widget passato come parametro */
Displ = XtDisplay (wid);
Colore.pixel=pixel;
XtSetArg (args[0], XmNcolormap, &cmap);
XtGetValues (wid, args, 1);
XQueryColor (Displ, cmap, &Colore);
vstring = (char *)XtCalloc (15, sizeof(char));
sprintf (vstring,"#%04x%04x%04x",Colore.red,Colore.green,Colore.blue);
return (vstring);
}

Pixel XdStringToPixel(wid,stringa)
Widget wid;
String stringa;
{
Colormap colmap;
XColor xcol;
colmap = DefaultColormap ( XtDisplay(wid),
                        DefaultScreen(XtDisplay(wid)) );
if ( !XParseColor (XtDisplay(wid) , colmap , stringa , &xcol) )
           {
           printf("Errore XParseColor: colore inesistente\n");
           return(0);
           }
if(!XAllocColor(XtDisplay(wid),colmap,&xcol))
           {
           printf("Errore XAllocColor: impossibile allocare un nuovo colore\n");
           return(0);
           }
return(xcol.pixel);
}


#if defined VMS
static double rint( val)
double val;
{
int app_int;
double ret;
        app_int=(int)val;
        ret=(double)app_int;
return(ret);
}
#endif
