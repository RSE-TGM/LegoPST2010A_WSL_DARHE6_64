! UIMX ascii 2.0 key: 1448                                                      

*varWin.class: mainWindow
*varWin.parent: NO_PARENT
*varWin.defaultShell: transientShell
*varWin.static: true
*varWin.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo varWin.i\
   tipo \
   release 2.28\
   data 5/12/95\
   reserved @(#)varWin.i	2.28\
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
#include <stdio.h>\
#ifndef DESIGN_TIME\
#include <stdlib.h>\
#endif\
#include "lg1.h"\
#include "errore.h"\
#include "varWinType.h"\
#include "lg1MainWindowType.h"\
#include "message_type.h"\
#include "question_type.h"\
\
#include "filtri.h"\
\
void var_press();\
void var_enter();\
void var_leave();\
void var_release();\
void list_enter();\
void list_leave();\
void gost_win();\
\
\
\
\
extern ERR_LEVEL err_level;\
extern Display   *display;\
extern Window    root;\
extern GC        gost_win_gc;\
\
\
VAR_SEL  move_var;\
GOST_WIN gost_win_par;\
int      gost_win_drag_on;\
\
static int    highlight_on=False;\
static Widget highlight_wid, del_wid;\
\
extern swidget create_EditVarDescr();\
\
swidget fintavarWin;\
\

*varWin.ispecdecl: VAR_SEL sel_var;\
int     blocco;\
int indice_blocco,indice_variabile;\
int button_already_def;\
\
int filtro_attivo; /*indica se ci sono filtri attivi */\
FILTRI *filtro_attuale;    /* filtro attivo correntemente */\

*varWin.ispeclist: sel_var, blocco, indice_blocco, indice_variabile, button_already_def, filtro_attivo, filtro_attuale
*varWin.ispeclist.sel_var: "VAR_SEL", "%sel_var%"
*varWin.ispeclist.blocco: "int", "%blocco%"
*varWin.ispeclist.indice_blocco: "int", "%indice_blocco%"
*varWin.ispeclist.indice_variabile: "int", "%indice_variabile%"
*varWin.ispeclist.button_already_def: "int", "%button_already_def%"
*varWin.ispeclist.filtro_attivo: "int", "%filtro_attivo%"
*varWin.ispeclist.filtro_attuale: "FILTRI", "*%filtro_attuale%"
*varWin.funcdecl: swidget create_varWin( bl )\
int bl;
*varWin.funcname: create_varWin
*varWin.funcdef: "swidget", "<create_varWin>(%)"
*varWin.argdecl: int bl;
*varWin.arglist: bl
*varWin.arglist.bl: "int", "%bl%"
*varWin.icode: Widget wid;\
char str[80];\
Arg arg;\
BLOCCO *bloc=blocchi;\
\
move_var.status = sel_var.status = NON_SELEZIONATO;\
gost_win_par.primo = True;\
\
\

*varWin.fcode: blocco = bl;\
\
filtro_attivo = False;\
\
XtSetArg( arg, XmNkeyboardFocusPolicy, XmPOINTER );\
XtSetValues( XtParent(UxGetWidget(rtrn)), &arg, 1 );\
\
put_var_win_title( bloc[blocco].sigla_modulo, bloc[blocco].sigla_blocco , bloc[blocco].descr_blocco);\
\
add_var_list_event_handler( UxGetWidget(ingSW), NULL );\
add_var_list_event_handler( UxGetWidget(uscSW), NULL );\
\
add_variables();\
var_menu_set();\
\
add_filt_opt_butt(rtrn);\
\
return(rtrn);\
 
*varWin.auxdecl: /* verifica se una variabili passa attraverso\
   il filtro correntemente attivo */\
\
int filtra(char *nome)\
{\
   int i,len_var_filt;\
   char *var_filt;\
   int retval = 0;\
\
   if(filtro_attivo)\
   {\
      for(i=0;i<filtro_attuale->num_var;i++)\
      {\
         var_filt = filtro_attuale->var[i];\
         len_var_filt = strlen(filtro_attuale->var[i]);\
\
         if( strncmp(var_filt,nome,len_var_filt) == 0 )\
            retval+=1;\
         else\
            retval+=0;\
      }\
      return(retval);\
   }\
   else\
      return(1);\
}\
\
/*\
 * add_variables()\
 *\
 * La funzine viene chiamata quando viene attivata una nuova interfaccia di tipo\
 * 'varWin' e quando in una interfaccia gia' esistente si carica un nuovo blocco.\
 * Essa inserisce le variabili del blocco nelle due liste dell'interfaccia a \
 * seconda che siano di ingresso o di uscita.\
 */\
add_variables()\
{\
   int i,j;\
   BLOCCO *bloc=blocchi;  /* a causa dell'interprete uimx */\
   char filtvar[100];\
\
   if(filtro_attivo)\
   {\
      strcpy(filtvar,"Filter on ->");\
\
      for(i=0;i<filtro_attuale->num_var;i++)\
      {\
         strcat(filtvar,filtro_attuale->var[i] );\
         strcat(filtvar,",");\
\
\
      }\
\
/* elimino la ultima virgola */\
         filtvar[ strlen(filtvar) ] = 0;      \
\
      for(j=0;j<bloc[blocco].num_variabili; j++ )\
      {\
          if( filtra(bloc[blocco].variabili[j].nome) ) \
          {      \
               if ( bloc[blocco].variabili[j].tipo == INGRESSO )\
                  make_var_entry( ingList, j );\
               else\
                  make_var_entry( uscList, j );\
          }\
      }\
      \
   }\
   else\
   {\
      strcpy(filtvar,"");\
      for ( i=0; i<bloc[blocco].num_variabili; i++ )\
         if ( bloc[blocco].variabili[i].tipo == INGRESSO )\
           make_var_entry( ingList, i );\
         else\
           make_var_entry( uscList, i );\
   }\
\
}\
\
\
\
\
/* \
 * make_var_entry()\
 *\
 * Costruisce un entry per la lista delle variabili di uscita o di ingresso.\
 *\
 * Ogni entry e' cosi' composta:\
 *\
 *               frame --- row column --- label ( pixmap )\
 *                                    |\
 *                                    --- label ( identificatore variabile )\
 *\
 *\
 * Dinamicamente al row column vengono aggiunte altre label contenenti\
 * gli identificatori delle variabili connesse.\
 *\
 * Il grab automatico dell'evento di press button viene disattivato\
 * con la maschera 'OwnerGrabButtonMask' cosi che il release puo' essere\
 * intercettato da un qualunque altro widget. Comunque il release viene\
 * grabbato quando si esce dalla scrolled window ( vedi list_leave() ).\
 */\
make_var_entry( list_swid, variabile )\
swidget list_swid;\
int variabile;\
{\
  swidget fr, rc, pm, lb;\
  Widget  wid;\
  char str[100], nome_file[1024];\
  char *path_pxm;\
  BLOCCO  *bloc=blocchi; /* Serve per fregare l'interprete UIMX */\
\
\
  fr = UxCreateFrame( "var_fr", list_swid );\
  wid = UxCreateWidget( fr );\
\
#ifndef DESIGN_TIME\
  UxPutContext(wid, (char *) UxVarWinContext );\
#endif\
\
  /* cattura un eventuale release event accaduto al di fuori di un "var_lb" */\
  XtAddEventHandler( fr, ButtonReleaseMask, False,\
                     var_release, (XtPointer)variabile );\
\
  rc = UxCreateRowColumn( "var_rc", fr );\
  UxPutOrientation( rc, "horizontal" );\
  UxPutPacking( rc, "pack_none" );\
  wid = UxCreateWidget( rc );\
\
#ifndef DESIGN_TIME\
  UxPutContext(wid, (char *) UxVarWinContext );\
#endif\
\
  /* cattura un eventuale release event accaduto al di fuori di un "var_lb" */\
  XtAddEventHandler( wid, ButtonReleaseMask, False,\
                     var_release, (XtPointer)variabile );\
\
\
  pm = UxCreateLabel( "var_pm", rc );\
  wid = UxCreateWidget( pm );\
\
#ifndef DESIGN_TIME\
  UxPutContext(wid, (char *) UxVarWinContext );\
#endif\
\
  UxPutLabelType( pm, "pixmap" );\
\
  /* \
   * costruzione del nome del file contenente i bitmap per i widget 'pm'\
   */\
  if ( path_pxm = getenv( "LEGOCAD_ICO" ) )\
  {\
    strcpy( nome_file, path_pxm );\
    strcat( nome_file, "/" );\
  }\
  else\
    strcpy( nome_file, "" );\
  if ( bloc[blocco].variabili[variabile].connessioni )\
    strcat( nome_file, "conn.bmp" );\
  else\
    strcat( nome_file, "void.bmp" );\
\
  UxPutLabelPixmap( pm, nome_file );\
  /* cattura un eventuale release event accaduto al di fuori di un "var_lb" */\
  XtAddEventHandler( wid, ButtonReleaseMask, False,\
                     var_release, (XtPointer)variabile );\
\
\
  lb = UxCreateLabel( "var_lb", rc );\
  wid = UxCreateWidget( lb );\
  sprintf( str, "%s  %s", bloc[blocco].variabili[variabile].nome,\
                          bloc[blocco].variabili[variabile].descr );\
  UxPutLabelString( lb, str );\
  UxPutHighlightThickness( lb, 3 );\
\
  set_something(lb,XmNx,20);\
  /*\
   * Setta il funzionamento dei widget "var_lb".\
   */\
  XtAddEventHandler( wid, ButtonPressMask | OwnerGrabButtonMask, False,\
                     var_press, (XtPointer)variabile );\
  XtAddEventHandler( wid, EnterWindowMask, False, var_enter, NULL );\
  XtAddEventHandler( wid, LeaveWindowMask, False, var_leave, NULL );\
  XtAddEventHandler( wid, ButtonReleaseMask, False,\
                     var_release, (XtPointer)variabile );\
  XtAddEventHandler( wid, Button2MotionMask, False, gost_win, NULL );\
\
#ifndef DESIGN_TIME\
  UxPutContext(wid, (char *) UxVarWinContext );\
#endif\
}\
\
\
\
\
\
/*\
 * var_press()\
 *\
 * Event Handler attivato quando si preme il primo o secondo bottone su\
 * un "var_lb" od un "var_lb_conn"\
 *  \
 * Il press di Button1 preseleziona la variabile.\
 * Il press di Button2 predispone la variabile per muoverla in un altra lista\
 * al fine di connetterla.\
 */\
void var_press( w, variabile, event )\
Widget w;\
XtPointer variabile;\
XButtonEvent *event;\
{\
   swidget swid;\
   int width, height, var=(int)variabile;\
   char *salva_context;\
\
\
   set_var_win_list_context(w, &salva_context);\
\
   switch ( event->button )\
   {\
\
      case Button1:\
                    /*\
                     * Se era gia' stata selezionata una variabile la deseleziona.\
                     */\
                    if ( sel_var.status == SELEZIONATO )\
                    {\
                       swid = UxWidgetToSwidget( sel_var.wid );\
                       inverti_colori( swid );\
                    }\
\
                    /* \
                     * Rende visibile la selezione della variabile\
                     */\
                    swid = UxWidgetToSwidget( w );\
                    inverti_colori( swid );\
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
\
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
                        * memorizza i parametri del della variabile da collegare\
                        */\
                       move_var.status = MOVE_TEMP;\
                       move_var.wid    = w; \
                       move_var.var    = var;\
                       move_var.bloc   = blocco;\
\
                       /*\
                        * Event loop per eseguire il collegamento della \
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
\
\
/*\
 * var_enter()\
 *\
 * Event Handler attivato quando si entra in un "var_lb" od un "var_lb_conn"\
 *  \
 */\
void var_enter( w, variabile, event )\
Widget w;\
XtPointer variabile;\
XEnterWindowEvent *event;\
{\
  char *salva_context;\
  int  var=(int)variabile;\
\
  set_var_win_list_context(w, &salva_context);\
\
  /* \
   * testa se l'evento e' duvuto ad un ormale ingreso nel widget (non ad un \
   * grab), se e' premuto il bottone 1 e se si e' in fase di selezione\
   * di una variabile (il press era avvenuto su di un 'var_lb' o \
   * un 'var_lb_conn')\
   */\
  if ( event->mode==NotifyNormal  &&  event->state & Button1Mask  &&\
       sel_var.status == SEL_ON )\
  {\
     /*\
      * preseleziona la variabile\
      */\
     inverti_colori( UxWidgetToSwidget( w ) );\
     sel_var.status = SEL_TEMP;\
     sel_var.wid    = w;\
     sel_var.var    = var;\
     sel_var.bloc   = blocco;\
  }\
\
  reset_var_win_list_context(salva_context);\
\
}\
\
\
\
\
/*\
 * var_leave()\
 *\
 * Event Handler attivato quando si esce da un "var_lb" o da un "var_lb_conn"\
 *  \
 */\
void var_leave( w, cd, event )\
Widget w;\
XtPointer cd;\
XLeaveWindowEvent *event;\
{\
  char *salva_context;\
\
  set_var_win_list_context(w, &salva_context);\
\
\
  /* \
   * testa se l'evento e' duvuto ad una normale uscita dal widget (non ad un \
   * grab), se e' premuto il bottone 1 e se si e' in fase di selezione\
   * di una variabile (il press era avvenuto su di un 'var_lb' o \
   * un 'var_lb_conn')\
   */\
  if ( event->mode==NotifyNormal  &&  event->state & Button1Mask  &&\
       sel_var.status == SEL_TEMP )\
  { \
     /*\
      * Deseleziona la variabile ma rimane in fase di selezione.\
      */\
     inverti_colori( UxWidgetToSwidget( w ) );\
     sel_var.status = SEL_ON;\
  }\
\
\
  reset_var_win_list_context(salva_context);\
\
}\
\
\
\
\
\
/*\
 * var_release()\
 *\
 * Event Handler attivato quando si rilascia il primo o secondo bottone.\
 * Se e' premuto il primo bottone il release viene intercettato da tutti i widget\
 * della lista a cui appartiene il widget su cui si e' effettuato il press; pero'\
 * se si esce dalla scrolled window il release viene grabbato alla scrolled \
 * window stessa.\
 * Se e' premuto il secondo bottone del mouse, all'atto del press si attiva\
 * un grab per il release che avvenga all'esterno dell'applicazione, mentre se\
 * il release avviene sopa un widget dell'applicazione esso viene gestito (ed\
 * eventualmente dispacciato) da un event loop secondario.\
 *  \
 */\
void var_release( w, variabile, event )\
Widget w;\
XtPointer variabile;\
XButtonEvent *event;\
{\
  Widget wid;\
  char *salva_context;\
  char str[1024];\
  int var=(int)variabile;\
  BLOCCO *bloc=blocchi;\
  Arg arg;\
\
  extern MESSAGE message;\
\
   /* La routine puo' essere chiamata o per una release su un "var_lb" o\
    * "var_lb_conn"  oppure per un release grabbato dalla scrolled window\
    * contenete il widget su cui si e' effettuato i press (questo nel caso che\
    * il pointer sia uscito dalla scrolled window). Nel secondo caso la scrolled\
    * window non e' un swidget, mentre in ambedue i casi lo e' sempre il parent.\
    * Ecco perche' si setta il contesto del padre.\
    */\
   set_var_win_list_context(XtParent(w), &salva_context);\
\
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
                   /* \
                    * Sistema la configurazione dei menu a seguito delle\
                    * mutate condizioni.\
                    */\
                   var_menu_set();\
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
                     if ( move_var.bloc == blocco )\
                     {\
                        err_level = ERROR;\
                        errore( "ERROR  same block" );\
                     }\
                     else \
                     { \
                        if ( tenta_connessione( blocco, var,\
                                                move_var.bloc, move_var.var )\
                           )\
                        {\
                           visualizza_connessione( w, var );\
\
                           /*\
                            * Toglie l'highlight al widget del release!!\
                            */\
                           _XmUnhighlightBorder(w);\
                          \
                           /*\
                            * Toglie l'highlightOnEnter ai 'var_lb' widget della\
                            * lista alla quale appartiene il widget del release.\
                            */\
                           highlight_on = False;\
                           highlight( highlight_wid, "false" );\
\
                           /*\
                            * Informa dell'avvenuta connessione.\
                            */\
                           if( bloc[blocco].variabili[var].nome[0] ==\
                              bloc[move_var.bloc].variabili[move_var.var].nome[0] )\
 			   {\
                              strcpy( str, "Connected " );\
                              strcat( str, bloc[blocco].variabili[var].nome );\
                              strcat( str, " to " );\
                              strcat( str,\
                                 bloc[move_var.bloc].variabili[move_var.var].nome );\
			   }\
                           else\
                           {\
			      strcpy(str ,"WARNING ");\
                              strcat(str,bloc[blocco].variabili[var].nome);\
                              strcat(str," ");\
                              strcat(str,bloc[move_var.bloc].variabili[move_var.var].nome);\
                              strcat(str,"\n are not homogeneus");    \
			   }\
                           message = MSG_MADE_CONN;\
                           messageDB_activate( str );\
                        }\
\
                   }\
   \
                   move_var.status = NON_SELEZIONATO;\
\
                   break;\
\
  }\
\
  reset_var_win_list_context(salva_context);\
\
}\
\
\
\
\
/*\
 * inverti_colori()\
 *\
 * Inverte il background ed il foreground del widget argomento.\
 */\
inverti_colori( swid )\
swidget swid;\
{\
   char *background;\
\
   background = UxGetBackground( swid );\
   UxPutBackground( swid, UxGetForeground( swid ) );\
   UxPutForeground( swid, background );\
\
\
}\
\
\
\
\
/*\
 * list_enter()\
 *\
 * La funzione viene attivata quando si entra in una delle scrolled window \
 * dell'interfaccia 'varWin'.\
 * Se si sta selezionando una variabile (Button1 premuto) l'evento di enter \
 * viene notificato solo se si rientra nella scrolled window dove era stato\
 * premuto il buttone (cio' a causa del grab attivato quando si era usciti\
 * dalla scrolled window, vedi list_leave). In tal caso viene tolto il grab.\
 * Se si entra nella scrolled window con il button2 premuto si setta a True\
 * l'attributo highlightOnEnter dei widget 'var_lb' figli della scrolled window.\
 * \
 * Gli eventi di enter generati passando da una window figlia della scrolled\
 * window alla scrolled window stessa vengono scartati testando il campo\
 * 'detail' dell'evento generato.\
 */\
void list_enter( w, cd, event )\
Widget w;\
XtPointer cd;\
XEvent *event;\
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
          event->type==EnterNotify &&\
          ((XEnterWindowEvent*)event)->mode==NotifyNormal &&\
          ((XEnterWindowEvent*)event)->detail!=NotifyInferior \
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
     XUngrabPointer( display, CurrentTime );\
   }\
   else if ( move_var.status == MOVE_ON  &&  event->type==EnterNotify && \
             ((XEnterWindowEvent*)event)->detail!=NotifyInferior &&\
             move_var.bloc != blocco \
           )\
   {\
      /*\
       * Setta l'highlight per la scolled window\
       */\
      XSetInputFocus( display, XtWindow(w), RevertToNone, CurrentTime );\
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
\
\
\
\
/* \
 * list_leave()\
 *\
 * La funzione viene attivata quando si esce da una delle scrolled window \
 * dell'interfaccia 'varWin'.\
 * Se si sta selezionando una variabile (Button1 premuto) viene settato un grab.\
 * Se si esce dalla scrolled window con il button2 premuto si setta a False\
 * l'attributo highlightOnEnter dei widget 'var_lb' figli della scrolled window.\
 * \
 * Gli eventi di enter generati passando da una window figlia della scrolled\
 * window alla scrolled window stessa vengono scartati testando il campo\
 * 'detail' dell'evento generato.\
 */\
void list_leave( w, cd, event )\
Widget w;\
XtPointer cd;\
XLeaveWindowEvent *event;\
{\
   char *salva_context;\
   Arg  arg;\
   Widget *wids;\
\
\
   set_var_win_list_context(XtParent(w), &salva_context);\
\
   if ( event->mode == NotifyNormal  &&  event->detail != NotifyInferior )\
             \
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
\
}\
\
\
\
/*\
 * highlight()\
 *\
 * Setta l'attributo highlightOnEnter per i figli 'var_lb' del widget 'w'.\
 */\
highlight( w, val )\
Widget w;\
char *val;\
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
     UxPutHighlightOnEnter( UxWidgetToSwidget(rc_var_children[1]), val );\
   }\
\
}\
\
\
\
\
/*\
 * gost_win()\
 *\
 * La funzione viene attivata su ogni evento di motion con il button2 premuto.\
 * Disegna su root un rettangolo che segue lo spostamento del cursore.\
 */\
