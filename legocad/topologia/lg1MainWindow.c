
/*******************************************************************************
	lg1MainWindow.c
	(Generated from interface file lg1MainWindow.i)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

/* Function prototypes for missing functions */
int sensitive(Widget, int);
int set_pixmap_cursor(Widget, const char*);
int undef_cursore(Widget);
int questionDB_activate(const char*);
int messageDB_activate(const char*);
void selModelActivate();
int Idel_graph_bloc();
int del_blocchi(int, int*);
int set_bloc(Widget, void*);
int libera_filtri(void*, int);
int Iadd_new_block_graf(int);
int tominus(char*);
char* trim_blank(char*);
int selgraf_blocco(char*, int);
int lancia_macro(Widget, Widget);
int Iset_graf_new_blname(char*, char*);
int lcDestroySwidget(Widget);
int lcCreateWidget(Widget);
void errore(const char*, ...);

#include <Xm/Text.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/ArrowB.h>
#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/PanedW.h>
#include <Xm/PushBG.h>
#include <Xm/CascadeBG.h>
#include <Xm/SeparatoG.h>
#include <Xm/CascadeB.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/MainW.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME

/*
   modulo lg1MainWindow.i
   tipo 
   release 2.27
   data 5/10/95
   reserved @(#)lg1MainWindow.i	2.27
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif
#ifndef DESIGN_TIME
#include <stdlib.h>
#endif
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#include "UxSubproc.h"


#include "filtri.h"
#include "lg1.h"
#include "question_type.h"
#include "errore.h"
#include "lg1MainWindowType.h"

handle id_subproc=0;

extern void istanzia_blocco();
extern void routine_vuota();
extern swidget instantiationDlg;
extern swidget output_text;
extern Widget topwidget;
/* bl_selezionati:
 * Elenco dei blocchi, contenuti nella lista dei blocchi visualizzata dalla
 * main window, che sono stati selezionati. L'elenco viene aggiornato dalla
 * callback di selezione estesa attivata interagendo con la lista.
 */ 
SELECTION bl_selezionati = { 0, NULL };


/* var_win_list:
 * Lista delle interfacce di tipo varWin attive in un dato istante.
 * Vedi le callback dei bottoni varCloseBt e varBt per l'inserimento e la
 * cancellazione di nuovi elementi dalla lista.
 */
VAR_WIN_TYPE  *var_win_list=NULL;

extern int block_selection_activate();

char blockname[15];
char modulename[15];
char blockdescr[60];

static int found_item=0; /* utilizzato nella search di un modulo */

extern int graphics_on;
extern int modifiche;    /* modifiche nella grafica */

int num_filtri = 0;
FILTRI *filtri[MAXFILTRI];
int ind_filt_default;

/*******************************************************************************
	The following function is an event-handler for posting menus.
*******************************************************************************/

static void	_Uxlg1MainWindowMenuPost( wgt, client_data, event, ctd )
	Widget		wgt;
	XtPointer	client_data;
	XEvent		*event;
	Boolean		*ctd;
{
	Widget	menu = (Widget) client_data;
	int 	which_button;

	XtVaGetValues( menu, XmNwhichButton, &which_button, NULL );

	if ( event->xbutton.button == which_button )
	{
		XmMenuPosition( menu, (XButtonPressedEvent*)event );
		XtManageChild( menu );
	}
}

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
	Widget	UxmenuBar;
	Widget	UxfilePane;
	Widget	UxopenBt;
	Widget	Uxseparator1;
	Widget	UxsaveBt;
	Widget	Uxseparator2;
	Widget	UxexitBt;
	Widget	UxfileCascade;
	Widget	UxeditPane;
	Widget	UxnewPane;
	Widget	UxnewProcessBl;
	Widget	Uxseparator5;
	Widget	UxnewRegBl;
	Widget	UxnewBt;
	Widget	Uxseparator3;
	Widget	UxdeleteBt;
	Widget	Uxseparator4;
	Widget	UxvarBt;
	Widget	UxeditCascade;
	Widget	UxOptionPane;
	Widget	UxDefaultFilterPane;
	Widget	UxNoFilterDef;
	Widget	UxSetDefFilter;
	Widget	Uxseparator6;
	Widget	UxDefineFilter;
	Widget	UxmenuBar_top_b2;
	Widget	UxmainPW;
	Widget	UxmainForm;
	Widget	UxblListLb;
	Widget	UxblSearchBox;
	Widget	UxblSearchLb;
	Widget	UxblSearchTF;
	Widget	UxblSearchUpBt;
	Widget	UxblSearchDownBt;
	Widget	UxblListSW;
	Widget	UxblPopup;
	Widget	UxblPopupLb;
	Widget	UxSeparator50;
	Widget	UxblPopupEditBt;
	Widget	UxblPopupDelBt;
	Widget	UxblPopupVarBt;
	Widget	UxmessageBox;
	Widget	UxmessageLb;
	Widget	UxmessageSW;
	Widget	UxmessagePopup;
	Widget	UxtitleMessPopup;
	Widget	Uxseparator10;
	Widget	UxclearBt;
	swidget	*UxDefFilterButt;
	int	Uxbutton_already_defined;
} _UxClg1MainWindow;

#define menuBar                 UxLg1MainWindowContext->UxmenuBar
#define filePane                UxLg1MainWindowContext->UxfilePane
#define openBt                  UxLg1MainWindowContext->UxopenBt
#define separator1              UxLg1MainWindowContext->Uxseparator1
#define saveBt                  UxLg1MainWindowContext->UxsaveBt
#define separator2              UxLg1MainWindowContext->Uxseparator2
#define exitBt                  UxLg1MainWindowContext->UxexitBt
#define fileCascade             UxLg1MainWindowContext->UxfileCascade
#define editPane                UxLg1MainWindowContext->UxeditPane
#define newPane                 UxLg1MainWindowContext->UxnewPane
#define newProcessBl            UxLg1MainWindowContext->UxnewProcessBl
#define separator5              UxLg1MainWindowContext->Uxseparator5
#define newRegBl                UxLg1MainWindowContext->UxnewRegBl
#define newBt                   UxLg1MainWindowContext->UxnewBt
#define separator3              UxLg1MainWindowContext->Uxseparator3
#define deleteBt                UxLg1MainWindowContext->UxdeleteBt
#define separator4              UxLg1MainWindowContext->Uxseparator4
#define varBt                   UxLg1MainWindowContext->UxvarBt
#define editCascade             UxLg1MainWindowContext->UxeditCascade
#define OptionPane              UxLg1MainWindowContext->UxOptionPane
#define DefaultFilterPane       UxLg1MainWindowContext->UxDefaultFilterPane
#define NoFilterDef             UxLg1MainWindowContext->UxNoFilterDef
#define SetDefFilter            UxLg1MainWindowContext->UxSetDefFilter
#define separator6              UxLg1MainWindowContext->Uxseparator6
#define DefineFilter            UxLg1MainWindowContext->UxDefineFilter
#define menuBar_top_b2          UxLg1MainWindowContext->UxmenuBar_top_b2
#define mainPW                  UxLg1MainWindowContext->UxmainPW
#define mainForm                UxLg1MainWindowContext->UxmainForm
#define blListLb                UxLg1MainWindowContext->UxblListLb
#define blSearchBox             UxLg1MainWindowContext->UxblSearchBox
#define blSearchLb              UxLg1MainWindowContext->UxblSearchLb
#define blSearchTF              UxLg1MainWindowContext->UxblSearchTF
#define blSearchUpBt            UxLg1MainWindowContext->UxblSearchUpBt
#define blSearchDownBt          UxLg1MainWindowContext->UxblSearchDownBt
#define blListSW                UxLg1MainWindowContext->UxblListSW
#define blPopup                 UxLg1MainWindowContext->UxblPopup
#define blPopupLb               UxLg1MainWindowContext->UxblPopupLb
#define Separator50             UxLg1MainWindowContext->UxSeparator50
#define blPopupEditBt           UxLg1MainWindowContext->UxblPopupEditBt
#define blPopupDelBt            UxLg1MainWindowContext->UxblPopupDelBt
#define blPopupVarBt            UxLg1MainWindowContext->UxblPopupVarBt
#define messageBox              UxLg1MainWindowContext->UxmessageBox
#define messageLb               UxLg1MainWindowContext->UxmessageLb
#define messageSW               UxLg1MainWindowContext->UxmessageSW
#define messagePopup            UxLg1MainWindowContext->UxmessagePopup
#define titleMessPopup          UxLg1MainWindowContext->UxtitleMessPopup
#define separator10             UxLg1MainWindowContext->Uxseparator10
#define clearBt                 UxLg1MainWindowContext->UxclearBt
#define DefFilterButt           UxLg1MainWindowContext->UxDefFilterButt
#define button_already_defined  UxLg1MainWindowContext->Uxbutton_already_defined

