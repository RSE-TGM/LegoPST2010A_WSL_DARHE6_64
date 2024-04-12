! UIMX ascii 2.5 key: 9155                                                      

*topLevelShell1.class: topLevelShell
*topLevelShell1.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo topLevelShell1.i\
   tipo \
   release 5.2\
   data 1/22/96\
   reserved @(#)topLevelShell1.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
#include <X11/Xlib.h>\
\
#ifdef SCO_UNIX\
#include <Xm/MwmUtil.h>\
#else\
#include <Xm/MwmUtil.h>\
#endif\
\
#include <X11/cursorfont.h>\
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
\
#include <Xl/XlDispReg.h>\
#include <Xl/XlPort.h>\
\
\
#include <Ol/OlDatabasePunti.h>\
\
#ifndef DESIGN_TIME\
#include <Ol/OlPertP.h>\
#else\
#include <Ol/OlPert.h>\
#endif\
\
#include <Rt/RtMemory.h>\
#include <Xm/Protocols.h>\
#include "page_sin_icon.bmp"\
#include "nop_button.bmp"\
#include "xaing_button.bmp"\
#include "xstaz_button.bmp"\
#include "xplot_button.bmp"\
#include "info_button.bmp"\
#include "close_button.bmp"\
#include "xreg_button.bmp"\
\
#include "other.h"\
#include "ric_aing.h"\
 \
\
extern Widget listDrawing[MAX_PAGE];\
extern swidget popup_topLevelShellStaz();\
extern OlDatabasePuntiObject database_simulatore;\
extern OlPertObject pert;\
extern AN_PAG *pagine;\
extern int totale_pagine;\
extern Boolean topologia_on;\
\
extern Boolean EsistePagina();\
\
static void refresh_page( );\
void SetCursorWait( );\
void UnsetCursorWait( );\

*topLevelShell1.ispecdecl: int operazione_attiva;\
Widget topLevel_selezionata;\
XtIntervalId    timer_refresh;\
WidgetList lista_wid;\
int num_wid;\
Region region_sin;\
BCK_OBJ * bkg_sin;\
Widget ListaWidVar[7];\
int key_refresh;\
int time_ref;\
Widget wid_attesa;\
int attesa;\
int cursor_wait_set;\
Cursor cursor_wait;\
XrmDatabase pag_db;\
Pixmap drawing_pixmap;\

*topLevelShell1.ispeclist: operazione_attiva, topLevel_selezionata, timer_refresh, lista_wid, num_wid, region_sin, bkg_sin, ListaWidVar, key_refresh, time_ref, wid_attesa, attesa, cursor_wait_set, cursor_wait, pag_db, drawing_pixmap
*topLevelShell1.ispeclist.operazione_attiva: "int", "%operazione_attiva%"
*topLevelShell1.ispeclist.topLevel_selezionata: "Widget", "%topLevel_selezionata%"
*topLevelShell1.ispeclist.timer_refresh: "XtIntervalId", "%timer_refresh%"
*topLevelShell1.ispeclist.lista_wid: "WidgetList", "%lista_wid%"
*topLevelShell1.ispeclist.num_wid: "int", "%num_wid%"
*topLevelShell1.ispeclist.region_sin: "Region", "%region_sin%"
*topLevelShell1.ispeclist.bkg_sin: "BCK_OBJ", "*%bkg_sin%"
*topLevelShell1.ispeclist.ListaWidVar: "Widget", "%ListaWidVar%[7]"
*topLevelShell1.ispeclist.key_refresh: "int", "%key_refresh%"
*topLevelShell1.ispeclist.time_ref: "int", "%time_ref%"
*topLevelShell1.ispeclist.wid_attesa: "Widget", "%wid_attesa%"
*topLevelShell1.ispeclist.attesa: "int", "%attesa%"
*topLevelShell1.ispeclist.cursor_wait_set: "int", "%cursor_wait_set%"
*topLevelShell1.ispeclist.cursor_wait: "Cursor", "%cursor_wait%"
*topLevelShell1.ispeclist.pag_db: "XrmDatabase", "%pag_db%"
*topLevelShell1.ispeclist.drawing_pixmap: "Pixmap", "%drawing_pixmap%"
*topLevelShell1.funcdecl: swidget create_topLevelShell1(Pagina,Padre,nome_disp,sfondo_sin)\
char *Pagina;\
Widget Padre;\
char *nome_disp;\
BCK_OBJ *sfondo_sin;\

*topLevelShell1.funcname: create_topLevelShell1
*topLevelShell1.funcdef: "swidget", "<create_topLevelShell1>(%)"
*topLevelShell1.argdecl: unsigned char *Pagina;\
Widget Padre;\
unsigned char *nome_disp;\
BCK_OBJ *sfondo_sin;
*topLevelShell1.arglist: Pagina, Padre, nome_disp, sfondo_sin
*topLevelShell1.arglist.Pagina: "unsigned char", "*%Pagina%"
*topLevelShell1.arglist.Padre: "Widget", "%Padre%"
*topLevelShell1.arglist.nome_disp: "unsigned char", "*%nome_disp%"
*topLevelShell1.arglist.sfondo_sin: "BCK_OBJ", "*%sfondo_sin%"
*topLevelShell1.icode: int top_x,top_y,top_width,top_height,drawing_width,drawing_height;\
char *top_tipo, *top_descrizione;\
Pixel *drawing_background;\
Pixmap pix;\
XmFontList FontTasti, FontLabel;\
int dim[4];\
int num_b;\
Atom WM_DELETE_WINDOW;  /* per distruz. pag da MWM */\
static void activateCB_menu2_p2_b1();\
drawing_pixmap=0;\
printf("Selezionata la Pagina %s display = %s\n",Pagina,nome_disp);\
if(!EsistePagina(Pagina))\
	return(NULL);\
\
/*\
	inizializzo il campo operazione attiva\
	-1 -> nessuna operazione\
	 1 -> xaing\
	 2 -> xplot\
	 3 -> xstaz\
	 4 -> info\
*/\
operazione_attiva = OPERAZIONE_NOP;\
cursor_wait_set = 0;\
topLevel_selezionata=Padre;\
\
#ifndef DESIGN_TIME\
if(!(pag_db=CaricaDB(XtDisplay(topLevel_selezionata),Pagina)))\
	return(False);\
\
if(!GetResTopLevel(Padre,&top_x,&top_y,&top_width,&top_height,&time_ref,\
		&top_tipo,&top_descrizione))\
	return(False);\
if(!GetResDrawing(Padre,&drawing_width,&drawing_height,&drawing_background,&drawing_pixmap))\
		return(False);\
if(strcmp(top_tipo,"Stazioni")==0)\
	return(popup_topLevelShellStaz(Pagina,Padre,nome_disp,sfondo_sin));\
#endif\
printf("Caricate le risorse\n");\
\

*topLevelShell1.fcode: /*\
  inizializza la regione di ridisegno\
*/\
#ifndef DESIGN_TIME\
if(sfondo_sin!=NULL)\
	{\
 	num_b=1;\
 	while(sfondo_sin[num_b-1].tipo>0)\
  		num_b++;\
 	(bkg_sin)=(BCK_OBJ*)XtCalloc(num_b,sizeof(BCK_OBJ));\
 	memcpy((bkg_sin),sfondo_sin,num_b*sizeof(BCK_OBJ));\
	AllocaColoriSfondo(topLevelShell1,bkg_sin);\
	}\
else\
	leggi_file_bck(Padre,Pagina,"bkg",&(bkg_sin),dim);\
\
#endif\
region_sin=NULL;\
\
/* setto il nome della pagina */\
set_something(topLevelShell1,XmNtitle,Pagina);\
set_something(topLevelShell1,XmNiconName,Pagina);\
set_something(topLevelShell1,XmNx,top_x);\
set_something(topLevelShell1,XmNy,top_y);\
set_something(topLevelShell1,XmNwidth,top_width+50);\
set_something(topLevelShell1,XmNheight,top_height);\
set_something(drawingSinottico,XmNwidth,drawing_width);\
set_something(drawingSinottico,XmNheight,drawing_height);\
if(drawing_pixmap)\
	set_something(drawingSinottico,XmNbackgroundPixmap,drawing_pixmap);\
else	\
	set_something(drawingSinottico,XmNbackground,drawing_background);\
\
\
LoadBitmap(formMenu,&pix,page_sin_icon_bits,page_sin_icon_width,page_sin_icon_height);\
set_something(rtrn,XmNiconPixmap,pix);\
\
LoadBitmap(drawnButtonNop,&pix,nop_button_bits,nop_button_width,nop_button_height);\
set_something(drawnButtonNop,XmNlabelPixmap,pix);\
/*\
Inserisco controllo su abilitazione bottoni\
*/\
set_something(drawnButtonXaing,XmNsensitive,topologia_on);\
LoadBitmap(drawnButtonXaing,&pix,xaing_button_bits,xaing_button_width,xaing_button_height);\
set_something(drawnButtonXaing,XmNlabelPixmap,pix);\
\
/*\
Staz e' sempre abilitato\
*/\
LoadBitmap(drawnButtonXstaz,&pix,xstaz_button_bits,xstaz_button_width,xstaz_button_height);\
set_something(drawnButtonXstaz,XmNlabelPixmap,pix);\
\
set_something(drawnButtonXplot,XmNsensitive,topologia_on);\
LoadBitmap(drawnButtonXplot,&pix,xplot_button_bits,xplot_button_width,xplot_button_height);\
set_something(drawnButtonXplot,XmNlabelPixmap,pix);\
\
LoadBitmap(drawnButtonInfo,&pix,info_button_bits,info_button_width,info_button_height);\
set_something(drawnButtonInfo,XmNlabelPixmap,pix);\
\
LoadBitmap(drawnButtonClose,&pix,close_button_bits,close_button_width,close_button_height);\
set_something(drawnButtonClose,XmNlabelPixmap,pix);\
\
LoadBitmap(drawnButtonReg,&pix,xreg_button_bits,xreg_button_width,xreg_button_height);\
set_something(drawnButtonReg,XmNlabelPixmap,pix);\
\
#ifndef DESIGN_TIME\
LoadFont(FONT_TASTI,&FontTasti,XtDisplay(rtrn));\
LoadFont(FONT_LABEL,&FontLabel,XtDisplay(rtrn));\
#endif\
set_something(label1,XmNfontList,FontTasti);\
set_something(label2,XmNfontList,FontTasti);\
set_something(label3,XmNfontList,FontTasti);\
set_something(label4,XmNfontList,FontTasti);\
set_something(label5,XmNfontList,FontTasti);\
set_something(label6,XmNfontList,FontTasti);\
set_something(menu2_p2_b1,XmNfontList,FontLabel);\
set_something(menu2_p2_b3,XmNfontList,FontLabel);\
set_something(menu2_p3_b1,XmNfontList,FontLabel);\
set_something(menu2_p3_b2,XmNfontList,FontLabel);\
set_something(DispTagModeButton,XmNfontList,FontLabel);\
set_something(DispValueModeButton,XmNfontList,FontLabel);\
set_something(DispUnmanagedModeButton,XmNfontList,FontLabel);\
set_something(MenuRegMode,XmNfontList,FontLabel);\
set_something(MenuPortMode,XmNfontList,FontLabel);\
set_something(DispPortModeButton,XmNfontList,FontLabel);\
set_something(NoDispPortModeButton,XmNfontList,FontLabel);\
#ifndef DESIGN_TIME \
if(!CreaPagina(drawingSinottico,&lista_wid, &num_wid))\
	return(NULL);\
#endif\
\
/*\
	inserisco la drawing area nell'elenco delle pagine attive\
*/\
#ifndef DESIGN_TIME\
if((key_refresh=InsElencoPagine(Pagina,lista_wid,num_wid,time_ref)) == -1)\
	return(NULL);\
#endif\
UxPopupInterface(rtrn,nonexclusive_grab);\
/*\
	creo il cursore di wait\
*/\
cursor_wait = XlCreateWaitCursor(rtrn);\
SetCursorWait(drawingSinottico);\
wid_attesa=NULL;\
attesa = 0;\
\
timer_refresh = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (topLevelShell1),\
            (unsigned long) (time_ref*100) ,refresh_page, UxContext);\
