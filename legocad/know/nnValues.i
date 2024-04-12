! UIMX ascii 2.0 key: 9113                                                      

*nnValues.class: bulletinBoardDialog
*nnValues.parent: NO_PARENT
*nnValues.parentExpression: wgtVparent
*nnValues.defaultShell: topLevelShell
*nnValues.static: true
*nnValues.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo nnValues.i\
   tipo \
   release 1.13\
   data 11/13/95\
   reserved @(#)nnValues.i	1.13\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
#include <stdio.h>\
/* "nnValues.c"   (ancillare di "nnEdit.c")\
* Scopo:       altera valori di variabili selezionate da nnEdit.\
* Dati:        da files 'f03.dat' e 'f14.dat', assunti precaricati.\
* Risultati:   nuovi valori delle variabili.\
* Note:\
* (1)  Verifica immissione in formato float.\
* (2)  Possibile recedere dall' alterazione immessa.\
* Autore:      C.Lusso (CISE) 1994\
*/\
\
 /* include: */\
#include <Xm/MessageB.h>\
#include <Xm/RowColumn.h>\
#include "f03.h"\
#include "f14.h"\
#include "uni_mis.h"\
#include "helpkit.h"\
 /* define: */\
#define NNV_LEN_VAL (OFF_END_DATO1 - OFF_INI_DATO1)\
 /* variabili: */\
static String\
 nnVzHpage = "nnValues",\
 szOmenu = "Omenu";\
 /* funzioni (in "nnWorks.c"): */\
extern S_UNI_MIS *nnVget_uni_mis( unsigned char ind_umis )\
;
*nnValues.ispecdecl: int\
 cValues,\
 *aiVals,\
 iValue;\
VAL_VAR\
 **apval0,\
 **apvalV;\
Widget\
 nnV_help,\
 nnV_rcOmenu;\
Position\
 xOmenu,\
 yOmenu;\
XmString\
 axsOnomi[N_TIPI_UMIS+1];\
XmButtonType\
 axtOtipi[N_TIPI_UMIS+1];\
Cardinal\
 cOdata;
*nnValues.ispeclist: cValues, aiVals, iValue, apval0, apvalV, nnV_help, nnV_rcOmenu, xOmenu, yOmenu, axsOnomi, axtOtipi, cOdata
*nnValues.ispeclist.cValues: "int", "%cValues%"
*nnValues.ispeclist.aiVals: "int", "*%aiVals%"
*nnValues.ispeclist.iValue: "int", "%iValue%"
*nnValues.ispeclist.apval0: "VAL_VAR", "**%apval0%"
*nnValues.ispeclist.apvalV: "VAL_VAR", "**%apvalV%"
*nnValues.ispeclist.nnV_help: "Widget", "%nnV_help%"
*nnValues.ispeclist.nnV_rcOmenu: "Widget", "%nnV_rcOmenu%"
*nnValues.ispeclist.xOmenu: "Position", "%xOmenu%"
*nnValues.ispeclist.yOmenu: "Position", "%yOmenu%"
*nnValues.ispeclist.axsOnomi: "XmString", "%axsOnomi%[6]"
*nnValues.ispeclist.axtOtipi: "XmButtonType", "%axtOtipi%[6]"
*nnValues.ispeclist.cOdata: "Cardinal", "%cOdata%"
*nnValues.funcdecl: swidget create_nnValues(\
 Widget wgtVparent,\
 String nnVzHfile,\
 VAL_VAR *avvValues,\
 int *aiV )\

*nnValues.funcname: create_nnValues
*nnValues.funcdef: "swidget", "<create_nnValues>(%)"
*nnValues.argdecl: Widget wgtVparent;\
String nnVzHfile;\
VAL_VAR *avvValues;\
int *aiV;
*nnValues.arglist: wgtVparent, nnVzHfile, avvValues, aiV
*nnValues.arglist.wgtVparent: "Widget", "%wgtVparent%"
*nnValues.arglist.nnVzHfile: "String", "%nnVzHfile%"
*nnValues.arglist.avvValues: "VAL_VAR", "*%avvValues%"
*nnValues.arglist.aiV: "int", "*%aiV%"
*nnValues.icode: /* codice iniziale: */\
{\
 int i, ivj, off;\
 VAL_VAR *pval;\
   cValues = aiV[0];\
   aiVals = (int *) XtCalloc( cValues+1, sizeof(int));\
   for (i=0; i<=cValues; i++)\
      aiVals[i] = aiV[i];\
   apval0 = (VAL_VAR **) XtMalloc( sizeof(VAL_VAR *) * cValues);\
   off = sizeof(VAL_VAR *) * cValues;\
   apvalV = (VAL_VAR **) XtMalloc( off + sizeof(VAL_VAR) * cValues);\
   for (i=0, pval=(VAL_VAR *)(apvalV+cValues); i<cValues; i++, pval++) {\
      ivj = aiV[1+i];\
      apval0[i] = (ivj>0) ? &avvValues[ivj-1] : &avvValues[neqsis-ivj-1];\
      apvalV[i] = pval;\
      memcpy( apvalV[i], apval0[i], sizeof(VAL_VAR));\
   }\
   for (i=0; i<N_TIPI_UMIS+1; i++)\
      axtOtipi[i] = XmPUSHBUTTON;\
}\

*nnValues.fcode: /* codice finale: */\
XtManageChild( rtrn);\
nnV_help = helpkit_propInfo( rtrn, nnVzHfile, nnVzHpage);\
{\
 char zModel[24];\
 Dimension wt;\
   sprintf( zModel, "Model name: %.8s", sigla );\
   UxPutStrRes( nnV_labModel, XmNlabelString, zModel );\
   XtVaGetValues( nnV_textValue,\
    XmNx, &xOmenu,\
    XmNy, &yOmenu,\
    XmNwidth, &wt,\
    NULL);\
   xOmenu += wt +10;\
   nnV_rcOmenu = XmCreateRowColumn( rtrn, szOmenu, NULL, 0);\
}\
XmListSelectPos( nnV_sList, 1, True);\
\
return(rtrn);\

*nnValues.auxdecl: /* codice ausiliario: */\
/* ------------------ */\
static void textValue( float val );\
static XtCallbackProc\
 nnVhelpCB(),\
 nnVsimpleCB(),\
 nnVokCB(),\
 nnVcancelCB();\
\
/* ------------------ */\
static void textValue( float val )\
{\
 char app[NNV_LEN_VAL+1];\
   spr_float( app, val );\
   XtVaSetValues( nnV_textValue, XmNvalue, app, NULL );\
}\
\
/* ------------------ */\
static XtCallbackProc nnVhelpCB(\
 Widget wgt,\
 XtPointer pC,\
 XmAnyCallbackStruct *pA)\
{\
 XtManageChild( nnV_help);\
}\
\
/* ------------------ */\
static XtCallbackProc nnVsimpleCB(\
 Widget wgt,\
 int iNuo,\
 XmAnyCallbackStruct *pA)\
{\
 VAL_VAR *pval =apvalV[iValue];\
   if (iNuo < cOdata) {\
     S_UNI_MIS *pum = nnVget_uni_mis( pval->ind_umis );\
     int iVec =pval->sel_umis;\
      apvalV[iValue]->sel_umis = iNuo;\
      if (iVec != pum->sel)\
         pval->val = (pval->val - pum->B[iVec]) / pum->A[iVec];\
      if (iNuo != pum->sel)\
         pval->val = pval->val * pum->A[iNuo] + pum->B[iNuo];\
      textValue( pval->val);\
   } else {\
      memcpy( pval, apval0[iValue], sizeof(VAL_VAR));\
      XmListSelectPos( nnV_sList, iValue +1, True);\
   }\
}\
\
/* ------------------ */\
static XtCallbackProc nnVokCB(\
 Widget wgt,\
 XtPointer pC,\
 XmAnyCallbackStruct *pA)\
{\
 int i;\
 FILE *fp;\
 S_UNI_MIS *pum;\
   for (i=0; i<cValues; i++) {\
      apval0[i]->val = apvalV[i]->val;\
      apval0[i]->sel_umis = apvalV[i]->sel_umis;\
   }\
   fnnV_ritorna_E( True);\
   nnVcancelCB( 0, 0, 0);\
}\
\
/* ------------------ */\
static XtCallbackProc nnVcancelCB(\
 Widget wgt,\
 XtPointer pC,\
 XmAnyCallbackStruct *pA)\
{\
   XtFree( apval0 );\
   XtFree( apvalV );\
   XtFree( axsOnomi );\
   XtFree( axtOtipi );\
   XtDestroyWidget( XtParent( nnValues) );\
}\
/* ------------------ */
*nnValues.name: nnValues
*nnValues.unitType: "pixels"
*nnValues.x: 200
*nnValues.y: 300
*nnValues.width: 400
*nnValues.height: 300
*nnValues.dialogStyle: "dialog_primary_application_modal"
*nnValues.noResize: "true"
*nnValues.helpCallback.source: public
*nnValues.helpCallback: nnVhelpCB
*nnValues.unmapCallback.source: public
*nnValues.unmapCallback: nnVcancelCB
*nnValues.autoUnmanage: "false"

*nnV_labModel.class: label
*nnV_labModel.parent: nnValues
*nnV_labModel.static: true
*nnV_labModel.name: nnV_labModel
*nnV_labModel.x: 50
*nnV_labModel.y: 20
*nnV_labModel.width: 290
*nnV_labModel.height: 20
*nnV_labModel.alignment: "alignment_center"

*nnV_sWin.class: scrolledWindow
*nnV_sWin.parent: nnValues
*nnV_sWin.static: true
*nnV_sWin.name: nnV_sWin
*nnV_sWin.scrollingPolicy: "application_defined"
*nnV_sWin.x: 20
*nnV_sWin.y: 50
*nnV_sWin.visualPolicy: "variable"
*nnV_sWin.scrollBarDisplayPolicy: "static"
*nnV_sWin.shadowThickness: 0
*nnV_sWin.height: 100
*nnV_sWin.width: 360

*nnV_sList.class: scrolledList
*nnV_sList.parent: nnV_sWin
*nnV_sList.static: true
*nnV_sList.name: nnV_sList
*nnV_sList.width: 360
*nnV_sList.height: 120
*nnV_sList.selectionPolicy: "browse_select"
*nnV_sList.browseSelectionCallback: {\
 XmListCallbackStruct *pA =\
(XmListCallbackStruct *)UxCallbackArg;\
 VAL_VAR *pval;\
 S_UNI_MIS *pum;\
 char *z;\
 Arg a[8];\
 Cardinal k, n;\
   iValue = pA->item_position -1;\
   pval = apvalV[iValue];\
   pum = nnVget_uni_mis( pval->ind_umis );\
   UxPutStrRes( nnV_labCodice, XmNlabelString, pum->codice);\
   textValue( pval->val);\
   for (k=0; k<N_TIPI_UMIS && *(z=pum->codm[k]) != ' '; k++)\
      axsOnomi[k] = XmStringCreateSimple( z);\
   axsOnomi[cOdata=k++] = XmStringCreateSimple( "(restore)");\
   XtDestroyWidget( nnV_rcOmenu );\
   n=0;\
   XtSetArg( a[n], XmNx, xOmenu); n++;\
   XtSetArg( a[n], XmNy, yOmenu); n++;\
   XtSetArg( a[n], XmNbuttonCount, k); n++;\
   XtSetArg( a[n], XmNbuttons, axsOnomi); n++;\
   XtSetArg( a[n], XmNbuttonType, axtOtipi); n++;\
   XtSetArg( a[n], XmNbuttonSet, pval->sel_umis); n++;\
   XtSetArg( a[n], XmNsimpleCallback, nnVsimpleCB); n++;\
   nnV_rcOmenu = XmCreateSimpleOptionMenu(\
    nnValues, szOmenu, a, n);\
   XtManageChild( nnV_rcOmenu );\
   while (k--)\
      XmStringFree( axsOnomi[k]);\
}
*nnV_sList.listSizePolicy: "resize_if_possible"
*nnV_sList.createCallback: {\
/* carica la ScrolledList delle Vars */\
 char ah[2+100+1], *z, b=' ';\
 int i, ivj;\
 XmString xs;\
   ah[1] = b;\
   ah[2+100] = '\0';\
   for (i=0; i<cValues; i++) {\
      ah[0] = (apval0[i]->noto) ? '*' : b;\
      ivj = aiVals[1+i];\
      z = (ivj>0) ? nom_sivar[ivj-1] : nom_vari[-ivj-1];\
      strncpy( ah+2, z, 100);\
      xs = XmStringCreateSimple( ah);\
      XmListAddItemUnselected( nnV_sList, xs, 0);\
      XmStringFree( xs);\
   }\
   XtVaSetValues( nnV_sList, XmNvisibleItemCount, cValues, NULL);\
\
}

*nnV_labCodice.class: label
*nnV_labCodice.parent: nnValues
*nnV_labCodice.static: true
*nnV_labCodice.name: nnV_labCodice
*nnV_labCodice.x: 40
*nnV_labCodice.y: 170
*nnV_labCodice.width: 100
*nnV_labCodice.height: 30

*nnV_pbOk.class: pushButton
*nnV_pbOk.parent: nnValues
*nnV_pbOk.static: true
*nnV_pbOk.name: nnV_pbOk
*nnV_pbOk.x: 40
*nnV_pbOk.y: 230
*nnV_pbOk.width: 80
*nnV_pbOk.height: 30
*nnV_pbOk.labelString: "Ok"
*nnV_pbOk.activateCallback.source: public
*nnV_pbOk.activateCallback: nnVokCB

*nnV_pbCancel.class: pushButton
*nnV_pbCancel.parent: nnValues
*nnV_pbCancel.static: true
*nnV_pbCancel.name: nnV_pbCancel
*nnV_pbCancel.x: 160
*nnV_pbCancel.y: 230
*nnV_pbCancel.width: 80
*nnV_pbCancel.height: 30
*nnV_pbCancel.labelString: "Cancel"
*nnV_pbCancel.activateCallback.source: public
*nnV_pbCancel.activateCallback: nnVcancelCB

*nnV_pbHelp.class: pushButton
*nnV_pbHelp.parent: nnValues
*nnV_pbHelp.static: true
*nnV_pbHelp.name: nnV_pbHelp
*nnV_pbHelp.x: 280
*nnV_pbHelp.y: 230
*nnV_pbHelp.width: 80
*nnV_pbHelp.height: 30
*nnV_pbHelp.labelString: "Help"
*nnV_pbHelp.activateCallback.source: public
*nnV_pbHelp.activateCallback: nnVhelpCB

*nnV_textValue.class: text
*nnV_textValue.parent: nnValues
*nnV_textValue.static: true
*nnV_textValue.name: nnV_textValue
*nnV_textValue.x: 150
*nnV_textValue.y: 170
*nnV_textValue.width: 100
*nnV_textValue.height: 30
*nnV_textValue.maxLength: NNV_LEN_VAL
*nnV_textValue.modifyVerifyCallback: {\
 XmTextVerifyPtr pA =\
(XmTextVerifyPtr) UxCallbackArg;\
 static char ahAbili[] = "0123456789+-.eE";\
 int i=0, l=pA->text->length;\
   while (i<l && strchr( ahAbili, pA->text->ptr[i]) )\
      i++;\
   while (i<l && pA->text->ptr[i]==' ' )\
      i++;\
   pA->doit = (i==l);\
}
*nnV_textValue.valueChangedCallback: {\
 XmAnyCallbackStruct *pA =\
(XmAnyCallbackStruct *) UxCallbackArg;\
 char *ahValue;\
 float val;\
   XtVaGetValues( UxWidget, XmNvalue, &ahValue, NULL);\
   if (sscanf( ahValue, "%f", &val) ) {\
      apvalV[iValue]->val = val;\
   } else {\
      textValue( apvalV[iValue]->val);\
   }\
   XtFree( ahValue);\
}

