! UIMX ascii 2.5 key: 2591                                                      

*topLevelShellStaz.class: topLevelShell
*topLevelShellStaz.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo topLevelShellStaz.i\
   tipo \
   release 5.2\
   data 1/22/96\
   reserved @(#)topLevelShellStaz.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <X11/Xlib.h>\
#ifdef SCO_UNIX\
#include <Xm/MwmUtil.h>\
#else\
#include <Xm/MwmUtil.h>\
#endif\
\
#ifndef DESIGN_TIME\
#include <Xl/Xl.h>\
#endif\
\
#ifndef DESIGN_TIME\
#include <Xl/XlCoreP.h>\
#include <Xl/XlManagerP.h>\
#else\
#include <Xl/XlCore.h>\
#include <Xl/XlManager.h>\
#endif\
\
#include <Xl/XlChangePage.h>\
#include <Ol/OlDatabasePunti.h>\
\
#ifndef DESIGN_TIME\
#include <Ol/OlPertP.h>\
#else\
#include <Ol/OlPert.h>\
#endif\
#include <Xm/Protocols.h>\
#include "page_staz_icon.bmp"\
\
#include "other.h"\
\
\
extern OlDatabasePuntiObject database_simulatore;\
extern OlPertObject pert;\
extern AN_PAG *pagine;\
extern Boolean topologia_on;\
                  \
static void refresh_page( );\
void SetCursorWaitStaz( );\
void activateCB_menu1_p1_b1();
*topLevelShellStaz.ispecdecl: Widget topLevel_selezionataStaz;\
XtIntervalId timer_refresh_staz;\
WidgetList lista_widStaz;\
int num_widStaz;\
Region region_staz;\
XmFontList FontLabelStaz;\
int key_refresh_staz;\
int time_ref_staz;\
BCK_OBJ *bkg_stazioni;\
Widget ListaWidVarStaz[7];\
Widget wid_attesa_staz;\
int attesa_staz;\
int cursor_wait_set_staz;\
Cursor cursor_wait_staz;\
XrmDatabase pag_db;\
Pixmap drawing_pixmap; /* pixmap per eventuale stipple dello sfondo */
*topLevelShellStaz.ispeclist: topLevel_selezionataStaz, timer_refresh_staz, lista_widStaz, num_widStaz, region_staz, FontLabelStaz, key_refresh_staz, time_ref_staz, bkg_stazioni, ListaWidVarStaz, wid_attesa_staz, attesa_staz, cursor_wait_set_staz, cursor_wait_staz, pag_db, drawing_pixmap
*topLevelShellStaz.ispeclist.topLevel_selezionataStaz: "Widget", "%topLevel_selezionataStaz%"
*topLevelShellStaz.ispeclist.timer_refresh_staz: "XtIntervalId", "%timer_refresh_staz%"
*topLevelShellStaz.ispeclist.lista_widStaz: "WidgetList", "%lista_widStaz%"
*topLevelShellStaz.ispeclist.num_widStaz: "int", "%num_widStaz%"
*topLevelShellStaz.ispeclist.region_staz: "Region", "%region_staz%"
*topLevelShellStaz.ispeclist.FontLabelStaz: "XmFontList", "%FontLabelStaz%"
*topLevelShellStaz.ispeclist.key_refresh_staz: "int", "%key_refresh_staz%"
*topLevelShellStaz.ispeclist.time_ref_staz: "int", "%time_ref_staz%"
*topLevelShellStaz.ispeclist.bkg_stazioni: "BCK_OBJ", "*%bkg_stazioni%"
*topLevelShellStaz.ispeclist.ListaWidVarStaz: "Widget", "%ListaWidVarStaz%[7]"
*topLevelShellStaz.ispeclist.wid_attesa_staz: "Widget", "%wid_attesa_staz%"
*topLevelShellStaz.ispeclist.attesa_staz: "int", "%attesa_staz%"
*topLevelShellStaz.ispeclist.cursor_wait_set_staz: "int", "%cursor_wait_set_staz%"
*topLevelShellStaz.ispeclist.cursor_wait_staz: "Cursor", "%cursor_wait_staz%"
*topLevelShellStaz.ispeclist.pag_db: "XrmDatabase", "%pag_db%"
*topLevelShellStaz.ispeclist.drawing_pixmap: "Pixmap", "%drawing_pixmap%"
*topLevelShellStaz.funcdecl: swidget popup_topLevelShellStaz(PaginaStaz,PadreStaz,nome_dispStaz,sfondo_staz)\
char *PaginaStaz;\
Widget PadreStaz;\
char *nome_dispStaz;\
BCK_OBJ *sfondo_staz;\
\

*topLevelShellStaz.funcname: popup_topLevelShellStaz
*topLevelShellStaz.funcdef: "swidget", "<popup_topLevelShellStaz>(%)"
*topLevelShellStaz.argdecl: unsigned char *PaginaStaz;\
Widget PadreStaz;\
unsigned char *nome_dispStaz;\
BCK_OBJ *sfondo_staz;
*topLevelShellStaz.arglist: PaginaStaz, PadreStaz, nome_dispStaz, sfondo_staz
*topLevelShellStaz.arglist.PaginaStaz: "unsigned char", "*%PaginaStaz%"
*topLevelShellStaz.arglist.PadreStaz: "Widget", "%PadreStaz%"
*topLevelShellStaz.arglist.nome_dispStaz: "unsigned char", "*%nome_dispStaz%"
*topLevelShellStaz.arglist.sfondo_staz: "BCK_OBJ", "*%sfondo_staz%"
*topLevelShellStaz.icode: int top_x,top_y,top_width,top_height,drawing_width,drawing_height;\
char *top_tipo, *top_descrizione;\
Pixel *drawing_background;\
int dim[4];\
int num_b;\
Pixmap pix;\
Atom WM_DELETE_WINDOW; /* per close con MWM*/\
printf("Selezionata la Pagina di stazioni %s\n",PaginaStaz);\
\
topLevel_selezionataStaz=PadreStaz;\
cursor_wait_set_staz = 0;\
drawing_pixmap=0;\
#ifndef DESIGN_TIME\
if(!(pag_db=CaricaDB(XtDisplay(topLevel_selezionataStaz),PaginaStaz)))\
	return(False);\
\
\
if(!GetResTopLevel(PadreStaz,&top_x,&top_y,&top_width,&top_height,&time_ref_staz,\
		&top_tipo,&top_descrizione))\
	return(False);\
if(!GetResDrawing(PadreStaz,&drawing_width,&drawing_height,&drawing_background, &drawing_pixmap))\
		return(False);\
#endif\
printf("Caricate le risorse\n");\
\

*topLevelShellStaz.fcode: /*\
  inizializza la regione di ridisegno\
*/\
if(sfondo_staz!=NULL)\
	{\
 	num_b=1;\
 	while(sfondo_staz[num_b-1].tipo>0)\
  		num_b++;\
 	(bkg_stazioni)=(BCK_OBJ*)XtCalloc(num_b,sizeof(BCK_OBJ));\
 	memcpy((bkg_stazioni),sfondo_staz,num_b*sizeof(BCK_OBJ));\
	AllocaColoriSfondo(topLevelShellStaz,bkg_stazioni);\
	}\
else\
	leggi_file_bck(PadreStaz,PaginaStaz,"bkg",&(bkg_stazioni),dim);\
\
region_staz=NULL;\
/* setto il nome della pagina */\
set_something(topLevelShellStaz,XmNtitle,PaginaStaz);\
set_something(topLevelShellStaz,XmNiconName,PaginaStaz);\
set_something(topLevelShellStaz,XmNx,top_x);\
set_something(topLevelShellStaz,XmNy,top_y);\
set_something(topLevelShellStaz,XmNwidth,top_width);\
set_something(topLevelShellStaz,XmNheight,top_height);\
set_something(drawingAreaStaz,XmNwidth,drawing_width);\
set_something(drawingAreaStaz,XmNheight,drawing_height);\
if(drawing_pixmap)\
	set_something(drawingAreaStaz,XmNbackgroundPixmap,drawing_pixmap);\
else\
	set_something(drawingAreaStaz,XmNbackground,drawing_background);\
#ifndef DESIGN_TIME\
LoadBitmap(scrolledWindowStaz,&pix,page_staz_icon_bits,page_staz_icon_width,page_staz_icon_height);\
#endif\
set_something(rtrn,XmNiconPixmap,pix);\
#ifndef DESIGN_TIME\
LoadFont(FONT_LABEL,&FontLabelStaz,XtDisplay(rtrn));\
#endif\
set_something(menu1_p1_b1,XmNfontList,FontLabelStaz);\
set_something(menu1_p1_b3,XmNfontList,FontLabelStaz);\
set_something(menu1_p2_b1,XmNfontList,FontLabelStaz);\
set_something(menu1_p2_b2,XmNfontList,FontLabelStaz);\
\
\
#ifndef DESIGN_TIME\
if(!CreaPagina(drawingAreaStaz,&lista_widStaz, &num_widStaz))\
	return(NULL);\
#endif\
/*\
	inserisco la drawing area nell'elenco delle pagine attive\
*/\
#ifndef DESIGN_TIME\
if((key_refresh_staz=InsElencoPagine(PaginaStaz,lista_widStaz,num_widStaz,time_ref_staz)) == -1)\
	return(NULL);\
#endif\
UxPopupInterface(rtrn, no_grab);\
/*\
	creo il cursore di wait\
*/\
cursor_wait_staz = XlCreateWaitCursor(rtrn);\
SetCursorWaitStaz(drawingAreaStaz);\
wid_attesa_staz=NULL;\
attesa_staz = 0;\
timer_refresh_staz = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (topLevelShellStaz),\
            (unsigned long) (time_ref_staz*100) ,refresh_page, UxContext);\