RaisePlotAing();\
\
/*\
chiamo la callback per distruggere la pagina quando uso close dell' MWM\
*/\
WM_DELETE_WINDOW=XmInternAtom(XtDisplay(topLevelShell1),"WM_DELETE_WINDOW",False);\
XmAddWMProtocolCallback(topLevelShell1,WM_DELETE_WINDOW,activateCB_menu2_p2_b1,NULL);\
\
return(rtrn);\

*topLevelShell1.auxdecl: void SetCursorWait(Widget w)\
{\
#ifndef DESIGN_TIME\
_UxCtopLevelShell1 *Context;\
Context =(_UxCtopLevelShell1 *) UxGetContext( w);\
\
XlSetCursor(Context->UxdrawingSinottico,Context->Uxcursor_wait);\
Context->Uxcursor_wait_set = 1;\
\
#endif\
}\
\
void UnsetCursorWait(Widget w)\
{\
#ifndef DESIGN_TIME\
_UxCtopLevelShell1 *Context;\
Context =(_UxCtopLevelShell1 *) UxGetContext( w);\
\
if(Context->Uxcursor_wait_set == 1)\
	{\
	Context->Uxcursor_wait_set = 0;\
	XlUnsetCursor(Context->UxdrawingSinottico);\
	}\
#endif\
}\
\
void IcoSelect(w)\
 Widget w;\
{\
XlCoreWidget wcore;\
XlManagerWidget wmanager;\
Widget Pagina_staz=NULL;\
Widget drawing;\
int operazione=0;\
#ifndef DESIGN_TIME\
_UxCtopLevelShell1 *Context;\
#endif\
 \
\
#ifndef DESIGN_TIME\
/* Ricavo il context */\
drawing=XtParent(w);\
if(XlIsXlComposite(drawing))\
	drawing=XtParent(drawing);\
\
Context =(_UxCtopLevelShell1 *) UxGetContext( drawing);\
operazione=Context->Uxoperazione_attiva;\
#endif\
	\
printf("IcoSelect %d\n",operazione_attiva);\
\
switch(operazione){\
	case OPERAZIONE_NOP:\
		{\
#ifndef DESIGN_TIME\
		if(XlIsGraficoSingle(w))\
		    {		\
		    /*\
		     Viene chiamata ActivateChangeVar solo quando mmi e'\
	  	     invocato con l' opzione -Topologia\
		    */ 	\
		    if(topologia_on)\
		    	if(!ActivateChangeVar(w,Context->UxdrawingSinottico,\
				&(Context->UxListaWidVar[0])))\
				popup_errorDialog("Error changig tag",\
				Context->UxdrawingSinottico);\
		    }\
#endif\
		break;\
		}\
	case OPERAZIONE_INFO:\
		{\
#ifndef DESIGN_TIME\
	        popup_formInfo(w,Context->UxtopLevel_selezionata);\
#endif\
		break;\
		};\
case OPERAZIONE_XAING:\
		{\
#ifndef DESIGN_TIME\
#if defined SCADA_MMI\
		/*\
			al momento XAING non e' utilizzabile\
		*/\
		popup_errorDialog("AING not available",\
				Context->UxdrawingSinottico);\
		break;\
#endif\
		if(AcceptAing(w))\
			{\
\
		         if(!ActivateAing(w,Context->UxdrawingSinottico,\
				Context->Uxnome_disp,\
				&(Context->UxListaWidVar[0])))\
			    popup_errorDialog("Variable not defined",\
				Context->UxdrawingSinottico);\
			}\
		else\
			popup_errorDialog("AING not available for this object",\
					Context->UxdrawingSinottico);\
#endif\
		break;\
		}\
case OPERAZIONE_XPLOT:\
		{\
#ifndef DESIGN_TIME\
		if(AcceptPlot(w))\
			{\
			if(!ActivatePlot(w,Context->UxdrawingSinottico,\
				Context->Uxnome_disp,\
				&(Context->UxListaWidVar[0])))\
			    popup_errorDialog("Variable not defined",\
				Context->UxdrawingSinottico);\
			}\
		else\
			popup_errorDialog("PLOT not available for this object",\
					Context->UxdrawingSinottico);\
#endif\
		break;\
		}\
        case OPERAZIONE_XSTAZ:\
		{\
		if(XlIsXlCore(w))\
			{\
			wcore=(XlCoreWidget)w;\
#ifndef DESIGN_TIME\
/***\
			printf("Apro la pagina di stazioni %s\n",\
				wcore->xlcore.pagina_staz);\
***/\
			if(!EsistePagina(\
				wcore->xlcore.pagina_staz))\
				{\
				popup_errorDialog("Pagina inesistente",\
					w/*Context->UxdrawingSinottico*/);\
				break;\
				}\
			if(wcore->xlcore.pagina_staz!=NULL)\
				{\
				int j;\
                                for(j=0; j<totale_pagine;j++)\
                                        if(strcmp(wcore->xlcore.pagina_staz,\
                                                pagine[j].nome)==0)\
                                                break;\
\
				Pagina_staz=popup_topLevelShellStaz(\
				   wcore->xlcore.pagina_staz,\
				   Context->UxtopLevel_selezionata,nome_disp,pagine[j].sfondo);\
				}\
                        if(Pagina_staz==NULL)\
				popup_errorDialog("Errore Creazione pagina",\
					w/*Context->UxdrawingSinottico*/);\
#endif\
			}\
		else\
			{\
                       \
			wmanager=(XlManagerWidget)w;\
#ifndef DESIGN_TIME\
/***\
			printf("Apro la pagina di stazioni %s\n",\
				wmanager->xlmanager.pagina_staz);\
***/\
			if(!EsistePagina(\
				wmanager->xlmanager.pagina_staz))\
				{\
				popup_errorDialog("Pagina inesistente",\
					w/*Context->UxdrawingSinottico*/);\
				break;\
				}\
			if(PaginaAperta(Context->UxtopLevel_selezionata,\
				wmanager->xlmanager.pagina_staz))\
				break;\
			if(!CanOpenPage(w))\
				break;\
			if(wmanager->xlmanager.pagina_staz!=NULL)\
				Pagina_staz=popup_topLevelShellStaz(\
				   wmanager->xlmanager.pagina_staz,\
				   Context->UxtopLevel_selezionata,nome_disp,NULL);\
                        if(Pagina_staz==NULL)\
				popup_errorDialog("Errore Creazione pagina",\
					w/*Context->UxdrawingSinottico*/);\
#endif\
			}\
		break;\
    		}\
        case OPERAZIONE_REG:\
/* individuo tramite ilcampo object_tag di xlcore la pagina da aprire\
   e la apro\
*/\
#ifndef DESIGN_TIME\
           if( XlIsXlCore(w))\
           {\
printf("Richiamata la operazione OPERAZIONE_REG\n");\
\
              wcore = (XlCoreWidget)w;\
printf("Apro la pagina di regolazione %s\n",wcore->xlcore.object_tag);\
\
              if( !EsistePagina(wcore->xlcore.object_tag))\
              {\
                 popup_errorDialog("Pagina di regolazione inesistente",w);\
                 break;\
              }\
              if( wcore->xlcore.object_tag!=NULL)\
              {\
                 int j;\
                \
                 for(j=0;j<totale_pagine;j++)\
                    if( strcmp(wcore->xlcore.object_tag,pagine[j].nome) == 0 )\
                       break;\
                 Pagina_staz=popup_topLevelShellStaz( wcore->xlcore.object_tag,\
                                 Context->UxtopLevel_selezionata,nome_disp,pagine[j].sfondo);\
              }\
\
              if( Pagina_staz == NULL )\
                 popup_errorDialog("Errore creazione pagina",w);\
\
           }\
	   else\
           {\
                       \
		wmanager=(XlManagerWidget)w;\
		printf("Apro la pagina di stazioni %s\n",\
				wmanager->xlmanager.object_tag);\
\
		if(!EsistePagina(wmanager->xlmanager.object_tag))\
		{\
		   popup_errorDialog("Pagina inesistente",w);\
		   break;\
		}\
		if(PaginaAperta(Context->UxtopLevel_selezionata,wmanager->xlmanager.object_tag))\
		   break;\
		if(!CanOpenPage(w))\
		   break;\
		if(wmanager->xlmanager.object_tag!=NULL)\
		   Pagina_staz=popup_topLevelShellStaz(\
				   wmanager->xlmanager.object_tag,\
				   Context->UxtopLevel_selezionata,nome_disp,NULL);\
                if(Pagina_staz==NULL)\
	           popup_errorDialog("Errore Creazione pagina",w);\
	  }\
#endif\
        break;\
	};\
}\
\
\
\
#ifndef DESIGN_TIME\
static void refresh_page(_UxCtopLevelShell1 *Context)\
#else\
static void refresh_page()\
#endif\
{\
int i;\
\
\
#ifndef DESIGN_TIME\
/*** carlo 3-12-97\
**/\
if(Context->Uxattesa != -1)\
	{\
	++ Context->Uxattesa;\
	if(Context->Uxattesa ==2)\
		{\
		Context->Uxwid_attesa=popup_Attesa(Context->UxdrawingSinottico);\
		}\
	}\
if(Context->Uxwid_attesa != NULL)\
	SettaAttesa(Context->Uxwid_attesa,Context->Uxtime_ref);\
\
\
if(!OlSetDataPage(database_simulatore,Context->Uxkey_refresh))\
        {\
        show_warning("Error in refresh");\
        return;\
        }\
if(OlGetDataStatus(database_simulatore,Context->Uxkey_refresh))\
   {\
   Context->Uxattesa = -1;\
   if(Context->Uxwid_attesa != NULL)\
	{\
	XtDestroyWidget(Context->Uxwid_attesa);\
	Context->Uxwid_attesa=NULL;\
	}\
\
   UnsetCursorWait(Context->UxdrawingSinottico);\
	\
   XlRefreshWidget(Context->Uxlista_wid,Context->Uxnum_wid);\
   }\
if(!OlUnsetDataPage(database_simulatore,Context->Uxkey_refresh))\
        {\
        show_warning("Error in refresh");\
        return;\
        }\
/*\
        carica il timer per il refresh\
*/\
Context->Uxtimer_refresh = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (Context->UxtopLevelShell1),\
            (unsigned long) (Context->Uxtime_ref*100) ,refresh_page, Context);\
