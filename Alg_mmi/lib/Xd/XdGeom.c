/**********************************************************************
*
*       C Source:               XdGeom.c
*       Subsystem:              1
*       Description:
*       %created_by:    furlani %
*       %date_created:  Fri Jun 18 15:22:49 1999 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XdGeom.c-3 %  (%full_filespec: XdGeom.c-3:csrc:1 %)";
#endif
/*
   modulo XdGeom.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdGeom.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XdGeom.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/* XdGeom.c
 *      Routines per la grafica
 *      utilizzate all'interno dei Draget
 */
#include <Xm/Xm.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Rt/RtMemory.h>

Region RegionIntorno(Position,Position,float);
Region RegionIntorno(Position x,Position y,float z)
{
XPoint points[5];
short delta=2;
/* fissato delta indipendente dallo zoom
if(z>= 0.5) delta *= z;
*/
points[0].x= z*x-delta;
points[0].y= z*y+delta;
points[1].x= z*x+delta;
points[1].y= z*y+delta;
points[2].x= z*x+delta;
points[2].y= z*y-delta;
points[3].x= z*x-delta;
points[3].y= z*y-delta;
points[4]= points[0];
return(XPolygonRegion(points,5,WindingRule));
}


Region RegionClip(ev)
XEvent *ev;
{
XRectangle rectangle;
Region region;
rectangle.x=ev->xexpose.x;
rectangle.y=ev->xexpose.y;
rectangle.width= (unsigned short) ev->xexpose.width;
rectangle.height= (unsigned short) ev->xexpose.height;
region=XCreateRegion();
XUnionRectWithRegion(&rectangle,region,region);
return(region);
}

/*
 Crea una regione rettangolare in corrispondenza al rettangolo piu'
 piccolo circoscritto ad una regione data
*/
Region RegionClipBox(region_inp)
Region region_inp;
{
Region region;
XRectangle rectangle;
XClipBox(region_inp, &rectangle);
region=XCreateRegion();
XUnionRectWithRegion(&rectangle,region,region);
return(region);
}

Region RegionLineIntorno(Position xin,Position yin,Position xfin,Position yfin,float z)
{
int dx,dy;
XPoint points[5];
float sinalfa; /* coeff. angolare retta */
float cosalfa;
int delta=2;
double ipoten;
ipoten=pow((double)(yfin-yin),(double)2)+pow((double)(xfin-xin),(double)2);
ipoten=sqrt(ipoten);
if(ipoten!=0)
	{
	sinalfa=((double)(yfin-yin))/ipoten;
	cosalfa=((double)(xfin-xin))/ipoten;
	}
else
	sinalfa=cosalfa=0;
dx= delta*sinalfa;
dy= delta*cosalfa;
/*
 Crea la regione di selezione
*/
points[0].x= z*xin-dx;
points[0].y= z*yin+dy;
points[1].x= z*xfin-dx;
points[1].y= z*yfin+dy;
points[2].x= z*xfin+dx;
points[2].y= z*yfin-dy;
points[3].x= z*xin+dx;
points[3].y= z*yin-dy;
points[4]= points[0];
return(XPolygonRegion(points,5,WindingRule));
}


Region RegionRectIntorno(x1,y1,x2,y2,z)
Position x1,y1,x2,y2;
float z;
{
int  width, height, topx, topy;
int i;
XRectangle rect[4];
int d=2;  /* delta */
Region reg;
x1= x1*z;
y1= y1*z;
x2= x2*z;
y2= y2*z;
/*
 Crea la regione di selezione come anello rettangolare
 facendo la union di 4 rettangoli
*/
reg=XCreateRegion();
 /* find top left corner */
topx= (x1 < x2) ? x1 : x2;
topy= (y1 < y2) ? y1 : y2;

width= abs(x1-x2);
height= abs(y1-y2);

rect[0].x= topx-d;
rect[0].y= topy-d;
rect[0].width = width+ 2*d;
rect[0].height = 2*d;

rect[1].x= topx-d;
rect[1].y= topy-d;
rect[1].width = 2*d;
rect[1].height = height + 2*d;

rect[2].x= topx-d;
rect[2].y= topy +height -d;
rect[2].width = width+ 2*d;
rect[2].height = 2*d;

rect[3].x= topx + width -d;
rect[3].y= topy-d;
rect[3].width = 2*d;
rect[3].height = height + 2*d;

for(i=0; i< 4; i++)
	XUnionRectWithRegion(&rect[i],reg,reg);
return(reg);
}

/*
 Regione da utilizzarsi per la selezione del cerchio o dell'arco:
 versione provvisoria
*/

Region RegionCircleIntorno(x1,y1,x2,y2,z)
Position x1,y1,x2,y2;
float z;
{
int  width, height, topx, topy;
int i;
XRectangle rect[4];
int d;  /* delta */
Region reg;

short delta=5;
if(z>= 0.5) delta *= z;
x1= x1*z;
y1= y1*z;
x2= x2*z;
y2= y2*z;
/*
 Crea la regione di selezione come anello rettangolare
 facendo la union di 4 rettangoli
*/
reg=XCreateRegion();
 /* find top left corner */
topx= (x1 < x2) ? x1 : x2;
topy= (y1 < y2) ? y1 : y2;

width= abs(x1-x2);
height= abs(y1-y2);

d= height/3;
rect[0].x= topx-delta;
rect[0].y= topy-delta;
rect[0].width = width+2*delta;
rect[0].height = d;

d= width/3;
rect[1].x= topx-delta;
rect[1].y= topy-delta;
rect[1].width = d;
rect[1].height = height+2*delta;

d= height/3;
rect[2].x= topx-delta;
rect[2].y= topy+height+delta-d;
rect[2].width = width+2*delta;
rect[2].height = d;

d= width/3;
rect[3].x= topx + width+delta-d;
rect[3].y= topy-delta;
rect[3].width = d;
rect[3].height = height+2*delta;

for(i=0; i< 4; i++)
	XUnionRectWithRegion(&rect[i],reg,reg);
return(reg);
}




