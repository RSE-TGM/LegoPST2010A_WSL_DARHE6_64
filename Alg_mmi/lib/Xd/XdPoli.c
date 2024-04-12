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
   modulo XdPoli.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdPoli.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XdPoli.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*
 XdPoli - oggetto poligono 
*/
#include <Xm/Xm.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>

#include <Xd/XdCoreP.h>
#include <Xd/XdPoliP.h>
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
XdPoliClassRec xdPoliClassRec = {
	{ /* xdcore fields */
	  /* initialized */     False,
	  /* class_name */ 	"XdPoli",
	  /* superclass */      (DragetClass)&xdCoreClassRec,
	  /* gcxor      */	NULL,
	  /* gcsel      */	NULL,
	  /* zoom       */      1.0,
	  /* draget size */	sizeof(XdPoliRec),
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

DragetClass xdPoliDragetClass = (DragetClass) &xdPoliClassRec;

/*
 Metodi
*/

static void Initialize(dra)
Draget dra;
{
XdPoliDraget dr;
Widget wid;
}

static void Destroy(dra)
Draget dra;
{
XdPoliDraget dr;
dr=(XdPoliDraget)dra;
dr->xdcore.managed= False; /* impedisce che venga effettuato
			il redraw su oggetto in cancellazione */
XtFree(dr->xdpoli.points);
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
int npunto,npunto_prec,npunto_succ;
Display *display;
XdPoliDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
dr=(XdPoliDraget)dra;
z = class->xdcore_class.zoom;
display=XtDisplay(dr->xdcore.wid);
/*
 A seconda del numero della regione di resize selezionata determina
 quale e' il punto che deve rimanere fissato
*/
npunto=dr->xdcore.num_resize;
npunto_prec= npunto-1;
npunto_succ= npunto+1;
if(npunto_prec<0) npunto_prec= dr->xdpoli.npoints-1;
if(npunto_succ>=dr->xdpoli.npoints) npunto_succ=0;

if(dr->xdcore.is_first == False)
	{
	XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z * dr->xdpoli.points[npunto_prec].x),
			(int)(z * dr->xdpoli.points[npunto_prec].y),
			(int)(z * dr->xdpoli.xprev),
			(int)( z * dr->xdpoli.yprev));
	XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z * dr->xdpoli.points[npunto_succ].x),
			(int)(z * dr->xdpoli.points[npunto_succ].y),
			(int)(z * dr->xdpoli.xprev),
			(int)( z * dr->xdpoli.yprev));
	}
else
	{
	dr->xdcore.is_first = False;
	}

dr->xdpoli.xprev= ev->xmotion.x /z;
dr->xdpoli.yprev= ev->xmotion.y /z;

XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z * dr->xdpoli.points[npunto_prec].x),
			(int)(z * dr->xdpoli.points[npunto_prec].y),
			(int)(z * dr->xdpoli.xprev),
			(int)( z * dr->xdpoli.yprev));
XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z * dr->xdpoli.points[npunto_succ].x),
			(int)(z * dr->xdpoli.points[npunto_succ].y),
			(int)(z * dr->xdpoli.xprev),
			(int)( z * dr->xdpoli.yprev));
XFlush(display);
}

static Boolean EndResize(dra,ev)
Draget dra;
XEvent *ev;
{
int npunto;
float z;
XdPoliDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdPoliDraget)dra;
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
 memorizza il punto spostato
*/
npunto=dr->xdcore.num_resize;
dr->xdpoli.points[npunto].x = ev->xbutton.x / z;
dr->xdpoli.points[npunto].y =  ev->xbutton.y / z;
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
XdPoliDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdPoliDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/*
 il delta di spostamento viene memorizzato rispettivamente in:
	dr->xdpoli.xprev e
	dr->xdpoli.yprev
*/
if(dr->xdcore.is_first == False)
	draw_poli_off(dr,class->xdcore_class.gcxor,dr->xdpoli.xprev,
					dr->xdpoli.yprev);
else
	{
	dr->xdcore.is_first = False;
	x_click = ev->xmotion.x / z;
	y_click = ev->xmotion.y / z;
	}

dr->xdpoli.xprev= ev->xmotion.x / z - x_click;
dr->xdpoli.yprev= ev->xmotion.y / z - y_click;