#endif\
}\
\
void PageSelect(Widget w, char *nomePagina, int tipoApertura)\
{\
Widget Pagina_new = NULL;\
#ifndef DESIGN_TIME\
Boolean sostituzione = False;\
_UxCtopLevelShell1 *Context;\
int dim[4];\
int num_pag;\
 \
Context =(_UxCtopLevelShell1 *) UxGetContext(w);\
\
SetCursorWait(Context->UxdrawingSinottico);\
\
if((tipoApertura == CHANGE_PAGE)&& sostituzione)\
	{\
	if(!EsistePagina(nomePagina))\
		{\
	 	popup_errorDialog("Errore Creazione pagina",w);\
		return;\
		}\
	if(!CaricaDB(XtDisplay(Context->UxtopLevel_selezionata),nomePagina))\
		{\
		UnsetCursorWait(Context->UxdrawingSinottico);\
		return;\
		}\
	XtFree(Context->Uxbkg_sin);\
	leggi_file_bck(w,nomePagina,"bkg",&(Context->Uxbkg_sin),dim);\
 	Context->Uxregion_sin=NULL;\
 	DistruggiPagina(Context->Uxlista_wid,Context->Uxnum_wid);\
	if(!CreaPagina(Context->UxdrawingSinottico,&(Context->Uxlista_wid),\
		 &(Context->Uxnum_wid)))\
		{\
		UnsetCursorWait(Context->UxdrawingSinottico);\
		return;\
		}	\
	}\
else\
	{\
        if((nomePagina!=NULL)||(tipoApertura == CLOSE_PAGE))\
                {\
		if(tipoApertura != CLOSE_PAGE)\
                {        \
                if(!PaginaAperta(Context->UxtopLevel_selezionata,nomePagina))\
                  {\
		  if(!CanOpenPage(w))\
			{\
			UnsetCursorWait(Context->UxdrawingSinottico);\
			return;\
			}\
                  num_pag=NumeroPagina(nomePagina);\
                  Pagina_new=create_topLevelShell1(nomePagina,\
                        Context->UxtopLevel_selezionata,Context->Uxnome_disp,\
                        pagine[num_pag].sfondo);\
                  if(Pagina_new==NULL)\
                        {\
                        popup_errorDialog("Errore Creazione pagina",w);\
                        UnsetCursorWait(Context->UxdrawingSinottico);\
			return;\
                        }\
                    }\
		  }\
                  if((tipoApertura == CHANGE_PAGE)||(tipoApertura ==CLOSE_PAGE)) \
                        {        \
			DelElencoPagine(Context->Uxkey_refresh, \
				Context->UxdrawingSinottico);\
			XSync(XtDisplay(w),False);	\
                        XtRemoveTimeOut(Context->Uxtimer_refresh);\
                        XtDestroyWidget(Context->UxtopLevelShell1);\
                        }\
                }\
	}\
UnsetCursorWait(Context->UxdrawingSinottico);\
#endif	\
}\
\
ClosePageSin(Widget w)\
{\
        _UxCtopLevelShell1      *UxSaveCtx, *UxContext;\
\
        UxSaveCtx = UxTopLevelShell1Context;\
        UxTopLevelShell1Context = UxContext =\
                        (_UxCtopLevelShell1 *) UxGetContext( w );\
\
        DelElencoPagine(key_refresh,drawingSinottico);\
        if(drawing_pixmap)\
		XFreePixmap(XtDisplay(w),drawing_pixmap);\
        XSync(XtDisplay(w),False);\
	XtRemoveTimeOut(timer_refresh);\
	XlFreeCursor(topLevelShell1,cursor_wait);\
	XtDestroyWidget(topLevelShell1);\
        if( pag_db != NULL )\
           XrmDestroyDatabase(pag_db);\
	printf("Close Page Sinottico\n");\
\
\
        UxTopLevelShell1Context = UxSaveCtx;        \
\
}
*topLevelShell1.static: true
*topLevelShell1.name: topLevelShell1
*topLevelShell1.parent: NO_PARENT
*topLevelShell1.parentExpression: topLevel_selezionata
*topLevelShell1.x: 110
*topLevelShell1.y: 30
*topLevelShell1.width: 1060
*topLevelShell1.height: 900
*topLevelShell1.background: "#000000"
*topLevelShell1.deleteResponse: "do_nothing"
*topLevelShell1.iconName.source: public
*topLevelShell1.iconName: "topLevelShell1"
*topLevelShell1.title.source: public
*topLevelShell1.title: "topLevelShell1"
*topLevelShell1.minWidth: 100
*topLevelShell1.minHeight: 580
*topLevelShell1.mwmDecorations: MWM_DECOR_TITLE | MWM_DECOR_RESIZEH | MWM_DECOR_MINIMIZE | MWM_DECOR_MAXIMIZE
*topLevelShell1.destroyCallback: {\
\
}
*topLevelShell1.mwmFunctions: -1\
\


