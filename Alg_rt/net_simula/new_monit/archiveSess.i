! UIMX ascii 2.8 key: 7279                                                      

*archiveSess.class: formDialog
*archiveSess.classinc:
*archiveSess.classspec:
*archiveSess.classmembers:
*archiveSess.classconstructor:
*archiveSess.classdestructor:
*archiveSess.gbldecl: #include <stdio.h>\
\
#include <sys/stat.h>\
#include <sys/types.h>\
#include "sim_param.h"\
#include "sim_types.h"\
#include "comandi.h"\
#include "sked.h"\
#include "refresh.h"\
#include "f22_circ.h"\
\
\
#define MAX_NAME_DIR	256\
#define SESS_STAT_WARN	"WARN_F22"\
#define SESS_STAT_OK	"-OK_F22-"\
\
typedef struct {\
                int  position;\
                char status[20];\
               } POS_SESS;\
\
\
extern int 	_MAX_BACK_TRACK;\
extern VAL 	val;\
\
int recoveryInfoSession();\
int createDirSession();\
int recoveryRangeF22(float *,float *);\
int liberaAllocDinam();\

*archiveSess.ispecdecl: XmString	*list_sess;\
BKTAB		*bk_sess_head;\
POS_SESS	*pos_sess_bktab;\
char		nome_dir_sess[MAX_NAME_DIR];
*archiveSess.ispeclist: list_sess, bk_sess_head, pos_sess_bktab, nome_dir_sess
*archiveSess.ispeclist.list_sess: "XmString", "*%list_sess%"
*archiveSess.ispeclist.bk_sess_head: "BKTAB", "*%bk_sess_head%"
*archiveSess.ispeclist.pos_sess_bktab: "POS_SESS", "*%pos_sess_bktab%"
*archiveSess.ispeclist.nome_dir_sess: "char", "%nome_dir_sess%[256]"
*archiveSess.funcdecl: swidget create_archiveSess(UxParent)\
swidget UxParent;
*archiveSess.funcname: create_archiveSess
*archiveSess.funcdef: "swidget", "<create_archiveSess>(%)"
*archiveSess.argdecl: swidget UxParent;
*archiveSess.arglist: UxParent
*archiveSess.arglist.UxParent: "swidget", "%UxParent%"
*archiveSess.icode:
*archiveSess.fcode: if(recoveryInfoSession()==0) {\
   UxPopupInterface(rtrn, no_grab);\
}\
else {\
   fprintf(stderr,"WARNING!!! Error in dynamic allocation.\n");\
}\
return(rtrn);\

