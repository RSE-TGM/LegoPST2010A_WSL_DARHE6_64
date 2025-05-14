/**********************************************************************
*
*       C Source:               XlDrawingUtil.c
*       Subsystem:              1
*       Description:
*       %created_by:    lopez %
*       %date_created:  Thu Oct 24 16:24:23 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XlDrawingUtil.c-3.1.4.2.2 %  (%full_filespec: XlDrawingUtil.c-3.1.4.2.2:csrc:1 %)";
#endif
/*
   modulo XlDrawingUtil.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlDrawingUtil.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XlDrawingUtil.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*
 *  XlDrawingUtil.c - utility per disegnare all'interno degli 
 *	              oggetti grafici Xl... .
 *                    Le cordinate variano (sia X sia Y) da 0  a  100.0
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <Xm/XmP.h>
#include <X11/StringDefs.h>
#include <Xl/XlCoreP.h>
#include <Xl/XlDrawingUtil.h>


#define DEFAULTWIDTH  50
#define DEFAULTHEIGHT 50
#define PIGRECO 3.14159265358979323846

#if defined LINUX
Display *printer=NULL;
#else
extern Display *printer;         
#endif

void gest_trasf_coor(Widget cw,int *x1,int *y1)
{
int core_width=cw->core.width;
int core_height=cw->core.height;
int app_x1;
int app_y1;
XlCoreWidget Xl_cw = (XlCoreWidget) cw;


	switch(Xl_cw->xlcore.rotate){
		case ROTATE_0:
			{
			*x1 = (float)(*x1*core_width)/100.0;
			*y1= (float)(*y1*core_height)/100.0;
			break;
			}
		case ROTATE_90:
			{
			*x1 = (float)(*x1*core_height)/100.0;
			*y1= (float)(*y1*core_width)/100.0;
			app_x1= *x1;
			app_y1= *y1;
			*x1=core_width- app_y1;
			*y1= app_x1;
			break;
			}
		case ROTATE_180:
			{
			*x1 = (float)(*x1*core_width)/100.0;
			*y1= (float)(*y1*core_height)/100.0;
			*x1= core_width - *x1;
			*y1= core_height - *y1;
			break;
			}
		case ROTATE_270:
			{
			*x1 = (float)(*x1*core_height)/100.0;
			*y1= (float)(*y1*core_width)/100.0;
			app_x1= *x1;
			app_y1= *y1;
			*x1= app_y1;
			*y1= core_height - app_x1;
			break;
			}
		}
	switch(Xl_cw->xlcore.ass_rotate){
		case NO_Y_ASS_ROTATE:
			break;
		case Y_ASS_ROTATE:
			{
			*x1=core_width- *x1;
			break;
			}
		}
}

void gest_detrasf_coor_composite(Position *x1,Position *y1,
			Dimension width_obj, Dimension height_obj,
			Dimension width, Dimension height,
			int rotate,int ass_rotate)
{
int app_x1;
int app_y1;


	switch(rotate){
		case ROTATE_0:
			{
			break;
			}
		case ROTATE_90:
			{
			app_x1= *x1;
			app_y1= *y1;
			*y1=width - app_x1 - width_obj;
			*x1=app_y1;
			break;
			}
		case ROTATE_180:
			{
			*x1= width - *x1 -width_obj ;
			*y1= height - *y1 - height_obj;
			break;
			}
		case ROTATE_270:
			{
			app_x1= *x1;
			app_y1= *y1;
			*x1= height -app_y1 - height_obj;
			*y1= app_x1;
			break;
			}
		}
	switch(ass_rotate){
		case NO_Y_ASS_ROTATE:
			break;
		case Y_ASS_ROTATE:
			{
/**
			*x1=width - *x1 - width_obj;
*/
			if((rotate == ROTATE_90) || (rotate == ROTATE_270))
				*y1=width - *y1 - width_obj;
			else
				*x1=width - *x1 - width_obj;
			break;
			}
		}
