/**********************************************************************
*
*       C Source:               XdGroup.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon Jun 19 18:34:30 2006 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XdGroup.c-2 %  (%full_filespec: XdGroup.c-2:csrc:1 %)";
#endif
/*
   modulo XdGroup.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdGroup.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XdGroup.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*
 XdGroup - oggetto raggruppamento di draget 
*/
#include <Xm/Xm.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>

#include <Xd/XdCoreP.h>
#include <Xd/XdGroupP.h>
#include <Xd/Xd.h>
#include <Xd/XdGeom.h>
#include <Xd/XdLista.h>
#include <message.h>

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
XdGroupClassRec  xdGroupClassRec = {
	{ /* xdcore fields */
	  /* initialized */     False,
	  /* class_name */ 	"XdGroup",
	  /* superclass */      (DragetClass)&xdCoreClassRec,
	  /* gcxor      */	NULL,
	  /* gcsel      */	NULL,
	  /* zoom       */      1.0,
	  /* draget size */	sizeof(XdGroupRec),
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

DragetClass xdGroupDragetClass = (DragetClass) &xdGroupClassRec;

/*
 Metodi
*/

static void Initialize(dra)
Draget dra;
{
XdGroupDraget dr;
dr=(XdGroupDraget)dra;
}

static void Destroy(dra)
Draget dra;
{
XdGroupDraget dr;
dr=(XdGroupDraget)dra;
dr->xdcore.managed= False; /* impedisce che venga effettuato
			il redraw su oggetto in cancellazione */
XdDestroyLista(dr->xdgroup.dr_list);
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
XdGroupDraget dr;
float z;
DragetClass class;
class=XdClass(dra);
dr=(XdGroupDraget)dra;
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
	xfix=dr->xdgroup.xf;
	yfix=dr->xdgroup.yf;
	}
*/
switch(dr->xdcore.num_resize)
	{
	case 0:
	xfix=dr->xdgroup.xf;
        yfix=dr->xdgroup.yf;
        break;
	case 1:
	xfix=dr->xdcore.x;
        yfix=dr->xdgroup.yf;
        break;
	case 2:
	xfix=dr->xdcore.x;
        yfix=dr->xdcore.y;
	break;
	case 3:
	xfix=dr->xdgroup.xf;
        yfix=dr->xdcore.y;
	break;
	}
	

if(dr->xdcore.is_first == False)
	draw_rect(dr,class->xdcore_class.gcxor,False,
			(int)(z * xfix),(int)(z * yfix),
			(int)(z * dr->xdgroup.xprev),
			(int)( z * dr->xdgroup.yprev));
else
	{
	dr->xdcore.is_first = False;
	}

dr->xdgroup.xprev= ev->xmotion.x /z;
dr->xdgroup.yprev= ev->xmotion.y /z;

draw_rect(dr,class->xdcore_class.gcxor,False,
                        (int)(z * xfix),(int)(z * yfix),
                        (int)(z * dr->xdgroup.xprev),
			(int)(z * dr->xdgroup.yprev));
XFlush(display);
}

static Boolean EndResize(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
GROUP_EV gr_ev; /* notifica un evento di ridimensionamento del gruppo
		   al singolo componente appartenente al gruppo
		*/
float wnew,hnew,w,h;
float fatt_y,fatt_x;
int xfix,yfix;
XdGroupDraget dr;
Draget drf;
DragetClass class,classf;
class=XdClass(dra);
dr=(XdGroupDraget)dra;
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
	dr->xdgroup.xf = ev->xbutton.x / z;
	dr->xdgroup.yf = ev->xbutton.y / z;
	}
else
	{
	dr->xdcore.x = ev->xbutton.x / z;
	dr->xdcore.y = ev->xbutton.y / z;
	}
*/

w=dr->xdgroup.xf-dr->xdcore.x;
h=dr->xdgroup.yf-dr->xdcore.y;

switch(dr->xdcore.num_resize)
	{
	case 0:
	dr->xdcore.x = ev->xbutton.x / z;
        dr->xdcore.y = ev->xbutton.y / z;
	xfix=dr->xdgroup.xf;
	yfix=dr->xdgroup.yf;
	break;
	case 1:
	dr->xdgroup.xf = ev->xbutton.x / z;
	dr->xdcore.y = ev->xbutton.y / z;
	yfix=dr->xdgroup.yf;
	xfix=dr->xdcore.x;
	break;
	case 2:
	dr->xdgroup.xf = ev->xbutton.x / z;
	dr->xdgroup.yf = ev->xbutton.y / z;
	xfix=dr->xdcore.x;
	yfix=dr->xdcore.y;
	break;
	case 3:
	dr->xdcore.x = ev->xbutton.x / z;
	dr->xdgroup.yf = ev->xbutton.y / z;
	xfix=dr->xdgroup.xf;
	yfix=dr->xdcore.y;
	break;
	}


wnew=dr->xdgroup.xf-dr->xdcore.x;
hnew=dr->xdgroup.yf-dr->xdcore.y;
fatt_x=wnew/w;
fatt_y=hnew/h;
/*
 Esegue il resize degli oggetti componenti 
*/

/*
 Richiama le routines di modifica degli
 oggetti componenti il gruppo per traslarli opportunamente
*/
gr_ev.type=RESIZE_GROUP;
gr_ev.n_angle= dr->xdcore.num_resize;
gr_ev.fatt_x=fatt_x;
gr_ev.fatt_y=fatt_y;
gr_ev.xfix=xfix;
gr_ev.yfix=yfix;

ListDragetRew(dr->xdgroup.dr_list);
while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
        {
	classf=XdClass(drf);
	classf->xdcore_class.modify(drf,0,0,0,0,&gr_ev);
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
 esegue il clear del disegno di partenza
*/
class->xdcore_class.clear(dr);
/*
 Ridisegna l'oggetto
*/
/*****
class->xdcore_class.expose(dr,NULL);
******/
}


static Boolean Move(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
static int x_click,y_click;
int xfix,yfix;
Display *display;
XdGroupDraget dr;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdGroupDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/*
 il delta di spostamento viene memorizzato rispettivamente in:
	dr->xdgroup.xprev e
	dr->xdgroup.yprev
*/
if(dr->xdcore.is_first == False)
	draw_rect(dr,class->xdcore_class.gcxor,False,
		(int)(z*(dr->xdcore.x+dr->xdgroup.xprev)),
		(int)(z*(dr->xdcore.y+dr->xdgroup.yprev)),
		(int)(z*(dr->xdgroup.xf+dr->xdgroup.xprev)),
		(int)(z*(dr->xdgroup.yf+dr->xdgroup.yprev)));
else
	{
	dr->xdcore.is_first = False;
	x_click = ev->xmotion.x / z;
	y_click = ev->xmotion.y / z;
	}

dr->xdgroup.xprev= ev->xmotion.x / z - x_click;
dr->xdgroup.yprev= ev->xmotion.y / z - y_click;

draw_rect(dr,class->xdcore_class.gcxor,False,
		(int)(z*(dr->xdcore.x+dr->xdgroup.xprev)),
		(int)(z*(dr->xdcore.y+dr->xdgroup.yprev)),
		(int)(z*(dr->xdgroup.xf+dr->xdgroup.xprev)),
		(int)(z*(dr->xdgroup.yf+dr->xdgroup.yprev)));

XFlush(display);
}


static Boolean EndMove(dra,ev)
Draget dra;
XEvent *ev;
{
int dx,dy;
XdGroupDraget dr;
Draget drf;
DragetClass class,classf;
float z;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdGroupDraget)dra;
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
 Cancella l'ultimo rettangolo di spostamento
 disegnato
*/
draw_rect(dr,class->xdcore_class.gcxor,False,
		(int)(z*(dr->xdcore.x+dr->xdgroup.xprev)),
		(int)(z*(dr->xdcore.y+dr->xdgroup.yprev)),
		(int)(z*(dr->xdgroup.xf+dr->xdgroup.xprev)),
		(int)(z*(dr->xdgroup.yf+dr->xdgroup.yprev)));
/*
 esegue il clear del disegno di partenza
*/
class->xdcore_class.clear(dr);
/*
 salva i delta di spostamento
*/
dx=dr->xdgroup.xprev;
dy=dr->xdgroup.yprev;
/*
 memorizza i punti finali
*/
dr->xdgroup.xf += dr->xdgroup.xprev;
dr->xdgroup.yf +=  dr->xdgroup.yprev;
dr->xdcore.x +=  dr->xdgroup.xprev;
dr->xdcore.y += dr->xdgroup.yprev;

dr->xdcore.managed= True; /* l'oggetto e' completo */
dr->xdcore.moving= False; /* termine move dell'oggetto */
dr->xdcore.resizing= False; /* termine resize dell'oggetto */

/*
 Richiama le routines di modifica degli
 oggetti componenti il gruppo per traslarli opportunamente
*/
ListDragetRew(dr->xdgroup.dr_list);
while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
        {
	classf=XdClass(drf);
	classf->xdcore_class.modify(drf,dx,dy,0,0,NULL);
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


static void Redraw(dra,ev)
Draget dra;
XEvent *ev;
{
float z;
Region region;
Display *display;
unsigned int delta=4;
XdGroupDraget dr;
Draget drf;
DragetClass class;
DragetClass classf;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdGroupDraget)dra;
/*
 se l'oggetto non e' completo oppure e' in cancellazione
 esce senza ridisegnarlo
*/
if (dr->xdcore.managed == False) 
	return;
display=XtDisplay(dr->xdcore.wid);
/*
 Richiama le routines di ridisegno degli
 oggetti componenti il gruppo
*/
ListDragetRew(dr->xdgroup.dr_list);
while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
        {
	classf=XdClass(drf);
	classf->xdcore_class.expose(drf,ev);
        }

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
                        (int)(z*dr->xdgroup.xf-(delta/2)),
			(int)(z*dr->xdgroup.yf-(delta/2)),
                                delta,delta);
	XFillRectangle(display,XtWindow(dr->xdcore.wid),
			class->xdcore_class.gcsel,
                        (int)(z*dr->xdgroup.xf-(delta/2)),
			(int)(z*dr->xdcore.y-(delta/2)),
                                delta,delta);
	XFillRectangle(display,XtWindow(dr->xdcore.wid),
			class->xdcore_class.gcsel,
                        (int)(z*dr->xdcore.x-(delta/2)),
			(int)(z*dr->xdgroup.yf-(delta/2)),
                                delta,delta);
	}
}

