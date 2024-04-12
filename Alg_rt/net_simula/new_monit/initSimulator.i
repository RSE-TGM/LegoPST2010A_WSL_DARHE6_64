! UIMX ascii 2.5 key: 1907                                                      

*initSimulator.class: form
*initSimulator.gbldecl: #include <stdio.h>\
#include <malloc.h>\
#include <X11/Intrinsic.h>\
\
#ifndef DESIGN_TIME\
extern int _MAX_SNAP_SHOT;\
extern int _MAX_BACK_TRACK;\
#include "init_sim.h"\
#include "backtrack.h"\
#include "bistrutt.h"\
#include "preview.h"\
/* #include "interf_attive.h"  */\
extern int init_ci_interface_active;\
extern int init_bt_interface_active;\
extern int bt_interface_active;\
#include "cursore.h"\
extern int inizializzazione;\
extern int backtrack_caricato;\
SNTAB *snap_list;\
BKTAB *bt_list;\
XtIntervalId timer_initci;\
XtIntervalId timer_initbt;\
int tasto_loadci_attivabile = False;\
int tasto_loadbt_attivabile = False;\
#endif
*initSimulator.ispecdecl: int item_select; /* elemento della lista selezionato */\

*initSimulator.ispeclist: item_select
*initSimulator.ispeclist.item_select: "int", "%item_select%"
*initSimulator.funcdecl: swidget create_initSimulator(padre_init, tipo)\
Widget padre_init;\
int tipo;
*initSimulator.funcname: create_initSimulator
*initSimulator.funcdef: "swidget", "<create_initSimulator>(%)"
*initSimulator.argdecl: Widget padre_init;\
int tipo;
*initSimulator.arglist: padre_init, tipo
*initSimulator.arglist.padre_init: "Widget", "%padre_init%"
*initSimulator.arglist.tipo: "int", "%tipo%"
*initSimulator.icode: #ifndef DESIGN_TIME\
set_cursor (padre_init,CLOCK);\
#endif
*initSimulator.fcode: #ifndef DESIGN_TIME\
XtAddEventHandler (UxGetWidget(scrollListaSnap), ButtonPressMask, False, \
                     Popup_Menu, listaSnapPopupMenu);\
/*\
 * per commutazione a backtrack e per snapshot\
 */\
snap_list = (SNTAB*)malloc(sizeof(SNTAB)*_MAX_SNAP_SHOT);\
read_lista_snap (snap_list);\
\
switch (tipo)\
   {\
   case INIT_FROM_CI:\
      init_ci_interface_active = 1; \
      initSimCi = rtrn;\
      XtVaSetValues (XtParent(UxGetWidget(rtrn)), \
         XmNtitle, "INIT CI", XmNiconName, "INIT CI", NULL);\
      display_lista_snap (UxGetWidget(scrollListaSnap), snap_list);\
      tasto_load_ci = initLoadpb;\
      tasto_loadci_attivabile = False;\
      attiva_timer_initSimci (initSimCi);\
      break;\
   case INIT_FROM_BT:\
      init_bt_interface_active = 1; \
      initSimBt = rtrn;\
      XtVaSetValues (XtParent(UxGetWidget(rtrn)), \
         XmNtitle, "INIT BT",XmNiconName, "INIT BT",NULL);\
      bt_list = (BKTAB*)malloc(sizeof(BKTAB)*_MAX_BACK_TRACK);\
      read_lista_bt (bt_list);\
      display_lista_bt (UxGetWidget(scrollListaSnap), bt_list);\
      tasto_load_bt = initLoadpb;\
      tasto_loadbt_attivabile = False;\
      attiva_timer_initSimbt (initSimBt);\
      break;	\
   }\
set_cursor(padre_init,NORMALE);\
#endif\
\
UxPopupInterface (rtrn, no_grab);\
return(rtrn);\
\
\

*initSimulator.auxdecl: int carica_lista_bt ()\
{\
#ifndef DESIGN_TIME\
      read_lista_bt (bt_list);\
      display_lista_bt (UxGetWidget(scrollListaSnap), bt_list);\
#endif\
      return (0);   \
}
*initSimulator.name.source: public
*initSimulator.static: false
*initSimulator.name: initSimulator
*initSimulator.parent: NO_PARENT
*initSimulator.defaultShell: topLevelShell
*initSimulator.resizePolicy: "resize_none"
*initSimulator.unitType: "pixels"
*initSimulator.x: 100
*initSimulator.y: 100
*initSimulator.width: 700
*initSimulator.height: 450
*initSimulator.defaultPosition: "false"

