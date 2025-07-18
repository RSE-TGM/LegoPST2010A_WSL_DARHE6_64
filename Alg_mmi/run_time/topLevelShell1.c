
/*******************************************************************************
       topLevelShell1.c
       (Generated from interface file topLevelShell1.i)
       Associated Resource file: topLevelShell1.rf
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/CascadeB.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/DrawingA.h>
#include <Xm/ScrolledW.h>
#include <Xm/Label.h>
#include <Xm/DrawnB.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

#include "libutilx.h"

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo topLevelShell1.i
   tipo 
   release 5.2
   data 1/22/96
   reserved @(#)topLevelShell1.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <X11/Xlib.h>

#ifdef SCO_UNIX
#include <Xm/MwmUtil.h>
#else
#include <Xm/MwmUtil.h>
#endif

#include <X11/cursorfont.h>

#ifndef DESIGN_TIME
#include <Xl/Xl.h>
#endif

#ifndef DESIGN_TIME
#include <Xl/XlCoreP.h>
#include <Xl/XlManagerP.h>
#else
#include <Xl/XlCore.h>
#include <Xl/XlManager.h>
#endif

#include <Xl/XlChangePage.h>

#include <Xl/XlDispReg.h>
#include <Xl/XlPort.h>


#include <Ol/OlDatabasePunti.h>

#ifndef DESIGN_TIME
#include <Ol/OlPertP.h>
#else
#include <Ol/OlPert.h>
#endif

#include <Rt/RtMemory.h>
#include <Xm/Protocols.h>
#include "page_sin_icon.bmp"
#include "nop_button.bmp"
#include "xaing_button.bmp"
#include "xstaz_button.bmp"
#include "xplot_button.bmp"
#include "info_button.bmp"
#include "close_button.bmp"
#include "xreg_button.bmp"

#include "other.h"
#include "ric_aing.h"
#include "res_edit.h"
  

extern Widget listDrawing[MAX_PAGE];
extern swidget popup_topLevelShellStaz();
extern OlDatabasePuntiObject database_simulatore;
extern OlPertObject pert;
extern AN_PAG *pagine;
extern int totale_pagine;
extern Boolean topologia_on;

extern Boolean EsistePagina();

static void refresh_page( );
void SetCursorWait( );
void UnsetCursorWait( );
extern Boolean XlSetSomething(WidgetList ,Cardinal ,char * , char * , char * );


/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxtopLevelShell1;
	Widget	Uxform1;
	Widget	UxformMenu;
	Widget	Uxform2;
	Widget	UxdrawnButtonClose;
	Widget	Uxlabel5;
	Widget	UxdrawnButtonXaing;
	Widget	UxdrawnButtonXstaz;
	Widget	UxdrawnButtonInfo;
	Widget	Uxlabel1;
	Widget	Uxlabel3;
	Widget	Uxlabel4;
	Widget	UxdrawnButtonNop;
	Widget	Uxlabel6;
	Widget	UxdrawnButtonXplot;
	Widget	Uxlabel2;
	Widget	UxdrawnButtonReg;
	Widget	Uxlabel8;
	Widget	Uxform3;
	Widget	UxscrolledWindow1;
	Widget	UxdrawingSinottico;
	Widget	Uxmenu2;
	Widget	Uxmenu2_p4;
	Widget	UxDispTagModeButton;
	Widget	UxDispValueModeButton;
	Widget	Uxmenu2_p4_b4;
	Widget	UxDispUnmanagedModeButton;
	Widget	UxMenuRegMode;
	Widget	Uxmenu2_p5;
	Widget	UxDispPortModeButton;
	Widget	UxNoDispPortModeButton;
	Widget	UxMenuPortMode;
	Widget	Uxmenu2_p2_b6;
	Widget	Uxmenu2_p3;
	Widget	Uxmenu2_p3_b1;
	Widget	Uxmenu2_p3_b2;
	Widget	Uxmenu2_p2_b3;
	Widget	Uxmenu2_p2_b4;
	Widget	Uxmenu2_p2_b1;
	int	Uxoperazione_attiva;
	Widget	UxtopLevel_selezionata;
	XtIntervalId	Uxtimer_refresh;
	WidgetList	Uxlista_wid;
	int	Uxnum_wid;
	Region	Uxregion_sin;
	BCK_OBJ	*Uxbkg_sin;
	Widget	UxListaWidVar[7];
	int	Uxkey_refresh;
	int	Uxtime_ref;
	Widget	Uxwid_attesa;
	int	Uxattesa;
	int	Uxcursor_wait_set;
	Cursor	Uxcursor_wait;
	XrmDatabase	Uxpag_db;
	Pixmap	Uxdrawing_pixmap;
	unsigned char	*UxPagina;
	Widget	UxPadre;
	unsigned char	*Uxnome_disp;
	BCK_OBJ	*Uxsfondo_sin;
} _UxCtopLevelShell1;

static _UxCtopLevelShell1      *UxTopLevelShell1Context;
#define topLevelShell1          UxTopLevelShell1Context->UxtopLevelShell1
#define form1                   UxTopLevelShell1Context->Uxform1
#define formMenu                UxTopLevelShell1Context->UxformMenu
#define form2                   UxTopLevelShell1Context->Uxform2
#define drawnButtonClose        UxTopLevelShell1Context->UxdrawnButtonClose
#define label5                  UxTopLevelShell1Context->Uxlabel5
#define drawnButtonXaing        UxTopLevelShell1Context->UxdrawnButtonXaing
#define drawnButtonXstaz        UxTopLevelShell1Context->UxdrawnButtonXstaz
#define drawnButtonInfo         UxTopLevelShell1Context->UxdrawnButtonInfo
#define label1                  UxTopLevelShell1Context->Uxlabel1
#define label3                  UxTopLevelShell1Context->Uxlabel3
#define label4                  UxTopLevelShell1Context->Uxlabel4
#define drawnButtonNop          UxTopLevelShell1Context->UxdrawnButtonNop
#define label6                  UxTopLevelShell1Context->Uxlabel6
#define drawnButtonXplot        UxTopLevelShell1Context->UxdrawnButtonXplot
#define label2                  UxTopLevelShell1Context->Uxlabel2
#define drawnButtonReg          UxTopLevelShell1Context->UxdrawnButtonReg
#define label8                  UxTopLevelShell1Context->Uxlabel8
#define form3                   UxTopLevelShell1Context->Uxform3
#define scrolledWindow1         UxTopLevelShell1Context->UxscrolledWindow1
#define drawingSinottico        UxTopLevelShell1Context->UxdrawingSinottico
#define menu2                   UxTopLevelShell1Context->Uxmenu2
#define menu2_p4                UxTopLevelShell1Context->Uxmenu2_p4
#define DispTagModeButton       UxTopLevelShell1Context->UxDispTagModeButton
#define DispValueModeButton     UxTopLevelShell1Context->UxDispValueModeButton
#define menu2_p4_b4             UxTopLevelShell1Context->Uxmenu2_p4_b4
#define DispUnmanagedModeButton UxTopLevelShell1Context->UxDispUnmanagedModeButton
#define MenuRegMode             UxTopLevelShell1Context->UxMenuRegMode
#define menu2_p5                UxTopLevelShell1Context->Uxmenu2_p5
#define DispPortModeButton      UxTopLevelShell1Context->UxDispPortModeButton
#define NoDispPortModeButton    UxTopLevelShell1Context->UxNoDispPortModeButton
#define MenuPortMode            UxTopLevelShell1Context->UxMenuPortMode
#define menu2_p2_b6             UxTopLevelShell1Context->Uxmenu2_p2_b6
#define menu2_p3                UxTopLevelShell1Context->Uxmenu2_p3
#define menu2_p3_b1             UxTopLevelShell1Context->Uxmenu2_p3_b1
#define menu2_p3_b2             UxTopLevelShell1Context->Uxmenu2_p3_b2
#define menu2_p2_b3             UxTopLevelShell1Context->Uxmenu2_p2_b3
#define menu2_p2_b4             UxTopLevelShell1Context->Uxmenu2_p2_b4
#define menu2_p2_b1             UxTopLevelShell1Context->Uxmenu2_p2_b1
#define operazione_attiva       UxTopLevelShell1Context->Uxoperazione_attiva
#define topLevel_selezionata    UxTopLevelShell1Context->UxtopLevel_selezionata
#define timer_refresh           UxTopLevelShell1Context->Uxtimer_refresh
#define lista_wid               UxTopLevelShell1Context->Uxlista_wid
#define num_wid                 UxTopLevelShell1Context->Uxnum_wid
#define region_sin              UxTopLevelShell1Context->Uxregion_sin
#define bkg_sin                 UxTopLevelShell1Context->Uxbkg_sin
#define ListaWidVar             UxTopLevelShell1Context->UxListaWidVar
#define key_refresh             UxTopLevelShell1Context->Uxkey_refresh
#define time_ref                UxTopLevelShell1Context->Uxtime_ref
#define wid_attesa              UxTopLevelShell1Context->Uxwid_attesa
#define attesa                  UxTopLevelShell1Context->Uxattesa
#define cursor_wait_set         UxTopLevelShell1Context->Uxcursor_wait_set
#define cursor_wait             UxTopLevelShell1Context->Uxcursor_wait
#define pag_db                  UxTopLevelShell1Context->Uxpag_db
#define drawing_pixmap          UxTopLevelShell1Context->Uxdrawing_pixmap
#define Pagina                  UxTopLevelShell1Context->UxPagina
#define Padre                   UxTopLevelShell1Context->UxPadre
#define nome_disp               UxTopLevelShell1Context->Uxnome_disp
#define sfondo_sin              UxTopLevelShell1Context->Uxsfondo_sin


/*******************************************************************************
       The following function is an event-handler for posting menus.
*******************************************************************************/

