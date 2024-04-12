/**********************************************************************
*
*       C Source:               draw.c
*       Subsystem:              2
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 12:13:04 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: draw.c,2 %  (%full_filespec: 2,csrc,draw.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)draw.c	2.7\t4/11/95";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/cursorfont.h>
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/List.h>
#include <Xm/Text.h>
#include <Xm/SeparatoG.h>
#include <Xm/DialogS.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>
#include <Xm/BulletinB.h>
#include <Xm/ToggleB.h>

#include "macro.h"
#include "ico_mesg.h"
#include "libutilx.h"
#ifdef VMS
#define M_PI        3.14159265358979323846
#endif 

short round_mio(double);

/* VARIABILI UTILIZZATE NELLE FUNZIONI Xlib */
extern Display *display;
extern int screen;
extern Cursor cursore_a_crocetta;
extern GC xorGC, iconGC, lineGC;

extern Pixel apix[];

/* VARIABILI DI WIDGET */
extern Widget top_level;

extern Arg args[20];
extern Cardinal nargs;

extern Boolean snap_status;
extern int snap_val;

extern Boolean modifiche;
extern char *warning_mesg[];
extern Dialog_geometry geom_attention;

extern Boolean disegna_freccia;
extern unsigned int spessore_linea, lung_freccia, larg_freccia;
extern Pixel colore_linea;

extern MacroBlockType *macroblocks;

static int xx1, yy1, xx2, yy2;
static XPoint *tmpline;
static int num_tmpline, num_tmpline_alloc;

/*---------------------------------------------------------------------*/
void funz_expose(w, ind_macro, ev, boh)
Widget w;
int ind_macro;
XEvent *ev;
Boolean boh;
{
   int i, num_line;
   GLine *lp;

   if (ev->type == Expose)
   {
      if (ev->xexpose.count)
         return;
   }
   else
      return;

   num_line = macroblocks[ind_macro].num_line;
   
   for( i=0 ; i<num_line ; i++ )
   {
      lp = &macroblocks[ind_macro].line[i];

      XSetForeground(display, lineGC, apix[lp->color]);
      XSetLineAttributes(display, lineGC, lp->thickness, LineSolid,
			 CapButt, JoinMiter);

      if (lp->num_points == 0)
         continue;

      if (lp->with_arrow)
      {
         XDrawLines(display, XtWindow(w), lineGC, lp->points,
		    lp->num_points-1,CoordModeOrigin );
         traccia_freccia(w, &lp->points[lp->num_points-2],
			    &lp->points[lp->num_points-1],
			    lp->length_arrow, lp->width_arrow);
      }
      else
      {
         XDrawLines(display, XtWindow(w), lineGC, lp->points, lp->num_points,
                    CoordModeOrigin );
      }
   }
}