*form4.class: form
*form4.static: true
*form4.name: form4
*form4.parent: initSimulator
*form4.resizePolicy: "resize_none"
*form4.x: 5
*form4.y: 260
*form4.width: 855
*form4.height: 75
*form4.rightAttachment: "attach_form"
*form4.topAttachment: "attach_none"
*form4.leftAttachment: "attach_form"
*form4.bottomAttachment: "attach_form"

*frame3.class: frame
*frame3.static: true
*frame3.name: frame3
*frame3.parent: form4
*frame3.x: 5
*frame3.y: 340
*frame3.width: 765
*frame3.height: 80
*frame3.bottomAttachment: "attach_form"
*frame3.leftOffset: 0
*frame3.rightAttachment: "attach_form"
*frame3.leftAttachment: "attach_form"
*frame3.topAttachment: "attach_form"

*form3.class: form
*form3.static: true
*form3.name: form3
*form3.parent: frame3
*form3.resizePolicy: "resize_none"
*form3.x: 0
*form3.y: 0
*form3.width: 745
*form3.height: 75

*initLoadpb.class: pushButton
*initLoadpb.name.source: public
*initLoadpb.static: false
*initLoadpb.name: initLoadpb
*initLoadpb.parent: form3
*initLoadpb.x: 20
*initLoadpb.y: 15
*initLoadpb.width: 130
*initLoadpb.height: 45
*initLoadpb.labelString: "LOAD"
*initLoadpb.activateCallback: {\
#ifndef DESIGN_TIME \
switch (tipo)\
{\
   case INIT_FROM_CI:\
      printf ("load snap %d\n", item_select);\
      if (carica_ci ((Widget)UxClientData,item_select) == 0)\
         {\
         fprintf (stderr,"snapshot %d caricato\n",item_select);\
         inizializzazione = 1;\
         }\
      else\
         {\
         fprintf (stderr,"***snapshot %d non caricato\n",item_select);\
         }	\
      break;\
   case INIT_FROM_BT:\
      printf ("load bt %d\n", item_select);\
      if (init_from_bt ((Widget)UxClientData,\
                      punt_rec_backtrack[item_select]+1) == 0)\
         {\
         fprintf (stderr,"backtrack %d caricato\n",item_select);\
         inizializzazione = 1;\
         }\
      else\
         {\
         fprintf (stderr,"***backtrack %d non caricato\n",item_select);\
         }	      \
      break;\
   default:\
      printf ("non riconosciuta\n");\
      break;\
}\
#endif\
\
\
}
*initLoadpb.bottomAttachment: "attach_form"
*initLoadpb.bottomOffset: 15
*initLoadpb.rightAttachment: "attach_position"
*initLoadpb.rightPosition: 20
*initLoadpb.leftAttachment: "attach_form"
*initLoadpb.leftOffset: 20
*initLoadpb.topAttachment: "attach_form"
*initLoadpb.topOffset: 15
*initLoadpb.sensitive: "false"
*initLoadpb.activateCallbackClientData: initSimulator

*initQuitpb.class: pushButton
*initQuitpb.static: true
*initQuitpb.name: initQuitpb
*initQuitpb.parent: form3
*initQuitpb.x: 510
*initQuitpb.y: 15
*initQuitpb.width: 130
*initQuitpb.height: 45
*initQuitpb.labelString: "QUIT"
*initQuitpb.activateCallback: {\
printf ("fine colloquio initialization \n");\
#ifndef DESIGN_TIME\
if (tipo == INIT_FROM_CI)\
   {\
   init_ci_interface_active = 0;\
   UxDestroyInterface (initSimCi);\
   free (snap_list); \
   stop_timer (timer_initci); \
   }\
else if (tipo == INIT_FROM_BT)\
   {\
   init_bt_interface_active = 0;\
   UxDestroyInterface (initSimBt);\
   free (bt_list);\
   stop_timer (timer_initbt);\
   if (backtrack_caricato)  /* salvata la ci di ritorno */\
      if (!bt_interface_active) /* non esiste bt mngmt */\
         backtrack_caricato = 0;\
   }\
#endif\
}
*initQuitpb.bottomAttachment: "attach_form"
*initQuitpb.bottomOffset: 15
*initQuitpb.leftAttachment: "attach_position"
*initQuitpb.leftOffset: 0
*initQuitpb.rightAttachment: "attach_form"
*initQuitpb.rightOffset: 20
*initQuitpb.topAttachment: "attach_form"
*initQuitpb.topOffset: 15
*initQuitpb.rightPosition: 0
*initQuitpb.leftPosition: 80

