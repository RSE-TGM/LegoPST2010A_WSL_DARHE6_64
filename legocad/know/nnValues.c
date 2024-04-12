
/*******************************************************************************
	nnValues.c
	(Generated from interface file nnValues.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Text.h>
#include <Xm/PushB.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/Label.h>
#include <Xm/BulletinB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo nnValues.i
   tipo 
   release 1.13
   data 11/13/95
   reserved @(#)nnValues.i	1.13
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

/* "nnValues.c"   (ancillare di "nnEdit.c")
* Scopo:       altera valori di variabili selezionate da nnEdit.
* Dati:        da files 'f03.dat' e 'f14.dat', assunti precaricati.
* Risultati:   nuovi valori delle variabili.
* Note:
* (1)  Verifica immissione in formato float.
* (2)  Possibile recedere dall' alterazione immessa.
* Autore:      C.Lusso (CISE) 1994
*/

 /* include: */
#include <Xm/MessageB.h>
#include <Xm/RowColumn.h>
#include "f03.h"
#include "f14.h"
#include "uni_mis.h"
#include "helpkit.h"
 /* define: */
#define NNV_LEN_VAL (OFF_END_DATO1 - OFF_INI_DATO1)
 /* variabili: */
static String
 nnVzHpage = "nnValues",
 szOmenu = "Omenu";
 /* funzioni (in "nnWorks.c"): */
extern S_UNI_MIS *nnVget_uni_mis( unsigned char ind_umis )
;

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
	Widget	UxnnValues;
	Widget	UxnnV_labModel;
	Widget	UxnnV_sWin;
	Widget	UxnnV_sList;
	Widget	UxnnV_labCodice;
	Widget	UxnnV_pbOk;
	Widget	UxnnV_pbCancel;
	Widget	UxnnV_pbHelp;
	Widget	UxnnV_textValue;
	int	UxcValues;
	int	*UxaiVals;
	int	UxiValue;
	VAL_VAR	**Uxapval0;
	VAL_VAR	**UxapvalV;
	Widget	UxnnV_help;
	Widget	UxnnV_rcOmenu;
	Position	UxxOmenu;
	Position	UxyOmenu;
	XmString	UxaxsOnomi[6];
	XmButtonType	UxaxtOtipi[6];
	Cardinal	UxcOdata;
	Widget	UxwgtVparent;
	String	UxnnVzHfile;
	VAL_VAR	*UxavvValues;
	int	*UxaiV;
} _UxCnnValues;

#define nnValues                UxNnValuesContext->UxnnValues
#define nnV_labModel            UxNnValuesContext->UxnnV_labModel
#define nnV_sWin                UxNnValuesContext->UxnnV_sWin
#define nnV_sList               UxNnValuesContext->UxnnV_sList
#define nnV_labCodice           UxNnValuesContext->UxnnV_labCodice
#define nnV_pbOk                UxNnValuesContext->UxnnV_pbOk
#define nnV_pbCancel            UxNnValuesContext->UxnnV_pbCancel
#define nnV_pbHelp              UxNnValuesContext->UxnnV_pbHelp
#define nnV_textValue           UxNnValuesContext->UxnnV_textValue
#define cValues                 UxNnValuesContext->UxcValues
#define aiVals                  UxNnValuesContext->UxaiVals
#define iValue                  UxNnValuesContext->UxiValue
#define apval0                  UxNnValuesContext->Uxapval0
#define apvalV                  UxNnValuesContext->UxapvalV
#define nnV_help                UxNnValuesContext->UxnnV_help
#define nnV_rcOmenu             UxNnValuesContext->UxnnV_rcOmenu
#define xOmenu                  UxNnValuesContext->UxxOmenu
#define yOmenu                  UxNnValuesContext->UxyOmenu
#define axsOnomi                UxNnValuesContext->UxaxsOnomi
#define axtOtipi                UxNnValuesContext->UxaxtOtipi
#define cOdata                  UxNnValuesContext->UxcOdata
#define wgtVparent              UxNnValuesContext->UxwgtVparent
#define nnVzHfile               UxNnValuesContext->UxnnVzHfile
#define avvValues               UxNnValuesContext->UxavvValues
#define aiV                     UxNnValuesContext->UxaiV

static _UxCnnValues	*UxNnValuesContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_nnValues();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/* codice ausiliario: */
/* ------------------ */
static void textValue( float val );
static XtCallbackProc
 nnVhelpCB(),
 nnVsimpleCB(),
 nnVokCB(),
 nnVcancelCB();

/* ------------------ */
static void textValue( float val )
{
 char app[NNV_LEN_VAL+1];
   spr_float( app, val );
   XtVaSetValues( nnV_textValue, XmNvalue, app, NULL );
}