RaisePlotAing();\
/*\
Quando uso la close della MWM della decorazione attivo la finestra di close\
*/\
 WM_DELETE_WINDOW=XmInternAtom(XtDisplay(topLevelShellStaz),"WM_DELETE_WINDOW",False);\
XmAddWMProtocolCallback(topLevelShellStaz,WM_DELETE_WINDOW,activateCB_menu1_p1_b1,NULL);\
\
\
return(rtrn);\

*topLevelShellStaz.auxdecl: void SetCursorWaitStaz(Widget w)\
{\
#ifndef DESIGN_TIME\
_UxCtopLevelShellStaz *Context;\
Context =(_UxCtopLevelShellStaz *) UxGetContext( w);\
\
XlSetCursor(Context->UxdrawingAreaStaz,Context->Uxcursor_wait_staz);\
Context->Uxcursor_wait_set_staz = 1;\
\
#endif\
}\
\
void UnsetCursorWaitStaz(Widget w)\
{\
#ifndef DESIGN_TIME\
_UxCtopLevelShellStaz *Context;\
Context =(_UxCtopLevelShellStaz *) UxGetContext( w);\
\
if(Context->Uxcursor_wait_set_staz == 1)\
	{\
	Context->Uxcursor_wait_set_staz = 0;\
	XlUnsetCursor(Context->UxdrawingAreaStaz);\
	}\
#endif\
}\
\
void IcoSelectStaz(w)\
 Widget w;\
{\
XlCoreWidget wcore;\
XlManagerWidget wmanager;\
Widget drawing;\
#ifndef DESIGN_TIME\
_UxCtopLevelShellStaz *Context;\
#endif\
 \
\
#ifndef DESIGN_TIME\
/* Ricavo il context */\
drawing=XtParent(w);\
\
#ifndef DESIGN_TIME\
if(XlIsXlComposite(drawing))\
	drawing=XtParent(drawing);\
#endif\
\
Context =(_UxCtopLevelShellStaz *) UxGetContext( drawing);\
#endif\
printf("IcoSelectStaz\n");\
#ifndef DESIGN_TIME\
		if(XlIsGraficoSingle(w))\
		    {\
		/*\
		Uso la ActivateChangeVar solo quando mmi e' invocato \
		con il flag -Topologia. (ActivateChangeVar utilizza il Variable\
		Editor che utilizza la topologia caricata in shm).\
		*/\
		    if(topologia_on)			\
		        if(!ActivateChangeVar(w,Context->UxdrawingAreaStaz,\
				&(Context->UxListaWidVarStaz[0])))\
			    popup_errorDialog("Error changig tag",\
				Context->UxdrawingAreaStaz);\
		    }\
#endif\
\
\
}\
\
#ifndef DESIGN_TIME\
static void refresh_page(_UxCtopLevelShellStaz *Context)\
#else\
static void refresh_page()\
#endif\
{\
int i;\
#ifndef DESIGN_TIME\
if(Context->Uxattesa_staz != -1)\
	{\
	++ Context->Uxattesa_staz;\
	if(Context->Uxattesa_staz ==2)\
		{\
		Context->Uxwid_attesa_staz=popup_Attesa(Context->UxdrawingAreaStaz);\
		\
		}\
	}\
if(Context->Uxwid_attesa_staz != NULL)\
	SettaAttesa(Context->Uxwid_attesa_staz,Context->Uxtime_ref_staz);\
\
if(!OlSetDataPage(database_simulatore,Context->Uxkey_refresh_staz))\
        {\
        show_warning("Error in refresh");\
        return;\
        }\
if(OlGetDataStatus(database_simulatore,Context->Uxkey_refresh_staz))   \
   {\
   Context->Uxattesa_staz = -1;\
   if(Context->Uxwid_attesa_staz != NULL)\
	{\
	XtDestroyWidget(Context->Uxwid_attesa_staz);\
	Context->Uxwid_attesa_staz=NULL;\
	}\
	UnsetCursorWaitStaz(Context->UxdrawingAreaStaz);\
	XlRefreshWidget(Context->Uxlista_widStaz,Context->Uxnum_widStaz);\
\
   }\
if(!OlUnsetDataPage(database_simulatore,Context->Uxkey_refresh_staz))\
        {\
        show_warning("Error in refresh");\
        return;\
        }\
/*\
        carica il timer per il refresh\
*/\
Context->Uxtimer_refresh_staz = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (Context->UxtopLevelShellStaz),\
            (unsigned long) (Context->Uxtime_ref_staz*100) ,\
		refresh_page, Context);\