*archiveSess.auxdecl: /*******************************************************************/\
/*                                                                 */\
/*   Funzione che recupera dal file backtrack.dat il tempo di      */\
/*   inizio e la descrizione delle sessioni presenti. Carica       */\
/*   inoltre queste informazioni nell'interfaccia 'archiveSess'.   */\
/*                                                                 */\
/*******************************************************************/\
int recoveryInfoSession()\
{\
FILE		*fp_bktk = NULL;\
int		tot_session = 0;\
int		i,j,k,last_backtrack,ind_list;\
STATO_CR	stato_cr;\
char		str_sess[300];\
int		ore,minuti,secondi,giorno,mese,anno;\
float		time_st_f22,time_end_f22,time_st_sess;\
\
   pos_sess_bktab=NULL;\
   bk_sess_head=NULL;\
   list_sess=NULL;\
\
   if((fp_bktk=fopen("backtrack.dat", "r"))==NULL) {\
      fprintf(stderr,"Backtrack file not existent\n");\
      return(-1);\
   }\
   else {\
      pos_sess_bktab=(POS_SESS *)XtCalloc(_MAX_BACK_TRACK,sizeof(POS_SESS));\
      if(pos_sess_bktab==NULL) {\
         fprintf(stderr,"Error in XtCalloc: pos_sess_bktab\n");\
         return(-1);\
      }\
      bk_sess_head=(BKTAB*)XtCalloc(_MAX_BACK_TRACK,sizeof(BKTAB));\
      if(bk_sess_head==NULL) {\
         fprintf(stderr,"Error in XtCalloc:bk_sess_head\n");\
         XtFree(pos_sess_bktab);\
         return(-1);\
      }\
      list_sess=(XmString *)XtCalloc(_MAX_BACK_TRACK,sizeof(XmString));\
      if(list_sess==NULL) {\
        fprintf(stderr,"Error in XtCalloc: list_sess\n");\
        XtFree(pos_sess_bktab);\
        XtFree(bk_sess_head);\
        return(-1);\
      }  \
         \
      fseek(fp_bktk,sizeof(HEADER_REGISTRAZIONI),SEEK_SET);\
\
printf("*********************************************\n");\
printf("Stato dei backtrack presenti in backtrack.dat\n");\
printf("*********************************************\n");\
printf("NUM\tSTAT\tFORZ\tDESCR\t\tTEMPO\n");\
\
      for(i=1;i<=_MAX_BACK_TRACK;i++) {\
         fread(&bk_sess_head[i-1],sizeof(BKTAB),1,fp_bktk);\
\
printf(" %d\t%d\t%d\t%s\t%f\n",\
       i,bk_sess_head[i-1].stat,bk_sess_head[i-1].forzato,\
       bk_sess_head[i-1].descr,bk_sess_head[i-1].tempo);\
\
      }\
\
printf("*********************************************\n");\
\
      load_stato_cr(&stato_cr);\
/*\
   Recupero dei tempi del primo e dell'ultimo campione presenti nel\
   file f22circ.dat corrente\
*/\
      recoveryRangeF22(&time_st_f22,&time_end_f22);\
\
printf("time_st_f22 = %f\ttime_end_f22 = %f\n",time_st_f22,time_end_f22);\
\
/*      \
   Ciclo su tutti i backtrack presenti. Si estraggono quelli che\
   corrispondono all'inizio di una sessione e si caricano tempo e\
   descrizione nell'interfaccia.\
*/\
      last_backtrack=stato_cr.last_bktk_save;\
      k=last_backtrack+1;\
      if(k>_MAX_BACK_TRACK)\
         k=1;\
      ind_list=0;\
\
printf("**********************************************************\n");\
printf("Elenco dei backtrack che sono inizio di una nuova sessione\n");\
printf("**********************************************************\n");\
printf("NUM\tTIME\tDESCRIPTION\n");\
\
      for(j=0,k=last_backtrack+1;j<_MAX_BACK_TRACK;k++,j++) {\
         if(k>_MAX_BACK_TRACK)\
            k=1;\
         if((bk_sess_head[k-1].stat==1)&&(bk_sess_head[k-1].forzato!=0)) {\
            /* Il backtrack corrente e'inizio di una sessione */\
            pos_sess_bktab[ind_list].position=k;\
/*\
printf("pos_sess_bktab[%d] = %d\n",ind_list,pos_sess_bktab[ind_list].position); \
*/\
            ore=0;\
            minuti=0;\
            secondi=0;\
            giorno=1;\
            mese=1;\
            anno=2000;\
            converti_tempo((bk_sess_head[k-1].tempo/1000.0),&ore,&minuti,&secondi,&giorno,\
                           &mese,&anno);\
            time_st_sess=(bk_sess_head[k-1].tempo)/1000.0;\
/*\
printf("time_st_sess= %f\n", time_st_sess); \
*/\
            if(time_st_sess<time_st_f22) {\
               sprintf(str_sess,"%2d:%2d:%2d   -%s-   %s",ore,minuti,secondi,\
                       SESS_STAT_WARN,bk_sess_head[k-1].descr);\
               strcpy(pos_sess_bktab[ind_list].status,SESS_STAT_WARN);\
            }\
            else {\
               sprintf(str_sess,"%2d:%2d:%2d   -%s-   %s",ore,minuti,secondi,\
                       SESS_STAT_OK,bk_sess_head[k-1].descr);\
               strcpy(pos_sess_bktab[ind_list].status,SESS_STAT_OK);\
            } \
 \
printf(" %d\t%2d:%2d:%2d\t%s\n", pos_sess_bktab[ind_list].position,ore,minuti,\
       secondi,bk_sess_head[k-1].descr);\
            list_sess[ind_list]=XmStringCreateSimple(str_sess);\
            ind_list++;\
         }         \
      }\
\
printf("**********************************************************\n");\
      \
      XtVaSetValues(scrolledListSess,XmNitems,list_sess,XmNitemCount,\
                    ind_list,XmNvisibleItemCount,5,NULL);\
      fclose(fp_bktk);\
   }\
return(0);           \
}\
\
\
\
\
/*******************************************************************/\
/*                                                                 */\
/*   Funzione che crea la directory di archiviazione dei files     */\
/*   relativi alla sessione selezionata e il file README relativo. */\
/*                                                                 */\
/*******************************************************************/ \
int createDirSession(descr_session,sess_state)\
char	*descr_session;\
char	*sess_state;\
{\
\
FILE	*fp_app,*fp_readme;\
int	out_sys;\
char	*path_session;\
char	path_tmp[FILENAME_MAX],pid_curr[10];\
char	comando[FILENAME_MAX+20];\
char	warn_readme[200];\
\
\
printf("**************************\n");\
printf("Lancio della shell archive\n");\
printf("**************************\n");\
\
   strcpy(path_tmp,getenv("HOME"));\
   strcat(path_tmp,"/tmp");\
   strcat(path_tmp,"/app_arch_");\
   sprintf(pid_curr,"%d",getpid());\
   strcat(path_tmp,pid_curr);\
\
   strcpy(comando,"archive > ");\
   strcat(comando,path_tmp);\
      \
   out_sys=system(comando);\
   if(out_sys==-1) {\
      perror("esecuzione della shell: archive");\
      return(-1);\
   }\
   /* La shell e' stata eseguita correttamente. Recupero del nome della\
      directory.                                                        */\
   if((fp_app=fopen(path_tmp,"r")) == NULL) {\
      perror("apertura del file: app_archive");\
      return(-1);\
   }\
   fgets(nome_dir_sess,MAX_NAME_DIR,fp_app);\
   nome_dir_sess[strlen(nome_dir_sess)-1]='\0';  /* si toglie il new line */\
   fclose(fp_app);\
   strcpy(comando,"rm ");\
   strcat(comando,path_tmp);\
   out_sys=system(comando);\
   if(out_sys==-1) {\
      perror("rimozione del file app_archive");\
      return(-1);\
   }\
   /* Creazione della directory di archiviazione */\
   path_session=(char *)getcwd((char *) NULL, FILENAME_MAX+1);\
   strcat(path_session,"/");\
   strcat(path_session,nome_dir_sess);\
   if(mkdir(path_session,S_IRWXU|S_IRGRP|S_IROTH)) {\
      perror("creazione directory di archiviazione");\
      return(-1);\
   }\
   /* Creazione del file 'README' nella directory appena creata. */\
   strcat(path_session,"/README");\
   if((strcmp(descr_session,""))==0) {\
      printf("WARNING!!! Descrizione sessione assente.\n");\
      strcpy(descr_session,"No description");\
   }\
   if((fp_readme=fopen(path_session,"w")) == NULL) {\
      perror("apertura del file: README");\
      return(-1);\
   }   \
   strcat(descr_session,"\n");\
   fwrite(descr_session,sizeof(char),(strlen(descr_session)),fp_readme);\
   if(strcmp(sess_state,SESS_STAT_WARN)==0) {\
      strcpy(warn_readme,"WARNING!!! Non allineati i tempi nei files backtrack.dat e f22circ.dat\n");\
      fwrite(warn_readme,sizeof(char),(strlen(warn_readme)),fp_readme);\
   }\
   fclose(fp_readme);\
\
return(0);\
\
}\
\
/*******************************************************************/\
/*                                                                 */\
/*   Funzione che recupera i tempi del primo e dell'ultimo         */\
/*   presenti nel file f22circ.dat corrente                        */\
/*                                                                 */\
/*******************************************************************/\
int recoveryRangeF22(first_time,last_time)\
float *first_time;\
float *last_time;\
{\
int campione,offset;\
PUNT_FILE_F22 file_f22;\
F22CIRC_HD header;\
SIMULATOR simpar;\
F22CIRC_T t_22;\
int size_campione;\
int offheader;\
\
\
   if(f22_open_file("f22circ", &file_f22)==0) {\
      fprintf(stderr,"Errore apertura file f22circ.dat\n");\
      return(-1);\
   }\
   if(f22_leggo_header(&header,file_f22,0,&simpar)==0) {\
     fprintf(stderr,"Errore lettura header file f22circ.dat\n"); \
     return(-1);\
   }\
   size_campione = (header.num_var_graf ) *sizeof(float) + sizeof(F22CIRC_T);\
   offheader = sizeof(HEADER_REGISTRAZIONI) + sizeof(F22CIRC_HD) +\
               sizeof(F22CIRC_VAR) * header.num_var_graf;\
/*\
   Recupero del tempo dell'ultimo campione\
*/\
   campione=header.p_fine;\
   offset=offheader + (campione-1)*size_campione;\
   fseek(file_f22.fp,offset,SEEK_SET);\
   fread(&t_22,sizeof(F22CIRC_T),1,file_f22.fp);\
   *last_time=t_22.tempo;\
/*\
   Recupero del tempo del primo campione\
*/\
   campione=header.p_iniz;\
   offset=offheader + (campione-1)*size_campione;\
   fseek(file_f22.fp,offset,SEEK_SET);\
   fread(&t_22,sizeof(F22CIRC_T),1,file_f22.fp);\
   *first_time=t_22.tempo;\
 \
   f22_close_file(file_f22);\
\
}\
\
\
\
/*******************************************************************/\
/*                                                                 */\
/*   Funzione che libera le strutture allocate dinamicamente       */\
/*                                                                 */\
/*******************************************************************/\
int liberaAllocDinam()\
{\
int	i;\
\
   for(i=0;i<_MAX_BACK_TRACK;i++) {\
      if(list_sess[i]!=NULL) {\
         XmStringFree(list_sess[i]);\
      }\
   }\
   if(list_sess!=NULL) {\
      XtFree(list_sess);\
   }\
   if(bk_sess_head!=NULL) {\
      XtFree(bk_sess_head);\
   }\
   if(pos_sess_bktab!=NULL) {\
      XtFree(pos_sess_bktab);\
   }\
\
}
*archiveSess.static: true
*archiveSess.name: archiveSess
*archiveSess.parent: NO_PARENT
*archiveSess.parentExpression: UxParent
*archiveSess.defaultShell: topLevelShell
*archiveSess.width: 420
*archiveSess.height: 460
*archiveSess.isCompound: "true"
*archiveSess.compoundIcon: "formD.xpm"
*archiveSess.compoundName: "form_Dialog"
*archiveSess.x: 500
*archiveSess.y: 640
*archiveSess.unitType: "pixels"
*archiveSess.autoUnmanage: "false"

