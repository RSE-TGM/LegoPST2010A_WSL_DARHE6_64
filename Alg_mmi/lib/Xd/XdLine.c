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
   modulo XdLine.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdLine.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XdLine.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*
 XdLine - oggetto linea 
*/
#include <Xm/Xm.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>

#include <Xd/XdCoreP.h>
#include <Xd/XdLineP.h>
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
 Inizializzazione del class record
*/
XdLineClassRec xdLineClassRec = {
	{ /* xdcore fields */
	  /* initialized */     False,
	  /* class_name */ 	"XdLine",
	  /* superclass */      (DragetClass)&xdCoreClassRec,
	  /* gcxor      */	NULL,
	  /* gcsel      */	NULL,
	  /* zoom       */      1.0,
	  /* draget size */	sizeof(XdLineRec),
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
	  /* copy       */	Copy,
#ifdef XPRINTER_USED
	  /* print      */      Print
#endif
	},
	{
	 /* dummy       */ 0
	}
};

DragetClass xdLineDragetClass = (DragetClass) &xdLineClassRec;

/*
 Metodi
*/

static void Initialize(dra)
Draget dra;
{
XdLineDraget dr;
Widget wid;
}

static void Destroy(dra)
Draget dra;
{
XdLineDraget dr;
dr=(XdLineDraget)dra;
dr->xdcore.managed= False; /* impedisce che venga effettuato
			il redraw su oggetto in cancellazione */
}

/*
  Ridimensionamento della linea tramite movimento del
  mouse
*/
static Boolean Resize(dra,ev)
Draget dra;
XEvent *ev;
{
int xfix,yfix;
Display *display;
XdLineDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
dr=(XdLineDraget)dra;
z = class->xdcore_class.zoom;
display=XtDisplay(dr->xdcore.wid);
/*
 A seconda del numero della regione di resize selezionata determina
 quale e' il punto che deve rimanere fissato
*/
if(dr->xdcore.num_resize==1)
	{
	xfix=dr->xdcore.x;
	yfix=dr->xdcore.y;
	}
else
	{
	xfix=dr->xdline.xf;
	yfix=dr->xdline.yf;
	}

if(dr->xdcore.is_first == False)
	XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z * xfix),(int)(z * yfix),
			(int)(z * dr->xdline.xprev),
			(int)( z * dr->xdline.yprev));
else
	{
	dr->xdcore.is_first = False;
	}

dr->xdline.xprev= ev->xmotion.x /z;
dr->xdline.yprev= ev->xmotion.y /z;

XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
                        (int)(z * xfix),(int)(z * yfix),
                        (int)(z * dr->xdline.xprev),
			(int)(z * dr->xdline.yprev));
XFlush(display);
}

static Boolean EndResize(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
XdLineDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdLineDraget)dra;
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
if(dr->xdcore.num_resize==1)
	{
	dr->xdline.xf = ev->xbutton.x / z;
	dr->xdline.yf = ev->xbutton.y / z;
	}
else
	{
	dr->xdcore.x = ev->xbutton.x / z;
	dr->xdcore.y =  ev->xbutton.y / z;
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
float fx,fy;
int xfix,yfix;
Display *display;
XdLineDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdLineDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/*
 il delta di spostamento viene memorizzato rispettivamente in:
	dr->xdline.xprev e
	dr->xdline.yprev
*/
if(dr->xdcore.is_first == False)
	XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
		(int)(z*(dr->xdcore.x+dr->xdline.xprev)),
		(int)(z*(dr->xdcore.y+dr->xdline.yprev)),
		(int)(z*(dr->xdline.xf+dr->xdline.xprev)),
		(int)(z*(dr->xdline.yf+dr->xdline.yprev)));
else
	{
	dr->xdcore.is_first = False;
	x_click = ev->xmotion.x / z;
	y_click = ev->xmotion.y / z;
	}

fx = (float)((float)ev->xmotion.x / z) - x_click;
fy = (float) ((float)ev->xmotion.y / z) - y_click;

if (fx > 0 && fx < 1)
	dr->xdline.xprev= 1; 
else if (fx > -1 && fx < 0)
	 dr->xdline.xprev= -1;
else dr->xdline.xprev= fx;
if (fy > 0 && fy < 1)
        dr->xdline.yprev= 1;
else if (fy > -1 && fy < 0)
         dr->xdline.yprev= -1;
else dr->xdline.yprev= fy;


/*
dr->xdline.xprev= (float)(ev->xmotion.x / z) - x_click;
dr->xdline.yprev= (float) (ev->xmotion.y / z) - y_click;
*/

XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
		(int)(z*(dr->xdcore.x+dr->xdline.xprev)),
		(int)(z*(dr->xdcore.y+dr->xdline.yprev)),
		(int)(z*(dr->xdline.xf+dr->xdline.xprev)),
		(int)(z*(dr->xdline.yf+dr->xdline.yprev)));