static _UxClg1MainWindow	*UxLg1MainWindowContext;

Widget	lg1MainWindow;
Widget	modNameLb;
Widget	blListSL;
Widget	messageST;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_lg1MainWindow();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/* 
 * int set_bl_list()
 *
 * Scrive nella lista dei blocchi visualizzata dalla main window
 * le descrizioni dei blocchi contenuti in memoria nella variabile 'blocchi'.
 */
extern ERR_LEVEL err_level;

int set_bl_list()
{

   extern swidget blListSL;

   Arg      arg[2];
   char     entry[81];
   XmString *lista;
   int      i;
   BLOCCO   *bloc=blocchi;  /* serve a causa dell'interprete uimx */



   /* 
    * Gestisce il caso in cui non  ci sono blocchi in memoria. 
    * Cio' capita all'inizio e ogni volta che fallisce una operazione di 
    * apertura di nuovo modello.
    */
   if ( ! num_blocchi )
   {
      XtSetArg(arg[0], XmNitems, NULL);
      XtSetArg(arg[1], XmNitemCount, 0);   
      XtSetValues(UxGetWidget(blListSL), arg, 2);
      return 0;
   } 



   /* 
    * Costruisce la lista degli identificatori dei blocchi.
    */
   lista = ( XmString * ) malloc ( num_blocchi * sizeof(XmString) );

   for (i=0; i<num_blocchi; i++ )
   {
      strcpy ( entry, bloc[i].sigla_modulo ); 
      strcat ( entry,  " (" );
      strcat ( entry, bloc[i].sigla_blocco );
      strcat ( entry,  ")  " );
      strcat ( entry, bloc[i].descr_blocco );
      lista[i]=XmStringCreateSimple(entry);  
   }


   /*
    * Trasferisce la lista nel widget 'blListSL'.
    */
   XtSetArg(arg[0], XmNitems, lista);
   XtSetArg(arg[1], XmNitemCount, num_blocchi);   
   XtSetValues(UxGetWidget(blListSL), arg, 2);

   /* 
    * Libera la memoria utilizzata per costruire la lista.
    */
   for ( i=0; i<num_blocchi; i++ )
      XmStringFree(lista[i]); 
//      XtFree(lista[i]); 

   XtFree( (char*)lista );


}




/*
 * int set_model_name()
 *
 * Scrive il nome del modello nel widget 'modNAmeLb'.
 */
int set_model_name()
{
  extern swidget   modNameLb;
  extern char      *str_toupper();
  extern char      nome_modello[];
  
  char app[100];


  if ( err_level == ERROR )
     UxPutLabelString(modNameLb,"No model selected");
  else
  {
     str_toupper(nome_modello);
     sprintf(app,"Model name: %s",nome_modello);  
     UxPutLabelString(modNameLb,app);
  }
}





/*
 * write_message()
 *
 * Appende un messaggio nel widget 'messageSt'.
 */
int write_message( mess )
char *mess;
{
  char   *str, *new_str;
  extern swidget messageST;


  /*
   * Ottiene la stringa contenuta nel widget. 
   */
  str = UxGetText( messageST );

  /*
   * costruisce la nuova stringa.
   */
  new_str = (char*) malloc ( sizeof(char*) * ( strlen(mess)+strlen(str)+1 ) );
  strcpy( new_str, str );
  if ( *str )
     strcat( new_str, "\n\n" );
  strcat( new_str, mess );

  /*
   * Introduce nel widget la nuova stringa.
   */
  UxPutText( messageST, new_str );

  /*
   * Libera la memoria utilizzata.
   */
  free( str );
  free( new_str );

}




/*
 * main_win_setup()
 *
 * Settaggio dei menu puldown e del menu popup della main window.
 * Si setta l'attributo sensitive dei vari bottoni e lo stato dei toggle button.
 */
int main_menu_setup()
{

   /*
    * Settaggio dei bottoni di attivazione delle interfacce contenenti gli 
    * elenchi delle variabili.
    */
   if ( bl_selezionati.num  ==  1 )
   { 
     sensitive( blPopupVarBt, True );
     sensitive( varBt, True );
     sensitive( blPopupEditBt, True );
   }
   else
   {
     sensitive( blPopupVarBt, False );
     sensitive( varBt, False );
     sensitive( blPopupEditBt, False);
   }


   /*
    * Settaggio dei bottoni di cancellazione dei blocchi.
    */
   if ( bl_selezionati.num )
   {
     sensitive( blPopupDelBt, True );
     sensitive( deleteBt, True );
   }
   else
   {
     sensitive( blPopupDelBt, False );
     sensitive( deleteBt, False );
   }

   sensitive( newRegBl, True );

}


int desel_open_but()
{
   sensitive(openBt,False);
}

/*
 * sensitive()
 *
 * Setta l'attributo 'sensitive' di un bottone.
 */
int sensitive( swid, val )
swidget swid;
int     val;
{
   Arg arg;

   XtSetArg( arg, XmNsensitive, val );
   XtSetValues( UxGetWidget(swid), &arg, 1 );
}








/*
 * set_win_cursor()
 *
 * Setta il cursore per la main window e per le interfacce 'varWin' attive.
 */
int set_win_cursors( cursor )
char *cursor;
{
   VAR_WIN_TYPE *cur;


   set_pixmap_cursor( UxGetWidget(lg1MainWindow), cursor );

   for ( cur=var_win_list; cur; cur=cur->succ )
      set_pixmap_cursor( UxGetWidget(cur->swid), cursor );

}




/*
 * reset_win_cursors()
 *
 * Ristabilisce il cursore di sistema per la main window e le window delle
 * interfacce 'varWin' attive.
 */
int reset_win_cursors()
{
   VAR_WIN_TYPE *cur;


   undef_cursore( UxGetWidget(lg1MainWindow) );

   for ( cur=var_win_list; cur; cur=cur->succ )
      undef_cursore( UxGetWidget(cur->swid) );

}



/*
 * bl_del_cb()
 *
 * Funzione che viene attivata quando si richiede di cancellare un insieme
 * di blocchi.
 * Essa attiva l'interfaccia 'questionDB' per chiedere conferma della 
 * cancellazione.
 */
