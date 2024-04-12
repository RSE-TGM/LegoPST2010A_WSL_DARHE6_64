! UIMX ascii 2.0 key: 2947                                                      

*topVarWin1.class: mainWindow
*topVarWin1.parent: NO_PARENT
*topVarWin1.defaultShell: topLevelShell
*topVarWin1.static: true
*topVarWin1.gbldecl: /*\
   modulo topVarWin1.i\
   tipo \
   release 1.25\
   data 2/5/96\
   reserved @(#)topVarWin1.i	1.25\
*/\
/*\
        Variabile per identificazione della versione\
*/\
#ifndef DESIGN_TIME\
#endif\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "lg1_topsim.h"\
#include "varwin.h"\
#include "filtri.h"\
\
extern SIMULATORE *simulatore;\
VAR_SEL  move_var;\
GOST_WIN gost_win_par;\
int      gost_win_drag_on;\
\
static int    highlight_on=False;\
static Widget highlight_wid, del_wid;\
\
extern GC gost_win_gc;\
extern swidget create_msgToUser();
*topVarWin1.ispecdecl: VAR_SEL sel_var;\
int filtro_attivo;\
FILTRI *filtro_attuale;\
int blocco;\
MODELLO *locmod;\
int indice_modello;\
int indice_blocco;\
int indice_variabile;\
Boolean show_on;
*topVarWin1.ispeclist: sel_var, filtro_attivo, filtro_attuale, blocco, locmod, indice_modello, indice_blocco, indice_variabile, show_on
*topVarWin1.ispeclist.sel_var: "VAR_SEL", "%sel_var%"
*topVarWin1.ispeclist.filtro_attivo: "int", "%filtro_attivo%"
*topVarWin1.ispeclist.filtro_attuale: "FILTRI", "*%filtro_attuale%"
*topVarWin1.ispeclist.blocco: "int", "%blocco%"
*topVarWin1.ispeclist.locmod: "MODELLO", "*%locmod%"
*topVarWin1.ispeclist.indice_modello: "int", "%indice_modello%"
*topVarWin1.ispeclist.indice_blocco: "int", "%indice_blocco%"
*topVarWin1.ispeclist.indice_variabile: "int", "%indice_variabile%"
*topVarWin1.ispeclist.show_on: "Boolean", "%show_on%"
*topVarWin1.funcdecl: swidget create_topVarWin1(MODELLO *qtask,int ind_modello,int ind_blocco)\

*topVarWin1.funcname: create_topVarWin1
*topVarWin1.funcdef: "swidget", "<create_topVarWin1>(%)"
*topVarWin1.argdecl: MODELLO *qtask;\
int ind_modello;\
int ind_blocco;
*topVarWin1.arglist: qtask, ind_modello, ind_blocco
*topVarWin1.arglist.qtask: "MODELLO", "*%qtask%"
*topVarWin1.arglist.ind_modello: "int", "%ind_modello%"
*topVarWin1.arglist.ind_blocco: "int", "%ind_blocco%"
*topVarWin1.icode: Cardinal nargs;\
Arg args[10];\
\
if( qtask == NULL)\
   return(NULL);\
\
indice_modello = ind_modello;\
blocco = ind_blocco;\
move_var.status = sel_var.status = NON_SELEZIONATO;\
gost_win_par.primo = True;\
\
filtro_attivo = False;\
\
locmod = qtask;\
\
show_on = False;\
printf("create BLOCCO =%d\n",blocco);\

*topVarWin1.fcode: filtro_attivo = False;\
nargs=0;\
                \
XtSetArg( args[nargs], XmNkeyboardFocusPolicy, XmPOINTER );nargs++;                \
XtSetValues( XtParent(UxGetWidget(rtrn)), args, nargs );\
\
set_title(qtask->blocchi[ind_blocco]);\
\
add_var_list_event_handler(ingSW1);\
add_var_list_event_handler(uscSW1);\
\
add_variables(qtask->blocchi[ind_blocco]);\
\
return(rtrn);\

*topVarWin1.auxdecl: void var_press();\
int var_release();\
int show_all_conn();\
int no_show_all_connections();\
int show_connections();\
int no_show_connections(); \
\
\
\
/*-------------------------------------------\
 *\
 * cancella tutte le connessioni di un blocco\
 *\
 *-------------------------------------------*/ \
\
int block_delete_all_connections(BLOCCO bloc)\
{\
   extern Boolean simulator_changed;\
   CONNMODEL *conn,*prec,*conn_ext;\
   int i,j;   \
   int var_int,mod_ext,bl_ext,var_ext;\
\
\
   conn = bloc.var_conn_task;\
\
   /* scorro tutte le connessioni di questo blocco  */\
   while( conn != NULL)\
   {\
\
      /*\
          per ogni connessione che trovo annullo la connessione\
          nel blocco associato \
      */    \
      var_int = conn->var_interna;\
      mod_ext = conn->modello_esterno;\
      bl_ext  = conn->blocco_esterno;\
      var_ext = conn->var_esterna;  \
\
      /* cerco la variabile connessa */\
      conn_ext = simulatore->modelli[ mod_ext ]->blocchi[ bl_ext ].var_conn_task;\
      prec = NULL;\
      while( conn_ext != NULL )\
      {\
\
         if( conn_ext->var_esterna == var_int )\
         {\
            /* ho trovato la connessione corrispondente da eliminare */\
            if( prec == NULL)\
               simulatore->modelli[ mod_ext ]->blocchi[ bl_ext ].var_conn_task = conn_ext->succ;\
            else\
               prec->succ =  conn_ext->succ;        \
\
            /* decremento le connessioni della variabile */\
\
            if(simulatore->modelli[ mod_ext ]->blocchi[ bl_ext ].variabili[ var_ext].model_conn)\
               simulatore->modelli[ mod_ext ]->blocchi[ bl_ext ].variabili[ var_ext].model_conn--;\
\
         }  \
         prec = conn_ext;\
         conn_ext = conn_ext->succ;\
\
         simulator_changed = TRUE;\
\
      } /* end while */\
     \
      conn = conn->succ;\
   } /* end while */\
}\
 \
/*-------------------------------------------\
 *\
 * cancella tutte le connessioni di una task\
 *\
 *-------------------------------------------*/ \
\
int task_delete_all_connections(MODELLO *task)\
{\
   int i,j;\
\
\
   for(i=0;i<task->num_blocchi;i++)\
   {\
      block_delete_all_connections( task->blocchi[i] );\
      task->blocchi[i].var_conn_task=NULL;\
\
      for(j=0;j< task->blocchi[i].num_variabili; j++)\
         task->blocchi[i].variabili[j].model_conn = 0; \
   }\
\
}\
\
\
/*-----------------------------------------\
 *\
 * cancella le connessioni nella varWin\
 * connessa\
 * \
 ---------------------------------------*/ \