#ifdef XPRINTER_USED
static void Print(dra,flag)
Draget dra;
Boolean flag;
{
extern DragetClass xdCoreDragetClass;
XdGroupDraget dr;
Draget drf;
DragetClass classf;
/*
 Richiama le routines di print degli
 oggetti componenti il gruppo
*/
dr=(XdGroupDraget) dra;
ListDragetRew(dr->xdgroup.dr_list);
while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
        {
/*
 richiama il metodo di print relativo a XdCore che
 si occupa del salvataggio
 dei GC (gc e gc_fg) (Flag settato a True).
*/
	xdCoreDragetClass->xdcore_class.print(drf,True);
/*
 richiama il metodo di print specifico per l'oggetto
*/
	classf=XdClass(drf);
	classf->xdcore_class.print(drf,True);
/*
 richiama il metodo di print relativo a XdCore che
 si occupa del ripristino
 dei GC (gc e gc_fg) (Flag settato a False).
*/
	xdCoreDragetClass->xdcore_class.print(drf,False);
        }
}
#endif

static Boolean FirstPoint(dra,ev)
Draget dra;
XEvent *ev;
{
}

static Boolean LastPoint(dra,ev)
Draget dra;
XEvent *ev;
{
}

static Boolean FirstDraw(dra,ev)
Draget dra;
XEvent *ev;
{
}


