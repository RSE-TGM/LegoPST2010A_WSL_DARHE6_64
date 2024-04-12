/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif

/*
 XdRect - oggetto rettangolo 
*/
#include <Xm/Xm.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>

#include <Xd/XdCoreP.h>
#include <Xd/XdRectP.h>
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
static void draw_rect();
/*
 Inizializzazione del class record
*/
XdRectClassRec xdRectClassRec = {
	{ /* xdcore fields */
	  /* initialized */     False,
	  /* class_name */ 	"XdRect",
	  /* superclass */      (DragetClass)&xdCoreClassRec,
	  /* gcxor      */	NULL,
	  /* gcsel      */	NULL,
	  /* zoom       */      1.0,
	  /* draget size */	sizeof(XdRectRec),
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

DragetClass xdRectDragetClass = (DragetClass) &xdRectClassRec;

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
XdRectDraget dr;
dr=(XdRectDraget)dra;
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
Display *display;
XdRectDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
dr=(XdRectDraget)dra;
z = class->xdcore_class.zoom;
display=XtDisplay(dr->xdcore.wid);
/*
 A seconda del numero della regione di resize selezionata determina
 quale e' il punto che deve rimanere fissato
*/
/*
if(dr->xdcore.num_resize==1)
	{
	xfix=dr->xdcore.x;
	yfix=dr->xdcore.y;
	}
else
	{
	xfix=dr->xdrect.xf;
	yfix=dr->xdrect.yf;
	}
*/
switch(dr->xdcore.num_resize)
	{
	case 0:
	xfix=dr->xdrect.xf;
        yfix=dr->xdrect.yf;
        break;
	case 1:
	xfix=dr->xdcore.x;
        yfix=dr->xdrect.yf;
        break;
	case 2:
	xfix=dr->xdcore.x;
        yfix=dr->xdcore.y;
	break;
	case 3:
	xfix=dr->xdrect.xf;
        yfix=dr->xdcore.y;
	break;
	}
	

if(dr->xdcore.is_first == False)
	draw_rect(dr,class->xdcore_class.gcxor,False,
			(int)(z * xfix),(int)(z * yfix),
			(int)(z * dr->xdrect.xprev),
			(int)( z * dr->xdrect.yprev));
else
	{
	dr->xdcore.is_first = False;
	}

dr->xdrect.xprev= ev->xmotion.x /z;
dr->xdrect.yprev= ev->xmotion.y /z;

draw_rect(dr,class->xdcore_class.gcxor,False,
                        (int)(z * xfix),(int)(z * yfix),
                        (int)(z * dr->xdrect.xprev),
			(int)(z * dr->xdrect.yprev));
XFlush(display);
}

static Boolean EndResize(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
XdRectDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdRectDraget)dra;
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
/*
if(dr->xdcore.num_resize==1)
	{
	dr->xdrect.xf = ev->xbutton.x / z;
	dr->xdrect.yf = ev->xbutton.y / z;
	}
else
	{
	dr->xdcore.x = ev->xbutton.x / z;
	dr->xdcore.y = ev->xbutton.y / z;
	}
*/
switch(dr->xdcore.num_resize)
	{
	case 0:
	dr->xdcore.x = ev->xbutton.x / z;
        dr->xdcore.y = ev->xbutton.y / z;
	break;
	case 1:
	dr->xdrect.xf = ev->xbutton.x / z;
	dr->xdcore.y = ev->xbutton.y / z;
	break;
	case 2:
	dr->xdrect.xf = ev->xbutton.x / z;
	dr->xdrect.yf = ev->xbutton.y / z;
	break;
	case 3:
	dr->xdcore.x = ev->xbutton.x / z;
	dr->xdrect.yf = ev->xbutton.y / z;
	break;
	}

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
XdRectDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdRectDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/*
 il delta di spostamento viene memorizzato rispettivamente in:
	dr->xdrect.xprev e
	dr->xdrect.yprev
*/
if(dr->xdcore.is_first == False)
	draw_rect(dr,class->xdcore_class.gcxor,False,
		(int)(z*(dr->xdcore.x+dr->xdrect.xprev)),
		(int)(z*(dr->xdcore.y+dr->xdrect.yprev)),
		(int)(z*(dr->xdrect.xf+dr->xdrect.xprev)),
		(int)(z*(dr->xdrect.yf+dr->xdrect.yprev)));
else
	{
	dr->xdcore.is_first = False;
	x_click = ev->xmotion.x / z;
	y_click = ev->xmotion.y / z;
	}

dr->xdrect.xprev= ev->xmotion.x / z - x_click;
dr->xdrect.yprev= ev->xmotion.y / z - y_click;

draw_rect(dr,class->xdcore_class.gcxor,False,
		(int)(z*(dr->xdcore.x+dr->xdrect.xprev)),
		(int)(z*(dr->xdcore.y+dr->xdrect.yprev)),
		(int)(z*(dr->xdrect.xf+dr->xdrect.xprev)),
		(int)(z*(dr->xdrect.yf+dr->xdrect.yprev)));

XFlush(display);
}