//static void	_UxtopLevelShell1MenuPost( wgt, client_data, event, ctd )
static void	_UxtopLevelShell1MenuPost( wgt, client_data, event)
	Widget		wgt;
	XtPointer	client_data;
	XEvent		*event;

{
	Widget	menu = (Widget) client_data;
	int 	which_button;

	XtVaGetValues( menu, XmNwhichButton, &which_button, NULL );

	if ( event->xbutton.button == which_button )
	{
		XmMenuPosition( menu, (XButtonPressedEvent *) event );
		XtManageChild( menu );
	}
}


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_topLevelShell1();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

void SetCursorWait(Widget w)
{
#ifndef DESIGN_TIME
_UxCtopLevelShell1 *Context;
Context =(_UxCtopLevelShell1 *) UxGetContext( w);

XlSetCursor(Context->UxdrawingSinottico,Context->Uxcursor_wait);
Context->Uxcursor_wait_set = 1;

#endif
}

void UnsetCursorWait(Widget w)
{
#ifndef DESIGN_TIME
_UxCtopLevelShell1 *Context;
Context =(_UxCtopLevelShell1 *) UxGetContext( w);

if(Context->Uxcursor_wait_set == 1)
	{
	Context->Uxcursor_wait_set = 0;
	XlUnsetCursor(Context->UxdrawingSinottico);
	}
#endif
}

