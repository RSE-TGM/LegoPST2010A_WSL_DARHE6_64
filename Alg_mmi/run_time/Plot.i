! UIMX ascii 2.5 key: 3075                                                      

*Plot.class: topLevelShell
*Plot.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo Plot.i\
   tipo \
   release 5.2\
   data 1/22/96\
   reserved @(#)Plot.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
#include <string.h>\
#include <stdlib.h>\
#include <math.h>\
\
\
#ifndef DESIGN_TIME\
#include <Xl/Xl.h>\
#endif\
\
#include <Ol/OlDatabasePunti.h>\
\
#ifdef SCO_UNIX\
#include <Xm/MwmUtil.h>\
#else\
/*\
#include <X11/MwmUtil.h>\
*/\
#include <Xm/MwmUtil.h>\
#endif\
\
#include "other.h"\
\
#include "page_plot_icon.bmp"\
\
extern OlDatabasePuntiObject database_simulatore;\
static void CreaGrafico( );\
void DestroyPlot( );\
static void refresh_plot( );\

*Plot.ispecdecl: char plotSelect[20];\
char plotunimisSelect[20];\
float aplotSelect;\
float bplotSelect;\
Widget topLevel_selezionataPlot;\
XtIntervalId timer_refresh_plot;\
XmFontList FontLabelPlot;\
int key_refresh_plot;\
WidgetList lista_wid_plot;\
int num_wid_plot;\
int indplotSelect;\
XrmDatabase RisDb;
*Plot.ispeclist: plotSelect, plotunimisSelect, aplotSelect, bplotSelect, topLevel_selezionataPlot, timer_refresh_plot, FontLabelPlot, key_refresh_plot, lista_wid_plot, num_wid_plot, indplotSelect, RisDb
*Plot.ispeclist.plotSelect: "unsigned char", "%plotSelect%[20]"
*Plot.ispeclist.plotunimisSelect: "unsigned char", "%plotunimisSelect%[20]"
*Plot.ispeclist.aplotSelect: "float", "%aplotSelect%"
*Plot.ispeclist.bplotSelect: "float", "%bplotSelect%"
*Plot.ispeclist.topLevel_selezionataPlot: "Widget", "%topLevel_selezionataPlot%"
*Plot.ispeclist.timer_refresh_plot: "XtIntervalId", "%timer_refresh_plot%"
*Plot.ispeclist.FontLabelPlot: "XmFontList", "%FontLabelPlot%"
*Plot.ispeclist.key_refresh_plot: "int", "%key_refresh_plot%"
*Plot.ispeclist.lista_wid_plot: "WidgetList", "%lista_wid_plot%"
*Plot.ispeclist.num_wid_plot: "int", "%num_wid_plot%"
*Plot.ispeclist.indplotSelect: "int", "%indplotSelect%"
*Plot.ispeclist.RisDb: "XrmDatabase", "%RisDb%"
*Plot.funcdecl: swidget popup_Plot(rigaPlot,PadrePlot)\
char *rigaPlot;\
Widget PadrePlot;\

*Plot.funcname: popup_Plot
*Plot.funcdef: "swidget", "<popup_Plot>(%)"
*Plot.argdecl: unsigned char *rigaPlot;\
Widget PadrePlot;
*Plot.arglist: rigaPlot, PadrePlot
*Plot.arglist.rigaPlot: "unsigned char", "*%rigaPlot%"
*Plot.arglist.PadrePlot: "Widget", "%PadrePlot%"
*Plot.icode: char c1[20],c2[20],c3[20],c4[20],c5[20],c6[20],c7[20];\
Pixmap pix;\
\
if(!CanOpenPage(PadrePlot))\
	return(NULL);\
\
sscanf(rigaPlot,"%s %s %s %s %s %s %s",plotSelect,c2,c3,c4,c5,c6,plotunimisSelect);\
aplotSelect=atof(c5);\
bplotSelect=atof(c6);\
#ifndef DESIGN_TIME\
if(!LoadFont(FONT_LABEL,&FontLabelPlot,XtDisplay(PadrePlot)))\
	exit(0);\
#endif
*Plot.fcode: set_something(ClosePlot,XmNfontList,FontLabelPlot);\
\
#ifndef DESIGN_TIME\
LoadBitmap(drawingPlot,&pix,page_plot_icon_bits,page_plot_icon_width,\
		page_plot_icon_height);\
#endif\
set_something(rtrn,XmNiconPixmap,pix);\
\
CreaGrafico(drawingPlot);\
#ifndef DESIGN_TIME\
if((key_refresh_plot=\
	InsElencoPagine("__PLOT__",lista_wid_plot,num_wid_plot,\
			REFRESH_PLOT/1000)) == -1)\
	return(NULL);\
#endif\
\
UxPopupInterface(rtrn, no_grab);\
#ifndef DESIGN_TIME\
timer_refresh_plot = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (PadrePlot),\
            (unsigned long) REFRESH_PLOT ,refresh_plot, UxContext);\
#endif\
\
\
return(rtrn);\

