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
 XdCore - superclass per tutti gli oggetti di disegno
*/
#include <Xm/Xm.h>

#include <stdio.h>
#include <stdlib.h>
#include <Xd/Xd.h>
#include <Xd/XdCoreP.h>
#include <Xl/Xl.h>

/*
 Dichiarazione dei metodi
*/
static void Initialize();
static void ClassInitialize();
static void Destroy();
static Boolean Resize();
static void Redraw();
static Boolean Pick();
static void Select();
static Boolean Read();
static void Write();
#ifdef XPRINTER_USED
static void Print();
#endif
static void DeleteRegions();

#define FILTRA_READ  0
#define FILTRA_WRITE 1
/*
 Inizializzazione del class record
*/
XdCoreClassRec xdCoreClassRec = {
	{ /* xdcore fields */
	  /* initialized */	False,
	  /* class_name */ 	"XdCore",
	  /* superclass */	NULL,
	  /* gcxor      */      NULL,
	  /* gcsel      */      NULL,
	  /* zoom       */	1.0,
	  /* draget size */	sizeof(XdCoreRec),
	  /* class_init */	ClassInitialize,
	  /* initialize */	Initialize,
	  /* destroy    */	Destroy,
	  /* resize     */	Resize,
	  /* end_resize */	NULL,
	  /* move       */      NULL,
	  /* end_move   */      NULL,
	  /* expose     */      Redraw,
	  /* first_point */	NULL,
	  /* last_point  */	NULL,
	  /* first_draw  */     NULL,
          /* pick       */ 	Pick,
	  /* select     */	Select,
	  /* clear      */      NULL,
	  /* crea_regions */    NULL,
	  /* delete_regions */  DeleteRegions,
	  /* read	*/	Read,
	  /* write	*/	Write,
 	  /* get_size   */      NULL,
	  /* modify     */      NULL,
          /* copy       */      NULL,
#ifdef XPRINTER_USED
	  /* print      */      Print
#endif
	}
	};

DragetClass xdCoreDragetClass = (DragetClass) &xdCoreClassRec;

/*
 Metodi
*/

static void ClassInitialize(dr)
Draget dr;
{
DragetClass class;
class= XdClass(dr);
/*
 Setta il GC per il disegno in xor dell'oggetto in costruzione
*/
/*
 per ottenere un disegno in nero deve tener conto del background
 della window su cui si sta disegnando
*/
class->xdcore_class.gcxor = XdGetXorGC(dr->xdcore.wid);
/*
 GC per disegno oggetto selezionato
*/
class->xdcore_class.gcsel = XdGetCopyGC(dr->xdcore.wid);
}

static void DeleteRegions(dr)
Draget dr;
{
int i;
if(dr->xdcore.select_region)
	XDestroyRegion(dr->xdcore.select_region);
for(i=0;i <dr->xdcore.num_move_regions; i++)
	if(dr->xdcore.move_regions[i])
		XDestroyRegion(dr->xdcore.move_regions[i]);
XtFree(dr->xdcore.move_regions);
for(i=0;i <dr->xdcore.num_resize_regions; i++)
	if(dr->xdcore.resize_regions[i])
		XDestroyRegion(dr->xdcore.resize_regions[i]);
XtFree(dr->xdcore.resize_regions);
}

static void Initialize(dr)
Draget dr;
{
}


static void Destroy(dr)
Draget dr;
{
printf("\n richiamato destroy DrCore");
}

static Boolean Resize(ev)
XEvent *ev;
{
printf("\n richiamato resize DrCore");
}

static void Redraw(dr,ev)
Draget dr;
XEvent *ev;
{
printf("\n richiamato expose DrCore");
}

static Boolean Pick(dr,ev,type)
Draget dr;
XEvent *ev;
Boolean type;
{
int iret,i;
DragetClass class;
Boolean selected;
int x,y;
class= XdClass(dr);
x=ev->xbutton.x;
y=ev->xbutton.y;
selected= XPointInRegion(dr->xdcore.select_region,x,y);
/*
 Tratta i casi in cui cambia lo stato dell'oggetto
*/
/*
 Passaggio da non selezionato a selezionato
*/
if(selected && !dr->xdcore.selected)
        {
        class->xdcore_class.select(dr,True,True);
        }
/*
 Passaggio da selezionato a non selezionato
 ( solo se la selezione non e' del tipo
   PICK_EXTENDED )
*/
else if (type != PICK_EXTENDED && !selected && dr->xdcore.selected)
        {
        class->xdcore_class.select(dr,False,True);
        }
/*
 Esamina se il punto e' in una regione di move
*/
for(i=0;i< dr->xdcore.num_move_regions; i++)
	if(XPointInRegion(dr->xdcore.move_regions[i],x,y))	
		{
		dr->xdcore.moving=True;
		dr->xdcore.num_move=i;
		}
/*
 Esamina se il punto e' in una regione di resize
*/
for(i=0;i< dr->xdcore.num_resize_regions; i++)
        if(XPointInRegion(dr->xdcore.resize_regions[i],x,y))      
                {
		selected=True; /* aggiunta per gestione groups */
                dr->xdcore.resizing=True;
                dr->xdcore.num_resize=i;
                }
/*
 Setta il flag che notifica l'inizio di una operazione di move
 o di resize
*/
if(dr->xdcore.moving || dr->xdcore.resizing)
	{
	dr->xdcore.is_first=True;
	}
/*
return(dr->xdcore.selected);
*/
return(selected);
}


