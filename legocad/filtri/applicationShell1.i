! UIMX ascii 2.0 key: 9209                                                      

*filtriShell1.class: applicationShell
*filtriShell1.parent: NO_PARENT
*filtriShell1.static: true
*filtriShell1.gbldecl: /*\
   modulo applicationShell1.i\
   tipo \
   release 2.6\
   data 3/20/95\
   reserved @(#)applicationShell1.i	2.6\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h> \
#include <Xm/List.h>     \
#ifndef FILTRI_H\
#include "filtri.h"\
#endif          \
\
extern char filedf[];                 /* filename file di editing */\
extern FILE *fpedf;                   /* file di edting */\
extern FILTRI *filtri[];              /* vettore filtri */\
extern short num_filtri;              /* numero di filtri definiti */\
\
\
extern swidget create_exitdialogShell1();  \
extern swidget exitdialogShell1;	         /* Quit Application swidget */ \
extern swidget create_opendialogShell2();\
extern swidget opendialogShell2;		 /* Editing File Selection */\
extern swidget create_editShell1();\
extern swidget editShell1;                       /* Edit Filter  */ \
\
short num_filtro_selez;                          /* indice filtro selezionato */\
int operaz;                                      /* tipo operazione menu di EDIT */
*filtriShell1.ispecdecl: int selez;
*filtriShell1.ispeclist: selez
*filtriShell1.ispeclist.selez: "int", "%selez%"
*filtriShell1.funcdecl: swidget create_filtriShell1()
*filtriShell1.funcname: create_filtriShell1
*filtriShell1.funcdef: "swidget", "<create_filtriShell1>(%)"
*filtriShell1.icode: /* selez = variabile di stato filtro selezionato */\
\
selez=False;\

