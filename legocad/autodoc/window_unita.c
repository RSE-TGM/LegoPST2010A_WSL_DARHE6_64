
/*******************************************************************************
	window_unita.c
	(Generated from interface file window_unita.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/BulletinB.h>
#include <Xm/ScrolledW.h>
#include <Xm/SeparatoG.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <Xm/Form.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo window_unita.i
   tipo 
   release 1.13
   data 5/15/95
   reserved @(#)window_unita.i	1.13
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/


#include <Xm/RowColumn.h>

#include "autodoc.h"
#include "unita.h"

/************************************************************************/
/* VARIABILI GLOBALI ESTERNE						*/
/************************************************************************/
extern Display *display;

extern Boolean open_window_unita;

extern UnitaMisura unimis[];
extern int num_unita_misura;

extern Arg args[];
extern int nargs;

extern XmString cstring;

extern XmFontList fontList;

/************************************************************************/
/* VARIABILI GLOBALI 							*/
/************************************************************************/

/*******************************************************************************
	The definition of the context structure:
	If you create multiple instances of your interface, the context
	structure ensures that your callbacks use the variables for the
	correct instance.

	For each swidget in the interface, each argument to the Interface
	function, and each variable in the Instance Specific section of the
	Declarations Editor, there is an entry in the context structure.
	and a #define.  The #define makes the variable name refer to the
	corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	Uxwindow_unita;
	Widget	Uxlabel6;
	Widget	Uxpb_done;
	Widget	UxseparatorGadget4;
	Widget	UxscrolledWindow3;
	Widget	Uxbboard_unita;
	Widget	Uxpb_apply_unita;
	Widget	*Uxopt_menu;
} _UxCwindow_unita;

#define window_unita            UxWindow_unitaContext->Uxwindow_unita
#define label6                  UxWindow_unitaContext->Uxlabel6
#define pb_done                 UxWindow_unitaContext->Uxpb_done
#define separatorGadget4        UxWindow_unitaContext->UxseparatorGadget4
#define scrolledWindow3         UxWindow_unitaContext->UxscrolledWindow3
#define bboard_unita            UxWindow_unitaContext->Uxbboard_unita
#define pb_apply_unita          UxWindow_unitaContext->Uxpb_apply_unita
#define opt_menu                UxWindow_unitaContext->Uxopt_menu

static _UxCwindow_unita	*UxWindow_unitaContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_window_unita();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/*** Widget crea_opt_menu_unita(indice, y)
 ***    Parametri:
 ***       int indice : indice array delle unita di misura (unimis[]).
 ***       int y : posizione y del widget
 ***
 ***    Descrizione:
 ***        option-menu per la selezione dell'unita di misura.
 ***/
Widget crea_opt_menu_unita(indice, y)
int indice, y;
{
   int i, ind_dim;
   Widget wmenu, wpull, wpb[5];

   ind_dim = unimis[indice].ind_selez;
   nargs = 0;
   XtSetArg(args[nargs], XmNfontList, fontList); nargs++;
   wpull = XmCreatePulldownMenu(UxGetWidget(bboard_unita), "PDownMenuUnita",
                                args, nargs);

   for ( i=0 ; i<5 ; i++ )
      if ( Empty(unimis[indice].dim[i].codice) )
         break;
      else
      {
         cstring = CREATE_CSTRING(unimis[indice].dim[i].codice);

         nargs = 0;
         XtSetArg(args[nargs], XmNwidth, 60); nargs++;
         XtSetArg(args[nargs], XmNfontList, fontList); nargs++;
         XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;
         XtSetArg(args[nargs], XmNuserData, &unimis[indice]); nargs++;
         XtSetArg(args[nargs], XmNrecomputeSize, False); nargs++;
         wpb[i] = XmCreatePushButton(wpull, "PushBdimUnita", args, nargs);
         XtAddCallback(wpb[i], XmNactivateCallback, cambia_dim_unita, i);
         XtManageChild(wpb[i]);

         XmStringFree(cstring);
      }

   XtVaSetValues(wpull, XmNmenuHistory, wpb[ind_dim], NULL);

   nargs = 0;
   XtSetArg(args[nargs], XmNx, 100); nargs++;
   XtSetArg(args[nargs], XmNy, y); nargs++;
   XtSetArg(args[nargs], XmNwidth, 60); nargs++;
   XtSetArg(args[nargs], XmNfontList, fontList); nargs++;
   XtSetArg(args[nargs], XmNheight, ALTEZZA_TEXT); nargs++;
   XtSetArg(args[nargs], XmNsubMenuId, wpull); nargs++;
   XtSetArg(args[nargs], XmNmenuHistory, wpb[ind_dim]);
   wmenu = XmCreateOptionMenu(UxGetWidget(bboard_unita), "OptMenuUnita", 
			      args,nargs);

   return(wmenu);
}