static void Select(dr,flag,do_expose)
Draget dr;
Boolean flag;
Boolean do_expose;
{
DragetClass class;
class= XdClass(dr);
if(flag == True && dr->xdcore.selected== False) /* selezione */
        {
        dr->xdcore.selected= flag;
/*
        class->xdcore_class.expose(dr,NULL);
*/
	if (do_expose)
        	class->xdcore_class.clear(dr);
        }
else if( flag==False && dr->xdcore.selected== True) /* deselezione */
/*
        forza un refresh della zona selezionata
*/
        {
        dr->xdcore.selected= flag;
	if (do_expose)
        	class->xdcore_class.clear(dr);
        }
}


static Boolean Read(dr,xdgc,fp)
Draget dr;
XdGC *xdgc;
FILE *fp;
{
char buf[10],str_color[50];
int filled;
/*
 ricava gli attributi del contesto di disegno:
	- ampiezza del contorno
	- stile di disegno contorno (linea continua o tratteggiata)
	- colore di foreground contorno
	- colore di background contorno
	- colore di filling
	- attributo di filled
*/
if(fscanf(fp,"%s %d\n",buf, &xdgc->width_contorno)!=2)
	return(False);
fscanf(fp,"%s %d\n",buf, &xdgc->style_contorno);
fscanf(fp,"%s %s",buf,str_color);
XdFilterAnimated(FILTRA_READ,str_color);
xdgc->fg_contorno=XdStringToPixel(xdgc->wid,str_color);
fscanf(fp,"%s %s",buf,str_color);
XdFilterAnimated(FILTRA_READ,str_color);
xdgc->bg_contorno=XdStringToPixel(xdgc->wid,str_color);
fscanf(fp,"%s %s",buf,str_color);
XdFilterAnimated(FILTRA_READ,str_color);
xdgc->fg_fill=XdStringToPixel(xdgc->wid,str_color);
fscanf(fp,"%s %d",buf,&filled);
if(filled) xdgc->filled=True;
else  xdgc->filled=False;
return(True);
}

static void Write(dr,fp)
Draget dr;
FILE *fp;
{
Display *display;
unsigned long valuemask= GCForeground | GCBackground | GCLineWidth
                         | GCLineStyle;
XGCValues values;
extern  char *XdPixelToString(Widget,Pixel);
char *str_color;
/*
 ricava gli attributi del contenuti in gc
	- ampiezza del contorno
	- stile di disegno contorno (linea continua o tratteggiata)
	- colore di foreground contorno
	- colore di background contorno
*/
display=XtDisplay(dr->xdcore.wid);
/*
 Caso in cui il gc non e' definito: Caso di oggetto gruppo
 Vengono scritti valori pari a 0
*/
if(dr->xdcore.gc ==NULL)
	{
	fprintf(fp,"wi_c 0\n");
	fprintf(fp,"st_c 0\n");
	fprintf(fp,"fg_c #000000000000\n");
	fprintf(fp,"bg_c #000000000000\n");
	fprintf(fp,"fg_f #000000000000\n");
	fprintf(fp,"fill 0\n");
	}
else
	{
	XGetGCValues(display,dr->xdcore.gc,valuemask,&values);

	fprintf(fp,"wi_c %d\n", values.line_width);
	fprintf(fp,"st_c %d\n", values.line_style);

	str_color=XdPixelToString(dr->xdcore.wid,(Pixel)values.foreground);
	XdFilterAnimated(FILTRA_WRITE,str_color);
	fprintf(fp,"fg_c %s\n", str_color);
	XtFree(str_color);

	str_color=XdPixelToString(dr->xdcore.wid,(Pixel)values.background);
	XdFilterAnimated(FILTRA_WRITE,str_color);
	fprintf(fp,"bg_c %s\n", str_color);
	XtFree(str_color);

/*
 ricava gli attributi contenuti in gc_bg
	- colore di filling
	- attributo di filled
*/
	valuemask= GCForeground;
	XGetGCValues(display,dr->xdcore.gc_bg,valuemask,&values);

	str_color=XdPixelToString(dr->xdcore.wid,(Pixel)values.foreground);
	XdFilterAnimated(FILTRA_WRITE,str_color);
	fprintf(fp,"fg_f %s\n", str_color);
	XtFree(str_color);

	fprintf(fp,"fill %d\n", dr->xdcore.filled);
	}
}