/*
	impongo che le coordinate siano positive
*/
if( *x1 < 0) *x1=0;
if( *y1 < 0) *y1=0;
}

void gest_trasf_coor_composite(Position *x1,Position *y1,
			Dimension width_obj, Dimension height_obj,
			Dimension width, Dimension height,
			int rotate,int ass_rotate)
{
int app_x1;
int app_y1;


	switch(rotate){
		case ROTATE_0:
			{
			break;
			}
		case ROTATE_90:
			{
			app_x1= *x1;
			app_y1= *y1;
			*x1=width- app_y1 - width_obj;
			*y1=app_x1;
			break;
			}
		case ROTATE_180:
			{
			*x1= width - *x1 -width_obj ;
			*y1= height - *y1 - height_obj;
			break;
			}
		case ROTATE_270:
			{
			app_x1= *x1;
			app_y1= *y1;
			*x1= app_y1;
			*y1= height -app_x1 - height_obj;
			break;
			}
		}
	switch(ass_rotate){
		case NO_Y_ASS_ROTATE:
			break;
		case Y_ASS_ROTATE:
			{
			*x1=width- *x1 - width_obj;
			break;
			}
		}
/*
	impongo che le coordinate siano positive
*/
if( *x1 < 0) *x1=0;
if( *y1 < 0) *y1=0;
}

void gest_trasf_coor_ico(int *x1,int *y1,int width, int height,
			int rotate,int ass_rotate,
			int top,int bottom,int left,int right)
{
int app_x1;
int app_y1;


	switch(rotate){
		case ROTATE_0:
			{
			break;
			}
		case ROTATE_90:
			{
			app_x1= *x1;
			app_y1= *y1;
			*x1=width- app_y1;
			*y1=app_x1;
			break;
			}
		case ROTATE_180:
			{
			*x1= width - *x1;
			*y1= height - *y1;
			break;
			}
		case ROTATE_270:
			{
			app_x1= *x1;
			app_y1= *y1;
			*x1= app_y1;
			*y1= height - app_x1;
			break;
			}
		}
	switch(ass_rotate){
		case NO_Y_ASS_ROTATE:
			break;
		case Y_ASS_ROTATE:
			{
			*x1=width- *x1;
			break;
			}
		}
}


void gest_trasf_wh(Widget cw,int *x1,int *y1,int *width,int *height)
{
int core_width=cw->core.width;
int core_height=cw->core.height;
int app_x1;
int app_y1;
int app_width;
int app_height;
XlCoreWidget Xl_cw = (XlCoreWidget) cw;



	switch(Xl_cw->xlcore.rotate){
		case ROTATE_0:
			{
			*x1 = (float)(*x1*core_width)/100.0;
			*y1= (float)(*y1*core_height)/100.0;
			*width = *width*core_width/100.0;
			*height = (float)(*height*core_height)/100.0;
			break;
			}
		case ROTATE_90:
			{
			app_x1= *x1;
			app_y1= *y1;
			app_width= *width;
			app_height= *height;
			*x1 = (float)(*x1*core_height)/100.0;
			*y1= (float)(*y1*core_width)/100.0;
			*width = (float)(app_height*core_width)/100.0;
			*height = (float)(app_width*core_height)/100.0;
			*x1=(float)(core_width- app_y1*core_width/100.0) 
				- *width;
			*y1= (float)(app_x1*core_height)/100.0;
			break;
			}
		case ROTATE_180:
			{
			*x1 = (float)(*x1*core_width)/100.0;
			*y1= (float)(*y1*core_height)/100.0;
			*width = (float)(*width*core_width)/100.0;
			*height = (float)(*height*core_height)/100.0;
			*x1= core_width - *x1 - *width;
			*y1= core_height - *y1 - *height;
			break;
			}
		case ROTATE_270:
			{
			app_y1= *y1;
			app_width= *width;
			app_height= *height;
			*x1 = (float)(*x1*core_height)/100.0;
			*y1= (float)(*y1*core_width)/100.0;
			*width = (float)(app_height*core_width)/100.0;
			*height = (float)(app_width*core_height)/100.0;
			app_x1= *x1;
			*x1= (float)(app_y1*core_width)/100.0;
			*y1= core_height - app_x1 - *height;
			break;
			}
		}
	switch(Xl_cw->xlcore.ass_rotate){
		case NO_Y_ASS_ROTATE:
			break;
		case Y_ASS_ROTATE:
			{
			*x1=core_width- *x1 - *width;
			break;
			}
		}
}


