/**********************************************************************
*
*       C Source:               XdCircle.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Thu Oct 17 15:46:55 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XdCircle.c-2 %  (%full_filespec: XdCircle.c-2:csrc:1 %)";
#endif
/*
   modulo XdCircle.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdCircle.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XdCircle.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*
 XdCircle - oggetto cerchio 
*/
#include <Xm/Xm.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <Xd/XdCoreP.h>
#include <Xd/XdCircleP.h>
#include <Xd/Xd.h>
#include <Xd/XdGeom.h>

/*
 Dichiarazione dei metodi
*/
static void Initialize();
static void Destroy();
static Boolean Resize();
static Boolean EndResize();
static Boolean Move();
static Boolean EndMove();
static void Redraw();
static Boolean FirstPoint();
static Boolean LastPoint();
static Boolean FirstDraw();
static void Clear();
static Boolean Read();
static void Write();
static void GetSize();
static void Modify();
static void CreaRegions();
static void Copy();
#ifdef XPRINTER_USED
static void Print();
#endif
/*
 funzioni di utilita'
*/
static void draw_arc();
static void draw_arc_first();
static void draw_circle();
/*
 Inizializzazione del class record
*/
XdCircleClassRec xdCircleClassRec = {
	{ /* xdcore fields */
	  /* initialized */     False,
	  /* class_name */ 	"XdCircle",
	  /* superclass */      (DragetClass)&xdCoreClassRec,
	  /* gcxor      */	NULL,
	  /* gcsel      */	NULL,
	  /* zoom       */      1.0,
	  /* draget size */	sizeof(XdCircleRec),
	  /* class_init */	_XdInheritClassInitialize,
	  /* initialize */	Initialize,
	  /* destroy    */	Destroy,
	  /* resize     */	Resize,
	  /* end resize   */	EndResize,
	  /* move     */	Move,
	  /* end move */	EndMove,
	  /* expose     */      Redraw,
	  /* first_point */	FirstPoint,
	  /* last_point  */	LastPoint,
	  /* first_draw  */     FirstDraw,
          /* pick       */ 	_XdInheritPick,
	  /* select     */	_XdInheritSelect,
	  /* clear      */      Clear,
	  /* crea_regions */    CreaRegions,
	  /* delete_regions */  _XdInheritDeleteRegions,
	  /* read	*/	Read,
	  /* write	*/	Write,
	  /* get_size   */      GetSize,
	  /* modify     */      Modify,
	  /* copy       */      Copy,
#ifdef XPRINTER_USED
	  /* print      */      Print
#endif
	},
	{
	 /* dummy       */ 0
	}
};

DragetClass xdCircleDragetClass = (DragetClass) &xdCircleClassRec;

/*
 Metodi
*/

static void Initialize(dra)
Draget dra;
{
}

static void Destroy(dra)
Draget dra;
{
XdCircleDraget dr;
dr=(XdCircleDraget)dra;
dr->xdcore.managed= False; /* impedisce che venga effettuato
			il redraw su oggetto in cancellazione */
}