#ifdef XPRINTER_USED
static void Print(dr,flag)
Draget dr;
Boolean flag;
{
static GC gc_save,gc_bg_save;
Display *display;
unsigned long valuemask= GCForeground | GCBackground | GCLineWidth
                         | GCLineStyle;
XGCValues values;
XGCValues values_print;
extern  char *XdPixelToString(Widget,Pixel);
char *str_color;
/*
 ricava gli attributi del contenuti in gc
	- ampiezza del contorno
	- stile di disegno contorno (linea continua o tratteggiata)
	- colore di foreground contorno
	- colore di background contorno
*/
display=XtDisplay(dr->xdcore.wid);
/*
 Caso di oggetto gruppo
 Non viene effettuata nessuna operazione sui gc.
*/
if(XdIsGroup(dr))
	return;
if(flag==True)
	{
	gc_save=dr->xdcore.gc;
	gc_bg_save=dr->xdcore.gc_bg;

	XGetGCValues(display,dr->xdcore.gc,valuemask,&values);
	values_print.foreground = XlPrintGetPixel(dr->xdcore.wid, values.foreground);
   	values_print.background = XlPrintGetPixel(dr->xdcore.wid, values.background);
	values_print.line_width= values.line_width;
	values_print.line_style= values.line_style;
	dr->xdcore.gc=XCreateGC(XlDisplay(dr->xdcore.wid),
					XlWindow(dr->xdcore.wid),
					valuemask,&values_print);

	XGetGCValues(display,dr->xdcore.gc_bg,valuemask,&values);
	values_print.foreground = XlPrintGetPixel(dr->xdcore.wid, values.foreground);
   	values_print.background = XlPrintGetPixel(dr->xdcore.wid, values.background);
	values_print.line_width= values.line_width;
	values_print.line_style= values.line_style;
	dr->xdcore.gc_bg=XCreateGC(XlDisplay(dr->xdcore.wid),
					XlWindow(dr->xdcore.wid),
					valuemask,&values_print);

	}
else
	{
	XFreeGC(XlDisplay(dr->xdcore.wid),dr->xdcore.gc);
	XFreeGC(XlDisplay(dr->xdcore.wid),dr->xdcore.gc_bg);
	dr->xdcore.gc=gc_save;
	dr->xdcore.gc_bg=gc_bg_save;
	}
}
#endif
/*
 XdFilterAnimated 
	esamina se un colore fa parte dei 'falsi colori' utilizzati
 	per rappresentare la parte di disegno animato.
  	Questa routine va sostituita in caso vengano modificati i falsi
	colori.
*/
XdFilterAnimated(type,str_color)
int type;
char *str_color;
{
static char* tabella_colori[4]= { "#dddddddddddd", "#bbbbbbbbbbbb",
				  "#999999999999", "#777777777777"};
int num_color;
int i;
if(type == FILTRA_WRITE)
	{
   	for(i=0; i<4; i++)
		if (strcmp(str_color, tabella_colori[i]) == 0)
			{
			sprintf(str_color,"@%d",i+1);
			break;
			}
	}
else if (type == FILTRA_READ)
	{
	if (str_color[0]=='@')
		{
		sscanf(&str_color[1],"%d",&num_color);
		if(num_color <1 || num_color>4)
			{
			printf("\n indice var. d'animazione scorretto");
			printf("\n inserito indice = 1");
			num_color=1;
			}
		strcpy(str_color, tabella_colori[num_color-1]);
		}
	}
}

Draget XdCreateCoreDraget(wid,gc)
Widget wid; /* widget su cui effettuare il disegno */
GC gc;
{
Draget dr;
DragetClass class;
dr=(Draget)XtCalloc(1,sizeof(XdCoreRec));
if(dr==NULL)
        {
        printf("\n impossibile creare Draget");
        }
dr->xdcore.draget_class= &xdCoreClassRec;
dr->xdcore.wid=wid;
dr->xdcore.gc=gc;
/*
 Se la classe cui appartiene l'oggetto non e' stata inizializzata
 la inizializza
*/
class= XdClass(dr);
if(class->xdcore_class.initialized == False)
	{
	class->xdcore_class.class_initialize(dr);
	class->xdcore_class.initialized= True;
	}
}