*form1.class: form
*form1.static: true
*form1.name: form1
*form1.parent: topLevelShell1
*form1.resizePolicy: "resize_none"
*form1.unitType: "pixels"
*form1.x: 110
*form1.y: 70
*form1.width: 910
*form1.height: 760
*form1.background: "#000000"
*form1.navigationType: "none"
*form1.traversalOn: "false"

*formMenu.class: form
*formMenu.static: true
*formMenu.name: formMenu
*formMenu.parent: form1
*formMenu.resizePolicy: "resize_none"
*formMenu.x: 970
*formMenu.y: 0
*formMenu.width: 56
*formMenu.height: 900
*formMenu.bottomAttachment: "attach_form"
*formMenu.leftAttachment: "attach_none"
*formMenu.rightAttachment: "attach_form"
*formMenu.topAttachment: "attach_form"
*formMenu.background: "#50a050"

*form2.class: form
*form2.static: true
*form2.name: form2
*form2.parent: formMenu
*form2.resizePolicy: "resize_none"
*form2.x: 20
*form2.y: 780
*form2.width: 60
*form2.height: 80
*form2.rightAttachment: "attach_form"
*form2.bottomAttachment: "attach_form"
*form2.leftAttachment: "attach_form"
*form2.background: "#50a050"

*drawnButtonClose.class: drawnButton
*drawnButtonClose.static: true
*drawnButtonClose.name: drawnButtonClose
*drawnButtonClose.parent: form2
*drawnButtonClose.x: 4
*drawnButtonClose.y: 2
*drawnButtonClose.width: 50
*drawnButtonClose.height: 50
*drawnButtonClose.background: "#50a050"
*drawnButtonClose.disarmCallback: {\
set_something( drawnButtonClose, XmNshadowType, XmSHADOW_OUT);\
}
*drawnButtonClose.pushButtonEnabled: "false"
*drawnButtonClose.shadowThickness: 3
*drawnButtonClose.topShadowColor: "#9ebac2"
*drawnButtonClose.highlightColor: "#000000"
*drawnButtonClose.highlightOnEnter: "false"
*drawnButtonClose.shadowType: "shadow_out"
*drawnButtonClose.activateCallback: {\
printf("Chiusura della pagina\n");\
if(!CanClosePage(Pagina))\
	{\
	popup_errorDialog("Unable to close this page",drawingSinottico);\
	return;\
	}\
#ifndef DESIGN_TIME\
popup_CloseQuestion(topLevelShell1,drawingSinottico,&(timer_refresh),key_refresh);\
#endif\
}
*drawnButtonClose.labelType: "pixmap"
*drawnButtonClose.armCallback: {\
set_something( drawnButtonClose, XmNshadowType, XmSHADOW_IN);\
}