/*** void cambia_dim_unita(w, ind_dim, call_data)
 ***    Parametri:
 ***       Widget w : widget.
 ***       int ind_dim : dimensione unita misura
 ***       XmPushButtonCallbackStruct *call_data : non utilizzato.
 ***
 ***    Descrizione:
 ***       La callback viene chiamata quando l'utente cambia la dimensione
 ***       dell'unita' di misura.
 ***/
void cambia_dim_unita(w, ind_dim, call_data)
Widget w;
int ind_dim;
XmAnyCallbackStruct *call_data;
{
   UnitaMisura *umis;

   get_something(w, XmNuserData, &umis);
   umis->ind_selez = ind_dim;
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pb_done( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCwindow_unita        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxWindow_unitaContext;
	UxWindow_unitaContext = UxContext =
			(_UxCwindow_unita *) UxGetContext( UxWidget );
	{
	open_window_unita = False;
	
	free(opt_menu);
	
	XtDestroyWidget(XtParent(UxGetWidget(window_unita)));
	}
	UxWindow_unitaContext = UxSaveCtx;
}

static void	activateCB_pb_apply_unita( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCwindow_unita        *UxSaveCtx, *UxContext;

	UxSaveCtx = UxWindow_unitaContext;
	UxWindow_unitaContext = UxContext =
			(_UxCwindow_unita *) UxGetContext( UxWidget );
	{
	
	/* salva le modifiche nel file */
	salva_unita_misura();
	
	/* Cambia le unita di misura nelle window aperte */
	aggiorna_unita_misura();
	}
	UxWindow_unitaContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_window_unita()
{
	Widget	window_unita_shell;

	window_unita_shell = XtVaCreatePopupShell( "window_unita_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 370,
			XmNy, 350,
			XmNwidth, 370,
			XmNheight, 370,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "window_unita",
			NULL );

	window_unita = XtVaCreateWidget( "window_unita",
			xmFormWidgetClass, window_unita_shell,
			XmNautoUnmanage, FALSE,
			XmNdialogStyle, XmDIALOG_MODELESS,
			RES_CONVERT( XmNdialogTitle, "MEASURING UNIT" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 370,
			XmNwidth, 370,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( window_unita, (char *) UxWindow_unitaContext );

	label6 = XtVaCreateManagedWidget( "label6",
			xmLabelWidgetClass, window_unita,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Select the measure unit to be modified:" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 250,
			XmNy, 20,
			XmNx, 10,
			NULL );

	UxPutContext( label6, (char *) UxWindow_unitaContext );

	pb_done = XtVaCreateManagedWidget( "pb_done",
			xmPushButtonWidgetClass, window_unita,
			XmNrightOffset, 20,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightPosition, 65,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 55,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			RES_CONVERT( XmNlabelString, "Close" ),
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 120,
			XmNy, 330,
			XmNx, 130,
			NULL );

	UxPutContext( pb_done, (char *) UxWindow_unitaContext );

	separatorGadget4 = XtVaCreateManagedWidget( "separatorGadget4",
			xmSeparatorGadgetClass, window_unita,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightOffset, 5,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomWidget, pb_done,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNheight, 10,
			XmNwidth, 680,
			XmNy, 370,
			XmNx, 20,
			NULL );

	UxPutContext( separatorGadget4, (char *) UxWindow_unitaContext );

	scrolledWindow3 = XtVaCreateManagedWidget( "scrolledWindow3",
			xmScrolledWindowWidgetClass, window_unita,
			XmNtopWidget, label6,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomWidget, separatorGadget4,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 250,
			XmNwidth, 350,
			XmNy, 60,
			XmNx, 10,
			XmNscrollingPolicy, XmAUTOMATIC,
			NULL );

	UxPutContext( scrolledWindow3, (char *) UxWindow_unitaContext );

	bboard_unita = XtVaCreateManagedWidget( "bboard_unita",
			xmBulletinBoardWidgetClass, scrolledWindow3,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 1300,
			XmNwidth, 330,
			XmNy, -2,
			XmNx, 8,
			XmNresizePolicy, XmRESIZE_ANY,
			NULL );

	UxPutContext( bboard_unita, (char *) UxWindow_unitaContext );

	pb_apply_unita = XtVaCreateManagedWidget( "pb_apply_unita",
			xmPushButtonWidgetClass, window_unita,
			RES_CONVERT( XmNlabelString, "Apply" ),
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightPosition, 45,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNbackground, "#4f9f9f" ),
			XmNheight, 30,
			XmNwidth, 90,
			XmNy, 320,
			XmNx, 20,
			NULL );

	UxPutContext( pb_apply_unita, (char *) UxWindow_unitaContext );

	XtAddCallback( window_unita, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxWindow_unitaContext );

	XtAddCallback( pb_done, XmNactivateCallback,
			activateCB_pb_done,
			(XtPointer) UxWindow_unitaContext );

	XtAddCallback( pb_apply_unita, XmNactivateCallback,
			activateCB_pb_apply_unita,
			(XtPointer) UxWindow_unitaContext );



	return ( window_unita );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_window_unita()
{
	Widget                  rtrn;
	_UxCwindow_unita        *UxContext;

	UxWindow_unitaContext = UxContext =
		(_UxCwindow_unita *) XtMalloc( sizeof(_UxCwindow_unita) );

	{
		int i, y, ind;
		Widget wlabel, wbutton;
		
		open_window_unita = True;
		
		opt_menu = (Widget *) calloc(num_unita_misura, sizeof(Widget));
		rtrn = _Uxbuild_window_unita();

		for ( i = 0, y = 10 ; i < num_unita_misura ; i++, y += ALTEZZA_TEXT+5 )
		{
		/* creazione LABEL unita di misura */
		   cstring = CREATE_CSTRING(unimis[i].nome_tipo);
		
		   nargs = 0;
		   XtSetArg(args[nargs], XmNx, 10); nargs++;
		   XtSetArg(args[nargs], XmNy, y); nargs++;
		   XtSetArg(args[nargs], XmNheight, ALTEZZA_TEXT); nargs++;
		   XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;
		   XtSetArg(args[nargs], XmNfontList, fontList); nargs++;
		   XtSetArg(args[nargs], XmNrecomputeSize, True); nargs++;
		   XtSetArg(args[nargs], XmNalignment, XmALIGNMENT_BEGINNING); nargs++;
		   wlabel = XmCreateLabel(UxGetWidget(bboard_unita), "LabelUnita", args,nargs);
		   XmStringFree(cstring);
		
		   opt_menu[i] = crea_opt_menu_unita(i, y);
		
		   XtManageChild(opt_menu[i]);
		   XtManageChild(wlabel);
		}
		
		UxPopupInterface(rtrn, no_grab);
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_window_unita()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_window_unita();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