static Boolean EndMove(dra,ev)
Draget dra;
XEvent *ev;
{
XdRectDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdRectDraget)dra;
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
dr->xdrect.xf += dr->xdrect.xprev;
dr->xdrect.yf +=  dr->xdrect.yprev;
dr->xdcore.x +=  dr->xdrect.xprev;
dr->xdcore.y += dr->xdrect.yprev;

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
XdRectDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdRectDraget)dra;
/***  eliminaz rett. selez zoomati
if (z >= 0.5)
	delta *= z;
*/
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

draw_rect(dr,dr->xdcore.gc,dr->xdcore.filled,
                        (int)(z * dr->xdcore.x),(int)(z * dr->xdcore.y),
                        (int)(z * dr->xdrect.xf), (int)(z * dr->xdrect.yf));
/*
 Se l'oggetto e' nello stato selezionato disegna i rettangolini
 di selezione
*/
if(dr->xdcore.selected)
	{
	XFillRectangle(display,XtWindow(dr->xdcore.wid),
			class->xdcore_class.gcsel,
			(int)(z*dr->xdcore.x-(delta/2)),
			(int)(z*dr->xdcore.y-(delta/2)),
				delta,delta);
	XFillRectangle(display,XtWindow(dr->xdcore.wid),
			class->xdcore_class.gcsel,
                        (int)(z*dr->xdrect.xf-(delta/2)),
			(int)(z*dr->xdrect.yf-(delta/2)),
                                delta,delta);
	XFillRectangle(display,XtWindow(dr->xdcore.wid),
			class->xdcore_class.gcsel,
                        (int)(z*dr->xdrect.xf-(delta/2)),
			(int)(z*dr->xdcore.y-(delta/2)),
                                delta,delta);
	XFillRectangle(display,XtWindow(dr->xdcore.wid),
			class->xdcore_class.gcsel,
                        (int)(z*dr->xdcore.x-(delta/2)),
			(int)(z*dr->xdrect.yf-(delta/2)),
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
XdRectDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdRectDraget)dra;
draw_rect(dr,dr->xdcore.gc,dr->xdcore.filled,
                        (int)(z * dr->xdcore.x),(int)(z * dr->xdcore.y),
                        (int)(z * dr->xdrect.xf), (int)(z * dr->xdrect.yf));
}
#endif

static Boolean FirstPoint(dra,ev)
Draget dra;
XEvent *ev;
{
XdRectDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdRectDraget)dra;
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
XdRectDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdRectDraget)dra;
z = class->xdcore_class.zoom;
/*
 memorizza i punti finali
*/
dr->xdrect.xf = ev->xbutton.x / z;
dr->xdrect.yf = ev->xbutton.y /z;
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
if(dr->xdrect.xf == dr->xdcore.x && dr->xdrect.yf == dr->xdcore.y)
        return(False);