void gost_win( event_x, event_y )\
int event_x, event_y;\
{\
  int x, y;\
\
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
        XDrawRectangle( display, root, gost_win_gc,\
                        gost_win_par.save_x, gost_win_par.save_y,\
                        gost_win_par.width, gost_win_par.height );\
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
     XDrawRectangle( display, root, gost_win_gc, x, y,\
                     gost_win_par.width, gost_win_par.height );\
  }\
\
}\
\
\
\
\
/*\
 * clear_gost_win()\
 *\
 * Cancella l'ultima gost window dopo che aver rilasciato il button2\
 */\
clear_gost_win()\
{\
\
   XDrawRectangle( display, root, gost_win_gc,\
                   gost_win_par.save_x, gost_win_par.save_y,\
                   gost_win_par.width, gost_win_par.height );\
\
   gost_win_par.primo = True;\
}\
\
\
\
\
\
\
show_connections(variabile, var_wid)\
int variabile;\
Widget var_wid;\
{\
\
   swidget lb;\
   Widget  wid;\
   CONN    *conn;\
   int     count;\
   Position swap;\
   Dimension he;\
   char    str[100];\
   BLOCCO  *bloc=blocchi; /* Serve per fregare l'interprete UIMX */\
\
\
   for ( conn=bloc[blocco].variabili_connesse, count=0;\
         count<bloc[blocco].variabili[variabile].connessioni;\
         conn = conn->succ )\
      if ( conn->var_interna == variabile )\
      {\
\
        lb = UxCreateLabel( "var_lb_conn",\
                            UxWidgetToSwidget(var_wid) );\
        wid = UxCreateWidget( lb );\
\
#ifndef DESIGN_TIME\
   UxPutContext( wid, (char *) UxVarWinContext );      \
#endif\
\
        sprintf( str, "       %s  %s",\
             bloc[conn->blocco_esterno].variabili[conn->var_esterna].nome,\
             bloc[conn->blocco_esterno].variabili[conn->var_esterna].descr );\
        UxPutLabelString( lb, str );\
        XtAddEventHandler( wid, ButtonPressMask | OwnerGrabButtonMask, False,\
                           var_press, (XtPointer)variabile );\
        XtAddEventHandler( wid, EnterWindowMask, False, var_enter, NULL );\
        XtAddEventHandler( wid, LeaveWindowMask, False, var_leave, NULL );\
        XtAddEventHandler( wid, ButtonReleaseMask, False,\
                           var_release, (XtPointer)variabile );\
\
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
\
\
no_show_connections( var_wid )\
Widget var_wid;\
{\
   Arg arg[2];\
   int i, num;\
   Widget *wids;\
\
\
   XtSetArg( arg[0], XmNnumChildren, &num );\
   XtSetArg( arg[1], XmNchildren, &wids );\
\
   XtGetValues( var_wid, arg, 2 );\
\
   for ( i=2; i<num; i++ )\
   {\
      if ( sel_var.status == SELEZIONATO && sel_var.wid == wids[i] )\
      {\
        sel_var.status = NON_SELEZIONATO;\
        var_menu_set();\
      }\
\
      XtDestroyWidget( wids[i] );\
   }\
}\
\
\
\
var_menu_set()\
{\
   Arg arg[1];\
   int num;\
   BLOCCO  *bloc=blocchi; /* Serve per fregare l'interprete UIMX */\
\
\
/* set (non)attivo nel popup l'item edit descrizione */\
   if ( sel_var.status == NON_SELEZIONATO  )\
   {\
        sensitive( ingPopupedit, False );\
        sensitive( uscPopupedit, False );\
   }\
   else\
   {\
        if ( bloc[blocco].variabili[sel_var.var].tipo == INGRESSO )\
        {\
          sensitive( ingPopupedit, True );\
          sensitive( uscPopupedit, False );\
        }\
        else\
        {\
          sensitive( ingPopupedit, False );\
          sensitive( uscPopupedit, True );\
        }\
   }\
\
/*set (non)attivo nel popup e nel bar menu gli di show conn */\
   if ( sel_var.status == NON_SELEZIONATO  ||  sel_var.conn  ||\
        !(bloc[blocco].variabili[sel_var.var].connessioni) )\
   {\
      XmToggleButtonSetState( UxGetWidget(varShowConnBt), False, False );\
      sensitive( varShowConnBt, False );\
      XmToggleButtonSetState( UxGetWidget(ingPopupShowConnBt), False, False );\
      sensitive( ingPopupShowConnBt, False );\
      XmToggleButtonSetState( UxGetWidget(uscPopupShowConnBt), False, False );\
      sensitive( uscPopupShowConnBt, False );\
   }\
   else\
   {\
      sensitive( varShowConnBt, True );\
  \
      if ( bloc[blocco].variabili[sel_var.var].tipo == INGRESSO )\
      {\
         sensitive( ingPopupShowConnBt, True );\
         sensitive( uscPopupShowConnBt, False );\
      }\
      else\
      {\
         sensitive( uscPopupShowConnBt, True );\
         sensitive( ingPopupShowConnBt, False );\
      }\
\
\
      XtSetArg( arg[0], XmNnumChildren, &num );\
      XtGetValues( XtParent(sel_var.wid), arg, 1 );\
\
      if ( num > 2 )\
      {\
        XmToggleButtonSetState( UxGetWidget(varShowConnBt), True, False );\
\
        if ( bloc[blocco].variabili[sel_var.var].tipo == INGRESSO )\
        {\
          XmToggleButtonSetState( UxGetWidget(ingPopupShowConnBt), True, False );\
          XmToggleButtonSetState( UxGetWidget(uscPopupShowConnBt), False, False );\
        }\
        else\
        {\
          XmToggleButtonSetState( UxGetWidget(ingPopupShowConnBt), False, False );\
          XmToggleButtonSetState( UxGetWidget(uscPopupShowConnBt), True, False );\
        }\
\
     }\
      else\
      {\
        XmToggleButtonSetState( UxGetWidget(varShowConnBt), False, False );\
        XmToggleButtonSetState( UxGetWidget(ingPopupShowConnBt), False, False );\
        XmToggleButtonSetState( UxGetWidget(uscPopupShowConnBt), False, False );\
      }\
   }\
\
\
/*set (non)attivo nel popup e nel bar menu gli item di delete conn */\
   if ( sel_var.status == NON_SELEZIONATO || !sel_var.conn )\
   {\
     sensitive( ingPopupDelConnBt, False );\
     sensitive( uscPopupDelConnBt, False );\
     sensitive( varDelConnBt, False );\
   }\
   else \
   {\
      sensitive( varDelConnBt, True );\
\
      if (bloc[blocco].variabili[sel_var.var].tipo == INGRESSO )\
      {\
         sensitive( ingPopupDelConnBt, True );\
         sensitive( uscPopupDelConnBt, False );\
      }\
      else\
      {\
         sensitive( ingPopupDelConnBt, False );\
         sensitive( uscPopupDelConnBt, True );\
      }\
   }\
\
    \
}\
\
\
\
\
show_all_conn( list, tipo, on )\
swidget list;\
TIPO_VAR tipo;\
int on;\
{\
   Arg arg[2];\
   int i, num, ind_wid, ind_var;\
   Widget *wids, *rc;\
   BLOCCO *bloc=blocchi;\
\
\
   XtSetArg( arg[0], XmNchildren, &wids );\
\
   XtGetValues( UxGetWidget(list), arg, 1 );\
\
\
   for ( ind_wid=ind_var=0; ind_var<bloc[blocco].num_variabili; ind_var++ )\
   {\
     if ( ( bloc[blocco].variabili[ind_var].tipo == tipo  ||\
            tipo == USCITA && bloc[blocco].variabili[ind_var].tipo == STATO\
          )\
            && filtra( bloc[blocco].variabili[ind_var].nome )\
        )\
     {\
         if ( ! (bloc[blocco].variabili[ind_var].connessioni) )\
            ind_wid++;\
         else\
         {\
            XtSetArg( arg[0], XmNchildren, &rc );\
            XtGetValues( wids[ind_wid], arg, 1 );\
\
            if ( on )\
            {\
              XtSetArg( arg[0], XmNnumChildren, &num );\
              XtGetValues( *rc, arg, 1 );\
              if ( num == 2 )\
                 show_connections( ind_var, *rc );\
            }\
            else\
              no_show_connections( *rc );\
\
            ind_wid++;\
         }\
      }\
   }\
\
   var_menu_set();\
}\
\
\
\
create_gost_win_gc()\
{\
\
  gost_win_gc  = XCreateGC( display, root, 0, NULL );\
\
  XSetFunction( display, gost_win_gc, GXxor );\
  XSetSubwindowMode( display, gost_win_gc, IncludeInferiors );\
  XSetForeground( display, gost_win_gc, ~0 );\
  XSetLineAttributes( display, gost_win_gc, 0, LineSolid, CapButt, JoinMiter );\
\
}\
\
\
\
add_var_list_event_handler(wid)\
Widget wid;\
{\
  XtAddEventHandler( wid, LeaveWindowMask, False, list_leave, NULL );\
  XtAddEventHandler( wid, EnterWindowMask | ButtonReleaseMask,\
                     False, list_enter, NULL );\
  XtAddEventHandler( wid, ButtonReleaseMask, False, var_release, 0 );\
}\
\
\
\
\
event_loop_for_conn(w)\
Widget w;\
{\
  int     fine=False;\
  char    *name;\
  XEvent  event;\
  Widget  wid;\
  swidget swid;\
  char list_name[10];\
  BLOCCO *bloc=blocchi;\
  Cursor cursor;\
\
\
   get_pixmap_cursor( "move", &cursor );\
\
   XGrabPointer( XtDisplay(w), XtWindow(w), True,\
                 Button2MotionMask | ButtonReleaseMask |\
                 LeaveWindowMask | EnterWindowMask,\
                 GrabModeSync, GrabModeAsync,\
                 None, cursor, CurrentTime );\
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
               wid = XtWindowToWidget(display, event.xbutton.window);\
               if ( wid  &&  wid != w  &&\
                    UxIsValidSwidget(swid = UxWidgetToSwidget(wid))  &&\
                    (name = UxGetName(swid))  &&  !strcmp( name, "var_lb" )\
                  )\
                 UxDispatchEvent(&event);\
               else\
               {\
                 err_level = ERROR;\
                 errore( "ERROR out of window" );\
                 move_var.status = NON_SELEZIONATO;\
               }\
\
               break;\
\
         case EnterNotify:\
         case LeaveNotify:\
               wid = XtWindowToWidget(display, event.xcrossing.window);\
               if ( wid  &&  UxIsValidSwidget(swid = UxWidgetToSwidget(wid)) &&\
                    (name = UxGetName(swid))  && \
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
   XUngrabPointer(display, CurrentTime);\
\
}\
\
\
\
\
#ifndef DESIGN_TIME\
\
set_var_win_list_context(w, salva_context)\
Widget w;\
char   **salva_context;\
{\
   swidget swid;\
\
   swid            = UxWidgetToSwidget(w);\
   *salva_context  = (char *) UxVarWinContext;\
   UxVarWinContext = (_UxCvarWin *) UxGetContext(swid);\
}\
\
\
\
reset_var_win_list_context(salva_context)\
char *salva_context;\
{\
   UxVarWinContext = (_UxCvarWin *) salva_context;\
}\
\
#endif\
\
\
\
\
set_var_pixmap( w, nome )\
Widget w;\
char   *nome;\
{\
\
   Arg arg;\
   Widget *wids;\
\
   XtSetArg( arg, XmNchildren, &wids );\
   XtGetValues( XtParent(w), &arg, 1 );\
\
   UxPutLabelPixmap( UxWidgetToSwidget(*wids), nome );\
\
}\
\
\
\
visualizza_connessione( w, var )\
Widget w;\
int    var;\
{\
   Arg arg;\
   int num;\
   char *salva_context;\
   char *path_pxm;\
   char nome_file[1024];\
\
 \
   XtSetArg( arg, XmNnumChildren, &num );\
   XtGetValues( XtParent(w), &arg, 1 );\
\
   if ( num > 2 )\
     no_show_connections( XtParent(w) );\
  \
   show_connections( var, XtParent(w) );\
   \
   var_menu_set();\
\
\
   set_var_win_list_context( move_var.wid, &salva_context );\
 \
   XtSetArg( arg, XmNnumChildren, &num );\
   XtGetValues( XtParent(move_var.wid), &arg, 1 );\
\
   if ( num > 2 )\
     no_show_connections( XtParent(move_var.wid) );\
  \
   show_connections( move_var.var, XtParent(move_var.wid) );\
\
   var_menu_set();\
\
   reset_var_win_list_context( salva_context );\
\
\
   if ( path_pxm = getenv( "LEGOCAD_ICO" ) )\
   {\
     strcpy( nome_file, path_pxm );\
     strcat( nome_file, "/" );\
   }\
   else\
     strcpy( nome_file, "" );\
   strcat( nome_file, "conn.bmp" );\
   set_var_pixmap( w, nome_file );\
   set_var_pixmap( move_var.wid, nome_file );\
\
}\
\
\
\
tenta_connessione( bl1, var1, bl2, var2 )\
int bl1, var1, bl2, var2;\
{\
   extern MESSAGE message;\
   extern int changes_in_F01;\
   int dummy,i,j,totale_connessioni;\
   BLOCCO *bloc = blocchi;\
\
   char str[100];\
\
   CONN *conn;\
\
\
   if ( bloc[bl1].variabili[var1].tipo == INGRESSO  &&\
        bloc[bl2].variabili[var2].tipo == INGRESSO\
           ||\
        bloc[bl1].variabili[var1].tipo != INGRESSO &&\
        bloc[bl2].variabili[var2].tipo != INGRESSO\
      )\
   {\
      err_level = ERROR;\
      errore( "ERROR, connection is not possible\n between two variables of same type" );\
      return(0);\
   }\
\
\
   if ( bloc[bl1].variabili[var1].tipo != INGRESSO )\
   {\
      dummy = bl1;\
      bl1   = bl2;\
      bl2   = dummy;\
\
      dummy = var1;\
      var1  = var2;\
      var2  = dummy;\
   }\
\
\
   if ( bloc[bl1].variabili[var1].connessioni )\
   {\
      err_level = ERROR;\
      errore( "ERROR variable already connected %s",bloc[bl1].variabili[var1].nome );\
      return(0);\
   }\
\
/* verifico che non sia gia' stata effettuata una connessione\
   della uscitacon qualche altro ingresso dello stesso blocco \
*/\
   totale_connessioni = 0;\
   if( bloc[bl1].variabili_connesse )\
   {\
      printf("\nblocco in esame %s\n",bloc[bl1].label);\
      for(i=0;i<bloc[bl1].num_variabili;i++)\
      {\
         printf("variabile in esame %s n.connessioni %d\n",bloc[bl1].variabili[i].nome,\
bloc[bl1].variabili[i].connessioni);\
         if(bloc[bl1].variabili[i].connessioni )\
         {\
            totale_connessioni += bloc[bl1].variabili[i].connessioni;\
         }\
      }\
   }\
\
   printf("totale connessioni del blocco = %d\n",totale_connessioni);\
\
   conn = bloc[bl1].variabili_connesse;\
   for(i=0;i<totale_connessioni;i++)\
   {\
      if( conn->blocco_esterno == bl2 && conn->var_esterna == var2)\
      {\
        printf("la variabile di uscita proposta e' gia' stata connessa con questo blocco \n");\
        err_level = ERROR;\
        errore( "ERROR  %s variables already connetcted \nwith this block",bloc[bl2].variabili[var2].nome);\
        return(0);\
      }\
      conn = conn->succ;\
   }\
\
   changes_in_F01 = True;   \
   make_connessione ( bl1, var1, bl2, var2 );\
\
}\
\
\
\
clear_list( list )\
swidget list;\
{\
   Arg arg[4];\
   Cardinal i, num,narg;\
   WidgetList wids;\
\
   narg = 0;\
   XtSetArg( arg[narg], XmNnumChildren, &num );narg++;\
   XtSetArg( arg[narg], XmNchildren, &wids );narg++;\
   XtGetValues( UxWidgetToSwidget(list), arg, narg );\
\
   sel_var.status = NON_SELEZIONATO;\
\
   for ( i=0; i<num; i++ )\
     XtDestroyWidget( wids[i] );\
}\
\
\
\
put_var_win_title( str1, str2, descr )\
char *str1;\
char *str2;\
char *descr;\
{\
  char str[100];\
\
  strcpy( str, "Block:  " );\
  strcat( str, str1 );\
  strcat( str, str2 );\
  strcat( str, " ");\
  strcat( str, descr);  \
  UxPutLabelString( varTitleLb, str );\
}\
\
\
\
num_conn( w )\
Widget w;\
{\
  Arg    arg;\
  Widget *wids;\
  int    i;\
\
\
  XtSetArg( arg, XmNchildren, &wids );\
  XtGetValues( XtParent(w), &arg, 1 );\
\
  for ( i=0; ; i++ ) \
    if ( wids[i] == w )\
      break;\
\
  if ( i <= 1)\
    return(0);\
  else\
    return(i-1);\
}\
\
\
\
del_conn_cb(w)\
Widget w;\
{\
  extern QUESTION question;\
\
  question = QST_DEL_CONN;\
\
  questionDB_activate( " Delete connection? " );\
\
  del_wid = w;\
}\
\
\
\
del_conn_qst_cb()\
{\
   extern int changes_in_F01;\
   Widget sec_w;\
   int sec_bl, sec_var;\
   char *salva_context1, *salva_context2;\
   char *path_pxm;\
   char nome_file[1024];\
   BLOCCO *bloc=blocchi;\
\
\
   if ( path_pxm = getenv( "LEGOCAD_ICO" ) )\
   {\
     strcpy( nome_file, path_pxm );\
     strcat ( nome_file, "/" );\
   }\
   else\
     strcpy( nome_file, "" );\
   strcat ( nome_file, "void.bmp" );\
\
\
   set_var_win_list_context(del_wid, &salva_context1);\
\
   search_sec_conn_wid( &sec_w, &sec_bl, &sec_var );\
\
   changes_in_F01 = True;\
   delete_connessione( blocco, sel_var.var, sel_var.conn );\
\
   set_var_win_list_context(del_wid, &salva_context1);\
\
   if ( !bloc[blocco].variabili[sel_var.var].connessioni )\
     set_var_pixmap( sel_var.wid, nome_file );\
\
\
   no_show_connections( XtParent(sel_var.wid) );\
   show_connections( sel_var.var, XtParent(sel_var.wid) );\
\
   if ( sec_w )\
   {\
      if ( !bloc[sec_bl].variabili[sec_var].connessioni )\
         set_var_pixmap( sec_w, nome_file );\
  \
      set_var_win_list_context(sec_w, &salva_context2);\
\
      no_show_connections( XtParent(sec_w) );\
      show_connections( sec_var, XtParent(sec_w) );\
\
      if ( sel_var.wid == sec_w )\
        var_menu_set();\
\
      reset_var_win_list_context(salva_context2);\
   }\
\
   reset_var_win_list_context(salva_context1);\
\
}\
\
\
\
search_sec_conn_wid ( w, bb, var )\
Widget *w;\
int    *bb, *var;\
{\
   BLOCCO *bloc=blocchi;\
   VAR_WIN_TYPE *cor_win;\
   CONN *cor_conn, *sec_cor_conn;\
   TIPO_VAR tipo;\
   Widget *fr_ch, *rc_ch, *wids;\
   Arg arg[2];\
   int i, count, ind_wid, ind_var, num, sec_var, sec_bl;\
   char *salva_context;\
   char nomeappo[100];\
\
   extern VAR_WIN_TYPE  *var_win_list;\
\
\
   *w = NULL;\
\
   for ( count=0, cor_conn=bloc[blocco].variabili_connesse;    \
         ;\
         cor_conn=cor_conn->succ\
       )\
      if ( cor_conn->var_interna == sel_var.var )\
         if ( ++count == sel_var.conn )\
            break;\
\
\
   for ( cor_win=var_win_list; cor_win; cor_win=cor_win->succ )\
      if ( cor_win->bloc == cor_conn->blocco_esterno )\
         break;\
\
\
   if ( cor_win )\
   {\
/* recupero i dati della variabile connessa */\
      sec_var = cor_conn->var_esterna;\
      sec_bl  = cor_conn->blocco_esterno;\
\
      tipo = bloc[sec_bl].variabili[sec_var].tipo;\
\
/* switch del context per recupera l'indice del widget della variabile connessa \
   la quale deve superare anche il filtro \
*/ \
      set_var_win_list_context(UxGetWidget(cor_win->swid), &salva_context);\
\
      for ( ind_wid=(-1), ind_var=0; ind_var<=sec_var; ind_var++ )\
         if ( ( bloc[sec_bl].variabili[ind_var].tipo == tipo  ||\
                tipo == USCITA && bloc[sec_bl].variabili[ind_var].tipo == STATO\
              )\
               &&\
              filtra( bloc[sec_bl].variabili[sec_var].nome )\
\
            )\
            ind_wid ++;\
\
\
/* se e' visualizzata allora recupero lo widget */       \
      if( ind_wid >= 0 )\
      {\
         XtSetArg( arg[0], XmNchildren, &wids );\
         if ( tipo == INGRESSO )\
           XtGetValues( UxGetWidget(ingList), arg, 1 );\
         else\
           XtGetValues( UxGetWidget(uscList), arg, 1 );\
\
         XtSetArg( arg[0], XmNchildren, &fr_ch );\
         XtGetValues( wids[ind_wid], arg, 1 );\
 \
         XtSetArg( arg[0], XmNnumChildren, &num );\
         XtSetArg( arg[1], XmNchildren, &rc_ch );\
         XtGetValues( *fr_ch, arg, 2 );\
\
         *w   = rc_ch[1];\
         *bb  = cor_conn->blocco_esterno;\
         *var = cor_conn->var_esterna;      \
      }\
      else\
          *w = NULL;\
\
/* reset del context */\
      reset_var_win_list_context(salva_context);\
   }\
}\
\
\
set_bloc( swid, bloc )\
swidget swid;\
int bloc;\
{\
   char *salva_context;\
\
   set_var_win_list_context(UxGetWidget(swid), &salva_context);\
\
   blocco = bloc;\
\
   reset_var_win_list_context(salva_context);\
}\
\
\
var_edit_descr(int ind_bloc,int ind_var)\
{\
  extern swidget EditVarDescr;\
  char descrizione[100];\
  BLOCCO *bloc = blocchi;\
\
  strcpy(descrizione,bloc[ind_bloc].variabili[ind_var].descr);\
\
\
  fintavarWin = varWin;\
  create_EditVarDescr();\
  UxPopupInterface(EditVarDescr,no_grab);  \
  UxPutTextString(EditVarDescr,descrizione);\
\
}\
\
\
void set_new_var_descr(swidget UxThisWidget,char *new_descr)\
{\
   extern int changes_in_F01;\
   char entry[200];\
   XmString item;\
       \
   BLOCCO *bloc = blocchi;  \
#ifndef DESIGN_TIME\
_UxCvarWin      *UxSaveCtx, *UxContext;\
UxSaveCtx = UxVarWinContext;\
UxVarWinContext = UxContext =\
                        (_UxCvarWin *) UxGetContext( UxThisWidget );\
#endif\
   printf("set_new_descr -> [%s]\n",new_descr);\
   strcpy( bloc[ indice_blocco ].variabili[ indice_variabile ].descr, new_descr);\
\
   changes_in_F01 = True;\
\
   clear_list( ingList );\
   clear_list( uscList );\
   add_variables();\
   var_menu_set();\
#ifndef DESIGN_TIME\
 UxVarWinContext = UxSaveCtx;\
#endif\
}\
\
/* refresh_lista\
 *\
 * effettua il refresh completo della lista delle veriabili\
 * sia di ingresso che di uscita\
 */\
refresh_lista()\
{\
   clear_list(ingList);\
   clear_list(uscList);\
   add_variables();\
   var_menu_set();\
}\
\
/* OptFilterCB\
 * callback attivazione filtro dopo la selezione nel\
 * option menu di filtri\
 *\
 */\
int OptFilterCB(Widget w,int ind_filtro, XmAnyCallbackStruct *call_data)\
{\
#ifndef DESIGN_TIME\
   _UxCvarWin      *UxSaveCtx, *UxContext;\
   swidget UxThisWidget;\
#endif\
\
\
   extern FILTRI *filtri[];      /* ed anche questa  e saranno definite nel main */\
   int i;\
   char filter_label[100];\
\
#ifndef DESIGN_TIME\
   UxSaveCtx = UxVarWinContext;\
   UxThisWidget = UxWidgetToSwidget( w );\
   UxSaveCtx = UxVarWinContext;\
   UxVarWinContext = UxContext = (_UxCvarWin *) UxGetContext( UxThisWidget   );\
#endif\
\
\
/* inizializzo la variabile globale e il filtro attuale */\
   filtro_attivo = True;\
   filtro_attuale = filtri[ind_filtro];\
\
   refresh_lista();\
\
/* costruisco la filter label */\
   strcpy(filter_label,"Filter on ->");\
   for(i=0;i<filtro_attuale->num_var;i++)\
   {\
         strcat(filter_label,filtro_attuale->var[i] );\
         strcat(filter_label,",");\
/* elimino la ultima vrigola */\
         filter_label[ strlen(filter_label) ] = 0;\
   }\
    \
   UxPutLabelString(label2,filter_label);\
\
#ifndef DESIGN_TIME\
   UxVarWinContext = UxSaveCtx;\
#endif\
\
}\
\
void add_filt_opt_butt(swidget w)\
{\
\
#ifndef DESIGN_TIME\
   _UxCvarWin      *UxSaveCtx, *UxContext;\
   swidget UxThisWidget;\
#endif\
\
   extern int num_filtri;           \
   extern FILTRI *filtri[];    \
\
   swidget *OptFilterButt;\
   int i,j;\
   char label_butt[20];\
   extern int ind_filt_default;\
\
#ifndef DESIGN_TIME\
   UxSaveCtx = UxVarWinContext;\
   UxThisWidget =  w ;\
   UxSaveCtx = UxVarWinContext;\
   UxVarWinContext = UxContext = (_UxCvarWin *) UxGetContext( UxThisWidget   );\
#endif\
   \
   if(num_filtri)\
   	OptFilterButt = (swidget *)calloc( num_filtri,sizeof(swidget) );\
\
\
   for(i=0; i < num_filtri; i++)\
   {\
   /*creo i push button */\
\
      strcpy(label_butt,filtri[i]->nome_filtro);\
      OptFilterButt[i] = UxCreatePushButton(label_butt,filterPane);\
      UxPutLabelString(OptFilterButt[i],label_butt);\
      UxCreateWidget(OptFilterButt[i]);\
\
/* e definisco la callback */\
      UxAddCallback(OptFilterButt[i],XmNactivateCallback,OptFilterCB,i);\
#ifndef DESIGN_TIME\
      UxPutContext( OptFilterButt[i], (char *) UxVarWinContext );\
#endif\
   }\
   button_already_def = True;\
\
   \
/* setto la voce di default del menu */      \
    \
    if(ind_filt_default)\
    {\
       set_something(UxGetWidget(filterSel),XmNmenuHistory,UxGetWidget(OptFilterButt[ind_filt_default-1]));  \
       filtro_attivo = True;\
       filtro_attuale = filtri[ind_filt_default-1];\
    }\
    else\
       filtro_attivo = False;\
\
   if(num_filtri)\
	free(OptFilterButt);\
\
    refresh_lista();\
                  \
#ifndef DESIGN_TIME\
   UxVarWinContext = UxSaveCtx;\
#endif\
}\
\
\
\

*varWin.name: varWin
*varWin.unitType: "pixels"
*varWin.x: 793
*varWin.y: 278
*varWin.width: 555
*varWin.height: 503

*varMenuBar.class: rowColumn
*varMenuBar.parent: varWin
*varMenuBar.static: true
*varMenuBar.name: varMenuBar
*varMenuBar.rowColumnType: "menu_bar"
*varMenuBar.menuAccelerator: "<KeyUp>F10"

*varFilePane.class: rowColumn
*varFilePane.parent: varMenuBar
*varFilePane.static: true
*varFilePane.name: varFilePane
*varFilePane.rowColumnType: "menu_pulldown"

*varLoadBt.class: pushButton
*varLoadBt.parent: varFilePane
*varLoadBt.static: true
*varLoadBt.name: varLoadBt
*varLoadBt.labelString: "Load"
*varLoadBt.activateCallback: {\
   VAR_WIN_TYPE *cor;\
   BLOCCO *bloc=blocchi;\
\
   extern SELECTION bl_selezionati;\
   extern VAR_WIN_TYPE   *var_win_list;\
\
\
   if ( bl_selezionati.num != 1 )\
   {\
\
      err_level = ERROR;\
      if ( bl_selezionati.num )\
         errore( "selezionati troppi blocchi");\
      else\
         errore("nessun blocco selezionato");\
\
   }\
   else if ( blocco != bl_selezionati.pos[0] )\
   {\
      for ( cor=var_win_list; cor; cor=cor->succ )\
         if ( cor->bloc ==  bl_selezionati.pos[0] )\
            break;\
\
      if ( cor )\
         XRaiseWindow( display, XtWindow(XtParent(UxGetWidget(cor->swid))) );\
      else\
      {\
         for ( cor=var_win_list; cor; cor=cor->succ )\
            if ( cor->bloc ==  blocco )\
              break;\
         blocco      = bl_selezionati.pos[0];\
         cor->bloc   = blocco;\
         clear_list( ingList );\
         clear_list( uscList );\
         add_variables();\
         put_var_win_title( bloc[blocco].sigla_modulo, bloc[blocco].sigla_blocco, bloc[blocco].descr_blocco);\
      }\
   }\
\
}
*varLoadBt.mnemonic: "L"

*varCloseBt.class: pushButton
*varCloseBt.parent: varFilePane
*varCloseBt.static: true
*varCloseBt.name: varCloseBt
*varCloseBt.labelString: "Close"
*varCloseBt.mnemonic: "C"
*varCloseBt.activateCallback: {\
  VAR_WIN_TYPE *cor, *temp;\
  extern VAR_WIN_TYPE   *var_win_list;\
\
  if ( var_win_list )\
\
    if ( var_win_list->bloc == blocco )\
    {\
\
       temp    = var_win_list;\
       var_win_list = var_win_list->succ;\
       free( temp );\
\
    }\
    else\
    {\
\
       for ( cor=var_win_list; cor->succ; cor=cor->succ )\
         if ( blocco == ((VAR_WIN_TYPE*)cor->succ)->bloc )\
           break;\
\
       temp      = cor->succ;\
       cor->succ = ((VAR_WIN_TYPE*)cor->succ)->succ;\
       free( temp );\
\
    }\
\
\
  UxDestroyInterface( varWin );\
}\


*varEditorPane.class: rowColumn
*varEditorPane.parent: varMenuBar
*varEditorPane.static: true
*varEditorPane.name: varEditorPane
*varEditorPane.rowColumnType: "menu_pulldown"

*varShowConnBt.class: toggleButton
*varShowConnBt.parent: varEditorPane
*varShowConnBt.static: true
*varShowConnBt.name: varShowConnBt
*varShowConnBt.labelString: "Show connections"
*varShowConnBt.mnemonic: "S"
*varShowConnBt.valueChangedCallback: {\
  BLOCCO *bloc=blocchi;\
\
  if ( ((XmToggleButtonCallbackStruct*)UxCallbackArg)->set )\
       show_connections(sel_var.var, XtParent(sel_var.wid));\
  else\
    no_show_connections( XtParent(sel_var.wid) );\
\
  if ( bloc[blocco].variabili[sel_var.var].tipo == INGRESSO )\
    XmToggleButtonSetState( UxGetWidget(ingPopupShowConnBt),\
                            ((XmToggleButtonCallbackStruct*)UxCallbackArg)->set,\
                            False\
                          );\
  else\
    XmToggleButtonSetState( UxGetWidget(uscPopupShowConnBt),\
                            ((XmToggleButtonCallbackStruct*)UxCallbackArg)->set,\
                            False\
                          ); \
}

*varDelConnBt.class: pushButton
*varDelConnBt.parent: varEditorPane
*varDelConnBt.static: true
*varDelConnBt.name: varDelConnBt
*varDelConnBt.labelString: "Delete connection"
*varDelConnBt.mnemonic: "D"
*varDelConnBt.activateCallback: { del_conn_cb(UxWidget); }

*varViewPane.class: rowColumn
*varViewPane.parent: varMenuBar
*varViewPane.static: true
*varViewPane.name: varViewPane
*varViewPane.rowColumnType: "menu_pulldown"

*varIngConnBt.class: toggleButton
*varIngConnBt.parent: varViewPane
*varIngConnBt.static: true
*varIngConnBt.name: varIngConnBt
*varIngConnBt.labelString: "Show input connections"
*varIngConnBt.mnemonic: "i"
*varIngConnBt.valueChangedCallback: if ( ((XmToggleButtonCallbackStruct*)UxCallbackArg)->set )\
  show_all_conn( ingList, INGRESSO, True );\
else\
  show_all_conn( ingList, INGRESSO, False );\


*varUscConnBt.class: toggleButton
*varUscConnBt.parent: varViewPane
*varUscConnBt.static: true
*varUscConnBt.name: varUscConnBt
*varUscConnBt.labelString: "Show output connections"
*varUscConnBt.mnemonic: "o"
*varUscConnBt.valueChangedCallback: if ( ((XmToggleButtonCallbackStruct*)UxCallbackArg)->set )\
  show_all_conn( uscList, USCITA, True );\
else\
  show_all_conn( uscList, USCITA, False );\


*varFileCascade.class: cascadeButton
*varFileCascade.parent: varMenuBar
*varFileCascade.static: true
*varFileCascade.name: varFileCascade
*varFileCascade.labelString: "File"
*varFileCascade.mnemonic: "F"
*varFileCascade.subMenuId: "varFilePane"

*varEditCascade.class: cascadeButton
*varEditCascade.parent: varMenuBar
*varEditCascade.static: true
*varEditCascade.name: varEditCascade
*varEditCascade.labelString: "Edit"
*varEditCascade.subMenuId: "varEditorPane"
*varEditCascade.mnemonic: "E"

*varViewCascade.class: cascadeButton
*varViewCascade.parent: varMenuBar
*varViewCascade.static: true
*varViewCascade.name: varViewCascade
*varViewCascade.labelString: "View"
*varViewCascade.mnemonic: "V"
*varViewCascade.subMenuId: "varViewPane"

*varForm.class: form
*varForm.parent: varWin
*varForm.static: true
*varForm.name: varForm

*varTitleLb.class: label
*varTitleLb.parent: varForm
*varTitleLb.static: true
*varTitleLb.name: varTitleLb
*varTitleLb.x: 5
*varTitleLb.y: 10
*varTitleLb.width: 545
*varTitleLb.height: 35
*varTitleLb.leftAttachment: "attach_form"
*varTitleLb.leftOffset: 5
*varTitleLb.rightAttachment: "attach_form"
*varTitleLb.rightOffset: 5
*varTitleLb.topAttachment: "attach_form"
*varTitleLb.topOffset: 5
*varTitleLb.fontList: "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1"

*filterBox.class: form
*filterBox.parent: varForm
*filterBox.static: true
*filterBox.name: filterBox
*filterBox.resizePolicy: "resize_any"
*filterBox.x: 20
*filterBox.y: 80
*filterBox.width: 115
*filterBox.height: 55
*filterBox.leftAttachment: "attach_form"
*filterBox.leftOffset: 20
*filterBox.topAttachment: "attach_widget"
*filterBox.topOffset: 10
*filterBox.topWidget: "varTitleLb"
*filterBox.rightAttachment: "attach_form"
*filterBox.rightOffset: 20

*filterLb.class: label
*filterLb.parent: filterBox
*filterLb.static: true
*filterLb.name: filterLb
*filterLb.x: 0
*filterLb.y: 0
*filterLb.width: 180
*filterLb.height: 20
*filterLb.leftAttachment: "attach_form"
*filterLb.leftOffset: 0
*filterLb.rightAttachment: "attach_none"
*filterLb.rightOffset: 0
*filterLb.topAttachment: "attach_form"
*filterLb.topOffset: 0
*filterLb.alignment: "alignment_beginning"
*filterLb.labelString: "Filter"
*filterLb.marginLeft: 10

*filterSel.class: rowColumn
*filterSel.parent: filterBox
*filterSel.static: true
*filterSel.name: filterSel
*filterSel.rowColumnType: "menu_option"
*filterSel.subMenuId: "filterPane"
*filterSel.bottomAttachment: "attach_form"
*filterSel.bottomOffset: 0
*filterSel.leftAttachment: "attach_form"
*filterSel.leftOffset: 0
*filterSel.rightAttachment: "attach_none"
*filterSel.rightOffset: 0
*filterSel.topAttachment: "attach_widget"
*filterSel.topOffset: 0
*filterSel.topWidget: "filterLb"
*filterSel.y: 25
*filterSel.marginHeight: 0
*filterSel.marginWidth: 0
*filterSel.spacing: 0
*filterSel.x: 5
*filterSel.createCallback: {\
\
}
*filterSel.packing: "pack_column"
*filterSel.orientation: "vertical"

*filterPane.class: rowColumn
*filterPane.parent: filterSel
*filterPane.static: false
*filterPane.name: filterPane
*filterPane.rowColumnType: "menu_pulldown"
*filterPane.width: 120
*filterPane.packing: "pack_column"
*filterPane.menuHistory: ""

*defFil.class: pushButton
*defFil.parent: filterPane
*defFil.static: true
*defFil.name: defFil
*defFil.labelString: "No Filter"
*defFil.mnemonic: "N"
*defFil.activateCallback: {\
\
/*printf("disattiva tutti i filtri\n");*/\
\
UxPutLabelString(label2,"                                     ");\
\
filtro_attivo = False;\
filtro_attuale = NULL;\
\
refresh_lista();\
}

*label2.class: label
*label2.parent: filterBox
*label2.static: true
*label2.name: label2
*label2.x: 140
*label2.y: 20
*label2.width: 360
*label2.height: 30
*label2.labelString: ""

*varFrame.class: frame
*varFrame.parent: varForm
*varFrame.static: true
*varFrame.name: varFrame
*varFrame.x: 10
*varFrame.y: 155
*varFrame.width: 540
*varFrame.height: 310
*varFrame.bottomAttachment: "attach_form"
*varFrame.bottomOffset: 5
*varFrame.leftAttachment: "attach_form"
*varFrame.leftOffset: 5
*varFrame.rightAttachment: "attach_form"
*varFrame.rightOffset: 5
*varFrame.topAttachment: "attach_widget"
*varFrame.topOffset: 10
*varFrame.topWidget: "filterBox"

*panedWindow1.class: panedWindow
*panedWindow1.parent: varFrame
*panedWindow1.static: true
*panedWindow1.name: panedWindow1
*panedWindow1.x: 15
*panedWindow1.y: 155
*panedWindow1.width: 565
*panedWindow1.height: 155

*ingForm.class: form
*ingForm.parent: panedWindow1
*ingForm.static: true
*ingForm.name: ingForm
*ingForm.resizePolicy: "resize_none"
*ingForm.x: 15
*ingForm.y: 10
*ingForm.width: 535
*ingForm.height: 160

*ingLb.class: label
*ingLb.parent: ingForm
*ingLb.static: true
*ingLb.name: ingLb
*ingLb.x: 25
*ingLb.y: 185
*ingLb.width: 150
*ingLb.height: 25
*ingLb.labelString: "Input"
*ingLb.alignment: "alignment_beginning"
*ingLb.leftAttachment: "attach_form"
*ingLb.leftOffset: 20
*ingLb.rightAttachment: "attach_form"
*ingLb.rightOffset: 20
*ingLb.topAttachment: "attach_form"
*ingLb.topOffset: 0

*ingSW.class: scrolledWindow
*ingSW.parent: ingForm
*ingSW.static: true
*ingSW.name: ingSW
*ingSW.scrollingPolicy: "automatic"
*ingSW.x: 5
*ingSW.y: 25
*ingSW.width: 215
*ingSW.height: 230
*ingSW.bottomAttachment: "attach_form"
*ingSW.bottomOffset: 5
*ingSW.leftAttachment: "attach_form"
*ingSW.leftOffset: 5
*ingSW.rightAttachment: "attach_form"
*ingSW.rightOffset: 5
*ingSW.topAttachment: "attach_widget"
*ingSW.topOffset: 0
*ingSW.topWidget: "ingLb"

*ingList.class: rowColumn
*ingList.parent: ingSW
*ingList.static: true
*ingList.name: ingList
*ingList.x: 7
*ingList.y: 2
*ingList.width: 475
*ingList.height: 100
*ingList.adjustMargin: "true"
*ingList.adjustLast: "true"
*ingList.entryAlignment: "alignment_end"
*ingList.isAligned: "true"
*ingList.packing: "pack_tight"
*ingList.spacing: 0

*ingPopup.class: rowColumn
*ingPopup.parent: ingList
*ingPopup.static: true
*ingPopup.name: ingPopup
*ingPopup.rowColumnType: "menu_popup"
*ingPopup.menuAccelerator: "<KeyUp>F4"

*ingPopupLb.class: label
*ingPopupLb.parent: ingPopup
*ingPopupLb.static: true
*ingPopupLb.name: ingPopupLb
*ingPopupLb.labelString: "INPUT VARIABLES"

*separator32.class: separator
*separator32.parent: ingPopup
*separator32.static: true
*separator32.name: separator32

*ingPopupedit.class: pushButton
*ingPopupedit.parent: ingPopup
*ingPopupedit.static: true
*ingPopupedit.name: ingPopupedit
*ingPopupedit.labelString: "Edit Descr"
*ingPopupedit.mnemonic: "E"
*ingPopupedit.activateCallback: var_edit_descr(indice_blocco,indice_variabile);

*ingPopupShowConnBt.class: toggleButton
*ingPopupShowConnBt.parent: ingPopup
*ingPopupShowConnBt.static: true
*ingPopupShowConnBt.name: ingPopupShowConnBt
*ingPopupShowConnBt.labelString: "Show connection"
*ingPopupShowConnBt.mnemonic: "S"
*ingPopupShowConnBt.valueChangedCallback: {\
  if ( ((XmToggleButtonCallbackStruct*)UxCallbackArg)->set )\
    show_connections(sel_var.var, XtParent(sel_var.wid));\
  else\
    no_show_connections( XtParent(sel_var.wid) );\
\
  XmToggleButtonSetState( UxGetWidget(varShowConnBt),\
                          ((XmToggleButtonCallbackStruct*)UxCallbackArg)->set,\
                          False\
                        );\
}

*ingPopupDelConnBt.class: pushButton
*ingPopupDelConnBt.parent: ingPopup
*ingPopupDelConnBt.static: true
*ingPopupDelConnBt.name: ingPopupDelConnBt
*ingPopupDelConnBt.labelString: "Delete connection"
*ingPopupDelConnBt.mnemonic: "D"
*ingPopupDelConnBt.activateCallback: del_conn_cb(UxWidget);

*uscForm.class: form
*uscForm.parent: panedWindow1
*uscForm.static: true
*uscForm.name: uscForm
*uscForm.resizePolicy: "resize_none"
*uscForm.x: 20
*uscForm.y: 65
*uscForm.width: 52
*uscForm.height: 160

*uscLb.class: label
*uscLb.parent: uscForm
*uscLb.static: true
*uscLb.name: uscLb
*uscLb.x: 355
*uscLb.y: 190
*uscLb.width: 165
*uscLb.height: 25
*uscLb.labelString: "Output"
*uscLb.alignment: "alignment_beginning"
*uscLb.leftAttachment: "attach_form"
*uscLb.leftOffset: 20
*uscLb.rightAttachment: "attach_form"
*uscLb.rightOffset: 20
*uscLb.topAttachment: "attach_form"
*uscLb.topOffset: 0

*uscSW.class: scrolledWindow
*uscSW.parent: uscForm
*uscSW.static: true
*uscSW.name: uscSW
*uscSW.scrollingPolicy: "automatic"
*uscSW.x: 330
*uscSW.y: 225
*uscSW.width: 180
*uscSW.height: 230
*uscSW.bottomAttachment: "attach_form"
*uscSW.bottomOffset: 5
*uscSW.leftAttachment: "attach_form"
*uscSW.leftOffset: 5
*uscSW.rightAttachment: "attach_form"
*uscSW.rightOffset: 5
*uscSW.topAttachment: "attach_widget"
*uscSW.topOffset: 0
*uscSW.topWidget: "uscLb"
*uscSW.shadowThickness: 2
*uscSW.translations: "" 

*uscList.class: rowColumn
*uscList.parent: uscSW
*uscList.static: true
*uscList.name: uscList
*uscList.x: 2
*uscList.y: 2
*uscList.width: 480
*uscList.height: 105
*uscList.shadowThickness: 0
*uscList.topShadowColor: "#0000cb00da00"
*uscList.bottomShadowColor: "#420048000000"
*uscList.sensitive: "true"
*uscList.spacing: 0
*uscList.traversalOn: "true"
*uscList.packing: "pack_tight"

*uscPopup.class: rowColumn
*uscPopup.parent: uscList
*uscPopup.static: true
*uscPopup.name: uscPopup
*uscPopup.rowColumnType: "menu_popup"
*uscPopup.menuAccelerator: "<KeyUp>F4"

*uscPopupLb.class: label
*uscPopupLb.parent: uscPopup
*uscPopupLb.static: true
*uscPopupLb.name: uscPopupLb
*uscPopupLb.labelString: "OUTPUT VARIABLES"

*separator35.class: separator
*separator35.parent: uscPopup
*separator35.static: true
*separator35.name: separator35

*uscPopupedit.class: pushButton
*uscPopupedit.parent: uscPopup
*uscPopupedit.static: true
*uscPopupedit.name: uscPopupedit
*uscPopupedit.labelString: "Edit Descr"
*uscPopupedit.mnemonic: "E"
*uscPopupedit.activateCallback: var_edit_descr(indice_blocco,indice_variabile);

*uscPopupShowConnBt.class: toggleButton
*uscPopupShowConnBt.parent: uscPopup
*uscPopupShowConnBt.static: true
*uscPopupShowConnBt.name: uscPopupShowConnBt
*uscPopupShowConnBt.labelString: "Show connections"
*uscPopupShowConnBt.mnemonic: "S"
*uscPopupShowConnBt.valueChangedCallback: {\
  if ( ((XmToggleButtonCallbackStruct*)UxCallbackArg)->set )\
    show_connections(sel_var.var, XtParent(sel_var.wid));\
  else\
    no_show_connections( XtParent(sel_var.wid) );\
\
  XmToggleButtonSetState( UxGetWidget(varShowConnBt),\
                          ((XmToggleButtonCallbackStruct*)UxCallbackArg)->set,\
                          False\
                        );\
}

*uscPopupDelConnBt.class: pushButton
*uscPopupDelConnBt.parent: uscPopup
*uscPopupDelConnBt.static: true
*uscPopupDelConnBt.name: uscPopupDelConnBt
*uscPopupDelConnBt.labelString: "Delete connection"
*uscPopupDelConnBt.mnemonic: "D"
*uscPopupDelConnBt.activateCallback: del_conn_cb(UxWidget);