void gest_trasf_wh_ico(int *x1,int *y1,int *width,int *height,	
		int core_width,int core_height, int rotate,int ass_rotate,
			int top,int bottom,int left,int right)
{
int app_x1;
int app_y1;
int app_width;
int app_height;



	switch(rotate){
		case ROTATE_0:
			{
			break;
			}
		case ROTATE_90:
			{
			app_x1= *x1;
			app_y1= *y1;
			app_width= *width;
			app_height= *height;
			*x1 = *x1;
			*y1= *y1;
			*width = app_height;
			*height = app_width;
			*x1=core_width- app_y1 - *width;
			*y1= app_x1;
			break;
			}
		case ROTATE_180:
			{
			*x1 = *x1;
			*y1= *y1;
			*width = *width;
			*height = *height;
			*x1= core_width - *x1 - *width;
			*y1= core_height - *y1 - *height;
			break;
			}
		case ROTATE_270:
			{
			app_y1= *y1;
			app_width= *width;
			app_height= *height;
			*x1 = *x1;
			*y1= *y1;
			*width = app_height;
			*height = app_width;
			app_x1= *x1;
			*x1= app_y1;
			*y1= core_height - app_x1 - *height;
			break;
			}
		}
	switch(ass_rotate){
		case NO_Y_ASS_ROTATE:
			break;
		case Y_ASS_ROTATE:
			{
			*x1=core_width- *x1 - *width;
			break;
			}
		}
}






void gest_trasf_arc(Widget cw, int *angle1,int *angle2)
{
XlCoreWidget Xl_cw = (XlCoreWidget) cw;


	switch(Xl_cw->xlcore.rotate){
		case ROTATE_0:
			break;
		case ROTATE_90:
			{
			*angle1 -= 90*64;
			break;
			}
		case ROTATE_180:
			{
			*angle1 -= 180*64;
			break;
			}
		case ROTATE_270:
			{
			*angle1 -= 270*64;
			break;
			}
		}
	switch(Xl_cw->xlcore.ass_rotate){
		case NO_Y_ASS_ROTATE:
			break;
		case Y_ASS_ROTATE:
			{
			if((Xl_cw->xlcore.rotate==ROTATE_0)||
				(Xl_cw->xlcore.rotate==ROTATE_180))
			{
				*angle1 = 180*64 - *angle1;
				*angle2 = -(*angle2);
			}
			else
			{
				*angle1 -= 90*64;
			}
			break;
			}
		}
}


void gest_trasf_arc_ico(int *angle1,int *angle2,int rotate, int ass_rotate)
{

	switch(rotate){
		case ROTATE_0:
			break;
		case ROTATE_90:
			{
			*angle1 -= 90*64;
			break;
			}
		case ROTATE_180:
			{
			*angle1 -= 180*64;
			break;
			}
		case ROTATE_270:
			{
			*angle1 -= 270*64;
			break;
			}
		}
	switch(ass_rotate){
		case NO_Y_ASS_ROTATE:
			break;
		case Y_ASS_ROTATE:
			{
			if((rotate==ROTATE_0)||
				(rotate==ROTATE_180))
			{
				*angle1 = 180*64 - *angle1;
				*angle2 = -(*angle2);
			}
			break;
			}
		}
}