*initViewpb.class: pushButton
*initViewpb.static: true
*initViewpb.name: initViewpb
*initViewpb.parent: form3
*initViewpb.x: 170
*initViewpb.y: 15
*initViewpb.width: 130
*initViewpb.height: 45
*initViewpb.labelString: "VIEW"
*initViewpb.activateCallback: {\
char testo[20];\
#ifndef DESIGN_TIME\
if (tipo == INIT_FROM_CI)\
   {    \
   printf ("preview ci %d\n",item_select);\
   sprintf (testo,"I.C. %d",item_select);\
   create_previewSnap(CI_VIEW,item_select,testo);\
   }\
else if (tipo == INIT_FROM_BT)\
   {\
   printf ("preview bt %d rec n. %d\n",\
      item_select,punt_rec_backtrack[item_select]+1);\
   sprintf (testo,"BT %d",item_select);\
   create_previewSnap(BT_VIEW,punt_rec_backtrack[item_select]+1,testo);\
   }\
#endif\
\
\
}
*initViewpb.sensitive: "false"
*initViewpb.bottomAttachment: "attach_form"
*initViewpb.bottomOffset: 15
*initViewpb.leftAttachment: "attach_widget"
*initViewpb.leftOffset: 20
*initViewpb.leftWidget: "initLoadpb"
*initViewpb.topAttachment: "attach_form"
*initViewpb.topOffset: 15
*initViewpb.rightAttachment: "attach_position"
*initViewpb.rightPosition: 40

*menu1.class: rowColumn
*menu1.static: true
*menu1.name: menu1
*menu1.parent: initSimulator
*menu1.rowColumnType: "menu_bar"
*menu1.rightAttachment: "attach_form"
*menu1.menuAccelerator: "<KeyUp>F10"
*menu1.leftAttachment: "attach_form"

*initMenu.class: rowColumn
*initMenu.static: true
*initMenu.name: initMenu
*initMenu.parent: menu1
*initMenu.rowColumnType: "menu_pulldown"

*initMenuExitpb.class: pushButton
*initMenuExitpb.static: true
*initMenuExitpb.name: initMenuExitpb
*initMenuExitpb.parent: initMenu
*initMenuExitpb.labelString: "Exit"
*initMenuExitpb.mnemonic: "E"
*initMenuExitpb.activateCallback: {\
printf ("fine colloquio init\n");\
#ifndef DESIGN_TIME\
if (tipo == INIT_FROM_CI)\
   {\
   init_ci_interface_active = 0;\
   UxDestroyInterface (initSimCi);\
   stop_timer (timer_initci); \
   }\
else if (tipo == INIT_FROM_BT)\
   {\
   init_bt_interface_active = 0;\
   UxDestroyInterface (initSimBt);\
   stop_timer (timer_initbt);\
   if (backtrack_caricato)  /* salvata la ci di ritorno */\
      if (!bt_interface_active) /* non esiste bt mngmt */\
         backtrack_caricato = 0;\
   }\
#endif\
}

*menu1_top_b2.class: cascadeButton
*menu1_top_b2.static: true
*menu1_top_b2.name: menu1_top_b2
*menu1_top_b2.parent: menu1
*menu1_top_b2.labelString: "File"
*menu1_top_b2.mnemonic: "F"
*menu1_top_b2.subMenuId: "initMenu"