draw_poli_off(dr,class->xdcore_class.gcxor,dr->xdpoli.xprev,
                                        dr->xdpoli.yprev);

XFlush(display);
}


static Boolean EndMove(dra,ev)
Draget dra;
XEvent *ev;
{
int i;
XdPoliDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdPoliDraget)dra;
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
for(i=0; i< dr->xdpoli.npoints; i++)
	{
	dr->xdpoli.points[i].x+= dr->xdpoli.xprev;
	dr->xdpoli.points[i].y+= dr->xdpoli.yprev;
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


static void Redraw(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
int i;
Region region;
Display *display;
unsigned int delta=4;
XdPoliDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdPoliDraget)dra;
/*
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
draw_poli(dr);

/*
 Se l'oggetto e' nello stato selezionato disegna i rettangolini
 di selezione
*/
if(dr->xdcore.selected)
	{
	for(i=0; i<dr->xdpoli.npoints; i++)
		{
		XFillRectangle(display,XtWindow(dr->xdcore.wid),
			class->xdcore_class.gcsel,
			(int)(z*dr->xdpoli.points[i].x-(delta/2)),
			(int)(z*dr->xdpoli.points[i].y-(delta/2)),
				delta,delta);
		}
	}
XDestroyRegion(region);
}

#ifdef XPRINTER_USED
static void Print(dra,flag)
Draget dra;
Boolean flag;
{
float z;
XdPoliDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdPoliDraget)dra;
draw_poli(dr);
}
#endif

static Boolean FirstPoint(dra,ev)
Draget dra;
XEvent *ev;
{
XdPoliDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdPoliDraget)dra;
dr->xdcore.x= ev->xbutton.x / z;
dr->xdcore.y= ev->xbutton.y / z;
dr->xdcore.managed= False; /* indica che l'oggetto e' in fase di 
				costruzione: impedisce che venga effettuato
				il redraw su oggetto non completo */
dr->xdcore.is_first= True;
/* 
 se il punto e' successivo al primo esamina che non sia coincidente al
 punto precedente ( in tal caso non memorizza il nuovo punto)
*/
if(dr->xdpoli.npoints && 
        dr->xdpoli.points[dr->xdpoli.npoints-1].x == dr->xdcore.x &&
	dr->xdpoli.points[dr->xdpoli.npoints-1].y == dr->xdcore.y)
	{
	printf("\n coincidenti !!\n");
	return(False);
	}

dr->xdpoli.npoints++;
dr->xdpoli.points=(XPoint *)XtRealloc(dr->xdpoli.points, 
			dr->xdpoli.npoints*sizeof(XPoint));
/*
 Inserisce nel vettore dei punti quello appena allocato
*/
dr->xdpoli.points[dr->xdpoli.npoints-1].x = dr->xdcore.x;
dr->xdpoli.points[dr->xdpoli.npoints-1].y = dr->xdcore.y;
/*
 esamina se l'evento corrispondente e' di movimento del
 mouse: in questo caso significa che si sta disegnando a
 mano libera
*/
if(ev->xmotion.type == MotionNotify && ev->xmotion.state== Button1Mask)
	{
	XDrawLine(XtDisplay(dr->xdcore.wid),
			XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z*dr->xdpoli.points[dr->xdpoli.npoints-2].x),
			(int)(z*dr->xdpoli.points[dr->xdpoli.npoints-2].y),
			(int)(z*dr->xdpoli.points[dr->xdpoli.npoints-1].x),
			(int)(z*dr->xdpoli.points[dr->xdpoli.npoints-1].y));
	}
return(True);
}

static Boolean LastPoint(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
XdPoliDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdPoliDraget)dra;
z = class->xdcore_class.zoom;
/*
 memorizza i punti finali
*/
dr->xdpoli.xf = ev->xbutton.x / z;
dr->xdpoli.yf = ev->xbutton.y /z;

if(dr->xdpoli.npoints > 1 &&
        dr->xdpoli.points[dr->xdpoli.npoints-1].x == dr->xdpoli.xf &&
        dr->xdpoli.points[dr->xdpoli.npoints-1].y == dr->xdpoli.yf)
        {
        printf("\n coincidenti !!\n");
        }