/*---------------------------------------------------------------------*/
void funz_draw_line(wparent, ind_macro, call_data)
Widget wparent;
int ind_macro;
XmAnyCallbackStruct *call_data;
{
   Boolean fine = False, nuova_linea = False, punto_iniziale = True;
   Boolean win_wrong;
   XEvent event;
   Time t1, t2;
   XPoint c1, c2;
   Widget w;
   int mouse_button;

   w = macroblocks[ind_macro].wtavblock;

/* Accontenta le richieste di Expose penzolanti */
   while ( XCheckMaskEvent(display, ExposureMask, &event) )
       XtDispatchEvent(&event);

/* grab (cattura) del mouse pointer */
   if ( XGrabPointer(display, XtWindow(w), False,
                     ButtonPressMask|PointerMotionMask,
                     GrabModeSync, GrabModeAsync, XtWindow(w),
                     cursore_a_crocetta, CurrentTime)   !=  GrabSuccess)
   {
        s_warning( top_level, &geom_attention, APPLICATION_NAME,
                   warning_mesg, WCANTGRAB );
        return;
   }

   fine = False;

   XSetLineAttributes(display, xorGC, spessore_linea, LineSolid,
		      CapButt, JoinMiter);
   while (!fine)
   {
      XAllowEvents(display, SyncPointer, CurrentTime);
      XWindowEvent(display, XtWindow(w), ButtonPressMask|PointerMotionMask,
                   &event);

      switch (event.type)
      {
         case ButtonPress:
              mouse_button = event.xbutton.button;

           /* Esci dalla modalita' draw */
              if (mouse_button == Button3) 
                 fine = True;

              if (event.xbutton.window != XtWindow(w))
              {
                 win_wrong = True;
                 break;
              }
              win_wrong = False;

              c1.x = event.xbutton.x;
              c1.y = event.xbutton.y;
           
           /* Controlla che l'utente abbia stabilito il punto iniziale */
              if (punto_iniziale && mouse_button == Button1)
              {
                 tmpline = (XPoint *) calloc_mem(50, sizeof(XPoint));
                 num_tmpline = 0;
                 num_tmpline_alloc = 50;

                 XSetForeground(display, lineGC, apix[colore_linea]);
                 XSetLineAttributes(display, lineGC, spessore_linea, LineSolid,
	              	      CapButt, JoinMiter);

              /* l'utente ha stabilito il punto iniziale */
                 t1 = event.xbutton.time;
                 punto_iniziale = False;
                 start_draw_line(w, &c1);
                 modifiche = True;
                 break;
              }

           /* controlla il double-click. In tal caso termina il tracciamento */
              if ((event.xbutton.time - t1) < 300 || mouse_button != Button1)
              {
                 if (!punto_iniziale)
                 {
                    end_draw_line(w, &c1, disegna_freccia);
                    tmp_fine_linee(ind_macro, (mouse_button == Button1));
                 }
                 punto_iniziale = True;
                 nuova_linea = False;
                 break;
              }

              nuova_linea = True;
              t1 = event.xbutton.time;
              c2.x = c1.x;
              c2.y = c1.y;
              break;

         case MotionNotify:
            /* se l'utente non ha stabilito il punto iniziale, non eseguire */
            /* il tracciamento */
              if (punto_iniziale || mouse_button != Button1 || win_wrong)
                 break;

              c1.x = event.xbutton.x;
              c1.y = event.xbutton.y;
              if ((event.xmotion.time - t1) > 300 && nuova_linea)
              {
		 end_draw_line(w, &c2, False);
                 start_draw_line(w, &c2);
                 nuova_linea = False;
              }
              if (!nuova_linea)
                 cont_draw_line(w, &c1);
              break;

         case Expose:
              XtDispatchEvent(&event);
              break;
      }
   }

/* Rimuovi il grab del mouse */
   XUngrabPointer(display, CurrentTime);

   XSetLineAttributes(display, xorGC, 1, LineSolid, CapButt, JoinMiter);
}

