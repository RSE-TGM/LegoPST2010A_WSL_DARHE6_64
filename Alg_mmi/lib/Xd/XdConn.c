/**********************************************************************
*
*       C Source:               XdConn.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Dec 22 18:16:02 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XdConn.c-5.1.1 %  (%full_filespec: XdConn.c-5.1.1:csrc:1 %)";
#endif
/*
   modulo XdConn.c
   tipo 
   release 5.2
   data 12/15/95
   reserved @(#)XdConn.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XdConn.c	5.2\t12/15/95";
/*
        Fine sezione per SCCS
*/
/*
 XdConn - oggetto connessione 
*/
#include <Xm/Xm.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include <stdio.h>
#include <stdlib.h>

#include <Xd/XdCoreP.h>
#include <Xd/XdConnP.h>
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
XdConnClassRec xdConnClassRec = {
	{ /* xdcore fields */
	  /* initialized */     False,
	  /* class_name */ 	"XdConn",
	  /* superclass */      (DragetClass)&xdCoreClassRec,
	  /* gcxor      */	NULL,
	  /* gcsel      */	NULL,
	  /* zoom       */      1.0,
	  /* draget size */	sizeof(XdConnRec),
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
          /* Copy       */      Copy,
#ifdef XPRINTER_USED
	  /* Print      */      Print
#endif
	},
	{
	 /* dummy       */ 0
	}
};

DragetClass xdConnDragetClass = (DragetClass) &xdConnClassRec;

/*
 Metodi
*/

static void Initialize(dra)
Draget dra;
{
XdConnDraget dr;
Widget wid;
}

static void Destroy(dra)
Draget dra;
{
XdConnDraget dr;
int last;
float z;
DragetClass class;
class=XdClass(dra);
dr=(XdConnDraget)dra;
z = class->xdcore_class.zoom;
dr->xdcore.managed= False; /* impedisce che venga effettuato
			il redraw su oggetto in cancellazione */
/*
 Richiama (se definito) il metodo di cancellazione connessione
*/
last=dr->xdconn.npoints-1;
if(*xdConnClassRec.xdconn_class.deleteConn != NULL)
	{
	(*xdConnClassRec.xdconn_class.deleteConn)(dr->xdcore.wid,
	(int)(dr->xdconn.points[0].x*z),(int)(dr->xdconn.points[0].y*z),
	(int)(dr->xdconn.points[last].x*z),(int)(dr->xdconn.points[last].y*z));
	}
XtFree(dr->xdconn.points);
/********
XtReleaseGC(dr->xdcore.wid,dr->xdcore.gc);
XtReleaseGC(dr->xdcore.wid,dr->xdcore.gc_bg);
********/
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
XdConnDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
dr=(XdConnDraget)dra;
z = class->xdcore_class.zoom;
display=XtDisplay(dr->xdcore.wid);
/*
 A seconda del numero della regione di resize selezionata determina
 quale e' il punto che deve rimanere fissato
*/
npunto=dr->xdcore.num_resize;
/*
 In corrispondenza dei punti estremi non si effettua il resize
*/
if(npunto == 0 || npunto == (dr->xdconn.npoints-1))
	return;
npunto_prec= npunto-1;
npunto_succ= npunto+1;

if(dr->xdcore.is_first == False)
	{
	XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z * dr->xdconn.points[npunto_prec].x),
			(int)(z * dr->xdconn.points[npunto_prec].y),
			(int)(z * dr->xdconn.xprev),
			(int)( z * dr->xdconn.yprev));
	XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z * dr->xdconn.points[npunto_succ].x),
			(int)(z * dr->xdconn.points[npunto_succ].y),
			(int)(z * dr->xdconn.xprev),
			(int)( z * dr->xdconn.yprev));
	}
else
	{
	dr->xdcore.is_first = False;
	}

dr->xdconn.xprev= ev->xmotion.x /z;
dr->xdconn.yprev= ev->xmotion.y /z;

XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z * dr->xdconn.points[npunto_prec].x),
			(int)(z * dr->xdconn.points[npunto_prec].y),
			(int)(z * dr->xdconn.xprev),
			(int)( z * dr->xdconn.yprev));
XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z * dr->xdconn.points[npunto_succ].x),
			(int)(z * dr->xdconn.points[npunto_succ].y),
			(int)(z * dr->xdconn.xprev),
			(int)( z * dr->xdconn.yprev));