XFlush(display);
}


static Boolean EndMove(dra,ev)
Draget dra;
XEvent *ev;
{
XdLineDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdLineDraget)dra;
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
dr->xdline.xf += dr->xdline.xprev;
dr->xdline.yf +=  dr->xdline.yprev;
dr->xdcore.x +=  dr->xdline.xprev;
dr->xdcore.y += dr->xdline.yprev;

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
XdLineDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdLineDraget)dra;
/* eliminaz rett. selez zoomati
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
	{
	region=RegionClip(ev);
	XSetRegion(display,dr->xdcore.gc,region);
	XSetRegion(display,class->xdcore_class.gcsel,region);
	}
else
	{
	XSetRegion(display,dr->xdcore.gc,dr->xdcore.select_region);
	XSetRegion(display,class->xdcore_class.gcsel,dr->xdcore.select_region);
	}
/****** fine clipping **********/

XDrawLine(display,XtWindow(dr->xdcore.wid),dr->xdcore.gc,
                        (int)(z * dr->xdcore.x),(int)(z * dr->xdcore.y),
                        (int)(z * dr->xdline.xf), (int)(z * dr->xdline.yf));
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
                        (int)(z*dr->xdline.xf-(delta/2)),
			(int)(z*dr->xdline.yf-(delta/2)),
                                delta,delta);
	}
if(ev!=NULL) 
	XDestroyRegion(region);
}

#ifdef XPRINTER_USED
static void Print(dra,flag)
Draget dra;
Boolean flag;
{
float z;
XdLineDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdLineDraget)dra;
XDrawLine(XlDisplay(dr->xdcore.wid),XlWindow(dr->xdcore.wid),dr->xdcore.gc,
                        (int)(z * dr->xdcore.x),(int)(z * dr->xdcore.y),
                        (int)(z * dr->xdline.xf), (int)(z * dr->xdline.yf));
}
#endif

static Boolean FirstPoint(dra,ev)
Draget dra;
XEvent *ev;
{
XdLineDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdLineDraget)dra;
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
XdLineDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdLineDraget)dra;
z = class->xdcore_class.zoom;
/*
 memorizza i punti finali
*/
dr->xdline.xf = ev->xbutton.x / z;
dr->xdline.yf = ev->xbutton.y /z;
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
if(dr->xdline.xf == dr->xdcore.x && dr->xdline.yf == dr->xdcore.y)
	return(False);
else
	return(True);
}

static Boolean FirstDraw(dra,ev)
Draget dra;
XEvent *ev;
{
Display *display;
XdLineDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdLineDraget)dra;
display=XtDisplay(dr->xdcore.wid);
if(dr->xdcore.is_first == False)
	XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
			(int)(z*dr->xdline.xprev), (int)(z*dr->xdline.yprev));
else
	dr->xdcore.is_first = False;

dr->xdline.xprev= ev->xmotion.x / z;
dr->xdline.yprev= ev->xmotion.y / z;

XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
                        (int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
                        (int)(z*dr->xdline.xprev), (int)(z*dr->xdline.yprev));
XFlush(display);
}


static void Clear(dra)
Draget dra;
{
int width, height, topx, topy;
int delta=3;
Display *display;
float z;
XdLineDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdLineDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/* 
 Determina l'area su cui effettuare il clear
*/
topx=(dr->xdcore.x < dr->xdline.xf) ? dr->xdcore.x : dr->xdline.xf;
topy=(dr->xdcore.y < dr->xdline.yf) ? dr->xdcore.y : dr->xdline.yf;
topx-=delta;
topy-=delta;

width= (abs(dr->xdcore.x-dr->xdline.xf))+2*delta;
height= (abs(dr->xdcore.y-dr->xdline.yf))+2*delta;

/* patch per server di ucin14 **/
XDrawLine(display, XtWindow(dr->xdcore.wid), class->xdcore_class.gcxor, 
	(int)(z*topx), (int)(z*topy),
                (int) (z*topx), (int)(z*topy));
/* fine patch ***/

XClearArea(display,XtWindow(dr->xdcore.wid),
                        (int)(z * (topx)),
                        (int)(z * (topy)),
                        (unsigned int)(z * width),
			(unsigned int)(z * height),True);

}