#endif\
}\
\
void PageStazSelect(Widget w, char *nomePagina, int tipoApertura)\
{\
Widget Pagina_new = NULL;\
#ifndef DESIGN_TIME\
_UxCtopLevelShellStaz *Context;\
int num_pag;\
\
Context =(_UxCtopLevelShellStaz *) UxGetContext(w);\
\
SetCursorWaitStaz(Context->UxdrawingAreaStaz);\
\
if(nomePagina!=NULL)\
     {\
	if(tipoApertura != CLOSE_PAGE)\
	{\
        if(!PaginaAperta(Context->UxtopLevel_selezionataStaz,nomePagina))\
                {\
	if(!CanOpenPage(w))\
		{\
		UnsetCursorWaitStaz(Context->UxdrawingAreaStaz);\
		return;\
		}\
		\
        num_pag=NumeroPagina(nomePagina);\
        Pagina_new=create_topLevelShell1(nomePagina,\
                        Context->UxtopLevel_selezionataStaz,\
                        Context->Uxnome_dispStaz,pagine[num_pag].sfondo);\
        if(Pagina_new==NULL)\
                {\
                popup_errorDialog("Errore Creazione pagina",\
                        w/*Context->UxdrawingAreaStaz*/);\
		UnsetCursorWaitStaz(Context->UxdrawingAreaStaz);\
                return;\
                }\
                }\
	}\
        if((tipoApertura == CHANGE_PAGE)||(tipoApertura == CLOSE_PAGE))\
                {\
		DelElencoPagine(Context->Uxkey_refresh_staz, \
			Context->UxdrawingAreaStaz);\
		XSync(XtDisplay(w),False);\
                XtRemoveTimeOut(Context->Uxtimer_refresh_staz);\
                XtDestroyWidget(Context->UxtopLevelShellStaz);\
                }\
        }\
UnsetCursorWaitStaz(Context->UxdrawingAreaStaz);\
#endif	\
}\
\
ClosePageStaz(Widget w)\
{\
#ifndef DESIGN_TIME\
_UxCtopLevelShellStaz *Context;\
 \
	Context =(_UxCtopLevelShellStaz *) UxGetContext(w);\
        DelElencoPagine(Context->Uxkey_refresh_staz, \
		Context->UxdrawingAreaStaz);\
	XSync(XtDisplay(w),False);\
	XtRemoveTimeOut(Context->Uxtimer_refresh_staz);\
	XlFreeCursor(Context->UxtopLevelShellStaz,Context->Uxcursor_wait_staz);\
	if(drawing_pixmap)\
		XFreePixmap(XtDisplay(w),drawing_pixmap);\
	XtDestroyWidget(Context->UxtopLevelShellStaz);\
        XrmDestroyDatabase(Context->Uxpag_db);\
	printf("Close Page Stazioni\n");\
#endif\
}
*topLevelShellStaz.static: true
*topLevelShellStaz.name: topLevelShellStaz
*topLevelShellStaz.parent: NO_PARENT
*topLevelShellStaz.parentExpression: topLevel_selezionataStaz
*topLevelShellStaz.x: 110
*topLevelShellStaz.y: 30
*topLevelShellStaz.width: 1060
*topLevelShellStaz.height: 900
*topLevelShellStaz.background: "#000000"
*topLevelShellStaz.iconName.source: public
*topLevelShellStaz.iconName: "topLevelShell2"
*topLevelShellStaz.title.source: public
*topLevelShellStaz.title: "topLevelShell2"
*topLevelShellStaz.mwmDecorations: MWM_DECOR_TITLE | MWM_DECOR_RESIZEH | MWM_DECOR_MINIMIZE | MWM_DECOR_MAXIMIZE
*topLevelShellStaz.deleteResponse: "do_nothing"