*labelTitle.class: label
*labelTitle.static: true
*labelTitle.name: labelTitle
*labelTitle.parent: archiveSess
*labelTitle.isCompound: "true"
*labelTitle.compoundIcon: "label.xpm"
*labelTitle.compoundName: "label_"
*labelTitle.x: 0
*labelTitle.y: 0
*labelTitle.width: 460
*labelTitle.height: 25
*labelTitle.rightAttachment: "attach_form"
*labelTitle.leftAttachment: "attach_form"
*labelTitle.labelString: "Selected session"
*labelTitle.alignment: "alignment_beginning"
*labelTitle.leftOffset: 20
*labelTitle.rightOffset: 20
*labelTitle.topOffset: 10
*labelTitle.topAttachment: "attach_form"

*scrolledWindowSess.class: scrolledWindow
*scrolledWindowSess.static: true
*scrolledWindowSess.name: scrolledWindowSess
*scrolledWindowSess.parent: archiveSess
*scrolledWindowSess.scrollingPolicy: "application_defined"
*scrolledWindowSess.visualPolicy: "variable"
*scrolledWindowSess.scrollBarDisplayPolicy: "static"
*scrolledWindowSess.shadowThickness: 0
*scrolledWindowSess.isCompound: "true"
*scrolledWindowSess.compoundIcon: "scrllist.xpm"
*scrolledWindowSess.compoundName: "scrolled_List"
*scrolledWindowSess.x: 20
*scrolledWindowSess.y: 40
*scrolledWindowSess.rightAttachment: "attach_form"
*scrolledWindowSess.rightOffset: 20
*scrolledWindowSess.leftAttachment: "attach_form"
*scrolledWindowSess.leftOffset: 20
*scrolledWindowSess.topOffset: 40
*scrolledWindowSess.bottomAttachment: "attach_form"
*scrolledWindowSess.bottomOffset: 180
*scrolledWindowSess.topAttachment: "attach_form"
*scrolledWindowSess.height: 250