static Boolean Read(dra,xdgc,fp)
Draget dra;
XdGC *xdgc;
FILE *fp;
{
XdLineDraget dr;
int x,y,xf,yf;
DragetClass class;
dr=(XdLineDraget)dra;
class=XdClass(dra);
fscanf(fp,"%d %d %d %d",&x,&y,&xf,&yf);
dr->xdcore.x=x;
dr->xdcore.y=y;
dr->xdline.xf=xf;
dr->xdline.yf=yf;
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
XdLineDraget dr;
XdLineDraget dr_dest;
int x,y,xf,yf;
DragetClass class;
dr=(XdLineDraget)dra;
dr_dest=(XdLineDraget)dra_dest;
class=XdClass(dra);
dr_dest->xdcore.x=dr->xdcore.x;
dr_dest->xdcore.y=dr->xdcore.y;
dr_dest->xdline.xf=dr->xdline.xf;
dr_dest->xdline.yf=dr->xdline.yf;
dr_dest->xdcore.filled=dr->xdcore.filled;
dr_dest->xdcore.managed= True; /* l'oggetto e' completo */
dr_dest->xdcore.selected= True; /* l'oggetto e' settato selezionato */
class->xdcore_class.crea_regions(dr_dest);
}

static void Write(dra,fp)
Draget dra;
FILE *fp;
{
XdLineDraget dr;
dr=(XdLineDraget)dra;
fprintf(fp,"line %d %d %d %d\n",dr->xdcore.x,dr->xdcore.y,
		dr->xdline.xf,dr->xdline.yf);
}

static void GetSize(dra,xmin,ymin,xmax,ymax)
Draget dra;
int *xmin,*ymin,*xmax,*ymax;
{
XdLineDraget dr;
XGCValues values;
int offset;
dr=(XdLineDraget)dra;
*xmin=(dr->xdcore.x < dr->xdline.xf) ? dr->xdcore.x : dr->xdline.xf;
*ymin=(dr->xdcore.y < dr->xdline.yf) ? dr->xdcore.y : dr->xdline.yf;

*xmax=(dr->xdcore.x > dr->xdline.xf) ? dr->xdcore.x : dr->xdline.xf;
*ymax=(dr->xdcore.y > dr->xdline.yf) ? dr->xdcore.y : dr->xdline.yf;
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
XdLineDraget dr;
GROUP_EV *gr_ev; /* notifica un evento di ridimensionamento del gruppo
                   al singolo componente appartenente al gruppo
                  */
DragetClass class;
dr=(XdLineDraget)dra;
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
	dr->xdline.xf+=dx;
	dr->xdline.yf+=dy;
	}
else   /* evento di resize di gruppo presente */
        {
/*
  le coordinate vengono moltiplicate per il fattore di ridimensionamento
  del gruppo contenitore
*/
        dr->xdcore.x = gr_ev->xfix+gr_ev->fatt_x * (dr->xdcore.x - gr_ev->xfix);
        dr->xdcore.y = gr_ev->yfix+gr_ev->fatt_y * (dr->xdcore.y - gr_ev->yfix);
        dr->xdline.xf = gr_ev->xfix+
                        gr_ev->fatt_x * (dr->xdline.xf- gr_ev->xfix);
        dr->xdline.yf = gr_ev->yfix+
                        gr_ev->fatt_y * (dr->xdline.yf- gr_ev->yfix);
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
 Routine di creazione (generalizzabile e spostabile in DrUtil.c)
*/
Draget XdCreateLineDraget(wid, gc, gc_bg)
Widget wid; /* widget su cui effettuare il disegno */
GC gc;
GC gc_bg;
{
Draget dr;
DragetClass class;
class=(DragetClass)&xdLineClassRec;
return(XdCreateDraget(wid,class,gc,gc_bg));
}



static void CreaRegions(dr)
XdLineDraget dr;
{
float z;
DragetClass class;
int iret;
Region select_region;
short delta=4;
class=XdClass(dr);
z = class->xdcore_class.zoom;
/*
if(z>= 0.5) delta *= z;
*/
/*
 Crea la regione di move
*/
dr->xdcore.num_move_regions=1;
dr->xdcore.move_regions=(Region *)XtCalloc(dr->xdcore.num_move_regions,sizeof(Region));
dr->xdcore.move_regions[0]= RegionLineIntorno(dr->xdcore.x,
                                                dr->xdcore.y,
                                                dr->xdline.xf,
                                                dr->xdline.yf,
                                                z);

/*
 Crea le regioni di resize
*/
dr->xdcore.num_resize_regions=2;
dr->xdcore.resize_regions=(Region *)XtCalloc(dr->xdcore.num_resize_regions,sizeof(Region));
dr->xdcore.resize_regions[0]=RegionIntorno(dr->xdcore.x,dr->xdcore.y,z);
dr->xdcore.resize_regions[1]=RegionIntorno(dr->xdline.xf,dr->xdline.yf,z);

/* 
 Crea la regione di selezione come unione della regione di move e di quelle 
 di resize
*/
select_region=XCreateRegion();
dr->xdcore.select_region=XCreateRegion();
XUnionRegion(dr->xdcore.resize_regions[0],
		dr->xdcore.resize_regions[1],
		select_region);
XUnionRegion(dr->xdcore.move_regions[0],
		select_region,
		dr->xdcore.select_region);
XDestroyRegion(select_region);
}