/*
	Scrive un testo ruotabile.
            
        Le coordinate x1,y1 sono relative al centro del rettangolo
        contenete la stringa di testo

*/

/*
E' stato introdotto un GC specifico per la stampante
Tale GC DEVE essere eliminato dopo essere stato utilizzato
by Fabio
*/

static GC gc_testoScr0=NULL;
static GC gc_testoScr1=NULL;
static GC gc_testo_printer=NULL;
static unsigned long valuemask= GCForeground | GCBackground ;

void
XlTesto(Widget cw,Drawable drawable,GC gc,int x1,int y1,char *testo,
	XFontStruct *font_info)
{
char *c=testo;
int nchar=0;
XlCoreWidget Xl_cw = (XlCoreWidget) cw;
int core_width=cw->core.width;
int core_height=cw->core.height;
int ascent=font_info->ascent;
int descent=font_info->descent;
int width;
int app_x = x1;
int app_y = y1;
Position offX,offY;
GC *pgc_testo=NULL;
XGCValues values;


   if(printer)
   {
      gc_testo_printer=XCreateGC(XlDisplay(cw),(Drawable)XlWindow(cw),0,NULL);
      pgc_testo = &gc_testo_printer;
   }
   else
   {
     gc_testoScr0 = DefaultGC(XtDisplay(cw),XScreenNumberOfScreen( XtScreen(cw)) );
     pgc_testo = &gc_testoScr0;
   }
      


   XCopyGC(XlDisplay(cw),gc,valuemask,*pgc_testo);
   XSetFont(XlDisplay(cw),*pgc_testo,font_info->fid);
   offX=XlPrintOffsetX(cw);
   offY=XlPrintOffsetY(cw);

   while(c[nchar]!=0)
       	nchar++;

   gest_trasf_coor(cw,&app_x,&app_y);
   width=XTextWidth(font_info,testo,strlen(testo));
   app_x = app_x - width/2;

   app_y = app_y -(ascent+descent)/2 + ascent;
   XDrawString( XlDisplay(cw), drawable, *pgc_testo, app_x+offX, app_y+offY,
		 testo, strlen(testo));

   if( printer )
        XFreeGC(XlDisplay(cw),gc_testo_printer);

}

void
XlTestoSimple(Widget cw,Drawable drawable,GC gc,int x1,int y1,char *testo,
        XFontStruct *font_info)
{
char *c=testo;
int nchar=0;
XlCoreWidget Xl_cw = (XlCoreWidget) cw;
int core_width=cw->core.width;
int core_height=cw->core.height;
int ascent=font_info->ascent;
int descent=font_info->descent;
int width;
int app_x = x1;
int app_y = y1;
Position offX,offY;
XGCValues values;

GC *pgc_testo=NULL;


   if(printer)
   {
      gc_testo_printer=XCreateGC(XlDisplay(cw),(Drawable)XlWindow(cw),0,NULL);
      pgc_testo = &gc_testo_printer;
   }
   else
   {
     gc_testoScr0 = DefaultGC(XtDisplay(cw),XScreenNumberOfScreen( XtScreen(cw)) );
     pgc_testo = &gc_testoScr0;
   }

   XCopyGC(XlDisplay(cw),gc,valuemask,*pgc_testo);
   XSetFont(XlDisplay(cw),*pgc_testo,font_info->fid);

	offX=XlPrintOffsetX(cw);
	offY=XlPrintOffsetY(cw);


        gest_trasf_coor(cw,&app_x,&app_y);
        app_x = app_x;
        app_y = app_y -(ascent+descent)/2 + ascent;
        XDrawString( XlDisplay(cw), drawable, *pgc_testo, app_x+offX, app_y+offY,
                 testo, strlen(testo));
   if(printer)
        XFreeGC(XlDisplay(cw),gc_testo_printer);
}