\
int cancella_var_conn(Widget wtop,CONNMODEL *connext)\
{\
   extern void getSecVarWin();\
   Widget otherVarWin;\
   char *salva_context1,*salva_context2;\
   CONNMODEL *local_conn,*prec;\
   VAR local_var;\
   int i,j,k;\
   Widget *wids,*wch;\
   int numing,numusc;\
   Arg arg[3];\
   Cardinal narg;\
   int tot,ning,nusc,irc;\
   int blocco_vis;\
   blocco_vis = False;\
\
/* recupero lo id della altra varWin visualizzata */\
   getSecVarWin(wtop,&otherVarWin);\
\
   if( otherVarWin != NULL )\
   {\
       /* setto il context dell'altra varWin */\
       set_var_win_list_context(otherVarWin,&salva_context1);\
\
        /* verifico che sia relativa al blocco che contiene la connessione\
           corrispondente */\
       if( connext->blocco_esterno == blocco)\
          blocco_vis = True;\
\
       if( blocco_vis )\
       {\
          /* caso di connessione su ingresso */\
          if(locmod->blocchi[connext->blocco_esterno].variabili[connext->var_esterna].tipo == INGRESSO )\
          {\
             /* recupero gli id dei frame degli ingressi\
               ( i quali a loro volta contengono un row_col )\
             */\
             get_something(ingList1,XmNchildren,&wids);\
\
             /* per determinare quale frame contiene la connessione applico\
                la formula\
                   irc =  nvaring - ( numtotvariabili - ind_variabile )\
\
               questa vale sempre nella ipotesi che la varWin sia\
               costruita a partire dalla lista della uscite\
               quindi la prima uscita ha come indice variabile 0\
             */\
\
             /* ricavo il numero di uscite */\
             for(i=0,nusc=0;\
                 i<locmod->blocchi[connext->blocco_esterno].num_variabili;i++)\
                if( locmod->blocchi[connext->blocco_esterno].variabili[i].tipo != INGRESSO )\
                   nusc++;\
\
             tot = locmod->blocchi[connext->blocco_esterno].num_variabili;\
             ning = tot - nusc;\
             irc =  ning - (tot- connext->var_esterna);\
\
             /* recupero i row_col */\
             get_something(wids[irc],XmNchildren,&wch);\
\
             /* recupero ciascuna label interna all'item */\
             get_something(wch[0],XmNchildren,&wids);\
\
         } /* enf if == INGRESSO */\
         else\
         {\
\
             /* recupero gli id dei frame degli ingressi\
               ( i quali a loro volta contengono un row_col )\
             */\
             get_something(uscList1,XmNchildren,&wids);\
\
             /* recupero il row_col */\
             get_something(wids[connext->var_esterna],XmNchildren,&wch);\
\
             /* recupero ciascuna label interna all'item */\
             get_something(wch[0],XmNchildren,&wids);\
         }\
\
       } /* end if == blocco */\
    } /* endif otherVarWin != NULL */\
\
/* elimino la connessione */\
    local_conn = simulatore->modelli[connext->modello_esterno]->blocchi[connext->blocco_esterno].var_conn_task;\
    prec = NULL;\
\
    /* cerco tale connessione */\
    while( local_conn != NULL)\
    {\
       if( local_conn->var_interna == connext->var_esterna )\
       {\
          if(local_conn->var_esterna == connext->var_interna  )\
          {\
             /* ho trovato la connessione */\
\
             /* elimino (ma non libero) la connessione */\
             if( prec == NULL)\
               simulatore->modelli[connext->modello_esterno]->blocchi[connext->blocco_esterno].var_conn_task = local_conn->succ;\
             else\
               prec->succ = local_conn->succ;\
\
             /* decremento le connessioni della variabile*/\
             simulatore->modelli[connext->modello_esterno]->blocchi[connext->blocco_esterno].variabili[connext->var_esterna].model_conn--;\
\
          }\
       }\
       prec = local_conn;\
       local_conn = local_conn->succ;\
    } /* end while */\
\
    if( blocco_vis )\
    {\
        /* se era la unica connessione elimino anche il pixmap */\
        if( simulatore->modelli[connext->modello_esterno]->blocchi[connext->blocco_esterno].variabili[connext->var_esterna].model_conn < 1 )\
            set_var_pixmap(wids[1],"void.bmp");\
\
        /*devo eliminare l'item della connessione */\
        no_show_connections(wch[0]);\
        show_connections(connext->var_esterna ,wch[0]);\
    }\
\
    reset_var_win_list_context(salva_context1);\
}\
\
\
\
\
/* \
   delete_connection\
   cancella la connessione selezionata.\
   Nella var_press e var_release vengono assegnati gli opportuni\
   valori ai dati nella struttura SEL_VAR, e in questa routine\
   vengono utilizzati.    \
*/\
int delete_connection( Widget widctx )\
{\
   extern Boolean simulator_changed;\
   int i;\
   CONNMODEL *conn,*prec;\
   char *salva_context;\
\
   set_var_win_list_context( widctx, &salva_context);\
\
\
   if( sel_var.status == SELEZIONATO )\
   {\
\
/* se e' stata selezionata una connessione */\
\
      if( sel_var.conn )\
      {\
\
          conn = locmod->blocchi[indice_blocco].var_conn_task;\
          prec = NULL;\
\
          /* cerco tale connessione */\
          i=0;\
          while( conn != NULL)\
          {\
             if( conn->var_interna == indice_variabile )\
             {\
                if( i == (sel_var.conn-1) )\
                {\
                   /* ho trovato la connessione */\
 \
                       \
                   no_show_connections(XtParent(sel_var.wid));      \
\
\
                    /* devo aggiornare anche la variabile connessa*/\
\
\
                    cancella_var_conn( topVarWin1, conn );\
\
\
                   /* elimino (ma non libero) la connessione */ \
                   if( prec == NULL)\
                      locmod->blocchi[indice_blocco].var_conn_task = conn->succ;\
                   else\
                      prec->succ = conn->succ;           \
                     \
                    /* decremento le connessioni della variabile*/\
                    locmod->blocchi[indice_blocco].variabili[indice_variabile].model_conn--;\
\
                    show_connections( indice_variabile,  XtParent(sel_var.wid));\
\
                    /* se era la unica connessione elimino anche il pixmap */\
                    if(!locmod->blocchi[indice_blocco].variabili[indice_variabile].model_conn) \
                        set_var_pixmap(sel_var.wid,"void.bmp");\
         \
                    simulator_changed = TRUE;\
               }\
               i++;\
            }\
            prec = conn; \
            conn = conn->succ;\
         } /*end while */ \
      }\
   }\
\
   reset_var_win_list_context(salva_context);\
}\
\
\
/*---\
\
   distrugge lo widget interno all'item della lista \
   dove si trova la label che descrive la connessione\
   Ricordati la struttura di ciascun item! \
\
   rowcol  \
   pixmap1  pixmap2  label1(variabile)\
      label2(variabile connessa dell'altro modello)\
\
---*/\
\
no_show_connections(Widget var_wid)\
{\
   Arg arg[5];\
   Cardinal narg;\
   int i, num;\
   Widget *wids;\
      \
\
/* recupero tutti gli widget interni ad un item della lista\
   con indice 0 c'e' il pixmap connessione interna del modello\
   con indice 1 c'e' il pixmap connessione con altro modello\
   con indice 2 c'e' la label della variabile\
   con indice 3 c'e' la label della variabile connessa \
*/   \
   narg=0;\
   XtSetArg( arg[narg], XmNnumChildren, &num );narg++;\
   XtSetArg( arg[narg], XmNchildren, &wids );narg++;\
   XtGetValues( var_wid, arg, narg );\
\
/* distruggo tutti gli widget interni ad un item con indice\
   uguale o maggiore a 3.\
*/\
    \
   for ( i=3; i<num; i++ )\
   {\
      if ( sel_var.status == SELEZIONATO && sel_var.wid == wids[i] )\
        sel_var.status = NON_SELEZIONATO;\
\
      XtDestroyWidget( wids[i] );\
   }    \
}\
\
/*\
 elimina la visualizzazione di tutte le connessioni\
*/\
no_show_all_connections()\
{\
   Arg arg[10];\
   Cardinal num,nc;\
   Widget *wids,*rc;\
   int i,ind_wid;\
\
   show_on = False;\
\
/* recupero tutti gli item della lista di ingresso\
*/\
   num=0;\
   XtSetArg( arg[num], XmNchildren, &wids );num++;\
   XtGetValues( UxGetWidget(ingList1), arg, num );\
\
   for(i=ind_wid=0;i<locmod->blocchi[blocco].num_variabili;i++)\
   {\
      if( locmod->blocchi[blocco].variabili[i].tipo == USCITA ||\
          locmod->blocchi[blocco].variabili[i].tipo == STATO )\
          continue;\
\
/* se questa veriabile e' connessa con un altro modello \
   elimino la visualizzazione della connessione\
*/\
      if( locmod->blocchi[blocco].variabili[i].model_conn )\
      {\
          num=0;\
          XtSetArg( arg[num], XmNchildren, &rc );num++;\
          XtGetValues( wids[ind_wid], arg, num );\
          no_show_connections(rc[0]);\
          ind_wid++;\
      }      \
      else\
          ind_wid++;\
      \
   }\
\
/* eseguo la stessa cosa per la lista di uscita \
*/\
   num=0;\
   XtSetArg( arg[num], XmNchildren, &wids );num++;\
   XtGetValues( UxGetWidget(uscList1), arg, num );\
\
   for(i=ind_wid=0;i<locmod->blocchi[blocco].num_variabili;i++)\
   {\
      if( locmod->blocchi[blocco].variabili[i].tipo == INGRESSO)\
         break;\
\
\
      if( locmod->blocchi[blocco].variabili[i].model_conn )\
      {\
          num=0;\
          XtSetArg( arg[num], XmNchildren, &rc );num++;\
          XtGetValues( wids[ind_wid], arg, num );\
          no_show_connections(rc[0]);\
          ind_wid++;\
      }      \
      else\
          ind_wid++;\
   }\
}\
\
/*\
   visualizza tutte le connessioni di una variabile\
   del blocco \
*/\
\
show_connections( int variabile, Widget var_wid)\
{\
   swidget lb;\
   Widget  wid;\
   CONNMODEL  *conn;\
   int     count;\
   Position swap;\
   Dimension he;\
   char    str[200];\
   BLOCCO *bloc;\
\
\
   bloc = locmod->blocchi;\
\
/* creo tante label quante sono le connessioni di \
   questa variabile\
*/\
\
   for ( conn=bloc[blocco].var_conn_task, count=0;\
         count<bloc[blocco].variabili[variabile].model_conn;\
         conn = conn->succ )\
      if ( conn->var_interna == variabile )\
      {\
         lb = UxCreateLabel( "var_lb_conn",\
                             UxWidgetToSwidget(var_wid) );\
        UxPutBackground( lb, UxGetBackground(var_wid) );\
        UxPutForeground( lb, UxGetForeground(var_wid) );\
        wid = UxCreateWidget( lb );\
\
#ifndef DESIGN_TIME\
        UxPutContext(wid, (char *) UxTopVarWin1Context );\
#endif\
\
       sprintf( str, "%s     %s  %s",\
             simulatore->modelli[conn->modello_esterno]->nome,\
             simulatore->modelli[conn->modello_esterno]->blocchi[conn->blocco_esterno].variabili[conn->var_esterna].nome,\
             simulatore->modelli[conn->modello_esterno]->blocchi[conn->blocco_esterno].variabili[conn->var_esterna].descr );\
\
        UxPutLabelString( lb, str );\
        UxPutBackground( lb, UxGetBackground(var_wid) );\
        UxPutForeground( lb, UxGetForeground(var_wid) );\
\
\
        XtAddEventHandler( wid, ButtonPressMask | OwnerGrabButtonMask, False,\
                           var_press, (XtPointer)variabile );\
        XtAddEventHandler( wid, ButtonReleaseMask, False,\
                           var_release, (XtPointer)variabile );\
/**\
        XtAddEventHandler( wid, EnterWindowMask, False, var_enter, NULL );\
        XtAddEventHandler( wid, LeaveWindowMask, False, var_leave, NULL );\
        XtAddEventHandler( wid, ButtonReleaseMask, False,\
                           var_release, (XtPointer)variabile );\
***/\
        if (!count)\
        {\
           get_something(lb,XmNy,&swap);\
           get_something(lb,XmNheight,&he);\
        }\
\
        swap += he;\
        set_something(lb,XmNy,swap);\
\
        count++;\
      }\
      \
}\
\
\
/* \
   visualizze tutte le connessioni di tutte le variabili di un blocco\
*/\
\
show_all_conn()\
{\
   Arg arg[10];\
   Cardinal num,nc;\
   Widget *wids,*rc;\
   int i,ind_wid;\
\
\
   show_on = True;\
\
/* visualizzo tutte le connessioni della lista di ingresso */\
\
   num=0;\
   XtSetArg( arg[num], XmNchildren, &wids );num++;\
   XtGetValues( UxGetWidget(ingList1), arg, num );\
\
\
   for(i=ind_wid=0;i<locmod->blocchi[blocco].num_variabili;i++)\
   {\
      if( locmod->blocchi[blocco].variabili[i].tipo == USCITA ||\
          locmod->blocchi[blocco].variabili[i].tipo == STATO )\
          continue;\
\
      if( locmod->blocchi[blocco].variabili[i].model_conn )\
      {\
          num=0;\
          XtSetArg( arg[num], XmNchildren, &rc );num++;\
          XtGetValues( wids[ind_wid], arg, num );\
          show_connections(i,rc[0]);\
          ind_wid++;\
      }      \
      else\
          ind_wid++;\
   }\
\
/* visualizzo le connessioni di tutte le variabili di uscita */ \
   num=0;\
   XtSetArg( arg[num], XmNchildren, &wids );num++;\
   XtGetValues( UxGetWidget(uscList1), arg, num );\
\
   for(i=ind_wid=0;i<locmod->blocchi[blocco].num_variabili;i++)\
   {\
\
\
/* esco dal ciclo se ho trovato una variabile di uscita.\
   Questo perche' al momento della creazione della lista \
   creo prima quelle di uscita e dopo quelle di ingresso\
   e gli indici seguono quindi questa disposizione\
*/\
      if( locmod->blocchi[blocco].variabili[i].tipo == INGRESSO )\
          break;\
\
      if( locmod->blocchi[blocco].variabili[i].model_conn )\
      {\
          num=0;\
          XtSetArg( arg[num], XmNchildren, &rc );num++;\
          XtGetValues( wids[ind_wid], arg, num );\
          show_connections(i,rc[0]);\
          ind_wid++;\
      }      \
      else\
          ind_wid++;\
   }\
\
}\
\
\
/*\
 * inverti_colori()\
 *\
 * Inverte il background ed il foreground del widget argomento.\
 */\