static void Clear(dra)
Draget dra;
{
static XEvent eve_exp;
XmDrawingAreaCallbackStruct str;
Display *display;
float z;
XdGroupDraget dr;
int xmin,xmax,ymin,ymax;
unsigned int width,height;
int delta=3;
DragetClass class;
class=XdClass(dra);
z = class->xdcore_class.zoom;
dr=(XdGroupDraget)dra;
display=XtDisplay(dr->xdcore.wid);
/* 
 Determina l'area su cui effettuare il clear
*/
if(dr->xdcore.x < dr->xdgroup.xf)
	{
	xmin = dr->xdcore.x;
	xmax = dr->xdgroup.xf;
	}
else
	{
	xmin = dr->xdgroup.xf;
	xmax = dr->xdcore.x;
	}

if(dr->xdcore.y < dr->xdgroup.yf)
	{
	ymin = dr->xdcore.y;
	ymax = dr->xdgroup.yf;
	}
else
	{
	ymin = dr->xdgroup.yf;
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
extern DragetClass xdCoreDragetClass;
int x,y,xf,yf;
DragetClass class,classf;
XdGroupDraget dr;
Draget drf;
Widget wid;
GC gc,gc_bg;
char buf[10];
int i;
dr=(XdGroupDraget)dra;
class=XdClass(dra);
wid= dr->xdcore.wid;
fscanf(fp,"%d %d %d %d %d\n",&dr->xdgroup.num_draget,
		&x,&y,
                &xf,&yf);
dr->xdcore.x=x;
dr->xdcore.y=y;
dr->xdgroup.xf=xf;
dr->xdgroup.yf=yf;
/*
 alloca la lista nella quale inserire i figli
*/
dr->xdgroup.dr_list= XdCreateLista();

/*
 Legge i record relativi ai figli e li crea
*/
for(i=0; i<dr->xdgroup.num_draget; i++)
        {
/*
 Richiama il metodo di read di core che si occupa di leggere
 i settaggi generali
*/
	xdgc->wid=dr->xdcore.wid;
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
        	drf=XdCreateDraget(wid,XdTagToClass(buf),gc,gc_bg);
/*
richiama il metodo per la lettura dei parametri dell'oggetto
*/
        	classf=XdClass(drf);
        	classf->xdcore_class.zoom=1.0;
        	classf->xdcore_class.read(drf,xdgc,fp);
        	ListDragetAdd(dr->xdgroup.dr_list,drf);
        	}
	}

fscanf(fp,"%s\n",buf);
if(strcmp(buf,"endgroup"))
  {
	printf("\n errore fine lettura gruppo");
	SetMsg(NULL,NULL,ERRMSG,"Caricamento del background",
        "Errore fine lettura gruppo",
	NULL,False,NULL,False,NULL);
  }
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
DragetClass class,classf;
Draget drf,drfnew;
Widget wid;
XdGroupDraget dr;
XdGroupDraget dr_dest;
dr=(XdGroupDraget)dra;
wid= dra_dest->xdcore.wid;
dr_dest=(XdGroupDraget)dra_dest;
class=XdClass(dra);
dr_dest->xdcore.x=dr->xdcore.x;
dr_dest->xdcore.y=dr->xdcore.y;
dr_dest->xdgroup.xf=dr->xdgroup.xf;
dr_dest->xdgroup.yf=dr->xdgroup.yf;
dr_dest->xdgroup.num_draget=dr->xdgroup.num_draget;
dr_dest->xdcore.filled=dr->xdcore.filled;
dr_dest->xdcore.managed= True; /* l'oggetto e' completo */
dr_dest->xdcore.selected= True; /* setta l'oggetto a selezionato */
/*
 alloca la lista nella quale inserire i figli
*/
dr_dest->xdgroup.dr_list= XdCreateLista();

/*
  Duplica i figli e li inserisce nella lista 
*/
ListDragetRew(dr->xdgroup.dr_list);
while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
        {
	classf=XdClass(drf);
/*
 Crea il duplicato dei figli
*/
	drfnew=XdCreateDraget(wid,classf,drf->xdcore.gc,drf->xdcore.gc_bg);
	classf->xdcore_class.copy(drf,drfnew);
	drfnew->xdcore.selected= False;
        ListDragetAdd(dr_dest->xdgroup.dr_list,drfnew);
	}

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
XdGroupDraget dr;
Draget drf;
DragetClass classf;
extern DragetClass xdCoreDragetClass;
dr=(XdGroupDraget)dra;
fprintf(fp,"group %d %d %d %d %d\n",dr->xdgroup.num_draget,
		dr->xdcore.x,dr->xdcore.y,
                dr->xdgroup.xf,dr->xdgroup.yf);
/*
 Scrive i record relativi agli oggetti interni al
 gruppo
*/
ListDragetRew(dr->xdgroup.dr_list);
while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
        {
	classf=XdClass(drf);
/*
 richiama il metodo di write relativo a XdCore che
 si occupa della scrittura delle informazioni relative
 ai GC (gc e gc_fg)
*/
	xdCoreDragetClass->xdcore_class.write(drf,fp);
/*
 richiama il metodo di write specifico per l'oggetto
*/
	classf->xdcore_class.write(drf,fp);
        }
/*
 scrive la label di fine gruppo
*/
fprintf(fp,"endgroup\n");
}