/*
 XdGetXorGC
   ricava in base al colore di background della window su cui si disegna
   un colore adatto alla visualizzazione di spostamenti e ridimensionamenti 
   (rubber)
*/ 
GC XdGetXorGC(wid)
Widget wid;
{
XGCValues values;
XColor Colore,Col;
unsigned int sommaColor;
Colormap cmap;
Display *display;
unsigned long valuemask= GCForeground | GCLineStyle | GCFunction
                          | GCSubwindowMode;
display= XtDisplay(wid);
/*
 Setta il GC per il disegno in xor dell'oggetto in costruzione
*/
/*
 per ottenere un disegno in nero deve tener conto del background
 della window su cui si sta disegnando
*/
get_something(wid, XmNbackground, &Colore.pixel);
get_something(wid, XmNcolormap, &cmap);
XQueryColor (display, cmap, &Colore);
values.function = GXxor;
printf("DEBUG: XdGeom back red =%x green=%x blue=%x\n",Colore.red,Colore.green,Colore.blue);
sommaColor= Colore.red + Colore.green + Colore.blue;

/*
A seconda del tipo di bkg foreground chiaro o scuro
*/
if( sommaColor < (32000 * 3))
        {
#ifndef NUTC
        values.foreground =  BlackPixel(display,0) ^ Colore.pixel;
#endif
        Colore.red = Colore.red ^ 0xff00;
        Colore.green = Colore.green ^ 0xff00;
        Colore.blue = Colore.blue ^ 0xff00;
        if( !XAllocColor( display, cmap, &Colore))
          {
          fprintf(stderr,"ERROR: Impossible to allocate color\n");
          }
        values.foreground =  Colore.pixel;
        }
else
        {
#ifndef NUTC
        values.foreground =  BlackPixel(display,0) ^ Colore.pixel;
#endif
        Colore.red = Colore.red ^ 0;
        Colore.green = Colore.green ^ 0;
        Colore.blue = Colore.blue ^ 0;
        if( !XAllocColor( display, cmap, &Colore))
          {
          fprintf(stderr,"ERROR: Impossible to allocate color\n");
          }
        values.foreground =  Colore.pixel;
        }


values.line_style = LineSolid;
values.subwindow_mode= IncludeInferiors;
return(XtGetGC(wid,valuemask,&values));

}


/*
 XdGetCopyGC
   ricava in base al colore di background della window su cui si disegna
   un colore adatto alla visualizzazione della selezione di un oggetto
*/
GC XdGetCopyGC(wid)
Widget wid;
{
XGCValues values;
XColor Colore;
unsigned int sommaColor;
Colormap cmap;
Display *display;
unsigned long valuemask= GCForeground | GCLineStyle | GCFunction
                          | GCSubwindowMode;
display= XtDisplay(wid);
/*
 Setta il GC per il disegno in xor dell'oggetto in costruzione
*/
/*
 per ottenere un disegno in nero deve tener conto del background
 della window su cui si sta disegnando
*/
get_something(wid, XmNbackground, &Colore.pixel);
get_something(wid, XmNcolormap, &cmap);
XQueryColor (display, cmap, &Colore);
values.function = GXcopy;
sommaColor= Colore.red + Colore.green + Colore.blue;
if( sommaColor < (32000 * 3))
        values.foreground =  WhitePixel(display,0);
else
        values.foreground =  BlackPixel(display,0);

values.line_style = LineSolid;
values.subwindow_mode= IncludeInferiors;
return(XtGetGC(wid,valuemask,&values));
}

/*
 IntersectRectangle 
 ritorna True se due rettangoli (di cui si passano posizione e ampiezze)
 si intersecano
*/ 
Boolean XdIntersectRectangle(int x1,int y1,int w1,int h1,
                           int x2,int y2,int w2,int h2)
{
/*
 coordinate dei centri dei due rettangoli
*/
int c1x,c2x; /* ascisse dei due centri */ 
int c1y,c2y; /* ordinate dei due centri */
/*
 calcolo coordinate centri
*/
c1x=x1+w1/2;
c2x=x2+w2/2;
c1y=y1+h1/2;
c2y=y2+h2/2;
/*
 I due rettangoli si intersecano se si intersecano le loro
 proiezioni sugli assi delle ascisse e delle coordinate.
 Le proiezioni si intersecano se la distanza tra i centri 
 e' inferiore alla somma della meta' delle due ampiezze.
*/
if(((c2x-c1x)*(c2x-c1x)<=(w1/2+w2/2)*(w1/2+w2/2))&&
        ((c2y-c1y)*(c2y-c1y)<=(h1/2+h2/2)*(h1/2+h2/2)))
        return(True);
else
        return(False);
}
           