else  /* inserisce l'ultimo punto */
	{
	dr->xdpoli.npoints++;
	dr->xdpoli.points=(XPoint *)XtRealloc(dr->xdpoli.points, 
			dr->xdpoli.npoints*sizeof(XPoint));
/*
 Inserisce nel vettore dei punti quello appena allocato
*/
	dr->xdpoli.points[dr->xdpoli.npoints-1].x = dr->xdpoli.xf;
	dr->xdpoli.points[dr->xdpoli.npoints-1].y = dr->xdpoli.yf;
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
if(dr->xdpoli.npoints == 2 && dr->xdpoli.points[0].x==dr->xdpoli.points[1].x
			   && dr->xdpoli.points[0].y==dr->xdpoli.points[1].y )
	return(False);
else
        return(True);
}

static Boolean FirstDraw(dra,ev)
Draget dra;
XEvent *ev;
{
Display *display;
XdPoliDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdPoliDraget)dra;
display=XtDisplay(dr->xdcore.wid);
if(dr->xdcore.is_first == False)
	XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
			(int)(z*dr->xdpoli.xprev), (int)(z*dr->xdpoli.yprev));
else
	dr->xdcore.is_first = False;

dr->xdpoli.xprev= ev->xmotion.x / z;
dr->xdpoli.yprev= ev->xmotion.y / z;

XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
                        (int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
                        (int)(z*dr->xdpoli.xprev), (int)(z*dr->xdpoli.yprev));
XFlush(display);
}


static void Clear(dra)
Draget dra;
{
XRectangle rect;
int width, height, topx, topy;
int delta=3;
Display *display;
float z;
XdPoliDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdPoliDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/* 
 Determina l'area su cui effettuare il clear
*/
XClipBox(dr->xdcore.select_region,&rect);
/*
topx=(dr->xdcore.x < dr->xdpoli.xf) ? dr->xdcore.x : dr->xdpoli.xf;
topy=(dr->xdcore.y < dr->xdpoli.yf) ? dr->xdcore.y : dr->xdpoli.yf;
topx-=delta;
topy-=delta;

width= (abs(dr->xdcore.x-dr->xdpoli.xf))+2*delta;
height= (abs(dr->xdcore.y-dr->xdpoli.yf))+2*delta;
XDrawLine(display, XtWindow(dr->xdcore.wid), class->xdcore_class.gcxor, 
	(int)(z*topx), (int)(z*topy),
                (int) (z*topx), (int)(z*topy));

XClearArea(display,XtWindow(dr->xdcore.wid),
                        (int)(z * (topx)),
                        (int)(z * (topy)),
                        (unsigned int)(z * width),
			(unsigned int)(z * height),True);
*/
topx=rect.x;
topy=rect.y;
width=rect.width;
height=rect.height;
/* patch per ucin14 */
XDrawLine(display, XtWindow(dr->xdcore.wid), class->xdcore_class.gcxor, 
	(int)(topx), (int)(topy),
                (int) (topx), (int)(topy));
/* fine patch */
XClearArea(display,XtWindow(dr->xdcore.wid),
                        (int)(topx),
                        (int)(topy),
                        (unsigned int)(width),
			(unsigned int)(height),True);
}


static Boolean Read(dra,xdgc,fp)
Draget dra;
XdGC *xdgc;
FILE *fp;
{
XdPoliDraget dr;
int x,y,i;
DragetClass class;
dr=(XdPoliDraget)dra;
class=XdClass(dra);
fscanf(fp,"%d",&dr->xdpoli.npoints);
dr->xdpoli.points=(XPoint *)XtCalloc(dr->xdpoli.npoints, 
					sizeof(XPoint));
for(i=0;i<dr->xdpoli.npoints; i++)
	{
	fscanf(fp," %d %d",&x,&y);
	dr->xdpoli.points[i].x=x;
	dr->xdpoli.points[i].y=y;
	}
dr->xdcore.filled=xdgc->filled;
dr->xdcore.managed= True; /* l'oggetto e' completo */
class->xdcore_class.crea_regions(dr);
return(True);
}