static void GetSize(dra,xmin,ymin,xmax,ymax)
Draget dra;
int *xmin,*ymin,*xmax,*ymax;
{
XdGroupDraget dr;
XGCValues values;
int offset;

dr=(XdGroupDraget)dra;
*xmin=(dr->xdcore.x < dr->xdgroup.xf) ? dr->xdcore.x : dr->xdgroup.xf;
*ymin=(dr->xdcore.y < dr->xdgroup.yf) ? dr->xdcore.y : dr->xdgroup.yf;

*xmax=(dr->xdcore.x > dr->xdgroup.xf) ? dr->xdcore.x : dr->xdgroup.xf;
*ymax=(dr->xdcore.y > dr->xdgroup.yf) ? dr->xdcore.y : dr->xdgroup.yf;
}

static void Modify(dra,dx,dy,dw,dh,ev)
Draget dra;
int dx,dy,dw,dh;
XEvent *ev;
{
XdGroupDraget dr;
Draget drf;
GROUP_EV *gr_ev; /* notifica un evento di ridimensionamento del gruppo
                   al singolo componente appartenente al gruppo
                */
DragetClass class,classf;
dr=(XdGroupDraget)dra;
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
	dr->xdgroup.xf+=dx;
	dr->xdgroup.yf+=dy;
/*
 propaga la traslazione ai figli
*/
	ListDragetRew(dr->xdgroup.dr_list);
	while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
       		 {
		 classf=XdClass(drf);
		 classf->xdcore_class.modify(drf,dx,dy,0,0,NULL);
       		 }
	}