/* ------------------ */
static XtCallbackProc nnVhelpCB(
 Widget wgt,
 XtPointer pC,
 XmAnyCallbackStruct *pA)
{
 XtManageChild( nnV_help);
}

/* ------------------ */
static XtCallbackProc nnVsimpleCB(
 Widget wgt,
 int iNuo,
 XmAnyCallbackStruct *pA)
{
 VAL_VAR *pval =apvalV[iValue];
   if (iNuo < cOdata) {
     S_UNI_MIS *pum = nnVget_uni_mis( pval->ind_umis );
     int iVec =pval->sel_umis;
      apvalV[iValue]->sel_umis = iNuo;
      if (iVec != pum->sel)
         pval->val = (pval->val - pum->B[iVec]) / pum->A[iVec];
      if (iNuo != pum->sel)
         pval->val = pval->val * pum->A[iNuo] + pum->B[iNuo];
      textValue( pval->val);
   } else {
      memcpy( pval, apval0[iValue], sizeof(VAL_VAR));
      XmListSelectPos( nnV_sList, iValue +1, True);
   }
}

/* ------------------ */
static XtCallbackProc nnVokCB(
 Widget wgt,
 XtPointer pC,
 XmAnyCallbackStruct *pA)
{
 int i;
 FILE *fp;
 S_UNI_MIS *pum;
   for (i=0; i<cValues; i++) {
      apval0[i]->val = apvalV[i]->val;
      apval0[i]->sel_umis = apvalV[i]->sel_umis;
   }
   fnnV_ritorna_E( True);
   nnVcancelCB( 0, 0, 0);
}

/* ------------------ */
static XtCallbackProc nnVcancelCB(
 Widget wgt,
 XtPointer pC,
 XmAnyCallbackStruct *pA)
{
   XtFree( (char *) apval0 );
   XtFree( (char *) apvalV );
   XtFree( (char *) axsOnomi );
   XtFree( axtOtipi );
   XtDestroyWidget( XtParent( nnValues) );
}
/* ------------------ */

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	createCB_nnV_sList( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCnnValues            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxNnValuesContext;
	UxNnValuesContext = UxContext =
			(_UxCnnValues *) UxGetContext( UxWidget );
	{
	/* carica la ScrolledList delle Vars */
	 char ah[2+100+1], *z, b=' ';
	 int i, ivj;
	 XmString xs;
	   ah[1] = b;
	   ah[2+100] = '\0';
	   for (i=0; i<cValues; i++) {
	      ah[0] = (apval0[i]->noto) ? '*' : b;
	      ivj = aiVals[1+i];
	      z = (ivj>0) ? nom_sivar[ivj-1] : nom_vari[-ivj-1];
	      strncpy( ah+2, z, 100);
	      xs = XmStringCreateSimple( ah);
	      XmListAddItemUnselected( nnV_sList, xs, 0);
	      XmStringFree( xs);
	   }
	   XtVaSetValues( nnV_sList, XmNvisibleItemCount, cValues, NULL);
	
	}
	UxNnValuesContext = UxSaveCtx;
}

static void	browseSelectionCB_nnV_sList( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCnnValues            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxNnValuesContext;
	UxNnValuesContext = UxContext =
			(_UxCnnValues *) UxGetContext( UxWidget );
	{
	 XmListCallbackStruct *pA =
	(XmListCallbackStruct *)UxCallbackArg;
	 VAL_VAR *pval;
	 S_UNI_MIS *pum;
	 char *z;
	 Arg a[8];
	 Cardinal k, n;
	   iValue = pA->item_position -1;
	   pval = apvalV[iValue];
	   pum = nnVget_uni_mis( pval->ind_umis );
	   UxPutStrRes( nnV_labCodice, XmNlabelString, pum->codice);
	   textValue( pval->val);
	   for (k=0; k<N_TIPI_UMIS && *(z=pum->codm[k]) != ' '; k++)
	      axsOnomi[k] = XmStringCreateSimple( z);
	   axsOnomi[cOdata=k++] = XmStringCreateSimple( "(restore)");
	   XtDestroyWidget( nnV_rcOmenu );
	   n=0;
	   XtSetArg( a[n], XmNx, xOmenu); n++;
	   XtSetArg( a[n], XmNy, yOmenu); n++;
	   XtSetArg( a[n], XmNbuttonCount, k); n++;
	   XtSetArg( a[n], XmNbuttons, axsOnomi); n++;
	   XtSetArg( a[n], XmNbuttonType, axtOtipi); n++;
	   XtSetArg( a[n], XmNbuttonSet, pval->sel_umis); n++;
	   XtSetArg( a[n], XmNsimpleCallback, nnVsimpleCB); n++;
	   nnV_rcOmenu = XmCreateSimpleOptionMenu(
	    nnValues, szOmenu, a, n);
	   XtManageChild( nnV_rcOmenu );
	   while (k--)
	      XmStringFree( axsOnomi[k]);
	}
	UxNnValuesContext = UxSaveCtx;
}