void IcoSelect(w)
 Widget w;
{
XlCoreWidget wcore;
XlManagerWidget wmanager;
Widget Pagina_staz=NULL;
Widget drawing;
int operazione=0;
#ifndef DESIGN_TIME
_UxCtopLevelShell1 *Context;
#endif
 

#ifndef DESIGN_TIME
/* Ricavo il context */
drawing=XtParent(w);
if(XlIsXlComposite(drawing))
	drawing=XtParent(drawing);

Context =(_UxCtopLevelShell1 *) UxGetContext( drawing);
operazione=Context->Uxoperazione_attiva;
#endif
	
printf("IcoSelect %d\n",operazione_attiva);

switch(operazione){
	case OPERAZIONE_NOP:
		{
#ifndef DESIGN_TIME
		if(XlIsGraficoSingle(w))
		    {		
		    /*
		     Viene chiamata ActivateChangeVar solo quando mmi e'
	  	     invocato con l' opzione -Topologia
		    */ 	
		    if(topologia_on)
		    	if(!ActivateChangeVar(w,Context->UxdrawingSinottico,
				&(Context->UxListaWidVar[0])))
				popup_errorDialog("Error changig tag",
				Context->UxdrawingSinottico);
		    }
#endif
		break;
		}
	case OPERAZIONE_INFO:
		{
#ifndef DESIGN_TIME
	        popup_formInfo(w,Context->UxtopLevel_selezionata);
#endif
		break;
		};
case OPERAZIONE_XAING:
		{
#ifndef DESIGN_TIME
#if defined SCADA_MMI
		/*
			al momento XAING non e' utilizzabile
		*/
		popup_errorDialog("AING not available",
				Context->UxdrawingSinottico);
		break;
#endif
		if(AcceptAing(w))
			{

		         if(!ActivateAing(w,Context->UxdrawingSinottico,
				Context->Uxnome_disp,
				&(Context->UxListaWidVar[0])))
			    popup_errorDialog("Variable not defined",
				Context->UxdrawingSinottico);
			}
		else
			popup_errorDialog("AING not available for this object",
					Context->UxdrawingSinottico);
#endif
		break;
		}
case OPERAZIONE_XPLOT:
		{
#ifndef DESIGN_TIME
		if(AcceptPlot(w))
			{
			if(!ActivatePlot(w,Context->UxdrawingSinottico,
				Context->Uxnome_disp,
				&(Context->UxListaWidVar[0])))
			    popup_errorDialog("Variable not defined",
				Context->UxdrawingSinottico);
			}
		else
			popup_errorDialog("PLOT not available for this object",
					Context->UxdrawingSinottico);
#endif
		break;
		}
        case OPERAZIONE_XSTAZ:
		{
		if(XlIsXlCore(w))
			{
			wcore=(XlCoreWidget)w;
#ifndef DESIGN_TIME
/***
			printf("Apro la pagina di stazioni %s\n",
				wcore->xlcore.pagina_staz);
***/
			if(!EsistePagina(
				wcore->xlcore.pagina_staz))
				{
				popup_errorDialog("Pagina inesistente",
					w/*Context->UxdrawingSinottico*/);
				break;
				}
			if(wcore->xlcore.pagina_staz!=NULL)
				{
				int j;
                                for(j=0; j<totale_pagine;j++)
                                        if(strcmp(wcore->xlcore.pagina_staz,
                                                pagine[j].nome)==0)
                                                break;

				Pagina_staz=popup_topLevelShellStaz(
				   wcore->xlcore.pagina_staz,
				   Context->UxtopLevel_selezionata,nome_disp,pagine[j].sfondo);
				}
                        if(Pagina_staz==NULL)
				popup_errorDialog("Errore Creazione pagina",
					w/*Context->UxdrawingSinottico*/);
#endif
			}
		else
			{
                       
			wmanager=(XlManagerWidget)w;
#ifndef DESIGN_TIME
/***
			printf("Apro la pagina di stazioni %s\n",
				wmanager->xlmanager.pagina_staz);
***/
			if(!EsistePagina(
				wmanager->xlmanager.pagina_staz))
				{
				popup_errorDialog("Pagina inesistente",
					w/*Context->UxdrawingSinottico*/);
				break;
				}
			if(PaginaAperta(Context->UxtopLevel_selezionata,
				wmanager->xlmanager.pagina_staz))
				break;
			if(!CanOpenPage(w))
				break;
			if(wmanager->xlmanager.pagina_staz!=NULL)
				Pagina_staz=popup_topLevelShellStaz(
				   wmanager->xlmanager.pagina_staz,
				   Context->UxtopLevel_selezionata,nome_disp,NULL);
                        if(Pagina_staz==NULL)
				popup_errorDialog("Errore Creazione pagina",
					w/*Context->UxdrawingSinottico*/);
#endif
			}
		break;
    		}
        case OPERAZIONE_REG:
/* individuo tramite ilcampo object_tag di xlcore la pagina da aprire
   e la apro
*/
#ifndef DESIGN_TIME
           if( XlIsXlCore(w))
           {
printf("Richiamata la operazione OPERAZIONE_REG\n");

              wcore = (XlCoreWidget)w;
printf("Apro la pagina di regolazione %s\n",wcore->xlcore.object_tag);

              if( !EsistePagina(wcore->xlcore.object_tag))
              {
                 popup_errorDialog("Pagina di regolazione inesistente",w);
                 break;
              }
              if( wcore->xlcore.object_tag!=NULL)
              {
                 int j;
                
                 for(j=0;j<totale_pagine;j++)
                    if( strcmp(wcore->xlcore.object_tag,pagine[j].nome) == 0 )
                       break;
                 Pagina_staz=popup_topLevelShellStaz( wcore->xlcore.object_tag,
                                 Context->UxtopLevel_selezionata,nome_disp,pagine[j].sfondo);
              }

              if( Pagina_staz == NULL )
                 popup_errorDialog("Errore creazione pagina",w);

           }
	   else
           {
                       
		wmanager=(XlManagerWidget)w;
		printf("Apro la pagina di stazioni %s\n",
				wmanager->xlmanager.object_tag);

		if(!EsistePagina(wmanager->xlmanager.object_tag))
		{
		   popup_errorDialog("Pagina inesistente",w);
		   break;
		}
		if(PaginaAperta(Context->UxtopLevel_selezionata,wmanager->xlmanager.object_tag))
		   break;
		if(!CanOpenPage(w))
		   break;
		if(wmanager->xlmanager.object_tag!=NULL)
		   Pagina_staz=popup_topLevelShellStaz(
				   wmanager->xlmanager.object_tag,
				   Context->UxtopLevel_selezionata,nome_disp,NULL);
                if(Pagina_staz==NULL)
	           popup_errorDialog("Errore Creazione pagina",w);
	  }
#endif
        break;
	};
}



#ifndef DESIGN_TIME
static void refresh_page(_UxCtopLevelShell1 *Context)
#else
static void refresh_page()
#endif
{
int i;


#ifndef DESIGN_TIME
/*** carlo 3-12-97
**/
if(Context->Uxattesa != -1)
	{
	++ Context->Uxattesa;
	if(Context->Uxattesa ==2)
		{
		Context->Uxwid_attesa=popup_Attesa(Context->UxdrawingSinottico);
		}
	}
if(Context->Uxwid_attesa != NULL)
	SettaAttesa(Context->Uxwid_attesa,Context->Uxtime_ref);


if(!OlSetDataPage(database_simulatore,Context->Uxkey_refresh))
        {
        show_warning("Error in refresh");
        return;
        }
if(OlGetDataStatus(database_simulatore,Context->Uxkey_refresh))
   {
   Context->Uxattesa = -1;
   if(Context->Uxwid_attesa != NULL)
	{
	XtDestroyWidget(Context->Uxwid_attesa);
	Context->Uxwid_attesa=NULL;
	}

   UnsetCursorWait(Context->UxdrawingSinottico);
	
   XlRefreshWidget(Context->Uxlista_wid,Context->Uxnum_wid);
   }
if(!OlUnsetDataPage(database_simulatore,Context->Uxkey_refresh))
        {
        show_warning("Error in refresh");
        return;
        }
/*
        carica il timer per il refresh
*/
Context->Uxtimer_refresh = XtAppAddTimeOut (
            XtWidgetToApplicationContext (Context->UxtopLevelShell1),
            (unsigned long) (Context->Uxtime_ref*100) ,(XtTimerCallbackProc)refresh_page, Context);
#endif
}

void PageSelect(Widget w, char *nomePagina, int tipoApertura)
{
Widget Pagina_new = NULL;
#ifndef DESIGN_TIME
Boolean sostituzione = False;
_UxCtopLevelShell1 *Context;
int dim[4];
int num_pag;
 
Context =(_UxCtopLevelShell1 *) UxGetContext(w);

SetCursorWait(Context->UxdrawingSinottico);

if((tipoApertura == CHANGE_PAGE)&& sostituzione)
	{
	if(!EsistePagina(nomePagina))
		{
	 	popup_errorDialog("Errore Creazione pagina",w);
		return;
		}
	if(!CaricaDB(XtDisplay(Context->UxtopLevel_selezionata),nomePagina))
		{
		UnsetCursorWait(Context->UxdrawingSinottico);
		return;
		}
	XtFree((char*)Context->Uxbkg_sin);
	leggi_file_bck(w,nomePagina,"bkg",&(Context->Uxbkg_sin),dim);
 	Context->Uxregion_sin=NULL;
 	DistruggiPagina(Context->Uxlista_wid,Context->Uxnum_wid);
	if(!CreaPagina(Context->UxdrawingSinottico,&(Context->Uxlista_wid),
		 &(Context->Uxnum_wid)))
		{
		UnsetCursorWait(Context->UxdrawingSinottico);
		return;
		}	
	}
else
	{
        if((nomePagina!=NULL)||(tipoApertura == CLOSE_PAGE))
                {
		if(tipoApertura != CLOSE_PAGE)
                {        
                if(!PaginaAperta(Context->UxtopLevel_selezionata,nomePagina))
                  {
		  if(!CanOpenPage(w))
			{
			UnsetCursorWait(Context->UxdrawingSinottico);
			return;
			}
                  num_pag=NumeroPagina(nomePagina);
                  Pagina_new=create_topLevelShell1(nomePagina,
                        Context->UxtopLevel_selezionata,Context->Uxnome_disp,
                        pagine[num_pag].sfondo);
                  if(Pagina_new==NULL)
                        {
                        popup_errorDialog("Errore Creazione pagina",w);
                        UnsetCursorWait(Context->UxdrawingSinottico);
			return;
                        }
                    }
		  }
                  if((tipoApertura == CHANGE_PAGE)||(tipoApertura ==CLOSE_PAGE)) 
                        {        
			DelElencoPagine(Context->Uxkey_refresh, 
				Context->UxdrawingSinottico);
			XSync(XtDisplay(w),False);	
                        XtRemoveTimeOut(Context->Uxtimer_refresh);
                        XtDestroyWidget(Context->UxtopLevelShell1);
                        }
                }
	}
UnsetCursorWait(Context->UxdrawingSinottico);
#endif	
}