/*
  Ridimensionamento del rettangolo tramite movimento del
  mouse
*/
static Boolean Resize(dra,ev)
Draget dra;
XEvent *ev;
{
int xfix,yfix;
int xini,yini,xfin,yfin;
Display *display;
XdCircleDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
dr=(XdCircleDraget)dra;
z = class->xdcore_class.zoom;
display=XtDisplay(dr->xdcore.wid);

/*
 A seconda del numero della regione di resize selezionata determina
 quale e' il punto fisso
*/
if(dr->xdcore.is_first == False)
	{
	get_real_limits(dr,&xini,&yini,&xfin,&yfin);
	switch(dr->xdcore.num_resize)
       	 {
       	 case 0:
       	 xini = dr->xdcircle.xprev;
       	 yini = dr->xdcircle.yprev;
       	 break;
       	 case 1:
       	 xfin = dr->xdcircle.xprev;
       	 yini = dr->xdcircle.yprev;
       	 break;
       	 case 2:
       	 xfin = dr->xdcircle.xprev;
       	 yfin = dr->xdcircle.yprev;
       	 break;
       	 case 3:
       	 xini = dr->xdcircle.xprev;
       	 yfin = dr->xdcircle.yprev;
       	 break;
       	 }

	get_circle_coord(dr,
		&xini,&yini,&xfin,&yfin);

	draw_arc(dr,class->xdcore_class.gcxor,False,
                        (int)(z * xini),(int)(z * yini),
                        (int)(z * xfin),
                        (int)( z * yfin),dr->xdcircle.a1,dr->xdcircle.a2);
	}
else
	dr->xdcore.is_first = False;

dr->xdcircle.xprev= ev->xmotion.x /z;
dr->xdcircle.yprev= ev->xmotion.y /z;
get_real_limits(dr,&xini,&yini,&xfin,&yfin);

switch(dr->xdcore.num_resize)
        {
        case 0:
        xini = ev->xbutton.x / z;
        yini = ev->xbutton.y / z;
        break;
        case 1:
        xfin = ev->xbutton.x / z;
        yini = ev->xbutton.y / z;
        break;
        case 2:
        xfin = ev->xbutton.x / z;
        yfin = ev->xbutton.y / z;
        break;
        case 3:
        xini = ev->xbutton.x / z;
        yfin = ev->xbutton.y / z;
        break;
        }
get_circle_coord(dr,&xini,&yini,&xfin,&yfin);
draw_arc(dr,class->xdcore_class.gcxor,False,
                        (int)(z * xini),(int)(z * yini),
                        (int)(z * xfin),
                        (int)( z * yfin),dr->xdcircle.a1,dr->xdcircle.a2);
XFlush(display);
}

static Boolean EndResize(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
XdCircleDraget dr;
int xini,yini,xfin,yfin;
DragetClass class;
class=XdClass(dra);
dr=(XdCircleDraget)dra;
z = class->xdcore_class.zoom;
/*
 se non e' stato eseguito alcun movimento esce subito
*/
if(dr->xdcore.is_first== True)
	{
	dr->xdcore.managed= True; /* l'oggetto e' completo */
	dr->xdcore.moving= False; /* termine move dell'oggetto */
	dr->xdcore.resizing= False; /* termine resize dell'oggetto */
	return(False);
	}
/*
 esegue il clear del disegno di partenza
*/
class->xdcore_class.clear(dr);
/*
 memorizza i punti finali
*/
get_real_limits(dr,&xini,&yini,&xfin,&yfin);
switch(dr->xdcore.num_resize)
        {
        case 0:
        xini = ev->xbutton.x / z;
        yini = ev->xbutton.y / z;
        break;
        case 1:
        xfin = ev->xbutton.x / z;
        yini = ev->xbutton.y / z;
        break;
        case 2:
        xfin = ev->xbutton.x / z;
        yfin = ev->xbutton.y / z;
        break;
        case 3:
        xini = ev->xbutton.x / z;
        yfin = ev->xbutton.y / z;
        break;
        }

get_circle_coord(dr,&xini,&yini,
		    &xfin,&yfin);
dr->xdcore.x=xini;
dr->xdcore.y=yini;
dr->xdcircle.xf=xfin;
dr->xdcircle.yf=yfin;

dr->xdcore.managed= True; /* l'oggetto e' completo */
dr->xdcore.moving= False; /* termine move dell'oggetto */
dr->xdcore.resizing= False; /* termine resize dell'oggetto */

/*
 Distrugge le regions create in precedenza
*/
class->xdcore_class.delete_regions(dr);
/*
 Crea le nuove regions
*/
class->xdcore_class.crea_regions(dr);
/*
 Ridisegna l'oggetto
*/
class->xdcore_class.expose(dr,NULL);
}


