! UIMX ascii 2.0 key: 1970                                                      

*Foraus.class: form
*Foraus.parent: NO_PARENT
*Foraus.defaultShell: topLevelShell
*Foraus.static: true
*Foraus.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo Foraus.i\
   tipo \
   release 1.13\
   data 5/16/95\
   reserved @(#)Foraus.i	1.13\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
#include <stdio.h>\
#include <string.h>\
#include <sys/stat.h>\
#include <sys/access.h>\
#include <linfo.h>\
#include "legomain.h"\
\
/********************************* in legomain.h\
#define SAVE_TMP_FORAUS  90\
#define SAVE_FORAUS      91\
#define MIN_LEN_RIGA    100\
#define PATTERN "C~FORAUS_"\
#define FILE_TMP_NAME "foraus.tmp"\
#define FILE_FORAUS   "foraus.for"\
**************************************************/\
\
extern char path_libut[];\
\
LTM *ltm;\
int nmoduli;\
#ifndef DESIGN_TIME\
char *elenco[300];\
char *codice[300];\
#else\
char *elenco[100];\
char *codice[100];\
#endif\
int nmodaux;\

*Foraus.ispecdecl: Boolean foraus_ok;
*Foraus.ispeclist: foraus_ok
*Foraus.ispeclist.foraus_ok: "Boolean", "%foraus_ok%"
*Foraus.funcdecl: swidget create_Foraus()\

*Foraus.funcname: create_Foraus
*Foraus.funcdef: "swidget", "<create_Foraus>(%)"
*Foraus.icode: foraus_ok = False;
*Foraus.fcode: UxPutSensitive(arrowButton1,"false");\
\
if( LoadModulesList(scrolledList1) != True)\
{\
   create_vis_msg("Can't read model module list: crealtm.dat");\
   return(NULL);\
}\
   \
if( LoadForausStdList() != True)\
   create_vis_msg("Can't read user auxiliary fortran: foraus.for");\
\
\
return(rtrn);\

*Foraus.auxdecl: /*-------------------------------------------\
 * \
 * routine di uso generale \
 *\
 *--------------------------------------------*/\
\
/*---------------------------------\
 * distrugge la interfaccia Foraus\
 * ricevendo in input uno widget\
 * della interfaccia\
 *---------------------------------*/\
\
close_interface(swidget wid)\
{\
/* forse e' necessario recuperare il Context */\
/* distruggo la interfacccia Foraus */\
   UxDestroyInterface(wid);\
}  \
\
/*-----\
 *   ritorna la lista delle posizioni degli item selezionati.\
 *  L'utente ha la rsponsabilita' di liberare la memoria occupata\
 *-----*/\
\
get_selection_list(Widget lista,int **positions,int  *nitem)\
{\
  return( XmListGetSelectedPos(lista,positions,nitem) );\
}\
\
/*-----\
 *\
 *  seleziona tutti gli item della lista\
 *\
 *-----*/\
\
select_all_item(Widget lista)\
{\
   int tot_item,i;\
\
   UxPutSensitive(arrowButton1,"true");\
\
   XtVaGetValues(lista,XmNitemCount,&tot_item,NULL);\
   for(i=0;i<tot_item;i++)\
      XmListSelectPos(lista,i,False);\
}\
\
/*--------\
 *\
 * deseleziona tutti gli item della lista\
 *\
 *--------*/\
\
unselect_all_item(Widget lista)\
{\
   UxPutSensitive(arrowButton1,"false");\
   XmListDeselectAllItems(lista);\
}\
\
/*---------\
 * \
 * set di un item nella lista\
 *\
 *----------*/\
set_item_list(Widget lista,char *cstr,int pos)\
{\
   XmString item;\
\
   item = XmStringCreateSimple(cstr);\
   XmListAddItem(lista,item,pos);\
}\
\
/*-------------\
 *\
 * carica un file in memoria\
 *\
 *-------------*/\
\
int load_file_in_memory(FILE *fp,char **str)\
{\
   struct stat info_file;\
   char *ptr = NULL,*ptr2 = NULL;\
   \
\
   if( *str != NULL)\
      return(False);\
\
/* recupero le dimensioni del file e alloco memoria */\
   if ( !fstat(fileno(fp),&info_file))\
   {\
      ptr = (char *) XtMalloc ((unsigned) info_file.st_size+1);\
   }\
   else\
      ptr = (char *) XtMalloc (sizeof(char) * 100000);\
\
/* leggo tutto il file */\
   ptr2 = ptr;\
   while (fgets(ptr2,140,fp) != NULL)\
      ptr2 = ptr2+strlen(ptr2);\
\
\
   if( strlen(ptr) )\
     *str = ptr;\
\
   return(True);    \
}\
\
/*--------------------------------\
 *\
 * ricerca pattern in una stringa \
 *\
 *---------------------------------*/ \
\
char *cerca_pattern(char *str,char *pattern)\
{\
   return( strstr(str,pattern) );\
}\
\
put_string_on_file(char *fname,char *str)\
{\
   FILE *fp;\
   char appo[10]; \
\
   if( (fp = fopen(fname,"a")) == NULL)\
   {\
      fclose(fp);\
      return(False);\
   }\
\
   fputs(str,fp);\
/*   sprintf(appo,"\n%s\n","C"); */\
\
   sprintf(appo,"\n");\
   fputs(appo,fp);\
\
   fclose(fp);\
}\
\
/*##################################################################*/\
\
/*-----------------------------------------------\
 *                                               \
 *   gestione lista moduli                         \
 *                                              \
 *-----------------------------------------------*/\
\
/*----------\
 *\
 * allocazione vettore strutture lista moduli \
 *\
 *----------*/\
 \
int alloca_ltm(LTM **ltm,int nrecord)\
{\
    if(nrecord > 0 )\
       (*ltm) = (LTM *)calloc(nrecord,sizeof(LTM));\
       if(*ltm == NULL)\
          return(NULL);\
    return(TRUE);\
}\
\
/*----------\
 * \
 * ritorna la riga letta dal file\
 *\
 *----------*/\
 \
read_riga(FILE *fp,char *riga)\
{\
   int retval;\
   char nl;\
\
/*\
   l'utente deve dimensionare\
   la riga almeno 100 char (per sicurezza)\
*/\
\
   retval = fscanf(fp,"%[^\n]",riga); /* legge fino al newline */\
   fscanf(fp,"%c",&nl);               /* legge il new_line     */\
   return(retval);\
}\
\
/*----------\
 *\
 * skip di una riga \
 *\
 -----------*/\
\
void skip_riga(FILE *fp)\
{\
    char riga[200];\
\
    read_riga(fp,riga);               /* effettua la read di una riga\
                                         il cui contenuto viene perduto*/\
}\
\
/*------------\
 * \
 * ritorna il numero di mofuli presenti in crealtm.dat\
 *\
 *------------*/\
\
int conta_moduli_ltm(FILE *fp)\
{\
   int nmod;\
   char riga [200];\
\
   rewind(fp);     /* riposiziono il file pointer all'inizio del file */\
   skip_riga(fp);  /* skip prima riga */\
\
   nmod=0;      /* ogni record conta un modulo */\
   while( read_riga(fp,riga) != EOF)\
      nmod++;\
\
   return(nmod);\
}\
\
/*---------\
 *\
 * legge il file crealrm.dat\
 * e riempie con i dati la struttura ltm\
 *\
 *----------*/\
  \
int leggi_ltm(LTM *sltm,FILE *fp)\
{\
   int ind;\
   char riga[200],*appo;\
\
   rewind(fp);     /* riposiziono il file pointer all'inizio del file */\
   skip_riga(fp);  /* skip prima riga */\
\
   ind =0;\
   while( read_riga(fp,riga) != EOF)\
   {\
      strncpy(sltm[ind].nome_modulo,riga,4);\
      appo = &riga[4];\
      if( *appo == '*' )\
         sltm[ind].rout_std = TRUE;\
      else\
         sltm[ind].rout_std = FALSE;\
\
      appo++;\
      strcpy(sltm[ind].descr_modulo,appo);\
      ind++;\
   }\
}\
\
/*-----------------------------\
 *\
 * legge il file crealtm.dat\
 * e setta la lista\
 *\
 *------------------------------*/\
\
LoadModulesList(Widget lista)\
{\
   extern char path_modello[];\
   char fileltm[100],cstring[200];\
   FILE *fpltm;\
   int i;\
      \
   sprintf(fileltm,"%s/proc/%s",path_modello,FNAME_CREALTM);\
   if( !esiste_file( fileltm) )\
      return(False);\
\
   if( (fpltm = fopen(fileltm,"r")) == NULL )\
   {\
      fclose(fpltm);\
      return(False);\
   }\
\
   nmoduli = conta_moduli_ltm(fpltm);  \
\
   if( alloca_ltm(&ltm,nmoduli) == NULL)\
   {\
      fclose(fpltm);\
      return(False);\
   }\
\
   leggi_ltm(ltm,fpltm);\
\
   for(i=0;i<nmoduli;i++)\
   {\
       if(ltm[i].rout_std)\
          sprintf(cstring,"%s *  %s",ltm[i].nome_modulo, ltm[i].descr_modulo);\
       else\
          sprintf(cstring,"%s    %s",ltm[i].nome_modulo, ltm[i].descr_modulo);\
\
        set_item_list(lista,cstring,i+1);\
   }\
\
   return(True);\
}\
\
get_foraux(char *modname,char *path,char **auxcode)\
{\
   char minname[10];\
   char pathfile[200];\
   char pattern_search[100];\
   FILE *fp;\
   char *ptrini=NULL,*ptrfin=NULL;\
   char *strfile=NULL,*appo;\
   int i;\
   char *fcode;\
\
   strcpy(minname,modname);\
   for(i=0;i<strlen(minname);i++)\
      minname[i] = tolower(minname[i]);\
\
/* recupero il percorso del modulo in libut */\
   sprintf(pathfile,"%s/%s.f",path,minname);\
\
   if( !esiste_file(pathfile) )\
      return(False);\
\
\
   if( (fp = fopen(pathfile,"r")) == NULL)\
   {\
       fclose(fp);\
       return(False);\
   }\
\
\
   load_file_in_memory(fp,&strfile);\
\
\
   sprintf(pattern_search,"%s%s~",PATTERN,modname);\
\
   ptrini = cerca_pattern(strfile,pattern_search);\
   if( ptrini == NULL)\
      return(False);\
\
   ptrfin = cerca_pattern( (ptrini+strlen(pattern_search)),pattern_search); \
   if( ptrfin == NULL)\
      return(False);   \
\
   ptrfin += (strlen(pattern_search)+1);\
\
   fcode = malloc( ((ptrfin - ptrini) +10) );\
  \
   memcpy(fcode,ptrini,(ptrfin - ptrini));\
\
/* tappo la fine del fortran che e' chiuso da ~C */\
   appo = strrchr(fcode,'~');\
   appo += 2;\
   *appo = 0;\
      \
\
   (*auxcode) = malloc( strlen(fcode) +2 );\
   strcpy((*auxcode),fcode);\
         \
   return(True);\
}\
\
get_fortran_module(char *nome_mod,char **code)\
{\
\
   if( get_foraux(nome_mod,path_libut,code) == False)\
      return(False);\
   \
   return(True);\
}\
\
/*##########################################################################*/\
\
/*----------------------------------------------\
 *\
 *   gestione lista FORAUS\
 *\
 *----------------------------------------------*/\
\
\
/*----------------------------------\
 *\
 * recupero il nome di un modulo\
 *\
 *--------------------------------*/\
\
char *get_module_name(char *ptr)\
{\
   char *appo;\
   char nomemod[10];\
   char *ptr2=NULL;\
\
/* alloco memoria per il nome (che poi non libero) */\
   appo = malloc( sizeof(char)*6 );\
\
/* cerco l'inizio del nome del modulo all'interno del PATTERN */\
   ptr2 = strchr(ptr,'_');        \
   ptr2++;\
\
\
   strncpy(appo,ptr2,4);\
   appo[4]=0;\
\
   return(appo);\
}\
\
\
/*------------------------------------------------\
 *\
 * set del nome del modulo nell'elenco moduli\
 *\
 *------------------------------------------------*/\
set_elenco_modulo(char *modname,int pos)\
{\
   \
   elenco[pos] = malloc( strlen(modname)+2 );\
   strcpy(elenco[pos] , modname);\
}\
\
/*------------------------------------------------\
 *\
 * set del codice del modulo \
 *\
 *------------------------------------------------*/\
salva_elenco_codice(char *code,int pos)\
{\
   codice[pos] = malloc( strlen(code)+2 );\
   strcpy(codice[pos] , code);\
}\
\
\
libera_elenco_codice(int pos)\
{\
   if( codice[pos] )\
      free(codice[pos]);\
}\
\
libera_elenco_moduli(int pos)\
{\
   if( elenco[pos] )\
      free( elenco[pos] );\
}\
/*----------------------------------------------\
 *  rimuovo un modulo dal fortran ausiliario\
 *  input:   nome del modulo\
 *           posinlist  posizione nella lista\
 ----------------------------------------------*/\
\
rimuovi_modulo(int posinlist)\
{\
   int iarray,i;\
\
   iarray = posinlist -1;\
\
\
/* libero il codice del modulo */\
   libera_elenco_codice(iarray);\
   libera_elenco_moduli(iarray);\
\
/* compatto l'elenco */\
\
   printf("compatta elenco \n");\
\
   for(i = iarray;i<nmodaux-1;i++)\
   {\
      codice[i] = codice[i+1];\
      elenco[i] = elenco[i+1];\
   }\
\
\
   nmodaux--;\
}\
\
\
/*----------------------------\
 *\
 * crea l'elenco dei moduli presenti in foraus.for\
 *\
 *------------------------------*/\
\
crea_elenco(char *str)\
{\
   char *ptr1=NULL,*ptr2=NULL,appo[100];\
   char *ptrini=NULL,*ptrfin=NULL,*ptrapp=NULL;\
   char name[100],pattern_search[50];\
   char *cod;\
\
\
   nmodaux = 0;\
\
   strcpy(pattern_search,PATTERN);\
   ptr1 = str;\
   while( True ) \
   {\
\
/* cerco il pattern d'inizio codice modulo */\
      ptrini = cerca_pattern(ptr1,pattern_search);\
\
/* finisco il ciclo quando non ne trovo piu' */ \
      if( ptrini == NULL)\
         break;\
\
/* recupero il nome del modulo e lo aggiungo nella lista */\
      strcpy(name, get_module_name(ptrini));  \
      set_elenco_modulo(name,nmodaux);\
\
\
/* cerco (e mi aspetto) la fine del codice del modulo */\
      ptrfin = cerca_pattern(ptrini+strlen(pattern_search),PATTERN);  \
      if( ptrfin == NULL)\
         break;\
\
/*recupero il codice in foraus relativo al modulo */\
      cod = malloc( (ptrfin - ptrini) + strlen(pattern_search) + 10 );\
      memcpy( cod, ptrini, ( (ptrfin - ptrini ) + strlen(pattern_search) + 8 ) );\
      ptr2 = strrchr(cod,'~');\
      ptr2 += 2;\
      *ptr2=0;   \
      salva_elenco_codice( cod, nmodaux );\
      free(cod);\
\
\
/* reinizializzo e sposto un po' piu avanti il \
   pointer altrimenti ritrova questa stringa */ \
      ptr1 = ptrfin + strlen(pattern_search);\
      nmodaux++;\
   }\
   return(True);\
}\
\
LoadForausStdList()\
{\
   extern char path_modello[];\
   FILE *fpfor;\
   char filefor[100];\
   char *stringa; \
   int i;\
   \
   sprintf(filefor,"%s/%s",path_modello,FILE_FORAUS);\
   if( !esiste_file(filefor) )\
      return(False);\
 \
\
   if( (fpfor = fopen(filefor,"r")) == NULL)\
   {\
      fclose(fpfor);\
      return(False);\
   } \
\
\
   stringa = NULL;\
   if( load_file_in_memory(fpfor,&stringa) == False)\
   {\
      fclose(fpfor);\
      return(False);\
   }\
\
   if( stringa)\
   {\
      crea_elenco(stringa);\
\
      for(i=0;i<nmodaux;i++)   \
      {   \
         set_item_list(scrolledList2,elenco[i],i+1);      \
      }\
\
      free(stringa);\
   }\
 \
   return(True);\
}\
\
int save_foraus(int cod_op)\
{\
   extern swidget create_vis_msg();\
   extern char path_modello[];\
   int i;\
   char filename[200];\
   char msg[200];\
\
   switch( cod_op)\
   {\
      case SAVE_TMP_FORAUS:\
         sprintf(filename,"%s/%s",path_modello,FILE_TMP_NAME);\
      break;\
      case SAVE_FORAUS:\
         sprintf(filename,"%s/%s",path_modello,FILE_FORAUS);\
      break;\
   }\
\
/* testo la esistenza del file temporaneo */\
   if( esiste_file )\
      if( svuota_file(filename) != True)\
      {\
         sprintf(msg,"Error opening file %s",filename);\
         create_vis_msg(msg);\
         foraus_ok = False;\
         return(False);\
      }          \
      \
   for(i=0;i<nmodaux;i++)\
      put_string_on_file(filename,codice[i]);\
\
   return(True);\
}\
\
int salva_su_conferma()\
{\
    extern swidget create_vis_msg();\
\
   if( foraus_ok != True)\
   {\
      create_vis_msg("Auxiliary fortran problem.\nError on Compilation test or not compiled.");  \
      return(False);\
   } \
   else\
   {\
      /* richiama interfaccia di conferma sovrascrittura \
         per il file foraus.for\
      */\
      create_question_operation(Foraus,SAVE_FORAUS);   \
    }     \
}\
\
int aggiungi_in_foraus()\
{\
   extern swidget create_vis_msg();\
   int i,j;\
   int *pos,nitem;\
   Boolean found = False,nofor = False;\
   char *appo=NULL;\
   char mesg[200];\
\
   strcpy(mesg,"");\
   if( get_selection_list(scrolledList1,&pos,&nitem) == 0 )\
   {\
      create_vis_msg("Nothing selected!");\
      return;\
   }\
\
   for(i=0;i<nitem;i++)\
   {\
      found = False;\
      for(j=0;j<nmodaux;j++)\
      {\
         if( strcmp(ltm[ pos[i] -1 ].nome_modulo,elenco[j]) == NULL)\
         {\
             found = True;\
             break;\
         }\
         else\
         {\
            found = False;\
         }\
       }       \
\
       if( !found )\
       {\
         if( get_fortran_module( ltm[ pos[i]-1 ].nome_modulo,&appo) != False)\
         {\
            set_elenco_modulo(ltm[ pos[i] -1 ].nome_modulo,nmodaux);\
            set_item_list(scrolledList2,elenco[nmodaux],0);\
            salva_elenco_codice(appo,nmodaux);\
            nmodaux++;\
         }\
         else\
         {\
            nofor = True;\
            sprintf((mesg+strlen(mesg)),"%s\n",ltm[ pos[i]-1 ].nome_modulo);\
         }  \
       }\
   }\
\
   if( nofor )\
   {\
      sprintf((mesg+strlen(mesg)),"%s","no fortran for module");\
      create_vis_msg(mesg);\
   }\
\
   if( appo != NULL)\
      free(appo); \
\
   return(True);\
}\
\
svuota_file(char *filename)\
{\
   FILE *fp;\
  \
   if( (fp = fopen(filename,"w")) == NULL)\
   {\
      fclose(fp);\
      return(False);\
   }\
   else\
   {\
      fclose(fp);\
      return(True);\
   }    \
}\
\
/*------------\
 *\
 * testa_foraus()\
 *\
 * effettua una compilazione del foraus\
 * che dovra' essere salvato. Se la compilazione\
 * va' a buon fine setta la variabile foraus_ok\
 *\
 *--------------*/\
\
testa_foraus()\
{\
   extern swidget create_vis_msg();\
   extern char path_modello[];\
   int i;\
   char filename[200];\
\
/* salvo su file temporaneo foraus.tmp */\
   save_foraus(SAVE_TMP_FORAUS);\
\
  \
/* lancia il make di compilazione del file foraus.tmp \
   l'output deve essere rediretto sulla man window di legocad\
   e se la compilazione e' ok setta foraus_ok a True\
*/  \
\
   return(esegui_comando(TEST_FORAUS));\
} \
\
\
\
rimuovi_moduli_foraus(Widget wcaller)\
{\
#ifndef DESIGN_TIME\
   _UxCForaus              *UxSaveCtx, *UxContext;\
#endif\
\
   int i,*pos,nit;\
\
#ifndef DESIGN_TIME\
   UxSaveCtx = UxForausContext;\
   UxForausContext = UxContext =\
              (_UxCForaus *) UxGetContext( wcaller);\
#endif\
\
\
\
  if( get_selection_list(scrolledList2,&pos,&nit) == 0)\
  {\
     create_vis_msg("Nothing selected");\
     return;\
  }\
  else\
  {\
    for(i=0;i<nit;i++)\
    {\
       if(i)\
       {\
          XmListDeletePos(scrolledList2,pos[i]-i);\
          rimuovi_modulo(pos[i]-i);\
       }\
       else\
       {\
          XmListDeletePos(scrolledList2,pos[i]);\
          rimuovi_modulo(pos[i]);\
       }\
    }\
  }\
\
#ifndef DESIGN_TIME\
  UxForausContext = UxSaveCtx;\
#endif\
}\
\
\
delete_foraus(Widget wcaller)\
{\
#ifndef DESIGN_TIME\
   _UxCForaus              *UxSaveCtx, *UxContext;\
#endif\
\
   extern swidget create_vis_msg();\
   char comando[256];\
   int i;\
\
#ifndef DESIGN_TIME\
   UxSaveCtx = UxForausContext;\
   UxForausContext = UxContext =\
              (_UxCForaus *) UxGetContext( wcaller);\
#endif\
\
/* libero il vettore */ \
   for(i = 0;i<nmodaux;i++)\
   {\
      free(codice[i]);\
      free(elenco[i]);\
   }\
\
   nmodaux=0;\
\
/* e cancello il file foraus */\
   if( !esiste_file(FILE_FORAUS) )\
      create_vis_msg("Auxiliary fortran file foraus.for not exists");\
   else\
   {\
      sprintf(comando,"rm %s",FILE_FORAUS);\
      system(comando);\
   }\
#ifndef DESIGN_TIME\
  UxForausContext = UxSaveCtx;\
#endif\
}
*Foraus.name: Foraus
*Foraus.resizePolicy: "resize_none"
*Foraus.unitType: "pixels"
*Foraus.x: 210
*Foraus.y: 169
*Foraus.width: 740
*Foraus.height: 480
*Foraus.dialogTitle: "Edit Auxiliary Fortran"

*pushButton3.class: pushButton
*pushButton3.parent: Foraus
*pushButton3.static: true
*pushButton3.name: pushButton3
*pushButton3.x: 20
*pushButton3.y: 430
*pushButton3.width: 140
*pushButton3.height: 30
*pushButton3.labelString: "Ok"
*pushButton3.activateCallback: {\
salva_su_conferma();\
}
*pushButton3.bottomAttachment: "attach_form"
*pushButton3.bottomOffset: 15
*pushButton3.leftAttachment: "attach_form"
*pushButton3.leftOffset: 20
*pushButton3.rightAttachment: "attach_none"
*pushButton3.rightOffset: 620

*pushButton5.class: pushButton
*pushButton5.parent: Foraus
*pushButton5.static: true
*pushButton5.name: pushButton5
*pushButton5.x: 20
*pushButton5.y: 340
*pushButton5.width: 90
*pushButton5.height: 40
*pushButton5.labelString: "Select All"
*pushButton5.activateCallback: {\
select_all_item(scrolledList1);\
}
*pushButton5.leftAttachment: "attach_form"
*pushButton5.leftOffset: 20
*pushButton5.bottomAttachment: "attach_widget"
*pushButton5.bottomOffset: 30
*pushButton5.bottomWidget: "pushButton3"

*pushButton6.class: pushButton
*pushButton6.parent: Foraus
*pushButton6.static: true
*pushButton6.name: pushButton6
*pushButton6.x: 110
*pushButton6.y: 340
*pushButton6.width: 90
*pushButton6.height: 40
*pushButton6.labelString: "Unselect All"
*pushButton6.activateCallback: {\
unselect_all_item(scrolledList1);\
}
*pushButton6.bottomAttachment: "attach_widget"
*pushButton6.bottomOffset: 30
*pushButton6.bottomWidget: "pushButton3"
*pushButton6.leftAttachment: "attach_widget"
*pushButton6.leftOffset: 5
*pushButton6.leftWidget: "pushButton5"

*label8.class: label
*label8.parent: Foraus
*label8.static: true
*label8.name: label8
*label8.x: 20
*label8.y: 10
*label8.width: 120
*label8.height: 20
*label8.alignment: "alignment_beginning"
*label8.labelString: "module list"
*label8.leftAttachment: "attach_form"
*label8.leftOffset: 20
*label8.bottomAttachment: "attach_none"
*label8.topAttachment: "attach_form"
*label8.topOffset: 10

*arrowButton1.class: arrowButton
*arrowButton1.parent: Foraus
*arrowButton1.static: true
*arrowButton1.name: arrowButton1
*arrowButton1.x: 390
*arrowButton1.y: 160
*arrowButton1.width: 50
*arrowButton1.height: 50
*arrowButton1.arrowDirection: "arrow_right"
*arrowButton1.activateCallback: {\
aggiungi_in_foraus();\
}
*arrowButton1.rightAttachment: "attach_form"
*arrowButton1.rightOffset: 300
*arrowButton1.leftAttachment: "attach_none"
*arrowButton1.leftOffset: 30

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.parent: Foraus
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.scrollingPolicy: "application_defined"
*scrolledWindow2.x: 20
*scrolledWindow2.y: 40
*scrolledWindow2.visualPolicy: "variable"
*scrolledWindow2.scrollBarDisplayPolicy: "static"
*scrolledWindow2.shadowThickness: 0
*scrolledWindow2.leftAttachment: "attach_form"
*scrolledWindow2.leftOffset: 20
*scrolledWindow2.bottomAttachment: "attach_widget"
*scrolledWindow2.bottomOffset: 10
*scrolledWindow2.bottomWidget: "pushButton5"
*scrolledWindow2.topAttachment: "attach_widget"
*scrolledWindow2.topOffset: 10
*scrolledWindow2.topWidget: "label8"
*scrolledWindow2.rightAttachment: "attach_widget"
*scrolledWindow2.rightOffset: 10
*scrolledWindow2.rightWidget: "arrowButton1"

*scrolledList1.class: scrolledList
*scrolledList1.parent: scrolledWindow2
*scrolledList1.static: true
*scrolledList1.name: scrolledList1
*scrolledList1.width: 260
*scrolledList1.height: 315
*scrolledList1.itemCount: 0
*scrolledList1.selectionPolicy: "multiple_select"
*scrolledList1.multipleSelectionCallback: {\
{\
int *positions,item;\
\
if( get_selection_list( scrolledList1,&positions,&item) == False)\
   UxPutSensitive(arrowButton1,"false");\
else\
   UxPutSensitive(arrowButton1,"true");\
}\
}

*menu3.class: rowColumn
*menu3.parent: scrolledList1
*menu3.static: true
*menu3.name: menu3
*menu3.rowColumnType: "menu_popup"
*menu3.mapCallback: {\
int *posiz=NULL,nsel=0;\
\
printf("chaimata la Map callback del popup menu\nrelativo alla module list\n"); \
\
if( get_selection_list(scrolledList1,&posiz,&nsel) == True)\
{\
  printf("%d item selected in module list \n",nsel);\
   UxPutSensitive( view_fortran,"true");\
   UxPutSensitive( view_doc,"true");\
}\
else\
{\
   UxPutSensitive( view_fortran,"false");\
   UxPutSensitive( view_doc,"false");\
}\
if(posiz != NULL)\
   free(posiz);\
}
*menu3.menuAccelerator: "<KeyUp>F4"

*view_fortran.class: pushButton
*view_fortran.parent: menu3
*view_fortran.static: true
*view_fortran.name: view_fortran
*view_fortran.labelString: "View fortran"
*view_fortran.activateCallback: {\
  extern swidget create_vis_msg();\
  extern swidget create_editText();\
  swidget swid;\
  int *pos,nit;\
  char titolo[200];\
\
  if( get_selection_list(scrolledList1,&pos,&nit) == 0)\
  {\
     create_vis_msg("Nothing selected");\
     return;\
  }\
  if( nit > 1)\
  {\
     create_vis_msg("Too much items selected");\
     return;\
  }\
 \
\
#ifndef DESIGN_TIME\
  if( get_fortran_module( ltm[ pos[0]-1 ].nome_modulo,&(ltm[ pos[0]-1 ]).auxftn_modulo ) == False)\
  {\
    create_vis_msg("No auxiliary fortran for selected module.");\
    return;       \
  }\
#endif\
\
  if( strlen( ltm[ pos[0]-1 ].auxftn_modulo ) == 0 )\
  {\
    create_vis_msg("No auxiliary fortran for selected module.");\
    return;       \
  }\
\
  create_editText(foraus_edit_fortran,VIEW_FORAUS,(ltm[ pos[0]-1 ]).auxftn_modulo,&(ltm[pos[0]-1]).auxftn_modulo,NULL );\
\
}

*view_doc.class: pushButton
*view_doc.parent: menu3
*view_doc.static: true
*view_doc.name: view_doc
*view_doc.labelString: "View module doc"
*view_doc.activateCallback: {\
\
  extern swidget create_vis_msg();\
  int *pos,nit;\
 \
  create_vis_msg("Use Librarian (Documentation View) for see module documentation");\
  return;\
\
  if( get_selection_list(scrolledList1,pos,&nit) == 0)\
  {\
     create_vis_msg("Nothing selected");\
     return;\
  }\
  if( nit > 1)\
  {\
     create_vis_msg("Too much items selected");\
     return;\
  }\
    \
\
}

*label9.class: label
*label9.parent: Foraus
*label9.static: true
*label9.name: label9
*label9.x: 460
*label9.y: 10
*label9.width: 250
*label9.height: 20
*label9.alignment: "alignment_beginning"
*label9.labelString: "std routine in auxiliary fortran"
*label9.leftAttachment: "attach_widget"
*label9.leftOffset: 10
*label9.leftWidget: "arrowButton1"
*label9.topAttachment: "attach_form"
*label9.topOffset: 10

*scrolledWindow4.class: scrolledWindow
*scrolledWindow4.parent: Foraus
*scrolledWindow4.static: true
*scrolledWindow4.name: scrolledWindow4
*scrolledWindow4.scrollingPolicy: "application_defined"
*scrolledWindow4.x: 360
*scrolledWindow4.y: 50
*scrolledWindow4.visualPolicy: "variable"
*scrolledWindow4.scrollBarDisplayPolicy: "static"
*scrolledWindow4.shadowThickness: 0
*scrolledWindow4.rightAttachment: "attach_form"
*scrolledWindow4.rightOffset: 20
*scrolledWindow4.bottomOffset: 10
*scrolledWindow4.bottomAttachment: "attach_widget"
*scrolledWindow4.bottomWidget: "pushButton5"
*scrolledWindow4.topOffset: 10
*scrolledWindow4.topAttachment: "attach_widget"
*scrolledWindow4.topWidget: "label8"
*scrolledWindow4.width: 250
*scrolledWindow4.leftAttachment: "attach_widget"
*scrolledWindow4.leftOffset: 10
*scrolledWindow4.leftWidget: "arrowButton1"

*scrolledList2.class: scrolledList
*scrolledList2.parent: scrolledWindow4
*scrolledList2.static: true
*scrolledList2.name: scrolledList2
*scrolledList2.width: 250
*scrolledList2.height: 290
*scrolledList2.itemCount: 0
*scrolledList2.selectionPolicy: "multiple_select"

*menu4.class: rowColumn
*menu4.parent: scrolledList2
*menu4.static: true
*menu4.name: menu4
*menu4.rowColumnType: "menu_popup"
*menu4.menuAccelerator: "<KeyUp>F4"
*menu4.mapCallback: {\
int *posiz=NULL,nsel=0;\
\
if( get_selection_list(scrolledList2,&posiz,&nsel) == True)\
{\
   UxPutSensitive( foraus_view_fortran,"true");\
   UxPutSensitive( foraus_remove_fortran,"true");\
}\
else\
{\
   UxPutSensitive( foraus_view_fortran,"false");\
   UxPutSensitive( foraus_remove_fortran,"false");\
}\
if(posiz != NULL)\
   free(posiz);\
}

*foraus_view_fortran.class: pushButton
*foraus_view_fortran.parent: menu4
*foraus_view_fortran.static: true
*foraus_view_fortran.name: foraus_view_fortran
*foraus_view_fortran.labelString: "View Fortran"
*foraus_view_fortran.activateCallback: {\
\
  extern swidget create_vis_msg();\
  extern swidget create_editText();\
  int *pos,nit;\
\
  if( get_selection_list(scrolledList2,&pos,&nit) == 0)\
  {\
     create_vis_msg("Nothing selected");\
     return;\
  }\
  if( nit > 1)\
  {\
     create_vis_msg("Too much items selected");\
     return;\
  }\
\
  create_editText(foraus_edit_fortran,VIEW_FORAUS,codice[ pos[0]-1 ],&(codice[pos[0]-1]),NULL );\
}\


*foraus_remove_fortran.class: pushButton
*foraus_remove_fortran.parent: menu4
*foraus_remove_fortran.static: true
*foraus_remove_fortran.name: foraus_remove_fortran
*foraus_remove_fortran.labelString: "Remove fortran"
*foraus_remove_fortran.activateCallback: {\
   extern swidget create_vis_msg();\
   int *pos,nit;\
\
  if( get_selection_list(scrolledList2,&pos,&nit) == 0)\
  {\
     create_vis_msg("Nothing selected");\
     return;\
  }\
\
   create_question_operation(Foraus,REMOVE_FORAUS);\
}

*foraus_edit_fortran.class: pushButton
*foraus_edit_fortran.parent: menu4
*foraus_edit_fortran.static: true
*foraus_edit_fortran.name: foraus_edit_fortran
*foraus_edit_fortran.labelString: "Edit Fortran"
*foraus_edit_fortran.activateCallback: {\
\
  extern swidget create_vis_msg();\
  extern swidget create_editText();\
  int *pos,nit;\
\
  if( get_selection_list(scrolledList2,&pos,&nit) == 0)\
  {\
     create_vis_msg("Nothing selected");\
     return;\
  }\
  if( nit > 1)\
  {\
     create_vis_msg("Too much items selected");\
     return;\
  }\
\
  create_editText(foraus_edit_fortran,EDIT_FORAUS,codice[ pos[0]-1 ],&(codice[pos[0]-1]),NULL );\
}\


*pushButton9.class: pushButton
*pushButton9.parent: Foraus
*pushButton9.static: true
*pushButton9.name: pushButton9
*pushButton9.x: 280
*pushButton9.y: 430
*pushButton9.width: 140
*pushButton9.height: 30
*pushButton9.labelString: "Compilation Test"
*pushButton9.activateCallback: {\
extern swidget create_vis_msg();\
\
if( testa_foraus() == 0 )\
  foraus_ok = True;\
else\
{\
   create_vis_msg("Auxiliary fortran compilation error");\
   foraus_ok = False;\
}\
}
*pushButton9.bottomAttachment: "attach_form"
*pushButton9.bottomOffset: 15
*pushButton9.leftAttachment: "attach_form"
*pushButton9.leftOffset: 300
*pushButton9.leftWidget: "pushButton3"

*pushButton4.class: pushButton
*pushButton4.parent: Foraus
*pushButton4.static: true
*pushButton4.name: pushButton4
*pushButton4.x: 590
*pushButton4.y: 440
*pushButton4.width: 140
*pushButton4.height: 30
*pushButton4.labelString: "Cancel"
*pushButton4.activateCallback: {\
UxDestroyInterface(XtParent(UxWidget));\
}
*pushButton4.rightAttachment: "attach_none"
*pushButton4.rightOffset: 20
*pushButton4.bottomAttachment: "attach_form"
*pushButton4.bottomOffset: 15
*pushButton4.leftAttachment: "attach_form"
*pushButton4.leftOffset: 580
*pushButton4.leftWidget: "pushButton9"

*pushButton7.class: pushButton
*pushButton7.parent: Foraus
*pushButton7.static: true
*pushButton7.name: pushButton7
*pushButton7.x: 460
*pushButton7.y: 340
*pushButton7.width: 90
*pushButton7.height: 40
*pushButton7.labelString: "Select All"
*pushButton7.activateCallback: {\
select_all_item(scrolledList2);\
}
*pushButton7.leftAttachment: "attach_widget"
*pushButton7.leftOffset: 10
*pushButton7.leftWidget: "arrowButton1"
*pushButton7.bottomAttachment: "attach_widget"
*pushButton7.bottomOffset: 30
*pushButton7.bottomWidget: "pushButton4"
*pushButton7.topAttachment: "attach_widget"
*pushButton7.topOffset: 10
*pushButton7.topWidget: "scrolledWindow2"

*pushButton8.class: pushButton
*pushButton8.parent: Foraus
*pushButton8.static: true
*pushButton8.name: pushButton8
*pushButton8.x: 550
*pushButton8.y: 340
*pushButton8.width: 90
*pushButton8.height: 40
*pushButton8.labelString: "Unselect All"
*pushButton8.activateCallback: {\
unselect_all_item(scrolledList2);\
}
*pushButton8.leftAttachment: "attach_widget"
*pushButton8.leftOffset: 10
*pushButton8.leftWidget: "pushButton7"
*pushButton8.bottomAttachment: "attach_widget"
*pushButton8.bottomOffset: 30
*pushButton8.bottomWidget: "pushButton4"
*pushButton8.topAttachment: "attach_widget"
*pushButton8.topOffset: 10
*pushButton8.topWidget: "scrolledWindow2"