int bl_del_cb()
{
   extern QUESTION question;
   char str[1024];
   int i;
   BLOCCO *bloc=blocchi;


   if ( bl_selezionati.num<15 )
   {
      strcpy( str, "Do yuo want delete these blocks?" );

      for ( i=0; i<bl_selezionati.num; i++ )
      {
        strcat( str, "\n     " );
        strcat( str, bloc[bl_selezionati.pos[i]].label );
      }
   }
   else
      strcpy( str, "Do yuo want delete the selected blocks?" );

   
   question = QST_DEL_BL;

   questionDB_activate( str );

}





/* 
 * bl_del_qst_cb()
 *
 * La funzione viene attivata quando si conferma la cancellazione di un insieme 
 * di blocchi.
 */
int bl_del_qst_cb()
{
  extern int changes_in_F01;

  int i;
  VAR_WIN_TYPE *cor;


  /* cancellazione blocchi dalla pagina grafica */
  /*printf("test step bl_del_qst_cb bl_selezionati.num %d\n",bl_selezionati.num);*/
  if(graphics_on == True)
     Idel_graph_bloc();

  /*
   * Cancellazione dei blocchi nel vettore 'blocchi[]'.
   */

  /*printf("test step 1 bl_del_qst_cb bl_selezionati.num %d\n",bl_selezionati.num);*/
  
/* introduco il test per verificare che ci siano blocchi selezionati
   nella lista, perche' potrebbero essere di tipo simbolo o remark
  nella grafica
*/

  if(bl_selezionati.num)
     del_blocchi ( bl_selezionati.num, bl_selezionati.pos );
  else
     return 0;

  /*printf("test step 2 bl_del_qst_cb\n");*/


  /*
   * Cancellazione dell'identificatore del bloccho dalla lista dei blocchi
   * visualizzata dalla main window.
   * Distruzione delle interfacce 'varWin' associate ai blocchi cancellati.
   */
  for ( i=bl_selezionati.num-1; i>-1; i-- )
  {
    XmListDeletePos( UxGetWidget(blListSL), bl_selezionati.pos[i]+1 );
 
    for ( cor=var_win_list; cor; cor=cor->succ )
       if ( bl_selezionati.pos[i] == cor->bloc )
         break;

    if ( cor )
      UxDestroyInterface( cor->swid );
  }



  /*
   * Aggiorna il campo 'bloc' degli elementi della lista 'var_win_list'.
   * Se un interfaccia era associata al blocco 3 e i blocchi 1 e 2 vengono
   * cancellati, (poiche il blocco 3 ora e' diventato il blocco 1) il campo
   * 'bloc' deve essere posto a 1.
   */
  for ( i=bl_selezionati.num-1; i>-1; i-- )
    for ( cor=var_win_list; cor; cor=cor->succ )
       if ( cor->bloc > bl_selezionati.pos[i] )
          (cor->bloc)--;


  /*
   * Setta la variabile locale 'blocco' di ogni interfaccia 'varWin'
   * con il nuovo valore calcolato del campo 'bloc'
   */
  for ( cor=var_win_list; cor; cor=cor->succ )
     set_bloc( cor->swid, (void*)(intptr_t)cor->bloc );


  /*
   * I blocchi selezionati sono stati cancellati quindi non ci sono piu' 
   * blocchi selezionati.
   */
  free ( bl_selezionati.pos );
  bl_selezionati.pos = NULL;
  bl_selezionati.num = 0;



  /*
   * Sono stati effettuati cambiamenti nel modello presente in memoria
   * che ora non rispetta piu' il contenuto del file f01 originario.
   */
  changes_in_F01 = True;

}




/* 
 * bl_var_cb()
 *
 * La funzione viene attivata quando si vogliono visualizzare le variabili di 
 * blocco selezionato.
 * Esa attiva l'interfaccia 'varWin' per il blocco selezionato ed inserisce
 * un elemento corrispondente nella lista 'var_win_list'.
 */
int bl_var_cb()
{
   extern swidget create_varWin();
   swidget swid;
   VAR_WIN_TYPE *new_var, *cor;



   /* 
    * Controlla se per il blocco selezionato e' gia stata attivata
    * un'interfaccia di tipo 'varWin'.
    */
   for ( cor=var_win_list; cor; cor=cor->succ )
      if ( bl_selezionati.pos[0] == cor->bloc )
        break;


   /*
    * Se esiete gia' l'interfaccia 'varWin' viene fatto un raise della stessa.
    */
   if ( cor )
   {
      XRaiseWindow( XtDisplay(UxGetWidget(cor->swid)),
                    XtWindow(XtParent(UxGetWidget(cor->swid))) );
      return 0;
   }



   /*
    * Creazione di una nuova interfaccia.
    */
   swid = create_varWin( bl_selezionati.pos[0] );
   UxPopupInterface( swid, no_grab );


   /*
    * Inserimento della nuova interfaccia nella lista 'var_win_list'.
    */
   new_var       = (VAR_WIN_TYPE*) malloc( sizeof( VAR_WIN_TYPE ) );
   new_var->bloc = bl_selezionati.pos[0];
   new_var->swid = swid;
   new_var->succ = var_win_list;

   var_win_list       = new_var;

}



extern int num_modulo;
extern char s_num_modulo[10];

void routine_vuota()
{
    UxPopdownInterface(instantiationDlg);
}


int do_dialogo()
{


   char str_num_modulo[10];
   char path[300],fnamexe[200];
   sprintf(str_num_modulo,"%d",num_modulo);
   strcpy(path , getenv("LEGOCAD_USER"));
   strcpy(fnamexe,path);
   strcat(fnamexe,"/legocad/libut/legoserver");
   if(id_subproc)
	UxDeleteSubproc(id_subproc);
   id_subproc = UxCreateSubproc(fnamexe,str_num_modulo,UxAppendTo);
   if(id_subproc == -1)
   {
      printf("Can't start subprocess\n");
      err_level = ERROR;
      printf("ERROR: Can't start subprocess\n");
      return(1);
   }

   UxSetSubprocEcho(id_subproc,1); /* setta l'eco sulla window di testo */

   if(-1 == UxSetSubprocClosure(id_subproc,UxGetWidget(output_text)))
   {
      printf("Can't set subproc closure \n");
      err_level = ERROR;
      printf("ERROR: Can't set subproc closure\n");
      return(1);
   }


   if(-1 ==UxSetSubprocExitCallback(id_subproc,istanzia_blocco))
   {
      printf("Can't set exit callback \n");
      err_level = ERROR;
      printf("ERROR: Can't set subproc closure\n");
      return(1);
   }
   if(-1 == UxRunSubproc(id_subproc,str_num_modulo))
   {
      printf("\n Can't start the application\n");
      err_level = ERROR;
      printf("ERROR: Can't set subproc closure\n");
      return(1);
   }
   UxPopupInterface(instantiationDlg,no_grab);


}