static void Copy(dra,dra_dest)
Draget dra;
Draget dra_dest;
{
XdPoliDraget dr;
XdPoliDraget dr_dest;
int i;
DragetClass class;
dr=(XdPoliDraget)dra;
dr_dest=(XdPoliDraget)dra_dest;
class=XdClass(dra);
dr_dest->xdpoli.npoints=dr->xdpoli.npoints;
dr_dest->xdpoli.points=(XPoint *)XtCalloc(dr_dest->xdpoli.npoints, 
					sizeof(XPoint));
for(i=0;i<dr_dest->xdpoli.npoints; i++)
	{
	dr_dest->xdpoli.points[i].x=dr->xdpoli.points[i].x;
	dr_dest->xdpoli.points[i].y=dr->xdpoli.points[i].y;
	}
dr_dest->xdcore.filled=dr->xdcore.filled;
dr_dest->xdcore.managed= True; /* l'oggetto e' completo */
dr_dest->xdcore.selected= True; /* l'oggetto e' settato selezionato */
class->xdcore_class.crea_regions(dr_dest);
}

static void Write(dra,fp)
Draget dra;
FILE *fp;
{
int i;
XdPoliDraget dr;
dr=(XdPoliDraget)dra;
fprintf(fp,"poli %d",dr->xdpoli.npoints);
for(i=0;i<dr->xdpoli.npoints; i++)
	fprintf(fp," %d %d",dr->xdpoli.points[i].x,dr->xdpoli.points[i].y);
fprintf(fp,"\n");
}

static void GetSize(dra,xmin,ymin,xmax,ymax)
Draget dra;
int *xmin,*ymin,*xmax,*ymax;
{
XdPoliDraget dr;
XGCValues values;
int offset;
int i;
dr=(XdPoliDraget)dra;
*xmin=dr->xdpoli.points[0].x;
*ymin=dr->xdpoli.points[0].y;
*xmax=dr->xdpoli.points[0].x;
*ymax=dr->xdpoli.points[0].y;
for(i=1;i<(dr->xdpoli.npoints); i++)
	{
	*xmin=(*xmin < dr->xdpoli.points[i].x) ? 
		*xmin : dr->xdpoli.points[i].x;
	*ymin=(*ymin < dr->xdpoli.points[i].y) ? 
		*ymin : dr->xdpoli.points[i].y;
	*xmax=(*xmax > dr->xdpoli.points[i].x) ?
                *xmax : dr->xdpoli.points[i].x;
        *ymax=(*ymax > dr->xdpoli.points[i].y) ?
                *ymax : dr->xdpoli.points[i].y;
	}
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
XdPoliDraget dr;
GROUP_EV *gr_ev; /* notifica un evento di ridimensionamento del gruppo
                   al singolo componente appartenente al gruppo
                */
DragetClass class;
int i;
dr=(XdPoliDraget)dra;
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
	for(i=0;i<(dr->xdpoli.npoints); i++)
        	{
		dr->xdpoli.points[i].x+=dx;
		dr->xdpoli.points[i].y+=dy;
		}
	}