static Boolean Move(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
static int x_click,y_click;
int xfix,yfix;
Display *display;
XdCircleDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdCircleDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/*
 il delta di spostamento viene memorizzato rispettivamente in:
	dr->xdcircle.xprev e
	dr->xdcircle.yprev
*/
if(dr->xdcore.is_first == False)
	{
	draw_arc(dr,class->xdcore_class.gcxor,False,
		(int)(z*(dr->xdcore.x+dr->xdcircle.xprev)),
		(int)(z*(dr->xdcore.y+dr->xdcircle.yprev)),
		(int)(z*(dr->xdcircle.xf+dr->xdcircle.xprev)),
		(int)(z*(dr->xdcircle.yf+dr->xdcircle.yprev)),
		dr->xdcircle.a1,dr->xdcircle.a2);
	}
else
	{
	dr->xdcore.is_first = False;
	x_click = ev->xmotion.x / z;
	y_click = ev->xmotion.y / z;
	}

dr->xdcircle.xprev= ev->xmotion.x / z - x_click;
dr->xdcircle.yprev= ev->xmotion.y / z - y_click;
draw_arc(dr,class->xdcore_class.gcxor,False,
	(int)(z*(dr->xdcore.x+dr->xdcircle.xprev)),
	(int)(z*(dr->xdcore.y+dr->xdcircle.yprev)),
	(int)(z*(dr->xdcircle.xf+dr->xdcircle.xprev)),
	(int)(z*(dr->xdcircle.yf+dr->xdcircle.yprev)),
	dr->xdcircle.a1, dr->xdcircle.a2);

XFlush(display);
}


static Boolean EndMove(dra,ev)
Draget dra;
XEvent *ev;
{
XdCircleDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdCircleDraget)dra;
/*
 se non e' stato eseguito alcun movimento esce subito
*/
if(dr->xdcore.is_first == True)
	{
	dr->xdcore.managed= True; /* l'oggetto e' completo */
	dr->xdcore.moving= False; /* termine move dell'oggetto */
	dr->xdcore.resizing= False; /* termine resize dell'oggetto */
	return(False);
	}
/*
 esegue il clear del disegno di partenza
*/
class->xdcore_class.clear(dr);
/*
 memorizza i punti finali
*/
dr->xdcircle.xf += dr->xdcircle.xprev;
dr->xdcircle.yf +=  dr->xdcircle.yprev;
dr->xdcore.x +=  dr->xdcircle.xprev;
dr->xdcore.y += dr->xdcircle.yprev;

dr->xdcore.managed= True; /* l'oggetto e' completo */
dr->xdcore.moving= False; /* termine move dell'oggetto */
dr->xdcore.resizing= False; /* termine resize dell'oggetto */

/*
 Distrugge le regions create in precedenza
*/
class->xdcore_class.delete_regions(dr);
/*
 Crea le nuove regions
*/
class->xdcore_class.crea_regions(dr);
/*
 Ridisegna l'oggetto
*/
class->xdcore_class.expose(dr,NULL);
}


static void Redraw(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
Region region;
Display *display;
unsigned int delta=4;
XdCircleDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdCircleDraget)dra;
/*
 se l'oggetto non e' completo oppure e' in cancellazione
 esce senza ridisegnarlo
*/
if (dr->xdcore.managed == False) 
	return;
display=XtDisplay(dr->xdcore.wid);
/*
 Se il metodo e' stato richiamato a risposta di un evento
 di expose ( ev != NULL) -> Crea una clipping region per il
 ridisegno e la setta per i gc utilizzati nel ridisegno
*/
/******* con clipping region ******/
if(ev!=NULL)
        region=RegionClip(ev);
else
        region=RegionClipBox(dr->xdcore.select_region);

XSetRegion(display,dr->xdcore.gc,region);
XSetRegion(display,class->xdcore_class.gcsel,region);
XSetRegion(display,dr->xdcore.gc_bg,region);
/****** fine clipping **********/
draw_arc(dr,dr->xdcore.gc,dr->xdcore.filled,
            (int)(z * dr->xdcore.x),(int)(z * dr->xdcore.y),
            (int)(z * dr->xdcircle.xf), (int)(z * dr->xdcircle.yf),
		dr->xdcircle.a1, dr->xdcircle.a2);