*filtriShell1.fcode: /*================================================================\
|\
|  mappa le interfacce apre e legge il file di editing dei filtri\
|  e visualizza i filtri \
|\
================================================================*/\
            \
{\
   short i=0,j=0,IER=0;\
   char *nomi[MAXFILTRI];\
\
   create_exitdialogShell1();\
   create_editShell1();\
\
\
   operaz = FILE_OPEN;\
\
   strcpy(filedf,NOMEFILEDIEDITING);\
\
   IER = openedf();                           /* apertura file di editing */\
   if( IER != OK)\
      printf("Errore apertura file di editing\n");\
   else\
   {\
      readedf();                             /* lettura file di editing */\
\
      for(i=0;i<num_filtri;i++)\
      {   \
         nomi[i] = (char *)(malloc(sizeof(char) * MAXCHNAME));\
         strcpy(nomi[i],filtri[i]->nome_filtro);\
      }\
\
      delete_all_items(scrolledList1);  /* elimino tutti gli items precedenti */\
      delete_all_items(scrolledList2);  \
      add_items_list(scrolledList1,nomi,num_filtri);  /* visualizzo la nuova lista */\
\
      closedf();\
\
      for(i=0;i<num_filtri;i++)\
         free(nomi[i]);\
   }\
\
   return(rtrn);\
}
*filtriShell1.auxdecl: /*==========================================================\
|\
|  add_items_list:  Aggiunge n items alla lista\
|\
===========================================================*/\
\
void add_items_list(swidget lista,char *dati[],int n_item)\
{\
   XmString item;\
   int i;\
\
\
   UxPutVisibleItemCount(lista,n_item);\
   if(UxGetWidget(lista) != NULL)\
   {\
      printf("\neseguo la add_items_list\n");\
      for(i=0;i < n_item;i++)\
      {\
         printf("item = %s\n",dati[i]);\
         item = (XmString)XmStringCreateLtoR( dati[i], XmSTRING_DEFAULT_CHARSET); \
         XmListAddItem(UxGetWidget(lista),item,i+1);\
         XmStringFree(item);        \
      }\
   }\
   else\
      printf("\nadd_items_list lista errata\n");\
\
   printf("/n ho terminato la add item \n");\
}\
\
/*========================================================\
|\
| delete_all_items:  elimina tutti gli items dalla lista\
|\
==========================================================*/\
\
void delete_all_items(swidget lista)\
{\
   if(UxGetWidget(lista) != NULL)\
   {\
      printf("\neseguo la delete_all_item\n");\
      XmListDeleteAllItems(UxGetWidget(lista));\
   }\
   else\
      printf("\ndelete_all_item lista non corretta\n");\
\
}\
\
/*==========================================================\
|\
|  refresh_lista_nomi:  Effettua il refresh della lista de\
|                       nomi dei filtri\
|\
===========================================================*/\
\
void refresh_lista_nomi()\
{\
   XmString item;\
   int i;\
\
   delete_all_items(scrolledList1);\
\
   UxPutVisibleItemCount(scrolledList1,num_filtri);\
\
   printf("\neseguo la refresh_lista_nomi\n");\
   for(i=0;i < num_filtri;i++)\
   {\
      item = (XmString)XmStringCreateLtoR( filtri[i]->nome_filtro, XmSTRING_DEFAULT_CHARSET); \
      XmListAddItem(UxGetWidget(scrolledList1),item,i+1);\
      XmStringFree(item);        \
   }\
}\
\
\
/*==========================================================\
|\
|   filtro_init:  alloca la memoria per la struttura di un \
|                 filtro e ne restituisce  il puntatore\
|                 \
===========================================================*/\
\
FILTRI *filtro_init()\
{\
   short j;\
   FILTRI *ftr;\
\
   printf("\n inizializzazione FILTRO \n");\
\
   ftr = (FILTRI *)(malloc(DIM_FILTRO));\
   memset(ftr,0,DIM_FILTRO);\
   for(j=0;j<MAXPARFILTRO;j++)\
   {\
      ftr->var[j] = (char *)(malloc( DIM_PAR ));\
      memset(ftr->var[j],0,DIM_PAR);\
   }\
   printf("\nterminata la inizializzaione \n");\
   return(ftr);\
}\
\
/*===============================================================\
|\
|    swap_filtri:  compatta il vettore  dei filtri dopo \
|                  una cancellazione\
|\
================================================================*/\
\
void swap_filtri(int ind)\
{\
   int j;\
\
   for(j=ind;j<num_filtri;j++)\
   {\
      filtri[j] = filtri[j+1];    \
   }\
}\
\
\
/*================================================================\
|\
|    filtro_free:  libera la memoria allocata per un filtro \
|                  e ne ripulisce il contenuto\
|\
=================================================================*/\
\
void filtro_free(int ind)\
{\
   int j;\
\
   for(j=0;j<filtri[ind]->num_var;j++)\
   {\
      memset(filtri[ind]->var[j],0,DIM_PAR);\
      free(filtri[ind]->var[j]);\
   }\
   memset(filtri[ind],0,DIM_FILTRO);\
   free(filtri[ind]);         \
   num_filtri--;\
   swap_filtri(ind);\
   \
}\
\
\
\
\
/*===================================================================\
|\
|  openedf:   apertura file di editing.  Il file pointer e' globale\
|             cosi' come le definizioni di errore.            \
|             Attualmente il nome del file e'cablato\
|            \
|\
===================================================================*/\
\
int openedf()\
{\
   char *getenv();\
\
   if(fpedf != NULL)\
      closedf();\
\
   strcpy(filedf,getenv("LEGOCAD_USER"));\
   strcat(filedf,"/filtri.edf");\
\
   printf("\nApro file -> %s \n",filedf);\
   if( ( fpedf=fopen(filedf,"r+") ) == NULL)\
   {\
      if( ( fpedf=fopen(filedf,"w") ) == NULL)\
         return(ERROPEN);\
   }\
   return(OK);\
}\
 \