void
XlTestoSimpleCentre(Widget cw,Drawable drawable,GC gc,int x1,int y1,char *testo,
        XFontStruct *font_info)
{
char *c=testo;
int nchar=0;
XlCoreWidget Xl_cw = (XlCoreWidget) cw;
int core_width=cw->core.width;
int core_height=cw->core.height;
int ascent=font_info->ascent;
int descent=font_info->descent;
int width;
int app_x = x1;
int app_y = y1;
int size;
Position offX,offY;
GC *pgc_testo=NULL;
XGCValues values;


   if(printer)
   {
      gc_testo_printer=XCreateGC(XlDisplay(cw),(Drawable)XlWindow(cw),0,NULL);
      pgc_testo = &gc_testo_printer;
   }
   else
   {
     gc_testoScr0 = DefaultGC(XtDisplay(cw),XScreenNumberOfScreen( XtScreen(cw)) );
     pgc_testo = &gc_testoScr0;
   }

   XCopyGC(XlDisplay(cw),gc,valuemask,*pgc_testo);
   XSetFont(XlDisplay(cw),*pgc_testo,font_info->fid);

	offX=XlPrintOffsetX(cw);
	offY=XlPrintOffsetY(cw);


	size=XTextWidth(font_info,testo,strlen(testo));
        gest_trasf_coor(cw,&app_x,&app_y);
        app_x = app_x-size/2;
	if(app_x<0)
		app_x=0;
        app_y = app_y -(ascent+descent)/2 + ascent;
        XDrawString( XlDisplay(cw), drawable, *pgc_testo, app_x+offX, app_y+offY,
                 testo, strlen(testo));

   if( printer )
      XFreeGC(XlDisplay(cw),gc_testo_printer);

}


/*
	Scrive un testo ruotabile.
            
        Le coordinate x1,y1 sono relative al centro del rettangolo
        contenete la stringa di testo

                   ----------
		   |  ***** |
		   |    *   |
		   |    *   |
  	 (x1,y1)   |    *   |
		-->x    *   |
		   |    *   |
		   |    *   |
		   |    *   |
		   |  ***** |
                   ----------
*/

void XlTestoRot(Widget cw,Drawable drawable,GC gc,int x1,int y1,char *testo,
        XFontStruct *font_info)
{
char *c=testo;
int nchar=0;
int i;
int step;
char app_t[10];
int width;
int app_x = x1;
int app_y = y1;
Position offX,offY;
int base;
int core_width=cw->core.width;
int core_height=cw->core.height;
XlCoreWidget Xl_cw = (XlCoreWidget) cw;
GC *pgc_testo=NULL;
XGCValues values;


   if(printer)
   {
      gc_testo_printer=XCreateGC(XlDisplay(cw),(Drawable)XlWindow(cw),0,NULL);
      pgc_testo = &gc_testo_printer;
   }
   else
   {
     gc_testoScr0 = DefaultGC(XtDisplay(cw),XScreenNumberOfScreen( XtScreen(cw)) );
     pgc_testo = &gc_testoScr0;
   }

   XCopyGC(XlDisplay(cw),gc,valuemask,*pgc_testo);
   XSetFont(XlDisplay(cw),*pgc_testo,font_info->fid);

   if((Xl_cw->xlcore.rotate==ROTATE_0)||(Xl_cw->xlcore.rotate==ROTATE_180))
	width=font_info->max_bounds.width*100.0/core_width;
   else
	width=(font_info->max_bounds.ascent+font_info->max_bounds.descent)*
			100.0/core_height;

   if(width<=0)
	width=1;

   while(c[nchar]!=0)
        nchar++;

   base = x1-width*nchar/2;
   for(i=0;i<nchar;i++)
        {
        sprintf(app_t,"%c",c[i]);
        XlTesto(cw,drawable,*pgc_testo,base,y1,app_t, font_info);
	base += width;
        }

   if( printer )
       XFreeGC(XlDisplay(cw),gc_testo_printer);
}

