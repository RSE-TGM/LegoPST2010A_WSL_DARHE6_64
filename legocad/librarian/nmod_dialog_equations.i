! UIMX ascii 2.0 key: 6949                                                      

*nmod_dialog_equations.class: dialogShell
*nmod_dialog_equations.parent: NO_PARENT
*nmod_dialog_equations.static: true
*nmod_dialog_equations.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo nmod_dialog_equations.i\
   tipo \
   release 2.23\
   data 5/9/95\
   reserved @(#)nmod_dialog_equations.i	2.23\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
\
/****************************************************************/\
/* INCLUDE FILES						*/\
/****************************************************************/\
\
#include <stdio.h>\
#include <string.h>\
#include <fcntl.h>\
#include <Xm/Xm.h>\
\
#include "definizioni.h"\
\
#ifndef LIBUTILX\
#include <libutilx.h>\
#define LIBUTILX\
#endif\
\
/****************************************************************/\
/* VARIABILI GLOBALI ESTERNE					*/\
/****************************************************************/\
\
extern Boolean non_salvato;\
\
extern Arg args[];\
extern Cardinal argcount;\
\
extern Boolean bool_dialog_equation;\
\
extern int num_var_stato,\
           num_var_algebriche,\
           num_var_ingresso,\
           num_dati_geometrici,\
           jac_rows,\
           jac_cols;\
\
extern StructVars *variabili;\
\
extern JacToggStruct jactoggstruct[100][300];\
\
extern swidget pb_nmod_varsetup, pb_nmod_JC;\
extern Boolean nmod_def_initialized;\
extern byte jacobian_type;\
\
extern char *names[];\
extern int num_colors;\
extern Pixel apix[];\
extern short color_values[];\
extern Colormap colormap;\
extern Display *display;\
extern Widget _nmod_varsetup;\
extern XmString cstring;\
\
/****************************************************************/\
/* VARIABILI GLOBALI						*/\
/****************************************************************/\
\
/* indica il numero di toggle settati a 'yes' e serve per dimensionare */\
/* alcuni array */\
int num_yes_toggle;\
\
char file_jac_temp[30];\
Boolean prima_volta_jac = True;
*nmod_dialog_equations.ispecdecl:
*nmod_dialog_equations.funcdecl: swidget create_dialog_equation()\

*nmod_dialog_equations.funcname: create_dialog_equation
*nmod_dialog_equations.funcdef: "swidget", "<create_dialog_equation>(%)"
*nmod_dialog_equations.icode: int i,j;\
\
/* Disabilita alcune voci di menu */\
set_something (UxGetWidget(pb_nmod_varsetup),XmNsensitive,False);\
if (nmod_def_initialized)\
   set_something (UxGetWidget(pb_nmod_JC),XmNsensitive,False);
*nmod_dialog_equations.fcode: /* Dimensionamenti Widgets */\
dimensiona_widgets();\
\
/* CREAZIONE WIDGETS JACOBIANO */\
for (i=0; i < jac_rows; i++ )\
{\
   for (j=0; j < jac_cols; j++ )\
      crea_jac_toggles (&jactoggstruct[i][j],\
                        (MARGIN+ WIDTH_JAC_TOGGLES)*j+MARGIN,\
                        (MARGIN+HEIGHT_JAC_TOGGLES)*i+MARGIN);\
\
  /* RIEMPIMENTO WINDOW NUMERO EQUAZIONI */\
   crea_jac_eq_labels (i,(MARGIN+HEIGHT_JAC_TOGGLES)*i+MARGIN);\
}\
\
/* RIEMPIMENTO WINDOW NOME VARIABILI */\
for (j=0; j < jac_cols; j++ )\
   crea_jac_var_labels (j,(MARGIN+WIDTH_JAC_TOGGLES)*j+MARGIN);\
\
if (prima_volta_jac)\
   prima_volta_jac = False;\
\
/* Assegnazione nome casuale al file tmp */\
tmpnam (file_jac_temp);\
\
/* Scrittura su file stati jacobiano */\
salva_jac();\
\
\
UxPopupInterface (rtrn, no_grab);\
bool_dialog_equation = False;\
\
/* GESTIONE CASSO-INTEGRATA DELLE SCROLLBAR DELL'INTERA WINDOW */\
scrolling_bird (UxGetWidget(scrollw_jac_equ),\
                UxGetWidget(scrollw_jac_var),\
                UxGetWidget(nmod_dialog2_scrollw3));\
\
return(rtrn);
*nmod_dialog_equations.auxdecl: /***************************************************************/\
/*** dimensiona_widgets()\
 ***\
 ***   Descrizione:\
 ***      Dimensiona alcuni widgets per l'allineamento della matrice jacobiana.\
 ***/\
dimensiona_widgets()\
{\
/* Dimensionamento tavola dei toggleButtons */\
   set_something (UxGetWidget(bboard_jac_toggles),\
                  XmNwidth, (MARGIN+WIDTH_JAC_TOGGLES)*jac_cols+MARGIN);\
   set_something (UxGetWidget(bboard_jac_toggles),\
                  XmNheight,(MARGIN+HEIGHT_JAC_TOGGLES)*jac_rows+MARGIN);\
\
/* Dimensionamento tavola delle labels  */\
   set_something (UxGetWidget(bboard_jac_equ),\
                  XmNheight,(MARGIN+HEIGHT_JAC_TOGGLES)*jac_rows+MARGIN);\
   set_something (UxGetWidget(bboard_jac_var),\
                  XmNwidth, (MARGIN+WIDTH_JAC_TOGGLES)*jac_cols+MARGIN);\
}\
\
/***************************************************************/\
/*** salva_jac()\
 ***\
 ***   Descrizione:\
 ***     Scrive in un file temp, in modalita' binaria, gli stati YES-NO\
 ***     dello jacobiano prima della visualizzazione della window.\
 ***     Gli stati possono essere cosi' recuperati se l'utente abbandona \
 ***     le eventuali modifiche.\
 ***/\
salva_jac()\
{\
   int i,j,fd;\
\
   if ( (fd = creat (file_jac_temp,0666)) == -1 )\
   {\
      printf ("Can't open temporary file for jacobian states storage. Sorry.\n");\
      return (-1);\
   }\
\
   for (i=0; i<jac_rows; i++)\
      for (j=0; j<jac_cols; j++)\
         write (fd, (char *)&jactoggstruct[i][j].jac_yes,sizeof(Boolean));\
\
   close (fd);\
   return (0);\
}\
\
/***************************************************************/\
/*** leggi_jac()\
 ***\
 ***   Descrizione:\
 ***      Legge da un file temp, in modalita' binaria, gli stati YES-NO\
 ***      dello jacobiano prima della visualizzazione della window.\
 ***/\
leggi_jac()\
{\
   int i,j,fd;\
\
   if ( (fd = open (file_jac_temp,O_RDONLY)) == -1 )\
   {\
      printf ("Can't open temporary file for jacobian states retrieve. Sorry.\n");\
      return (-1);\
   }\
\
   for (i=0; i<jac_rows; i++)\
      for (j=0; j<jac_cols; j++)\
         read (fd, (char *)&jactoggstruct[i][j].jac_yes, sizeof(Boolean));\
\
   close (fd);\
   return (0);\
}\
\
/***************************************************************/\
/*** crea_jac_toggles(jactructptr,posx, posy)\
 ***\
 ***   Descrizione:\
 ***     Utilita' per la creazione dei toggleButton dello jacobiano \
 ***     nella scrolled-window.\
 ***     N.B. Per volonta' del Divino Sylvan non si tratta piu' di toggleButtons\
 ***     bensi' di drawnButtons pieni e vuoti (bianchi e neri).\
 ***     Inizialmente sono tutti BLACK, cioe' settati a YES (=dipendenza).\
 ***/\
crea_jac_toggles(jacstructptr, posx, posy)\
JacToggStruct *jacstructptr;\
int posx, posy;\
{\
   Boolean set;\
   Pixel bg;\
\
   set = jacstructptr->jac_yes;\
   bg  = ((set) ? apix[BLACK] : apix[WHITE]);\
\
   argcount = 0;\
   XtSetArg(args[argcount], XmNx, posx); argcount++;\
   XtSetArg(args[argcount], XmNy, posy);  argcount++;\
   XtSetArg(args[argcount], XmNwidth,  WIDTH_JAC_TOGGLES);  argcount++;\
   XtSetArg(args[argcount], XmNheight, HEIGHT_JAC_TOGGLES); argcount++;\
   XtSetArg(args[argcount], XmNbackground, bg); argcount++;\
   XtSetArg(args[argcount], XmNrecomputeSize, False); argcount++;\
   jacstructptr->wdg = (Widget) XmCreateDrawnButton(UxGetWidget(bboard_jac_toggles), \
                                                    "NewmodToggle", args, argcount);\
\
   XtAddCallback (jacstructptr->wdg, XmNactivateCallback, jac_toggle_premuto, \
                  jacstructptr);\
\
   XtManageChild (jacstructptr->wdg);\
}\
\
/***************************************************************/\
/*** jac_toggle_premuto(w,jacstruct_ptr,reason)\
 ***\
 ***   Descrizione:\
 ***     Callback chiamata premendo un qualsiasi toggleButton dello jacobiano.\
 ***     Modifica la label e lo state del toggle premuto, aggiornando l'array\
 ***     degli stati della matrice.\
 ***     N.B. Trattasi di DrawnButton.\
 ***/\
void jac_toggle_premuto (w,jacstruct_ptr,reason)\
Widget w;\
JacToggStruct *jacstruct_ptr; \
XmDrawnButtonCallbackStruct *reason;\
{\
   Pixel bg;\
\
   get_something (w,XmNbackground,&bg);\
\
   if ( bg == apix[BLACK] )\
   {\
      num_yes_toggle--;\
      set_something (w,XmNbackground,apix[WHITE]);\
      jacstruct_ptr->jac_yes = False;\
   }\
   else\
   {\
      num_yes_toggle++;\
      set_something (w,XmNbackground,apix[BLACK]);\
      jacstruct_ptr->jac_yes = True;\
   }\
}\
\
/***************************************************************/\
/*** crea_jac_eq_labels(indice, posy)\
 ***    Parametri:\
 ***      int indice : numero equazione\
 ***      int posy : posizione y della label\
 ***\
 ***    Descrizione:\
 ***      Crea la label relativa al numero dell'equazione (intestazione righe\
 ***      matrice jacobiana).\
 ***/\
crea_jac_eq_labels(indice, posy)\
int indice;\
int posy;\
{\
   Widget wdg;\
   char *num_eq[5];\
\
   sprintf (num_eq,"%4d",indice+1);\
\
   cstring = CREATE_CSTRING(num_eq);\
   argcount = 0;\
   XtSetArg(args[argcount], XmNx, 0); argcount++;\
   XtSetArg(args[argcount], XmNy, posy);  argcount++;\
   XtSetArg(args[argcount], XmNheight, HEIGHT_JAC_TOGGLES); argcount++;\
   XtSetArg(args[argcount], XmNalignment, XmALIGNMENT_END); argcount++;\
   XtSetArg(args[argcount], XmNlabelString, cstring); argcount++;\
/* XtSetArg(args[argcount], XmNrecomputeSize, False); argcount++; */\
   XtSetArg(args[argcount], XmNmarginWidth, 0); argcount++;\
   wdg = XmCreateLabel(UxGetWidget(bboard_jac_equ), \
                               "NewmodJacLabel", args, argcount);\
   XmStringFree(cstring);\
\
   XtManageChild (wdg);\
}\
\
\
\
/***************************************************************/\
/*** crea_jac_var_labels(indice, posx)\
 ***    Parametri:\
 ***      int indice : indice nome variabile\
 ***      int posy : posizione y della label\
 ***\
 ***    Descrizione:\
 ***      Crea la label relativa al nome della variabile (intestazione colonne\
 ***      matrice jacobiana).\
 ***/\
crea_jac_var_labels(indice, posx)\
int indice;\
int posx;\
{\
   Widget    wdg;\
   XmString  cstring_var;\
\
   cstring_var = CREATE_CSTRING(variabili[indice].nome);\
\
   argcount = 0;\
   XtSetArg(args[argcount], XmNy, 0); argcount++;\
   XtSetArg(args[argcount], XmNx, posx);  argcount++;\
   XtSetArg(args[argcount], XmNwidth,  WIDTH_JAC_TOGGLES);  argcount++;\
   XtSetArg(args[argcount], XmNheight, HEIGHT_JAC_TOGGLES); argcount++;\
   XtSetArg(args[argcount], XmNalignment, XmALIGNMENT_CENTER); argcount++;\
   XtSetArg(args[argcount], XmNlabelString, cstring_var); argcount++;\
   XtSetArg(args[argcount], XmNrecomputeSize, False); argcount++;\
   wdg = XmCreateLabel(UxGetWidget(bboard_jac_var), \
                       "NewmodJacLabel", args, argcount);\
   XtManageChild (wdg);\
\
   XmStringFree (cstring_var);\
}\
\
/***************************************************************/\
/*** aggiorna_jac_var_labels()\
 ***\
 ***   Descrizione:  \
 ***      Aggiorna le labelStrings della matrice jacobiana se e' visualizzata.\
 ***/\
aggiorna_jac_var_labels()\
{\
   WidgetList wdg; /* Puntatore ad una lista di Widgets */\
   XmString cstring_var;\
   int indice;\
\
   get_something (UxGetWidget(bboard_jac_var), XmNchildren, &wdg);\
\
   for (indice=0; indice < jac_cols; indice++)\
   {\
      cstring_var = CREATE_CSTRING(variabili[indice].nome);\
\
      set_something (wdg[indice],XmNlabelString, cstring_var);\
      XmStringFree (cstring_var);\
   }\
}\
\
/***************************************************************/\
/*** scrolling_bird (sw_row,sw_col,sw_val)\
 ***    Parametri:\
 ***       Widget sw_row : scroll-list intestazione righe\
 ***       Widget sw_col : scroll-list intestazione colonne\
 ***       Widget sw_val : scroll-list matrice jacobiana\
 ***\
 ***    Descrizione:\
 ***       Funzione che gestisce lo scrolling unificato della matrice jacobiana.\
 ***/\
scrolling_bird (sw_row,sw_col,sw_val)\
Widget sw_row,sw_col,sw_val;\
{\
   Widget sbar_cols_hor,   sbar_cols_vert;    /* VARIABILI */\
   Widget sbar_rows_hor,   sbar_rows_vert;    /* EQUAZIONI */\
   Widget sbar_values_hor, sbar_values_vert;  /* MATRICE  */\
\
   get_something( sw_val, XmNverticalScrollBar,   &sbar_values_vert );\
   get_something( sw_val, XmNhorizontalScrollBar, &sbar_values_hor );\
\
   get_something( sw_row, XmNverticalScrollBar,   &sbar_rows_vert );\
   get_something( sw_row, XmNhorizontalScrollBar, &sbar_rows_hor );\
\
   get_something( sw_col, XmNverticalScrollBar,   &sbar_cols_vert );\
   get_something( sw_col, XmNhorizontalScrollBar, &sbar_cols_hor );\
\
/* Aggiunta callback scrollBar verticali */\
   XtAddCallback(sbar_values_vert, XmNincrementCallback, increment,\
                 sbar_rows_vert);\
   XtAddCallback(sbar_values_vert, XmNdecrementCallback, increment,\
                 sbar_rows_vert);\
   XtAddCallback(sbar_values_vert, XmNdragCallback, increment,\
                 sbar_rows_vert);\
   XtAddCallback(sbar_values_vert, XmNpageIncrementCallback, increment,\
                 sbar_rows_vert);\
   XtAddCallback(sbar_values_vert, XmNpageDecrementCallback, increment,\
                 sbar_rows_vert);\
\
/* Aggiunta callback scrollBar orizzontali */\
   XtAddCallback(sbar_values_hor, XmNincrementCallback, increment,\
                 sbar_cols_hor);\
   XtAddCallback(sbar_values_hor, XmNdecrementCallback, increment,\
                 sbar_cols_hor);\
   XtAddCallback(sbar_values_hor, XmNdragCallback, increment,\
                 sbar_cols_hor);\
   XtAddCallback(sbar_values_hor, XmNpageIncrementCallback, increment,\
                 sbar_cols_hor);\
   XtAddCallback(sbar_values_hor, XmNpageDecrementCallback, increment,\
                 sbar_cols_hor);\
\
/* Smappazzamento scrollBar */\
   XtUnmapWidget( sbar_cols_hor );\
   XtUnmapWidget( sbar_cols_vert );\
   XtUnmapWidget( sbar_rows_hor );\
   XtUnmapWidget( sbar_rows_vert );\
}\
\
/***************************************************************/\
/*** void increment(w, dato, list_info)\
 ***\
 ***   Descrizione:\
 ***      Gestisce la callback delle scrollbar della scroll-list della \
 ***      matrice jacobiana (muove anche le scroll-list di intestazione). \
 ***/\
void increment(w, dato, list_info)\
Widget w;\
Widget dato;\
XmScrollBarCallbackStruct *list_info;\
{\
    static int i=0;\
\
    if ( !i )\
    {\
       i++;\
       XtCallCallbacks(dato, XmNincrementCallback, list_info);\
       i = 0;\
    }\
    else\
    {\
       i = 0;\
       return;\
    }\
}\
\
/*-----------------------------------------------------------------------*/\
/*** void get_pixel(names,apix,count)\
 ***   Parametri:\
 ***     char *names: stringhe contenenti i nomi dei colori\
 ***     Pixel *apix: array per ospitare i valori di pixel (?)\
 ***     int count: contatore ENEL\
 ***\
 ***   Descrizione: \
 ***     Funzione che recupera i valori RGB dei nomi dei colori specificati. \
 ***/\
void get_pixel(names,apix,count)\
char *names[];\
Pixel *apix;\
int count;\
{\
   XColor defc;\
   int i;\
\
   for (i=0 ; i < count ; i++ )\
   {\
      if ( !XParseColor( display, colormap, names[i], &defc  ))\
         fprintf(stderr,"il colore %s non esiste nel database.\n",names[i]);\
      else\
         if ( !XAllocColor( display, colormap, &defc))\
            fprintf(stderr,"non e' possibile allocare il colore %s.\n",\
                    names[i]);\
         else\
            apix[i] = defc.pixel;\
   }\
}\
\
\
/*** chiudi_dialog_equation()\
 ***\
 ***   Descrizione:\
 ***     chiude la window di settaggio dello jacobiano\
 ***     (viene chiamato quando si preme OK o CANCEL) ***/\
chiudi_dialog_equation()\
{\
   UxDestroySwidget(nmod_dialog_equations);\
   bool_dialog_equation = True;\
   if ( unlink(file_jac_temp) )\
      printf ("Can't delete jacobian temporary file. Failure.\n");\
\
   set_something (UxGetWidget(pb_nmod_varsetup),XmNsensitive,True);\
   if (nmod_def_initialized && jacobian_type == ANALYTICAL)\
      set_something (UxGetWidget(pb_nmod_JC),XmNsensitive,True);\
}
*nmod_dialog_equations.name: nmod_dialog_equations
*nmod_dialog_equations.x: 820
*nmod_dialog_equations.y: 110
*nmod_dialog_equations.width: 80
*nmod_dialog_equations.height: 60
*nmod_dialog_equations.title: "NEWMOD - JACOBIAN MATRIX TOPOLOGY"
*nmod_dialog_equations.geometry: "+785+450"

*nmod_dialog2_form1.class: form
*nmod_dialog2_form1.parent: nmod_dialog_equations
*nmod_dialog2_form1.static: true
*nmod_dialog2_form1.name: nmod_dialog2_form1
*nmod_dialog2_form1.unitType: "pixels"
*nmod_dialog2_form1.x: 201
*nmod_dialog2_form1.y: 386
*nmod_dialog2_form1.width: 600
*nmod_dialog2_form1.height: 430
*nmod_dialog2_form1.autoUnmanage: "false"

*nmod_dialog2_ok.class: pushButton
*nmod_dialog2_ok.parent: nmod_dialog2_form1
*nmod_dialog2_ok.static: true
*nmod_dialog2_ok.name: nmod_dialog2_ok
*nmod_dialog2_ok.x: 10
*nmod_dialog2_ok.y: 510
*nmod_dialog2_ok.width: 100
*nmod_dialog2_ok.height: 30
*nmod_dialog2_ok.bottomAttachment: "attach_form"
*nmod_dialog2_ok.bottomOffset: 20
*nmod_dialog2_ok.leftAttachment: "attach_form"
*nmod_dialog2_ok.leftOffset: 20
*nmod_dialog2_ok.topAttachment: "attach_none"
*nmod_dialog2_ok.topOffset: 0
*nmod_dialog2_ok.labelString: "Ok"
*nmod_dialog2_ok.activateCallback: {\
salva_jac();  /* salva la situazione attuale. */\
\
non_salvato = True; \
\
chiudi_dialog_equation();\
}

*nmod_dialog2_sep1.class: separatorGadget
*nmod_dialog2_sep1.parent: nmod_dialog2_form1
*nmod_dialog2_sep1.static: true
*nmod_dialog2_sep1.name: nmod_dialog2_sep1
*nmod_dialog2_sep1.x: 10
*nmod_dialog2_sep1.y: 470
*nmod_dialog2_sep1.width: 660
*nmod_dialog2_sep1.height: 10
*nmod_dialog2_sep1.leftAttachment: "attach_form"
*nmod_dialog2_sep1.leftOffset: 10
*nmod_dialog2_sep1.rightAttachment: "attach_form"
*nmod_dialog2_sep1.rightOffset: 10
*nmod_dialog2_sep1.topAttachment: "attach_none"
*nmod_dialog2_sep1.topOffset: 0
*nmod_dialog2_sep1.topWidget: ""
*nmod_dialog2_sep1.bottomAttachment: "attach_widget"
*nmod_dialog2_sep1.bottomOffset: 20
*nmod_dialog2_sep1.bottomWidget: "nmod_dialog2_ok"

*labelGadget6.class: labelGadget
*labelGadget6.parent: nmod_dialog2_form1
*labelGadget6.static: true
*labelGadget6.name: labelGadget6
*labelGadget6.x: 90
*labelGadget6.y: 0
*labelGadget6.width: 200
*labelGadget6.height: 20
*labelGadget6.bottomAttachment: "attach_none"
*labelGadget6.bottomOffset: 0
*labelGadget6.rightAttachment: "attach_none"
*labelGadget6.rightOffset: 0
*labelGadget6.topAttachment: "attach_form"
*labelGadget6.topOffset: 15
*labelGadget6.alignment: "alignment_beginning"
*labelGadget6.labelString: "Variables"

*scrollw_jac_var.class: scrolledWindow
*scrollw_jac_var.parent: nmod_dialog2_form1
*scrollw_jac_var.static: true
*scrollw_jac_var.name: scrollw_jac_var
*scrollw_jac_var.scrollingPolicy: "automatic"
*scrollw_jac_var.unitType: "pixels"
*scrollw_jac_var.x: 100
*scrollw_jac_var.y: 30
*scrollw_jac_var.width: 290
*scrollw_jac_var.height: 60
*scrollw_jac_var.bottomAttachment: "attach_none"
*scrollw_jac_var.bottomOffset: 0
*scrollw_jac_var.leftAttachment: "attach_form"
*scrollw_jac_var.leftOffset: 80
*scrollw_jac_var.leftWidget: ""
*scrollw_jac_var.rightAttachment: "attach_form"
*scrollw_jac_var.rightOffset: 10
*scrollw_jac_var.topAttachment: "attach_widget"
*scrollw_jac_var.topOffset: 5
*scrollw_jac_var.topWidget: "labelGadget6"
*scrollw_jac_var.visualPolicy: "constant"
*scrollw_jac_var.scrollBarDisplayPolicy: "static"

*bboard_jac_var.class: bulletinBoard
*bboard_jac_var.parent: scrollw_jac_var
*bboard_jac_var.static: true
*bboard_jac_var.name: bboard_jac_var
*bboard_jac_var.resizePolicy: "resize_none"
*bboard_jac_var.unitType: "pixels"
*bboard_jac_var.x: -2
*bboard_jac_var.y: 8
*bboard_jac_var.width: 280
*bboard_jac_var.height: 30
*bboard_jac_var.noResize: "true"
*bboard_jac_var.marginHeight: 0
*bboard_jac_var.marginWidth: 0

*scrollw_jac_equ.class: scrolledWindow
*scrollw_jac_equ.parent: nmod_dialog2_form1
*scrollw_jac_equ.static: true
*scrollw_jac_equ.name: scrollw_jac_equ
*scrollw_jac_equ.scrollingPolicy: "automatic"
*scrollw_jac_equ.unitType: "pixels"
*scrollw_jac_equ.x: 70
*scrollw_jac_equ.y: 180
*scrollw_jac_equ.width: 60
*scrollw_jac_equ.height: 230
*scrollw_jac_equ.scrollBarDisplayPolicy: "as_needed"
*scrollw_jac_equ.visualPolicy: "variable"
*scrollw_jac_equ.scrolledWindowMarginHeight: 0
*scrollw_jac_equ.scrolledWindowMarginWidth: 0
*scrollw_jac_equ.shadowThickness: 2
*scrollw_jac_equ.bottomAttachment: "attach_widget"
*scrollw_jac_equ.bottomOffset: 5
*scrollw_jac_equ.leftAttachment: "attach_form"
*scrollw_jac_equ.leftOffset: 20
*scrollw_jac_equ.rightAttachment: "attach_none"
*scrollw_jac_equ.rightOffset: 0
*scrollw_jac_equ.bottomWidget: "nmod_dialog2_sep1"
*scrollw_jac_equ.topAttachment: "attach_form"
*scrollw_jac_equ.topOffset: 100
*scrollw_jac_equ.topWidget: ""

*bboard_jac_equ.class: bulletinBoard
*bboard_jac_equ.parent: scrollw_jac_equ
*bboard_jac_equ.static: true
*bboard_jac_equ.name: bboard_jac_equ
*bboard_jac_equ.resizePolicy: "resize_none"
*bboard_jac_equ.unitType: "pixels"
*bboard_jac_equ.x: -2
*bboard_jac_equ.y: -2
*bboard_jac_equ.width: 320
*bboard_jac_equ.height: 240
*bboard_jac_equ.noResize: "true"
*bboard_jac_equ.marginHeight: 0
*bboard_jac_equ.marginWidth: 0

*labelGadget8.class: labelGadget
*labelGadget8.parent: nmod_dialog2_form1
*labelGadget8.static: true
*labelGadget8.name: labelGadget8
*labelGadget8.x: 10
*labelGadget8.y: 40
*labelGadget8.width: 80
*labelGadget8.height: 20
*labelGadget8.alignment: "alignment_beginning"
*labelGadget8.labelString: "Equations"
*labelGadget8.leftAttachment: "attach_form"
*labelGadget8.leftOffset: 5
*labelGadget8.rightAttachment: "attach_none"
*labelGadget8.rightOffset: 0
*labelGadget8.topAttachment: "attach_none"
*labelGadget8.topOffset: 0
*labelGadget8.bottomAttachment: "attach_widget"
*labelGadget8.bottomOffset: 5
*labelGadget8.bottomWidget: "scrollw_jac_equ"

*nmod_dialog2_scrollw3.class: scrolledWindow
*nmod_dialog2_scrollw3.parent: nmod_dialog2_form1
*nmod_dialog2_scrollw3.static: true
*nmod_dialog2_scrollw3.name: nmod_dialog2_scrollw3
*nmod_dialog2_scrollw3.scrollingPolicy: "automatic"
*nmod_dialog2_scrollw3.unitType: "pixels"
*nmod_dialog2_scrollw3.x: 70
*nmod_dialog2_scrollw3.y: 180
*nmod_dialog2_scrollw3.width: 560
*nmod_dialog2_scrollw3.height: 230
*nmod_dialog2_scrollw3.bottomAttachment: "attach_widget"
*nmod_dialog2_scrollw3.bottomOffset: 5
*nmod_dialog2_scrollw3.bottomWidget: "nmod_dialog2_sep1"
*nmod_dialog2_scrollw3.rightAttachment: "attach_form"
*nmod_dialog2_scrollw3.rightOffset: 10
*nmod_dialog2_scrollw3.scrollBarDisplayPolicy: "static"
*nmod_dialog2_scrollw3.visualPolicy: "constant"
*nmod_dialog2_scrollw3.scrolledWindowMarginHeight: 0
*nmod_dialog2_scrollw3.scrolledWindowMarginWidth: 0
*nmod_dialog2_scrollw3.shadowThickness: 2
*nmod_dialog2_scrollw3.leftAttachment: "attach_form"
*nmod_dialog2_scrollw3.leftOffset: 80
*nmod_dialog2_scrollw3.leftWidget: "scrollw_jac_equ"
*nmod_dialog2_scrollw3.topAttachment: "attach_form"
*nmod_dialog2_scrollw3.topOffset: 100
*nmod_dialog2_scrollw3.topWidget: ""

*bboard_jac_toggles.class: bulletinBoard
*bboard_jac_toggles.parent: nmod_dialog2_scrollw3
*bboard_jac_toggles.static: true
*bboard_jac_toggles.name: bboard_jac_toggles
*bboard_jac_toggles.resizePolicy: "resize_none"
*bboard_jac_toggles.unitType: "pixels"
*bboard_jac_toggles.x: -2
*bboard_jac_toggles.y: -2
*bboard_jac_toggles.width: 320
*bboard_jac_toggles.height: 240
*bboard_jac_toggles.noResize: "true"

*nmod_dialog2_cancel.class: pushButton
*nmod_dialog2_cancel.parent: nmod_dialog2_form1
*nmod_dialog2_cancel.static: true
*nmod_dialog2_cancel.name: nmod_dialog2_cancel
*nmod_dialog2_cancel.x: 130
*nmod_dialog2_cancel.y: 510
*nmod_dialog2_cancel.width: 100
*nmod_dialog2_cancel.height: 30
*nmod_dialog2_cancel.bottomAttachment: "attach_form"
*nmod_dialog2_cancel.bottomOffset: 20
*nmod_dialog2_cancel.topAttachment: "attach_none"
*nmod_dialog2_cancel.topOffset: 0
*nmod_dialog2_cancel.labelString: "Cancel"
*nmod_dialog2_cancel.activateCallback: {\
leggi_jac();\
\
chiudi_dialog_equation();\
}
*nmod_dialog2_cancel.rightAttachment: "attach_none"
*nmod_dialog2_cancel.rightOffset: 0

*label1.class: label
*label1.parent: nmod_dialog2_form1
*label1.static: true
*label1.name: label1
*label1.x: 520
*label1.y: 380
*label1.width: 50
*label1.height: 30
*label1.background: "white"
*label1.bottomAttachment: "attach_form"
*label1.bottomOffset: 20
*label1.foreground: "black"
*label1.labelString: "No"
*label1.leftAttachment: "attach_none"
*label1.leftOffset: 0
*label1.recomputeSize: "false"
*label1.rightAttachment: "attach_form"
*label1.rightOffset: 10
*label1.topAttachment: "attach_none"
*label1.topOffset: 0
*label1.borderWidth: 1
*label1.resizable: "false"

*label2.class: label
*label2.parent: nmod_dialog2_form1
*label2.static: true
*label2.name: label2
*label2.x: 440
*label2.y: 380
*label2.width: 50
*label2.height: 30
*label2.background: "black"
*label2.bottomAttachment: "attach_form"
*label2.bottomOffset: 20
*label2.foreground: "white"
*label2.labelString: "Yes"
*label2.leftAttachment: "attach_none"
*label2.leftOffset: 0
*label2.recomputeSize: "false"
*label2.resizable: "false"
*label2.rightAttachment: "attach_widget"
*label2.rightOffset: 15
*label2.rightWidget: "label1"
*label2.topAttachment: "attach_none"
*label2.topOffset: 0
*label2.borderWidth: 1