/*===================================================================\
|\
|  closedf:   chiusura file di editing. Il file pointer e' globale\
|\
====================================================================*/\
\
int closedf()\
{\
   fclose(fpedf);\
   printf("\n terminata la closedf\n");\
}\
\
/*===================================================================\
|\
|  readedf:   lettura file di editing.  Il file pointer e' globale\
|             \
|             cosi come le condizioni di errore\
|\
===================================================================*/\
\
int readedf()\
{\
   char *buff[MAXCHNAME];\
   short i=0,j=0;\
\
   printf("\ninizia la lettura filtri \n");\
\
   num_filtri = 0; /* inizializzo */\
\
   while(1)\
   {\
      if((fscanf(fpedf,"%s",buff)) == EOF)\
         break;\
      if(feof(fpedf))\
         break;\
\
      if(!strcmp(buff,TAPPO))   /* inizio record */\
      {\
         filtri[num_filtri] =  filtro_init();\
         fscanf(fpedf,"%s",buff);\
         strcpy(filtri[num_filtri]->nome_filtro,buff);\
         printf("/nletto filtro -> %s\n",filtri[num_filtri]->nome_filtro);\
         num_filtri++;\
         j=0;\
      }\
      else\
      {\
         strcpy((filtri[num_filtri - 1])->var[j],buff);\
         j++;\
         filtri[num_filtri - 1]->num_var = j;\
      }\
   }\
\
   printf("termina la lettura filtri \n");\
}\
\
\
/*===================================================================\
|\
|  writedf:   scrittura file di editing.  Il file pointer e' globale             \
|             cosi come le condizioni di errore\
|\
===================================================================*/\
\
int writedf()\
{\
   char *buff[MAXCHNAME];\
   short i=0,j=0;\
\
   if(fpedf == NULL)\
   {\
      printf("\nNESSUN FILE DI EDITING APERTO\n");\
      return(-1);\
   }\
\
   fclose(fpedf);\
   fpedf = fopen(filedf,"w");\
   for(i=0;i<num_filtri;i++)\
   {\
      fprintf(fpedf,"%s","FILTRO ");\
      printf("/n scrivo il tappo %s\n",TAPPO);\
      fprintf(fpedf,"%s\n",filtri[i]->nome_filtro);\
      printf("/n scrivo il nome filtro %s\n",filtri[i]->nome_filtro);\
      for(j=0;j<filtri[i]->num_var;j++)\
      {\
         fprintf(fpedf,"%s\n",filtri[i]->var[j]);\
         printf("/n scrivo il filtro %s\n",filtri[i]->var[j]);\
      }\
   }\
   fclose(fpedf);\
   printf("\nsalvataggio terminato\n");\
}\
\
\
       
*filtriShell1.name: filtriShell1
*filtriShell1.x: 630
*filtriShell1.y: 430
*filtriShell1.width: 610
*filtriShell1.height: 490
*filtriShell1.allowShellResize: "false"
*filtriShell1.minHeight: 200
*filtriShell1.minWidth: 300

*mainWindow1.class: mainWindow
*mainWindow1.parent: filtriShell1
*mainWindow1.static: true
*mainWindow1.name: mainWindow1
*mainWindow1.unitType: "pixels"
*mainWindow1.x: 10
*mainWindow1.y: 20
*mainWindow1.width: 590
*mainWindow1.height: 460

*menu2.class: rowColumn
*menu2.parent: mainWindow1
*menu2.static: true
*menu2.name: menu2
*menu2.rowColumnType: "menu_bar"
*menu2.menuAccelerator: "<KeyUp>F10"

*menu1_p1.class: rowColumn
*menu1_p1.parent: menu2
*menu1_p1.static: true
*menu1_p1.name: menu1_p1
*menu1_p1.rowColumnType: "menu_pulldown"

*menu1_p1_b3.class: pushButton
*menu1_p1_b3.parent: menu1_p1
*menu1_p1_b3.static: true
*menu1_p1_b3.name: menu1_p1_b3
*menu1_p1_b3.labelString: "Save"
*menu1_p1_b3.mnemonic: "S"
*menu1_p1_b3.activateCallback: {\
   writedf();\
}

