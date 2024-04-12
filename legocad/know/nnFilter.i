! UIMX ascii 2.0 key: 3059                                                      

*nnFilter.class: bulletinBoardDialog
*nnFilter.parent: NO_PARENT
*nnFilter.parentExpression: nnF_parent
*nnFilter.defaultShell: topLevelShell
*nnFilter.static: true
*nnFilter.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo nnFilter.i\
   tipo \
   release 1.13\
   data 11/13/95\
   reserved @(#)nnFilter.i	1.13\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
\
#include <stdio.h>\
/* nnFilter.c       (ancillare di nnEdit.c)\
* Scopo:       filtra variabili per nnEdit.\
* Dati:        da files 'f03.dat', assunti precaricati.\
* Risultati:   se Ok, elenco variabili selezionate.\
* Note:        si auto-distrugge all'uscita.\
* Autore:      C.Lusso (CISE) 1994\
*/\
\
\
#include <Xm/RowColumn.h>\
#include "f03.h"\
#include "libutilx.h"\
#include "helpkit.h"\
\
/* dati globali: - */\
#define NNF_TEXT_MAXLEN 20\
static String\
 nnFzHpage = "nnFilter";\
static Find_struct\
 fsFindBloc;\
/* funzione in "nnEdit.c" */\
extern void fnnF_ritorna_E( int *);\
\
/* dati di istanza:\
Widget\
 nnF_help;      pagina privata di Aiuto (bozza)\
int\
 cVars,         conta variabili totali (=neqsis+nu)\
 cSelVars,      conta variabili selezionate\
 cSelOut,       conta out-var selezionate\
 cSelInp;       conta inp-var selezionate\
Boolean\
 oTextChg,      spia se testo del Filtro cambia\
 *abSelVars;    elenco [cVars] spie variabili selezionate\
char\
 *phFilter;     punta testo del Filtro\
*/
*nnFilter.ispecdecl: Widget\
 wgtFindBloc,\
 nnF_help;\
int\
 cVars,\
 cSelVars,\
 cSelOut,\
 cSelInp;\
Boolean\
 oTextChg,\
 *abSelVars;\
char\
 *phFilter;\

*nnFilter.ispeclist: wgtFindBloc, nnF_help, cVars, cSelVars, cSelOut, cSelInp, oTextChg, abSelVars, phFilter
*nnFilter.ispeclist.wgtFindBloc: "Widget", "%wgtFindBloc%"
*nnFilter.ispeclist.nnF_help: "Widget", "%nnF_help%"
*nnFilter.ispeclist.cVars: "int", "%cVars%"
*nnFilter.ispeclist.cSelVars: "int", "%cSelVars%"
*nnFilter.ispeclist.cSelOut: "int", "%cSelOut%"
*nnFilter.ispeclist.cSelInp: "int", "%cSelInp%"
*nnFilter.ispeclist.oTextChg: "Boolean", "%oTextChg%"
*nnFilter.ispeclist.abSelVars: "Boolean", "*%abSelVars%"
*nnFilter.ispeclist.phFilter: "unsigned char", "*%phFilter%"
*nnFilter.funcdecl: swidget create_nnFilter( Widget nnF_parent,\
 String nnFzHfile )\

*nnFilter.funcname: create_nnFilter
*nnFilter.funcdef: "swidget", "<create_nnFilter>(%)"
*nnFilter.argdecl: Widget nnF_parent;\
String nnFzHfile;
*nnFilter.arglist: nnF_parent, nnFzHfile
*nnFilter.arglist.nnF_parent: "Widget", "%nnF_parent%"
*nnFilter.arglist.nnFzHfile: "String", "%nnFzHfile%"
*nnFilter.icode: /* codice iniziale: */\
cVars = neqsis+nu;\
cSelVars = cSelOut = cSelInp = 0;\
abSelVars = (Boolean *) XtMalloc( sizeof(Boolean) * cVars);\
phFilter = NULL;\

*nnFilter.fcode: /* codice finale: */\
XtManageChild( rtrn);\
nnF_help = helpkit_propInfo( rtrn, nnFzHfile, nnFzHpage);\
{\
 char z[24];\
   sprintf( z, "Model name: %.8s", sigla);\
   UxPutStrRes( nnF_labCaso, XmNlabelString, z);\
}\
{ /* a[10] per find_kit() della libreria libutilx... */\
 Arg al[10];\
 Cardinal n=0;\
   XtSetArg( al[n], XmNx, 20); n++;\
   XtSetArg( al[n], XmNy, 250); n++;\
   wgtFindBloc = find_kit( nnFilter, al, n, &fsFindBloc );\
   fsFindBloc.ID_lista = (Widget) nnF_slistBloc;\
}\
\
XmTextSetMaxLength( nnF_textFilter, NNF_TEXT_MAXLEN);\
XmTextSetString( nnF_textFilter, "*");\
mostra_selMod();\
mostra_selBloc();\
XtSetSensitive( nnF_slistVars, False);\
mostra_selVars();\
\
return(rtrn);\

*nnFilter.auxdecl: /* codice ausiliario: */\
static void mostra_selMod( void);\
static void mostra_selBloc( void);\
static void mostra_selVars( void);\
static XtCallbackProc\
 nnFslistBlocSelelectionCB(),\
 nnFcancelCB(),\
 nnFhelpCB();\
\
/* -------------------------------- */\
static void mostra_selMod( void)\
{\
 char z[40];\
 int c;\
   get_something( nnF_slistMod, XmNselectedItemCount, &c);\
   sprintf( z, "modules %d, selected %d", nst, c);\
   UxPutStrRes( nnF_labMod, XmNlabelString, z);\
}\
\
/* -------------------------------- */\
static void mostra_selBloc( void)\
{\
 char z[40];\
 int c;\
   get_something( nnF_slistBloc, XmNselectedItemCount, &c);\
   sprintf( z, "blocks %d, selected %d", nbl, c);\
   UxPutStrRes( nnF_labBloc, XmNlabelString, z);\
}\
\
/* -------------------------------- */\
static void mostra_selVars( void)\
{\
 char z[50];\
   sprintf( z, "vars %d, selected %d (= %d + %d)",\
    cVars, cSelVars, cSelOut, cSelInp);\
   UxPutStrRes( nnF_labVars, XmNlabelString, z);\
}\
\
/* -------------------------------- */\
static XtCallbackProc nnFslistBlocSelelectionCB(\
 Widget w,\
 XtPointer pC,\
 XmListCallbackStruct *pA)\
{\
   mostra_selBloc();\
}\
\
/* ------------------ */\
static XtCallbackProc nnFcancelCB(\
 Widget w,\
 XtPointer pC,\
 XmPushButtonCallbackStruct *pA)\
{\
   XtFree( abSelVars);\
   XtFree( phFilter);\
   UxDestroyInterface( nnFilter );\
}\
\
/* ------------------ */\
static XtCallbackProc nnFhelpCB(\
 Widget w,\
 XtPointer pC,\
 XmAnyCallbackStruct *pA)\
{\
   XtManageChild( nnF_help );\
}\
\
/* codice ausiliario: fine. */
*nnFilter.name: nnFilter
*nnFilter.unitType: "pixels"
*nnFilter.x: 255
*nnFilter.y: 23
*nnFilter.width: 500
*nnFilter.height: 600
*nnFilter.autoUnmanage: "false"
*nnFilter.dialogStyle: "dialog_primary_application_modal"
*nnFilter.noResize: "true"
*nnFilter.helpCallback.source: public
*nnFilter.helpCallback: nnFhelpCB
*nnFilter.unmapCallback.source: public
*nnFilter.unmapCallback: nnFcancelCB
*nnFilter.resizePolicy: "resize_none"

*nnF_labCaso.class: label
*nnF_labCaso.parent: nnFilter
*nnF_labCaso.static: true
*nnF_labCaso.name: nnF_labCaso
*nnF_labCaso.x: 10
*nnF_labCaso.y: 10
*nnF_labCaso.width: 380
*nnF_labCaso.height: 20
*nnF_labCaso.alignment: "alignment_center"

*nnF_labMod.class: label
*nnF_labMod.parent: nnFilter
*nnF_labMod.static: true
*nnF_labMod.name: nnF_labMod
*nnF_labMod.x: 20
*nnF_labMod.y: 40
*nnF_labMod.width: 150
*nnF_labMod.height: 20
*nnF_labMod.alignment: "alignment_beginning"

*nnF_swinMod.class: scrolledWindow
*nnF_swinMod.parent: nnFilter
*nnF_swinMod.static: true
*nnF_swinMod.name: nnF_swinMod
*nnF_swinMod.x: 20
*nnF_swinMod.y: 60
*nnF_swinMod.height: 180
*nnF_swinMod.width: 70
*nnF_swinMod.scrollBarDisplayPolicy: "static"
*nnF_swinMod.scrollingPolicy: "application_defined"
*nnF_swinMod.shadowThickness: 0
*nnF_swinMod.visualPolicy: "variable"

*nnF_slistMod.class: scrolledList
*nnF_slistMod.parent: nnF_swinMod
*nnF_slistMod.static: true
*nnF_slistMod.name: nnF_slistMod
*nnF_slistMod.selectionPolicy: "multiple_select"
*nnF_slistMod.createCallback: {\
/* carica la ScrolledList dei Moduli */\
 Boolean *ab;\
 char zM[4+1];\
 XmString xs;\
 int i, iM;\
   ab = (Boolean *) XtMalloc( sizeof(Boolean) * nst);\
   for (iM=0; iM<nst; iM++)\
      ab[iM] = False;\
   zM[4] = '\0';\
   for (i=0; i<nbl; i++) {\
      iM = islb[i];\
      if (ab[ iM -1 ])\
         continue;\
      strncpy( zM, nosub[i], 4);\
      xs = XmStringCreateSimple( zM);\
      XmListAddItemUnselected( nnF_slistMod, xs, iM);\
      XmStringFree( xs);\
      ab[ iM -1 ] = True;\
   }\
   XtFree( ab);\
   xs = XmStringCreateSimple( "(all)");\
   XmListAddItemUnselected( nnF_slistMod, xs, 0);\
   XmStringFree( xs);\
   xs = XmStringCreateSimple( "(none)");\
   XmListAddItemUnselected( nnF_slistMod, xs, 0);\
   XmStringFree( xs);\
   set_something( nnF_slistMod, XmNvisibleItemCount, nst+2);\
}
*nnF_slistMod.multipleSelectionCallback: {\
/* gestisce selezioni della ScrolledList dei Moduli */\
 XmListCallbackStruct *pA =\
(XmListCallbackStruct *) UxCallbackArg;\
 int ip=pA->item_position;\
   if (ip > nst) {\
      XmListDeselectAllItems( nnF_slistMod);\
      if (ip == nst+1) {\
         int i=0;\
         while (i++ < nst)\
            XmListSelectPos( nnF_slistMod, i, False);\
      }\
   }\
   mostra_selMod();\
}
*nnF_slistMod.height: 120
*nnF_slistMod.width: 90
*nnF_slistMod.listSizePolicy: "resize_if_possible"

*nnF_aroBloc.class: arrowButton
*nnF_aroBloc.parent: nnFilter
*nnF_aroBloc.static: true
*nnF_aroBloc.name: nnF_aroBloc
*nnF_aroBloc.x: 100
*nnF_aroBloc.y: 110
*nnF_aroBloc.width: 30
*nnF_aroBloc.height: 70
*nnF_aroBloc.arrowDirection: "arrow_right"
*nnF_aroBloc.activateCallback: {\
/* dai Moduli selezionati, seleziona Blocchi */\
 int *ai, c, ia, i;\
   XmListDeselectAllItems( nnF_slistBloc);\
   if (XmListGetSelectedPos( nnF_slistMod, &ai, &c)) {\
      for (ia=0; ia<c; ia++)\
         for (i=0; i<nbl; i++)\
            if (islb[i] == ai[ia])\
               XmListSelectPos( nnF_slistBloc, i+1, False);\
      XtFree( ai);\
   }\
   mostra_selBloc();\
}

*nnF_labBloc.class: label
*nnF_labBloc.parent: nnFilter
*nnF_labBloc.static: true
*nnF_labBloc.name: nnF_labBloc
*nnF_labBloc.x: 180
*nnF_labBloc.y: 40
*nnF_labBloc.width: 200
*nnF_labBloc.height: 20
*nnF_labBloc.alignment: "alignment_center"

*nnF_swinBloc.class: scrolledWindow
*nnF_swinBloc.parent: nnFilter
*nnF_swinBloc.static: true
*nnF_swinBloc.name: nnF_swinBloc
*nnF_swinBloc.x: 140
*nnF_swinBloc.y: 60
*nnF_swinBloc.width: 340
*nnF_swinBloc.height: 180
*nnF_swinBloc.scrollBarDisplayPolicy: "static"
*nnF_swinBloc.scrollingPolicy: "application_defined"
*nnF_swinBloc.shadowThickness: 0
*nnF_swinBloc.visualPolicy: "variable"

*nnF_slistBloc.class: scrolledList
*nnF_slistBloc.parent: nnF_swinBloc
*nnF_slistBloc.static: true
*nnF_slistBloc.name: nnF_slistBloc
*nnF_slistBloc.selectionPolicy: "multiple_select"
*nnF_slistBloc.createCallback: {\
/* carica la ScrolledList dei Blocchi */\
 XmString xs;\
 char zB[80+1];\
 int i;\
   zB[80] = '\0';\
   for (i=0; i<nbl; i++) {\
      strncpy( zB, nom_bloc[i], 80);\
      xs = XmStringCreateSimple( zB);\
      XmListAddItemUnselected( nnF_slistBloc, xs, i+1);\
      XmStringFree( xs);\
   }\
   set_something( nnF_slistBloc, XmNvisibleItemCount, nbl);\
}
*nnF_slistBloc.height: 140
*nnF_slistBloc.width: 340
*nnF_slistBloc.listSizePolicy: "resize_if_possible"
*nnF_slistBloc.multipleSelectionCallback.source: public
*nnF_slistBloc.multipleSelectionCallback: nnFslistBlocSelelectionCB

*nnF_aroVars.class: arrowButton
*nnF_aroVars.parent: nnFilter
*nnF_aroVars.static: true
*nnF_aroVars.name: nnF_aroVars
*nnF_aroVars.x: 220
*nnF_aroVars.y: 300
*nnF_aroVars.width: 70
*nnF_aroVars.height: 30
*nnF_aroVars.arrowDirection: "arrow_down"
*nnF_aroVars.activateCallback: {\
/* dai Blocchi selezionati, seleziona Variabili:\
 * (1) delimita le parole-chiave nel Filtro;\
 * (2) costruisce nuovo elenco di variabili\
 */\
 int *ai, c, i, ibloc, j, ivj, iz, k;\
 Boolean bOk;\
 char *ph, *pV, ahV[100+1];\
 XmString xs;\
 static int chFilter, czFilter, al[NNF_TEXT_MAXLEN/2];\
 static char *azFilter[NNF_TEXT_MAXLEN/2];\
   if (oTextChg) {\
      XtFree( phFilter);\
      ph = phFilter = XmTextGetString( nnF_textFilter);\
      czFilter = 0;\
      do {\
         while (*ph && isspace(*ph))\
            ph++;\
         if (*ph)\
            azFilter[czFilter++] = ph;\
         else\
            break;\
         while (*ph && !isspace(*ph))\
            ph++;\
         if (*ph)\
            *ph++ = '\0';\
         else\
            break;\
      } while (*ph);\
      for (iz=0; iz<czFilter; iz++)\
         if ((al[iz]=strlen(azFilter[iz])) > 4)\
            azFilter[iz][al[iz]=4] = '\0';\
   }\
   XmListDeleteAllItems( nnF_slistVars);\
   for (i=0; i<cVars; i++)\
      abSelVars[i] = False;\
   cSelVars = cSelOut = cSelInp = 0;\
   ahV[100] = '\0';\
   if (XmListGetSelectedPos( nnF_slistBloc, &ai, &c)) {\
      UxPutStrRes( nnF_labVars, XmNlabelString, "Processing...");\
      XmUpdateDisplay( nnF_labVars);\
      for (i=0; i<c; i++) {\
         ibloc = ai[i] -1;\
         for (j=ip[ibloc]-1; j<ip[ibloc+1]-1; j++) {\
            ivj = ((ivj = ipvrs[j]) > 0) ? ivj : (neqsis -ivj);\
            if (abSelVars[ivj-1])\
               continue;\
            pV = (ivj<=neqsis) ? sivar[ivj-1] : vari[ivj-neqsis-1];\
            for (iz=0, bOk=False; iz<czFilter && !bOk; iz++)\
               for (k=0; k<al[iz]; k++) {\
                  if (bOk = azFilter[iz][k] == '*')\
                     break;\
                  if (bOk = azFilter[iz][k] == '?')\
                     continue;\
                  if (bOk = pV[k] == azFilter[iz][k])\
                     continue;\
                  else\
                     break;\
               }\
            if (!bOk)\
               continue;\
            abSelVars[ivj-1] = True;\
            cSelVars++;\
            if (ivj<=neqsis)\
              cSelOut++;\
            else\
              cSelInp++;\
         }\
      }\
      XtFree( ai);\
      for (i=0; i<cVars; i++) {\
         if (!abSelVars[i])\
            continue;\
         pV = (i<neqsis) ? nom_sivar[i] : nom_vari[i-neqsis];\
         strncpy( ahV, pV, 100);\
         xs = XmStringCreateSimple( ahV);\
         XmListAddItemUnselected( nnF_slistVars, xs, 0);\
         XmStringFree( xs);\
      }\
      set_something( nnF_slistVars,\
       XmNvisibleItemCount, (cSelVars) ? cSelVars : 1);\
   }\
   mostra_selVars();\
}

*nnF_sep.class: separator
*nnF_sep.parent: nnFilter
*nnF_sep.static: true
*nnF_sep.name: nnF_sep
*nnF_sep.x: 20
*nnF_sep.y: 300
*nnF_sep.width: 460
*nnF_sep.height: 10

*nnF_labFilter.class: label
*nnF_labFilter.parent: nnFilter
*nnF_labFilter.static: true
*nnF_labFilter.name: nnF_labFilter
*nnF_labFilter.x: 20
*nnF_labFilter.y: 340
*nnF_labFilter.width: 120
*nnF_labFilter.height: 30
*nnF_labFilter.labelString: "Vars Filter:"

*nnF_textFilter.class: text
*nnF_textFilter.parent: nnFilter
*nnF_textFilter.static: true
*nnF_textFilter.name: nnF_textFilter
*nnF_textFilter.x: 140
*nnF_textFilter.y: 340
*nnF_textFilter.width: 260
*nnF_textFilter.height: 30
*nnF_textFilter.modifyVerifyCallback: {\
/* traduce in maiuscolo i caratteri immessi */\
 XmTextVerifyCallbackStruct *pA =\
(XmTextVerifyCallbackStruct *) UxCallbackArg;\
 char *ph;\
 int i;\
   for (i=0, ph=pA->text->ptr; i<pA->text->length; i++, ph++)\
      if (islower(*ph))\
         *ph = toupper( *ph);\
   oTextChg = True;\
}
*nnF_textFilter.editMode: "single_line_edit"

*nnF_labVars.class: label
*nnF_labVars.parent: nnFilter
*nnF_labVars.static: true
*nnF_labVars.name: nnF_labVars
*nnF_labVars.x: 20
*nnF_labVars.y: 370
*nnF_labVars.width: 460
*nnF_labVars.height: 20

*nnF_swinVars.class: scrolledWindow
*nnF_swinVars.parent: nnFilter
*nnF_swinVars.static: true
*nnF_swinVars.name: nnF_swinVars
*nnF_swinVars.x: 20
*nnF_swinVars.y: 390
*nnF_swinVars.width: 460
*nnF_swinVars.height: 120
*nnF_swinVars.scrollingPolicy: "application_defined"
*nnF_swinVars.scrollBarDisplayPolicy: "static"
*nnF_swinVars.shadowThickness: 0
*nnF_swinVars.visualPolicy: "variable"

*nnF_slistVars.class: scrolledList
*nnF_slistVars.parent: nnF_swinVars
*nnF_slistVars.static: true
*nnF_slistVars.name: nnF_slistVars
*nnF_slistVars.listSizePolicy: "resize_if_possible"
*nnF_slistVars.height: 120
*nnF_slistVars.width: 410
*nnF_slistVars.sensitive: "false"

*nnF_pbOk.class: pushButton
*nnF_pbOk.parent: nnFilter
*nnF_pbOk.static: true
*nnF_pbOk.name: nnF_pbOk
*nnF_pbOk.x: 40
*nnF_pbOk.y: 540
*nnF_pbOk.width: 80
*nnF_pbOk.height: 30
*nnF_pbOk.labelString: "Ok"
*nnF_pbOk.activateCallback: {\
/* ritorna le variabili selezionate */\
 int *aiReturn, i, k;\
   if (cSelVars) {\
      aiReturn = (int *) XtMalloc( sizeof(int) * (2+cSelVars));\
      for (i=0, k=2; i<cVars; i++)\
         if (abSelVars[i])\
            aiReturn[k++] = i+1;\
      aiReturn[0] = cSelOut;\
      aiReturn[1] = cSelInp;\
   } else\
      aiReturn = NULL;\
   fnnF_ritorna_E( aiReturn);\
   XtFree( aiReturn);\
   nnFcancelCB( 0, 0, 0);\
}

*nnF_pbCancel.class: pushButton
*nnF_pbCancel.parent: nnFilter
*nnF_pbCancel.static: true
*nnF_pbCancel.name: nnF_pbCancel
*nnF_pbCancel.x: 210
*nnF_pbCancel.y: 540
*nnF_pbCancel.width: 80
*nnF_pbCancel.height: 30
*nnF_pbCancel.labelString: "Cancel"
*nnF_pbCancel.activateCallback.source: public
*nnF_pbCancel.activateCallback: nnFcancelCB

*nnF_pbHelp.class: pushButton
*nnF_pbHelp.parent: nnFilter
*nnF_pbHelp.static: true
*nnF_pbHelp.name: nnF_pbHelp
*nnF_pbHelp.x: 380
*nnF_pbHelp.y: 540
*nnF_pbHelp.width: 80
*nnF_pbHelp.height: 30
*nnF_pbHelp.labelString: "Help"
*nnF_pbHelp.activateCallback.source: public
*nnF_pbHelp.activateCallback: nnFhelpCB