*scrolledWindow3.class: scrolledWindow
*scrolledWindow3.static: true
*scrolledWindow3.name: scrolledWindow3
*scrolledWindow3.parent: initSimulator
*scrolledWindow3.scrollingPolicy: "application_defined"
*scrolledWindow3.x: 20
*scrolledWindow3.y: 105
*scrolledWindow3.visualPolicy: "variable"
*scrolledWindow3.scrollBarDisplayPolicy: "static"
*scrolledWindow3.shadowThickness: 0
*scrolledWindow3.rightAttachment: "attach_form"
*scrolledWindow3.rightOffset: 20
*scrolledWindow3.leftAttachment: "attach_form"
*scrolledWindow3.leftOffset: 20
*scrolledWindow3.bottomAttachment: "attach_widget"
*scrolledWindow3.bottomOffset: 20
*scrolledWindow3.bottomWidget: "form4"
*scrolledWindow3.height: 250
*scrolledWindow3.topAttachment: "attach_widget"
*scrolledWindow3.topOffset: 20
*scrolledWindow3.topWidget: "menu1"

*scrollListaSnap.class: scrolledList
*scrollListaSnap.static: true
*scrollListaSnap.name: scrollListaSnap
*scrollListaSnap.parent: scrolledWindow3
*scrollListaSnap.width: 660
*scrollListaSnap.height: 300
*scrollListaSnap.selectionPolicy: "single_select"
*scrollListaSnap.visibleItemCount: 15
*scrollListaSnap.singleSelectionCallback: {\
int n; \
XmListCallbackStruct *reason;\
reason = (XmListCallbackStruct *)UxCallbackArg;\
item_select = reason->item_position;\
\
printf ("lista: item_select = %d\n",item_select);\
\
#ifndef DESIGN_TIME\
\
switch (tipo)\
   {\
   case INIT_FROM_CI:\
      n = item_select - 1;\
      if ((snap_list+n)->stat == 1)   \
         {\
         XtVaSetValues (initViewpb, XmNsensitive, True, NULL);\
         XtVaSetValues (listaSnapPopupView,XmNsensitive, True, NULL); \
         tasto_loadci_attivabile = True;\
         }\
      else\
         {\
         XtVaSetValues (initViewpb, XmNsensitive, False, NULL);\
         XtVaSetValues (listaSnapPopupView,XmNsensitive, False, NULL);\
         tasto_loadci_attivabile = False;\
         }	\
      break;\
\
   case INIT_FROM_BT:\
      n = item_select;\
      if ((bt_list+punt_rec_backtrack[n])->stat == 1)\
         {\
         XtVaSetValues (initViewpb, XmNsensitive, True, NULL);\
         XtVaSetValues (listaSnapPopupView,XmNsensitive, True, NULL); \
         tasto_loadbt_attivabile = True;\
         }\
     else\
         {\
         XtVaSetValues (initViewpb, XmNsensitive, False, NULL);\
         XtVaSetValues (listaSnapPopupView,XmNsensitive, False, NULL);\
         tasto_loadbt_attivabile = False;\
         } \
      break;\
   }\
#endif\
}

*listaSnapPopupMenu.class: rowColumn
*listaSnapPopupMenu.static: true
*listaSnapPopupMenu.name: listaSnapPopupMenu
*listaSnapPopupMenu.parent: scrollListaSnap
*listaSnapPopupMenu.rowColumnType: "menu_popup"
*listaSnapPopupMenu.menuAccelerator: "Shift <KeyUp>F10"

*listaSnapPopupView.class: pushButton
*listaSnapPopupView.static: true
*listaSnapPopupView.name: listaSnapPopupView
*listaSnapPopupView.parent: listaSnapPopupMenu
*listaSnapPopupView.labelString: "View   "
*listaSnapPopupView.activateCallback: {\
char testo[20];\
#ifndef DESIGN_TIME\
if (tipo == INIT_FROM_CI)\
   {    \
   sprintf (testo,"I.C. %d",item_select);\
   create_previewSnap(CI_VIEW,item_select,testo);\
   }\
else if (tipo == INIT_FROM_BT)\
   {\
   sprintf (testo,"BT %d",item_select);\
   create_previewSnap(BT_VIEW,punt_rec_backtrack[item_select]+1,testo);\
   }\
#endif\
}
*listaSnapPopupView.sensitive: "false"