void gest_trasf_testo(Widget cw,int *x1,int *y1, char *testo, 
	XFontStruct *font_info)
{
XlCoreWidget Xl_cw = (XlCoreWidget) cw;
int width,height,ascent,descent;

	gest_trasf_coor(cw,x1,y1);
	ascent=font_info->ascent;
	descent=font_info->descent;
	width=font_info->max_bounds.width;
	height=ascent + descent;
	switch(Xl_cw->xlcore.rotate){
		case ROTATE_0:
			{
			*y1 = *y1 - height/2 + ascent ;
			break;
			}
		case ROTATE_90:
			{
			*x1 = *x1 - width/2;
			*y1 = *y1 + ascent;
			break;
			}
		case ROTATE_180:
			{
			*x1 = *x1 - width;
			*y1 = *y1 - height/2 + ascent ;
			break;
			}
		case ROTATE_270:
			{
			*x1 = *x1 - width/2;
			*y1 = *y1 + ascent;
			break;
			}
		}
	switch(Xl_cw->xlcore.ass_rotate){
		case NO_Y_ASS_ROTATE:
			{
			break;
			}
		case Y_ASS_ROTATE:
			{
			if(Xl_cw->xlcore.rotate==ROTATE_0)
				*x1 = *x1 - width;
			if(Xl_cw->xlcore.rotate==ROTATE_180)
				*x1 = *x1 + width;
			break;
			}
		}
}

void
XlRiempiRettangolo(Widget cw,Drawable drawable,GC gc,
                        int x1,int y1,int width, int height)
{
Position offX,offY;

	offX=XlPrintOffsetX(cw);
	offY=XlPrintOffsetY(cw);

/*
Verifico che l' oggetto sia o XlCore od un suo figlio
*/
        if(XlIsXlCore(cw))
           gest_trasf_wh(cw,&x1,&y1,&width,&height);

        XFillRectangle(XlDisplay(cw),drawable, gc,x1+offX,y1+offY,width,height);
}

void
XlRettangolo(Widget cw,Drawable drawable,GC gc,
                        int x1,int y1,int width, int height)
{
Position offX,offY;

	offX=XlPrintOffsetX(cw);
	offY=XlPrintOffsetY(cw);
        gest_trasf_wh(cw,&x1,&y1,&width,&height);
        XDrawRectangle(XlDisplay(cw),drawable, gc,x1+offX,y1+offY,width,height);
}

void
XlArco(Widget cw,Drawable drawable,GC gc,int x1,int y1,int width, int height,
        int angle1, int angle2)
{
Position offX,offY;

	offX=XlPrintOffsetX(cw);
	offY=XlPrintOffsetY(cw);

         gest_trasf_wh(cw,&x1,&y1,&width,&height);
         gest_trasf_arc(cw,&angle1,&angle2);
         XDrawArc(XlDisplay(cw),drawable,gc,x1+offX,y1+offY,width,height,angle1,angle2);
}
void
XlRiempiArco(Widget cw,Drawable drawable,GC gc,int x1,int y1,
	int width, int height,int angle1, int angle2)
{
Position offX,offY;

	offX=XlPrintOffsetX(cw);
	offY=XlPrintOffsetY(cw);

         gest_trasf_wh(cw,&x1,&y1,&width,&height);
         gest_trasf_arc(cw,&angle1,&angle2);
         XFillArc(XlDisplay(cw),drawable,gc,x1+offX,y1+offY,width,height,angle1,angle2);
}

void
XlLinea(Widget cw,Drawable drawable,GC gc,int x1,int y1,int x2,int y2)
{
Position offX,offY;

	offX=XlPrintOffsetX(cw);
	offY=XlPrintOffsetY(cw);
        gest_trasf_coor(cw,&x1,&y1);
        gest_trasf_coor(cw,&x2,&y2);
        XDrawLine(XlDisplay(cw),drawable,gc,x1+offX,y1+offY,x2+offX,y2+offY);
}

