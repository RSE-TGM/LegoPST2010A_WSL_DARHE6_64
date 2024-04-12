! UIMX ascii 2.0 key: 9474                                                      

*lg1MainWindow.class: mainWindow
*lg1MainWindow.parent: NO_PARENT
*lg1MainWindow.defaultShell: topLevelShell
*lg1MainWindow.static: false
*lg1MainWindow.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo lg1MainWindow.i\
   tipo \
   release 2.27\
   data 5/10/95\
   reserved @(#)lg1MainWindow.i	2.27\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
#include <stdio.h>\
#ifndef DESIGN_TIME\
#include <stdlib.h>\
#endif\
#include <signal.h>\
#include <string.h>\
#include <sys/types.h>\
#include <unistd.h>\
\
\
#include "UxSubproc.h"\
\
\
#include "filtri.h"\
#include "lg1.h"\
#include "question_type.h"\
#include "errore.h"\
#include "lg1MainWindowType.h"\
\
handle id_subproc=0;\
\
extern void istanzia_blocco();\
extern void routine_vuota();\
extern swidget instantiationDlg;\
extern swidget output_text;\
extern Widget topwidget;\
/* bl_selezionati:\
 * Elenco dei blocchi, contenuti nella lista dei blocchi visualizzata dalla\
 * main window, che sono stati selezionati. L'elenco viene aggiornato dalla\
 * callback di selezione estesa attivata interagendo con la lista.\
 */ \
SELECTION bl_selezionati = { 0, NULL };\
\
\
/* var_win_list:\
 * Lista delle interfacce di tipo varWin attive in un dato istante.\
 * Vedi le callback dei bottoni varCloseBt e varBt per l'inserimento e la\
 * cancellazione di nuovi elementi dalla lista.\
 */\
VAR_WIN_TYPE  *var_win_list=NULL;\
\
extern int block_selection_activate();\
\
char blockname[15];\
char modulename[15];\
char blockdescr[60];\
\
static int found_item=0; /* utilizzato nella search di un modulo */\
\
extern int graphics_on;\
extern int modifiche;    /* modifiche nella grafica */\
\
int num_filtri = 0;\
FILTRI *filtri[MAXFILTRI];\
int ind_filt_default;\

*lg1MainWindow.ispecdecl: swidget *DefFilterButt;\
int button_already_defined;\

*lg1MainWindow.ispeclist: DefFilterButt, button_already_defined
*lg1MainWindow.ispeclist.DefFilterButt: "swidget", "*%DefFilterButt%"
*lg1MainWindow.ispeclist.button_already_defined: "int", "%button_already_defined%"
*lg1MainWindow.funcdecl: swidget create_lg1MainWindow()\

*lg1MainWindow.funcname: create_lg1MainWindow
*lg1MainWindow.funcdef: "swidget", "<create_lg1MainWindow>(%)"
*lg1MainWindow.icode: Arg  arg;
*lg1MainWindow.fcode: /* \
 * Settaggio del titolo della main window.\
 */\
XtSetArg( arg, XmNtitle, "Topology Editor" );\
XtSetValues( XtParent(UxGetWidget(lg1MainWindow)), &arg, 1 );\
\
\
/*\
 * Settaggio dei menu della main window ( pulldown e popup ).\
 * Viene settato l'attributo sensitive dei vari bottoni e lo stato\
 * dei toggle button.\
 */\
main_menu_setup();\
\
/* se e' attiva la grafica verifico la congruenza tra macroblocks.dat e f01.dat */\
if(graphics_on)\
   lancia_macro(topwidget,UxGetWidget(blListSL));\
\
button_already_defined = False;\
\
def_filtri();\
\
return(rtrn);\

*lg1MainWindow.auxdecl: /* \
 * set_bl_list()\
 *\
 * Scrive nella lista dei blocchi visualizzata dalla main window\
 * le descrizioni dei blocchi contenuti in memoria nella variabile 'blocchi'.\
 */\
extern ERR_LEVEL err_level;\
\
set_bl_list()\
{\
\
   extern swidget blListSL;\
\
   Arg      arg[2];\
   char     entry[81];\
   XmString *lista;\
   int      i;\
   BLOCCO   *bloc=blocchi;  /* serve a causa dell'interprete uimx */\
\
\
\
   /* \
    * Gestisce il caso in cui non  ci sono blocchi in memoria. \
    * Cio' capita all'inizio e ogni volta che fallisce una operazione di \
    * apertura di nuovo modello.\
    */\
   if ( ! num_blocchi )\
   {\
      XtSetArg(arg[0], XmNitems, NULL);\
      XtSetArg(arg[1], XmNitemCount, 0);   \
      XtSetValues(UxGetWidget(blListSL), arg, 2);\
      return;\
   } \
\
\
\
   /* \
    * Costruisce la lista degli identificatori dei blocchi.\
    */\
   lista = ( XmString * ) malloc ( num_blocchi * sizeof(XmString) );\
\
   for (i=0; i<num_blocchi; i++ )\
   {\
      strcpy ( entry, bloc[i].sigla_modulo ); \
      strcat ( entry,  " (" );\
      strcat ( entry, bloc[i].sigla_blocco );\
      strcat ( entry,  ")  " );\
      strcat ( entry, bloc[i].descr_blocco );\
      lista[i]=XmStringCreateSimple(entry);  \
   }\
\
\
   /*\
    * Trasferisce la lista nel widget 'blListSL'.\
    */\
   XtSetArg(arg[0], XmNitems, lista);\
   XtSetArg(arg[1], XmNitemCount, num_blocchi);   \
   XtSetValues(UxGetWidget(blListSL), arg, 2);\
\
   /* \
    * Libera la memoria utilizzata per costruire la lista.\
    */\
   for ( i=0; i<num_blocchi; i++ )\
      XtFree(lista[i]); \
\
   XtFree( lista );\
\
\
}\
\
\
\
\
/*\
 * set_model_name()\
 *\
 * Scrive il nome del modello nel widget 'modNAmeLb'.\
 */\
set_model_name()\
{\
  extern swidget   modNameLb;\
  extern char      *str_toupper();\
  extern char      nome_modello[];\
  \
  char app[100];\
\
\
  if ( err_level == ERROR )\
     UxPutLabelString(modNameLb,"No model selected");\
  else\
  {\
     str_toupper(nome_modello);\
     sprintf(app,"Model name: %s",nome_modello);  \
     UxPutLabelString(modNameLb,app);\
  }\
}\
\
\
\
\
\
/*\
 * write_message()\
 *\
 * Appende un messaggio nel widget 'messageSt'.\
 */\
write_message( mess )\
char *mess;\
{\
  char   *str, *new_str;\
  extern swidget messageST;\
\
\
  /*\
   * Ottiene la stringa contenuta nel widget. \
   */\
  str = UxGetText( messageST );\
\
  /*\
   * costruisce la nuova stringa.\
   */\
  new_str = (char*) malloc ( sizeof(char*) * ( strlen(mess)+strlen(str)+1 ) );\
  strcpy( new_str, str );\
  if ( *str )\
     strcat( new_str, "\n\n" );\
  strcat( new_str, mess );\
\
  /*\
   * Introduce nel widget la nuova stringa.\
   */\
  UxPutText( messageST, new_str );\
\
  /*\
   * Libera la memoria utilizzata.\
   */\
  free( str );\
  free( new_str );\
\
}\
\
\
\
\
/*\
 * main_win_setup()\
 *\
 * Settaggio dei menu puldown e del menu popup della main window.\
 * Si setta l'attributo sensitive dei vari bottoni e lo stato dei toggle button.\
 */\
main_menu_setup()\
{\
\
   /*\
    * Settaggio dei bottoni di attivazione delle interfacce contenenti gli \
    * elenchi delle variabili.\
    */\
   if ( bl_selezionati.num  ==  1 )\
   { \
     sensitive( blPopupVarBt, True );\
     sensitive( varBt, True );\
     sensitive( blPopupEditBt, True );\
   }\
   else\
   {\
     sensitive( blPopupVarBt, False );\
     sensitive( varBt, False );\
     sensitive( blPopupEditBt, False);\
   }\
\
\
   /*\
    * Settaggio dei bottoni di cancellazione dei blocchi.\
    */\
   if ( bl_selezionati.num )\
   {\
     sensitive( blPopupDelBt, True );\
     sensitive( deleteBt, True );\
   }\
   else\
   {\
     sensitive( blPopupDelBt, False );\
     sensitive( deleteBt, False );\
   }\
\
   sensitive( newRegBl, True );\
\
}\
\
\
desel_open_but()\
{\
   sensitive(openBt,False);\
}\
\
/*\
 * sensitive()\
 *\
 * Setta l'attributo 'sensitive' di un bottone.\
 */\
sensitive( swid, val )\
swidget swid;\
int     val;\
{\
   Arg arg;\
\
   XtSetArg( arg, XmNsensitive, val );\
   XtSetValues( UxGetWidget(swid), &arg, 1 );\
}\
\
\
\
\
\
\
\
\
/*\
 * set_win_cursor()\
 *\
 * Setta il cursore per la main window e per le interfacce 'varWin' attive.\
 */\
set_win_cursors( cursor )\
char *cursor;\
{\
   VAR_WIN_TYPE *cur;\
\
\
   set_pixmap_cursor( UxGetWidget(lg1MainWindow), cursor );\
\
   for ( cur=var_win_list; cur; cur=cur->succ )\
      set_pixmap_cursor( UxGetWidget(cur->swid), cursor );\
\
}\
\
\
\
\
/*\
 * reset_win_cursors()\
 *\
 * Ristabilisce il cursore di sistema per la main window e le window delle\
 * interfacce 'varWin' attive.\
 */\
reset_win_cursors()\
{\
   VAR_WIN_TYPE *cur;\
\
\
   undef_cursore( UxGetWidget(lg1MainWindow) );\
\
   for ( cur=var_win_list; cur; cur=cur->succ )\
      undef_cursore( UxGetWidget(cur->swid) );\
\
}\
\
\
\
/*\
 * bl_del_cb()\
 *\
 * Funzione che viene attivata quando si richiede di cancellare un insieme\
 * di blocchi.\
 * Essa attiva l'interfaccia 'questionDB' per chiedere conferma della \
 * cancellazione.\
 */\
bl_del_cb()\
{\
   extern QUESTION question;\
   char str[1024];\
   int i;\
   BLOCCO *bloc=blocchi;\
\
\
   if ( bl_selezionati.num<15 )\
   {\
      strcpy( str, "Do yuo want delete these blocks?" );\
\
      for ( i=0; i<bl_selezionati.num; i++ )\
      {\
        strcat( str, "\n     " );\
        strcat( str, bloc[bl_selezionati.pos[i]].label );\
      }\
   }\
   else\
      strcpy( str, "Do yuo want delete the selected blocks?" );\
\
   \
   question = QST_DEL_BL;\
\
   questionDB_activate( str );\
\
}\
\
\
\
\
\
/* \
 * bl_del_qst_cb()\
 *\
 * La funzione viene attivata quando si conferma la cancellazione di un insieme \
 * di blocchi.\
 */\
bl_del_qst_cb()\
{\
  extern int changes_in_F01;\
\
  int i;\
  VAR_WIN_TYPE *cor;\
\
\
  /* cancellazione blocchi dalla pagina grafica */\
  /*printf("test step bl_del_qst_cb bl_selezionati.num %d\n",bl_selezionati.num);*/\
  if(graphics_on == True)\
     Idel_graph_bloc();\
\
  /*\
   * Cancellazione dei blocchi nel vettore 'blocchi[]'.\
   */\
\
  /*printf("test step 1 bl_del_qst_cb bl_selezionati.num %d\n",bl_selezionati.num);*/\
  \
/* introduco il test per verificare che ci siano blocchi selezionati\
   nella lista, perche' potrebbero essere di tipo simbolo o remark\
  nella grafica\
*/\
\
  if(bl_selezionati.num)\
     del_blocchi ( bl_selezionati.num, bl_selezionati.pos );\
  else\
     return;\
\
  /*printf("test step 2 bl_del_qst_cb\n");*/\
\
\
  /*\
   * Cancellazione dell'identificatore del bloccho dalla lista dei blocchi\
   * visualizzata dalla main window.\
   * Distruzione delle interfacce 'varWin' associate ai blocchi cancellati.\
   */\
  for ( i=bl_selezionati.num-1; i>-1; i-- )\
  {\
    XmListDeletePos( UxGetWidget(blListSL), bl_selezionati.pos[i]+1 );\
 \
    for ( cor=var_win_list; cor; cor=cor->succ )\
       if ( bl_selezionati.pos[i] == cor->bloc )\
         break;\
\
    if ( cor )\
      UxDestroyInterface( cor->swid );\
  }\
\
\
\
  /*\
   * Aggiorna il campo 'bloc' degli elementi della lista 'var_win_list'.\
   * Se un interfaccia era associata al blocco 3 e i blocchi 1 e 2 vengono\
   * cancellati, (poiche il blocco 3 ora e' diventato il blocco 1) il campo\
   * 'bloc' deve essere posto a 1.\
   */\
  for ( i=bl_selezionati.num-1; i>-1; i-- )\
    for ( cor=var_win_list; cor; cor=cor->succ )\
       if ( cor->bloc > bl_selezionati.pos[i] )\
          (cor->bloc)--;\
\
\
  /*\
   * Setta la variabile locale 'blocco' di ogni interfaccia 'varWin'\
   * con il nuovo valore calcolato del campo 'bloc'\
   */\
  for ( cor=var_win_list; cor; cor=cor->succ )\
     set_bloc( cor->swid, cor->bloc );\
\
\
  /*\
   * I blocchi selezionati sono stati cancellati quindi non ci sono piu' \
   * blocchi selezionati.\
   */\
  free ( bl_selezionati.pos );\
  bl_selezionati.pos = NULL;\
  bl_selezionati.num = 0;\
\
\
\
  /*\
   * Sono stati effettuati cambiamenti nel modello presente in memoria\
   * che ora non rispetta piu' il contenuto del file f01 originario.\
   */\
  changes_in_F01 = True;\
\
}\
\
\
\
\
/* \
 * bl_var_cb()\
 *\
 * La funzione viene attivata quando si vogliono visualizzare le variabili di \
 * blocco selezionato.\
 * Esa attiva l'interfaccia 'varWin' per il blocco selezionato ed inserisce\
 * un elemento corrispondente nella lista 'var_win_list'.\
 */\
bl_var_cb()\
{\
   extern swidget create_varWin();\
   swidget swid;\
   VAR_WIN_TYPE *new_var, *cor;\
\
\
\
   /* \
    * Controlla se per il blocco selezionato e' gia stata attivata\
    * un'interfaccia di tipo 'varWin'.\
    */\
   for ( cor=var_win_list; cor; cor=cor->succ )\
      if ( bl_selezionati.pos[0] == cor->bloc )\
        break;\
\
\
   /*\
    * Se esiete gia' l'interfaccia 'varWin' viene fatto un raise della stessa.\
    */\
   if ( cor )\
   {\
      XRaiseWindow( XtDisplay(UxGetWidget(cor->swid)),\
                    XtWindow(XtParent(UxGetWidget(cor->swid))) );\
      return;\
   }\
\
\
\
   /*\
    * Creazione di una nuova interfaccia.\
    */\
   swid = create_varWin( bl_selezionati.pos[0] );\
   UxPopupInterface( swid, no_grab );\
\
\
   /*\
    * Inserimento della nuova interfaccia nella lista 'var_win_list'.\
    */\
   new_var       = (VAR_WIN_TYPE*) malloc( sizeof( VAR_WIN_TYPE ) );\
   new_var->bloc = bl_selezionati.pos[0];\
   new_var->swid = swid;\
   new_var->succ = var_win_list;\
\
   var_win_list       = new_var;\
\
}\
\
\
\
extern int num_modulo;\
extern char s_num_modulo[10];\
\
void routine_vuota()\
{\
    UxPopdownInterface(instantiationDlg);\
}\
\
\
do_dialogo()\
{\
\
\
   char str_num_modulo[10];\
   char path[300],fnamexe[200];\
   sprintf(str_num_modulo,"%d",num_modulo);\
   strcpy(path , getenv("LEGOCAD_USER"));\
   strcpy(fnamexe,path);\
   strcat(fnamexe,"/legocad/libut/legoserver");\
   if(id_subproc)\
	UxDeleteSubproc(id_subproc);\
   id_subproc = UxCreateSubproc(fnamexe,str_num_modulo,UxAppendTo);\
   if(id_subproc == -1)\
   {\
      printf("Can't start subprocess\n");\
      err_level = ERROR;\
      errore("Can't start subprocess");\
      return(1);\
   }\
\
   UxSetSubprocEcho(id_subproc,1); /* setta l'eco sulla window di testo */\
\
   if(-1 == UxSetSubprocClosure(id_subproc,UxGetWidget(output_text)))\
   {\
      printf("Can't set subproc closure \n");\
      err_level = ERROR;\
      errore("Can't set subproc closure");\
      return(1);\
   }\
\
\
   if(-1 ==UxSetSubprocExitCallback(id_subproc,istanzia_blocco))\
   {\
      printf("Can't set exit callback \n");\
      err_level = ERROR;\
      errore("Can't set subproc closure");\
      return(1);\
   }\
   if(-1 == UxRunSubproc(id_subproc,str_num_modulo))\
   {\
      printf("\n Can't start the application\n");\
      err_level = ERROR;\
      errore("Can't set subproc closure");\
      return(1);\
   }\
   UxPopupInterface(instantiationDlg,no_grab);\
\
\
}\
\
\
\
\
\
\
del_block_from_list()\
{\
  extern int changes_in_F01;\
\
  int i;\
  VAR_WIN_TYPE *cor;\
\
  /*\
   * Cancellazione dei blocchi nel vettore 'blocchi[]'.\
   */\
\
  del_blocchi ( bl_selezionati.num, bl_selezionati.pos );\
\
 /*\
   * Cancellazione dell'identificatore del bloccho dalla lista dei blocchi\
   * visualizzata dalla main window.\
   * Distruzione delle interfacce 'varWin' associate ai blocchi cancellati.\
   */\
  for ( i=bl_selezionati.num-1; i>-1; i-- )\
  {\
    XmListDeletePos( UxGetWidget(blListSL), bl_selezionati.pos[i]+1 );\
\
    for ( cor=var_win_list; cor; cor=cor->succ )\
       if ( bl_selezionati.pos[i] == cor->bloc )\
         break;\
\
    if ( cor )\
      UxDestroyInterface( cor->swid );\
  }\
\
  /*\
   * Aggiorna il campo 'bloc' degli elementi della lista 'var_win_list'.\
   * Se un interfaccia era associata al blocco 3 e i blocchi 1 e 2 vengono\
   * cancellati, (poiche il blocco 3 ora e' diventato il blocco 1) il campo\
   * 'bloc' deve essere posto a 1.\
   */\
  for ( i=bl_selezionati.num-1; i>-1; i-- )\
    for ( cor=var_win_list; cor; cor=cor->succ )\
       if ( cor->bloc > bl_selezionati.pos[i] )\
          (cor->bloc)--;\
  \
\
\
  /*\
   * Setta la variabile locale 'blocco' di ogni interfaccia 'varWin'\
   * con il nuovo valore calcolato del campo 'bloc'\
   */\
  for ( cor=var_win_list; cor; cor=cor->succ )\
     set_bloc( cor->swid, cor->bloc );\
\
\
/*\
   * I blocchi selezionati sono stati cancellati quindi non ci sono piu'\
   * blocchi selezionati.\
   */\
  free ( bl_selezionati.pos );\
  bl_selezionati.pos = NULL;\
  bl_selezionati.num = 0;\
  /*\
   * Sono stati effettuati cambiamenti nel modello presente in memoria\
   * che ora non rispetta piu' il contenudeto del file f01 originario.\
   */\
  changes_in_F01 = True;\
 \
}\
\
/*\
 * bl_edit_cb()\
 *\
 * Funzione che viene attivata quando si richiede di editare la descrizione\
 * di un blocco.\
 */\
\
bl_edit_cb()\
{\
   extern swidget EditDescrDialog1; \
   extern swidget BlocName;\
   extern swidget ModuleName;\
   BLOCCO *bloc = blocchi;  /* frego UIMX */\
   char *descr;\
\
\
   descr = bloc[ bl_selezionati.pos[0] ].descr_blocco;   \
   UxPopupInterface(EditDescrDialog1,no_grab);\
   UxPutLabelString(ModuleName,bloc[ bl_selezionati.pos[0] ].sigla_modulo);\
   UxPutText(BlocName,bloc[ bl_selezionati.pos[0] ].sigla_blocco);\
   UxPutTextString(EditDescrDialog1,descr);\
}  \
\
void set_new_descr(char *new_bl_name,char *new_descr)\
{\
   extern int changes_in_F01;\
   int i;\
   char entry[200],*appstr,oldlabel[9];\
   XmString item;\
   BLOCCO *bloc = blocchi;  /* frego UIMX */\
\
/* posso aver modificato solo la descrizione */\
   if( !strcmp(new_bl_name,bloc[ bl_selezionati.pos[0] ].sigla_blocco) )\
      strcpy( bloc[ bl_selezionati.pos[0] ].descr_blocco, new_descr);   \
   else\
   {\
/* verifico la univocita' del nome del blocco */\
      for(i=0;i<num_blocchi;i++)\
         if( !strcmp(new_bl_name,bloc[i].sigla_blocco) )\
         {\
            err_level = ERROR;\
            errore("nome blocco gia' utilizzato %s",bloc[i].label);\
            return;\
         }\
/* modifiche alla desrizione */\
      strcpy( bloc[ bl_selezionati.pos[0] ].descr_blocco, new_descr);\
\
/* e alla sigla blocco */\
      strcpy(bloc[ bl_selezionati.pos[0] ].sigla_blocco,new_bl_name);\
          \
/* alle variabili */\
      for(i=0;i<bloc[ bl_selezionati.pos[0] ].num_variabili;i++)\
      {\
         appstr = &bloc[ bl_selezionati.pos[0] ].variabili[i].nome[4];\
         strcpy(appstr,new_bl_name);  \
      }\
\
/* alla label */\
      appstr = &bloc[ bl_selezionati.pos[0] ].label[4];\
      strcpy(appstr,new_bl_name);\
\
/* modifico il nome del blocco nella grafica */\
      if( graphics_on )\
      {\
         strcpy(oldlabel,bloc[bl_selezionati.pos[0]].sigla_modulo);\
         strcat(oldlabel,bloc[bl_selezionati.pos[0]].sigla_blocco);\
\
         Iset_graf_new_blname(oldlabel,new_bl_name);\
      }\
   }\
\
/* sistemo la lista */\
   strcpy ( entry, bloc[bl_selezionati.pos[0] ].sigla_modulo ); \
   strcat ( entry,  " (" );\
   strcat ( entry, bloc[bl_selezionati.pos[0]].sigla_blocco );\
   strcat ( entry,  ")  " );\
   strcat ( entry, bloc[bl_selezionati.pos[0]].descr_blocco );\
 \
   item = (XmString)XmStringCreateSimple(entry);\
   XmListDeletePos( UxGetWidget(blListSL), bl_selezionati.pos[0]+1 );\
   XmListAddItem(UxGetWidget(blListSL),item,bl_selezionati.pos[0]+1);\
   XmStringFree(item);\
   XmListSelectPos( UxGetWidget(blListSL), bl_selezionati.pos[0]+1, False);\
\
   changes_in_F01 = True;\
\
}\
\
\
void add_item(char *buff,int pos)\
{\
   extern swidget blListSL;\
   XmString *item;\
\
   \
/*\
   con pos = 0 viene aggiunto in fondo\
   con pos = 1 viene aggiunto in cima \
   con pos = n viene aggiunto alla ennesima posizione\
*/\
   if(pos > num_blocchi)\
   {\
      err_level = ERROR;\
      errore("Item out of sequence");\
      return;\
   }\
\
   \
   item = ( XmString *) malloc( sizeof(XmString) );\
\
   *item = (XmString)XmStringCreateSimple( buff );\
\
   XmListAddItem(UxGetWidget(blListSL),*item,pos);  \
   XmStringFree(item);\
}\
\
\
\
\
/* aggiungo items al menu di set default filter */\
\
int DefFilterCB(Widget w,int ind_filtro, XmAnyCallbackStruct *call_data)\
{\
   printf("Callback della opzione %d dei filtri\n",ind_filtro+1);\
\
\
/* inizializzo la variabile globale del filtro di default */\
 \
   ind_filt_default = ind_filtro+1;\
/*   printf("n. filtro di default %d\n",ind_filt_default); */\
\
}\
\
void add_filter_button()\
{\
   extern num_filtri;\
   extern FILTRI *filtri[];\
   int i,j;\
   char label_button[20];\
\
printf("DEBUG add_filter_button: button_already_defined=%d num_filtri=%d\n",button_already_defined,num_filtri);\
\
   if(button_already_defined)\
   {\
      for(i=0; i < num_filtri; i++)\
         UxDestroySwidget( DefFilterButt[i] );\
      button_already_defined = False;\
   }\
\
   DefFilterButt = (swidget *)calloc( num_filtri,sizeof(swidget) );\
\
   printf("definizione push button filtri = %d\n",num_filtri);\
\
   for(i=0; i < num_filtri; i++)\
   {\
   /*creo i push button */\
\
      strcpy(label_button,filtri[i]->nome_filtro);\
      DefFilterButt[i] = UxCreatePushButton(label_button,DefaultFilterPane);\
      UxPutLabelString(DefFilterButt[i],label_button);\
      UxCreateWidget(DefFilterButt[i]);\
\
/* e definisco la callback */\
      UxAddCallback(DefFilterButt[i],XmNactivateCallback,DefFilterCB,i);\
   }\
   button_already_defined = True;\
}  \
\
void elimina_filter_button()\
{\
   int i;\
\
   if(button_already_defined)\
   {\
      for(i=0; i < num_filtri; i++)\
      {\
         printf("DefFilterButt[%d]=%d\n",i,DefFilterButt[i]);\
         UxDestroySwidget( DefFilterButt[i] );\
      }\
      button_already_defined = False;\
   }\
}\
\
def_filtri()\
{\
   extern int inizializza_filtri();\
  \
/*printf("lancio la libera_filtri   num_filtri = %d\n");*/\
   if(num_filtri)\
   {\
      elimina_filter_button();\
      libera_filtri(filtri,num_filtri);\
   }\
/*printf("lancio la inizializza_filtri\n");*/\
   if(inizializza_filtri(filtri,&num_filtri) == -1)\
   { \
      err_level = ERROR;\
      errore("ERROR Cannot open $HOME/filtri.edf\n"); \
      return(0);\
   }\
/*printf("lancio la add_filter_butt\n");*/\
   if(num_filtri)\
      add_filter_button();    \
}\
\
\
\

*lg1MainWindow.name: lg1MainWindow
*lg1MainWindow.unitType: "pixels"
*lg1MainWindow.x: 685
*lg1MainWindow.y: 35
*lg1MainWindow.width: 560
*lg1MainWindow.height: 635

*menuBar.class: rowColumn
*menuBar.parent: lg1MainWindow
*menuBar.static: true
*menuBar.name: menuBar
*menuBar.rowColumnType: "menu_bar"
*menuBar.menuAccelerator: "<KeyUp>F10"
*menuBar.spacing: 0

*filePane.class: rowColumn
*filePane.parent: menuBar
*filePane.static: true
*filePane.name: filePane
*filePane.rowColumnType: "menu_pulldown"
*filePane.spacing: 0

*openBt.class: pushButton
*openBt.parent: filePane
*openBt.static: true
*openBt.name: openBt
*openBt.labelString: "Open"
*openBt.mnemonic: "O"
*openBt.activateCallback: selModelActivate();\


*separator1.class: separator
*separator1.parent: filePane
*separator1.static: true
*separator1.name: separator1

*saveBt.class: pushButton
*saveBt.parent: filePane
*saveBt.static: true
*saveBt.name: saveBt
*saveBt.labelString: "Save"
*saveBt.mnemonic: "S"
*saveBt.activateCallback: {\
extern int changes_in_F01;\
extern int modifiche;\
extern int write_f01();\
extern int Isalva_grafica();\
\
   if(changes_in_F01 || modifiche)\
   {\
      printf("Some changes made, saving...\n");\
      write_f01();\
      if(graphics_on)\
         Isalva_grafica();\
      messageDB_activate("Topology saved.");      \
   }\
   else\
   {\
             messageDB_activate("No changes made, do nothing...");      \
   }\
}

*separator2.class: separator
*separator2.parent: filePane
*separator2.static: true
*separator2.name: separator2

*exitBt.class: pushButton
*exitBt.parent: filePane
*exitBt.static: true
*exitBt.name: exitBt
*exitBt.labelString: "Exit"
*exitBt.mnemonic: "E"
*exitBt.activateCallback: {\
   extern int      changes_in_F01;\
   extern QUESTION question;\
\
\
   question = QST_USCITA;\
\
   if ( changes_in_F01 )\
     questionDB_activate( "F01 has been modified! \nDo you really want exit?" );\
   else\
     questionDB_activate( "Do you really want exit?" );\
\
}
*exitBt.sensitive: "true"

*editPane.class: rowColumn
*editPane.parent: menuBar
*editPane.static: true
*editPane.name: editPane
*editPane.rowColumnType: "menu_pulldown"
*editPane.entryAlignment: "alignment_beginning"

*newBt.class: cascadeButton
*newBt.parent: editPane
*newBt.static: true
*newBt.name: newBt
*newBt.labelString: "New"
*newBt.subMenuId: "newPane"
*newBt.stringDirection: "string_direction_l_to_r"

*separator3.class: separatorGadget
*separator3.parent: editPane
*separator3.static: true
*separator3.name: separator3

*deleteBt.class: pushButton
*deleteBt.parent: editPane
*deleteBt.static: true
*deleteBt.name: deleteBt
*deleteBt.labelString: "Delete"
*deleteBt.mnemonic: "D"
*deleteBt.activateCallback: bl_del_cb();

*separator4.class: separatorGadget
*separator4.parent: editPane
*separator4.static: true
*separator4.name: separator4

*varBt.class: pushButton
*varBt.parent: editPane
*varBt.static: true
*varBt.name: varBt
*varBt.labelString: "Variables ..."
*varBt.mnemonic: "V"
*varBt.activateCallback: bl_var_cb();

*newPane.class: rowColumn
*newPane.parent: editPane
*newPane.static: true
*newPane.name: newPane
*newPane.rowColumnType: "menu_pulldown"
*newPane.entryAlignment: "alignment_beginning"

*newProcessBl.class: pushButton
*newProcessBl.parent: newPane
*newProcessBl.static: true
*newProcessBl.name: newProcessBl
*newProcessBl.labelString: "Process Block"
*newProcessBl.activateCallback: if(graphics_on == False)\
   block_selection_activate(PROCESSO);   \
else\
   Iadd_new_block_graf(PROCESSO);
*newProcessBl.alignment: "alignment_beginning"

*separator5.class: separatorGadget
*separator5.parent: newPane
*separator5.static: true
*separator5.name: separator5

*newRegBl.class: pushButton
*newRegBl.parent: newPane
*newRegBl.static: true
*newRegBl.name: newRegBl
*newRegBl.labelString: "Regulation Block"
*newRegBl.activateCallback: if(graphics_on == False)\
   block_selection_activate(REGOLAZIONE);\
else \
   Iadd_new_block_graf(REGOLAZIONE);

*OptionPane.class: rowColumn
*OptionPane.parent: menuBar
*OptionPane.static: true
*OptionPane.name: OptionPane
*OptionPane.rowColumnType: "menu_pulldown"

*SetDefFilter.class: cascadeButtonGadget
*SetDefFilter.parent: OptionPane
*SetDefFilter.static: true
*SetDefFilter.name: SetDefFilter
*SetDefFilter.labelString: "Set Default Filter"
*SetDefFilter.subMenuId: "DefaultFilterPane"

*separator6.class: separatorGadget
*separator6.parent: OptionPane
*separator6.static: true
*separator6.name: separator6

*DefineFilter.class: pushButtonGadget
*DefineFilter.parent: OptionPane
*DefineFilter.static: true
*DefineFilter.name: DefineFilter
*DefineFilter.labelString: "Define Filter"
*DefineFilter.activateCallback: {\
  char nome[200];\
\
  if(var_win_list != NULL)\
  {\
     messageDB_activate("This program can't run \nwith variables window open");\
     return;\
  }\
\
  strcpy(nome,getenv("LEGOCAD_BIN"));  \
  strcat(nome,"/filtri");\
\
#ifndef DESIGN_TIME\
   signal(SIGCHLD,def_filtri);\
   if(!vfork())\
      execlp(nome,nome,(char *)0);\
#endif\
\
}

*DefaultFilterPane.class: rowColumn
*DefaultFilterPane.parent: OptionPane
*DefaultFilterPane.static: true
*DefaultFilterPane.name: DefaultFilterPane
*DefaultFilterPane.rowColumnType: "menu_pulldown"

*NoFilterDef.class: pushButtonGadget
*NoFilterDef.parent: DefaultFilterPane
*NoFilterDef.static: true
*NoFilterDef.name: NoFilterDef
*NoFilterDef.labelString: "No Filter"
*NoFilterDef.activateCallback: {\
   extern int ind_filt_default;\
\
   ind_filt_default = 0;\
}

*fileCascade.class: cascadeButton
*fileCascade.parent: menuBar
*fileCascade.static: true
*fileCascade.name: fileCascade
*fileCascade.labelString: "File"
*fileCascade.mnemonic: "F"
*fileCascade.subMenuId: "filePane"

*editCascade.class: cascadeButton
*editCascade.parent: menuBar
*editCascade.static: true
*editCascade.name: editCascade
*editCascade.labelString: "Edit"
*editCascade.mnemonic: "E"
*editCascade.subMenuId: "editPane"

*menuBar_top_b2.class: cascadeButton
*menuBar_top_b2.parent: menuBar
*menuBar_top_b2.static: true
*menuBar_top_b2.name: menuBar_top_b2
*menuBar_top_b2.labelString: "Options"
*menuBar_top_b2.mnemonic: "O"
*menuBar_top_b2.subMenuId: "OptionPane"

*mainPW.class: panedWindow
*mainPW.parent: lg1MainWindow
*mainPW.static: true
*mainPW.name: mainPW
*mainPW.sashIndent: -10
*mainPW.spacing: 20

*mainForm.class: form
*mainForm.parent: mainPW
*mainForm.static: true
*mainForm.name: mainForm
*mainForm.resizePolicy: "resize_none"
*mainForm.x: 15
*mainForm.y: 10
*mainForm.width: 530
*mainForm.height: 450
*mainForm.paneMaximum: 1000
*mainForm.allowResize: "false"
*mainForm.paneMinimum: 250

*modNameLb.class: label
*modNameLb.parent: mainForm
*modNameLb.static: false
*modNameLb.name: modNameLb
*modNameLb.x: 105
*modNameLb.y: 55
*modNameLb.width: 330
*modNameLb.height: 35
*modNameLb.leftAttachment: "attach_form"
*modNameLb.leftOffset: 5
*modNameLb.rightAttachment: "attach_form"
*modNameLb.rightOffset: 5
*modNameLb.labelString: "No model selected"
*modNameLb.fontList: "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1"
*modNameLb.topAttachment: "attach_form"
*modNameLb.topOffset: 10
*modNameLb.highlightThickness: 0
*modNameLb.highlightOnEnter: "false"
*modNameLb.highlightColor: "#cccc22224444"
*modNameLb.shadowThickness: 0
*modNameLb.traversalOn: "false"

*blListLb.class: label
*blListLb.parent: mainForm
*blListLb.static: true
*blListLb.name: blListLb
*blListLb.x: 25
*blListLb.y: 155
*blListLb.width: 110
*blListLb.height: 15
*blListLb.leftAttachment: "attach_form"
*blListLb.leftOffset: 5
*blListLb.topAttachment: "attach_widget"
*blListLb.topOffset: 25
*blListLb.topWidget: "modNameLb"
*blListLb.alignment: "alignment_center"
*blListLb.labelString: "Blocks in model"
*blListLb.rightAttachment: "attach_form"
*blListLb.rightOffset: 5
*blListLb.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"

*blSearchBox.class: rowColumn
*blSearchBox.parent: mainForm
*blSearchBox.static: true
*blSearchBox.name: blSearchBox
*blSearchBox.x: 30
*blSearchBox.y: 390
*blSearchBox.width: 422
*blSearchBox.height: 32
*blSearchBox.bottomAttachment: "attach_form"
*blSearchBox.bottomOffset: 20
*blSearchBox.leftAttachment: "attach_form"
*blSearchBox.orientation: "horizontal"
*blSearchBox.rightAttachment: "attach_form"
*blSearchBox.rightOffset: 30
*blSearchBox.leftOffset: 30
*blSearchBox.numColumns: 2
*blSearchBox.packing: "pack_tight"
*blSearchBox.resizable: "true"

*blSearchLb.class: label
*blSearchLb.parent: blSearchBox
*blSearchLb.static: true
*blSearchLb.name: blSearchLb
*blSearchLb.x: 10
*blSearchLb.y: 10
*blSearchLb.width: 260
*blSearchLb.height: 20
*blSearchLb.labelString: "Find:"
*blSearchLb.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"

*blSearchTF.class: textField
*blSearchTF.parent: blSearchBox
*blSearchTF.static: true
*blSearchTF.name: blSearchTF
*blSearchTF.x: 45
*blSearchTF.y: 3
*blSearchTF.width: 165
*blSearchTF.height: 39
*blSearchTF.resizeWidth: "false"
*blSearchTF.columns: 15

*blSearchUpBt.class: arrowButton
*blSearchUpBt.parent: blSearchBox
*blSearchUpBt.static: true
*blSearchUpBt.name: blSearchUpBt
*blSearchUpBt.x: 187
*blSearchUpBt.y: 3
*blSearchUpBt.width: 30
*blSearchUpBt.height: 32
*blSearchUpBt.activateCallback: {\
int i,appo;\
extern int found_item;\
char *buff;\
char riferimento[100];\
BLOCCO *bloc = blocchi; /* per ingannare l'interprete */\
\
buff = UxGetText( blSearchTF );\
\
if(buff != NULL) \
{\
   tominus(trim_blank(buff));\
\
   printf("search for text %s\n",buff);\
\
   appo=found_item-2;\
\
   for(i=appo;i>=0;i--)\
   {\
      \
      strcpy(riferimento,bloc[i].sigla_modulo);\
      tominus(trim_blank(riferimento));\
      strcat(riferimento,bloc[i].sigla_blocco);\
      tominus(trim_blank(riferimento));\
      strcat(riferimento,bloc[i].descr_blocco);\
      tominus(trim_blank(riferimento));\
/*\
      printf("stringa di riferimento %s\n",riferimento);\
*/\
      if( strstr(riferimento,buff) )\
      {\
         found_item = i+1;\
         break;\
      }\
\
   }\
      \
   if(found_item)\
   {\
      printf("found string in position %d\n",found_item);\
/*\
      XmListSelectPos( UxGetWidget(blListSL),found_item,True);\
*/\
      XmListSetPos(UxGetWidget(blListSL),found_item);\
   }\
}\
}

*blSearchDownBt.class: arrowButton
*blSearchDownBt.parent: blSearchBox
*blSearchDownBt.static: true
*blSearchDownBt.name: blSearchDownBt
*blSearchDownBt.x: 318
*blSearchDownBt.y: 3
*blSearchDownBt.width: 30
*blSearchDownBt.height: 30
*blSearchDownBt.arrowDirection: "arrow_down"
*blSearchDownBt.activateCallback: {\
int i;\
extern int found_item;\
char *buff;\
char riferimento[100];\
BLOCCO *bloc = blocchi; /* per ingannare l'interprete */\
\
buff = UxGetText( blSearchTF );\
\
if(buff != NULL)\
{\
   tominus(trim_blank(buff));\
\
   printf("search for text %s\n",buff);\
\
   \
   for(i=found_item;i<num_blocchi;i++)\
   {\
      strcpy(riferimento,bloc[i].sigla_modulo);\
      tominus(trim_blank(riferimento));\
      strcat(riferimento,bloc[i].sigla_blocco);\
      tominus(trim_blank(riferimento));\
      strcat(riferimento,bloc[i].descr_blocco);\
      tominus(trim_blank(riferimento));\
/*\
      printf("stringa di riferimento %s\n",riferimento);\
*/\
      if( strstr(riferimento,buff) )\
      {\
         found_item = i+1;\
         break;\
      }\
   }\
\
   if(found_item)\
   {   \
      printf("found string in position %d\n",found_item);\
\
/*\
      XmListSelectPos( UxGetWidget(blListSL),found_item,True);\
*/\
      XmListSetPos(UxGetWidget(blListSL),found_item);\
      printf("VItem visibili = %d\n",UxGetVisibleItemCount(blListSL));  \
   }\
}\
}

*blListSW.class: scrolledWindow
*blListSW.parent: mainForm
*blListSW.static: true
*blListSW.name: blListSW
*blListSW.scrollingPolicy: "application_defined"
*blListSW.x: 30
*blListSW.y: 100
*blListSW.visualPolicy: "variable"
*blListSW.scrollBarDisplayPolicy: "static"
*blListSW.shadowThickness: 0
*blListSW.bottomAttachment: "attach_widget"
*blListSW.bottomOffset: 10
*blListSW.bottomWidget: "blSearchBox"
*blListSW.leftAttachment: "attach_form"
*blListSW.leftOffset: 30
*blListSW.rightAttachment: "attach_form"
*blListSW.rightOffset: 30
*blListSW.topAttachment: "attach_widget"
*blListSW.topOffset: 5
*blListSW.topWidget: "blListLb"
*blListSW.height: 310

*blListSL.class: scrolledList
*blListSL.parent: blListSW
*blListSL.static: false
*blListSL.name: blListSL
*blListSL.width: 494
*blListSL.height: 279
*blListSL.selectionPolicy: "extended_select"
*blListSL.listSpacing: 0
*blListSL.scrollBarDisplayPolicy: "as_needed"
*blListSL.listSizePolicy: "constant"
*blListSL.highlightThickness: 0
*blListSL.shadowThickness: 2
*blListSL.listMarginHeight: 5
*blListSL.listMarginWidth: 5
*blListSL.extendedSelectionCallback: {\
XmListCallbackStruct *cb;\
int i;\
char labelbl[10];\
SELECTION appo;\
\
cb = (XmListCallbackStruct *) UxCallbackArg;\
\
/*\
 * Libera la struttura 'bl_selezionati' dopo aver deselezionato i relativi blocchi\
 * nella window di grafica.\
 */\
\
if ( bl_selezionati.pos )\
{\
\
  if(graphics_on)\
  {\
     /*** e' necessario salvare la situazione dei selezionati   \
          perche' viene manipolata nella selgraf->seleziona_blocco ***/\
\
     appo.num = bl_selezionati.num;\
     appo.pos = (int *) malloc ( sizeof(int) * appo.num );\
     memcpy (appo.pos, bl_selezionati.pos, \
           sizeof(int) * appo.num );\
          \
     for ( i=0; i<appo.num; i++ )\
     {\
       strcpy(labelbl,blocchi[appo.pos[i]].sigla_modulo);\
       strcat(labelbl,blocchi[appo.pos[i]].sigla_blocco);\
       selgraf_blocco(labelbl,False);\
     }\
  }\
  \
  free ( bl_selezionati.pos );\
}\
\
/* aggiornamento della situazione attuale */\
\
bl_selezionati.num = cb->selected_item_count;\
\
\
if ( bl_selezionati.num )\
{\
\
  /*\
   * Trasferimento della selezione dalla struttura 'cb' alla struttura\
   * 'bl_selezionati'.\
   */\
  bl_selezionati.pos = (int *) malloc ( sizeof(int) *  bl_selezionati.num );\
\
  memcpy ( bl_selezionati.pos, cb->selected_item_positions, \
           sizeof(int) * bl_selezionati.num );\
\
  /*\
   * I campi 'pos' vengono decrementati per poterli utilizzare come indici\
   * nel vettore 'blocchi[]'.\
   */\
  printf("bl_selezionati.num = %d\n",bl_selezionati.num);\
\
  for ( i=0; i<bl_selezionati.num; i++ )\
  {\
    bl_selezionati.pos[i] -= 1;\
/****    printf("bl_selezionati.pos[%d] = %d \n",i,bl_selezionati.pos[i]); ***/\
  }\
\
  for ( i=0; i<bl_selezionati.num; i++ )\
    if(graphics_on)\
    {\
       strcpy(labelbl,blocchi[bl_selezionati.pos[i]].sigla_modulo);\
       strcat(labelbl,blocchi[bl_selezionati.pos[i]].sigla_blocco);\
       selgraf_blocco(labelbl,True);\
    }  \
}\
else \
  bl_selezionati.pos = NULL; \
\
/*\
 * Setta i menu in relazione alla nuova situazione causata dal cambiamento \
 * della selezione.\
 */\
\
main_menu_setup();\
\
}
*blListSL.singleSelectionCallback: {\
\
}
*blListSL.itemCount: 0
*blListSL.selectedItemCount: 0
*blListSL.visibleItemCount: 50

*blPopup.class: rowColumn
*blPopup.parent: blListSL
*blPopup.static: true
*blPopup.name: blPopup
*blPopup.rowColumnType: "menu_popup"
*blPopup.menuAccelerator: "<KeyUp>F4"

*blPopupLb.class: label
*blPopupLb.parent: blPopup
*blPopupLb.static: true
*blPopupLb.name: blPopupLb
*blPopupLb.labelString: "BLOCKS"

*Separator50.class: separator
*Separator50.parent: blPopup
*Separator50.static: true
*Separator50.name: Separator50

*blPopupEditBt.class: pushButton
*blPopupEditBt.parent: blPopup
*blPopupEditBt.static: true
*blPopupEditBt.name: blPopupEditBt
*blPopupEditBt.labelString: "Edit Descr"
*blPopupEditBt.mnemonic: "E"
*blPopupEditBt.activateCallback: {bl_edit_cb(); }

*blPopupDelBt.class: pushButton
*blPopupDelBt.parent: blPopup
*blPopupDelBt.static: true
*blPopupDelBt.name: blPopupDelBt
*blPopupDelBt.labelString: "Delete"
*blPopupDelBt.mnemonic: "D"
*blPopupDelBt.activateCallback: { bl_del_cb(); }

*blPopupVarBt.class: pushButton
*blPopupVarBt.parent: blPopup
*blPopupVarBt.static: true
*blPopupVarBt.name: blPopupVarBt
*blPopupVarBt.labelString: "Variables ..."
*blPopupVarBt.mnemonic: "V"
*blPopupVarBt.activateCallback: { bl_var_cb(); }

*messageBox.class: form
*messageBox.parent: mainPW
*messageBox.static: true
*messageBox.name: messageBox
*messageBox.resizePolicy: "resize_none"
*messageBox.x: 20
*messageBox.y: 470
*messageBox.width: 520
*messageBox.height: 125
*messageBox.paneMinimum: 85

*messageLb.class: label
*messageLb.parent: messageBox
*messageLb.static: true
*messageLb.name: messageLb
*messageLb.x: 25
*messageLb.y: 15
*messageLb.width: 135
*messageLb.height: 15
*messageLb.leftAttachment: "attach_form"
*messageLb.leftOffset: 10
*messageLb.rightAttachment: "attach_form"
*messageLb.topAttachment: "attach_form"
*messageLb.topOffset: 0
*messageLb.alignment: "alignment_beginning"
*messageLb.labelString: "Messages"

*messageSW.class: scrolledWindow
*messageSW.parent: messageBox
*messageSW.static: true
*messageSW.name: messageSW
*messageSW.scrollingPolicy: "application_defined"
*messageSW.x: 0
*messageSW.y: 20
*messageSW.visualPolicy: "variable"
*messageSW.scrollBarDisplayPolicy: "static"
*messageSW.shadowThickness: 0
*messageSW.height: 150
*messageSW.width: 250
*messageSW.bottomAttachment: "attach_form"
*messageSW.leftAttachment: "attach_form"
*messageSW.leftOffset: 0
*messageSW.rightAttachment: "attach_form"
*messageSW.topAttachment: "attach_widget"
*messageSW.topOffset: 2
*messageSW.topWidget: "messageLb"

*messageST.class: scrolledText
*messageST.parent: messageSW
*messageST.static: false
*messageST.name: messageST
*messageST.width: 250
*messageST.height: 160
*messageST.scrollVertical: "true"
*messageST.resizeHeight: "true"
*messageST.resizeWidth: "true"
*messageST.cursorPositionVisible: "false"
*messageST.editable: "false"
*messageST.columns: 80
*messageST.scrollHorizontal: "true"
*messageST.editMode: "multi_line_edit"

*messagePopup.class: rowColumn
*messagePopup.parent: messageST
*messagePopup.static: true
*messagePopup.name: messagePopup
*messagePopup.rowColumnType: "menu_popup"
*messagePopup.menuAccelerator: "<KeyUp>F4"

*titleMessPopup.class: label
*titleMessPopup.parent: messagePopup
*titleMessPopup.static: true
*titleMessPopup.name: titleMessPopup
*titleMessPopup.labelString: "MESSAGE"

*separator10.class: separator
*separator10.parent: messagePopup
*separator10.static: true
*separator10.name: separator10

*clearBt.class: pushButton
*clearBt.parent: messagePopup
*clearBt.static: true
*clearBt.name: clearBt
*clearBt.labelString: "Clear Window"
*clearBt.activateCallback: {\
    extern swidget messageST;\
\
    UxPutText ( messageST, "" );\
}