*label5.class: label
*label5.static: true
*label5.name: label5
*label5.parent: form2
*label5.x: 4
*label5.y: 50
*label5.width: 50
*label5.height: 20
*label5.background: "#50a050"
*label5.labelString: "CLOSE"

*drawnButtonXaing.class: drawnButton
*drawnButtonXaing.static: true
*drawnButtonXaing.name: drawnButtonXaing
*drawnButtonXaing.parent: formMenu
*drawnButtonXaing.x: 4
*drawnButtonXaing.y: 118
*drawnButtonXaing.width: 50
*drawnButtonXaing.height: 50
*drawnButtonXaing.background: "#50a050"
*drawnButtonXaing.pushButtonEnabled: "false"
*drawnButtonXaing.shadowThickness: 3
*drawnButtonXaing.topShadowColor: "#9ebac2"
*drawnButtonXaing.highlightColor: "#000000"
*drawnButtonXaing.highlightOnEnter: "false"
*drawnButtonXaing.shadowType: "shadow_out"
*drawnButtonXaing.activateCallback: {\
printf("Premuto bottone AING\n");\
operazione_attiva=OPERAZIONE_XAING;\
set_something( drawnButtonXaing, XmNshadowType, XmSHADOW_IN);\
set_something( drawnButtonXstaz, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonInfo, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonNop, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonXplot, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonReg, XmNshadowType, XmSHADOW_OUT);\
\
\
}
*drawnButtonXaing.labelType: "pixmap"
*drawnButtonXaing.borderWidth: 0
*drawnButtonXaing.recomputeSize: "true"
*drawnButtonXaing.alignment: "alignment_center"
*drawnButtonXaing.sensitive: "true"