*formStaz.class: form
*formStaz.static: true
*formStaz.name: formStaz
*formStaz.parent: topLevelShellStaz
*formStaz.resizePolicy: "resize_none"
*formStaz.unitType: "pixels"
*formStaz.x: 10
*formStaz.y: 10
*formStaz.width: 880
*formStaz.height: 870

*scrolledWindowStaz.class: scrolledWindow
*scrolledWindowStaz.static: true
*scrolledWindowStaz.name: scrolledWindowStaz
*scrolledWindowStaz.parent: formStaz
*scrolledWindowStaz.scrollingPolicy: "automatic"
*scrolledWindowStaz.x: 10
*scrolledWindowStaz.y: 0
*scrolledWindowStaz.width: 1100
*scrolledWindowStaz.height: 940
*scrolledWindowStaz.bottomAttachment: "attach_form"
*scrolledWindowStaz.rightAttachment: "attach_form"
*scrolledWindowStaz.topAttachment: "attach_form"
*scrolledWindowStaz.background: "#50a050"
*scrolledWindowStaz.leftAttachment: "attach_form"
*scrolledWindowStaz.navigationType: "none"
*scrolledWindowStaz.traversalOn: "false"

*drawingAreaStaz.class: drawingArea
*drawingAreaStaz.static: true
*drawingAreaStaz.name: drawingAreaStaz
*drawingAreaStaz.parent: scrolledWindowStaz
*drawingAreaStaz.resizePolicy: "resize_none"
*drawingAreaStaz.x: 4
*drawingAreaStaz.y: 14
*drawingAreaStaz.width: 1200
*drawingAreaStaz.height: 1190
*drawingAreaStaz.background: "#000000"
*drawingAreaStaz.borderColor: "#000000"
*drawingAreaStaz.exposeCallback: {\
disegna_bck(UxWidget,bkg_stazioni,UxCallbackArg,&(region_staz),False);\
}
*drawingAreaStaz.marginHeight: 0
*drawingAreaStaz.marginWidth: 0
*drawingAreaStaz.navigationType: "none"
*drawingAreaStaz.traversalOn: "false"

