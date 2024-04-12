! UIMX ascii 2.0 key: 5986                                                      

*BlockSelectionBox.class: selectionBox
*BlockSelectionBox.parent: NO_PARENT
*BlockSelectionBox.defaultShell: topLevelShell
*BlockSelectionBox.static: true
*BlockSelectionBox.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo BlockSelectionBox.i\
   tipo \
   release 2.24\
   data 3/30/95\
   reserved @(#)BlockSelectionBox.i	2.24\
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
#include "errore.h"\
#include "lg1.h"\
\
extern ERR_LEVEL err_level;\
extern int num_modulo;\
extern void add_block();
*BlockSelectionBox.ispecdecl:
*BlockSelectionBox.funcdecl: swidget create_BlockSelectionBox()\

*BlockSelectionBox.funcname: create_BlockSelectionBox
*BlockSelectionBox.funcdef: "swidget", "<create_BlockSelectionBox>(%)"
*BlockSelectionBox.icode:
*BlockSelectionBox.fcode: return(rtrn);\

*BlockSelectionBox.auxdecl: /*\
    block_selection_setitem: definisce gli item selezionabili\
*/\
   \
\
block_selection_setitem(int tipo_mod)\
{\
   extern MODULO moduli[];\
   MODULO *lista_mod = moduli;        /*per ingannare l'interprete UIMX */\
   Arg       arg[2];\
   XmString *modu;\
   int i,trovati;\
  \
   int nitem;   \
   char riga[100];\
\
\
   printf("tipo lista selezionata = %d\n",tipo_mod);\
\
   if(tipo_mod == REGOLAZIONE)\
   {\
      UxPutListLabelString(BlockSelectionBox,"Regulation Block List");     \
      XmTextFieldSetEditable(textBlockName1,False);\
      XmTextFieldSetEditable(textBlockDescr,False);\
/*\
      UxPutEditable(textBlockName1,False);\
      UxPutEditable(textBlockDescr,False);\
*/\
   } \
   else if(tipo_mod == PROCESSO)\
   {\
      UxPutListLabelString(BlockSelectionBox,"Module List");\
      XmTextFieldSetEditable(textBlockName1,True);\
      XmTextFieldSetEditable(textBlockDescr,True);\
/*\
      UxPutEditable(UxGetWidget(textBlockName1),True);\
      UxPutEditable(UxGetWidget(textBlockDescr),True);\
*/\
   }\
\
\
   nitem = num_tot_moduli;\
\
   if ( nitem )\
   {\
     modu=(XmString *)malloc(nitem * sizeof(XmString));\
     printf("alloco sufficiente memoria\n");\
\
\
     trovati = 0;\
     for(i=0;i<nitem;i++)\
     {\
       if(lista_mod[i].tipo == tipo_mod)\
       {\
\
          strcpy(riga,lista_mod[i].sigla);\
          strcat(riga,"  ");\
          strcat(riga,lista_mod[i].descr);\
          modu[trovati]=XmStringCreateSimple(riga);\
          trovati++;\
       }\
     }\
          \
   printf("moduli trovati %d\n",trovati);\
\
   }\
\
   if(trovati)\
   {   \
      XtSetArg(arg[0], XmNlistItems, modu);\
      XtSetArg(arg[1], XmNlistItemCount, trovati);\
      XtSetValues(UxGetWidget(BlockSelectionBox), arg, 2);\
\
      printf("i have set %d argument values \n",trovati);\
\
      for(i=0;i<trovati;i++)\
        XtFree(modu[i]);\
\
   }\
   else\
   {\
     XtSetArg(arg[0], XmNlistItems, NULL);\
     XtSetArg(arg[1], XmNlistItemCount, 0);\
     XtSetValues(UxGetWidget(BlockSelectionBox), arg, 2);\
   }\
\
   printf("end subroutine block_selection_setitem\n");\
}\
\
\
\
int block_selection_activate(int tipo)\
{\
   \
   extern swidget   lg1MainWindow;\
\
   printf("call list for tipo = %d\n",tipo);\
    \
   block_selection_setitem(tipo);\
   UxPopupInterface(BlockSelectionBox, no_grab);\
   \
   UxPutText(textBlockName1,"");\
   UxPutText(textBlockDescr,"");\
   UxPutTextString(BlockSelectionBox,"");   \
}\
\
\

*BlockSelectionBox.name: BlockSelectionBox
*BlockSelectionBox.unitType: "pixels"
*BlockSelectionBox.x: 618
*BlockSelectionBox.y: 388
*BlockSelectionBox.height: 530
*BlockSelectionBox.dialogTitle: "Module Selection"
*BlockSelectionBox.cancelCallback: {\
UxPopdownInterface(UxWidget);   \
UxPutText(textBlockName1,"");\
UxPutText(textBlockDescr,"");\
UxPutTextString(UxWidget,"");\
\
}
*BlockSelectionBox.okCallback: {\
#ifdef VERSIONE_VECCHIA_ERRATA\
extern int num_tot_moduli;\
extern char blockname[],blockdescr[],modulename[];\
extern int changes_in_F01;\
/*\
extern void add_block();\
*/\
char *module_selected,verifica[9];\
int i,j,nitem;\
\
\
\
nitem = num_tot_moduli;\
\
strcpy(blockname,UxGetText(textBlockName1));\
strcpy(blockdescr,UxGetText(textBlockDescr));\
\
for(j=0;j< ( strlen(blockname) ) ;j++)\
{\
   blockname[j] = toupper(blockname[j]);\
}\
UxPutText(textBlockName1,blockname);\
\
module_selected = UxGetTextString(UxWidget);\
\
if(!(*module_selected))\
{\
   err_level = ERROR;\
   errore("No Module Selected");\
/*\
   UxPopdownInterface(UxWidget);\
*/\
   return;\
}\
\
for(j=0;j< 4 ;j++)\
{\
   module_selected[j] = toupper(module_selected[j]);\
}\
module_selected[4] = 0;\
strcpy(modulename,module_selected);\
\
UxPutTextString(UxWidget,module_selected);\
\
printf("module selected %s\n",module_selected);\
for(i=0;i<nitem;i++)\
   if( !strcmp(moduli[i].sigla,module_selected) )\
      break;\
   \
   \
if(moduli[i].tipo == PROCESSO) /* nelle reg. la descr. e il nome blocco non servono */\
   if(!(*blockname))  \
   {\
      err_level = ERROR;\
      errore("You must assign a block name");\
      UxPopdownInterface(UxWidget);\
      return;\
   }\
\
i++;\
printf("Module selected %s N.%d \n",module_selected,i);\
\
\
if( (strlen(blockname)) < 4 )\
   strncat(blockname,"   ",(4-strlen(blockname)));\
\
\
\
strcpy(verifica,module_selected);\
strcat(verifica,blockname);\
\
for(j=0;j<num_blocchi;j++)\
{\
   if(moduli[i].tipo == PROCESSO)\
   { \
      if(!strcmp(verifica,blocchi[j].label))\
      {\
         if(j == (num_blocchi -1))  /* ultimo blocco applicato */\
         {\
            UxPopdownInterface(UxWidget); /* esco senza errori */\
            return;\
         }\
         err_level=ERROR;\
         errore("Blocco gia' istanziato",verifica);\
         return;\
      }\
   }\
   else if(moduli[i].tipo == REGOLAZIONE )\
   {\
      if(!strcmp(module_selected,blocchi[j].sigla_modulo))\
      {\
         if(!j )  /* ultimo blocco applicato */\
         {\
            UxPopdownInterface(UxWidget); /* esco senza errori */\
            return;\
         }\
         err_level=ERROR;\
         errore("Blocco gia' istanziato");\
         return;\
      }\
   }  \
}\
\
if(num_blocchi == MAX_BLOCCHI  )\
{\
   err_level=ERROR;\
   errore("Raggiunto il numero massimo dei blocchi");\
   return;\
}\
\
num_modulo = i;\
\
changes_in_F01 = True;\
\
if(moduli[i].tipo == PROCESSO)\
   do_dialogo();\
else\
   add_block(REGOLAZIONE);\
\
UxPopdownInterface(UxWidget);\
\
#else                /******************* INIZIO VERSIONE BUONA ***********/\
\
extern int num_tot_moduli;\
extern char blockname[],blockdescr[],modulename[];\
extern int changes_in_F01;\
\
char *module_selected,verifica[9];\
int i,j,nitem;\
MODULO *mod = moduli;     /* serve a ingannare uimx */\
BLOCCO *bloc = blocchi;\
\
\
\
nitem = num_tot_moduli;\
\
strcpy(blockname,UxGetText(textBlockName1));\
strcpy(blockdescr,UxGetText(textBlockDescr));\
\
for(j=0;j< ( strlen(blockname) ) ;j++)\
{\
   blockname[j] = toupper(blockname[j]);\
}\
UxPutText(textBlockName1,blockname);\
\
module_selected = UxGetTextString(UxWidget);\
\
if(!(*module_selected))\
{\
   err_level = ERROR;\
   errore("No Module Selected");\
   UxPopdownInterface(UxWidget);\
   return;\
}\
\
for(j=0;j< 4  ;j++)\
{\
   module_selected[j] = toupper(module_selected[j]);\
}\
module_selected[4]=0;\
strcpy(modulename,module_selected);\
\
UxPutTextString(UxWidget,module_selected);\
\
printf("module selected %s\n",module_selected);\
for(i=0;i<nitem;i++)\
   if( !strcmp(mod[i].sigla,module_selected) )\
      break;\
   \
if(mod[i].tipo == PROCESSO) /* nelle reg. la descr. e il nome blocco non servono */\
   if(!(*blockname))  \
   {\
      err_level = ERROR;\
      errore("You must assign a block name");\
\
      return;\
   }\
\
\
printf("Module selected %s N.%d \n",module_selected,i);\
\
\
if( (strlen(blockname)) < 4 )\
   strncat(blockname,"   ",(4-strlen(blockname)));\
\
\
/***** verifico la duplicazione dei blocchi in base \
       ai quattro caratteri del nome del blocco  che \
       ho introdotto nel colloquio \
******/\
strcpy(verifica,blockname);\
\
for(j=0;j<num_blocchi;j++)\
{\
   if(mod[i].tipo == PROCESSO)\
   {\
      if(!strcmp(verifica,bloc[j].sigla_blocco))\
      {\
         err_level=ERROR;\
         errore("Blocco gia' istanziato",verifica);\
         return;\
      }\
   }\
   else if(mod[i].tipo == REGOLAZIONE )\
   {\
      if(!strcmp(module_selected,bloc[j].sigla_modulo))\
      {\
         err_level=ERROR;\
         errore("Blocco gia' istanziato");\
         return;\
      }\
   }  \
}\
\
if(num_blocchi == MAX_BLOCCHI  )\
{\
   err_level=ERROR;\
   errore("Raggiunto il numero massimo dei blocchi");\
   return;\
}\
\
\
num_modulo = i+1;\
\
changes_in_F01 = True;\
\
if(mod[i].tipo == PROCESSO)\
   do_dialogo();\
else\
  add_block(REGOLAZIONE);\
\
   UxPopdownInterface(UxWidget);\
\
/************************ FINE VERSIONE BUONA *******************/\
#endif\
}
*BlockSelectionBox.listLabelString: "Module List"
*BlockSelectionBox.selectionLabelString: "Selected Module"
*BlockSelectionBox.dialogType: "dialog_selection"
*BlockSelectionBox.applyCallback: {\
extern int num_tot_moduli;\
extern char blockname[],blockdescr[],modulename[];\
extern int changes_in_F01;\
\
char *module_selected,verifica[9];\
int i,j,nitem;\
MODULO *mod = moduli;     /* serve a ingannare uimx */\
BLOCCO *bloc = blocchi;\
\
\
\
nitem = num_tot_moduli;\
\
strcpy(blockname,UxGetText(textBlockName1));\
strcpy(blockdescr,UxGetText(textBlockDescr));\
\
for(j=0;j< ( strlen(blockname) ) ;j++)\
{\
   blockname[j] = toupper(blockname[j]);\
}\
UxPutText(textBlockName1,blockname);\
\
module_selected = UxGetTextString(UxWidget);\
\
if(!(*module_selected))\
{\
   err_level = ERROR;\
   errore("No Module Selected");\
   UxPopdownInterface(UxWidget);\
   return;\
}\
\
for(j=0;j< 4  ;j++)\
{\
   module_selected[j] = toupper(module_selected[j]);\
}\
module_selected[4]=0;\
strcpy(modulename,module_selected);\
\
UxPutTextString(UxWidget,module_selected);\
\
printf("module selected %s\n",module_selected);\
for(i=0;i<nitem;i++)\
   if( !strcmp(mod[i].sigla,module_selected) )\
      break;\
   \
if(mod[i].tipo == PROCESSO) /* nelle reg. la descr. e il nome blocco non servono */\
   if(!(*blockname))  \
   {\
      err_level = ERROR;\
      errore("You must assign a block name");\
\
      return;\
   }\
\
\
printf("Module selected %s N.%d \n",module_selected,i);\
\
\
if( (strlen(blockname)) < 4 )\
   strncat(blockname,"   ",(4-strlen(blockname)));\
\
\
/***** verifico la duplicazione dei blocchi in base \
       ai quattro caratteri del nome del blocco  che \
       ho introdotto nel colloquio \
******/\
strcpy(verifica,blockname);\
\
for(j=0;j<num_blocchi;j++)\
{\
   if(mod[i].tipo == PROCESSO)\
   {\
      if(!strcmp(verifica,bloc[j].sigla_blocco))\
      {\
         err_level=ERROR;\
         errore("Blocco gia' istanziato",verifica);\
         return;\
      }\
   }\
   else if(mod[i].tipo == REGOLAZIONE )\
   {\
      if(!strcmp(module_selected,bloc[j].sigla_modulo))\
      {\
         err_level=ERROR;\
         errore("Blocco gia' istanziato");\
         return;\
      }\
   }  \
}\
\
if(num_blocchi == MAX_BLOCCHI  )\
{\
   err_level=ERROR;\
   errore("Raggiunto il numero massimo dei blocchi");\
   return;\
}\
\
\
num_modulo = i+1;\
\
changes_in_F01 = True;\
\
if(mod[i].tipo == PROCESSO)\
   do_dialogo();\
else\
  add_block(REGOLAZIONE);\
\
   \
\
\
\
\
}
*BlockSelectionBox.width: 700
*BlockSelectionBox.textString: ""
*BlockSelectionBox.navigationType: "tab_group"
*BlockSelectionBox.textColumns: 90

*BlockName1.class: rowColumn
*BlockName1.parent: BlockSelectionBox
*BlockName1.static: true
*BlockName1.name: BlockName1
*BlockName1.x: 10
*BlockName1.y: 390
*BlockName1.width: 479
*BlockName1.height: 124

*labelBlockName1.class: labelGadget
*labelBlockName1.parent: BlockName1
*labelBlockName1.static: true
*labelBlockName1.name: labelBlockName1
*labelBlockName1.x: 0
*labelBlockName1.y: 70
*labelBlockName1.width: 100
*labelBlockName1.height: 100
*labelBlockName1.labelString: "Block Name"

*textBlockName1.class: textField
*textBlockName1.parent: BlockName1
*textBlockName1.static: true
*textBlockName1.name: textBlockName1
*textBlockName1.x: 0
*textBlockName1.y: 30
*textBlockName1.width: 97
*textBlockName1.height: 35
*textBlockName1.columns: 20
*textBlockName1.maxLength: 4
*textBlockName1.cursorPosition: 1

*labelBlockDescr1.class: labelGadget
*labelBlockDescr1.parent: BlockName1
*labelBlockDescr1.static: true
*labelBlockDescr1.name: labelBlockDescr1
*labelBlockDescr1.x: 0
*labelBlockDescr1.y: 60
*labelBlockDescr1.width: 250
*labelBlockDescr1.height: 20
*labelBlockDescr1.labelString: "Block Descr"

*textBlockDescr.class: textField
*textBlockDescr.parent: BlockName1
*textBlockDescr.static: true
*textBlockDescr.name: textBlockDescr
*textBlockDescr.x: 190
*textBlockDescr.y: 40
*textBlockDescr.width: 280
*textBlockDescr.height: 20
*textBlockDescr.maxLength: 73
*textBlockDescr.cursorPosition: 1