*scrolledListSess.class: scrolledList
*scrolledListSess.static: true
*scrolledListSess.name: scrolledListSess
*scrolledListSess.parent: scrolledWindowSess
*scrolledListSess.width: 410
*scrolledListSess.height: 250
*scrolledListSess.selectionPolicy: "extended_select"
*scrolledListSess.automaticSelection: "true"
*scrolledListSess.scrollBarDisplayPolicy: "as_needed"
*scrolledListSess.resizeRecursion: "none"
*scrolledListSess.dragRecursion: "up"
*scrolledListSess.listSizePolicy: "resize_if_possible"

*separSess.class: separator
*separSess.static: true
*separSess.name: separSess
*separSess.parent: archiveSess
*separSess.width: 460
*separSess.height: 20
*separSess.isCompound: "true"
*separSess.compoundIcon: "sep.xpm"
*separSess.compoundName: "separator_"
*separSess.x: 0
*separSess.y: 420
*separSess.rightAttachment: "attach_form"
*separSess.leftAttachment: "attach_form"
*separSess.topAttachment: "attach_widget"
*separSess.topOffset: 10
*separSess.topWidget: "scrolledWindowSess"

*labelDescr.class: label
*labelDescr.static: true
*labelDescr.name: labelDescr
*labelDescr.parent: archiveSess
*labelDescr.isCompound: "true"
*labelDescr.compoundIcon: "label.xpm"
*labelDescr.compoundName: "label_"
*labelDescr.x: 0
*labelDescr.y: 430
*labelDescr.width: 460
*labelDescr.height: 25
*labelDescr.labelString: "Selected session description"
*labelDescr.rightAttachment: "attach_form"
*labelDescr.leftAttachment: "attach_form"
*labelDescr.topAttachment: "attach_widget"
*labelDescr.topOffset: 0
*labelDescr.topWidget: "separSess"
*labelDescr.alignment: "alignment_beginning"
*labelDescr.leftOffset: 20
*labelDescr.rightOffset: 20