XFlush(display);
}

static Boolean EndResize(dra,ev)
Draget dra;
XEvent *ev;
{
int npunto;
float z;
XdConnDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdConnDraget)dra;
npunto=dr->xdcore.num_resize;
/*
 In corrispondenza dei punti estremi non si effettua il resize
*/
if(npunto == 0 || npunto == (dr->xdconn.npoints-1))
	return;
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
dr->xdconn.points[npunto].x = ev->xbutton.x / z;
dr->xdconn.points[npunto].y =  ev->xbutton.y / z;
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

#define DIREZ_O  1
#define DIREZ_V  2
#define DIREZ_BOH 3

static Boolean Move(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
static int direz;
static int x_click,y_click;
int xfix,yfix;
Display *display;
XdConnDraget dr;
DragetClass class;
return;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdConnDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/*
 il delta di spostamento viene memorizzato rispettivamente in:
	dr->xdconn.xprev e
	dr->xdconn.yprev
*/
if(dr->xdcore.is_first == False)
	draw_conn_off(dr,class->xdcore_class.gcxor,dr->xdconn.xprev,
					dr->xdconn.yprev);
else
	{
	dr->xdcore.is_first = False;
	x_click = ev->xmotion.x / z;
	y_click = ev->xmotion.y / z;
	direz=DIREZ_BOH;
	}

dr->xdconn.xprev= ev->xmotion.x / z - x_click;
dr->xdconn.yprev= ev->xmotion.y / z - y_click;
if(dr->xdconn.xprev ==0 && dr->xdconn.yprev==0)
	direz=DIREZ_BOH;
else if (direz==DIREZ_BOH && abs(dr->xdconn.xprev)> abs(dr->xdconn.yprev))
	{
	direz=DIREZ_O;
	dr->xdconn.yprev=0;
	}
else if (direz==DIREZ_BOH && abs(dr->xdconn.yprev)> abs(dr->xdconn.xprev))
        {
        direz=DIREZ_V;
        dr->xdconn.xprev=0;
        }
else if( direz == DIREZ_V)
	dr->xdconn.xprev=0;

else if ( direz == DIREZ_O)
	dr->xdconn.yprev=0;


draw_conn_off(dr,class->xdcore_class.gcxor,dr->xdconn.xprev,
                                        dr->xdconn.yprev);

XFlush(display);
}


static Boolean EndMove(dra,ev)
Draget dra;
XEvent *ev;
{
int i;
XdConnDraget dr;
DragetClass class;
return(False);
class=XdClass(dra);
dr=(XdConnDraget)dra;
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
for(i=0; i< dr->xdconn.npoints; i++)
	{
	dr->xdconn.points[i].x+= dr->xdconn.xprev;
	dr->xdconn.points[i].y+= dr->xdconn.yprev;
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
XdConnDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdConnDraget)dra;
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
/******* senza clipping
if(ev!=NULL)
	region=RegionClip(ev);
else
	region=RegionClipBox(dr->xdcore.select_region);
XSetRegion(display,dr->xdcore.gc,region);
XSetRegion(display,class->xdcore_class.gcsel,region);
XSetRegion(display,dr->xdcore.gc_bg,region);

fine clipping **********/
draw_conn(dr,dr->xdcore.gc);

/*
 Se l'oggetto e' nello stato selezionato disegna i rettangolini
 di selezione
*/
if(dr->xdcore.selected)
	{
	for(i=0; i<dr->xdconn.npoints; i++)
		{
		XFillRectangle(display,XtWindow(dr->xdcore.wid),
			class->xdcore_class.gcsel,
			(int)(z*dr->xdconn.points[i].x-(delta/2)),
			(int)(z*dr->xdconn.points[i].y-(delta/2)),
				delta,delta);
		}
	}
/* solo se clipping
XDestroyRegion(region);
****/
}

#ifdef XPRINTER_USED
static void Print(dra,flag)
Draget dra;
Boolean flag;
{
XdConnDraget dr;
dr=(XdConnDraget)dra;
draw_conn(dr);
}
#endif


static Boolean FirstPoint(dra,ev)
Draget dra;
XEvent *ev;
{
XdConnDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdConnDraget)dra;

dr->xdcore.x= ev->xbutton.x / z;
dr->xdcore.y= ev->xbutton.y / z;