*menu1.class: rowColumn
*menu1.static: true
*menu1.name: menu1
*menu1.parent: drawingAreaStaz
*menu1.rowColumnType: "menu_popup"
*menu1.menuAccelerator: "<KeyUp>F4"

*menu1_p2.class: rowColumn
*menu1_p2.static: true
*menu1_p2.name: menu1_p2
*menu1_p2.parent: menu1
*menu1_p2.rowColumnType: "menu_pulldown"
*menu1_p2.background: "#50a050"

*menu1_p2_b1.class: pushButton
*menu1_p2_b1.static: true
*menu1_p2_b1.name: menu1_p2_b1
*menu1_p2_b1.parent: menu1_p2
*menu1_p2_b1.labelString: "print"
*menu1_p2_b1.background: "#50a050"
*menu1_p2_b1.activateCallback: {\
#ifndef DESIGN_TIME\
if(!PrintScreen(drawingAreaStaz,nome_dispStaz,PaginaStaz,False,bkg_stazioni))\
	popup_errorDialog("Printer not available",drawingAreaStaz);\
#endif\
}

*menu1_p2_b2.class: pushButton
*menu1_p2_b2.static: true
*menu1_p2_b2.name: menu1_p2_b2
*menu1_p2_b2.parent: menu1_p2
*menu1_p2_b2.labelString: "Printer setup"
*menu1_p2_b2.background: "#50a050"
*menu1_p2_b2.activateCallback: {\
#ifndef DESIGN_TIME\
if(PrintSetup(drawingAreaStaz)==NULL)\
	popup_errorDialog("Printer not available",drawingAreaStaz);\
#endif\
}