/*---------------------------------------------------------------------*/
/*** void tmp_fine_linee()
L'utente ha terminato il gruppo di linee. si possono salvare nel vettore
line oppure scartare (in questo caso le linee precedentemente tracciate
vengono scartate ***/
tmp_fine_linee(ind_macro, accetta)
int ind_macro;
Boolean accetta;
{
   GLine **line;
   int *num_line, *num_line_alloc;
   Widget w;

   w = macroblocks[ind_macro].wtavblock;

   if (num_tmpline)
   {
      if (accetta)
         XSetForeground(display, lineGC, apix[colore_linea]);
      else
         XSetForeground(display, lineGC, apix[BLOCKS_TABLE_BG]);

      if (disegna_freccia)
      {
         XDrawLines(display, XtWindow(w), lineGC, tmpline, num_tmpline-1,
                    CoordModeOrigin );
         traccia_freccia(w, &tmpline[num_tmpline-2], &tmpline[num_tmpline-1],
			    lung_freccia, larg_freccia);
      }
      else
         XDrawLines(display, XtWindow(w), lineGC, tmpline, num_tmpline,
                    CoordModeOrigin );
      XSetForeground(display, lineGC, apix[colore_linea]);

   /* memorizza nel vettore line la linea temporanea appena creata */
      if (accetta)
      {
         line = &macroblocks[ind_macro].line;
         num_line = &macroblocks[ind_macro].num_line;
         num_line_alloc = &macroblocks[ind_macro].num_line_alloc;

         (*line)[*num_line].points = (XPoint *) calloc_mem(num_tmpline,
                                                           sizeof(XPoint));
         memcpy((char *) (*line)[*num_line].points, (char *) tmpline,
                                                    num_tmpline*sizeof(XPoint));
         (*line)[*num_line].num_points = num_tmpline;
         (*line)[*num_line].with_arrow = (Boolean) disegna_freccia;
         (*line)[*num_line].thickness = spessore_linea;
         (*line)[*num_line].color = colore_linea;
         (*line)[*num_line].length_arrow = lung_freccia;
         (*line)[*num_line].width_arrow = larg_freccia;
         (*num_line)++;

         if (*num_line >= *num_line_alloc)
            *line = (GLine *) realloc_mem(*line, *num_line_alloc += 50,
                                       sizeof(GLine));
      }
   }
   XtFree(tmpline);
}

/*---------------------------------------------------------------------*/
void start_draw_line(w, xp)
Widget w;
XPoint *xp;
{
   xx1 = xx2 = xp->x - xp->x % snap_val;
   yy1 = yy2 = xp->y - xp->y % snap_val;

   tmpline[num_tmpline].x = xx1;
   tmpline[num_tmpline++].y = yy1;
   XDrawLine(display, XtWindow(w), xorGC, xx1, yy1, xx2, yy2);
   if (num_tmpline >= num_tmpline_alloc)
       tmpline = (XPoint *) realloc_mem(tmpline, num_tmpline_alloc += 50,
                                       sizeof(XPoint));
}

/*---------------------------------------------------------------------*/
void cont_draw_line(w, xp)
Widget w;
XPoint *xp;
{
   XDrawLine(display, XtWindow(w), xorGC, xx1, yy1, xx2, yy2);

   xx2 = xp->x - xp->x % snap_val;
   yy2 = xp->y - xp->y % snap_val;

   XDrawLine(display, XtWindow(w), xorGC, xx1, yy1, xx2, yy2);
}

/*---------------------------------------------------------------------*/
void end_draw_line(w, xp, draw_arrow)
Widget w;
XPoint *xp;
Boolean draw_arrow;
{
   int bx, by, cx, cy;
   double lung, alfa, beta, xx3, yy3, fxx2, fyy2, fxx1, fyy1;
   XPoint point[3];

   XDrawLine(display, XtWindow(w), xorGC, xx1, yy1, xx2, yy2);

   fxx2 = xx2 = xp->x - xp->x % snap_val;
   fyy2 = yy2 = xp->y - xp->y % snap_val;
   fxx1 = xx1;
   fyy1 = yy1;

   lung = sqrt((fxx2-fxx1)*(fxx2-fxx1) + (fyy2-fyy1)*(fyy2-fyy1));
   if ( !lung )
   {
      printf("lunghezza zero!\n");
      num_tmpline--;
      return;
   }

   if (num_tmpline+1 >= num_tmpline_alloc)
       tmpline = (XPoint *) realloc_mem(tmpline, num_tmpline_alloc += 50,
                                       sizeof(XPoint));
   if (draw_arrow)
   {
/***
      lung -= (lung < lung_freccia) ? lung : lung_freccia;

      alfa = larg_freccia/lung;
      beta = atan2((fyy2-fyy1),(fxx2-fxx1));

      tmpline[num_tmpline].x = round(fxx1 + lung*cos(beta));
      tmpline[num_tmpline++].y = round(fyy1 + lung*sin(beta));
      tmpline[num_tmpline].x = xx2;
      tmpline[num_tmpline++].y = yy2;
***/
      tmpline[num_tmpline].x = round_mio(fxx2-(lung_freccia*(fxx2-fxx1)/lung));
      tmpline[num_tmpline++].y = round_mio(fyy2-(lung_freccia*(fyy2-fyy1)/lung));
      xx1 = tmpline[num_tmpline-1].x;
      yy1 = tmpline[num_tmpline-1].y;
      tmpline[num_tmpline].x = xx2;
      tmpline[num_tmpline++].y = yy2;
   }
   else
   {
      tmpline[num_tmpline].x = xx2;
      tmpline[num_tmpline++].y = yy2;
      XDrawLine(display, XtWindow(w), lineGC, xx1, yy1, xx2, yy2 );
   }
}