dr->xdcore.is_first= True;
dr->xdcore.managed= False; /* indica che l'oggetto e' in fase di 
				costruzione: impedisce che venga effettuato
				il redraw su oggetto non completo */
/* 
 se il punto e' successivo al primo esamina che non sia coincidente al
 punto precedente ( in tal caso non memorizza il nuovo punto)
*/
if(dr->xdconn.npoints && 
        dr->xdconn.points[dr->xdconn.npoints-1].x == dr->xdcore.x &&
	dr->xdconn.points[dr->xdconn.npoints-1].y == dr->xdcore.y)
	{
	printf("\n coincidenti !!\n");
	return(False);
	}
if(dr->xdconn.npoints > 0)
   {
	DisegnaCroce(XtDisplay(dr->xdcore.wid),XtWindow(dr->xdcore.wid),
	     class->xdcore_class.gcxor,(int)(z*dr->xdcore.x),
	     (int)(z*dr->xdcore.y));
    }
dr->xdconn.npoints++;
dr->xdconn.points=(XPoint *)XtRealloc(dr->xdconn.points, 
			dr->xdconn.npoints*sizeof(XPoint));
/*
 Inserisce nel vettore dei punti quello appena allocato
*/
dr->xdconn.points[dr->xdconn.npoints-1].x = dr->xdcore.x;
dr->xdconn.points[dr->xdconn.npoints-1].y = dr->xdcore.y;
/*
 esamina se l'evento corrispondente e' di movimento del
 mouse: in questo caso significa che si sta disegnando a
 mano libera
*/
if(ev->xmotion.type == MotionNotify && ev->xmotion.state== Button1Mask )
/*****
	ev->xany.type != KeyPress)
*****/
	{
        printf("Sto per fare la drawLine\n");
	XDrawLine(XtDisplay(dr->xdcore.wid),
			XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z*dr->xdconn.points[dr->xdconn.npoints-2].x),
			(int)(z*dr->xdconn.points[dr->xdconn.npoints-2].y),
			(int)(z*dr->xdconn.points[dr->xdconn.npoints-1].x),
			(int)(z*dr->xdconn.points[dr->xdconn.npoints-1].y));
	}
return(True);
}

static Boolean LastPoint(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
XdConnDraget dr;
DragetClass class;
class=XdClass(dra);
dr=(XdConnDraget)dra;
z = class->xdcore_class.zoom;
/*
 memorizza i punti finali
*/
if(ev->xany.type==ButtonPress)
	{
	dr->xdconn.xf = ev->xbutton.x / z;
	dr->xdconn.yf = ev->xbutton.y /z;
	}
else
	{
	dr->xdconn.xf = ev->xkey.x / z;
	dr->xdconn.yf = ev->xkey.y /z;
	}

if(dr->xdconn.npoints > 1 &&
        dr->xdconn.points[dr->xdconn.npoints-1].x == dr->xdconn.xf &&
        dr->xdconn.points[dr->xdconn.npoints-1].y == dr->xdconn.yf)
        {
        printf("\n coincidenti !!\n");
        }
else  /* inserisce l'ultimo punto */
	{
	dr->xdconn.npoints++;
	dr->xdconn.points=(XPoint *)XtRealloc(dr->xdconn.points, 
			dr->xdconn.npoints*sizeof(XPoint));
/*
 Inserisce nel vettore dei punti quello appena allocato
*/
	dr->xdconn.points[dr->xdconn.npoints-1].x = dr->xdconn.xf;
	dr->xdconn.points[dr->xdconn.npoints-1].y = dr->xdconn.yf;
	}
dr->xdcore.managed= True; /* l'oggetto e' completo */

DisegnaCroce(XtDisplay(dr->xdcore.wid),XtWindow(dr->xdcore.wid),
	     class->xdcore_class.gcxor,(int)(z*dr->xdconn.xprev),
             (int)(z*dr->xdconn.yprev));

class->xdcore_class.crea_regions(dr);
/*
 forza il ridisegno dell'oggetto finale
*/
class->xdcore_class.expose(dr,NULL);
/*
 se l'oggetto e' di dimensione nulla ritorna
 False
*/
if(dr->xdconn.npoints == 2 && dr->xdconn.points[0].x==dr->xdconn.points[1].x
			   && dr->xdconn.points[0].y==dr->xdconn.points[1].y )
	return(False);
/*
 caso in cui si interrompe la connessione
 (press del bottone 2 o 3 del mouse)
*/
else if (( ev->xbutton.button == Button2)|| ( ev->xbutton.button == Button3)
         ||(ev->xany.type==KeyPress))
	{
	printf("fine conn con bottone 2 \n");
	return(False);
	}
else
        return(True);
}