inverti_colori(swidget  swid )\
{\
   char *background;\
\
   background = UxGetBackground( swid );\
   UxPutBackground( swid, UxGetForeground( swid ) );\
   UxPutForeground( swid, background );\
}\
\
\
/* \
   event loop per effettuare le connessioni.\
   Viene attivato dalla press del button2 (var_press)\
*/\
  \
event_loop_for_conn(Widget w)\
{\
  int     fine=False;\
  char    *name;\
  XEvent  event;\
  Widget  wid;\
  swidget swid;\
  char list_name[10];\
  BLOCCO *bloc;\
  Cursor cursor;\
\
\
  bloc = locmod->blocchi;\
\
  XGrabPointer( XtDisplay(w), XtWindow(w), True,\
                 Button2MotionMask | ButtonReleaseMask |\
                 LeaveWindowMask | EnterWindowMask,\
                 GrabModeSync, GrabModeAsync,\
                 None, NULL, CurrentTime );\
\
   if ( bloc[blocco].variabili[move_var.var].tipo == INGRESSO )\
     strcpy(list_name, "uscSW");\
   else\
     strcpy(list_name, "ingSW");\
\
   while (!fine)\
   {\
      XAllowEvents(XtDisplay(w), SyncPointer, CurrentTime);\
      XNextEvent(XtDisplay(w),&event);\
      switch (event.type)\
      {\
         case ButtonRelease:\
\
               fine = True;\
\
               if ( move_var.status != MOVE_ON )\
                 break;\
\
               if ( gost_win_drag_on )\
                 clear_gost_win();\
\
               if ( highlight_on )\
               {\
                 highlight_on = False;\
                 highlight( highlight_wid, "false" );\
               }\
\
               wid = XtWindowToWidget( XtDisplay(w), event.xbutton.window);\
               if ( wid  &&  wid != w  &&\
                    UxIsValidSwidget(swid = UxWidgetToSwidget(wid))  &&\
                    (name = UxGetName(swid))  &&  !strcmp( name, "var_lb" )\
                  )\
                 UxDispatchEvent(&event);\
               else\
               {\
                 move_var.status = NON_SELEZIONATO;\
               }\
\
               break;\
         case EnterNotify:\
         case LeaveNotify:\
               wid = XtWindowToWidget(XtDisplay(w), event.xcrossing.window);\
               if ( wid  &&  UxIsValidSwidget(swid = UxWidgetToSwidget(wid)) &&\
                    (name = UxGetName(swid))  &&\
                    ( !strcmp(name, "var_lb")  ||  !strcmp(name, list_name) )\
                  )\
                 UxDispatchEvent(&event);\
               break;\
\
         case MotionNotify:\
               if ( move_var.status == MOVE_TEMP )\
                  move_var.status = MOVE_ON;\
               gost_win( event.xbutton.x_root, event.xbutton.y_root );\
               break;\
\
         case Expose:\
               UxDispatchEvent(&event);\
               break;\
      }\
   }\
\
   XUngrabPointer(XtDisplay(w), CurrentTime);\
\
}   \
\
/* \
   set di un pixmap su una label\
   utilizzato per evidenziare una variabile connessa sulla lista\
 \
*/\
set_var_pixmap(Widget w,char *nome)\
{\
   Arg arg;\
   Widget *wids;\
\
   XtSetArg( arg, XmNchildren, &wids );\
   XtGetValues( XtParent(w), &arg, 1 );\
\
   UxPutLabelPixmap( wids[1], nome );\
\
   set_something(wids[1],XmNx,2);\
}\
\
\
/*\
   visualizza il pixmap di avvenuta connessione "U"\
   sulla item della lista della variabile\
*/ \
visualizza_connessione(Widget w, int var)\
{\
   Arg arg[2];\
   Cardinal narg,num;\
   char *salva_context;\
   char *path_pxm;\
   char nome_file[1024];\
\
   narg=0;\
   XtSetArg( arg[narg], XmNnumChildren, &num );narg++;\
   XtGetValues( XtParent(w), &arg, narg );\
\
   if ( path_pxm = getenv( "LEGOCAD_ICO" ) )\
   {\
     strcpy( nome_file, path_pxm );\
     strcat( nome_file, "/" );\
   }\
   else\
     strcpy( nome_file, "" );\
\
   strcat( nome_file, "topconn.bmp" );\
   set_var_pixmap( w, nome_file );\
   set_var_pixmap( move_var.wid, nome_file );\
   show_connections(var,XtParent(w));\
}\
\
/* \
   effettua la connessione tra due variabili \
*/\
\
make_task_connection(int mod1,int bl1, int var1,int mod2, int bl2, int var2)\
{\
    extern Boolean simulator_changed;\
   CONNMODEL *new_conn;\
   BLOCCO *b1,*b2,*dummy;\
   int idummy;\
\
   b1=simulatore->modelli[mod1]->blocchi;\
   b2=simulatore->modelli[mod2]->blocchi;\
\
/* in b1 metto per comodita' l'ingresso\
   se necessario scambio b1 e b2\
*/\
   if( b2[bl2].variabili[var2].tipo == INGRESSO )\
   {\
      dummy = b2;\
      b2 = b1;\
      b1 = dummy;   \
\
      idummy = mod2;\
      mod2 = mod1;\
      mod1 = idummy;\
\
      idummy = bl2;\
      bl2 = bl1;\
      bl1 = idummy;\
\
      idummy = var2;\
      var2 = var1;\
      var1 = idummy;\
   }\
\
\
/* connessione dell'ingresso (blocco 1) */   \
\
   new_conn = (CONNMODEL *) calloc(1,sizeof(CONNMODEL) );\
   if(new_conn == NULL)\
   {\
     printf("errore allocazione\n");\
     return(FALSE);  \
   }\
\
   new_conn->modello_interno = mod1;\
   new_conn->modello_esterno = mod2;\
   new_conn->blocco_interno = bl1;\
   new_conn->blocco_esterno = bl2;\
   new_conn->var_interna = var1;\
   new_conn->var_esterna = var2;\
\
   new_conn->succ = b1[bl1].var_conn_task;\
   b1[bl1].var_conn_task = new_conn;\
\
   if( b1[bl1].variabili[var1].tipo == INGRESSO)\
       b1[bl1].variabili[var1].model_conn = 1;\
   else\
       b1[bl1].variabili[var1].model_conn++;\
\
\
/* connessione del blocco 2 */\
   new_conn = (CONNMODEL *) calloc(1,sizeof(CONNMODEL) );\
   if(new_conn == NULL)\
   {\
     printf("errore allocazione\n");\
     return(FALSE);  \
   }\
\
   new_conn->modello_interno = mod2;\
   new_conn->modello_esterno = mod1;\
   new_conn->blocco_interno = bl2;\
   new_conn->blocco_esterno = bl1;\
   new_conn->var_interna = var2;\
   new_conn->var_esterna = var1;\
\
   new_conn->succ = b2[bl2].var_conn_task;\
   b2[bl2].var_conn_task = new_conn;\
\
   if( b2[bl2].variabili[var2].tipo == INGRESSO)\
      b2[bl2].variabili[var2].model_conn = 1;\
   else\
      b2[bl2].variabili[var2].model_conn++;\
\
   simulator_changed = TRUE;\
   \
   return(TRUE);\
}\
\
/*\
   verifico se' la connessione e' effettuabile\
*/\
\
tenta_connessione(int mod1,int bl1, int var1,int mod2, int bl2, int var2)\
{\
   CONNMODEL *conn;\
   BLOCCO *b1,*b2,*dummy;\
   int idummy;\
   char msg[200];\
\
   printf("tenta_connessione \n %s con %s\n",\
           simulatore->modelli[mod1]->blocchi[bl1].variabili[var1].nome,\
           simulatore->modelli[mod2]->blocchi[bl2].variabili[var2].nome);\
\
\
   b1=simulatore->modelli[mod1]->blocchi;\
   b2=simulatore->modelli[mod2]->blocchi;\
\
/* non permetto la connessione tra due variabili dello stesso tipo */\
 \
   if( (b1[bl1].variabili[var1].tipo == INGRESSO &&\
       b2[bl2].variabili[var2].tipo == INGRESSO)\
       ||\
       (b1[bl1].variabili[var1].tipo != INGRESSO &&\
       b2[bl2].variabili[var2].tipo != INGRESSO)\
     )\
   {\
         sprintf(msg,"Can Not Connect Same TypeVariable"); \
         create_msgToUser(0,msg);\
\
         printf("ERRORE CONNESSIONE TRA DUE TIPI UGUALI\n");\
         return(FALSE);\
   }\
\
\
/* in b1 metto sempre per comodita' l'ingresso, \
   se e' il caso scambio b1 e b2 in modo da\
   avere in b1 l'ingresso\
 */\
\
   if( b2[bl2].variabili[var2].tipo == INGRESSO )\
   {\
      dummy = b2;\
      b2 = b1;\
      b1 = dummy;   \
\
      idummy = mod2;\
      mod2 = mod1;\
      mod1 = idummy;\
\
      idummy = bl2;\
      bl2 = bl1;\
      bl1 = idummy;\
\
      idummy = var2;\
      var2 = var1;\
      var1 = idummy;\
   }\
\
\
\
/* un ingresso puo' ricevere una sola connessione,\
   in caso contrario emetto un messaggio e impedisco\
   la seconda connessione \
*/ \
\
   if( (b1[bl1].variabili[var1].connessioni + b1[bl1].variabili[var1].model_conn) )\
   {\
         printf("ERRORE INGRESSO GIA' CONNESSO %s\n",b1[bl1].variabili[var1].nome);\
\
         sprintf(msg,"Input Variable %s Already Connected",b1[bl1].variabili[var1].nome); \
         create_msgToUser(0,msg);\
         return(FALSE);\
   }\
\
\
/* una variabile di uscita puo' essere connessa con una sola variabile di ingresso, \
   quindi verifico che non sia gia' stata connessa co un ingresso del blocco proposto.\
   (Ricorda in b1 c'e' l'ingresso in b2' l'uscita)\
*/\
\
   conn = b2[bl2].var_conn_task;\
   while( conn != NULL )\
   {\
      if( conn->modello_esterno ==  mod1 && conn->blocco_esterno == bl1 && conn->var_interna == var2)\
      {\
         sprintf(msg,"Output Variable %s Already Connected With This Block Variable %s",\
         b2[bl2].variabili[var2].nome,b1[bl1].variabili[conn->var_esterna].nome);\
         create_msgToUser(0,msg);\
\
         printf("ERRORE L'USCITA  %s E' GIA' STATA CONNESSA CON IL BLOCCO %s%s\n",\
         b2[bl2].variabili[var2].nome,b1[bl1].sigla_modulo,b1[bl1].sigla_blocco);\
\
         return(FALSE);\
      }\
      conn = conn->succ;\
   } \
\
   return( make_task_connection(mod1,bl1,var1,mod2,bl2,var2) );\
\
}\
\
\
/*** \
   ritorna il numero di connessioni di una variabile\
   tramite l'indice di widget\
***/\
 \