static void	valueChangedCB_nnV_textValue( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCnnValues            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxNnValuesContext;
	UxNnValuesContext = UxContext =
			(_UxCnnValues *) UxGetContext( UxWidget );
	{
	 XmAnyCallbackStruct *pA =
	(XmAnyCallbackStruct *) UxCallbackArg;
	 char *ahValue;
	 float val;
	   XtVaGetValues( UxWidget, XmNvalue, &ahValue, NULL);
	   if (sscanf( ahValue, "%f", &val) ) {
	      apvalV[iValue]->val = val;
	   } else {
	      textValue( apvalV[iValue]->val);
	   }
	   XtFree( ahValue);
	}
	UxNnValuesContext = UxSaveCtx;
}

static void	modifyVerifyCB_nnV_textValue( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCnnValues            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxNnValuesContext;
	UxNnValuesContext = UxContext =
			(_UxCnnValues *) UxGetContext( UxWidget );
	{
	 XmTextVerifyPtr pA =
	(XmTextVerifyPtr) UxCallbackArg;
	 static char ahAbili[] = "0123456789+-.eE";
	 int i=0, l=pA->text->length;
	   while (i<l && strchr( ahAbili, pA->text->ptr[i]) )
	      i++;
	   while (i<l && pA->text->ptr[i]==' ' )
	      i++;
	   pA->doit = (i==l);
	}
	UxNnValuesContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_nnValues()
{
	Widget	nnValues_shell;

	nnValues_shell = XtVaCreatePopupShell( "nnValues_shell",
			xmDialogShellWidgetClass, wgtVparent,
			XmNx, 200,
			XmNy, 300,
			XmNwidth, 400,
			XmNheight, 300,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "nnValues",
			NULL );

	nnValues = XtVaCreateWidget( "nnValues",
			xmBulletinBoardWidgetClass, nnValues_shell,
			XmNautoUnmanage, FALSE,
			XmNnoResize, TRUE,
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			XmNheight, 300,
			XmNwidth, 400,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( nnValues, (char *) UxNnValuesContext );

	nnV_labModel = XtVaCreateManagedWidget( "nnV_labModel",
			xmLabelWidgetClass, nnValues,
			XmNalignment, XmALIGNMENT_CENTER,
			XmNheight, 20,
			XmNwidth, 290,
			XmNy, 20,
			XmNx, 50,
			NULL );

	UxPutContext( nnV_labModel, (char *) UxNnValuesContext );

	nnV_sWin = XtVaCreateManagedWidget( "nnV_sWin",
			xmScrolledWindowWidgetClass, nnValues,
			XmNwidth, 360,
			XmNheight, 100,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 50,
			XmNx, 20,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( nnV_sWin, (char *) UxNnValuesContext );

	nnV_sList = XtVaCreateManagedWidget( "nnV_sList",
			xmListWidgetClass, nnV_sWin,
			XmNlistSizePolicy, XmRESIZE_IF_POSSIBLE,
			XmNselectionPolicy, XmBROWSE_SELECT,
			XmNheight, 120,
			XmNwidth, 360,
			NULL );

	UxPutContext( nnV_sList, (char *) UxNnValuesContext );

	createCB_nnV_sList( nnV_sList,
			(XtPointer) UxNnValuesContext, (XtPointer) NULL );

	nnV_labCodice = XtVaCreateManagedWidget( "nnV_labCodice",
			xmLabelWidgetClass, nnValues,
			XmNheight, 30,
			XmNwidth, 100,
			XmNy, 170,
			XmNx, 40,
			NULL );

	UxPutContext( nnV_labCodice, (char *) UxNnValuesContext );

	nnV_pbOk = XtVaCreateManagedWidget( "nnV_pbOk",
			xmPushButtonWidgetClass, nnValues,
			RES_CONVERT( XmNlabelString, "Ok" ),
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 230,
			XmNx, 40,
			NULL );

	UxPutContext( nnV_pbOk, (char *) UxNnValuesContext );

	nnV_pbCancel = XtVaCreateManagedWidget( "nnV_pbCancel",
			xmPushButtonWidgetClass, nnValues,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 230,
			XmNx, 160,
			NULL );

	UxPutContext( nnV_pbCancel, (char *) UxNnValuesContext );

	nnV_pbHelp = XtVaCreateManagedWidget( "nnV_pbHelp",
			xmPushButtonWidgetClass, nnValues,
			RES_CONVERT( XmNlabelString, "Help" ),
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 230,
			XmNx, 280,
			NULL );

	UxPutContext( nnV_pbHelp, (char *) UxNnValuesContext );

	nnV_textValue = XtVaCreateManagedWidget( "nnV_textValue",
			xmTextWidgetClass, nnValues,
			XmNmaxLength, NNV_LEN_VAL,
			XmNheight, 30,
			XmNwidth, 100,
			XmNy, 170,
			XmNx, 150,
			NULL );

	UxPutContext( nnV_textValue, (char *) UxNnValuesContext );

	XtAddCallback( nnValues, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxNnValuesContext );

	XtAddCallback( nnValues, XmNunmapCallback,
			nnVcancelCB,
			(XtPointer) UxNnValuesContext );
	XtAddCallback( nnValues, XmNhelpCallback,
			nnVhelpCB,
			(XtPointer) UxNnValuesContext );

	XtAddCallback( nnV_sList, XmNbrowseSelectionCallback,
			browseSelectionCB_nnV_sList,
			(XtPointer) UxNnValuesContext );

	XtAddCallback( nnV_pbOk, XmNactivateCallback,
			nnVokCB,
			(XtPointer) UxNnValuesContext );

	XtAddCallback( nnV_pbCancel, XmNactivateCallback,
			nnVcancelCB,
			(XtPointer) UxNnValuesContext );

	XtAddCallback( nnV_pbHelp, XmNactivateCallback,
			nnVhelpCB,
			(XtPointer) UxNnValuesContext );

	XtAddCallback( nnV_textValue, XmNvalueChangedCallback,
			valueChangedCB_nnV_textValue,
			(XtPointer) UxNnValuesContext );
	XtAddCallback( nnV_textValue, XmNmodifyVerifyCallback,
			modifyVerifyCB_nnV_textValue,
			(XtPointer) UxNnValuesContext );



	return ( nnValues );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_nnValues( _UxwgtVparent, _UxnnVzHfile, _UxavvValues, _UxaiV )
	Widget	_UxwgtVparent;
	String	_UxnnVzHfile;
	VAL_VAR	*_UxavvValues;
	int	*_UxaiV;
{
	Widget                  rtrn;
	_UxCnnValues            *UxContext;

	UxNnValuesContext = UxContext =
		(_UxCnnValues *) XtMalloc( sizeof(_UxCnnValues) );

	wgtVparent = _UxwgtVparent;
	nnVzHfile = _UxnnVzHfile;
	avvValues = _UxavvValues;
	aiV = _UxaiV;
	{
		/* codice iniziale: */
		{
		 int i, ivj, off;
		 VAL_VAR *pval;
		   cValues = aiV[0];
		   aiVals = (int *) XtCalloc( cValues+1, sizeof(int));
		   for (i=0; i<=cValues; i++)
		      aiVals[i] = aiV[i];
		   apval0 = (VAL_VAR **) XtMalloc( sizeof(VAL_VAR *) * cValues);
		   off = sizeof(VAL_VAR *) * cValues;
		   apvalV = (VAL_VAR **) XtMalloc( off + sizeof(VAL_VAR) * cValues);
		   for (i=0, pval=(VAL_VAR *)(apvalV+cValues); i<cValues; i++, pval++) {
		      ivj = aiV[1+i];
		      apval0[i] = (ivj>0) ? &avvValues[ivj-1] : &avvValues[neqsis-ivj-1];
		      apvalV[i] = pval;
		      memcpy( apvalV[i], apval0[i], sizeof(VAL_VAR));
		   }
		   for (i=0; i<N_TIPI_UMIS+1; i++)
		      axtOtipi[i] = XmPUSHBUTTON;
		}
		rtrn = _Uxbuild_nnValues();

		/* codice finale: */
		XtManageChild( rtrn);
		nnV_help = helpkit_propInfo( rtrn, nnVzHfile, nnVzHpage);
		{
		 char zModel[24];
		 Dimension wt;
		   sprintf( zModel, "Model name: %.8s", sigla );
		   UxPutStrRes( nnV_labModel, XmNlabelString, zModel );
		   XtVaGetValues( nnV_textValue,
		    XmNx, &xOmenu,
		    XmNy, &yOmenu,
		    XmNwidth, &wt,
		    NULL);
		   xOmenu += wt +10;
		   nnV_rcOmenu = XmCreateRowColumn( rtrn, szOmenu, NULL, 0);
		}
		XmListSelectPos( nnV_sList, 1, True);
		
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_nnValues( _UxwgtVparent, _UxnnVzHfile, _UxavvValues, _UxaiV )
	Widget	_UxwgtVparent;
	String	_UxnnVzHfile;
	VAL_VAR	*_UxavvValues;
	int	*_UxaiV;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_nnValues( _UxwgtVparent, _UxnnVzHfile, _UxavvValues, _UxaiV );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