/*
 Se l'oggetto e' nello stato selezionato disegna i rettangolini
 di selezione
*/
if(dr->xdcore.selected)
	{
	int xmin,ymin,xmax,ymax;
	get_real_limits(dr,&xmin,&ymin,&xmax,&ymax);
        XFillRectangle(display,XtWindow(dr->xdcore.wid),
                        class->xdcore_class.gcsel,
                        (int)(z*(xmin)-(delta/2)),
                        (int)(z*(ymin)-(delta/2)),
                                delta,delta);
        XFillRectangle(display,XtWindow(dr->xdcore.wid),
                        class->xdcore_class.gcsel,
                        (int)(z*xmax-(delta/2)),
                        (int)(z*ymax-(delta/2)),
                                delta,delta);
        XFillRectangle(display,XtWindow(dr->xdcore.wid),
                        class->xdcore_class.gcsel,
                        (int)(z*xmax-(delta/2)),
                        (int)(z*(ymin)-(delta/2)),
                                delta,delta);
        XFillRectangle(display,XtWindow(dr->xdcore.wid),
                        class->xdcore_class.gcsel,
                        (int)(z*(xmin)-(delta/2)),
                        (int)(z*ymax-(delta/2)),
                                delta,delta);
	}
XDestroyRegion(region);
}

#ifdef XPRINTER_USED
static void Print(dra,flag)
Draget dra;
Boolean flag;
{
float z;
XdCircleDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdCircleDraget)dra;
draw_arc(dr,dr->xdcore.gc,dr->xdcore.filled,
            (int)(z * dr->xdcore.x),(int)(z * dr->xdcore.y),
            (int)(z * dr->xdcircle.xf), (int)(z * dr->xdcircle.yf),
		dr->xdcircle.a1, dr->xdcircle.a2);
}
#endif

static Boolean FirstPoint(dra,ev)
Draget dra;
XEvent *ev;
{
XdCircleDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdCircleDraget)dra;
dr->xdcore.x= ev->xbutton.x / z;
dr->xdcore.y= ev->xbutton.y / z;
dr->xdcore.managed= False; /* indica che l'oggetto e' in fase di 
				costruzione: impedisce che venga effettuato
				il redraw su oggetto non completo */
dr->xdcore.is_first= True;
}

static Boolean LastPoint(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
int topx,topy,width,height,a1,a2;
XdCircleDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdCircleDraget)dra;
z = class->xdcore_class.zoom;
/*
 memorizza i punti finali
*/
dr->xdcircle.xf = ev->xbutton.x / z;
dr->xdcircle.yf = ev->xbutton.y /z;
if(dr->xdcircle.type == XD_TY_ARC)
	{
	get_first_arc_coord(dr->xdcore.x,dr->xdcore.y,
		dr->xdcircle.xf,dr->xdcircle.yf,
		&topx,&topy,&width,&height,&a1,&a2);

	dr->xdcore.x=topx;
	dr->xdcore.y=topy;
	dr->xdcircle.xf=topx+width;
	dr->xdcircle.yf=topy+height;
	dr->xdcircle.a1=a1;
	dr->xdcircle.a2=a2;
	}
else
	{
	dr->xdcircle.a1=0;
	dr->xdcircle.a2=360*64;
	}


dr->xdcore.managed= True; /* l'oggetto e' completo */
class->xdcore_class.crea_regions(dr);
/*
 forza il ridisegno dell'oggetto finale
*/
class->xdcore_class.expose(dr,NULL);
/*
 se l'oggetto e' di dimensione nulla ritorna
 False
*/
if(dr->xdcircle.xf == dr->xdcore.x && dr->xdcircle.yf == dr->xdcore.y)
        return(False);
else
        return(True);

}