int del_block_from_list()
{
  extern int changes_in_F01;

  int i;
  VAR_WIN_TYPE *cor;

  /*
   * Cancellazione dei blocchi nel vettore 'blocchi[]'.
   */

  del_blocchi ( bl_selezionati.num, bl_selezionati.pos );

 /*
   * Cancellazione dell'identificatore del bloccho dalla lista dei blocchi
   * visualizzata dalla main window.
   * Distruzione delle interfacce 'varWin' associate ai blocchi cancellati.
   */
  for ( i=bl_selezionati.num-1; i>-1; i-- )
  {
    XmListDeletePos( UxGetWidget(blListSL), bl_selezionati.pos[i]+1 );

    for ( cor=var_win_list; cor; cor=cor->succ )
       if ( bl_selezionati.pos[i] == cor->bloc )
         break;

    if ( cor )
      UxDestroyInterface( cor->swid );
  }

  /*
   * Aggiorna il campo 'bloc' degli elementi della lista 'var_win_list'.
   * Se un interfaccia era associata al blocco 3 e i blocchi 1 e 2 vengono
   * cancellati, (poiche il blocco 3 ora e' diventato il blocco 1) il campo
   * 'bloc' deve essere posto a 1.
   */
  for ( i=bl_selezionati.num-1; i>-1; i-- )
    for ( cor=var_win_list; cor; cor=cor->succ )
       if ( cor->bloc > bl_selezionati.pos[i] )
          (cor->bloc)--;
  


  /*
   * Setta la variabile locale 'blocco' di ogni interfaccia 'varWin'
   * con il nuovo valore calcolato del campo 'bloc'
   */
  for ( cor=var_win_list; cor; cor=cor->succ )
     set_bloc( cor->swid, (void*)(intptr_t)cor->bloc );


/*
   * I blocchi selezionati sono stati cancellati quindi non ci sono piu'
   * blocchi selezionati.
   */
  free ( bl_selezionati.pos );
  bl_selezionati.pos = NULL;
  bl_selezionati.num = 0;
  /*
   * Sono stati effettuati cambiamenti nel modello presente in memoria
   * che ora non rispetta piu' il contenudeto del file f01 originario.
   */
  changes_in_F01 = True;
 
}

/*
 * bl_edit_cb()
 *
 * Funzione che viene attivata quando si richiede di editare la descrizione
 * di un blocco.
 */

int bl_edit_cb()
{
   extern swidget EditDescrDialog1; 
   extern swidget BlocName;
   extern swidget ModuleName;
   BLOCCO *bloc = blocchi;  /* frego UIMX */
   char *descr;


   descr = bloc[ bl_selezionati.pos[0] ].descr_blocco;   
   UxPopupInterface(EditDescrDialog1,no_grab);
   UxPutLabelString(ModuleName,bloc[ bl_selezionati.pos[0] ].sigla_modulo);
   UxPutText(BlocName,bloc[ bl_selezionati.pos[0] ].sigla_blocco);
   UxPutTextString(EditDescrDialog1,descr);
}  

void set_new_descr(char *new_bl_name,char *new_descr)
{
   extern int changes_in_F01;
   int i;
   char entry[200],*appstr,oldlabel[9];
   XmString item;
   BLOCCO *bloc = blocchi;  /* frego UIMX */

/* posso aver modificato solo la descrizione */
   if( !strcmp(new_bl_name,bloc[ bl_selezionati.pos[0] ].sigla_blocco) )
      strcpy( bloc[ bl_selezionati.pos[0] ].descr_blocco, new_descr);   
   else
   {
/* verifico la univocita' del nome del blocco */
      for(i=0;i<num_blocchi;i++)
         if( !strcmp(new_bl_name,bloc[i].sigla_blocco) )
         {
            err_level = ERROR;
            errore("nome blocco gia' utilizzato %s",bloc[i].label);
            return;
         }
/* modifiche alla desrizione */
      strcpy( bloc[ bl_selezionati.pos[0] ].descr_blocco, new_descr);

/* e alla sigla blocco */
      strcpy(bloc[ bl_selezionati.pos[0] ].sigla_blocco,new_bl_name);
          
/* alle variabili */
      for(i=0;i<bloc[ bl_selezionati.pos[0] ].num_variabili;i++)
      {
         appstr = &bloc[ bl_selezionati.pos[0] ].variabili[i].nome[4];
         strcpy(appstr,new_bl_name);  
      }

/* alla label */
      appstr = &bloc[ bl_selezionati.pos[0] ].label[4];
      strcpy(appstr,new_bl_name);

/* modifico il nome del blocco nella grafica */
      if( graphics_on )
      {
         strcpy(oldlabel,bloc[bl_selezionati.pos[0]].sigla_modulo);
         strcat(oldlabel,bloc[bl_selezionati.pos[0]].sigla_blocco);

         Iset_graf_new_blname(oldlabel,new_bl_name);
      }
   }

/* sistemo la lista */
   strcpy ( entry, bloc[bl_selezionati.pos[0] ].sigla_modulo ); 
   strcat ( entry,  " (" );
   strcat ( entry, bloc[bl_selezionati.pos[0]].sigla_blocco );
   strcat ( entry,  ")  " );
   strcat ( entry, bloc[bl_selezionati.pos[0]].descr_blocco );
 
   item = (XmString)XmStringCreateSimple(entry);
   XmListDeletePos( UxGetWidget(blListSL), bl_selezionati.pos[0]+1 );
   XmListAddItem(UxGetWidget(blListSL),item,bl_selezionati.pos[0]+1);
   XmStringFree(item);
   XmListSelectPos( UxGetWidget(blListSL), bl_selezionati.pos[0]+1, False);

   changes_in_F01 = True;

}


void add_item(char *buff,int pos)
{
   extern swidget blListSL;
   XmString *item;

   
/*
   con pos = 0 viene aggiunto in fondo
   con pos = 1 viene aggiunto in cima 
   con pos = n viene aggiunto alla ennesima posizione
*/
   if(pos > num_blocchi)
   {
      err_level = ERROR;
      errore("Item out of sequence");
      return;
   }

   
   item = ( XmString *) malloc( sizeof(XmString) );

   *item = (XmString)XmStringCreateSimple( buff );

   XmListAddItem(UxGetWidget(blListSL),*item,pos);  
   XmStringFree(*item);
   XtFree((char*)item);
}




/* aggiungo items al menu di set default filter */

int DefFilterCB(Widget w,int ind_filtro, XmAnyCallbackStruct *call_data)
{
   printf("Callback della opzione %d dei filtri\n",ind_filtro+1);


/* inizializzo la variabile globale del filtro di default */
 
   ind_filt_default = ind_filtro+1;
/*   printf("n. filtro di default %d\n",ind_filt_default); */

}

void add_filter_button()
{
   extern int num_filtri;
   extern FILTRI *filtri[];
   int i,j;
   char label_button[20];

printf("DEBUG add_filter_button: button_already_defined=%d num_filtri=%d\n",button_already_defined,num_filtri);

   if(button_already_defined)
   {
      for(i=0; i < num_filtri; i++)
         UxDestroySwidget( DefFilterButt[i] );
      button_already_defined = False;
   }

   DefFilterButt = (swidget *)calloc( num_filtri,sizeof(swidget) );

   printf("definizione push button filtri = %d\n",num_filtri);

   for(i=0; i < num_filtri; i++)
   {
   /*creo i push button */

      strcpy(label_button,filtri[i]->nome_filtro);
      DefFilterButt[i] = UxCreatePushButton(label_button,DefaultFilterPane);
      UxPutLabelString(DefFilterButt[i],label_button);
      UxCreateWidget(DefFilterButt[i]);

/* e definisco la callback */
      UxAddCallback(DefFilterButt[i],XmNactivateCallback,(XtCallbackProc)DefFilterCB,(XtPointer)(intptr_t)i);
   }
   button_already_defined = True;
}  

void elimina_filter_button()
{
   int i;

   if(button_already_defined)
   {
      for(i=0; i < num_filtri; i++)
      {
         printf("DefFilterButt[%d]=%d\n",i,DefFilterButt[i]);
         UxDestroySwidget( DefFilterButt[i] );
      }
      button_already_defined = False;
   }
}