*menu1_p1_b2.class: pushButton
*menu1_p1_b2.parent: menu1_p1
*menu1_p1_b2.static: true
*menu1_p1_b2.name: menu1_p1_b2
*menu1_p1_b2.labelString: "Quit"
*menu1_p1_b2.mnemonic: "Q"
*menu1_p1_b2.activateCallback: {\
   UxPopupInterface(exitdialogShell1,no_grab);\
}

*menu2_p2.class: rowColumn
*menu2_p2.parent: menu2
*menu2_p2.static: true
*menu2_p2.name: menu2_p2
*menu2_p2.rowColumnType: "menu_pulldown"

*menu2_p2_b1.class: pushButton
*menu2_p2_b1.parent: menu2_p2
*menu2_p2_b1.static: true
*menu2_p2_b1.name: menu2_p2_b1
*menu2_p2_b1.labelString: "Open"
*menu2_p2_b1.activateCallback: {\
   if(selez == True)\
   {\
      UxPopupInterface(editShell1,no_grab);\
      operaz = OPEN_FILTRO;\
      aggiorna_edit_shell(filtri[num_filtro_selez]);\
   }\
}\
\
\
\


*menu2_p2_b2.class: pushButton
*menu2_p2_b2.parent: menu2_p2
*menu2_p2_b2.static: true
*menu2_p2_b2.name: menu2_p2_b2
*menu2_p2_b2.labelString: "New"
*menu2_p2_b2.activateCallback: {\
   extern int clear_field();\
 \
   printf("\npopup interface editShell1\n");\
   operaz = NEW_FILTRO;\
   clear_field();\
   UxPopupInterface(editShell1,no_grab);\
}

*menu2_p2_b3.class: pushButton
*menu2_p2_b3.parent: menu2_p2
*menu2_p2_b3.static: true
*menu2_p2_b3.name: menu2_p2_b3
*menu2_p2_b3.labelString: "Delete"
*menu2_p2_b3.activateCallback: {\
   extern void filtro_free();\
   int i,j;\
\
   if(selez == True)\
   {\
      printf("\nparte la delete del filtro n.%d\n",num_filtro_selez);\
  \
      filtro_free(num_filtro_selez);\
\
      delete_all_items(scrolledList1);\
      delete_all_items(scrolledList2);\
      refresh_lista_nomi();\
      printf("\ndelete filtro terminata\n");\
\
      selez=False;\
\
   }\
}

*menu1_top_b1.class: cascadeButton
*menu1_top_b1.parent: menu2
*menu1_top_b1.static: true
*menu1_top_b1.name: menu1_top_b1
*menu1_top_b1.labelString: "File"
*menu1_top_b1.subMenuId: "menu1_p1"

*menu2_top_b1.class: cascadeButton
*menu2_top_b1.parent: menu2
*menu2_top_b1.static: true
*menu2_top_b1.name: menu2_top_b1
*menu2_top_b1.labelString: "Edit"
*menu2_top_b1.subMenuId: "menu2_p2"

*form1.class: form
*form1.parent: mainWindow1
*form1.static: true
*form1.name: form1

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.parent: form1
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.x: 30
*scrolledWindow1.y: 60
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.shadowThickness: 0
*scrolledWindow1.bottomAttachment: "attach_form"
*scrolledWindow1.bottomOffset: 50
*scrolledWindow1.rightAttachment: "attach_position"
*scrolledWindow1.rightOffset: 0
*scrolledWindow1.leftAttachment: "attach_form"
*scrolledWindow1.leftOffset: 30
*scrolledWindow1.topAttachment: "attach_form"
*scrolledWindow1.topOffset: 50
*scrolledWindow1.resizable: "false"
*scrolledWindow1.rightPosition: 70