*textField1.class: textField
*textField1.static: true
*textField1.name: textField1
*textField1.parent: archiveSess
*textField1.width: 390
*textField1.isCompound: "true"
*textField1.compoundIcon: "textfield.xpm"
*textField1.compoundName: "text_Field"
*textField1.x: 40
*textField1.y: 470
*textField1.height: 30
*textField1.rightAttachment: "attach_form"
*textField1.rightOffset: 20
*textField1.leftAttachment: "attach_form"
*textField1.topAttachment: "attach_widget"
*textField1.topOffset: 5
*textField1.topWidget: "labelDescr"
*textField1.leftOffset: 20
*textField1.marginHeight: 2

*separOkCanc.class: separator
*separOkCanc.static: true
*separOkCanc.name: separOkCanc
*separOkCanc.parent: archiveSess
*separOkCanc.width: 460
*separOkCanc.height: 20
*separOkCanc.isCompound: "true"
*separOkCanc.compoundIcon: "sep.xpm"
*separOkCanc.compoundName: "separator_"
*separOkCanc.x: 10
*separOkCanc.y: 480
*separOkCanc.leftOffset: 0
*separOkCanc.rightAttachment: "attach_form"
*separOkCanc.topAttachment: "attach_widget"
*separOkCanc.topOffset: 10
*separOkCanc.topWidget: "textField1"
*separOkCanc.leftAttachment: "attach_form"