static Boolean FirstDraw(dra,ev)
Draget dra;
XEvent *ev;
{
Display *display;
XdCircleDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdCircleDraget)dra;
display=XtDisplay(dr->xdcore.wid);
if(dr->xdcore.is_first == False)
	{
	if(dr->xdcircle.type == XD_TY_ARC)
		draw_arc_first(dr,class->xdcore_class.gcxor,False,
			(int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
			(int)(z*dr->xdcircle.xprev), (int)(z*dr->xdcircle.yprev));
	else
		draw_circle(dr,class->xdcore_class.gcxor,False,
                        (int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
                        (int)(z*dr->xdcircle.xprev), (int)(z*dr->xdcircle.yprev)
);
	}
else
	dr->xdcore.is_first = False;

dr->xdcircle.xprev= ev->xmotion.x / z;
dr->xdcircle.yprev= ev->xmotion.y / z;

if(dr->xdcircle.type == XD_TY_ARC)
	draw_arc_first(dr,class->xdcore_class.gcxor,False,
                        (int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
                        (int)(z*dr->xdcircle.xprev), (int)(z*dr->xdcircle.yprev));
else
	draw_circle(dr,class->xdcore_class.gcxor,False,
                        (int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
                        (int)(z*dr->xdcircle.xprev), (int)(z*dr->xdcircle.yprev)
);

XFlush(display);
}


static void Clear(dra)
Draget dra;
{
static XEvent eve_exp;
XmDrawingAreaCallbackStruct str;
Display *display;
float z;
XdCircleDraget dr;
int xmin,xmax,ymin,ymax;
unsigned int width,height;
int delta=3;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdCircleDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/* 
 Determina l'area su cui effettuare il clear
*/
if(dr->xdcore.x < dr->xdcircle.xf)
	{
	xmin = dr->xdcore.x;
	xmax = dr->xdcircle.xf;
	}
else
	{
	xmin = dr->xdcircle.xf;
	xmax = dr->xdcore.x;
	}

if(dr->xdcore.y < dr->xdcircle.yf)
	{
	ymin = dr->xdcore.y;
	ymax = dr->xdcircle.yf;
	}
else
	{
	ymin = dr->xdcircle.yf;
	ymax = dr->xdcore.y;
	}
width= xmax-xmin+2*delta;
height= ymax-ymin+2*delta;

/* patch per server di ucin14 **/
XDrawLine(display, XtWindow(dr->xdcore.wid), class->xdcore_class.gcxor,
        (int)(z*xmin), (int)(z*ymin),
                (int) (z*xmin), (int)(z*ymin));
/* fine patch ***/


XClearArea(display,XtWindow(dr->xdcore.wid),
			(int)(z * (xmin-delta)),
			(int)(z * (ymin-delta)),
			(int)(z * width),(int)(z * height),True);

}


static Boolean Read(dra,xdgc,fp)
Draget dra;
XdGC *xdgc;
FILE *fp;
{
int x,y,xf,yf,a1,a2;
DragetClass class;
XdCircleDraget dr;
dr=(XdCircleDraget)dra;
class=XdClass(dra);
fscanf(fp,"%d %d %d %d %d %d",&x,&y,&xf,&yf,&a1,&a2);
dr->xdcore.x=x;
dr->xdcore.y=y;
dr->xdcircle.xf=xf;
dr->xdcircle.yf=yf;
dr->xdcircle.a1=a1;
dr->xdcircle.a2=a2;
dr->xdcore.filled=xdgc->filled;
dr->xdcore.managed= True; /* l'oggetto e' completo */
class->xdcore_class.crea_regions(dr);
return(True);
}


static void Copy(dra,dra_dest)
Draget dra;
Draget dra_dest;
{
DragetClass class;
XdCircleDraget dr;
XdCircleDraget dr_dest;
dr=(XdCircleDraget)dra;
dr_dest=(XdCircleDraget)dra_dest;
class=XdClass(dra);
dr_dest->xdcore.x=dr->xdcore.x;
dr_dest->xdcore.y=dr->xdcore.y;
dr_dest->xdcircle.xf=dr->xdcircle.xf;
dr_dest->xdcircle.yf=dr->xdcircle.yf;
dr_dest->xdcircle.a1=dr->xdcircle.a1;
dr_dest->xdcircle.a2=dr->xdcircle.a2;
dr_dest->xdcore.filled=dr->xdcore.filled;
dr_dest->xdcore.managed= True; /* l'oggetto e' completo */
dr_dest->xdcore.selected= True;
class->xdcore_class.crea_regions(dr_dest);
}

static void Write(Draget dra, FILE *fp)
{
XdCircleDraget dr;
dr=(XdCircleDraget)dra;
fprintf(fp,"circ %d %d %d %d %d %d\n",dr->xdcore.x,dr->xdcore.y,
                dr->xdcircle.xf,dr->xdcircle.yf,
		dr->xdcircle.a1,dr->xdcircle.a2);
}

static void GetSize(dra,xmin,ymin,xmax,ymax)
Draget dra;
int *xmin,*ymin,*xmax,*ymax;
{
XdCircleDraget dr;
XGCValues values;
int offset;

dr=(XdCircleDraget)dra;
*xmin=(dr->xdcore.x < dr->xdcircle.xf) ? dr->xdcore.x : dr->xdcircle.xf;
*ymin=(dr->xdcore.y < dr->xdcircle.yf) ? dr->xdcore.y : dr->xdcircle.yf;

*xmax=(dr->xdcore.x > dr->xdcircle.xf) ? dr->xdcore.x : dr->xdcircle.xf;
*ymax=(dr->xdcore.y > dr->xdcircle.yf) ? dr->xdcore.y : dr->xdcircle.yf;

/*
 tiene conto dello spessore della linea
*/
XGetGCValues(XtDisplay(dr->xdcore.wid),dr->xdcore.gc,GCLineWidth,
                &values);
if(values.line_width >= 2)
        {
        offset= values.line_width/2;
        *xmin= *xmin-offset;
        *ymin= *ymin-offset;
        *xmax= *xmax+offset;
        *ymax= *ymax+offset;
        }
/*
 Ricava la dimensione reale del'arco
*/
get_real_limits(dr,xmin,ymin,xmax,ymax);

}

static void Modify(dra,dx,dy,dw,dh,ev)
Draget dra;
int dx,dy,dw,dh;
XEvent *ev;
{
XdCircleDraget dr;
GROUP_EV *gr_ev; /* notifica un evento di ridimensionamento del gruppo
                   al singolo componente appartenente al gruppo
                */
DragetClass class;
dr=(XdCircleDraget)dra;
class=XdClass(dra);
gr_ev=(GROUP_EV *)ev;
/*
 esegue il clear del disegno di partenza
*/
class->xdcore_class.clear(dr);
if(gr_ev == NULL)
        {
/*
 trasla l'oggetto
*/
	dr->xdcore.x+=dx;
	dr->xdcore.y+=dy;
	dr->xdcircle.xf+=dx;
	dr->xdcircle.yf+=dy;
	}
else
	{
/*
  le coordinate vengono moltiplicate per il fattore di ridimensionamento
  del gruppo contenitore
*/
        dr->xdcore.x = gr_ev->xfix+gr_ev->fatt_x * (dr->xdcore.x - gr_ev->xfix);
        dr->xdcore.y = gr_ev->yfix+gr_ev->fatt_y * (dr->xdcore.y - gr_ev->yfix);
        dr->xdcircle.xf = gr_ev->xfix+
                        gr_ev->fatt_x * (dr->xdcircle.xf- gr_ev->xfix);
        dr->xdcircle.yf = gr_ev->yfix+
                        gr_ev->fatt_y * (dr->xdcircle.yf- gr_ev->yfix);
        }
/*
 Distrugge le regions create in precedenza
*/
class->xdcore_class.delete_regions(dr);
/*
 Crea le nuove regions
*/
class->xdcore_class.crea_regions(dr);
/*
 Ridisegna l'oggetto
*/
class->xdcore_class.expose(dr,NULL);
}



/*
 Routine di creazione
*/
Draget XdCreateCircleDraget(wid, gc, gc_bg)
Widget wid; /* widget su cui effettuare il disegno */
GC gc;
GC gc_bg;
{
XdCircleDraget dr;
DragetClass class;
class=(DragetClass)&xdCircleClassRec;
dr=(XdCircleDraget)XdCreateDraget(wid,class,gc,gc_bg);
dr->xdcircle.type= XD_TY_CIRCLE;
return(dr);
}

Draget XdCreateArcDraget(wid, gc, gc_bg)
Widget wid; /* widget su cui effettuare il disegno */
GC gc;
GC gc_bg;
{
XdCircleDraget dr;
DragetClass class;
class=(DragetClass)&xdCircleClassRec;
dr=(XdCircleDraget)XdCreateDraget(wid,class,gc,gc_bg);
dr->xdcircle.type= XD_TY_ARC;
return(dr);
}



static void CreaRegions(dr)
XdCircleDraget dr;
{
float z;
int xmin,ymin,xmax,ymax;
DragetClass class;
int iret;
Region select_region;
short delta=4;
class=XdClass(dr);
z = class->xdcore_class.zoom;
if(z>= 0.5) delta *= z;
/*
 Crea la regione di selezione
*/
get_real_limits(dr,&xmin,&ymin,&xmax,&ymax);
dr->xdcore.select_region= RegionRectIntorno(xmin,
                                                ymin,
                                                xmax,
                                                ymax,
                                                z);
/*
 Crea la regione di move
*/

dr->xdcore.num_move_regions=1;
dr->xdcore.move_regions=(Region *)XtCalloc(dr->xdcore.num_move_regions,sizeof(Region));
dr->xdcore.move_regions[0]=  RegionRectIntorno(xmin,
                                                ymin,
                                                xmax,
                                                ymax,
                                                z);
/*
 Crea le regioni di resize
*/
dr->xdcore.num_resize_regions=4;
dr->xdcore.resize_regions=(Region *)XtCalloc(dr->xdcore.num_resize_regions,sizeof(Region));
dr->xdcore.resize_regions[0]=RegionIntorno(xmin,ymin,z);
dr->xdcore.resize_regions[1]=RegionIntorno(xmax,ymin,z);
dr->xdcore.resize_regions[2]=RegionIntorno(xmax,ymax,z);
dr->xdcore.resize_regions[3]=RegionIntorno(xmin,ymax,z);

}


static void draw_circle(dr, drawGC,filled, x1, y1, x2, y2)
        Draget          dr;
	GC 		drawGC;
	Boolean         filled;
        int             x1, y1, x2, y2;
{
        int             width, height, topx, topy;
	GC gc_bg;
	Widget wid;
	wid=dr->xdcore.wid;
	gc_bg=dr->xdcore.gc_bg;

        /* find top left corner */
        topx= (x1 < x2) ? x1 : x2;
        topy= (y1 < y2) ? y1 : y2;

        width= abs(x1-x2);
        height= abs(y1-y2);
	if(filled)
		XFillArc(XtDisplay(wid), XtWindow(wid), gc_bg,
		 	topx, topy,
                	width, height , 0, 360*64);
        XDrawArc(XtDisplay(wid), XtWindow(wid), drawGC, topx, topy,
                width, height, 0, 360*64);
}

static void draw_arc_first(dr, drawGC,filled, x1, y1, x2, y2)
        Draget          dr;
	GC 		drawGC;
	Boolean         filled;
        int             x1, y1, x2, y2;
{
        int             width, height, topx, topy;
	int a1,a2;
	int dx,dy;
	GC gc_bg;
	Widget wid;
	wid=dr->xdcore.wid;
	gc_bg=dr->xdcore.gc_bg;

	get_first_arc_coord(x1,y1,x2,y2,&topx,&topy,&width,&height,&a1,&a2);

	if(filled)
		XFillArc(XtDisplay(wid), XtWindow(wid), gc_bg,
		 	topx, topy,
                	width, height , a1, a2);
        XDrawArc(XtDisplay(wid), XtWindow(wid), drawGC, topx, topy,
                width, height, a1, a2);
}

static void draw_arc(dr, drawGC,filled, x1, y1, x2, y2, a1, a2)
        Draget          dr;
	GC 		drawGC;
	Boolean         filled;
        int             x1, y1, x2, y2;  /* estremi rettangolo circoscritto */ 
	int		a1, a2;   /* angoli iniziale e finale */
{
        int             width, height, topx, topy;
	GC gc_bg;
	Widget wid;
	wid=dr->xdcore.wid;
	gc_bg=dr->xdcore.gc_bg;

        /* find top left corner */
        topx= (x1 < x2) ? x1 : x2;
        topy= (y1 < y2) ? y1 : y2;

        width= abs(x1-x2);
        height= abs(y1-y2);
	if(filled)
		XFillArc(XlDisplay(wid), XlWindow(wid), gc_bg,
		 	topx, topy,
                	width, height , a1, a2);
        XDrawArc(XlDisplay(wid), XlWindow(wid), drawGC, topx, topy,
                width, height, a1, a2);
}

/*
 Calcola i limiti reali dell'arco tenendo conto che occupa solo
 una parte dello spazio occupato dal cerchio 
*/
get_real_limits(dr,xmin,ymin,xmax,ymax)
XdCircleDraget dr;
int *xmin, *ymin, *xmax, *ymax;
{
int dx,dy;

dx= (dr->xdcircle.xf - dr->xdcore.x)/2;
dy= (dr->xdcircle.yf - dr->xdcore.y)/2;

*xmin=(dr->xdcore.x < dr->xdcircle.xf) ? dr->xdcore.x : dr->xdcircle.xf;
*ymin=(dr->xdcore.y < dr->xdcircle.yf) ? dr->xdcore.y : dr->xdcircle.yf;

*xmax=(dr->xdcore.x > dr->xdcircle.xf) ? dr->xdcore.x : dr->xdcircle.xf;
*ymax=(dr->xdcore.y > dr->xdcircle.yf) ? dr->xdcore.y : dr->xdcircle.yf;

/*
 Circonferenza completa -> nessuna variazione
*/
if( dr->xdcircle.a1 == 0 && dr->xdcircle.a2 == (360*64))
	return;
/*
 Archi
*/
if( dr->xdcircle.a1 == 0 && dr->xdcircle.a2 == (90*64))
	{
	*xmin=dr->xdcore.x+dx;
	*ymax=dr->xdcircle.yf-dy;
	}
else if(dr->xdcircle.a1 == (90 *64) && dr->xdcircle.a2 == (90*64))
	{
	*xmax=dr->xdcircle.xf-dx;
	*ymax=dr->xdcircle.yf-dy;
	}
else if(dr->xdcircle.a1 == (180 *64) && dr->xdcircle.a2 == (90*64))
	{
	*ymin=dr->xdcore.y+dy;
	*xmax=dr->xdcircle.xf-dx;
	}
else if(dr->xdcircle.a1 == (270 *64) && dr->xdcircle.a2 == (90*64))
	{
        *ymin=dr->xdcore.y+dy;
	*xmin=dr->xdcore.x+dx;
	}

}

/*
 get_circle_coord
 calcola i limite del cerchio in base ai punti estremi dell'arco
*/

get_circle_coord(dr, xmin,ymin,xmax,ymax)
XdCircleDraget dr;
int *xmin, *ymin, *xmax, *ymax;
{
int dx,dy;
dx= *xmax-*xmin;
dy= *ymax-*ymin;
/*
 Circonferenza completa -> nessuna variazione
*/
if( dr->xdcircle.a1 == 0 && dr->xdcircle.a2 == (360*64))
        return;
/*
 Archi
*/
if( dr->xdcircle.a1 == 0 && dr->xdcircle.a2 == (90*64))
        {
        *xmin= *xmin-dx;
        *ymax= *ymax+dy;
        }
else if(dr->xdcircle.a1 == (90 *64) && dr->xdcircle.a2 == (90*64))
        {
        *xmax= *xmax+dx;
        *ymax= *ymax+dy;
        }
else if(dr->xdcircle.a1 == (180 *64) && dr->xdcircle.a2 == (90*64))
        {
        *ymin= *ymin-dy;
        *xmax= *xmax+dx;
        }
else if(dr->xdcircle.a1 == (270 *64) && dr->xdcircle.a2 == (90*64))
        {
        *ymin= *ymin-dy;
        *xmin= *xmin-dx;
        }

}




get_first_arc_coord(x1,y1,x2,y2,topx,topy,width,height,a1,a2)
int x1,y1,x2,y2;
int *topx,*topy,*width,*height,*a1,*a2;
{
int dx,dy;
/* find top left corner */
*topx= (x1 < x2) ? x1 : x2;
*topy= (y1 < y2) ? y1 : y2;

*width= abs(x1-x2)*2;
*height= abs(y1-y2)*2;
dx=x2-x1;
dy=y2-y1;

if( dx>0 && dy>0)
	{
	*topx-=dx;
	*a1=0;
	*a2=90*64;
	}
else if( dx<0 && dy>0)
	{
	*a1=90*64;
	*a2=90*64;
	}
else if (dx<0 && dy<0)
	{
	*topy+=dy;
	*a1=180*64;
	*a2=90*64;
	}
else if( dx>0 && dy<0)
	{
	*topx-=dx;
	*topy+=dy;
	*a1=270*64;
	*a2=90*64;
	}
}