void ClosePageSin(Widget w)
{
        _UxCtopLevelShell1      *UxSaveCtx, *UxContext;

        UxSaveCtx = UxTopLevelShell1Context;
        UxTopLevelShell1Context = UxContext =
                        (_UxCtopLevelShell1 *) UxGetContext( w );

        DelElencoPagine(key_refresh,drawingSinottico);
        if(drawing_pixmap)
		XFreePixmap(XtDisplay(w),drawing_pixmap);
        XSync(XtDisplay(w),False);
	XtRemoveTimeOut(timer_refresh);
	XlFreeCursor(topLevelShell1,cursor_wait);
	XtDestroyWidget(topLevelShell1);
        if( pag_db != NULL )
           XrmDestroyDatabase(pag_db);
	printf("Close Page Sinottico\n");


        UxTopLevelShell1Context = UxSaveCtx;        

}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	destroyCB_topLevelShell1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	disarmCB_drawnButtonClose( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	set_something_val( drawnButtonClose, XmNshadowType, (XtArgVal) XmSHADOW_OUT);
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_drawnButtonClose( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	printf("Chiusura della pagina\n");
	if(!CanClosePage(Pagina))
		{
		popup_errorDialog("Unable to close this page",drawingSinottico);
		return;
		}
#ifndef DESIGN_TIME
	popup_CloseQuestion(topLevelShell1,drawingSinottico,&(timer_refresh),key_refresh);
#endif
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	armCB_drawnButtonClose( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	set_something_val( drawnButtonClose, XmNshadowType, (XtArgVal)XmSHADOW_IN);
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_drawnButtonXaing( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	printf("Premuto bottone AING\n");
	operazione_attiva=OPERAZIONE_XAING;
	set_something_val( drawnButtonXaing, XmNshadowType, (XtArgVal)XmSHADOW_IN);
	set_something_val( drawnButtonXstaz, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonInfo, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonNop, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonXplot, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonReg, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	
	
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_drawnButtonXstaz( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	printf("premuto il bottone display\n");
	operazione_attiva=OPERAZIONE_XSTAZ;
	set_something_val( drawnButtonXaing, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonXstaz, XmNshadowType, (XtArgVal)XmSHADOW_IN);
	set_something_val( drawnButtonInfo, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonNop, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonXplot, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonReg, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_drawnButtonInfo( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	printf("premuto bottone info\n");
	operazione_attiva=OPERAZIONE_INFO;
	set_something_val( drawnButtonXaing, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonXstaz, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonInfo, XmNshadowType, (XtArgVal)XmSHADOW_IN);
	set_something_val( drawnButtonNop, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonXplot, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonReg, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	
	
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_drawnButtonNop( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	printf("premuto bottone nop\n");
#ifndef DESIGN_TIME
	operazione_attiva=OPERAZIONE_NOP;
#endif
	set_something_val( drawnButtonXaing, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonXstaz, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonInfo, XmNshadowType, (XtArgVal) XmSHADOW_OUT);
	set_something_val( drawnButtonNop, XmNshadowType, (XtArgVal)XmSHADOW_IN);
	set_something_val( drawnButtonXplot, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonReg, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_drawnButtonXplot( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	printf("Premuto bottone PLOT\n");
	operazione_attiva=OPERAZIONE_XPLOT;
	set_something_val( drawnButtonXplot, XmNshadowType, (XtArgVal)XmSHADOW_IN);
	set_something_val( drawnButtonXstaz, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonInfo, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonNop, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonXaing, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonReg, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_drawnButtonReg( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	printf("premuto il bottone display\n");
	operazione_attiva=OPERAZIONE_REG;
	set_something_val( drawnButtonReg, XmNshadowType, (XtArgVal) XmSHADOW_IN);
	set_something_val( drawnButtonXaing, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonXstaz, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonInfo, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonNop, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	set_something_val( drawnButtonXplot, XmNshadowType, (XtArgVal)XmSHADOW_OUT);
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	exposeCB_drawingSinottico( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	if( bkg_sin != NULL)
	{
	   disegna_bck(UxWidget,bkg_sin,UxCallbackArg,&(region_sin),False);
	}
#endif
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_DispTagModeButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	XlSetSomething(lista_wid,num_wid,"DispReg",XlNdispRegMode,(char*)DISP_TAG_MODE);
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_DispValueModeButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	XlSetSomething(lista_wid,num_wid,"DispReg",XlNdispRegMode,(char*)DISP_VALUE_MODE);
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_DispUnmanagedModeButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	XlSetSomething(lista_wid,num_wid,"DispReg",XlNdispRegMode,DISP_UNMANAGED_MODE);
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_DispPortModeButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	XlSetSomething(lista_wid,num_wid,"Port",XlNvisibleMode,(char*)VISIBLE_PORT_ON);
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_NoDispPortModeButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	XlSetSomething(lista_wid,num_wid,"Port",XlNvisibleMode,VISIBLE_PORT_OFF);
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_menu2_p3_b1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	if(!PrintScreen(drawingSinottico,nome_disp,Pagina,False,bkg_sin))
		popup_errorDialog("Printer not available",drawingSinottico);
#endif
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_menu2_p3_b2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	if(PrintSetup(drawingSinottico)==NULL)
		popup_errorDialog("Printer not available",
	                               drawingSinottico);
#endif
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_menu2_p2_b1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	printf("Chiusura della pagina\n");
	if(!CanClosePage(Pagina))
		{
		popup_errorDialog("Unable to close this page",drawingSinottico);
		return;
		}
#ifndef DESIGN_TIME
	popup_CloseQuestion(topLevelShell1,drawingSinottico,&(timer_refresh),key_refresh);
#endif
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_topLevelShell1()
{
	Widget		_UxParent;
	Widget		menu2_shell;
	Widget		menu2_p4_shell;
	Widget		menu2_p5_shell;
	Widget		menu2_p3_shell;


	/* Creation of topLevelShell1 */
	_UxParent = topLevel_selezionata;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	topLevelShell1 = XtVaCreatePopupShell( "topLevelShell1",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 110,
			XmNy, 30,
			XmNwidth, 1060,
			XmNheight, 900,
			RES_CONVERT( XmNbackground, "#000000" ),
			XmNdeleteResponse, XmDO_NOTHING,
			XmNminWidth, 100,
			XmNminHeight, 580,
			XmNmwmDecorations, MWM_DECOR_TITLE | MWM_DECOR_RESIZEH | MWM_DECOR_MINIMIZE | MWM_DECOR_MAXIMIZE,
			XmNmwmFunctions, -1,
			NULL );
	XtAddCallback( topLevelShell1, XmNdestroyCallback,
		(XtCallbackProc) destroyCB_topLevelShell1,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( topLevelShell1, (char *) UxTopLevelShell1Context );


	/* Creation of form1 */
	form1 = XtVaCreateManagedWidget( "form1",
			xmFormWidgetClass,
			topLevelShell1,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 110,
			XmNy, 70,
			XmNwidth, 910,
			XmNheight, 760,
			RES_CONVERT( XmNbackground, "#000000" ),
			XmNnavigationType, XmNONE,
			XmNtraversalOn, FALSE,
			NULL );
	UxPutContext( form1, (char *) UxTopLevelShell1Context );


	/* Creation of formMenu */
	formMenu = XtVaCreateManagedWidget( "formMenu",
			xmFormWidgetClass,
			form1,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 970,
			XmNy, 0,
			XmNwidth, 56,
			XmNheight, 900,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_NONE,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( formMenu, (char *) UxTopLevelShell1Context );


	/* Creation of form2 */
	form2 = XtVaCreateManagedWidget( "form2",
			xmFormWidgetClass,
			formMenu,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 20,
			XmNy, 780,
			XmNwidth, 60,
			XmNheight, 80,
			XmNrightAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( form2, (char *) UxTopLevelShell1Context );


	/* Creation of drawnButtonClose */
	drawnButtonClose = XtVaCreateManagedWidget( "drawnButtonClose",
			xmDrawnButtonWidgetClass,
			form2,
			XmNx, 4,
			XmNy, 2,
			XmNwidth, 50,
			XmNheight, 50,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNpushButtonEnabled, FALSE,
			XmNshadowThickness, 3,
			RES_CONVERT( XmNtopShadowColor, "#9ebac2" ),
			RES_CONVERT( XmNhighlightColor, "#000000" ),
			XmNhighlightOnEnter, FALSE,
			XmNshadowType, XmSHADOW_OUT,
			XmNlabelType, XmPIXMAP,
			NULL );
	XtAddCallback( drawnButtonClose, XmNdisarmCallback,
		(XtCallbackProc) disarmCB_drawnButtonClose,
		(XtPointer) UxTopLevelShell1Context );
	XtAddCallback( drawnButtonClose, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButtonClose,
		(XtPointer) UxTopLevelShell1Context );
	XtAddCallback( drawnButtonClose, XmNarmCallback,
		(XtCallbackProc) armCB_drawnButtonClose,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( drawnButtonClose, (char *) UxTopLevelShell1Context );


	/* Creation of label5 */
	label5 = XtVaCreateManagedWidget( "label5",
			xmLabelWidgetClass,
			form2,
			XmNx, 4,
			XmNy, 50,
			XmNwidth, 50,
			XmNheight, 20,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNlabelString, "CLOSE" ),
			NULL );
	UxPutContext( label5, (char *) UxTopLevelShell1Context );


	/* Creation of drawnButtonXaing */
	drawnButtonXaing = XtVaCreateManagedWidget( "drawnButtonXaing",
			xmDrawnButtonWidgetClass,
			formMenu,
			XmNx, 4,
			XmNy, 118,
			XmNwidth, 50,
			XmNheight, 50,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNpushButtonEnabled, FALSE,
			XmNshadowThickness, 3,
			RES_CONVERT( XmNtopShadowColor, "#9ebac2" ),
			RES_CONVERT( XmNhighlightColor, "#000000" ),
			XmNhighlightOnEnter, FALSE,
			XmNshadowType, XmSHADOW_OUT,
			XmNlabelType, XmPIXMAP,
			XmNborderWidth, 0,
			XmNrecomputeSize, TRUE,
			XmNalignment, XmALIGNMENT_CENTER,
			XmNsensitive, TRUE,
			NULL );
	XtAddCallback( drawnButtonXaing, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButtonXaing,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( drawnButtonXaing, (char *) UxTopLevelShell1Context );


	/* Creation of drawnButtonXstaz */
	drawnButtonXstaz = XtVaCreateManagedWidget( "drawnButtonXstaz",
			xmDrawnButtonWidgetClass,
			formMenu,
			XmNx, 4,
			XmNy, 318,
			XmNwidth, 50,
			XmNheight, 50,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNpushButtonEnabled, FALSE,
			XmNshadowThickness, 3,
			XmNshadowType, XmSHADOW_OUT,
			XmNlabelType, XmPIXMAP,
			XmNrecomputeSize, TRUE,
			RES_CONVERT( XmNlabelString, "XSTAZ" ),
			NULL );
	XtAddCallback( drawnButtonXstaz, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButtonXstaz,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( drawnButtonXstaz, (char *) UxTopLevelShell1Context );


	/* Creation of drawnButtonInfo */
	drawnButtonInfo = XtVaCreateManagedWidget( "drawnButtonInfo",
			xmDrawnButtonWidgetClass,
			formMenu,
			XmNx, 5,
			XmNy, 520,
			XmNwidth, 50,
			XmNheight, 50,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNpushButtonEnabled, FALSE,
			XmNshadowThickness, 3,
			XmNshadowType, XmSHADOW_OUT,
			XmNlabelType, XmPIXMAP,
			NULL );
	XtAddCallback( drawnButtonInfo, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButtonInfo,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( drawnButtonInfo, (char *) UxTopLevelShell1Context );


	/* Creation of label1 */
	label1 = XtVaCreateManagedWidget( "label1",
			xmLabelWidgetClass,
			formMenu,
			XmNx, 4,
			XmNy, 168,
			XmNwidth, 50,
			XmNheight, 20,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNlabelString, "AING" ),
			NULL );
	UxPutContext( label1, (char *) UxTopLevelShell1Context );


	/* Creation of label3 */
	label3 = XtVaCreateManagedWidget( "label3",
			xmLabelWidgetClass,
			formMenu,
			XmNx, 4,
			XmNy, 368,
			XmNwidth, 50,
			XmNheight, 20,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNlabelString, "STAZ" ),
			NULL );
	UxPutContext( label3, (char *) UxTopLevelShell1Context );


	/* Creation of label4 */
	label4 = XtVaCreateManagedWidget( "label4",
			xmLabelWidgetClass,
			formMenu,
			XmNx, 4,
			XmNy, 568,
			XmNwidth, 50,
			XmNheight, 20,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNlabelString, "INFO" ),
			NULL );
	UxPutContext( label4, (char *) UxTopLevelShell1Context );


	/* Creation of drawnButtonNop */
	drawnButtonNop = XtVaCreateManagedWidget( "drawnButtonNop",
			xmDrawnButtonWidgetClass,
			formMenu,
			XmNx, 4,
			XmNy, 18,
			XmNwidth, 50,
			XmNheight, 50,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNlabelType, XmPIXMAP,
			XmNshadowThickness, 3,
			XmNshadowType, XmSHADOW_IN,
			NULL );
	XtAddCallback( drawnButtonNop, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButtonNop,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( drawnButtonNop, (char *) UxTopLevelShell1Context );


	/* Creation of label6 */
	label6 = XtVaCreateManagedWidget( "label6",
			xmLabelWidgetClass,
			formMenu,
			XmNx, 4,
			XmNy, 68,
			XmNwidth, 50,
			XmNheight, 20,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNlabelString, "NOP" ),
			NULL );
	UxPutContext( label6, (char *) UxTopLevelShell1Context );


	/* Creation of drawnButtonXplot */
	drawnButtonXplot = XtVaCreateManagedWidget( "drawnButtonXplot",
			xmDrawnButtonWidgetClass,
			formMenu,
			XmNx, 4,
			XmNy, 218,
			XmNwidth, 50,
			XmNheight, 50,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNpushButtonEnabled, FALSE,
			XmNshadowThickness, 3,
			RES_CONVERT( XmNtopShadowColor, "#9ebac2" ),
			RES_CONVERT( XmNhighlightColor, "#000000" ),
			XmNhighlightOnEnter, FALSE,
			XmNshadowType, XmSHADOW_OUT,
			XmNlabelType, XmPIXMAP,
			XmNborderWidth, 0,
			XmNrecomputeSize, TRUE,
			XmNalignment, XmALIGNMENT_CENTER,
			NULL );
	XtAddCallback( drawnButtonXplot, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButtonXplot,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( drawnButtonXplot, (char *) UxTopLevelShell1Context );


	/* Creation of label2 */
	label2 = XtVaCreateManagedWidget( "label2",
			xmLabelWidgetClass,
			formMenu,
			XmNx, 4,
			XmNy, 268,
			XmNwidth, 50,
			XmNheight, 20,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNlabelString, "PLOT" ),
			NULL );
	UxPutContext( label2, (char *) UxTopLevelShell1Context );


	/* Creation of drawnButtonReg */
	drawnButtonReg = XtVaCreateManagedWidget( "drawnButtonReg",
			xmDrawnButtonWidgetClass,
			formMenu,
			XmNx, 5,
			XmNy, 420,
			XmNwidth, 50,
			XmNheight, 50,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNpushButtonEnabled, FALSE,
			XmNshadowThickness, 3,
			XmNshadowType, XmSHADOW_OUT,
			XmNlabelType, XmPIXMAP,
			XmNrecomputeSize, TRUE,
			RES_CONVERT( XmNlabelString, "XSTAZ" ),
			NULL );
	XtAddCallback( drawnButtonReg, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButtonReg,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( drawnButtonReg, (char *) UxTopLevelShell1Context );


	/* Creation of label8 */
	label8 = XtVaCreateManagedWidget( "label8",
			xmLabelWidgetClass,
			formMenu,
			XmNx, 5,
			XmNy, 470,
			XmNwidth, 50,
			XmNheight, 20,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNlabelString, "REG" ),
			NULL );
	UxPutContext( label8, (char *) UxTopLevelShell1Context );


	/* Creation of form3 */
	form3 = XtVaCreateManagedWidget( "form3",
			xmFormWidgetClass,
			form1,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 10,
			XmNy, 0,
			XmNwidth, 1090,
			XmNheight, 940,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightWidget, formMenu,
			RES_CONVERT( XmNbackground, "#000000" ),
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			XmNnavigationType, XmNONE,
			XmNtraversalOn, FALSE,
			NULL );
	UxPutContext( form3, (char *) UxTopLevelShell1Context );


	/* Creation of scrolledWindow1 */
	scrolledWindow1 = XtVaCreateManagedWidget( "scrolledWindow1",
			xmScrolledWindowWidgetClass,
			form3,
			XmNscrollingPolicy, XmAUTOMATIC,
			XmNx, 10,
			XmNy, 0,
			XmNwidth, 1100,
			XmNheight, 940,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNnavigationType, XmNONE,
			XmNtraversalOn, FALSE,
			NULL );
	UxPutContext( scrolledWindow1, (char *) UxTopLevelShell1Context );


	/* Creation of drawingSinottico */
	drawingSinottico = XtVaCreateManagedWidget( "drawingSinottico",
			xmDrawingAreaWidgetClass,
			scrolledWindow1,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 4,
			XmNy, 14,
			XmNwidth, 1200,
			XmNheight, 1190,
			RES_CONVERT( XmNbackground, "#000000" ),
			XmNmarginHeight, 0,
			XmNmarginWidth, 0,
			XmNnavigationType, XmNONE,
			XmNtraversalOn, FALSE,
			NULL );
	XtAddCallback( drawingSinottico, XmNexposeCallback,
		(XtCallbackProc) exposeCB_drawingSinottico,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( drawingSinottico, (char *) UxTopLevelShell1Context );


	/* Creation of menu2 */
	menu2_shell = XtVaCreatePopupShell ("menu2_shell",
			xmMenuShellWidgetClass, drawingSinottico,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu2 = XtVaCreateWidget( "menu2",
			xmRowColumnWidgetClass,
			menu2_shell,
			XmNrowColumnType, XmMENU_POPUP,
			XmNmenuAccelerator, "<KeyUp>F4",
			NULL );
	UxPutContext( menu2, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p4 */
	menu2_p4_shell = XtVaCreatePopupShell ("menu2_p4_shell",
			xmMenuShellWidgetClass, menu2,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu2_p4 = XtVaCreateWidget( "menu2_p4",
			xmRowColumnWidgetClass,
			menu2_p4_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( menu2_p4, (char *) UxTopLevelShell1Context );


	/* Creation of DispTagModeButton */
	DispTagModeButton = XtVaCreateManagedWidget( "DispTagModeButton",
			xmPushButtonWidgetClass,
			menu2_p4,
			RES_CONVERT( XmNlabelString, "Tag mode" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( DispTagModeButton, XmNactivateCallback,
		(XtCallbackProc) activateCB_DispTagModeButton,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( DispTagModeButton, (char *) UxTopLevelShell1Context );


	/* Creation of DispValueModeButton */
	DispValueModeButton = XtVaCreateManagedWidget( "DispValueModeButton",
			xmPushButtonWidgetClass,
			menu2_p4,
			RES_CONVERT( XmNlabelString, "Value mode" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( DispValueModeButton, XmNactivateCallback,
		(XtCallbackProc) activateCB_DispValueModeButton,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( DispValueModeButton, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p4_b4 */
	menu2_p4_b4 = XtVaCreateManagedWidget( "menu2_p4_b4",
			xmSeparatorWidgetClass,
			menu2_p4,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( menu2_p4_b4, (char *) UxTopLevelShell1Context );


	/* Creation of DispUnmanagedModeButton */
	DispUnmanagedModeButton = XtVaCreateManagedWidget( "DispUnmanagedModeButton",
			xmPushButtonWidgetClass,
			menu2_p4,
			RES_CONVERT( XmNlabelString, "Unmanaged" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( DispUnmanagedModeButton, XmNactivateCallback,
		(XtCallbackProc) activateCB_DispUnmanagedModeButton,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( DispUnmanagedModeButton, (char *) UxTopLevelShell1Context );


	/* Creation of MenuRegMode */
	MenuRegMode = XtVaCreateManagedWidget( "MenuRegMode",
			xmCascadeButtonWidgetClass,
			menu2,
			RES_CONVERT( XmNlabelString, "Display reg mode" ),
			XmNsubMenuId, menu2_p4,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( MenuRegMode, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p5 */
	menu2_p5_shell = XtVaCreatePopupShell ("menu2_p5_shell",
			xmMenuShellWidgetClass, menu2,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu2_p5 = XtVaCreateWidget( "menu2_p5",
			xmRowColumnWidgetClass,
			menu2_p5_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( menu2_p5, (char *) UxTopLevelShell1Context );


	/* Creation of DispPortModeButton */
	DispPortModeButton = XtVaCreateManagedWidget( "DispPortModeButton",
			xmPushButtonWidgetClass,
			menu2_p5,
			RES_CONVERT( XmNlabelString, "Display ports" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( DispPortModeButton, XmNactivateCallback,
		(XtCallbackProc) activateCB_DispPortModeButton,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( DispPortModeButton, (char *) UxTopLevelShell1Context );


	/* Creation of NoDispPortModeButton */
	NoDispPortModeButton = XtVaCreateManagedWidget( "NoDispPortModeButton",
			xmPushButtonWidgetClass,
			menu2_p5,
			RES_CONVERT( XmNlabelString, "Unmanage ports" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( NoDispPortModeButton, XmNactivateCallback,
		(XtCallbackProc) activateCB_NoDispPortModeButton,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( NoDispPortModeButton, (char *) UxTopLevelShell1Context );


	/* Creation of MenuPortMode */
	MenuPortMode = XtVaCreateManagedWidget( "MenuPortMode",
			xmCascadeButtonWidgetClass,
			menu2,
			RES_CONVERT( XmNlabelString, "Port visual mode" ),
			XmNsubMenuId, menu2_p5,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( MenuPortMode, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p2_b6 */
	menu2_p2_b6 = XtVaCreateManagedWidget( "menu2_p2_b6",
			xmSeparatorWidgetClass,
			menu2,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNhighlightOnEnter, FALSE,
			XmNseparatorType, XmSHADOW_ETCHED_IN,
			NULL );
	UxPutContext( menu2_p2_b6, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p3 */
	menu2_p3_shell = XtVaCreatePopupShell ("menu2_p3_shell",
			xmMenuShellWidgetClass, menu2,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu2_p3 = XtVaCreateWidget( "menu2_p3",
			xmRowColumnWidgetClass,
			menu2_p3_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( menu2_p3, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p3_b1 */
	menu2_p3_b1 = XtVaCreateManagedWidget( "menu2_p3_b1",
			xmPushButtonWidgetClass,
			menu2_p3,
			RES_CONVERT( XmNlabelString, "Print" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( menu2_p3_b1, XmNactivateCallback,
		(XtCallbackProc) activateCB_menu2_p3_b1,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( menu2_p3_b1, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p3_b2 */
	menu2_p3_b2 = XtVaCreateManagedWidget( "menu2_p3_b2",
			xmPushButtonWidgetClass,
			menu2_p3,
			RES_CONVERT( XmNlabelString, "Printer setup" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( menu2_p3_b2, XmNactivateCallback,
		(XtCallbackProc) activateCB_menu2_p3_b2,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( menu2_p3_b2, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p2_b3 */
	menu2_p2_b3 = XtVaCreateManagedWidget( "menu2_p2_b3",
			xmCascadeButtonWidgetClass,
			menu2,
			RES_CONVERT( XmNlabelString, "Harcopy" ),
			XmNsubMenuId, menu2_p3,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( menu2_p2_b3, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p2_b4 */
	menu2_p2_b4 = XtVaCreateManagedWidget( "menu2_p2_b4",
			xmSeparatorWidgetClass,
			menu2,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNseparatorType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			NULL );
	UxPutContext( menu2_p2_b4, (char *) UxTopLevelShell1Context );


	/* Creation of menu2_p2_b1 */
	menu2_p2_b1 = XtVaCreateManagedWidget( "menu2_p2_b1",
			xmPushButtonWidgetClass,
			menu2,
			RES_CONVERT( XmNlabelString, "Close the page" ),
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	XtAddCallback( menu2_p2_b1, XmNactivateCallback,
		(XtCallbackProc) activateCB_menu2_p2_b1,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( menu2_p2_b1, (char *) UxTopLevelShell1Context );


	XtAddCallback( topLevelShell1, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxTopLevelShell1Context);

	XtAddEventHandler(drawingSinottico, ButtonPressMask,
			False, (XtEventHandler) _UxtopLevelShell1MenuPost, (XtPointer) menu2 );

	return ( topLevelShell1 );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_topLevelShell1( _UxPagina, _UxPadre, _Uxnome_disp, _Uxsfondo_sin )
	unsigned char	*_UxPagina;
	Widget	_UxPadre;
	unsigned char	*_Uxnome_disp;
	BCK_OBJ	*_Uxsfondo_sin;
{
	Widget                  rtrn;
	_UxCtopLevelShell1      *UxContext;
	static int		_Uxinit = 0;
	void activateCB_menu2_p2_b1();

	UxTopLevelShell1Context = UxContext =
		(_UxCtopLevelShell1 *) UxNewContext( sizeof(_UxCtopLevelShell1), False );

	Pagina = _UxPagina;
	Padre = _UxPadre;
	nome_disp = _Uxnome_disp;
	sfondo_sin = _Uxsfondo_sin;

	if ( ! _Uxinit )
	{
		UxLoadResources( "topLevelShell1.rf" );
		_Uxinit = 1;
	}

	{
		int top_x,top_y,top_width,top_height,drawing_width,drawing_height;
		char *top_tipo, *top_descrizione;
		Pixel *drawing_background;
		Pixmap pix;
		XmFontList FontTasti, FontLabel;
		int dim[4];
		int num_b;
		Atom WM_DELETE_WINDOW;  /* per distruz. pag da MWM */
//		static void activateCB_menu2_p2_b1();
		drawing_pixmap=0;
		printf("Selezionata la Pagina %s display = %s\n",Pagina,nome_disp);
		if(!EsistePagina(Pagina))
			return(NULL);
		
		/*
			inizializzo il campo operazione attiva
			-1 -> nessuna operazione
			 1 -> xaing
			 2 -> xplot
			 3 -> xstaz
			 4 -> info
		*/
		operazione_attiva = OPERAZIONE_NOP;
		cursor_wait_set = 0;
		topLevel_selezionata=Padre;
		
#ifndef DESIGN_TIME
		if(!(pag_db=CaricaDB(XtDisplay(topLevel_selezionata),Pagina)))
			return(False);
		
		if(!GetResTopLevel(Padre,&top_x,&top_y,&top_width,&top_height,&time_ref,
				&top_tipo,&top_descrizione))
			return(False);
		if(!GetResDrawing(Padre,&drawing_width,&drawing_height,(Pixel*)&drawing_background,&drawing_pixmap))
				return(False);
		if(strcmp(top_tipo,"Stazioni")==0)
			return(popup_topLevelShellStaz(Pagina,Padre,nome_disp,sfondo_sin));
#endif
		printf("Caricate le risorse\n");
		rtrn = _Uxbuild_topLevelShell1();

		/*
		  inizializza la regione di ridisegno
		*/
#ifndef DESIGN_TIME
		if(sfondo_sin!=NULL)
			{
		 	num_b=1;
		 	while(sfondo_sin[num_b-1].tipo>0)
		  		num_b++;
		 	(bkg_sin)=(BCK_OBJ*)XtCalloc(num_b,sizeof(BCK_OBJ));
		 	memcpy((bkg_sin),sfondo_sin,num_b*sizeof(BCK_OBJ));
			AllocaColoriSfondo(topLevelShell1,bkg_sin);
			}
		else
			leggi_file_bck(Padre,Pagina,"bkg",&(bkg_sin),dim);
		
#endif
		region_sin=NULL;
		
		/* setto il nome della pagina */
		set_something_val(topLevelShell1,XmNtitle,(XtArgVal)Pagina);
		set_something_val(topLevelShell1,XmNiconName,(XtArgVal)Pagina);
		set_something_val(topLevelShell1,XmNx,(XtArgVal)top_x);
		set_something_val(topLevelShell1,XmNy,(XtArgVal)top_y);
		set_something_val(topLevelShell1,XmNwidth,(XtArgVal)top_width+50);
		set_something_val(topLevelShell1,XmNheight,(XtArgVal)top_height);
		set_something_val(drawingSinottico,XmNwidth,(XtArgVal)drawing_width);
		set_something_val(drawingSinottico,XmNheight,(XtArgVal)drawing_height);
		if(drawing_pixmap)
			set_something_val(drawingSinottico,XmNbackgroundPixmap,(XtArgVal)drawing_pixmap);
		else	
			set_something_val(drawingSinottico,XmNbackground,(XtArgVal)drawing_background);
		
		
		LoadBitmap(formMenu,&pix,page_sin_icon_bits,page_sin_icon_width,page_sin_icon_height);
		set_something_val(rtrn,XmNiconPixmap,(XtArgVal)pix);
		
		LoadBitmap(drawnButtonNop,&pix,nop_button_bits,nop_button_width,nop_button_height);
		set_something_val(drawnButtonNop,XmNlabelPixmap,(XtArgVal)pix);
		/*
		Inserisco controllo su abilitazione bottoni
		*/
		set_something_val(drawnButtonXaing,XmNsensitive,(XtArgVal)topologia_on);
		LoadBitmap(drawnButtonXaing,&pix,xaing_button_bits,xaing_button_width,xaing_button_height);
		set_something_val(drawnButtonXaing,XmNlabelPixmap,(XtArgVal)pix);
		
		/*
		Staz e' sempre abilitato
		*/
		LoadBitmap(drawnButtonXstaz,&pix,xstaz_button_bits,xstaz_button_width,xstaz_button_height);
		set_something_val(drawnButtonXstaz,XmNlabelPixmap,(XtArgVal)pix);
		
		set_something_val(drawnButtonXplot,XmNsensitive,(XtArgVal)topologia_on);
		LoadBitmap(drawnButtonXplot,&pix,xplot_button_bits,xplot_button_width,xplot_button_height);
		set_something_val(drawnButtonXplot,XmNlabelPixmap,(XtArgVal)pix);
		
		LoadBitmap(drawnButtonInfo,&pix,info_button_bits,info_button_width,info_button_height);
		set_something_val(drawnButtonInfo,XmNlabelPixmap,(XtArgVal)pix);
		
		LoadBitmap(drawnButtonClose,&pix,close_button_bits,close_button_width,close_button_height);
		set_something_val(drawnButtonClose,XmNlabelPixmap,(XtArgVal)pix);
		
		LoadBitmap(drawnButtonReg,&pix,xreg_button_bits,xreg_button_width,xreg_button_height);
		set_something_val(drawnButtonReg,XmNlabelPixmap,(XtArgVal)pix);
		
#ifndef DESIGN_TIME
		LoadFont(FONT_TASTI,&FontTasti,XtDisplay(rtrn));
		LoadFont(FONT_LABEL,&FontLabel,XtDisplay(rtrn));
#endif
		set_something_val(label1,XmNfontList,(XtArgVal)FontTasti);
		set_something_val(label2,XmNfontList,(XtArgVal)FontTasti);
		set_something_val(label3,XmNfontList,(XtArgVal)FontTasti);
		set_something_val(label4,XmNfontList,(XtArgVal)FontTasti);
		set_something_val(label5,XmNfontList,(XtArgVal)FontTasti);
		set_something_val(label6,XmNfontList,(XtArgVal)FontTasti);
		set_something_val(menu2_p2_b1,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(menu2_p2_b3,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(menu2_p3_b1,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(menu2_p3_b2,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(DispTagModeButton,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(DispValueModeButton,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(DispUnmanagedModeButton,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(MenuRegMode,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(MenuPortMode,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(DispPortModeButton,XmNfontList,(XtArgVal)FontLabel);
		set_something_val(NoDispPortModeButton,XmNfontList,(XtArgVal)FontLabel);
#ifndef DESIGN_TIME 
		if(!CreaPagina(drawingSinottico,&lista_wid, &num_wid))
			return(NULL);
#endif
		
		/*
			inserisco la drawing area nell'elenco delle pagine attive
		*/
#ifndef DESIGN_TIME
		if((key_refresh=InsElencoPagine(Pagina,lista_wid,num_wid,time_ref)) == -1)
			return(NULL);
#endif
		UxPopupInterface(rtrn,nonexclusive_grab);
		/*
			creo il cursore di wait
		*/
		cursor_wait = XlCreateWaitCursor(rtrn);
		SetCursorWait(drawingSinottico);
		wid_attesa=NULL;
		attesa = 0;
		
		timer_refresh = XtAppAddTimeOut (
		            XtWidgetToApplicationContext (topLevelShell1),
		            (unsigned long) (time_ref*100) ,(XtTimerCallbackProc)refresh_page, UxContext);
		RaisePlotAing();
		
		/*
		chiamo la callback per distruggere la pagina quando uso close dell' MWM
		*/
		WM_DELETE_WINDOW=XmInternAtom(XtDisplay(topLevelShell1),"WM_DELETE_WINDOW",False);
		XmAddWMProtocolCallback(topLevelShell1,WM_DELETE_WINDOW,activateCB_menu2_p2_b1,NULL);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