*scrolledList1.class: scrolledList
*scrolledList1.parent: scrolledWindow1
*scrolledList1.static: false
*scrolledList1.name: scrolledList1
*scrolledList1.width: 280
*scrolledList1.height: 310
*scrolledList1.selectionPolicy: "single_select"
*scrolledList1.singleSelectionCallback: {\
short i;\
XmListCallbackStruct *callb;\
XmString item;\
char *par[MAXPARFILTRO];\
\
selez = True;\
\
num_filtro_selez = -1;\
callb = (XmListCallbackStruct *)UxCallbackArg;\
num_filtro_selez = callb->item_position -1;\
\
for(i=0;i<(filtri[num_filtro_selez])->num_var;i++)\
{\
   par[i] = (char *)malloc(sizeof(char) * MAXCHARPAR);\
   strcpy(par[i],filtri[num_filtro_selez]->var[i]);\
}\
\
printf("n var in risposta %d\n",(filtri[num_filtro_selez])->num_var);\
\
delete_all_items(scrolledList2);\
add_items_list(scrolledList2,par,filtri[num_filtro_selez]->num_var);\
\
\
for(i=0;i<(filtri[num_filtro_selez])->num_var;i++)\
   free(par[i]);\
\
free(par);\
free(callb);\
}
*scrolledList1.visibleItemCount: 1
*scrolledList1.traversalOn: "true"

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.parent: form1
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.scrollingPolicy: "application_defined"
*scrolledWindow2.x: 360
*scrolledWindow2.y: 50
*scrolledWindow2.visualPolicy: "variable"
*scrolledWindow2.scrollBarDisplayPolicy: "static"
*scrolledWindow2.shadowThickness: 0
*scrolledWindow2.height: 320
*scrolledWindow2.width: 100
*scrolledWindow2.bottomAttachment: "attach_form"
*scrolledWindow2.bottomOffset: 50
*scrolledWindow2.leftAttachment: "attach_position"
*scrolledWindow2.leftOffset: 0
*scrolledWindow2.rightAttachment: "attach_position"
*scrolledWindow2.topAttachment: "attach_form"
*scrolledWindow2.topOffset: 50
*scrolledWindow2.leftWidget: "scrolledWindow1"
*scrolledWindow2.leftPosition: 75
*scrolledWindow2.rightPosition: 95

*scrolledList2.class: scrolledList
*scrolledList2.parent: scrolledWindow2
*scrolledList2.static: false
*scrolledList2.name: scrolledList2
*scrolledList2.width: 230
*scrolledList2.height: 320
*scrolledList2.selectionPolicy: "single_select"
*scrolledList2.listSizePolicy: "constant"

*labelGadget2.class: labelGadget
*labelGadget2.parent: form1
*labelGadget2.static: true
*labelGadget2.name: labelGadget2
*labelGadget2.x: 440
*labelGadget2.y: 10
*labelGadget2.width: 120
*labelGadget2.height: 30
*labelGadget2.bottomAttachment: "attach_widget"
*labelGadget2.bottomPosition: 0
*labelGadget2.topAttachment: "attach_position"
*labelGadget2.topPosition: 0
*labelGadget2.leftAttachment: "attach_position"
*labelGadget2.leftPosition: 75
*labelGadget2.rightAttachment: "attach_position"
*labelGadget2.rightPosition: 95
*labelGadget2.labelString: "Filter"
*labelGadget2.bottomOffset: 5
*labelGadget2.bottomWidget: "scrolledWindow2"

*labelGadget1.class: labelGadget
*labelGadget1.parent: form1
*labelGadget1.static: true
*labelGadget1.name: labelGadget1
*labelGadget1.x: 30
*labelGadget1.y: 10
*labelGadget1.width: 280
*labelGadget1.height: 20
*labelGadget1.labelString: "Filter Name"
*labelGadget1.bottomAttachment: "attach_widget"
*labelGadget1.rightAttachment: "attach_position"
*labelGadget1.topAttachment: "attach_position"
*labelGadget1.topOffset: 0
*labelGadget1.leftAttachment: "attach_form"
*labelGadget1.leftOffset: 30
*labelGadget1.rightPosition: 70
*labelGadget1.topPosition: 0
*labelGadget1.bottomOffset: 5
*labelGadget1.bottomWidget: "scrolledWindow1"