*pushButOk.class: pushButton
*pushButOk.static: true
*pushButOk.name: pushButOk
*pushButOk.parent: archiveSess
*pushButOk.isCompound: "true"
*pushButOk.compoundIcon: "push.xpm"
*pushButOk.compoundName: "push_Button"
*pushButOk.x: 40
*pushButOk.y: 510
*pushButOk.width: 120
*pushButOk.height: 35
*pushButOk.topAttachment: "attach_widget"
*pushButOk.topOffset: 10
*pushButOk.topWidget: "separOkCanc"
*pushButOk.labelString: "Ok"
*pushButOk.activateCallback: {\
int	i,j,out_sys;\
int	*pos_list,pos_cnt;\
int	pos_first_bk,pos_last_bk,pos_sel_last;\
char    *descr_str;\
char	comando[256],stat_first_bk[20];\
float	time_start_sess,time_end_sess;\
\
   if(XmListGetSelectedPos(scrolledListSess,&pos_list,&pos_cnt)==True) {\
      /* Almeno una sessione e' stata selezionata */\
      UxDestroyInterface(UxThisWidget);\
      pos_first_bk=(pos_sess_bktab[(pos_list[0]-1)].position);\
      strcpy(stat_first_bk,(pos_sess_bktab[(pos_list[0]-1)].status));\
      time_start_sess=(bk_sess_head[pos_first_bk-1].tempo)/1000.0;\
      pos_sel_last=pos_list[(pos_cnt-1)];\
      pos_last_bk=(pos_sess_bktab[pos_sel_last].position);\
      if(pos_sel_last<_MAX_BACK_TRACK) {\
         if((pos_sess_bktab[pos_sel_last].position)!=0) {\
            time_end_sess=(bk_sess_head[pos_last_bk-1].tempo)/1000.0;\
         }\
         else {\
            time_end_sess=val.actual.tempo_sim;\
         }      \
      }\
      else {\
         time_end_sess=val.actual.tempo_sim;\
      }\
\
printf("*******************************\n");\
printf("Intervallo di tempo selezionato\n");\
printf("*******************************\n");\
printf("TEMPO INIZIALE (sec) -----> %f\n",time_start_sess);\
printf("TEMPO FINALE (sec)   -----> %f\n",time_end_sess);\
  \
      XtFree(pos_list);\
\
      descr_str=XmTextFieldGetString(textField1);\
      if(createDirSession(descr_str,stat_first_bk)==0) {\
         /* E' stata predisposta la directory che deve contenere i files relativi\
            alla sessione selezionata. Lancio del programma nsession.              */ \
         sprintf(comando,"nsession %f %f 5 %s",time_start_sess,time_end_sess,nome_dir_sess);\
\
printf("*********************************\n");\
printf("Comando per il lancio di nsession\n");\
printf("*********************************\n");\
printf("\t%s\n",comando);\
\
         out_sys=system(comando);\
         if(out_sys==-1) {\
            perror("esecuzione di: nsession");\
         }\
      }\
      liberaAllocDinam();\
   }\
   else {\
      /* Nessuna sessione e' stata selezionata */\
      create_attenzioneDialog(archiveSess,"No selection!!!",XmDIALOG_MESSAGE);\
   }\
\
}
*pushButOk.defaultButtonShadowThickness: 0

*pushButCanc.class: pushButton
*pushButCanc.static: true
*pushButCanc.name: pushButCanc
*pushButCanc.parent: archiveSess
*pushButCanc.isCompound: "true"
*pushButCanc.compoundIcon: "push.xpm"
*pushButCanc.compoundName: "push_Button"
*pushButCanc.x: 210
*pushButCanc.y: 500
*pushButCanc.width: 120
*pushButCanc.height: 35
*pushButCanc.labelString: "Cancel"
*pushButCanc.leftAttachment: "attach_widget"
*pushButCanc.leftOffset: 60
*pushButCanc.leftWidget: "pushButOk"
*pushButCanc.topAttachment: "attach_widget"
*pushButCanc.topOffset: 10
*pushButCanc.topWidget: "separOkCanc"
*pushButCanc.activateCallback: {\
   liberaAllocDinam();\
   UxDestroyInterface(UxThisWidget);\
}