else
	{
	for(i=0;i<(dr->xdpoli.npoints); i++)
        	{
		dr->xdpoli.points[i].x = gr_ev->xfix+
			gr_ev->fatt_x * (dr->xdpoli.points[i].x - gr_ev->xfix);
		dr->xdpoli.points[i].y = gr_ev->yfix+
			gr_ev->fatt_y * (dr->xdpoli.points[i].y - gr_ev->yfix);
		}
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
Draget XdCreatePoliDraget(wid, gc, gc_bg)
Widget wid; /* widget su cui effettuare il disegno */
GC gc;
GC gc_bg;
{
Draget dr;
DragetClass class;
class=(DragetClass)&xdPoliClassRec;
return(XdCreateDraget(wid,class,gc,gc_bg));
}



static void CreaRegions(dr)
XdPoliDraget dr;
{
float z;
DragetClass class;
int iret,i;
Region select_region;
short delta=4;
class=XdClass(dr);
z = class->xdcore_class.zoom;
if(z>= 0.5) delta *= z;
/*
 Crea la regione di move
*/
dr->xdcore.num_move_regions=dr->xdpoli.npoints;
dr->xdcore.move_regions=(Region *)XtCalloc(dr->xdcore.num_move_regions,sizeof(Region));
for(i=0; i< (dr->xdpoli.npoints-1); i++)
	dr->xdcore.move_regions[i]= RegionLineIntorno(dr->xdpoli.points[i].x,
                                                dr->xdpoli.points[i].y,
                                                dr->xdpoli.points[i+1].x,
                                                dr->xdpoli.points[i+1].y,
                                                z);
/* aggiunge la regione relativa alla linea che unisce il primo
   con l'ultimo punto
*/
i=dr->xdpoli.npoints-1;
if(dr->xdpoli.npoints >= 1)
	dr->xdcore.move_regions[i]= RegionLineIntorno(dr->xdpoli.points[i].x,
                                                dr->xdpoli.points[i].y,
                                                dr->xdpoli.points[0].x,
                                                dr->xdpoli.points[0].y,
                                                z);
/*
 Crea le regioni di resize
*/
dr->xdcore.num_resize_regions=dr->xdpoli.npoints;
dr->xdcore.resize_regions=(Region *)XtCalloc(dr->xdcore.num_resize_regions,sizeof(Region));
for(i=0; i< dr->xdpoli.npoints; i++)
	dr->xdcore.resize_regions[i]=RegionIntorno(dr->xdpoli.points[i].x,
					dr->xdpoli.points[i].y,z);

/* 
 Crea la regione di selezione come unione della regione di move e di quelle 
 di resize
*/
dr->xdcore.select_region=XCreateRegion();
for(i=0; i< (dr->xdpoli.npoints); i++)
	XUnionRegion(dr->xdcore.resize_regions[i],
		dr->xdcore.select_region,
		dr->xdcore.select_region);
for(i=0; i< (dr->xdpoli.npoints); i++)
        XUnionRegion(dr->xdcore.move_regions[i],
                dr->xdcore.select_region,
                dr->xdcore.select_region);
}

draw_poli(dr)
XdPoliDraget dr;
{
DragetClass class;
int i;
float z;
XPoint *points;
class=XdClass(dr);
z = class->xdcore_class.zoom;
if(z==1)
	{
	if(dr->xdcore.filled)
		XFillPolygon(XlDisplay(dr->xdcore.wid), 
			XlWindow(dr->xdcore.wid),
			dr->xdcore.gc_bg, dr->xdpoli.points, 
			dr->xdpoli.npoints,
			Complex,CoordModeOrigin);
	XDrawLines(XlDisplay(dr->xdcore.wid), XlWindow(dr->xdcore.wid),
                	dr->xdcore.gc,dr->xdpoli.points, 
			dr->xdpoli.npoints,
			CoordModeOrigin);
	}
else
	{
	points=(XPoint *)XtCalloc(dr->xdpoli.npoints, 
					sizeof(XPoint));
	for(i=0; i< dr->xdpoli.npoints; i++)
		{
		points[i].x= dr->xdpoli.points[i].x*z;
		points[i].y= dr->xdpoli.points[i].y*z;
		}
	if(dr->xdcore.filled)
		XFillPolygon(XlDisplay(dr->xdcore.wid), 
			XlWindow(dr->xdcore.wid),
			dr->xdcore.gc_bg, points, dr->xdpoli.npoints,
			Complex,CoordModeOrigin);
	XDrawLines(XlDisplay(dr->xdcore.wid), XlWindow(dr->xdcore.wid),
       		        dr->xdcore.gc,points, dr->xdpoli.npoints,
			CoordModeOrigin);
	}
}

draw_poli_off(dr, drawGC, offx,offy)
XdPoliDraget dr;
GC drawGC;
int offx,offy;
{
float z;
int i;
XPoint *points;
DragetClass class;
class= XdClass(dr);
z = class->xdcore_class.zoom;
points=(XPoint *)XtCalloc(dr->xdpoli.npoints, 
					sizeof(XPoint));
for(i=0; i< dr->xdpoli.npoints; i++)
	{
	points[i].x=(int)(z * (dr->xdpoli.points[i].x +offx));
	points[i].y= (int) (z * (dr->xdpoli.points[i].y +offy));
	}
/*
if(dr->xdcore.filled)
	XFillPolygon(XtDisplay(dr->xdcore.wid), XtWindow(dr->xdcore.wid),
		dr->xdcore.gc_bg, points, dr->xdpoli.npoints,
		Complex,CoordModeOrigin);
*/
XDrawLines(XtDisplay(dr->xdcore.wid), XtWindow(dr->xdcore.wid),
                drawGC,points, dr->xdpoli.npoints,
		CoordModeOrigin);
XtFree(points);
}