static Boolean FirstDraw(dra,ev)
Draget dra;
XEvent *ev;
{
Boolean bWarp;
int deltax,deltay;
static direz;
Display *display;
XdConnDraget dr;
float z;
DragetClass class;
static int warpX=0;
static int warpY=0;
static int oldevx=0;
static int oldevy=0;

class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdConnDraget)dra;
display=XtDisplay(dr->xdcore.wid);
deltax=0;
deltay=0;


/*
Verifico che l' evento non sia = al precedente
*/
if((oldevx==(int) (ev->xmotion.x / z)) && (oldevy==(int) (ev->xmotion.y / z)) )
   return 1;

oldevx=(int) (ev->xmotion.x / z);
oldevy=(int) (ev->xmotion.y / z);



if(dr->xdcore.is_first == False)
	{
	XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
			(int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
			(int)(z*dr->xdconn.xprev), (int)(z*dr->xdconn.yprev));
	DisegnaCroce(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
                        (int)(z*dr->xdconn.xprev),(int)(z*dr->xdconn.yprev));
        warpX=(int)(z*dr->xdconn.xprev);
        warpY=(int)(z*dr->xdconn.yprev);
	}
else
	{
	dr->xdcore.is_first = False;
	direz=DIREZ_BOH;
	}

deltax= (int) (ev->xmotion.x / z - dr->xdcore.x);
deltay= (int) (ev->xmotion.y / z - dr->xdcore.y);

dr->xdconn.xprev= dr->xdcore.x;
dr->xdconn.yprev= dr->xdcore.y;
bWarp=False;

if(abs(deltax)<4 && abs(deltay) <4)
	{
	direz= DIREZ_BOH;
	}
else if (direz==DIREZ_BOH && abs(deltax)> abs(deltay))
	{
	direz= DIREZ_O;
	dr->xdconn.xprev= ev->xmotion.x / z;
	if(deltay)
		bWarp=True;
	}
else if (direz==DIREZ_BOH && abs(deltay)> abs(deltax))
	{
        direz= DIREZ_V;
        dr->xdconn.yprev= ev->xmotion.y / z;
	if(deltax)
		bWarp=True;
	}
else if (direz==DIREZ_V)
	{
	dr->xdconn.yprev= ev->xmotion.y / z;
	if(deltax)
		bWarp=True;
	}

else if (direz==DIREZ_O)
	{
	dr->xdconn.xprev= ev->xmotion.x / z;
	if(deltay)
		bWarp=True;
	}



DisegnaCroce(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
                        (int)(z*dr->xdconn.xprev),(int)(z*dr->xdconn.yprev));
XDrawLine(display,XtWindow(dr->xdcore.wid),class->xdcore_class.gcxor,
                        (int)(z*dr->xdcore.x),(int)(z*dr->xdcore.y),
                        (int)(z*dr->xdconn.xprev), (int)(z*dr->xdconn.yprev));