int num_conn(Widget w)\
{\
  Arg    arg[3];\
  Cardinal narg;\
  int  numc,i;\
  Widget *wids;\
\
/* ricavo il numero di connessioni da\
   numero_widget figli del row_column - 3\
   il 3 e' ricavato da \
      2 pixmap di connessione +\
      1 label della variabile\
*/\
\
/* ricavo i children del row_column */   \
  narg=0;\
  XtSetArg( arg[narg], XmNnumChildren, &numc );narg++;\
  XtSetArg( arg[narg], XmNchildren, &wids );narg++;\
  XtGetValues( XtParent(w), arg, narg );\
\
/* restituisco il numero di connessioni */\
\
  for(i=3;i<numc;i++)\
     if( wids[i] ==  w)\
     {\
        return(i-2);\
        break;\
     } \
  return(0);\
}\
\
\
\
var_menu_set()\
{\
   printf("var_menu_set NULL FUNCTION\n"); \
}\
\
\
/***\
  effettua il reset della lista della variabili \
***/\
\
int clear_list( swidget list )\
{\
   Arg arg[4];\
   Cardinal i, num,narg;\
   WidgetList wids;\
\
/* recupero i children della lista */\
   narg = 0;\
   XtSetArg( arg[narg], XmNnumChildren, &num );narg++;\
   XtSetArg( arg[narg], XmNchildren, &wids );narg++;\
   XtGetValues( UxWidgetToSwidget(list), arg, narg );\
\
/* set stato variabile non selezionato */\
   sel_var.status = NON_SELEZIONATO;\
\
/* distruggo tutti gli widget della lista */\
   for ( i=0; i<num; i++ )\
     XtDestroyWidget( wids[i] );\
\
}\
\
\
int change_active_block(MODELLO *ttask,int in_blocco,Widget thiswin)\
{\
   char *salva_context;\
   Arg  arg;\
   Widget *wids;\
   Pixel bck;\
\
   set_var_win_list_context( thiswin, &salva_context);\
\
   blocco = in_blocco;\
   indice_blocco = in_blocco;\
\
   show_on = False;\
 \
   get_something(ingList1,XmNbackground,&bck);\
\
   set_title(ttask->blocchi[in_blocco]);\
\
   clear_list(ingList1);\
   clear_list(uscList1);\
   add_variables(ttask->blocchi[in_blocco]);\
\
   set_something(ingList1,XmNbackground,bck);\
\
   reset_var_win_list_context(salva_context);\
 \
}\
\
\
int filtra(char *nome)\
{\
   printf("I FILTRI NON SONO ANCORA ATTIVI \n");\
   return(True);\
}\
\
\
#ifndef DESIGN_TIME\
\
set_var_win_list_context(Widget w, char **salva_context)\
{\
   swidget swid;\
\
   swid            = UxWidgetToSwidget(w);\
   *salva_context  = (char *) UxTopVarWin1Context;\
   UxTopVarWin1Context = (_UxCtopVarWin1 *) UxGetContext(swid);\
}\
\
\
\
reset_var_win_list_context(char *salva_context)\
{\
   UxTopVarWin1Context = (_UxCtopVarWin1 *) salva_context;\
}\
\
#endif\
\
\
/*\
 * highlight()\
 *\
 * Setta l'attributo highlightOnEnter per i figli 'var_lb' del widget 'w'.\
 */\