traccia_freccia( w, p1, p2, len_arrw, wdt_arrw )
Widget w;
XPoint *p1, *p2;
int len_arrw, wdt_arrw;
{
   int bx, by, cx, cy;
   double lung, alfa, beta, fxx2, fyy2, fxx1, fyy1;
   double xa,xb,ya,yb,a,b,c,xp,yp;
   XPoint point[3];

   xa = p1->x;
   ya = p1->y;
   xb = p2->x;
   yb = p2->y;

   a = yb-ya;
   b = xa-xb;
   c = ya*xb-xa*yb;

   if ( a == 0 && b == 0)
      return;

   alfa = atan2(-a,b);
   beta = (alfa >= 0) ? alfa - M_PI : M_PI + alfa;
/****
printf("ang1: %d ang2: %d\n", (int) (alfa*180.0/M_PI),
                              (int) (beta*180.0/M_PI));
printf("segm. 1: %d %d\n",(int) ((wdt_arrw/2)*sin(alfa)),
		          (int) ((wdt_arrw/2)*cos(alfa)));
printf("segm. 2: %d %d\n",(int) ((wdt_arrw/2)*sin(beta)),
		          (int) ((wdt_arrw/2)*cos(beta)));
****/
   xp = xa-(wdt_arrw/2)*(sin(alfa));
   yp = ya+(wdt_arrw/2)*(cos(alfa));
   point[0].x = (short) round_mio(xp);
   point[0].y = (short) round_mio(yp);
   xp = xa-(wdt_arrw/2)*(sin(beta));
   yp = ya+(wdt_arrw/2)*(cos(beta));
   point[1].x = (short) round_mio(xp);
   point[1].y = (short) round_mio(yp);
   point[2].x = p2->x;
   point[2].y = p2->y;

/***
   fxx1 = p1->x;
   fyy1 = p1->y;
   fxx2 = p2->x;
   fyy2 = p2->y;

   lung = sqrt((fxx2-fxx1)*(fxx2-fxx1) + (fyy2-fyy1)*(fyy2-fyy1));

   lung -= (lung < len_arrw) ? lung : len_arrw;

   alfa = wdt_arrw/lung;
   beta = atan2((fyy2-fyy1),(fxx2-fxx1));

   point[0].x = (int) p1->x + round(lung*cos(alfa+beta));
   point[0].y = (int) p1->y + round(lung*sin(alfa+beta));
   point[1].x = (int) p1->x + round(lung*cos(beta-alfa));
   point[1].y = (int) p1->y + round(lung*sin(beta-alfa));
   point[2].x = p2->x;
   point[2].y = p2->y;
***/

   XFillPolygon(display, XtWindow(w), lineGC, point, 3, Convex,
                CoordModeOrigin);
}

short round_mio(val)
double val;
{
   return( ((int) val) + (((val-(int) val) > 0.5) ? 1 : 0));
}

/*------------------------------------------------------------------*/
/*** void delete_line(w,par,call_data)
 *** configurazione delle line (spessore, colore, freccia)
 ***/