*menu1_p1_b3.class: cascadeButton
*menu1_p1_b3.static: true
*menu1_p1_b3.name: menu1_p1_b3
*menu1_p1_b3.parent: menu1
*menu1_p1_b3.labelString: "Harcopy"
*menu1_p1_b3.subMenuId: "menu1_p2"
*menu1_p1_b3.background: "#50a050"

*menu1_p1_b4.class: separator
*menu1_p1_b4.static: true
*menu1_p1_b4.name: menu1_p1_b4
*menu1_p1_b4.parent: menu1
*menu1_p1_b4.background: "#50a050"

*menu1_p1_b1.class: pushButton
*menu1_p1_b1.static: true
*menu1_p1_b1.name: menu1_p1_b1
*menu1_p1_b1.parent: menu1
*menu1_p1_b1.labelString: "Close the page"
*menu1_p1_b1.background: "#50a050"
*menu1_p1_b1.activateCallback: {\
printf("Chiusura della pagina\n");\
if(!CanClosePage(PaginaStaz))\
	{\
	popup_errorDialog("Unable to close this page",drawingAreaStaz);\
	return;\
	}\
#ifndef DESIGN_TIME\
popup_CloseQuestion(topLevelShellStaz,drawingAreaStaz,&(timer_refresh_staz),\
	key_refresh_staz);\
#endif\
\
}