\
int highlight( Widget w, char *val )\
{\
   Arg arg[2];\
   Widget *sl_child, *rc, *rc_children, *fr_child, *rc_var_children;\
   int i, num;\
\
   XtSetArg( arg[0], XmNchildren, &sl_child );\
   XtGetValues( w, arg, 1 );\
\
   XtSetArg( arg[0], XmNchildren, &rc );\
   XtGetValues( *sl_child, arg, 1 );\
\
   XtSetArg( arg[0], XmNnumChildren, &num );\
   XtSetArg( arg[1], XmNchildren, &rc_children );\
   XtGetValues( *rc, arg, 2 );\
\
   for ( i=0; i<num; i++ )\
   {\
     XtSetArg( arg[0], XmNchildren, &fr_child );\
     XtGetValues( rc_children[i], arg, 1 );\
\
     XtSetArg( arg[0], XmNchildren, &rc_var_children );\
     XtGetValues( *fr_child, arg, 1 );\
\
     UxPutHighlightOnEnter( UxWidgetToSwidget(rc_var_children[1]), val);\
   }\
\
}\
\
\
int set_title(BLOCCO bloc)\
{\
   char str[100];\
\
   sprintf(str,"%s%s %s",bloc.sigla_modulo,bloc.sigla_blocco,bloc.descr_blocco);\
   trim_blank(str);\
   UxPutLabelString( varTitleLb1, str );\
   \
}\
\
/* \
   event handler sulla lista\
*/\
    \
int list_leave(Widget w,XtPointer cd,XLeaveWindowEvent *event)\
{\
   char *salva_context;\
   Arg  arg;\
   Widget *wids;\
\
   set_var_win_list_context( XtParent(w), &salva_context);\
\
   if ( event->mode == NotifyNormal  &&  event->detail != NotifyInferior )\
   {\
\
      if ( sel_var.status == SEL_ON )\
         XGrabPointer( XtDisplay(w), XtWindow(w), False,\
                       EnterWindowMask | ButtonReleaseMask,\
                       GrabModeAsync, GrabModeAsync,\
                       None, NULL, CurrentTime );\
\
      if ( move_var.status == MOVE_ON  &&  highlight_on )\
      {\
         highlight_on = False;\
         highlight( w, "false" );\
         gost_win_drag_on = True;\
      }\
   }\
\
   reset_var_win_list_context(salva_context);\
}\
\
/*\
   event handler sulla lista\
   enter\
*/\
\
int list_enter(Widget w, XtPointer cd, XEvent *event )\
{\
   char   *salva_context;\
   Arg    arg;\
   Widget *wids;\
\
\
   set_var_win_list_context(XtParent(w), &salva_context);\
\
   if ( sel_var.status == SEL_ON &&\
        (\
          event->type==EnterNotify && ((XEnterWindowEvent*)event)->mode==NotifyNormal &&  ((XEnterWindowEvent*)event)->detail!=NotifyInferior \
             ||\
          event->type == ButtonRelease\
        )\
      )\
   {\
     if ( event->type == ButtonRelease )\
     {\
        sel_var.status = NON_SELEZIONATO;\
        var_menu_set();\
     }\
     XUngrabPointer( XtDisplay(w), CurrentTime );\
   }\
   else if ( move_var.status == MOVE_ON  &&  event->type==EnterNotify && ((XEnterWindowEvent*)event)->detail!=NotifyInferior &&  move_var.bloc != blocco \
           )\
   {\
      /*\
       * Setta l'highlight per la scolled window\
       */\
      XSetInputFocus( XtDisplay(w), XtWindow(w), RevertToNone, CurrentTime );\
      highlight_on = True;\
      highlight_wid = w;\
      highlight( w, "true" );\
      /*\
       * mentre si e' nella scrolled window non viene disegnata la gost window\
       */\
      clear_gost_win();\
      gost_win_drag_on = False;\
   }\
\
\
   reset_var_win_list_context(salva_context);\
\
}\
\
/*\
  event handler sugli item delle variabili\
  release\
*/\
\
int var_release(Widget w,XtPointer variable,XButtonEvent *event)\
{\
  Widget wid;\
  char *salva_context;\
  char str[1024];\
  int var;\
  BLOCCO *bloc;\
  Arg arg;\
\
var = (int)variable;\
\
   /* La routine puo' essere chiamata o per una release su un "var_lb" o\
    * "var_lb_conn"  oppure per un release grabbato dalla scrolled window\
    * contenete il widget su cui si e' effettuato il press (questo nel caso che\
    * il pointer sia uscito dalla scrolled window). Nel secondo caso la scrolled\
    * window non e' un swidget, mentre in ambedue i casi lo e' sempre il parent.\
    * Ecco perche' si setta il contesto del padre.\
    */\
\
   set_var_win_list_context(XtParent(w), &salva_context);\
\
\
   bloc = locmod->blocchi;\
\
   switch ( event->button )\
   {\
\
      case Button1:\
                   /*\
                    * Se era preselezionata uuna variabile, (quindi il release\
                    * e' avvenuto nel widget associato a tale variabile) allora\
                    * la seleziona, altrimenti il release e avvenuto al difuori\
                    * di un 'var_lb' o di un 'var_lb_conn' widget e quindi\
                    * nessuna viene selezionata.\
                    */\
                   if ( sel_var.status == SEL_TEMP )\
                   {\
                      sel_var.wid    = w;\
                      sel_var.var    = var;\
                      sel_var.status = SELEZIONATO;\
                      sel_var.conn   = num_conn( w );\
                   }\
                   else if ( sel_var.status == SEL_ON )\
                      sel_var.status = NON_SELEZIONATO;\
\
                   break;\
\
      case Button2:\
                   /*\
                    * Col secondo bottone premuto vengono dispacciati i soli\
                    * eventi di release che avvengono su un 'var_lb' widget.\
                    */\
                   if ( move_var.status == MOVE_ON  ||\
                        move_var.status == MOVE_TEMP )\
                     if ( move_var.model == indice_modello )\
                     {\
/***\
                        err_level = ERROR;\
                        errore( "ERROR  same block" );\
***/\
                        printf("ERRORE STESSO MODELLO \n");\
                     }\
                     else \
                     { \
\
                       if ( tenta_connessione(indice_modello, blocco, var, move_var.model,move_var.bloc, move_var.var) )\
                           visualizza_connessione( w, var );\
                     }\
                     move_var.status = NON_SELEZIONATO;\
                     break;\
  }\
  reset_var_win_list_context(salva_context);\
\
}\
\
\
/* event handel sugli widget delle variabili\
   press\
*/\
 \
