! UIMX ascii 2.0 key: 255                                                       

*opendialogShell2.class: dialogShell
*opendialogShell2.parent: NO_PARENT
*opendialogShell2.static: false
*opendialogShell2.gbldecl: /*\
   modulo dialogShell2.i\
   tipo \
   release 2.6\
   data 3/20/95\
   reserved @(#)dialogShell2.i	2.6\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#ifndef FILTRI_h\
#include "filtri.h"\
#endif\
\
extern char filedf[];                 /* filename file di editing */\
extern FILE *fpedf;                   /* file di edting */\
extern FILTRI *filtri[];              /* vettore filtri */\
extern short num_filtri;              /* numero di filtri definiti */\
\
extern void add_items_list();         /* definita in filtri Shell1 */\
extern void delete_all_items();       /* definita in filtri Shell1 */\
extern swidget scrolledList1;\
extern swidget scrolledList2;\

*opendialogShell2.ispecdecl:
*opendialogShell2.funcdecl: swidget create_opendialogShell2()\

*opendialogShell2.funcname: create_opendialogShell2
*opendialogShell2.funcdef: "swidget", "<create_opendialogShell2>(%)"
*opendialogShell2.icode:
*opendialogShell2.fcode: return(rtrn);\

*opendialogShell2.auxdecl: FILTRI *Afiltro_init()\
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
|    swap_filtri: swap dei filtri\
|\
================================================================*/\
\
void Aswap_filtri(int ind)\
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
void Afiltro_free(int ind)\
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
int Aopenedf()\
{\
   strcpy(filedf,UxGetTextString(fileSelectionBox1));\
 \
    if(fpedf != NULL)\
      closedf();\
\
   if( ( fpedf=fopen(filedf,"r+") ) == NULL)\
   {\
      printf("\n Apro file nuovo\n");\
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
int Aclosedf()\
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
int Areadedf()\
{\
   char *buff[MAXCHNAME];\
   short i=0,j=0;\
\
   printf("\ninizia la lettura filtri \n");\
\
   /* reset dati filtri */\
\
   for(i=0;i<num_filtri;i++)\
   {\
      for(j=0;j<filtri[i]->num_var;j++)\
         memset(filtri[i]->var[j],0,DIM_PAR);\
      strcpy(filtri[i]->nome_filtro,"");\
      filtri[i]->num_var=0;\
   }\
\
   num_filtri = 0; /* inizializzo */\
\
   while(1)\
   {\
      fscanf(fpedf,"%s",buff);\
      if(feof(fpedf))\
         break;\
\
      if(!strcmp(buff,TAPPO))   /* inizio record */\
      {\
         filtri[num_filtri] =  Afiltro_init();\
         fscanf(fpedf,"%s",buff);\
         strcpy(filtri[num_filtri]->nome_filtro,buff);\
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
|  writedf:   scrittura file di editing.  Il file pointer e' globale\
|             \
|             cosi come le condizioni di errore\
|\
===================================================================*/\
\
int Awritedf()\
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
       \
\
\

*opendialogShell2.name: opendialogShell2
*opendialogShell2.x: 389
*opendialogShell2.y: 329
*opendialogShell2.width: 380
*opendialogShell2.height: 170

*fileSelectionBox1.class: fileSelectionBox
*fileSelectionBox1.parent: opendialogShell2
*fileSelectionBox1.static: true
*fileSelectionBox1.name: fileSelectionBox1
*fileSelectionBox1.resizePolicy: "resize_none"
*fileSelectionBox1.unitType: "pixels"
*fileSelectionBox1.x: 480
*fileSelectionBox1.y: 190
*fileSelectionBox1.width: 450
*fileSelectionBox1.height: 250
*fileSelectionBox1.dialogStyle: "dialog_primary_application_modal"
*fileSelectionBox1.dialogTitle: "Editing File Selection"
*fileSelectionBox1.dirMask.lock: true
*fileSelectionBox1.dirMask: "/usr/users/legoroot/svil/legocad/filtri/*.edf"
*fileSelectionBox1.noMatchString: "None"
*fileSelectionBox1.pattern.lock: true
*fileSelectionBox1.pattern: "*.edf"
*fileSelectionBox1.okCallback: {\
extern int operaz;\
short i=0,j=0,IER=0;\
char *nomi[MAXFILTRI];\
\
\
strcpy(filedf,UxGetTextString(UxWidget));\
\
\
IER = openedf();                           /* apertura file di editing */\
if( IER != OK)\
   printf("Errore apertura file di editing\n");\
else\
{\
   if(operaz == FILE_OPEN)\
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
   else if(operaz == FILE_SAVE)\
      writedf();\
\
}\
\
UxPopdownInterface(UxWidget);\
}
*fileSelectionBox1.cancelCallback: {\
UxPopdownInterface(UxWidget);\
}
*fileSelectionBox1.listVisibleItemCount: 4