void delete_line(wparent, ind_macro, call_data)
Widget wparent;
int ind_macro;
XmAnyCallbackStruct *call_data;
{
   int i, offset;
   XEvent event;
   Widget w;
   GLine *lp;

/* grab (cattura) del mouse pointer */
   w = macroblocks[ind_macro].wtavblock;
   if ( XGrabPointer(display, XtWindow(w), True,
                     ButtonReleaseMask|PointerMotionMask,
                     GrabModeSync, GrabModeAsync, XtWindow(w),
                     cursore_a_crocetta, CurrentTime)  !=  GrabSuccess)
   {
        s_warning( top_level, &geom_attention, APPLICATION_NAME,
                   warning_mesg, WCANTGRAB );
        return;
   }

   while (True)
   {
      XAllowEvents(display, SyncPointer, CurrentTime);
      XNextEvent(display, &event);

      if (event.type == ButtonPress)
      {
         if (event.xbutton.button == Button3)
            break;

         if (event.xbutton.window != XtWindow(w))
            continue;

         XSetForeground(display, lineGC, apix[BLOCKS_TABLE_BG]);
         for (i=0 ; i<macroblocks[ind_macro].num_line ; i++ )
            if ( check_line(&macroblocks[ind_macro].line[i], 
		            event.xbutton.x, 
		            event.xbutton.y ) )
            {
               lp = &macroblocks[ind_macro].line[i];

               modifiche = True;
	       XSetLineAttributes(display, lineGC, lp->thickness, LineSolid,
                                  CapButt, JoinMiter);
               if (lp->with_arrow)
               {
                  XDrawLines(display, XtWindow(w), lineGC, lp->points,
                             lp->num_points-1,CoordModeOrigin );
                  traccia_freccia(w, &lp->points[lp->num_points-2],
                                     &lp->points[lp->num_points-1],
		            	      lp->length_arrow, lp->width_arrow );
               }
               else
               {
                  XDrawLines(display, XtWindow(w), lineGC,
		             lp->points, lp->num_points, CoordModeOrigin );
               }

            /* cancella dalla memoria la linea */
               XtFree(lp->points);
               offset = macroblocks[ind_macro].num_line-i-1;
               if (offset)
                  memmove((char *) lp, (char *) (lp+1), offset*sizeof(GLine));
               macroblocks[ind_macro].num_line--;
            }
      }

      if (event.type == Expose)
         XtDispatchEvent(&event);
   }

/* Rimuovi il grab del mouse */
   XUngrabPointer(display, CurrentTime);
}

/*------------------------------------------------------------------*/
/*** Boolean check_line(line,x,y)
controlla se il punto (x,y) e' nelle vicinanze delle linee 'line'.
In tal caso ritorna True senno' False. ***/
int check_line(lp,x1,y1)
GLine *lp;
int x1, y1;
{
   int i, j;
   double minx, maxx, miny, maxy;
   double xa, ya, xb, yb, xp, yp;
   double rappo, a, b, c;

   for( j=0 ; j<lp->num_points-1 ; j++ )
   {
/* recupera i 2 punti della retta */
      xa = lp->points[j].x;
      ya = lp->points[j].y;
      xb = lp->points[j+1].x;
      yb = lp->points[j+1].y;

      minx = (xa<xb) ? xa : xb;
      maxx = (xa>xb) ? xa : xb;
      miny = (ya<yb) ? ya : yb;
      maxy = (ya>yb) ? ya : yb;

/* equazione della retta perpendicolare: ax+by+c */
      a = yb-ya;
      b = xa-xb;
      c = ya*xb-xa*yb;

      if ( a == 0 && b == 0)
         continue;

/* Coordinate del punto della retta perpendicolare passante per il */
/* punto x1, y1 */
      xp = (b*b*x1-a*b*y1-a*c)/(a*a+b*b);
      yp = (a*a*y1-a*b*x1-b*c)/(a*a+b*b);

/* se il punto non si trova nel segmento, continua con il segmento succ. */
      if (xp > maxx || xp < minx || yp > maxy || yp < miny)
         continue;
      rappo = ABS(a*x1+b*y1+c)/sqrt(a*a+b*b);
      if (rappo < DELTA_SELECT_LINE)
         return(True);
   }
   return(False);
}