else
	{
/*
  le coordinate vengono moltiplicate per il fattore di ridimensionamento
  del gruppo contenitore
*/
        dr->xdcore.x = gr_ev->xfix+gr_ev->fatt_x * (dr->xdcore.x - gr_ev->xfix);
        dr->xdcore.y = gr_ev->yfix+gr_ev->fatt_y * (dr->xdcore.y - gr_ev->yfix);
        dr->xdgroup.xf = gr_ev->xfix+
                        gr_ev->fatt_x * (dr->xdgroup.xf- gr_ev->xfix);
        dr->xdgroup.yf = gr_ev->yfix+
                        gr_ev->fatt_y * (dr->xdgroup.yf- gr_ev->yfix);
	
/*
 Propaga l'evento di modifica dimensioni del gruppo ai figli
*/
	ListDragetRew(dr->xdgroup.dr_list);
	while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
       		 {
		 classf=XdClass(drf);
		 classf->xdcore_class.modify(drf,0,0,0,0,gr_ev);
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
 Routine di creazione
*/
Draget XdCreateGroupDraget(wid, gc, gc_bg)
Widget wid; /* widget su cui effettuare il disegno */
GC gc;
GC gc_bg;
{
Draget dr;
DragetClass class;
class=(DragetClass)&xdGroupClassRec;
dr = (Draget)XdCreateDraget(wid,class,gc,gc_bg);
return(dr);
}

/*
 Routine di prima creazione del gruppo (viene chiamata
 a seguito della chiamata raggruppa: al gruppo viene passato
 un vettore contenente i draget 
 da inserire in lista ed il loro
 numero)

 I parametri passati alla funzioni sono:
	wid = indice di widget della drawing area
	dr_lista = oggetto XdLista relativi alla drawing area
*/
Draget XdFirstGroupDraget(wid,dr_lista)
Widget wid;
XdLista dr_lista;
{
float zoom;
int snap;
int num_selected,i;
Draget *list_dr_sel; /* lista dei Draget selezionati */
XdGroupDraget dr;
DragetClass class,classf;
class=(DragetClass)&xdGroupClassRec;
/*
 Verifica che vi siano oggetti selezionati da
 raggruppare: se non ve ne sono il raggruppamento non
 viene realizzato e XdGroup non creato.
*/
num_selected=ListGetSelected(dr_lista,&list_dr_sel);
if(num_selected == 0)
	{
	return(NULL);
	}
/*
 Ricava valore di zoom e di snap dal primo
 degli oggetti selezionati
*/
classf=XdClass(list_dr_sel[0]);
zoom=classf->xdcore_class.zoom;
snap=list_dr_sel[0]->xdcore.step;
/*
 Crea il draget vuoto
*/
dr=(XdGroupDraget)XdCreateDraget(wid,class,NULL,NULL);
/*
 Alloca lo spazio necessario per contenere la lista
*/
dr->xdgroup.dr_list= XdCreateLista();
/*
 inserisce i draget che sono in stato di selezione
 all'interno della lista passata come parametro
*/
dr->xdgroup.num_draget=num_selected;
dr->xdcore.step=snap;
class->xdcore_class.zoom=zoom;

for(i=0;i<num_selected; i++)
        {
/*
 Inserisce in lista e deseleziona l'oggetto
 (le connessioni non vengono incluse nel raggruppamento)
*/
        list_dr_sel[i]->xdcore.selected=False; 
	if(!XdIsConn(list_dr_sel[i]))
		{
        	ListDragetAdd(dr->xdgroup.dr_list,list_dr_sel[i]);
/*
 Elimina dalla lista di partenza il riferimanto ai draget
 trasferiti nella lista interna al XdGroup
*/
		ListDeleteDraget(dr_lista,list_dr_sel[i]);
		}
        }
XtFree(list_dr_sel);
/*
 Crea le regions di selezione, move e resize
*/
dr->xdcore.managed= True; /* l'oggetto e' completo */
dr->xdcore.selected= True; /* l'oggetto verra' visualizzato
                              come selezionato */
class->xdcore_class.crea_regions(dr);
/*
 forza il ridisegno dell'oggetto finale
*/
if(XtIsRealized(dr->xdcore.wid))
        class->xdcore_class.clear(dr);
/*
class->xdcore_class.expose(dr,NULL);
*/

return((Draget)dr);
}

/*
 XdGroupGetLista
 	ricava la lista contenuta nel Draget gruppo
*/
XdLista XdGroupGetList(dr)
Draget dr;
{
XdGroupDraget dr_group;
dr_group= (XdGroupDraget)dr;
return(dr_group->xdgroup.dr_list);
}

/*
 XdUngroupDraget - funzione che elimina un gruppo
 ripristinando la situazione precedente al raggruppamento
 Parametri:
	dr_group : Draget gruppo
	dr_lista : lista di oggetti della drawing area
*/
Boolean XdUngroupDraget(dr_group,dr_lista)
XdGroupDraget dr_group;
XdLista dr_lista;
{
int num_selected,i;
DragetClass class;
Draget drf;
class=(DragetClass)&xdGroupClassRec;
/*
 Copia i draget presenti nella lista interna sulla lista
 della drawing area
*/
ListDragetRew(dr_group->xdgroup.dr_list);
while((drf=ListDragetNext(dr_group->xdgroup.dr_list)) != NULL)
        {
        ListDragetAdd(dr_lista,drf);
	}
dr_group->xdcore.selected= False; /* l'oggetto verra' visualizzato
                              come non selezionato */
if(XtIsRealized(dr_group->xdcore.wid))
        class->xdcore_class.clear(dr_group);
/*
 Distrugge il draget group
*/
/*
 Elimina dalla lista il gruppo
*/
ListDeleteDraget(dr_lista,dr_group);
class->xdcore_class.destroy(dr_group);
class->xdcore_class.delete_regions(dr_group);
XtFree(dr_group);
}


static void CreaRegions(dr)
XdGroupDraget dr;
{
XRectangle rect_dr;
float z;
Draget drf; /* draget figli (componenti il gruppo) */
DragetClass class;
int iret,i;
Region select_region;
short delta=4;
class=XdClass(dr);
z = class->xdcore_class.zoom;
if(z>= 0.5) delta *= z;
/*
 Crea la regione di selezione come unione delle regioni
 degli oggetti che appartengono al gruppo.
*/
dr->xdcore.select_region=XCreateRegion();
ListDragetRew(dr->xdgroup.dr_list);
while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
        {
	XUnionRegion(drf->xdcore.select_region,
                dr->xdcore.select_region,
                dr->xdcore.select_region);
	}

/*
 Crea la regione di move
*/
dr->xdcore.num_move_regions=1;
dr->xdcore.move_regions=(Region *)XtCalloc(dr->xdcore.num_move_regions,sizeof(Region));
dr->xdcore.move_regions[0]=XCreateRegion();
ListDragetRew(dr->xdgroup.dr_list);
while((drf=ListDragetNext(dr->xdgroup.dr_list)) != NULL)
        {
	for(i=0; i<drf->xdcore.num_move_regions; i++)
		XUnionRegion(drf->xdcore.move_regions[i],
                dr->xdcore.move_regions[0],
                dr->xdcore.move_regions[0]);
	}
 
/*
 Crea le regioni di resize
*/
/*
 assegna le coordinate del rettangolo contenente
 il gruppo
*/
XClipBox(dr->xdcore.select_region,&rect_dr);
dr->xdcore.x=rect_dr.x/z;
dr->xdcore.y=rect_dr.y/z;
dr->xdgroup.xf=(rect_dr.x+rect_dr.width)/z;
dr->xdgroup.yf=(rect_dr.y+rect_dr.height)/z;

dr->xdcore.num_resize_regions=4;
dr->xdcore.resize_regions=(Region *)XtCalloc(dr->xdcore.num_resize_regions,sizeof(Region));
dr->xdcore.resize_regions[0]=RegionIntorno(dr->xdcore.x,dr->xdcore.y,z);
dr->xdcore.resize_regions[1]=RegionIntorno(dr->xdgroup.xf,dr->xdcore.y,z);
dr->xdcore.resize_regions[2]=RegionIntorno(dr->xdgroup.xf,dr->xdgroup.yf,z);
dr->xdcore.resize_regions[3]=RegionIntorno(dr->xdcore.x,dr->xdgroup.yf,z);
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
		XFillRectangle(XtDisplay(wid), XtWindow(wid), gc_bg,
		 	topx, topy,
                	width, height);
        XDrawRectangle(XtDisplay(wid), XtWindow(wid), drawGC, topx, topy,
                width, height);
}