else
        return(True);

}

static Boolean FirstDraw(dra,ev)
Draget dra;
XEvent *ev;
{
Display *display;
XdRectDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdRectDraget)dra;
display=XtDisplay(dr->xdcore.wid);
if(dr->xdcore.is_first == False)
	draw_rect(dr,class->xdcore_class.gcxor,False,
			(int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
			(int)(z*dr->xdrect.xprev), (int)(z*dr->xdrect.yprev));
else
	dr->xdcore.is_first = False;

dr->xdrect.xprev= ev->xmotion.x / z;
dr->xdrect.yprev= ev->xmotion.y / z;

draw_rect(dr,class->xdcore_class.gcxor,False,
                        (int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
                        (int)(z*dr->xdrect.xprev), (int)(z*dr->xdrect.yprev));
XFlush(display);
}


static void Clear(dra)
Draget dra;
{
static XEvent eve_exp;
XmDrawingAreaCallbackStruct str;
Display *display;
float z;
XdRectDraget dr;
int xmin,xmax,ymin,ymax;
unsigned int width,height;
int delta=3;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdRectDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/* 
 Determina l'area su cui effettuare il clear
*/
if(dr->xdcore.x < dr->xdrect.xf)
	{
	xmin = dr->xdcore.x;
	xmax = dr->xdrect.xf;
	}
else
	{
	xmin = dr->xdrect.xf;
	xmax = dr->xdcore.x;
	}

if(dr->xdcore.y < dr->xdrect.yf)
	{
	ymin = dr->xdcore.y;
	ymax = dr->xdrect.yf;
	}
else
	{
	ymin = dr->xdrect.yf;
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
			(unsigned int)(z * width),(unsigned int)(z * height),True);

}


static Boolean Read(dra,xdgc,fp)
Draget dra;
XdGC *xdgc;
FILE *fp;
{
int x,y,xf,yf;
DragetClass class;
XdRectDraget dr;
dr=(XdRectDraget)dra;
class=XdClass(dra);
fscanf(fp,"%d %d %d %d",&x,&y,&xf,&yf);
dr->xdcore.x=x;
dr->xdcore.y=y;
dr->xdrect.xf=xf;
dr->xdrect.yf=yf;
dr->xdcore.filled=xdgc->filled;
dr->xdcore.managed= True; /* l'oggetto e' completo */
class->xdcore_class.crea_regions(dr);
/*
 forza il ridisegno dell'oggetto finale
*/
/*
class->xdcore_class.expose(dr,NULL);
*/
return(True);
}


static void Copy(dra,dra_dest)
Draget dra;
Draget dra_dest;
{
DragetClass class;
XdRectDraget dr;
XdRectDraget dr_dest;
/* printf("\n richiamata copia draget"); */
dr=(XdRectDraget)dra;
dr_dest=(XdRectDraget)dra_dest;
class=XdClass(dra);
dr_dest->xdcore.x=dr->xdcore.x;
dr_dest->xdcore.y=dr->xdcore.y;
dr_dest->xdrect.xf=dr->xdrect.xf;
dr_dest->xdrect.yf=dr->xdrect.yf;
dr_dest->xdcore.filled=dr->xdcore.filled;
dr_dest->xdcore.managed= True; /* l'oggetto e' completo */
dr_dest->xdcore.selected= True; /* setta l'oggetto a selezionato */
class->xdcore_class.crea_regions(dr_dest);
/*
 forza il ridisegno dell'oggetto finale
*/
/*
class->xdcore_class.expose(dr,NULL);
*/
}



static void Write(Draget dra, FILE *fp)
{
XdRectDraget dr;
dr=(XdRectDraget)dra;
fprintf(fp,"rect %d %d %d %d\n",dr->xdcore.x,dr->xdcore.y,
                dr->xdrect.xf,dr->xdrect.yf);
}

static void GetSize(dra,xmin,ymin,xmax,ymax)
Draget dra;
int *xmin,*ymin,*xmax,*ymax;
{
XdRectDraget dr;
XGCValues values;
int offset;

dr=(XdRectDraget)dra;
*xmin=(dr->xdcore.x < dr->xdrect.xf) ? dr->xdcore.x : dr->xdrect.xf;
*ymin=(dr->xdcore.y < dr->xdrect.yf) ? dr->xdcore.y : dr->xdrect.yf;

*xmax=(dr->xdcore.x > dr->xdrect.xf) ? dr->xdcore.x : dr->xdrect.xf;
*ymax=(dr->xdcore.y > dr->xdrect.yf) ? dr->xdcore.y : dr->xdrect.yf;

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

}

static void Modify(dra,dx,dy,dw,dh,ev)
Draget dra;
int dx,dy,dw,dh;
XEvent *ev;
{
XdRectDraget dr;
GROUP_EV *gr_ev; /* notifica un evento di ridimensionamento del gruppo
                   al singolo componente appartenente al gruppo
                */
DragetClass class;
dr=(XdRectDraget)dra;
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
	dr->xdrect.xf+=dx;
	dr->xdrect.yf+=dy;
	}
else   /* evento di resize di gruppo presente */
	{
/* 
  le coordinate vengono moltiplicate per il fattore di ridimensionamento
  del gruppo contenitore
*/
	dr->xdcore.x = gr_ev->xfix+gr_ev->fatt_x * (dr->xdcore.x - gr_ev->xfix);
        dr->xdcore.y = gr_ev->yfix+gr_ev->fatt_y * (dr->xdcore.y - gr_ev->yfix);
	dr->xdrect.xf = gr_ev->xfix+
			gr_ev->fatt_x * (dr->xdrect.xf- gr_ev->xfix);
	dr->xdrect.yf = gr_ev->yfix+
		 	gr_ev->fatt_y * (dr->xdrect.yf- gr_ev->yfix);
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
Draget XdCreateRectDraget(wid, gc, gc_bg)
Widget wid; /* widget su cui effettuare il disegno */
GC gc;
GC gc_bg;
{
Draget dr;
DragetClass class;
class=(DragetClass)&xdRectClassRec;
return(XdCreateDraget(wid,class,gc,gc_bg));
}


static void CreaRegions(dr)
XdRectDraget dr;
{
float z;
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

dr->xdcore.select_region= RegionRectIntorno(dr->xdcore.x,
						dr->xdcore.y,
						dr->xdrect.xf,
						dr->xdrect.yf,
						z);
/*
 Crea la regione di move
*/
dr->xdcore.num_move_regions=1;
dr->xdcore.move_regions=(Region *)XtCalloc(dr->xdcore.num_move_regions,sizeof(Region));
dr->xdcore.move_regions[0]=  RegionRectIntorno(dr->xdcore.x,
                                                dr->xdcore.y,
                                                dr->xdrect.xf,
                                                dr->xdrect.yf,
                                                z);
 
/*
 Crea le regioni di resize
*/
dr->xdcore.num_resize_regions=4;
dr->xdcore.resize_regions=(Region *)XtCalloc(dr->xdcore.num_resize_regions,sizeof(Region));
dr->xdcore.resize_regions[0]=RegionIntorno(dr->xdcore.x,dr->xdcore.y,z);
dr->xdcore.resize_regions[1]=RegionIntorno(dr->xdrect.xf,dr->xdcore.y,z);
dr->xdcore.resize_regions[2]=RegionIntorno(dr->xdrect.xf,dr->xdrect.yf,z);
dr->xdcore.resize_regions[3]=RegionIntorno(dr->xdcore.x,dr->xdrect.yf,z);
}


static void draw_rect(dr, drawGC,filled, x1, y1, x2, y2)
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
		XFillRectangle(XlDisplay(wid), XlWindow(wid), gc_bg,
		 	topx, topy,
                	width, height);
        XDrawRectangle(XlDisplay(wid), XlWindow(wid), drawGC, topx, topy,
                width, height);
}

