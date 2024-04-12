/**********************************************************************
*
*       C Source:               statistiche.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:46:25 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: statistiche.c-4 %  (%full_filespec: statistiche.c-4:csrc:1 %)";
#endif

/* 
 * statistiche .c
 * gestione e display delle statistiche di simulazione
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <X11/Intrinsic.h>
#include <X11/Xlib.h>
#include <Xm/DrawingA.h>

#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"

#include "UxXt.h"
#include "sked.h"
#include "messaggi.h"
#include "bistrutt.h"
#include "refresh.h"
#include "statisticsDisplay.h"

#include "parametri.h"

extern char *ind_sh_top;
extern int nmod;
extern VAL val;
extern XtIntervalId timer_statisticsDisplay;

void refresh_stat_display();
Widget attiva_statistiche ();

char *nome_modello(char *, int);

/**************************************************************/
Widget attiva_statistiche (w)
Widget w;
{
	return (create_statisticsDisplay (w));
}
/**************************************************************/
int istogramma_tasks (w)
Widget w;	                 /* chiamante                   */
{
int i;
float max_val = 0.;
float tot_val = 0.;
char testo[50];
int altezza = 25;
int larghezza=300;
GC gc;
XGCValues gcv;

	_UxCstatisticsDisplay  *Ctx = (_UxCstatisticsDisplay *) UxGetContext(w);

	gcv.foreground = BlackPixelOfScreen (XtScreen(Ctx->UxdrawingArea1));
	gc = XCreateGC (XtDisplay(Ctx->UxdrawingArea1),
						RootWindowOfScreen(XtScreen(Ctx->UxdrawingArea1)), 
						0, NULL);  
	XtVaSetValues (Ctx->UxdrawingArea1, XmNuserData, gc, NULL);
	XSetForeground (UxDisplay, gc, colore_app[2]);

	for (i=0; i<nmod; i++)
		{
		tot_val += val.actual.tempo[i];
		if (val.actual.tempo[i] > max_val)
			max_val = val.actual.tempo[i];
		}

	for (i=0; i<nmod; i++)
      {
		sprintf(testo,"%s : %3.1f",
						nome_modello(ind_sh_top,i+1),val.actual.tempo[i]);
		XDrawString(UxDisplay,Ctx->Uxdwg,gc,
						3, ((i+1)*altezza)-5,testo,strlen(testo));
		if (max_val > 0.)
      		XFillRectangle(UxDisplay,Ctx->Uxdwg,gc,
     						100,(i*altezza)+5,
     						(int)(val.actual.tempo[i]*(larghezza-100)/max_val),
							altezza-5);
		}


	return (0);
}
/**********************************************************************/
int attiva_timer_statistiche (w)
Widget w;
{
   timer_statisticsDisplay =
                  XtAppAddTimeOut (XtWidgetToApplicationContext(w),
                  (unsigned long)5000, refresh_stat_display, w);
   return (0);
}
/**********************************************************************/
void refresh_stat_display (data)
XtPointer data;
{
Widget w = (Widget)data;
   XClearArea(UxDisplay,XtWindow(w),0,0,0,0,False);
	istogramma_tasks (w);  
	attiva_timer_statistiche (w);
	return;
}