if(bWarp)
    XWarpPointer(display,None,XtWindow(dr->xdcore.wid),
	(int)0,(int)0,(unsigned int)0,(unsigned int)0,
	(int)(dr->xdconn.xprev*z),(int)(dr->xdconn.yprev*z));

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
XdConnDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdConnDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/* 
 Determina l'area su cui effettuare il clear
*/
XClipBox(dr->xdcore.select_region,&rect);
/*
topx=(dr->xdcore.x < dr->xdconn.xf) ? dr->xdcore.x : dr->xdconn.xf;
topy=(dr->xdcore.y < dr->xdconn.yf) ? dr->xdcore.y : dr->xdconn.yf;
topx-=delta;
topy-=delta;

width= (abs(dr->xdcore.x-dr->xdconn.xf))+2*delta;
height= (abs(dr->xdcore.y-dr->xdconn.yf))+2*delta;
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
XdConnDraget dr;
int x,y,i;
DragetClass class;
dr=(XdConnDraget)dra;
class=XdClass(dra);
fscanf(fp,"%d",&dr->xdconn.npoints);
dr->xdconn.points=(XPoint *)XtCalloc(dr->xdconn.npoints, 
					sizeof(XPoint));
for(i=0;i<dr->xdconn.npoints; i++)
	{
	fscanf(fp," %d %d",&x,&y);
	dr->xdconn.points[i].x=x;
	dr->xdconn.points[i].y=y;
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
XdConnDraget dr;
XdConnDraget dr_dest;
int i;
DragetClass class;
dr=(XdConnDraget)dra;
dr_dest=(XdConnDraget)dra_dest;
class=XdClass(dra);

dr_dest->xdconn.npoints=dr->xdconn.npoints;
dr_dest->xdconn.points=(XPoint *)XtCalloc(dr_dest->xdconn.npoints, 
					sizeof(XPoint));
for(i=0;i<dr_dest->xdconn.npoints; i++)
	{
	dr_dest->xdconn.points[i].x=dr->xdconn.points[i].x;
	dr_dest->xdconn.points[i].y=dr->xdconn.points[i].y;
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
XdConnDraget dr;
dr=(XdConnDraget)dra;
fprintf(fp,"Conn %d",dr->xdconn.npoints);
for(i=0;i<dr->xdconn.npoints; i++)
	fprintf(fp," %d %d",dr->xdconn.points[i].x,dr->xdconn.points[i].y);
fprintf(fp,"\n");
}

/*
 N.B.
 Nel caso particolare della connessione il metodo get_size
 ritorna invece delle coordinate minime e massime le
 coordinate di INIZIO e FINE della connessione
*/
static void GetSize(dra,xmin,ymin,xmax,ymax)
Draget dra;
int *xmin,*ymin,*xmax,*ymax;
{
XdConnDraget dr;
XGCValues values;
int offset;
int i;
float z;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdConnDraget)dra;
*xmin=dr->xdconn.points[0].x *z;
*ymin=dr->xdconn.points[0].y *z;
*xmax=dr->xdconn.points[dr->xdconn.npoints-1].x *z;
*ymax=dr->xdconn.points[dr->xdconn.npoints-1].y *z;

}


static void Modify(dra,dx,dy,dxfin,dyfin,ev)
Draget dra;
int dx,dy,dxfin,dyfin; /* spostamenti relativi del punto iniziale
                          e finale della spezzata */
XEvent *ev;
{
XdConnDraget dr;
DragetClass class;
int i;
float z;
dr=(XdConnDraget)dra;
class=XdClass(dra);
printf(" chiamata Modify Conn dx=%d dy=%d dxfin=%d dyfin=%d\n",dx,dy,dxfin,dyfin);
z = class->xdcore_class.zoom;
/*
 esegue il clear del disegno di partenza
*/
class->xdcore_class.clear(dr);
/*
 se gli incrementi dei due estremi della spezzata sono tra loro
 eguali allora trasla l'oggetto
*/
if(dx==dxfin && dy==dyfin)
	{
	for(i=0;i<(dr->xdconn.npoints); i++)
       		 {
		 dr->xdconn.points[i].x+=(dx/z);
		 dr->xdconn.points[i].y+=(dy/z);
		 }
	}
/*
 se gli incrementi sono differenti allora sposta solamente gli
 estremi
*/
else
	{
	dr->xdconn.points[0].x+=(dx/z);
	dr->xdconn.points[0].y+=(dy/z);
	dr->xdconn.points[dr->xdconn.npoints-1].x+=(dxfin/z);
        dr->xdconn.points[dr->xdconn.npoints-1].y+=(dyfin/z);
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
/*
 setta l'attributo di managed a false per poter
 permettere la gestione delle altre connessioni
 escludendo la connessione per cui e' appena stato gestita
 la modify
*/
dr->xdcore.managed=False;
}


/*
 Routine di creazione (generalizzabile e spostabile in DrUtil.c)
*/
Draget XdCreateConnDraget(wid, gc, gc_bg)
Widget wid; /* widget su cui effettuare il disegno */
GC gc;
GC gc_bg;
{
Draget dr;
DragetClass class;
class=(DragetClass)&xdConnClassRec;
return(XdCreateDraget(wid,class,gc,gc_bg));
}



static void CreaRegions(dr)
XdConnDraget dr;
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
dr->xdcore.num_move_regions=dr->xdconn.npoints;
dr->xdcore.move_regions=(Region *)XtCalloc(dr->xdcore.num_move_regions,sizeof(Region));
for(i=0; i< (dr->xdconn.npoints-1); i++)
	dr->xdcore.move_regions[i]= RegionLineIntorno(dr->xdconn.points[i].x,
                                                dr->xdconn.points[i].y,
                                                dr->xdconn.points[i+1].x,
                                                dr->xdconn.points[i+1].y,
                                                z);
/* aggiunge la regione relativa alla linea che unisce il primo
   con l'ultimo punto
*/
i=dr->xdconn.npoints-1;
if(dr->xdconn.npoints >= 1)
	dr->xdcore.move_regions[i]= RegionLineIntorno(dr->xdconn.points[i].x,
                                                dr->xdconn.points[i].y,
                                                dr->xdconn.points[0].x,
                                                dr->xdconn.points[0].y,
                                                z);
/*
 Crea le regioni di resize
*/
dr->xdcore.num_resize_regions=dr->xdconn.npoints;
dr->xdcore.resize_regions=(Region *)XtCalloc(dr->xdcore.num_resize_regions,sizeof(Region));
for(i=0; i< dr->xdconn.npoints; i++)
	dr->xdcore.resize_regions[i]=RegionIntorno(dr->xdconn.points[i].x,
					dr->xdconn.points[i].y,z);

/* 
 Crea la regione di selezione come unione della regione di move e di quelle 
 di resize
*/
dr->xdcore.select_region=XCreateRegion();
for(i=0; i< (dr->xdconn.npoints); i++)
	XUnionRegion(dr->xdcore.resize_regions[i],
		dr->xdcore.select_region,
		dr->xdcore.select_region);
for(i=0; i< (dr->xdconn.npoints); i++)
        XUnionRegion(dr->xdcore.move_regions[i],
                dr->xdcore.select_region,
                dr->xdcore.select_region);
}