int def_filtri()
{
   extern int inizializza_filtri();
  
/*printf("lancio la libera_filtri   num_filtri = %d\n");*/
   if(num_filtri)
   {
      elimina_filter_button();
      libera_filtri(filtri,num_filtri);
   }
/*printf("lancio la inizializza_filtri\n");*/
   if(inizializza_filtri(filtri,&num_filtri) == -1)
   { 
      err_level = ERROR;
      errore("ERROR Cannot open $HOME/filtri.edf\n"); 
      return(0);
   }
/*printf("lancio la add_filter_butt\n");*/
   if(num_filtri)
      add_filter_button();    
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_openBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	selModelActivate();
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_saveBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{
	extern int changes_in_F01;
	extern int modifiche;
	extern int write_f01();
	extern int Isalva_grafica();
	
	   if(changes_in_F01 || modifiche)
	   {
	      printf("Some changes made, saving...\n");
	      write_f01();
	      if(graphics_on)
	         Isalva_grafica();
	      messageDB_activate("Topology saved.");      
	   }
	   else
	   {
	             messageDB_activate("No changes made, do nothing...");      
	   }
	}
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_exitBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{
	   extern int      changes_in_F01;
	   extern QUESTION question;
	
	
	   question = QST_USCITA;
	
	   if ( changes_in_F01 )
	     questionDB_activate( "F01 has been modified! \nDo you really want exit?" );
	   else
	     questionDB_activate( "Do you really want exit?" );
	
	}
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_newProcessBl( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	if(graphics_on == False)
	   block_selection_activate(PROCESSO);   
	else
	   Iadd_new_block_graf(PROCESSO);
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_newRegBl( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	if(graphics_on == False)
	   block_selection_activate(REGOLAZIONE);
	else 
	   Iadd_new_block_graf(REGOLAZIONE);
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_deleteBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	bl_del_cb();
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_varBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	bl_var_cb();
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_NoFilterDef( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{
	   extern int ind_filt_default;
	
	   ind_filt_default = 0;
	}
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_DefineFilter( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{
	  char nome[200];
	
	  if(var_win_list != NULL)
	  {
	     messageDB_activate("This program can't run \nwith variables window open");
	     return;
	  }
	
	  strcpy(nome,getenv("LEGOCAD_BIN"));  
	  strcat(nome,"/filtri");
	
#ifndef DESIGN_TIME
	   signal(SIGCHLD,(void(*)(int))def_filtri);
	   if(!vfork())
	      execlp(nome,nome,(char *)0);
#endif
	
	}
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_blSearchUpBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{
	int i,appo;
	extern int found_item;
	char *buff;
	char riferimento[100];
	BLOCCO *bloc = blocchi; /* per ingannare l'interprete */
	
	buff = UxGetText( blSearchTF );
	
	if(buff != NULL) 
	{
	   tominus(trim_blank(buff));
	
	   printf("search for text %s\n",buff);
	
	   appo=found_item-2;
	
	   for(i=appo;i>=0;i--)
	   {
	      
	      strcpy(riferimento,bloc[i].sigla_modulo);
	      tominus(trim_blank(riferimento));
	      strcat(riferimento,bloc[i].sigla_blocco);
	      tominus(trim_blank(riferimento));
	      strcat(riferimento,bloc[i].descr_blocco);
	      tominus(trim_blank(riferimento));
	/*
	      printf("stringa di riferimento %s\n",riferimento);
	*/
	      if( strstr(riferimento,buff) )
	      {
	         found_item = i+1;
	         break;
	      }
	
	   }
	      
	   if(found_item)
	   {
	      printf("found string in position %d\n",found_item);
	/*
	      XmListSelectPos( UxGetWidget(blListSL),found_item,True);
	*/
	      XmListSetPos(UxGetWidget(blListSL),found_item);
	   }
	}
	}
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_blSearchDownBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{
	int i;
	extern int found_item;
	char *buff;
	char riferimento[100];
	BLOCCO *bloc = blocchi; /* per ingannare l'interprete */
	
	buff = UxGetText( blSearchTF );
	
	if(buff != NULL)
	{
	   tominus(trim_blank(buff));
	
	   printf("search for text %s\n",buff);
	
	   
	   for(i=found_item;i<num_blocchi;i++)
	   {
	      strcpy(riferimento,bloc[i].sigla_modulo);
	      tominus(trim_blank(riferimento));
	      strcat(riferimento,bloc[i].sigla_blocco);
	      tominus(trim_blank(riferimento));
	      strcat(riferimento,bloc[i].descr_blocco);
	      tominus(trim_blank(riferimento));
	/*
	      printf("stringa di riferimento %s\n",riferimento);
	*/
	      if( strstr(riferimento,buff) )
	      {
	         found_item = i+1;
	         break;
	      }
	   }
	
	   if(found_item)
	   {   
	      printf("found string in position %d\n",found_item);
	
	/*
	      XmListSelectPos( UxGetWidget(blListSL),found_item,True);
	*/
	      XmListSetPos(UxGetWidget(blListSL),found_item);
	      printf("VItem visibili = %d\n",UxGetVisibleItemCount(blListSL));  
	   }
	}
	}
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	singleSelectionCB_blListSL( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{
	
	}
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	extendedSelectionCB_blListSL( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{
	XmListCallbackStruct *cb;
	int i;
	char labelbl[10];
	SELECTION appo;
	
	cb = (XmListCallbackStruct *) UxCallbackArg;
	
	/*
	 * Libera la struttura 'bl_selezionati' dopo aver deselezionato i relativi blocchi
	 * nella window di grafica.
	 */
	
	if ( bl_selezionati.pos )
	{
	
	  if(graphics_on)
	  {
	     /*** e' necessario salvare la situazione dei selezionati   
	          perche' viene manipolata nella selgraf->seleziona_blocco ***/
	
	     appo.num = bl_selezionati.num;
	     appo.pos = (int *) malloc ( sizeof(int) * appo.num );
	     memcpy (appo.pos, bl_selezionati.pos, 
	           sizeof(int) * appo.num );
	          
	     for ( i=0; i<appo.num; i++ )
	     {
	       strcpy(labelbl,blocchi[appo.pos[i]].sigla_modulo);
	       strcat(labelbl,blocchi[appo.pos[i]].sigla_blocco);
	       selgraf_blocco(labelbl,False);
	     }
	  }
	  
	  free ( bl_selezionati.pos );
	}
	
	/* aggiornamento della situazione attuale */
	
	bl_selezionati.num = cb->selected_item_count;
	
	
	if ( bl_selezionati.num )
	{
	
	  /*
	   * Trasferimento della selezione dalla struttura 'cb' alla struttura
	   * 'bl_selezionati'.
	   */
	  bl_selezionati.pos = (int *) malloc ( sizeof(int) *  bl_selezionati.num );
	
	  memcpy ( bl_selezionati.pos, cb->selected_item_positions, 
	           sizeof(int) * bl_selezionati.num );
	
	  /*
	   * I campi 'pos' vengono decrementati per poterli utilizzare come indici
	   * nel vettore 'blocchi[]'.
	   */
	  printf("bl_selezionati.num = %d\n",bl_selezionati.num);
	
	  for ( i=0; i<bl_selezionati.num; i++ )
	  {
	    bl_selezionati.pos[i] -= 1;
	/****    printf("bl_selezionati.pos[%d] = %d \n",i,bl_selezionati.pos[i]); ***/
	  }
	
	  for ( i=0; i<bl_selezionati.num; i++ )
	    if(graphics_on)
	    {
	       strcpy(labelbl,blocchi[bl_selezionati.pos[i]].sigla_modulo);
	       strcat(labelbl,blocchi[bl_selezionati.pos[i]].sigla_blocco);
	       selgraf_blocco(labelbl,True);
	    }  
	}
	else 
	  bl_selezionati.pos = NULL; 
	
	/*
	 * Setta i menu in relazione alla nuova situazione causata dal cambiamento 
	 * della selezione.
	 */
	
	int main_menu_setup();
	
	}
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_blPopupEditBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{bl_edit_cb(); }
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_blPopupDelBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{ bl_del_cb(); }
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_blPopupVarBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{ bl_var_cb(); }
	UxLg1MainWindowContext = UxSaveCtx;
}

static void	activateCB_clearBt( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxClg1MainWindow       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLg1MainWindowContext;
	UxLg1MainWindowContext = UxContext =
			(_UxClg1MainWindow *) UxGetContext( UxWidget );
	{
	    extern swidget messageST;
	
	    UxPutText ( messageST, "" );
	}
	UxLg1MainWindowContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_lg1MainWindow()
{
	Widget	lg1MainWindow_shell;
	Widget	filePane_shell;
	Widget	editPane_shell;
	Widget	newPane_shell;
	Widget	OptionPane_shell;
	Widget	DefaultFilterPane_shell;
	Widget	blPopup_shell;
	Widget	messagePopup_shell;

	lg1MainWindow_shell = XtVaCreatePopupShell( "lg1MainWindow_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 685,
			XmNy, 35,
			XmNwidth, 560,
			XmNheight, 635,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "lg1MainWindow",
			XmNiconName, "lg1MainWindow",
			NULL );

	lg1MainWindow = XtVaCreateManagedWidget( "lg1MainWindow",
			xmMainWindowWidgetClass, lg1MainWindow_shell,
			XmNheight, 635,
			XmNwidth, 560,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( lg1MainWindow, (char *) UxLg1MainWindowContext );

	menuBar = XtVaCreateManagedWidget( "menuBar",
			xmRowColumnWidgetClass, lg1MainWindow,
			XmNspacing, 0,
			XmNmenuAccelerator, "<KeyUp>F10",
			XmNrowColumnType, XmMENU_BAR,
			NULL );

	UxPutContext( menuBar, (char *) UxLg1MainWindowContext );

	filePane_shell = XtVaCreatePopupShell ("filePane_shell",
			xmMenuShellWidgetClass, menuBar,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	filePane = XtVaCreateWidget( "filePane",
			xmRowColumnWidgetClass, filePane_shell,
			XmNspacing, 0,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( filePane, (char *) UxLg1MainWindowContext );

	openBt = XtVaCreateManagedWidget( "openBt",
			xmPushButtonWidgetClass, filePane,
			RES_CONVERT( XmNmnemonic, "O" ),
			RES_CONVERT( XmNlabelString, "Open" ),
			NULL );

	UxPutContext( openBt, (char *) UxLg1MainWindowContext );

	separator1 = XtVaCreateManagedWidget( "separator1",
			xmSeparatorWidgetClass, filePane,
			NULL );

	UxPutContext( separator1, (char *) UxLg1MainWindowContext );

	saveBt = XtVaCreateManagedWidget( "saveBt",
			xmPushButtonWidgetClass, filePane,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Save" ),
			NULL );

	UxPutContext( saveBt, (char *) UxLg1MainWindowContext );

	separator2 = XtVaCreateManagedWidget( "separator2",
			xmSeparatorWidgetClass, filePane,
			NULL );

	UxPutContext( separator2, (char *) UxLg1MainWindowContext );

	exitBt = XtVaCreateManagedWidget( "exitBt",
			xmPushButtonWidgetClass, filePane,
			XmNsensitive, TRUE,
			RES_CONVERT( XmNmnemonic, "E" ),
			RES_CONVERT( XmNlabelString, "Exit" ),
			NULL );

	UxPutContext( exitBt, (char *) UxLg1MainWindowContext );

	fileCascade = XtVaCreateManagedWidget( "fileCascade",
			xmCascadeButtonWidgetClass, menuBar,
			XmNsubMenuId, filePane,
			RES_CONVERT( XmNmnemonic, "F" ),
			RES_CONVERT( XmNlabelString, "File" ),
			NULL );

	UxPutContext( fileCascade, (char *) UxLg1MainWindowContext );

	editPane_shell = XtVaCreatePopupShell ("editPane_shell",
			xmMenuShellWidgetClass, menuBar,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	editPane = XtVaCreateWidget( "editPane",
			xmRowColumnWidgetClass, editPane_shell,
			XmNentryAlignment, XmALIGNMENT_BEGINNING,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( editPane, (char *) UxLg1MainWindowContext );

	newPane_shell = XtVaCreatePopupShell ("newPane_shell",
			xmMenuShellWidgetClass, editPane,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	newPane = XtVaCreateWidget( "newPane",
			xmRowColumnWidgetClass, newPane_shell,
			XmNentryAlignment, XmALIGNMENT_BEGINNING,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( newPane, (char *) UxLg1MainWindowContext );

	newProcessBl = XtVaCreateManagedWidget( "newProcessBl",
			xmPushButtonWidgetClass, newPane,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "Process Block" ),
			NULL );

	UxPutContext( newProcessBl, (char *) UxLg1MainWindowContext );

	separator5 = XtVaCreateManagedWidget( "separator5",
			xmSeparatorGadgetClass, newPane,
			NULL );

	UxPutContext( separator5, (char *) UxLg1MainWindowContext );

	newRegBl = XtVaCreateManagedWidget( "newRegBl",
			xmPushButtonWidgetClass, newPane,
			RES_CONVERT( XmNlabelString, "Regulation Block" ),
			NULL );

	UxPutContext( newRegBl, (char *) UxLg1MainWindowContext );

	newBt = XtVaCreateManagedWidget( "newBt",
			xmCascadeButtonWidgetClass, editPane,
			XmNstringDirection, XmSTRING_DIRECTION_L_TO_R,
			XmNsubMenuId, newPane,
			RES_CONVERT( XmNlabelString, "New" ),
			NULL );

	UxPutContext( newBt, (char *) UxLg1MainWindowContext );

	separator3 = XtVaCreateManagedWidget( "separator3",
			xmSeparatorGadgetClass, editPane,
			NULL );

	UxPutContext( separator3, (char *) UxLg1MainWindowContext );

	deleteBt = XtVaCreateManagedWidget( "deleteBt",
			xmPushButtonWidgetClass, editPane,
			RES_CONVERT( XmNmnemonic, "D" ),
			RES_CONVERT( XmNlabelString, "Delete" ),
			NULL );

	UxPutContext( deleteBt, (char *) UxLg1MainWindowContext );

	separator4 = XtVaCreateManagedWidget( "separator4",
			xmSeparatorGadgetClass, editPane,
			NULL );

	UxPutContext( separator4, (char *) UxLg1MainWindowContext );

	varBt = XtVaCreateManagedWidget( "varBt",
			xmPushButtonWidgetClass, editPane,
			RES_CONVERT( XmNmnemonic, "V" ),
			RES_CONVERT( XmNlabelString, "Variables ..." ),
			NULL );

	UxPutContext( varBt, (char *) UxLg1MainWindowContext );

	editCascade = XtVaCreateManagedWidget( "editCascade",
			xmCascadeButtonWidgetClass, menuBar,
			XmNsubMenuId, editPane,
			RES_CONVERT( XmNmnemonic, "E" ),
			RES_CONVERT( XmNlabelString, "Edit" ),
			NULL );

	UxPutContext( editCascade, (char *) UxLg1MainWindowContext );

	OptionPane_shell = XtVaCreatePopupShell ("OptionPane_shell",
			xmMenuShellWidgetClass, menuBar,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	OptionPane = XtVaCreateWidget( "OptionPane",
			xmRowColumnWidgetClass, OptionPane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( OptionPane, (char *) UxLg1MainWindowContext );

	DefaultFilterPane_shell = XtVaCreatePopupShell ("DefaultFilterPane_shell",
			xmMenuShellWidgetClass, OptionPane,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	DefaultFilterPane = XtVaCreateWidget( "DefaultFilterPane",
			xmRowColumnWidgetClass, DefaultFilterPane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( DefaultFilterPane, (char *) UxLg1MainWindowContext );

	NoFilterDef = XtVaCreateManagedWidget( "NoFilterDef",
			xmPushButtonGadgetClass, DefaultFilterPane,
			RES_CONVERT( XmNlabelString, "No Filter" ),
			NULL );

	UxPutContext( NoFilterDef, (char *) UxLg1MainWindowContext );

	SetDefFilter = XtVaCreateManagedWidget( "SetDefFilter",
			xmCascadeButtonGadgetClass, OptionPane,
			XmNsubMenuId, DefaultFilterPane,
			RES_CONVERT( XmNlabelString, "Set Default Filter" ),
			NULL );

	UxPutContext( SetDefFilter, (char *) UxLg1MainWindowContext );

	separator6 = XtVaCreateManagedWidget( "separator6",
			xmSeparatorGadgetClass, OptionPane,
			NULL );

	UxPutContext( separator6, (char *) UxLg1MainWindowContext );

	DefineFilter = XtVaCreateManagedWidget( "DefineFilter",
			xmPushButtonGadgetClass, OptionPane,
			RES_CONVERT( XmNlabelString, "Define Filter" ),
			NULL );

	UxPutContext( DefineFilter, (char *) UxLg1MainWindowContext );

	menuBar_top_b2 = XtVaCreateManagedWidget( "menuBar_top_b2",
			xmCascadeButtonWidgetClass, menuBar,
			XmNsubMenuId, OptionPane,
			RES_CONVERT( XmNmnemonic, "O" ),
			RES_CONVERT( XmNlabelString, "Options" ),
			NULL );

	UxPutContext( menuBar_top_b2, (char *) UxLg1MainWindowContext );

	mainPW = XtVaCreateManagedWidget( "mainPW",
			xmPanedWindowWidgetClass, lg1MainWindow,
			XmNspacing, 20,
			XmNsashIndent, -10,
			NULL );

	UxPutContext( mainPW, (char *) UxLg1MainWindowContext );

	mainForm = XtVaCreateManagedWidget( "mainForm",
			xmFormWidgetClass, mainPW,
			XmNpaneMinimum, 250,
			XmNallowResize, FALSE,
			XmNpaneMaximum, 1000,
			XmNheight, 450,
			XmNwidth, 530,
			XmNy, 10,
			XmNx, 15,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( mainForm, (char *) UxLg1MainWindowContext );

	modNameLb = XtVaCreateManagedWidget( "modNameLb",
			xmLabelWidgetClass, mainForm,
			XmNtraversalOn, FALSE,
			XmNshadowThickness, 0,
			RES_CONVERT( XmNhighlightColor, "#cccc22224444" ),
			XmNhighlightOnEnter, FALSE,
			XmNhighlightThickness, 0,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--18-180-75-75-p-103-iso8859-1" ),
			RES_CONVERT( XmNlabelString, "No model selected" ),
			XmNrightOffset, 5,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_FORM,
			XmNheight, 35,
			XmNwidth, 330,
			XmNy, 55,
			XmNx, 105,
			NULL );

	UxPutContext( modNameLb, (char *) UxLg1MainWindowContext );

	blListLb = XtVaCreateManagedWidget( "blListLb",
			xmLabelWidgetClass, mainForm,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			XmNrightOffset, 5,
			XmNrightAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Blocks in model" ),
			XmNalignment, XmALIGNMENT_CENTER,
			XmNtopWidget, modNameLb,
			XmNtopOffset, 25,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_FORM,
			XmNheight, 15,
			XmNwidth, 110,
			XmNy, 155,
			XmNx, 25,
			NULL );

	UxPutContext( blListLb, (char *) UxLg1MainWindowContext );

	blSearchBox = XtVaCreateManagedWidget( "blSearchBox",
			xmRowColumnWidgetClass, mainForm,
			XmNresizable, TRUE,
			XmNpacking, XmPACK_TIGHT,
			XmNnumColumns, 2,
			XmNleftOffset, 30,
			XmNrightOffset, 30,
			XmNrightAttachment, XmATTACH_FORM,
			XmNorientation, XmHORIZONTAL,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNheight, 32,
			XmNwidth, 422,
			XmNy, 390,
			XmNx, 30,
			NULL );

	UxPutContext( blSearchBox, (char *) UxLg1MainWindowContext );

	blSearchLb = XtVaCreateManagedWidget( "blSearchLb",
			xmLabelWidgetClass, blSearchBox,
			XmNfontList, UxConvertFontList( "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1" ),
			RES_CONVERT( XmNlabelString, "Find:" ),
			XmNheight, 20,
			XmNwidth, 260,
			XmNy, 10,
			XmNx, 10,
			NULL );

	UxPutContext( blSearchLb, (char *) UxLg1MainWindowContext );

	blSearchTF = XtVaCreateManagedWidget( "blSearchTF",
			xmTextFieldWidgetClass, blSearchBox,
			XmNcolumns, 15,
			XmNresizeWidth, FALSE,
			XmNheight, 39,
			XmNwidth, 165,
			XmNy, 3,
			XmNx, 45,
			NULL );

	UxPutContext( blSearchTF, (char *) UxLg1MainWindowContext );

	blSearchUpBt = XtVaCreateManagedWidget( "blSearchUpBt",
			xmArrowButtonWidgetClass, blSearchBox,
			XmNheight, 32,
			XmNwidth, 30,
			XmNy, 3,
			XmNx, 187,
			NULL );

	UxPutContext( blSearchUpBt, (char *) UxLg1MainWindowContext );

	blSearchDownBt = XtVaCreateManagedWidget( "blSearchDownBt",
			xmArrowButtonWidgetClass, blSearchBox,
			XmNarrowDirection, XmARROW_DOWN,
			XmNheight, 30,
			XmNwidth, 30,
			XmNy, 3,
			XmNx, 318,
			NULL );

	UxPutContext( blSearchDownBt, (char *) UxLg1MainWindowContext );

	blListSW = XtVaCreateManagedWidget( "blListSW",
			xmScrolledWindowWidgetClass, mainForm,
			XmNheight, 310,
			XmNtopWidget, blListLb,
			XmNtopOffset, 5,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 30,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 30,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomWidget, blSearchBox,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 100,
			XmNx, 30,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( blListSW, (char *) UxLg1MainWindowContext );

	blListSL = XtVaCreateManagedWidget( "blListSL",
			xmListWidgetClass, blListSW,
			XmNvisibleItemCount, 50,
			XmNselectedItemCount, 0,
			XmNitemCount, 0,
			XmNlistMarginWidth, 5,
			XmNlistMarginHeight, 5,
			XmNshadowThickness, 2,
			XmNhighlightThickness, 0,
			XmNlistSizePolicy, XmCONSTANT,
			XmNscrollBarDisplayPolicy, XmAS_NEEDED,
			XmNlistSpacing, 0,
			XmNselectionPolicy, XmEXTENDED_SELECT,
			XmNheight, 279,
			XmNwidth, 494,
			NULL );

	UxPutContext( blListSL, (char *) UxLg1MainWindowContext );

	blPopup_shell = XtVaCreatePopupShell ("blPopup_shell",
			xmMenuShellWidgetClass, blListSL,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	blPopup = XtVaCreateWidget( "blPopup",
			xmRowColumnWidgetClass, blPopup_shell,
			XmNmenuAccelerator, "<KeyUp>F4",
			XmNrowColumnType, XmMENU_POPUP,
			NULL );

	UxPutContext( blPopup, (char *) UxLg1MainWindowContext );

	blPopupLb = XtVaCreateManagedWidget( "blPopupLb",
			xmLabelWidgetClass, blPopup,
			RES_CONVERT( XmNlabelString, "BLOCKS" ),
			NULL );

	UxPutContext( blPopupLb, (char *) UxLg1MainWindowContext );

	Separator50 = XtVaCreateManagedWidget( "Separator50",
			xmSeparatorWidgetClass, blPopup,
			NULL );

	UxPutContext( Separator50, (char *) UxLg1MainWindowContext );

	blPopupEditBt = XtVaCreateManagedWidget( "blPopupEditBt",
			xmPushButtonWidgetClass, blPopup,
			RES_CONVERT( XmNmnemonic, "E" ),
			RES_CONVERT( XmNlabelString, "Edit Descr" ),
			NULL );

	UxPutContext( blPopupEditBt, (char *) UxLg1MainWindowContext );

	blPopupDelBt = XtVaCreateManagedWidget( "blPopupDelBt",
			xmPushButtonWidgetClass, blPopup,
			RES_CONVERT( XmNmnemonic, "D" ),
			RES_CONVERT( XmNlabelString, "Delete" ),
			NULL );

	UxPutContext( blPopupDelBt, (char *) UxLg1MainWindowContext );

	blPopupVarBt = XtVaCreateManagedWidget( "blPopupVarBt",
			xmPushButtonWidgetClass, blPopup,
			RES_CONVERT( XmNmnemonic, "V" ),
			RES_CONVERT( XmNlabelString, "Variables ..." ),
			NULL );

	UxPutContext( blPopupVarBt, (char *) UxLg1MainWindowContext );

	messageBox = XtVaCreateManagedWidget( "messageBox",
			xmFormWidgetClass, mainPW,
			XmNpaneMinimum, 85,
			XmNheight, 125,
			XmNwidth, 520,
			XmNy, 470,
			XmNx, 20,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( messageBox, (char *) UxLg1MainWindowContext );

	messageLb = XtVaCreateManagedWidget( "messageLb",
			xmLabelWidgetClass, messageBox,
			RES_CONVERT( XmNlabelString, "Messages" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNheight, 15,
			XmNwidth, 135,
			XmNy, 15,
			XmNx, 25,
			NULL );

	UxPutContext( messageLb, (char *) UxLg1MainWindowContext );

	messageSW = XtVaCreateManagedWidget( "messageSW",
			xmScrolledWindowWidgetClass, messageBox,
			XmNtopWidget, messageLb,
			XmNtopOffset, 2,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNwidth, 250,
			XmNheight, 150,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 20,
			XmNx, 0,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( messageSW, (char *) UxLg1MainWindowContext );

	messageST = XtVaCreateManagedWidget( "messageST",
			xmTextWidgetClass, messageSW,
			XmNeditMode, XmMULTI_LINE_EDIT ,
			XmNscrollHorizontal, TRUE,
			XmNcolumns, 80,
			XmNeditable, FALSE,
			XmNcursorPositionVisible, FALSE,
			XmNresizeWidth, TRUE,
			XmNresizeHeight, TRUE,
			XmNscrollVertical, TRUE,
			XmNheight, 160,
			XmNwidth, 250,
			NULL );

	UxPutContext( messageST, (char *) UxLg1MainWindowContext );

	messagePopup_shell = XtVaCreatePopupShell ("messagePopup_shell",
			xmMenuShellWidgetClass, messageST,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	messagePopup = XtVaCreateWidget( "messagePopup",
			xmRowColumnWidgetClass, messagePopup_shell,
			XmNmenuAccelerator, "<KeyUp>F4",
			XmNrowColumnType, XmMENU_POPUP,
			NULL );

	UxPutContext( messagePopup, (char *) UxLg1MainWindowContext );

	titleMessPopup = XtVaCreateManagedWidget( "titleMessPopup",
			xmLabelWidgetClass, messagePopup,
			RES_CONVERT( XmNlabelString, "MESSAGE" ),
			NULL );

	UxPutContext( titleMessPopup, (char *) UxLg1MainWindowContext );

	separator10 = XtVaCreateManagedWidget( "separator10",
			xmSeparatorWidgetClass, messagePopup,
			NULL );

	UxPutContext( separator10, (char *) UxLg1MainWindowContext );

	clearBt = XtVaCreateManagedWidget( "clearBt",
			xmPushButtonWidgetClass, messagePopup,
			RES_CONVERT( XmNlabelString, "Clear Window" ),
			NULL );

	UxPutContext( clearBt, (char *) UxLg1MainWindowContext );

	XtAddCallback( lg1MainWindow, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( openBt, XmNactivateCallback,
			activateCB_openBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( saveBt, XmNactivateCallback,
			activateCB_saveBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( exitBt, XmNactivateCallback,
			activateCB_exitBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( newProcessBl, XmNactivateCallback,
			activateCB_newProcessBl,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( newRegBl, XmNactivateCallback,
			activateCB_newRegBl,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( deleteBt, XmNactivateCallback,
			activateCB_deleteBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( varBt, XmNactivateCallback,
			activateCB_varBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( NoFilterDef, XmNactivateCallback,
			activateCB_NoFilterDef,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( DefineFilter, XmNactivateCallback,
			activateCB_DefineFilter,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( blSearchUpBt, XmNactivateCallback,
			activateCB_blSearchUpBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( blSearchDownBt, XmNactivateCallback,
			activateCB_blSearchDownBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( blListSL, XmNsingleSelectionCallback,
			singleSelectionCB_blListSL,
			(XtPointer) UxLg1MainWindowContext );
	XtAddCallback( blListSL, XmNextendedSelectionCallback,
			extendedSelectionCB_blListSL,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( blPopupEditBt, XmNactivateCallback,
			activateCB_blPopupEditBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( blPopupDelBt, XmNactivateCallback,
			activateCB_blPopupDelBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( blPopupVarBt, XmNactivateCallback,
			activateCB_blPopupVarBt,
			(XtPointer) UxLg1MainWindowContext );

	XtAddCallback( clearBt, XmNactivateCallback,
			activateCB_clearBt,
			(XtPointer) UxLg1MainWindowContext );


	XtAddEventHandler( blListSL, ButtonPressMask,
			False, _Uxlg1MainWindowMenuPost, blPopup );
	XtAddEventHandler( messageST, ButtonPressMask,
			False, _Uxlg1MainWindowMenuPost, messagePopup );
	XmMainWindowSetAreas( lg1MainWindow, menuBar, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, mainPW );

	return ( lg1MainWindow );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_lg1MainWindow()
{
	Widget                  rtrn;
	_UxClg1MainWindow       *UxContext;

	UxLg1MainWindowContext = UxContext =
		(_UxClg1MainWindow *) XtMalloc( sizeof(_UxClg1MainWindow) );

	{
		Arg  arg;
		rtrn = _Uxbuild_lg1MainWindow();

		/* 
		 * Settaggio del titolo della main window.
		 */
		XtSetArg( arg, XmNtitle, "Topology Editor" );
		XtSetValues( XtParent(UxGetWidget(lg1MainWindow)), &arg, 1 );
		
		
		/*
		 * Settaggio dei menu della main window ( pulldown e popup ).
		 * Viene settato l'attributo sensitive dei vari bottoni e lo stato
		 * dei toggle button.
		 */
		int main_menu_setup();
		
		/* se e' attiva la grafica verifico la congruenza tra macroblocks.dat e f01.dat */
		if(graphics_on)
		   lancia_macro(topwidget,UxGetWidget(blListSL));
		
		button_already_defined = False;
		
		def_filtri();
		
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_lg1MainWindow()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_lg1MainWindow();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