void var_press( Widget w, XtPointer variabile, XButtonEvent *event )\
{\
   swidget swid;\
   int width, height, var;\
   char *salva_context;\
\
   var = (int)variabile;\
\
   set_var_win_list_context(w, &salva_context);\
\
\
   switch ( event->button )\
   {\
     case Button1:\
                    /*\
                     * Se era gia' stata selezionata una variabile la deseleziona.\
                     */\
\
                    if ( sel_var.status == SELEZIONATO )\
                    {\
                       swid = UxWidgetToSwidget( sel_var.wid );\
\
                       inverti_colori( swid );\
\
                    }\
                    /*\
                     * Rende visibile la selezione della variabile\
                     */\
                    swid = UxWidgetToSwidget( w );\
\
                    inverti_colori( swid );\
\
\
\
                    /*\
                     * Preseleziona la variabile ( status = SEL_TEMP ).\
                     * La selezione diverra' effettiva solo se il release\
                     * avviene su un 'var_lb' o un 'var_lb_con'\
                     */\
                    sel_var.status = SEL_TEMP;\
                    sel_var.wid    = w;\
                    sel_var.var    = var;\
                    sel_var.bloc   = blocco;\
                    indice_blocco = blocco;\
                    indice_variabile = var;\
\
                    break;\
      case Button2:\
                    swid   = UxWidgetToSwidget( w );\
\
                       /*\
                        * Setta i parametri per disegnare la gost window che segue\
                        * il movimento del cursore fino al release di Button2\
                        */\
                       gost_win_par.width   = UxGetWidth( swid );\
                       gost_win_par.height  = UxGetHeight( swid );\
                       gost_win_par.mouse_x =  event->x;\
                       gost_win_par.mouse_y =  event->y;\
\
                       gost_win_drag_on     = True;\
\
                       /*\
                        * memorizza i parametri della variabile da collegare\
                        */\
                       move_var.status = MOVE_TEMP;\
                       move_var.wid    = w;\
                       move_var.var    = var;\
                       move_var.bloc   = blocco;\
                       move_var.model = indice_modello;\
\
                       /*\
\
                        * Event loop per eseguire il collegamento della\
                        * variabile. Il loop viene terminato dal release\
                        * di Button2.\
                        */\
                       event_loop_for_conn(w);\
\
                       break;\
   }\
\
   reset_var_win_list_context(salva_context);\
}\
\
\
\
int add_var_list_event_handler(Widget wid)\
{\
  XtAddEventHandler( wid, LeaveWindowMask, False, list_leave, NULL );\
  XtAddEventHandler( wid, EnterWindowMask | ButtonReleaseMask,False, list_enter, NULL );\
  XtAddEventHandler( wid, ButtonReleaseMask, False, var_release, 0 );\
}\
\
\
make_var_entry(swidget lista,BLOCCO bloc, int ind_var)\
{\
  swidget fr, rc, pm, pmconn,lb;\
  Widget  wid;\
  char str[100], nome_file[1024];\
  char *path_pxm,back[100],fore[100];\
\
/**** DEBUG PRINT\
printf("make_var_entry ind_var = %d ",ind_var);\
******/\
\
  strcpy(back,UxGetBackground(lista));  \
  strcpy(fore,UxGetForeground(lista));  \
\
  fr = UxCreateFrame( "var_fr", lista );\
\
  UxPutBackground(fr,back);\
\
  wid = UxCreateWidget( fr );\
\
#ifndef DESIGN_TIME\
  UxPutContext(wid, (char *) UxTopVarWin1Context );\
#endif\
\
  /* cattura un eventuale release event accaduto al di fuori di un "var_lb" */\
  XtAddEventHandler( fr, ButtonReleaseMask, False,\
                     var_release, (XtPointer)ind_var );\
\
  rc = UxCreateRowColumn( "var_rc", fr );\
  UxPutOrientation( rc, "horizontal" );\
  UxPutPacking( rc, "pack_none" );\
  UxPutBackground(rc,back);\
  wid = UxCreateWidget( rc );\
\
#ifndef DESIGN_TIME\
  UxPutContext(wid, (char *) UxTopVarWin1Context );\
#endif\
\
  /* cattura un eventuale release event accaduto al di fuori di un "var_lb" */\
  XtAddEventHandler( wid, ButtonReleaseMask, False,\
                     var_release, (XtPointer)ind_var );\
\
  pm = UxCreateLabel( "var_pm", rc );\
  UxPutBackground(pm,back);\
  UxPutForeground(pm,fore);\
  wid = UxCreateWidget( pm );\
\
  set_something(pm,XmNx,20);\
\
#ifndef DESIGN_TIME\
  UxPutContext(wid, (char *) UxTopVarWin1Context );\
#endif\
\
  UxPutLabelType( pm, "pixmap" );\
\
  /*\
   * costruzione del nome del file contenente i bitmap per i widget 'pm'\
   */\
  if ( path_pxm = getenv( "LEGOCAD_ICO" ) )\
  {\
    strcpy( nome_file, path_pxm );\
    strcat( nome_file, "/" );\
  }\
  else\
    strcpy( nome_file, "" );\
\
  if ( bloc.variabili[ind_var].connessioni )\
    strcat( nome_file, "conn.bmp" );\
  else\
    strcat( nome_file, "void.bmp" );\
\
  UxPutLabelPixmap( pm, nome_file );\
\
  /* cattura un eventuale release event accaduto al di fuori di un "var_lb" */\
  XtAddEventHandler( wid, ButtonReleaseMask, False,\
                     var_release, (XtPointer)ind_var );\
\
\
\
  pmconn = UxCreateLabel( "var_pmconn", rc );\
  UxPutBackground(pmconn,back);\
  UxPutForeground(pmconn,fore);\
  wid = UxCreateWidget( pmconn );\
\
  set_something(pmconn,XmNx,2);\
\
#ifndef DESIGN_TIME\
  UxPutContext(wid, (char *) UxTopVarWin1Context );\
#endif\
\
  UxPutLabelType( pmconn, "pixmap" );\
\
  /*\
   * costruzione del nome del file contenente i bitmap per i widget 'pm'\
   */\
  if ( path_pxm = getenv( "LEGOCAD_ICO" ) )\
  {\
    strcpy( nome_file, path_pxm );\
    strcat( nome_file, "/" );\
  }\
  else\
    strcpy( nome_file, "" );\
\
  if ( bloc.variabili[ind_var].model_conn )\
    strcat( nome_file, "topconn.bmp" );\
  else\
    strcat( nome_file, "void.bmp" );\
\
  UxPutLabelPixmap( pmconn, nome_file );\
\
  /* cattura un eventuale release event accaduto al di fuori di un "var_lb" */\
  XtAddEventHandler( wid, ButtonReleaseMask, False,\
                     var_release, (XtPointer)ind_var );\
\
\
  lb = UxCreateLabel( "var_lb", rc );\
  UxPutBackground(lb,back);\
  UxPutForeground(lb,fore);\
  wid = UxCreateWidget( lb );\
  sprintf( str, "%s  %s", bloc.variabili[ind_var].nome,\
                          bloc.variabili[ind_var].descr );\
\
\
  UxPutLabelString( lb, str );\
  UxPutHighlightThickness( lb, 3 );\
\
  set_something(lb,XmNx,40);\
\
\
  /*\
   * Setta il funzionamento dei widget "var_lb".\
   */\
\
\
  XtAddEventHandler( wid, ButtonPressMask | OwnerGrabButtonMask, False,var_press, (XtPointer)ind_var );\
/**\
  XtAddEventHandler( wid, EnterWindowMask, False, var_enter, NULL );\
  XtAddEventHandler( wid, LeaveWindowMask, False, var_leave, NULL );\
**/\
  XtAddEventHandler( wid, ButtonReleaseMask, False,var_release, (XtPointer)ind_var );\
  XtAddEventHandler( wid, Button2MotionMask, False, gost_win, NULL );\
\
#ifndef DESIGN_TIME\
  UxPutContext(wid, (char *) UxTopVarWin1Context );\
#endif\
\
\
}\
\
int add_variables(BLOCCO bloc)\
{\
   int i,j;\
   char filtvar[100];\
\
\
   if(filtro_attivo)\
   {\
\
      strcpy(filtvar,"Filter on ->");\
\
      for(i=0;i<filtro_attuale->num_var;i++)\
      {\
         strcat(filtvar,filtro_attuale->var[i] );\
         strcat(filtvar,",");\
      }\
  \
      /* elimino la ultima virgola */\
      filtvar[ strlen(filtvar) ] = 0;\
\
\
      for(j=0;j<bloc.num_variabili; j++ )\
      {          \
          if( filtra(bloc.variabili[j].nome) )\
          {\
             if ( bloc.variabili[j].tipo == INGRESSO )\
                 make_var_entry( ingList1, bloc, j );\
             else\
                 make_var_entry( uscList1, bloc, j );\
          }\
      }\
   }\
   else\
   {\
\
      strcpy(filtvar,"");\
      for ( i=0; i<bloc.num_variabili; i++ )\
      {\
         if ( bloc.variabili[i].tipo == INGRESSO )\
           make_var_entry( ingList1, bloc, i );\
         else\
           make_var_entry( uscList1, bloc, i );   \
      }\
   }\
}  \
\
\
/*\
 * gost_win()\
 *\
 * La funzione viene attivata su ogni evento di motion con il button2 premuto.\
 * Disegna su root un rettangolo che segue lo spostamento del cursore.\
 */\
