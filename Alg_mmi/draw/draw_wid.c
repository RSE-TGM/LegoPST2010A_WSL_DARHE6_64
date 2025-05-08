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
        Inizio sezione per SCCS
*/
/*
   modulo draw_wid.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)draw_wid.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)draw_wid.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/

/*
 draw_wid.c
 contiene funzioni per la manipolazioni di risorse locali all'oggetto
 draw_wid che contiene i draget.
*/
#include <stdio.h>
#include <X11/Intrinsic.h>
#include <draw.h>
/*
 funzioni di utilita' per il set e/o get delle risorse
 del draw_wid.
*/

Region get_region(Widget w)
{
Region ret;
gs_draw_ris(w,DR_REGION,&ret,False);
return(ret);
}

void set_region(Widget w, Region value)
{
gs_draw_ris(w,DR_REGION,&value,True);
}


int get_line_style(Widget w)
{
int ret;
gs_draw_ris(w,DR_LINE_STYLE,&ret,False);
return(ret);
}

void set_line_style(Widget w, int value)
{
gs_draw_ris(w,DR_LINE_STYLE,&value,True);
}

int get_line_width(Widget w)
{
int ret;
gs_draw_ris(w,DR_LINE_WIDTH,&ret,False);
return(ret);
}

int set_line_width(Widget w, int value)
{
gs_draw_ris(w,DR_LINE_WIDTH,&value,True);
}

int get_def_line_style(Widget w)
{
int ret;
gs_draw_ris(w,DR_DEF_LINE_STYLE,&ret,False);
return(ret);
}

int set_def_line_style(Widget w, int value)
{
gs_draw_ris(w,DR_DEF_LINE_STYLE,&value,True);
}

int get_def_line_width(Widget w)
{
int ret;
gs_draw_ris(w,DR_DEF_LINE_WIDTH,&ret,False);
return(ret);
}

int set_def_line_width(Widget w, int value)
{
gs_draw_ris(w,DR_DEF_LINE_WIDTH,&value,True);
}

int get_step(Widget w)
{
int ret;
gs_draw_ris(w,DR_STEP,&ret,False);
return(ret);
}

int set_step(Widget w, int value)
{
gs_draw_ris(w,DR_STEP,&value,True);
}

int get_grid_on(Widget w)
{
int ret;
gs_draw_ris(w,DR_GRID_ON,&ret,False);
return(ret);
}

int  set_grid_on(Widget w, int value)
{
gs_draw_ris(w,DR_GRID_ON,&value,True);
}

int get_def_filled(Widget w)
{
int ret;
gs_draw_ris(w,DR_DEF_FILLED,&ret,False);
return(ret);
}

int set_def_filled(Widget w, int value)
{
gs_draw_ris(w,DR_DEF_FILLED,&value,True);
}

float get_def_zoom(Widget w)
{
float ret;
gs_draw_ris(w,DR_DEF_ZOOM,&ret,False);
return(ret);
}

int set_def_zoom(Widget w, float value)
{
gs_draw_ris(w,DR_DEF_ZOOM,&value,True);
}

GC get_gc(Widget w)
{
GC ret;
gs_draw_ris(w,DR_GC,&ret,False);
return(ret);
}

int set_gc(Widget w, GC value)
{
gs_draw_ris(w,DR_GC,&value,True);
}

GC get_gc_bg(Widget w)
{
GC ret;
gs_draw_ris(w,DR_GC_BG,&ret,False);
return(ret);
}

int set_gc_bg(Widget w, GC value)
{
gs_draw_ris(w,DR_GC_BG,&value,True);
}

GC get_def_gc(Widget w)
{
GC ret;
gs_draw_ris(w,DR_DEF_GC,&ret,False);
return(ret);
}

int set_def_gc(Widget w, GC value)
{
gs_draw_ris(w,DR_DEF_GC,&value,True);
}

GC get_def_gc_bg(Widget w)
{
GC ret;
gs_draw_ris(w,DR_DEF_GC_BG,&ret,False);
return(ret);
}

int set_def_gc_bg(Widget w, GC value)
{
gs_draw_ris(w,DR_DEF_GC_BG,&value,True);
}
 
Widget get_bott_fill(Widget w)
{
Widget ret;
gs_draw_ris(w,DR_BOTT_FILL,&ret,False);
return(ret);
}

int set_bott_fill(Widget w, Widget value)
{
gs_draw_ris(w,DR_BOTT_FILL,&value,True);
}

Widget get_bott_border(Widget w)
{
Widget ret;
gs_draw_ris(w,DR_BOTT_BORDER,&ret,False);
return(ret);
}

int set_bott_border(Widget w, Widget value)
{
gs_draw_ris(w,DR_BOTT_BORDER,&value,True);
}

Widget get_def_bott_fill(Widget w)
{
Widget ret;
gs_draw_ris(w,DR_DEF_BOTT_FILL,&ret,False);
return(ret);
}

int set_def_bott_fill(Widget w, Widget value)
{
gs_draw_ris(w,DR_DEF_BOTT_FILL,&value,True);
}

Widget get_def_bott_border(Widget w)
{
Widget ret;
gs_draw_ris(w,DR_DEF_BOTT_BORDER,&ret,False);
return(ret);
}

int set_def_bott_border(Widget w, Widget value)
{
gs_draw_ris(w,DR_DEF_BOTT_BORDER,&value,True);
}

Widget get_bott_arrow(Widget w)
{
Widget ret;
gs_draw_ris(w,DR_BOTT_ARROW,&ret,False);
return(ret);
}

int set_bott_arrow(Widget w, Widget value)
{
gs_draw_ris(w,DR_BOTT_ARROW,&value,True);
}


int init_st_draw(ST_DRAW_WID *st_draw)
{
st_draw->region= NULL;
st_draw->def_zoom=1.0;
st_draw->def_filled=1;
st_draw->step=1;
st_draw->grid_on=0;
st_draw->line_width=0;
st_draw->line_style=LineSolid;
st_draw->def_line_width=0;
st_draw->def_line_style=LineSolid;
}