*drawnButtonXstaz.class: drawnButton
*drawnButtonXstaz.static: true
*drawnButtonXstaz.name: drawnButtonXstaz
*drawnButtonXstaz.parent: formMenu
*drawnButtonXstaz.x: 4
*drawnButtonXstaz.y: 318
*drawnButtonXstaz.width: 50
*drawnButtonXstaz.height: 50
*drawnButtonXstaz.background: "#50a050"
*drawnButtonXstaz.pushButtonEnabled: "false"
*drawnButtonXstaz.shadowThickness: 3
*drawnButtonXstaz.shadowType: "shadow_out"
*drawnButtonXstaz.activateCallback: {\
printf("premuto il bottone display\n");\
operazione_attiva=OPERAZIONE_XSTAZ;\
set_something( drawnButtonXaing, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonXstaz, XmNshadowType, XmSHADOW_IN);\
set_something( drawnButtonInfo, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonNop, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonXplot, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonReg, XmNshadowType, XmSHADOW_OUT);\
\
}
*drawnButtonXstaz.labelType: "pixmap"
*drawnButtonXstaz.recomputeSize: "true"
*drawnButtonXstaz.labelString: "XSTAZ"

*drawnButtonInfo.class: drawnButton
*drawnButtonInfo.static: true
*drawnButtonInfo.name: drawnButtonInfo
*drawnButtonInfo.parent: formMenu
*drawnButtonInfo.x: 5
*drawnButtonInfo.y: 520
*drawnButtonInfo.width: 50
*drawnButtonInfo.height: 50
*drawnButtonInfo.background: "#50a050"
*drawnButtonInfo.pushButtonEnabled: "false"
*drawnButtonInfo.shadowThickness: 3
*drawnButtonInfo.shadowType: "shadow_out"
*drawnButtonInfo.activateCallback: {\
printf("premuto bottone info\n");\
operazione_attiva=OPERAZIONE_INFO;\
set_something( drawnButtonXaing, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonXstaz, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonInfo, XmNshadowType, XmSHADOW_IN);\
set_something( drawnButtonNop, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonXplot, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonReg, XmNshadowType, XmSHADOW_OUT);\
\
\
}
*drawnButtonInfo.labelType: "pixmap"

*label1.class: label
*label1.static: true
*label1.name: label1
*label1.parent: formMenu
*label1.x: 4
*label1.y: 168
*label1.width: 50
*label1.height: 20
*label1.background: "#50a050"
*label1.labelString: "AING"

*label3.class: label
*label3.static: true
*label3.name: label3
*label3.parent: formMenu
*label3.x: 4
*label3.y: 368
*label3.width: 50
*label3.height: 20
*label3.background: "#50a050"
*label3.labelString: "STAZ"

*label4.class: label
*label4.static: true
*label4.name: label4
*label4.parent: formMenu
*label4.x: 4
*label4.y: 568
*label4.width: 50
*label4.height: 20
*label4.background: "#50a050"
*label4.labelString: "INFO"

*drawnButtonNop.class: drawnButton
*drawnButtonNop.static: true
*drawnButtonNop.name: drawnButtonNop
*drawnButtonNop.parent: formMenu
*drawnButtonNop.x: 4
*drawnButtonNop.y: 18
*drawnButtonNop.width: 50
*drawnButtonNop.height: 50
*drawnButtonNop.background: "#50a050"
*drawnButtonNop.labelType: "pixmap"
*drawnButtonNop.shadowThickness: 3
*drawnButtonNop.activateCallback: {\
printf("premuto bottone nop\n");\
#ifndef DESIGN_TIME\
operazione_attiva=OPERAZIONE_NOP;\
#endif\
set_something( drawnButtonXaing, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonXstaz, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonInfo, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonNop, XmNshadowType, XmSHADOW_IN);\
set_something( drawnButtonXplot, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonReg, XmNshadowType, XmSHADOW_OUT);\
\
}
*drawnButtonNop.shadowType: "shadow_in"

*label6.class: label
*label6.static: true
*label6.name: label6
*label6.parent: formMenu
*label6.x: 4
*label6.y: 68
*label6.width: 50
*label6.height: 20
*label6.background: "#50a050"
*label6.labelString: "NOP"