int gost_win(int event_x,int event_y )\
{\
  int x, y;\
\
\
  if ( move_var.status == MOVE_ON && gost_win_drag_on )\
  {\
     /*\
      * calcola le coordinate del vertice alto sinistro della gost window\
      */\
     x = event_x - gost_win_par.mouse_x;\
     y = event_y - gost_win_par.mouse_y;\
     if ( ! gost_win_par.primo )\
        /*\
         * Cancella la gost window precedente.\
         */\
        XDrawRectangle( UxDisplay, DefaultRootWindow(UxDisplay), gost_win_gc, gost_win_par.save_x, gost_win_par.save_y,  gost_win_par.width, gost_win_par.height );\
\
     gost_win_par.primo  = False;\
\
     /*  \
      * conserva le nuove coordinate per la successiva cancellazione della\
      * gost window\
      */\
     gost_win_par.save_x = x;\
     gost_win_par.save_y = y;\
\
     /*\
      * Disegna la nuova gost window.\
      */\
     XDrawRectangle( UxDisplay, DefaultRootWindow(UxDisplay), gost_win_gc, x, y, gost_win_par.width, gost_win_par.height );\
  }\
\
}\
\
/*\
 * clear_gost_win()\
 *\
 * Cancella l'ultima gost window dopo che aver rilasciato il button2\
 */\
clear_gost_win()\
{\
\
   XDrawRectangle( UxDisplay, DefaultRootWindow(UxDisplay), gost_win_gc,\
                   gost_win_par.save_x, gost_win_par.save_y,\
                   gost_win_par.width, gost_win_par.height );\
\
   gost_win_par.primo = True;\
}\
\
\
create_gost_win_gc()\
{\
\
  gost_win_gc  = XCreateGC( UxDisplay, DefaultRootWindow(UxDisplay), 0, NULL );\
\
  XSetFunction( UxDisplay, gost_win_gc, GXxor );\
  XSetSubwindowMode( UxDisplay, gost_win_gc, IncludeInferiors );\
  XSetForeground( UxDisplay, gost_win_gc, ~0 );\
  XSetLineAttributes( UxDisplay, gost_win_gc, 0, LineSolid, CapButt, JoinMiter );\
\
}\

*topVarWin1.name: topVarWin1
*topVarWin1.unitType: "pixels"
*topVarWin1.x: 800
*topVarWin1.y: 440
*topVarWin1.width: 560
*topVarWin1.height: 400

*varForm1.class: form
*varForm1.parent: topVarWin1
*varForm1.static: true
*varForm1.name: varForm1

*varTitleLb1.class: label
*varTitleLb1.parent: varForm1
*varTitleLb1.static: true
*varTitleLb1.name: varTitleLb1
*varTitleLb1.x: 5
*varTitleLb1.y: 10
*varTitleLb1.width: 545
*varTitleLb1.height: 35
*varTitleLb1.leftAttachment: "attach_form"
*varTitleLb1.leftOffset: 5
*varTitleLb1.rightAttachment: "attach_form"
*varTitleLb1.rightOffset: 5
*varTitleLb1.topAttachment: "attach_form"
*varTitleLb1.topOffset: 5
*varTitleLb1.fontList: "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1"
*varTitleLb1.labelString: "Block Name Selected"

*filterLb1.class: label
*filterLb1.parent: varForm1
*filterLb1.static: true
*filterLb1.name: filterLb1
*filterLb1.x: 0
*filterLb1.y: 0
*filterLb1.height: 20
*filterLb1.alignment: "alignment_beginning"
*filterLb1.labelString: "Filter"
*filterLb1.marginLeft: 10
*filterLb1.leftOffset: 5
*filterLb1.topAttachment: "attach_widget"
*filterLb1.topOffset: 5
*filterLb1.topWidget: "varTitleLb1"
*filterLb1.leftAttachment: "attach_form"

*filterSel1.class: rowColumn
*filterSel1.parent: varForm1
*filterSel1.static: true
*filterSel1.name: filterSel1
*filterSel1.rowColumnType: "menu_option"
*filterSel1.subMenuId: "filterPane1"
*filterSel1.y: 25
*filterSel1.marginHeight: 0
*filterSel1.marginWidth: 0
*filterSel1.spacing: 0
*filterSel1.x: 5
*filterSel1.createCallback: {\
\
}
*filterSel1.packing: "pack_column"
*filterSel1.orientation: "vertical"
*filterSel1.topAttachment: "attach_widget"
*filterSel1.topOffset: 3
*filterSel1.topWidget: "varTitleLb1"
*filterSel1.leftAttachment: "attach_widget"
*filterSel1.leftOffset: 5
*filterSel1.leftWidget: "filterLb1"

*filterPane1.class: rowColumn
*filterPane1.parent: filterSel1
*filterPane1.static: false
*filterPane1.name: filterPane1
*filterPane1.rowColumnType: "menu_pulldown"
*filterPane1.width: 120
*filterPane1.packing: "pack_column"
*filterPane1.menuHistory: ""

*defFil1.class: pushButton
*defFil1.parent: filterPane1
*defFil1.static: true
*defFil1.name: defFil1
*defFil1.labelString: "No Filter"
*defFil1.mnemonic: "N"