draw_conn(dr)
XdConnDraget dr;
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
			dr->xdcore.gc_bg, dr->xdconn.points, 
			dr->xdconn.npoints,
			Complex,CoordModeOrigin);
	XDrawLines(XlDisplay(dr->xdcore.wid), XlWindow(dr->xdcore.wid),
                	dr->xdcore.gc,dr->xdconn.points, 
			dr->xdconn.npoints,
			CoordModeOrigin);
	}
else
	{
	points=(XPoint *)XtCalloc(dr->xdconn.npoints, 
					sizeof(XPoint));
	for(i=0; i< dr->xdconn.npoints; i++)
		{
		points[i].x= dr->xdconn.points[i].x*z;
		points[i].y= dr->xdconn.points[i].y*z;
		}
	if(dr->xdcore.filled)
		XFillPolygon(XlDisplay(dr->xdcore.wid), 
			XlWindow(dr->xdcore.wid),
			dr->xdcore.gc_bg, points, dr->xdconn.npoints,
			Complex,CoordModeOrigin);
	XDrawLines(XlDisplay(dr->xdcore.wid), XlWindow(dr->xdcore.wid),
       		        dr->xdcore.gc,points, dr->xdconn.npoints,
			CoordModeOrigin);
	}
}

draw_conn_off(dr, drawGC, offx,offy)
XdConnDraget dr;
GC drawGC;
int offx,offy;
{
float z;
int i;
XPoint *points;
DragetClass class;
class= XdClass(dr);
z = class->xdcore_class.zoom;
points=(XPoint *)XtCalloc(dr->xdconn.npoints, 
					sizeof(XPoint));
for(i=0; i< dr->xdconn.npoints; i++)
	{
	points[i].x=(int)(z * (dr->xdconn.points[i].x +offx));
	points[i].y= (int) (z * (dr->xdconn.points[i].y +offy));
	}
/*
if(dr->xdcore.filled)
	XFillPolygon(XtDisplay(dr->xdcore.wid), XtWindow(dr->xdcore.wid),
		dr->xdcore.gc_bg, points, dr->xdconn.npoints,
		Complex,CoordModeOrigin);
*/
XDrawLines(XtDisplay(dr->xdcore.wid), XtWindow(dr->xdcore.wid),
                drawGC,points, dr->xdconn.npoints,
		CoordModeOrigin);
XtFree(points);
}


DisegnaCroce(display,win,gc,x,y)
Display *display;
Drawable win;
GC gc;
int x,y;
{
/* 
 Disegna la linea orizzontale
*/
XDrawLine(display,win,gc,0,y,1200,y);
/* 
 Disegna la linea verticale
*/
XDrawLine(display,win,gc,x,0,x,1000);
}