*drawnButtonXplot.class: drawnButton
*drawnButtonXplot.static: true
*drawnButtonXplot.name: drawnButtonXplot
*drawnButtonXplot.parent: formMenu
*drawnButtonXplot.x: 4
*drawnButtonXplot.y: 218
*drawnButtonXplot.width: 50
*drawnButtonXplot.height: 50
*drawnButtonXplot.background: "#50a050"
*drawnButtonXplot.pushButtonEnabled: "false"
*drawnButtonXplot.shadowThickness: 3
*drawnButtonXplot.topShadowColor: "#9ebac2"
*drawnButtonXplot.highlightColor: "#000000"
*drawnButtonXplot.highlightOnEnter: "false"
*drawnButtonXplot.shadowType: "shadow_out"
*drawnButtonXplot.activateCallback: {\
printf("Premuto bottone PLOT\n");\
operazione_attiva=OPERAZIONE_XPLOT;\
set_something( drawnButtonXplot, XmNshadowType, XmSHADOW_IN);\
set_something( drawnButtonXstaz, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonInfo, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonNop, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonXaing, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonReg, XmNshadowType, XmSHADOW_OUT);\
\
}
*drawnButtonXplot.labelType: "pixmap"
*drawnButtonXplot.borderWidth: 0
*drawnButtonXplot.recomputeSize: "true"
*drawnButtonXplot.alignment: "alignment_center"

*label2.class: label
*label2.static: true
*label2.name: label2
*label2.parent: formMenu
*label2.x: 4
*label2.y: 268
*label2.width: 50
*label2.height: 20
*label2.background: "#50a050"
*label2.labelString: "PLOT"

*drawnButtonReg.class: drawnButton
*drawnButtonReg.static: true
*drawnButtonReg.name: drawnButtonReg
*drawnButtonReg.parent: formMenu
*drawnButtonReg.x: 5
*drawnButtonReg.y: 420
*drawnButtonReg.width: 50
*drawnButtonReg.height: 50
*drawnButtonReg.background: "#50a050"
*drawnButtonReg.pushButtonEnabled: "false"
*drawnButtonReg.shadowThickness: 3
*drawnButtonReg.shadowType: "shadow_out"
*drawnButtonReg.activateCallback: {\
printf("premuto il bottone display\n");\
operazione_attiva=OPERAZIONE_REG;\
set_something( drawnButtonReg, XmNshadowType, XmSHADOW_IN);\
set_something( drawnButtonXaing, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonXstaz, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonInfo, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonNop, XmNshadowType, XmSHADOW_OUT);\
set_something( drawnButtonXplot, XmNshadowType, XmSHADOW_OUT);\
}
*drawnButtonReg.labelType: "pixmap"
*drawnButtonReg.recomputeSize: "true"
*drawnButtonReg.labelString: "XSTAZ"

*label8.class: label
*label8.static: true
*label8.name: label8
*label8.parent: formMenu
*label8.x: 5
*label8.y: 470
*label8.width: 50
*label8.height: 20
*label8.background: "#50a050"
*label8.labelString: "REG"

*form3.class: form
*form3.static: true
*form3.name: form3
*form3.parent: form1
*form3.resizePolicy: "resize_none"
*form3.x: 10
*form3.y: 0
*form3.width: 1090
*form3.height: 940
*form3.rightAttachment: "attach_widget"
*form3.rightWidget: "formMenu"
*form3.background: "#000000"
*form3.leftAttachment: "attach_form"
*form3.bottomAttachment: "attach_form"
*form3.topAttachment: "attach_form"
*form3.navigationType: "none"
*form3.traversalOn: "false"

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.parent: form3
*scrolledWindow1.scrollingPolicy: "automatic"
*scrolledWindow1.x: 10
*scrolledWindow1.y: 0
*scrolledWindow1.width: 1100
*scrolledWindow1.height: 940
*scrolledWindow1.bottomAttachment: "attach_form"
*scrolledWindow1.rightAttachment: "attach_form"
*scrolledWindow1.topAttachment: "attach_form"
*scrolledWindow1.leftAttachment: "attach_form"
*scrolledWindow1.background: "#50a050"
*scrolledWindow1.navigationType: "none"
*scrolledWindow1.traversalOn: "false"

*drawingSinottico.class: drawingArea
*drawingSinottico.static: true
*drawingSinottico.name: drawingSinottico
*drawingSinottico.parent: scrolledWindow1
*drawingSinottico.resizePolicy: "resize_none"
*drawingSinottico.x: 4
*drawingSinottico.y: 14
*drawingSinottico.width: 1200
*drawingSinottico.height: 1190
*drawingSinottico.background: "#000000"
*drawingSinottico.exposeCallback: {\
#ifndef DESIGN_TIME\
if( bkg_sin != NULL)\
{\
   disegna_bck(UxWidget,bkg_sin,UxCallbackArg,&(region_sin),False);\
}\
#endif\
}
*drawingSinottico.marginHeight: 0
*drawingSinottico.marginWidth: 0
*drawingSinottico.navigationType: "none"
*drawingSinottico.traversalOn: "false"

*menu2.class: rowColumn
*menu2.static: true
*menu2.name: menu2
*menu2.parent: drawingSinottico
*menu2.rowColumnType: "menu_popup"
*menu2.menuAccelerator: "<KeyUp>F4"

*menu2_p3.class: rowColumn
*menu2_p3.static: true
*menu2_p3.name: menu2_p3
*menu2_p3.parent: menu2
*menu2_p3.rowColumnType: "menu_pulldown"
*menu2_p3.background: "#50a050"

*menu2_p3_b1.class: pushButton
*menu2_p3_b1.static: true
*menu2_p3_b1.name: menu2_p3_b1
*menu2_p3_b1.parent: menu2_p3
*menu2_p3_b1.labelString: "Print"
*menu2_p3_b1.background: "#50a050"
*menu2_p3_b1.activateCallback: {\
#ifndef DESIGN_TIME\
if(!PrintScreen(drawingSinottico,nome_disp,Pagina,False,bkg_sin))\
	popup_errorDialog("Printer not available",drawingSinottico);\
#endif\
}