*varFrame1.class: frame
*varFrame1.parent: varForm1
*varFrame1.static: true
*varFrame1.name: varFrame1
*varFrame1.x: 10
*varFrame1.y: 155
*varFrame1.width: 540
*varFrame1.height: 310
*varFrame1.bottomAttachment: "attach_form"
*varFrame1.bottomOffset: 5
*varFrame1.leftAttachment: "attach_form"
*varFrame1.leftOffset: 5
*varFrame1.rightAttachment: "attach_form"
*varFrame1.rightOffset: 5
*varFrame1.topAttachment: "attach_widget"
*varFrame1.topOffset: 5
*varFrame1.topWidget: "filterSel1"

*panedWindow3.class: panedWindow
*panedWindow3.parent: varFrame1
*panedWindow3.static: true
*panedWindow3.name: panedWindow3
*panedWindow3.x: 15
*panedWindow3.y: 155
*panedWindow3.width: 565
*panedWindow3.height: 155

*ingForm1.class: form
*ingForm1.parent: panedWindow3
*ingForm1.static: true
*ingForm1.name: ingForm1
*ingForm1.resizePolicy: "resize_none"
*ingForm1.x: 15
*ingForm1.y: 10
*ingForm1.width: 535
*ingForm1.height: 160
*ingForm1.paneMinimum: 100

*ingLb1.class: label
*ingLb1.parent: ingForm1
*ingLb1.static: true
*ingLb1.name: ingLb1
*ingLb1.x: 25
*ingLb1.y: 185
*ingLb1.width: 150
*ingLb1.height: 25
*ingLb1.labelString: "Input"
*ingLb1.alignment: "alignment_beginning"
*ingLb1.leftAttachment: "attach_form"
*ingLb1.leftOffset: 20
*ingLb1.rightAttachment: "attach_form"
*ingLb1.rightOffset: 20
*ingLb1.topAttachment: "attach_form"
*ingLb1.topOffset: 0

*ingSW1.class: scrolledWindow
*ingSW1.parent: ingForm1
*ingSW1.static: true
*ingSW1.name: ingSW1
*ingSW1.scrollingPolicy: "automatic"
*ingSW1.x: 5
*ingSW1.y: 25
*ingSW1.width: 215
*ingSW1.height: 230
*ingSW1.bottomAttachment: "attach_form"
*ingSW1.bottomOffset: 5
*ingSW1.leftAttachment: "attach_form"
*ingSW1.leftOffset: 5
*ingSW1.rightAttachment: "attach_form"
*ingSW1.rightOffset: 5
*ingSW1.topAttachment: "attach_widget"
*ingSW1.topOffset: 0
*ingSW1.topWidget: "ingLb1"

*ingList1.class: rowColumn
*ingList1.parent: ingSW1
*ingList1.static: true
*ingList1.name: ingList1
*ingList1.x: 7
*ingList1.y: 2
*ingList1.width: 475
*ingList1.height: 100
*ingList1.adjustMargin: "true"
*ingList1.adjustLast: "true"
*ingList1.entryAlignment: "alignment_end"
*ingList1.isAligned: "true"
*ingList1.packing: "pack_tight"
*ingList1.spacing: 0

*menu3.class: rowColumn
*menu3.parent: ingList1
*menu3.static: true
*menu3.name: menu3
*menu3.rowColumnType: "menu_popup"
*menu3.menuAccelerator: "<KeyUp>F4"

*menu3_p1_b1.class: pushButton
*menu3_p1_b1.parent: menu3
*menu3_p1_b1.static: true
*menu3_p1_b1.name: menu3_p1_b1
*menu3_p1_b1.labelString: "Delete Connection"
*menu3_p1_b1.activateCallback: {\
   delete_connection(UxWidget);\
}

*uscForm1.class: form
*uscForm1.parent: panedWindow3
*uscForm1.static: true
*uscForm1.name: uscForm1
*uscForm1.resizePolicy: "resize_none"
*uscForm1.x: 20
*uscForm1.y: 65
*uscForm1.width: 52
*uscForm1.height: 160
*uscForm1.paneMinimum: 100

*uscLb1.class: label
*uscLb1.parent: uscForm1
*uscLb1.static: true
*uscLb1.name: uscLb1
*uscLb1.x: 355
*uscLb1.y: 190
*uscLb1.width: 165
*uscLb1.height: 25
*uscLb1.labelString: "Output"
*uscLb1.alignment: "alignment_beginning"
*uscLb1.leftAttachment: "attach_form"
*uscLb1.leftOffset: 20
*uscLb1.rightAttachment: "attach_form"
*uscLb1.rightOffset: 20
*uscLb1.topAttachment: "attach_form"
*uscLb1.topOffset: 0

*uscSW1.class: scrolledWindow
*uscSW1.parent: uscForm1
*uscSW1.static: true
*uscSW1.name: uscSW1
*uscSW1.scrollingPolicy: "automatic"
*uscSW1.x: 330
*uscSW1.y: 225
*uscSW1.width: 180
*uscSW1.height: 230
*uscSW1.bottomAttachment: "attach_form"
*uscSW1.bottomOffset: 5
*uscSW1.leftAttachment: "attach_form"
*uscSW1.leftOffset: 5
*uscSW1.rightAttachment: "attach_form"
*uscSW1.rightOffset: 5
*uscSW1.topAttachment: "attach_widget"
*uscSW1.topOffset: 0
*uscSW1.topWidget: "uscLb1"
*uscSW1.shadowThickness: 2
*uscSW1.translations: "" 

*uscList1.class: rowColumn
*uscList1.parent: uscSW1
*uscList1.static: true
*uscList1.name: uscList1
*uscList1.x: 2
*uscList1.y: 2
*uscList1.width: 480
*uscList1.height: 105
*uscList1.shadowThickness: 0
*uscList1.topShadowColor: "#0000cb00da00"
*uscList1.bottomShadowColor: "#420048000000"
*uscList1.sensitive: "true"
*uscList1.spacing: 0
*uscList1.traversalOn: "true"
*uscList1.packing: "pack_tight"

*menu5.class: rowColumn
*menu5.parent: uscList1
*menu5.static: true
*menu5.name: menu5
*menu5.rowColumnType: "menu_popup"
*menu5.menuAccelerator: "<KeyUp>F4"

*menu5_p1_b1.class: pushButton
*menu5_p1_b1.parent: menu5
*menu5_p1_b1.static: true
*menu5_p1_b1.name: menu5_p1_b1
*menu5_p1_b1.labelString: "Delete Connectio"
*menu5_p1_b1.activateCallback: {\
   delete_connection(UxWidget);\
}

*menu4.class: rowColumn
*menu4.parent: varForm1
*menu4.static: true
*menu4.name: menu4
*menu4.rowColumnType: "menu_bar"
*menu4.leftAttachment: "attach_widget"
*menu4.leftOffset: 300
*menu4.leftWidget: "filterSel1"
*menu4.topAttachment: "attach_widget"
*menu4.topWidget: "varTitleLb1"
*menu4.menuAccelerator: "<KeyUp>F10"
*menu4.height: 11
*menu4.width: 50
*menu4.mappedWhenManaged: "true"
*menu4.ancestorSensitive: "true"

*menu4_p1.class: rowColumn
*menu4_p1.parent: menu4
*menu4_p1.static: true
*menu4_p1.name: menu4_p1
*menu4_p1.rowColumnType: "menu_pulldown"
*menu4_p1.height: 21
*menu4_p1.width: 50

*menu4_p1_b1.class: pushButton
*menu4_p1_b1.parent: menu4_p1
*menu4_p1_b1.static: true
*menu4_p1_b1.name: menu4_p1_b1
*menu4_p1_b1.labelString: "Show Connections"
*menu4_p1_b1.activateCallback: show_all_conn();\


*menu4_p1_b2.class: pushButton
*menu4_p1_b2.parent: menu4_p1
*menu4_p1_b2.static: true
*menu4_p1_b2.name: menu4_p1_b2
*menu4_p1_b2.labelString: "No Show Connections"
*menu4_p1_b2.activateCallback: no_show_all_connections();

*menu4_top_b1.class: cascadeButton
*menu4_top_b1.parent: menu4
*menu4_top_b1.static: true
*menu4_top_b1.name: menu4_top_b1
*menu4_top_b1.labelString: "Options"
*menu4_top_b1.subMenuId: "menu4_p1"
*menu4_top_b1.alignment: "alignment_center"