*Plot.auxdecl: void DestroyPlot(Widget w)\
{\
#ifndef DESIGN_TIME\
_UxCPlot *Context;\
\
        Context =(_UxCPlot *) UxGetContext(w);	\
	DelElencoPagine(Context->Uxkey_refresh_plot, \
		Context->UxdrawingPlot);\
	XSync(XtDisplay(w),False);\
	XtRemoveTimeOut(Context->Uxtimer_refresh_plot);\
	XtDestroyWidget(Context->UxPlot);\
	XrmDestroyDatabase(Context->UxRisDb);\
#endif\
}\
\
\
\
\
static void CreaGrafico(Widget Drawing)\
{\
#ifndef DESIGN_TIME\
_UxCPlot *Context;\
XrmDatabase SaveDb;\
Display *display;\
\
	WriteDbPlot();	\
        Context =(_UxCPlot *) UxGetContext(Drawing);\
	RisDb=XrmGetFileDatabase("TemplateGrafPlot.rtf");\
	display=XtDisplay(Drawing);\
	SaveDb=display->db;\
	\
	display->db=RisDb;\
	CreaPagina(Context->UxdrawingPlot,&(Context->Uxlista_wid_plot),\
		 &(Context->Uxnum_wid_plot));\
	Context->UxindplotSelect = SettaGrafPlot(Context->Uxlista_wid_plot[0],Context->UxrigaPlot,\
		Context->UxaplotSelect,Context->UxbplotSelect);\
	display->db=SaveDb;\
	\
#endif\
}\
\
#ifndef DESIGN_TIME\
static void refresh_plot(_UxCPlot *Context)\
#else\
static void refresh_plot()\
#endif\
{\
#ifndef DESIGN_TIME\
if(!OlSetDataPage(database_simulatore,Context->Uxkey_refresh_plot))\
        {\
        show_warning("Error in refresh");\
        return;\
        }\
if(OlGetDataStatus(database_simulatore,Context->Uxkey_refresh_plot))\
     XlRefreshWidget(Context->Uxlista_wid_plot,Context->Uxnum_wid_plot);\
	\
if(!OlUnsetDataPage(database_simulatore,Context->Uxkey_refresh_plot))\
        {\
        show_warning("Error in refresh");\
        return;\
        }\
/*\
        carica il timer per il refresh\
*/\
Context->Uxtimer_refresh_plot = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (Context->UxPlot),\
            (unsigned long) REFRESH_PLOT ,refresh_plot, Context);\
#endif	\
}\
\

*Plot.static: true
*Plot.name: Plot
*Plot.parent: NO_PARENT
*Plot.x: 260
*Plot.y: 330
*Plot.width: 400
*Plot.height: 240
*Plot.mwmDecorations: MWM_DECOR_BORDER | MWM_DECOR_MINIMIZE | MWM_DECOR_RESIZEH
*Plot.iconName: plotSelect
*Plot.title: plotSelect
*Plot.minHeight: 100
*Plot.minWidth: 200

*sfondoPlot.class: form
*sfondoPlot.static: true
*sfondoPlot.name: sfondoPlot
*sfondoPlot.parent: Plot
*sfondoPlot.resizePolicy: "resize_none"
*sfondoPlot.unitType: "pixels"
*sfondoPlot.x: 0
*sfondoPlot.y: 10
*sfondoPlot.width: 280
*sfondoPlot.height: 180
*sfondoPlot.background: "#50a050"

*drawingPlot.class: drawingArea
*drawingPlot.static: true
*drawingPlot.name: drawingPlot
*drawingPlot.parent: sfondoPlot
*drawingPlot.resizePolicy: "resize_none"
*drawingPlot.x: 0
*drawingPlot.y: 0
*drawingPlot.width: 380
*drawingPlot.height: 220
*drawingPlot.bottomAttachment: "attach_form"
*drawingPlot.leftAttachment: "attach_form"
*drawingPlot.rightAttachment: "attach_form"
*drawingPlot.topAttachment: "attach_form"
*drawingPlot.background: "#50a050"
*drawingPlot.resizeCallback: {\
Dimension w,h;\
\
\
get_something(drawingPlot,XmNwidth,&w);\
get_something(drawingPlot,XmNheight,&h);\
\
printf("Eseguito resize sulla plot  w=%d  h=%d\n",w,h);\
w -=20;\
h -=20;\
\
set_something(lista_wid_plot[0],XlNwidth0,w);\
set_something(lista_wid_plot[0],XlNheight0,h);\
}

*menuClosePlot.class: rowColumn
*menuClosePlot.static: true
*menuClosePlot.name: menuClosePlot
*menuClosePlot.parent: drawingPlot
*menuClosePlot.rowColumnType: "menu_popup"

*ClosePlot.class: pushButton
*ClosePlot.static: true
*ClosePlot.name: ClosePlot
*ClosePlot.parent: menuClosePlot
*ClosePlot.labelString: "Close"
*ClosePlot.background: "#50a050"
*ClosePlot.activateCallback: {\
DestroyPlot(UxWidget);\
}