*menu2_p3_b2.class: pushButton
*menu2_p3_b2.static: true
*menu2_p3_b2.name: menu2_p3_b2
*menu2_p3_b2.parent: menu2_p3
*menu2_p3_b2.labelString: "Printer setup"
*menu2_p3_b2.background: "#50a050"
*menu2_p3_b2.activateCallback: {\
#ifndef DESIGN_TIME\
if(PrintSetup(drawingSinottico)==NULL)\
	popup_errorDialog("Printer not available",\
                               drawingSinottico);\
#endif\
}

*menu2_p4.class: rowColumn
*menu2_p4.static: true
*menu2_p4.name: menu2_p4
*menu2_p4.parent: menu2
*menu2_p4.rowColumnType: "menu_pulldown"
*menu2_p4.background: "#50a050"

*DispTagModeButton.class: pushButton
*DispTagModeButton.static: true
*DispTagModeButton.name: DispTagModeButton
*DispTagModeButton.parent: menu2_p4
*DispTagModeButton.labelString: "Tag mode"
*DispTagModeButton.background: "#50a050"
*DispTagModeButton.activateCallback: XlSetSomething(lista_wid,num_wid,"DispReg",XlNdispRegMode,DISP_TAG_MODE);

*DispValueModeButton.class: pushButton
*DispValueModeButton.static: true
*DispValueModeButton.name: DispValueModeButton
*DispValueModeButton.parent: menu2_p4
*DispValueModeButton.labelString: "Value mode"
*DispValueModeButton.background: "#50a050"
*DispValueModeButton.activateCallback: XlSetSomething(lista_wid,num_wid,"DispReg",XlNdispRegMode,DISP_VALUE_MODE);

*menu2_p4_b4.class: separator
*menu2_p4_b4.static: true
*menu2_p4_b4.name: menu2_p4_b4
*menu2_p4_b4.parent: menu2_p4
*menu2_p4_b4.background: "#50a050"

*DispUnmanagedModeButton.class: pushButton
*DispUnmanagedModeButton.static: true
*DispUnmanagedModeButton.name: DispUnmanagedModeButton
*DispUnmanagedModeButton.parent: menu2_p4
*DispUnmanagedModeButton.labelString: "Unmanaged"
*DispUnmanagedModeButton.background: "#50a050"
*DispUnmanagedModeButton.activateCallback: XlSetSomething(lista_wid,num_wid,"DispReg",XlNdispRegMode,DISP_UNMANAGED_MODE);\


*menu2_p5.class: rowColumn
*menu2_p5.static: true
*menu2_p5.name: menu2_p5
*menu2_p5.parent: menu2
*menu2_p5.rowColumnType: "menu_pulldown"
*menu2_p5.background: "#50a050"

*DispPortModeButton.class: pushButton
*DispPortModeButton.static: true
*DispPortModeButton.name: DispPortModeButton
*DispPortModeButton.parent: menu2_p5
*DispPortModeButton.labelString: "Display ports"
*DispPortModeButton.activateCallback: XlSetSomething(lista_wid,num_wid,"Port",XlNvisibleMode,VISIBLE_PORT_ON);
*DispPortModeButton.background: "#50a050"

*NoDispPortModeButton.class: pushButton
*NoDispPortModeButton.static: true
*NoDispPortModeButton.name: NoDispPortModeButton
*NoDispPortModeButton.parent: menu2_p5
*NoDispPortModeButton.labelString: "Unmanage ports"
*NoDispPortModeButton.activateCallback: XlSetSomething(lista_wid,num_wid,"Port",XlNvisibleMode,VISIBLE_PORT_OFF);
*NoDispPortModeButton.background: "#50a050"

*MenuRegMode.class: cascadeButton
*MenuRegMode.static: true
*MenuRegMode.name: MenuRegMode
*MenuRegMode.parent: menu2
*MenuRegMode.labelString: "Display reg mode"
*MenuRegMode.subMenuId: "menu2_p4"
*MenuRegMode.background: "#50a050"

*MenuPortMode.class: cascadeButton
*MenuPortMode.static: true
*MenuPortMode.name: MenuPortMode
*MenuPortMode.parent: menu2
*MenuPortMode.labelString: "Port visual mode"
*MenuPortMode.subMenuId: "menu2_p5"
*MenuPortMode.background: "#50a050"

*menu2_p2_b6.class: separator
*menu2_p2_b6.static: true
*menu2_p2_b6.name: menu2_p2_b6
*menu2_p2_b6.parent: menu2
*menu2_p2_b6.background: "#50a050"
*menu2_p2_b6.highlightOnEnter: "false"
*menu2_p2_b6.separatorType: "shadow_etched_in"

*menu2_p2_b3.class: cascadeButton
*menu2_p2_b3.static: true
*menu2_p2_b3.name: menu2_p2_b3
*menu2_p2_b3.parent: menu2
*menu2_p2_b3.labelString: "Harcopy"
*menu2_p2_b3.subMenuId: "menu2_p3"
*menu2_p2_b3.background: "#50a050"

*menu2_p2_b4.class: separator
*menu2_p2_b4.static: true
*menu2_p2_b4.name: menu2_p2_b4
*menu2_p2_b4.parent: menu2
*menu2_p2_b4.background: "#50a050"
*menu2_p2_b4.separatorType: "shadow_etched_in"
*menu2_p2_b4.shadowThickness: 2

*menu2_p2_b1.class: pushButton
*menu2_p2_b1.static: true
*menu2_p2_b1.name: menu2_p2_b1
*menu2_p2_b1.parent: menu2
*menu2_p2_b1.labelString: "Close the page"
*menu2_p2_b1.activateCallback: {\
printf("Chiusura della pagina\n");\
if(!CanClosePage(Pagina))\
	{\
	popup_errorDialog("Unable to close this page",drawingSinottico);\
	return;\
	}\
#ifndef DESIGN_TIME\
popup_CloseQuestion(topLevelShell1,drawingSinottico,&(timer_refresh),key_refresh);\
#endif\
}
*menu2_p2_b1.background: "#50a050"

