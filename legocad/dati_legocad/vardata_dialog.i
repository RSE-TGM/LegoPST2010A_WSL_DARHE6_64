! UIMX ascii 2.0 key: 559                                                       

*vardata_dialog.class: formDialog
*vardata_dialog.parent: NO_PARENT
*vardata_dialog.defaultShell: topLevelShell
*vardata_dialog.static: true
*vardata_dialog.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo vardata_dialog.i\
   tipo \
   release 2.21\
   data 11/3/95\
   reserved @(#)vardata_dialog.i	2.21\
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
#include <malloc.h>\
#include <string.h>\
#include <memory.h>\
#include <ctype.h>\
#include <Xm/MenuShell.h>\
#include <Xm/BulletinB.h>\
#include "f14.h"\
#include "f03.h"\
#include "uni_mis.h"\
#include "dati.h"\
extern Boolean glob_modified;\
extern int n_editors;\
extern S_UNI_MIS uni_mis[];\
extern VAL_VAR *valout;\
extern VAL_VAR *valinp;\
extern DATO_RIGA *array_dati;\
extern HEADER_DATI *header_dati;\
extern DATO_DESCR *array_descr;\
extern int num_note;\
#define TIPO_INP 1 /* variabile di ingresso per il modello */\
#define TIPO_OUT 0 /* variabile di uscita per il modello */\
#define TIPO_INPBLO 2 /* variabile in ingresso per il blocco */\
#define TIPO_OUTBLO 3 /* variabile in uscita per il blocco */\
#define TIPO_DOPPIA -1 /* variabile annullata dalla lista perche'\
                          gia' presente */\
\
/*\
 definizione tipo di riga nella lista parametri\
*/\
#define TIPO_RIGA_DESCR 0\
#define TIPO_RIGA_PARAM 1\
#define TIPO_RIGA_INTESTA 2\
/*\
 struttura per editing dei valori delle variabili\
*/\
typedef struct riga_edi{\
			int tipo; /* indica se di input o di output al modello */\
			int punt; /* indica la posizione in valinp o valout */\
			int io_blo; /* indica se ingresso o uscita dal blocco */\
			char etichetta[120];\
			char valore_str[120];\
			int num_options;\
			int num_opt_sel;\
			int nota;\
			char opzione[N_TIPI_UMIS][L_NOMI_UMIS];\
			swidget sw_opt; /* option menu */\
			swidget sw_val; /* testo per inserim.valore */\
			swidget sw_nn;  /* toggle button per noto/non noto */\
			} RIGA_EDI;\
/*\
 strutture per editing dei dati (parametri) associati ai blocchi\
*/\
typedef struct param {\
			char descr_str[9];\
			char valore_str[11];\
			swidget sw_val;\
			int punt; /* posizione nell'array dei dati */\
			} PARAM;\
\
typedef union u_param{\
			char descr_str[L_RIGA_F14];\
			PARAM par[3];\
			} U_PARAM;\
\
typedef struct riga_param {\
			int tipo_riga;\
			U_PARAM u;\
			} RIGA_PARAM;\
/*\
 lista per editing dei valori da assegnare alle variabili\
*/\
#ifdef ORIGINALE\
typedef struct edit_list{\
		int num_righe;\
		int last_selected;\
		RIGA_EDI *riga;\
		} EDIT_LIST;\
/*\
 lista per editing dei dati (parametri)\
*/\
typedef struct param_list{\
		int num_righe;\
		int last_selected;\
		RIGA_PARAM *riga;\
		} PARAM_LIST;\
#else\
typedef struct edit_list{\
		int num_righe;\
		int last_selected;\
		RIGA_EDI riga[1000];\
		} EDIT_LIST;\
/*\
 lista per editing dei dati (parametri)\
*/\
typedef struct param_list{\
		int num_righe;\
		int last_selected;\
		RIGA_PARAM riga[1000];\
		} PARAM_LIST;\
#endif\
\
/*\
 union utilizzata per l'individuazione nella opt_callback\
 del bottone di opzione selezionato\
*/\
typedef union riga_opt{\
		char c[2];\
		int i;\
		}RIGA_OPT;\
void opt_callback();\
void mod_callback();
*vardata_dialog.ispecdecl: Widget sw_top; /* lista di livello superiore che contiene la lista\
                  di editing */\
int lista_edit_on;\
int tipo_lista;\
EDIT_LIST lista; /* lista delle variabili */\
PARAM_LIST lparam; /* lista dei parametri */\
Boolean modified;
*vardata_dialog.ispeclist: sw_top, lista_edit_on, tipo_lista, lista, lparam, modified
*vardata_dialog.ispeclist.sw_top: "Widget", "%sw_top%"
*vardata_dialog.ispeclist.lista_edit_on: "int", "%lista_edit_on%"
*vardata_dialog.ispeclist.tipo_lista: "int", "%tipo_lista%"
*vardata_dialog.ispeclist.lista: "EDIT_LIST", "%lista%"
*vardata_dialog.ispeclist.lparam: "PARAM_LIST", "%lparam%"
*vardata_dialog.ispeclist.modified: "Boolean", "%modified%"
*vardata_dialog.funcdecl: swidget popup_vardata(tipolista)\
int tipolista; /* tipo di lista desiderata */
*vardata_dialog.funcname: popup_vardata
*vardata_dialog.funcdef: "swidget", "<popup_vardata>(%)"
*vardata_dialog.argdecl: int tipolista;
*vardata_dialog.arglist: tipolista
*vardata_dialog.arglist.tipolista: "int", "%tipolista%"
*vardata_dialog.icode: swidget sw_sel; /* bottone dell'option menu che\
		   definisce il tipo di lista desiderato */
*vardata_dialog.fcode: modified=False; /* setta il Boolean che indica se sono state\
                   effettuate modifiche */\
tipo_lista=tipolista;\
switch(tipo_lista)\
	{\
	case ALL_VAR:\
		sw_sel=valori_Variables;\
		break;\
	case INP_VAR:\
		sw_sel=valori_Inp_Var;\
		break;\
	case OUT_VAR:\
		sw_sel=valori_Out_Var;\
		break;\
	case ALL_DATA:\
		sw_sel=valori_Data;\
		break;\
	}\
set_something(UxGetWidget(menu_valori),\
                       XmNmenuHistory,\
                       UxGetWidget(sw_sel));\
\
lista_edit_on=False;\
#ifdef ORIGINALE\
lista.riga=NULL;\
#endif\
lista.num_righe=0;\
aggiorna_all_lists();\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*vardata_dialog.auxdecl: /* is_not_blank \
*/\
\
int is_not_blank(char *str)\
{\
   int i,len,appo,ret;\
\
   len = strlen(str);\
\
   ret = False;\
   \
   for(i=0;i<len;i++)\
   {\
      if(str[i] == ' ')\
         appo = False;\
      else\
         appo = True;\
   \
      ret |= appo;\
   }\
\
   return(ret);\
}\
\
/*\
 aggiorna_all_lists\
	aggiorna la lista dei blocchi selezionati e la lista delle\
        variabili in editing in base ai blocchi in selezione \
        nella main window .\
*/\
extern int tot_descr; /* numero totale di descrizioni inframmezzate all'area\
                         dati: viene settato della routine di libreria\
                         read_file_f14 */\
aggiorna_all_lists()\
{\
int i;\
extern swidget listaBlocchi;\
char *sel_items;\
int nitems; /* numero di blocchi selezionati nella main window */\
int nitems_sel; /* numero di blocchi nella lista di blocchi selezionati */\
if(lista_edit_on)\
	{\
	UxDestroySwidget(sw_top);\
	lista_edit_on=False;\
	}\
nitems=UxGetSelectedItemCount(listaBlocchi);\
/* \
 se vi sono blocchi selezionati procede all'aggiornamento delle\
 liste\
*/\
if(nitems)\
	{\
	sel_items=UxGetSelectedItems(listaBlocchi);\
/*\
  Aggiorna la lista dei blocchi selezionati\
*/\
/*\
 Se si e' in modalita' replace list cancella la lista attuale dei\
 blocchi selezionati \
*/\
	nitems_sel=nitems;\
	XmListDeleteAllItems(UxGetWidget(listaBlocchiSel));\
	for(i=0;i<nitems;i++)\
		{\
		aggiungi_item_n(listaBlocchiSel,&sel_items[80*i+i],80);\
		}\
/*\
 Aggiorna la lista delle variabili appartenenti ai blocchi\
*/\
\
	aggiorna_lista_var(sel_items,nitems,80);\
	lista_edit_on=True;\
	create_edit(vardata_rc);\
	}\
}\
\
\
/*\
 create_edit\
 creazione grafica della lista per l'editing dei valori delle\
 variabili o dei valori dei parametri\
*/ \
create_edit(parent)\
swidget parent;\
{\
/*\
 creazione di un row_column che conterra' l'intera lista\
*/\
\
sw_top =  XtVaCreateManagedWidget ("top_rowcol",\
                xmBulletinBoardWidgetClass, parent,\
                XmNmarginHeight,0,\
		XmNmarginWidth,0,\
                XmNmarginTop,0,\
                XmNmarginBottom,0,\
                NULL);\
/*\
 Esamina se deve essere visualizzata la lista dei parametri\
 o una delle liste relative alle variabili\
*/\
if(tipo_lista == ALL_DATA)\
	create_edit_param();\
else\
	create_edit_var();\
}\
\
/*\
 create_edit_var\
 creazione lista di editing per le variabili\
*/\
create_edit_var()\
{\
RIGA_OPT r_opt;\
int	i,j;\
int 	tipovar_ok; /* tipo di variabile da accettarsi in\
		       visualizzazione in base al tipo\
                       di lista richiesta */\
int num_selezio;\
swidget menuvar_p1_shell;\
swidget sw,sw1;\
swidget sw_riga;\
swidget menu1; /* option menu */\
swidget menu1_p1; /* pulldown associato all'option menu */\
swidget sw_push[N_TIPI_UMIS]; /* push button dell'option menu */\
int altezza; /* altezza di una riga */\
int posiz;\
/*\
 in base al tipo di lista richiesta stabilisce quali sono\
 le variabili accettabili\
*/	\
if(tipo_lista== INP_VAR)\
	tipovar_ok=TIPO_INPBLO;\
else if (tipo_lista== OUT_VAR)\
	tipovar_ok=TIPO_OUTBLO;\
/*\
 crea le righe componenti l'intera lista\
*/\
altezza=30;\
posiz=0;\
for (i=0; i<lista.num_righe; i++)\
	{\
	if(lista.riga[i].io_blo!=TIPO_DOPPIA)\
		{\
/*\
 se e' stata richiesta una lista specifica effettua la creazione\
 della riga solo per le variabili di tipo accettabile\
*/\
		if(tipo_lista!=ALL_VAR)\
			{\
		  	if(lista.riga[i].io_blo!=tipovar_ok)\
				continue;\
			}\
/*\
 crea un row_column per ogni riga\
*/\
		\
		sw_riga=UxCreateRowColumn("r_rowcol",sw_top);\
		UxPutPacking(sw_riga,"pack_tight");\
		UxPutOrientation(sw_riga,"horizontal");\
		UxPutNumColumns(sw_riga,1);\
		UxPutY(sw_riga, posiz*altezza);\
		posiz++;\
		UxCreateWidget(sw_riga);\
/*\
 crea il toggle button per la selezione noto/ non noto\
*/\
		\
		sw = UxCreateToggleButton("togg", sw_riga);\
		UxPutLabelString(sw,"");\
		UxPutSelectColor(sw,"red");\
		UxPutIndicatorSize(sw,10);\
		UxPutMarginHeight(sw,0);\
		UxPutHighlightThickness(sw,1);\
		UxPutShadowThickness(sw,0);\
		UxPutSpacing(sw,0);\
		lista.riga[i].sw_nn=sw;\
		if(lista.riga[i].nota)\
			UxPutSet(sw,"true");\
		else\
			UxPutSet(sw,"false");\
#ifndef DESIGN_TIME\
		UxPutContext(sw, (char *)UxVardata_dialogContext );\
#endif\
\
		UxAddCallback(sw,XmNvalueChangedCallback,mod_callback,NULL);\
		UxCreateWidget(sw);	\
/*\
 crea il widget Text per l'input del valore da assegnare alla\
 variabile\
*/	\
		\
		sw = UxCreateText("text", sw_riga);\
		UxPutHeight(sw,20);\
		UxPutMarginHeight(sw,1);\
		UxPutColumns(sw,10);\
		UxPutMaxLength(sw,10);\
		if(lista.riga[i].valore_str)\
                   if( is_not_blank( lista.riga[i].valore_str ) )\
			UxPutText(sw,lista.riga[i].valore_str);\
#ifndef DESIGN_TIME\
		UxPutContext(sw, (char *)UxVardata_dialogContext );\
#endif\
\
		UxAddCallback(sw,XmNvalueChangedCallback,mod_callback,NULL);\
		UxCreateWidget(sw);\
		lista.riga[i].sw_val=sw;\
/*\
 crea l'option menu per la selezione della unita' di misura\
*/\
/*\
 1. Creazione della shell per il pulldown menu\
*/\
		menuvar_p1_shell = XtVaCreatePopupShell ("menuvar_p1_shell",\
                        xmMenuShellWidgetClass, sw_riga,\
                        XmNwidth, 1,\
                        XmNheight, 1,\
                        XmNallowShellResize, TRUE,\
                        XmNoverrideRedirect, TRUE,\
                        NULL );\
/*\
 2. Creazione del pulldown menu (menu pane)\
*/\
\
		menu1_p1 =  XtVaCreateWidget ("rcb",\
        		xmRowColumnWidgetClass, menuvar_p1_shell,\
        		XmNmarginHeight,0,\
        		XmNrowColumnType, XmMENU_PULLDOWN,\
        		NULL);\
\
		\
/*\
 Creazione dei bottoni degli option menu\
*/\
		for(j=0;j<lista.riga[i].num_options;j++)\
			{\
			sw_push[j]=UxCreatePushButton("opt",menu1_p1);\
\
			UxPutLabelString(sw_push[j],lista.riga[i].opzione[j]);\
			UxPutRecomputeSize(sw_push[j],"false");\
			UxPutWidth(sw_push[j],60);\
			UxPutMarginHeight(sw_push[j],0);\
\
			r_opt.c[0]=(char)i;\
			r_opt.c[1]=(char)j;\
#ifndef DESIGN_TIME\
			UxPutContext(sw_push[j], (char *)UxVardata_dialogContext );\
#endif\
\
			UxAddCallback(sw_push[j],XmNactivateCallback,opt_callback,r_opt.i);\
			UxCreateWidget(sw_push[j]);\
			}\
\
		\
		\
		num_selezio=lista.riga[i].num_opt_sel;\
		menu1= XtVaCreateManagedWidget( "menuvar_valori",\
                        xmRowColumnWidgetClass, sw_riga,\
			XmNmarginHeight,0,\
                        XmNsubMenuId, menu1_p1,\
                        XmNrowColumnType, XmMENU_OPTION,\
			XmNmenuHistory,sw_push[num_selezio],\
                        NULL );\
\
\
		lista.riga[i].sw_opt=menu1;\
\
\
/*\
 crea la label contenente nome e descrizione della variabile\
*/			\
	\
		sw = UxCreateLabelGadget("label", sw_riga);\
		UxPutLabelString(sw, lista.riga[i].etichetta);\
		UxPutMarginHeight(sw,0);\
		UxPutMarginTop(sw,0);\
		UxPutMarginBottom(sw,0);\
		UxCreateWidget(sw);\
		}\
				\
	}\
}\
\
/*\
 create_edit_param\
 creazione lista di editing parametri\
*/\
create_edit_param()\
{\
int i,k;\
swidget sw_riga;\
swidget sw;\
char s[128];\
int altezza=30;\
/*\
 crea le righe componenti l'intera lista\
*/\
for (i=0; i<lparam.num_righe; i++)\
	{\
/*\
 crea un row_column per ogni riga\
*/\
	sprintf(s,"r_rowcol%d",i);\
	sw_riga=UxCreateRowColumn(s,sw_top);\
	UxPutPacking(sw_riga,"pack_tight");\
	UxPutOrientation(sw_riga,"horizontal");\
	UxPutNumColumns(sw_riga,1);\
	UxPutMarginHeight(sw_riga,0);\
	UxPutY(sw_riga , altezza*i);\
	UxCreateWidget(sw_riga);\
\
	if(lparam.riga[i].tipo_riga==TIPO_RIGA_DESCR)\
		{\
		sprintf(s, "label%d", i);\
		sw = UxCreateLabelGadget(s, sw_riga);\
		UxPutLabelString(sw, lparam.riga[i].u.descr_str);\
		UxPutMarginHeight(sw,2);\
		UxPutMarginTop(sw,2);\
		UxPutMarginBottom(sw,2);\
		UxPutForeground(sw_riga,"#0000ff");\
		UxCreateWidget(sw);\
		}\
	else if (lparam.riga[i].tipo_riga==TIPO_RIGA_INTESTA)\
		{\
		sprintf(s, "titolo%d", i);\
		sw = UxCreateLabelGadget(s, sw_riga);\
		UxPutLabelString(sw, lparam.riga[i].u.descr_str);\
		UxPutMarginHeight(sw,2);\
		UxPutMarginTop(sw,2);\
		UxPutMarginBottom(sw,2);\
		UxPutForeground(sw_riga,"#ff0000");\
		UxCreateWidget(sw);\
		}\
	else\
		{\
		UxPutPacking(sw_riga,"pack_column");\
		UxPutEntryAlignment(sw_riga,"alignment_end");\
		for(k=0;k<3;k++)\
			{\
			if(lparam.riga[i].u.par[k].descr_str[0]==0)\
				continue;\
			sprintf(s, "label%d%d", i,k);\
			sw = UxCreateLabelGadget(s, sw_riga);\
			UxPutLabelString(sw, lparam.riga[i].u.par[k].descr_str);\
			UxPutMarginHeight(sw,0);\
			UxPutMarginTop(sw,0);\
			UxPutMarginBottom(sw,0);\
			UxCreateWidget(sw);\
/*\
 crea il widget Text per l'input del valore da assegnare al\
 parametro\
*/	\
			sprintf(s, "text%d%d", i,k);\
			sw = UxCreateText(s, sw_riga);\
			UxPutHeight(sw,15);\
			UxPutMaxLength(sw,10);\
			UxPutColumns(sw,10);\
			UxPutMarginHeight(sw,0);\
			UxPutMarginTop(sw,0);\
			UxPutMarginBottom(sw,0);\
\
			if(lparam.riga[i].u.par[k].valore_str)\
                           if( is_not_blank( lparam.riga[i].u.par[k].valore_str) )\
				UxPutText(sw,lparam.riga[i].u.par[k].valore_str);\
#ifndef DESIGN_TIME\
			UxPutContext(sw, (char *)UxVardata_dialogContext );\
#endif\
\
			UxAddCallback(sw,XmNvalueChangedCallback,mod_callback,NULL);\
\
			UxCreateWidget(sw);\
			lparam.riga[i].u.par[k].sw_val=sw;\
			}\
		}\
	}		\
}\
\
/*\
 recreate_edit()\
	distrugge e ricrea la lista di editing\
*/\
recreate_edit()\
{\
/*\
 cancella la lista attuale\
*/\
XtDestroyWidget(sw_top);\
/*\
 crea la nuova lista \
*/\
create_edit(vardata_rc);\
}\
\
\
/*\
aggiorna_lista_var\
	in base ai blocchi selezionati visualizza le informazioni relative\
	alle variabili\
*/\
aggiorna_lista_var(blocchi,nblocchi,lun_nome)\
char *blocchi;\
int nblocchi;\
int lun_nome;\
{\
int i;\
int j,k;\
int ind_blo;\
int ind_descr; /* indice nell'array delle descrizioni\
                  dei parametri del blocco */\
int ind_riga_dato;  /* indice nell'array dei parametri */\
int num_descr;\
int cont;\
int inizio_ingressi;\
int num_riga,tot_righe;\
int num_riga_param,tot_righe_param;\
int *array_blo; /* contiene gli indici di tutti i blocchi */\
\
num_riga=0;\
num_riga_param=0;\
tot_righe=0;\
tot_righe_param=0;\
/*\
 se necessario libera la memoria allocata per la struttura\
 lista di editing\
*/\
free_righe_edit();\
/*\
 esamina ogni blocco selezionato\
*/\
array_blo= (int *)XtMalloc(nblocchi*sizeof(int));\
if(array_blo==NULL)\
	{\
	printf("\n malloc non riuscita ");\
	return(0);\
	}\
/*\
 calcola il numero totale di righe necessario per l'editing\
 delle variabili (tot_righe) ed il numero totale di righe \
 necessario per l'editing dei parametri\
*/\
for(i=0;i<nblocchi;i++)\
	{\
/*\
 ricerca in base al nome la posizione del blocco nella lista dei\
 blocchi del modello\
*/\
	array_blo[i]=cerca_blocco(&blocchi[i*lun_nome+i],lun_nome);\
	if(array_blo[i]==-1) \
		{\
		printf("\n blocco non trovato");\
		free(array_blo);\
		return(0);\
		}\
	tot_righe+=(ip[array_blo[i]+1]-ip[array_blo[i]]);\
/*\
 calcola il numero di righe per la lista dei parametri\
*/\
	tot_righe_param+=(header_dati[array_blo[i]].num_righe_dati +\
                          header_dati[array_blo[i]].num_descr+1);\
	}\
/*\
  alloca lo spazio necessario per la struttura delle righe da\
  editare\
*/\
alloca_righe_edit(tot_righe,tot_righe_param);\
\
for(i=0;i<nblocchi;i++)\
	{\
	ind_blo=array_blo[i];\
/*\
 individua la posizione nelle liste delle variabili delle descrizioni\
 delle variabili stesse\
*/\
	inizio_ingressi=nusta[ind_blo]+nusci[ind_blo];\
	cont=0;\
	for(j=ip[ind_blo]-1;j<(ip[ind_blo+1]-1);j++)\
		{\
/*\
 riempie la riga di editing in base alle informazioni relative\
 alla variabile\
*/\
		if(cont >= inizio_ingressi)\
			fill_riga_edi(j,num_riga,TIPO_INPBLO);\
		else\
			fill_riga_edi(j,num_riga,TIPO_OUTBLO);\
		cont++;  \
		num_riga++;\
		}\
/*\
 riempie le righe per l'editing dei parametri\
*/\
	ind_descr=header_dati[ind_blo].inizio_descr;\
	ind_riga_dato=header_dati[ind_blo].inizio;\
	num_descr=header_dati[ind_blo].num_descr;\
/*\
 copia il titolo relativo al blocco\
*/\
	strcpy(lparam.riga[num_riga_param].u.descr_str,\
                &header_dati[ind_blo].titolo[strlen(HEADER_BLOCCO_F14)]);	  \
	lparam.riga[num_riga_param].tipo_riga=TIPO_RIGA_INTESTA;\
	num_riga_param++;\
\
	for(j=0;j<header_dati[ind_blo].num_righe_dati;j++)\
		{\
		if(num_descr)\
		   while(array_descr[ind_descr].dato_seguente==ind_riga_dato &&\
                        ind_descr < tot_descr )\
                	{\
			lparam.riga[num_riga_param].tipo_riga=TIPO_RIGA_DESCR;\
			strcpy(lparam.riga[num_riga_param].u.descr_str,\
				&array_descr[ind_descr].descr[strlen(DESCRIZIONE_IN_DATI)]);\
                        ind_descr++;\
			num_riga_param++;\
                        }\
                \
                for(k=0;k<array_dati[ind_riga_dato].num_dati;k++)\
			{\
			sprintf(lparam.riga[num_riga_param].u.par[k].descr_str,\
				"%s",\
				array_dati[ind_riga_dato].dato[k].descr);\
			str_cut(lparam.riga[num_riga_param].u.par[k].descr_str);\
			strncpy(lparam.riga[num_riga_param].u.par[k].valore_str,\
				  array_dati[ind_riga_dato].dato[k].val,10);\
			lparam.riga[num_riga_param].u.par[k].valore_str[10]=0;\
			app_n_blank(lparam.riga[num_riga_param].u.par[k].valore_str,10);\
			lparam.riga[num_riga_param].u.par[k].punt=ind_riga_dato;\
                        }\
                if(array_dati[ind_riga_dato].num_dati)\
			{\
			lparam.riga[num_riga_param].tipo_riga=TIPO_RIGA_PARAM;\
			num_riga_param++;\
                        ind_riga_dato++;\
			}\
		}\
/*\
 potrebbero esserci ancora delle descrizioni da riportare\
*/\
        while(ind_descr < num_descr)\
                {\
                lparam.riga[num_riga_param].tipo_riga=TIPO_RIGA_DESCR;\
                strcpy(lparam.riga[num_riga_param].u.descr_str,\
                &array_descr[ind_descr].descr[strlen(DESCRIZIONE_IN_DATI)]);\
                ind_descr++;\
                num_riga_param++;\
                }\
	}\
/*\
 esamina le righe di editing per vedere se vi sono righe\
 doppie; in tal caso modifica il tipo delle righe duplicate\
 in TIPO_DOPPIO\
*/\
filtra_righe_edit();\
free(array_blo);\
}\
\
/*\
 alloca_righe_edit\
*/\
alloca_righe_edit(num_righe,num_righe_param)\
int num_righe;\
int num_righe_param;\
{\
lista.last_selected= -1;\
lista.num_righe=num_righe;\
#ifdef ORIGINALE\
lista.riga=(RIGA_EDI *)calloc(lista.num_righe,sizeof(RIGA_EDI));\
#else\
memset(lista.riga,0,lista.num_righe*sizeof(RIGA_EDI));\
#endif\
lparam.last_selected= -1;\
lparam.num_righe=num_righe_param;\
#ifdef ORIGINALE\
lparam.riga=(RIGA_PARAM *)calloc(lparam.num_righe,sizeof(RIGA_PARAM));\
#else\
memset(lparam.riga,0,lparam.num_righe*sizeof(RIGA_PARAM));\
#endif\
}\
\
/*\
free_righe_edit\
*/\
free_righe_edit()\
{\
\
#ifdef ORIGINALE\
if(lista.riga)\
	free(lista.riga);\
lista.riga=NULL;\
#endif\
lista.num_righe=0;\
\
#ifdef ORIGINALE\
if(lparam.riga)\
	free(lparam.riga);\
lparam.riga=NULL;\
#endif\
lparam.num_righe=0;\
\
}\
\
/*\
 filtra_righe_edit()\
	esamina le righe di editing per vedere se vi sono righe\
 	doppie; in tal caso modifica il tipo delle righe duplicate\
 	in TIPO_DOPPIO\
*/\
filtra_righe_edit()\
{\
int i,j;\
for(i=0;i<lista.num_righe;i++)\
	{\
	for(j=0;j<lista.num_righe;j++)\
		{\
		if(j==i) continue;\
		if(lista.riga[i].io_blo==TIPO_DOPPIA) continue;\
		if(lista.riga[i].tipo==lista.riga[j].tipo &&\
		   lista.riga[i].punt==lista.riga[j].punt)\
			{\
/* \
 le due righe sono uguali viene eliminata con precedenza la riga \
 descrivente un ingresso.\
*/\
			if(lista.riga[j].io_blo==TIPO_INPBLO &&\
                           lista.riga[i].io_blo==TIPO_OUTBLO) \
				{\
				lista.riga[j].io_blo=TIPO_DOPPIA;\
				}\
			else if(lista.riga[j].io_blo==TIPO_OUTBLO &&\
                                lista.riga[i].io_blo==TIPO_INPBLO) \
				{\
				lista.riga[i].io_blo=TIPO_DOPPIA;\
				}\
			}\
		}\
	}\
}\
                           \
		\
/*\
 cerca_blocco\
*/\
int cerca_blocco(nome,lun_nome)\
char *nome;\
int lun_nome;\
{\
int i;\
for(i=0;i<nbl;i++)\
	{\
	if(memcmp(nome,nom_bloc[i],lun_nome)==0)\
		return(i);\
	}\
return(-1);\
}\
\
/*\
 fill_riga_edi\
*/\
fill_riga_edi(pos_var,num_riga,io_blo)\
int pos_var;\
int num_riga;\
int io_blo;  /* indica se in ingresso o uscita da un blocco */\
{\
int j,i;\
int ind_var; /* indice della variabile nei vettori nomsivar,nomvari, \
                valinp e valout */\
VAL_VAR *p_var;\
if(ipvrs[pos_var]>0)\
	{\
	ind_var=ipvrs[pos_var]-1;\
	sprintf(lista.riga[num_riga].etichetta,"%.100s",nom_sivar[ind_var]);\
	p_var= &valout[ind_var];\
	lista.riga[num_riga].tipo=TIPO_OUT;\
	}\
else\
	{\
	ind_var= -(ipvrs[pos_var])-1;\
	sprintf(lista.riga[num_riga].etichetta,"%.100s",nom_vari[ind_var]);\
	p_var= &valinp[ind_var];\
	lista.riga[num_riga].tipo=TIPO_INP;\
	}\
lista.riga[num_riga].io_blo=io_blo;\
lista.riga[num_riga].punt=ind_var;\
spr_float(lista.riga[num_riga].valore_str,p_var->val);\
lista.riga[num_riga].num_options=0;\
for(i=0;i<N_TIPI_UMIS;i++)\
	{\
	if(strcmp(uni_mis[p_var->ind_umis].codm[i],"      "))\
		{\
		strcpy(lista.riga[num_riga].opzione[i],\
			uni_mis[p_var->ind_umis].codm[i]);\
		lista.riga[num_riga].num_options++;\
		}\
	}\
if(strcmp(uni_mis[p_var->ind_umis].codm[0],"---")==0)\
	lista.riga[num_riga].num_options=1;\
\
lista.riga[num_riga].num_opt_sel=p_var->sel_umis;\
lista.riga[num_riga].nota=p_var->noto;\
}\
\
/* verifica dato\
   controlla che l'input il dato introdotto sia compreso nei caratteri printabili\
*/\
\
int verifica_dato(char *str)\
{\
  int i,ok;\
\
   ok = 1;\
   for(i=0;i<strlen(str);i++)\
      if(!isprint((int)str[i]))\
      {\
        ok = 0;\
        break;\
      }\
\
   return(ok);\
}\
\
\
/*\
 salva_variazioni\
	salva le variazioni effettuate nella lista di editing\
*/\
salva_variazioni()\
{\
int i,k;\
int ind_riga_dato; /* posizione nell'array dei dati */\
int tipovar_ok;\
VAL_VAR *p_var;\
Widget w_button;\
char *str;\
float save_val;\
int iret;\
char appoggio[200];\
int app;\
extern swidget create_vis_msg();\
/*\
 E' in editing la lista relativa ai parametri\
*/\
if(tipo_lista==ALL_DATA)\
	{\
	for(i=0;i<lparam.num_righe;i++)\
		{\
		if(lparam.riga[i].tipo_riga==\
			TIPO_RIGA_PARAM)\
			{\
			ind_riga_dato=lparam.riga[i].u.par[0].punt;\
			for(k=0;k< array_dati[ind_riga_dato].num_dati;k++)\
				{\
				str=UxGetText(lparam.riga[i].u.par[k].sw_val);\
                                strcpy(appoggio,str);\
				app_n_blank(appoggio,10);\
				appoggio[10]=0;\
                                if( verifica_dato(appoggio) )\
                                   {\
				   strcpy(array_dati[ind_riga_dato].dato[k].val,\
                                        appoggio);	\
				   strcpy(lparam.riga[i].u.par[k].valore_str,appoggio);\
                                   }\
                                else\
          		           {\
		                   sprintf(appoggio,\
			                  "Invalid input field in line %d data %8.8s.\n It was substituted with previous value",\
        		                   i+1,lparam.riga[i].u.par[k].descr_str);\
		                   create_vis_msg(appoggio);\
		           \
		                   UxPutText(lista.riga[i].sw_val,lparam.riga[i].u.par[k].valore_str);\
		                   }\
				}\
			}\
		}\
	}\
/*\
 E' in editing una lista relativa alle variabili\
*/\
else \
{\
for(i=0;i<lista.num_righe;i++)\
	{\
	if(tipo_lista== INP_VAR)\
		tipovar_ok=TIPO_INPBLO;\
	else if (tipo_lista== OUT_VAR)\
		tipovar_ok=TIPO_OUTBLO;\
\
	if(lista.riga[i].io_blo==TIPO_DOPPIA) continue;\
	if(tipo_lista!=ALL_VAR)\
			{\
		  	if(lista.riga[i].io_blo!=tipovar_ok)\
				continue;\
			}\
	if(lista.riga[i].tipo==TIPO_OUT)\
		p_var= &valout[lista.riga[i].punt];\
	else\
		p_var= &valinp[lista.riga[i].punt];\
/*\
 Ricava il valore della variabile nell'unita' di misura\
 correntemente selezionata\
*/\
	str=UxGetText(lista.riga[i].sw_val);\
	save_val=p_var->val;\
	iret=sscanf(str,"%f%s",&(p_var->val),appoggio);\
	if(iret!=1)\
		{\
		sprintf(appoggio,\
			"Invalid input field in line %d variable %8.8s.\n It was substituted with previous value",\
        		i+1,lista.riga[i].etichetta);\
		create_vis_msg(appoggio);\
		p_var->val=save_val;\
		UxPutText(lista.riga[i].sw_val,lista.riga[i].valore_str);\
		}\
	else\
		strcpy(lista.riga[i].valore_str,str);\
	str=UxGetSet(lista.riga[i].sw_nn);\
/*\
 ritorna 'true' o 'false' in forma di stringhe; quindi e' sufficiente\
 testare la prima lettera.\
*/\
	if(str[0]=='t' && p_var->noto==0)\
		{\
		lista.riga[i].nota=1;\
		p_var->noto=1;\
		num_note++;\
		}\
	else if (str[0]=='f' && p_var->noto==1)\
		{\
		lista.riga[i].nota=0;\
		p_var->noto=0;\
		num_note--;\
		}\
	p_var->sel_umis=lista.riga[i].num_opt_sel; \
	}\
}\
}\
\
void mod_callback(w,u_data,data)\
Widget w;\
caddr_t u_data;\
XmAnyCallbackStruct *data;\
{\
#ifndef DESIGN_TIME\
/*\
 Salvataggio e recupero del Context relativo alla window per la quale e'\
 stata richiamata la funzione di callback\
*/\
_UxCvardata_dialog      *UxSaveCtx, *UxContext;\
swidget                 UxThisWidget;\
\
UxThisWidget = UxWidgetToSwidget( w );\
UxSaveCtx = UxVardata_dialogContext;\
UxVardata_dialogContext = UxContext =\
                        (_UxCvardata_dialog *) UxGetContext( UxThisWidget );\
#endif\
modified=True;\
#ifndef DESIGN_TIME\
/*\
 Ripristino del Context precedente alla chiamata della presente\
 callback function\
*/\
UxVardata_dialogContext = UxSaveCtx;\
#endif\
}\
\
\
void opt_callback(w,opt,data)\
Widget w;\
RIGA_OPT opt;\
XmAnyCallbackStruct *data;\
{\
float value,value_def;\
char *str;\
char app[20];\
int umis_sel,umis_sel_old,num_riga,ind_umis;\
VAL_VAR *p_var; /* puntatore alla variabile corrente */\
#ifndef DESIGN_TIME\
/*\
 Salvataggio e recupero del Context relativo alla window per la quale e'\
 stata richiamata la funzione di callback\
*/\
_UxCvardata_dialog      *UxSaveCtx, *UxContext;\
swidget                 UxThisWidget;\
\
UxThisWidget = UxWidgetToSwidget( w );\
UxSaveCtx = UxVardata_dialogContext;\
UxVardata_dialogContext = UxContext =\
                        (_UxCvardata_dialog *) UxGetContext( UxThisWidget );\
#endif\
/*\
 se e' cambiata l'unita' di misura selezionata\
*/\
num_riga=opt.c[0];\
umis_sel=opt.c[1];\
\
if(umis_sel!=lista.riga[num_riga].num_opt_sel)\
	{\
	if(lista.riga[num_riga].tipo==TIPO_OUT)\
		p_var= &valout[lista.riga[num_riga].punt];\
	else\
		p_var= &valinp[lista.riga[num_riga].punt];\
	umis_sel_old=lista.riga[num_riga].num_opt_sel;\
	lista.riga[num_riga].num_opt_sel=umis_sel;\
	sscanf(UxGetText(lista.riga[num_riga].sw_val),"%f",&value);\
/*\
 trasforma il valore nell'unita' di misura di default\
*/\
	ind_umis=p_var->ind_umis;\
	value_def=(value-uni_mis[ind_umis].B[umis_sel_old])\
                  /uni_mis[ind_umis].A[umis_sel_old];\
/*\
 trasforma il valore nella nuova unita' di misura\
*/\
	value=value_def*uni_mis[ind_umis].A[umis_sel]+\
		uni_mis[ind_umis].B[umis_sel];\
	spr_float(app,value);	\
	UxPutText(lista.riga[num_riga].sw_val,app);\
	}\
#ifndef DESIGN_TIME\
/*\
 Ripristino del Context precedente alla chiamata della presente\
 callback function\
*/\
UxVardata_dialogContext = UxSaveCtx;\
#endif\
}\
/*\
 scrolla_lista \
	effettua lo scrolling della lista di editing a seguito di una\
 	operazione di find\
*/\
scrolla_lista(pos,poslista)\
int pos;\
int poslista;\
{\
Widget w_bar;\
int maximum;\
int pos_slider;\
int dim_slider;\
int free_slider; /* corsa libera per lo slider */\
float delta; /* spostamento da dare allo slider corrispondente\
              alle righe da scrollare */\
XEvent event;\
XmScrollBarCallbackStruct call_data;\
call_data.reason=XmCR_VALUE_CHANGED;\
call_data.event=&event;\
\
\
if(lista_edit_on)\
	{\
/*\
	elimina l'evidenziazione sulla riga precedentemente \
	selezionata\
*/\
	elim_selez_lista();\
\
/*\
 Ricava l'indice di widget della scroll bar verticale\
*/\
	get_something(UxGetWidget(vardata_sw),XmNverticalScrollBar,&w_bar);\
/*\
 Ricava dimensione massima e dimensione attuale dello slider\
 della scroll bar per determinare la corsa libera dello slider\
*/\
	get_something(w_bar,XmNmaximum,&maximum);\
	get_something(w_bar,XmNsliderSize,&dim_slider);\
	free_slider=maximum-dim_slider;\
/*\
 determina la frazione rispetto al totale di cui si deve spostare\
 lo slider\
*/\
	if (tipo_lista == ALL_DATA)\
		delta=((float)pos/(float)lparam.num_righe); /* percentuale di incremento */\
	else\
		delta=((float)pos/(float)lista.num_righe);\
/*\
 determina lo spostamento da richiedere allo slider\
*/\
	pos_slider=(delta*maximum);\
	if(pos_slider>free_slider)\
		pos_slider=free_slider;\
/*\
 sposta lo slider seleziona la riga a cui ci si deve posizionare ed\
 esegue la callback relativa allo spostamento effettuato dallo \
 slider\
*/ \
	set_something(w_bar,XmNvalue,pos_slider); \
	call_data.value=pos_slider;\
	set_selez_lista(poslista);\
\
	XtCallCallbacks(w_bar,XmNvalueChangedCallback,&call_data);\
\
	}\
}\
\
elim_selez_lista()\
{\
int poslista;\
if(tipo_lista==ALL_DATA)\
	{\
	if(lparam.last_selected!=-1)\
		{\
		poslista=lparam.last_selected;\
		if(lparam.riga[poslista].tipo_riga==TIPO_RIGA_PARAM)\
			{\
			XmTextSetHighlight(UxGetWidget(lparam.riga[poslista].u.par[0].sw_val),\
				0,strlen(lparam.riga[poslista].u.par[0].valore_str),\
				XmHIGHLIGHT_NORMAL);\
			}\
		}  	\
	}\
else\
	{\
	if(lista.last_selected!=-1)\
		{\
		poslista=lista.last_selected;\
		XmTextSetHighlight(UxGetWidget(lista.riga[poslista].sw_val),\
			0,strlen(lista.riga[poslista].valore_str),XmHIGHLIGHT_NORMAL);\
		}\
	}\
}\
\
set_selez_lista(poslista)\
int poslista;\
{\
if(tipo_lista==ALL_DATA)\
	{\
	if(lparam.riga[poslista].tipo_riga==TIPO_RIGA_PARAM)\
		{\
		XmTextSetHighlight(UxGetWidget(lparam.riga[poslista].u.par[0].sw_val),\
				0,strlen(lparam.riga[poslista].u.par[0].valore_str),\
				XmHIGHLIGHT_SELECTED);\
		}\
	lparam.last_selected=poslista;\
	}\
else\
	{\
	XmTextSetHighlight(UxGetWidget(lista.riga[poslista].sw_val),\
			0,strlen(lista.riga[poslista].valore_str),\
			XmHIGHLIGHT_SELECTED);\
	lista.last_selected=poslista;\
	}\
}\
\
\
\
cerca_in_lista(str,direz,posvis,poslist)\
char *str;\
int direz;\
int *posvis;\
int *poslist;\
{\
int posriga;\
int iret;\
if(tipo_lista==ALL_DATA)\
	{\
	iret=cerca_in_lparam(str,direz,&posriga,poslist);\
	*posvis=*poslist;\
	}\
else\
	iret=cerca_in_lista_edi(str,direz,posvis,poslist);\
return(iret);\
}\
\
\
\
cerca_in_lista_edi(str,direz,posvis,poslist)\
char *str;\
int direz;\
int *posvis;\
int *poslist;\
{\
int i;\
int start,inc;\
int trovato;\
int tipovar_ok;\
\
if(tipo_lista== INP_VAR)\
	tipovar_ok=TIPO_INPBLO;\
else if (tipo_lista== OUT_VAR)\
	tipovar_ok=TIPO_OUTBLO;\
\
if(lista.last_selected!=-1)\
	start=lista.last_selected;\
else \
	start=0;\
trovato=0;\
inc=direz;\
i=next_pos_lista(start,inc);\
\
while(!trovato && i!= start)\
	{\
	if((strstr(lista.riga[i].etichetta,str) ||\
	   strstr(lista.riga[i].valore_str,str)) &&\
		lista.riga[i].io_blo!=TIPO_DOPPIA &&\
	   (lista.riga[i].io_blo==tipovar_ok || tipo_lista == ALL_VAR))\
		trovato=1;\
	else\
		{\
		i=next_pos_lista(i,inc);\
		}\
	}\
if(i==start && !trovato) \
	{\
	*poslist= -1;\
	*posvis= -1;\
	return(-1);\
	}\
else\
	{\
	*poslist=i;\
	*posvis=plista_to_pvis(i);\
	return(*posvis);\
	}\
}\
\
\
/*\
 cerca_in_lparam\
 	ricerca nella lista dei parametri\
*/\
cerca_in_lparam(str,direz,posriga,poslist)\
char *str;\
int direz;\
int *poslist;\
int *posriga; /* posizione all'interno della riga */\
{\
int start,i,j;\
int trovato;\
if(lparam.last_selected!=-1)\
	start=lparam.last_selected;\
else \
	start=0;\
trovato=0;\
i=next_pos_lista(start,direz);\
\
while(!trovato && i!= start)\
	{\
	if(lparam.riga[i].tipo_riga!=TIPO_RIGA_PARAM)\
		{\
		if(strstr(lparam.riga[i].u.descr_str,str))\
			{\
			trovato=1;\
			*poslist=i;\
			*posriga= -1; /* indica che si e' trovata una riga di commento */\
			return(*poslist);\
			}\
		else\
			{\
			\
			i=next_pos_lista(i,direz);\
			}\
		}\
	else\
		{\
		for(j=0;j<3;j++)\
			{\
			if(lparam.riga[i].u.par[j].descr_str[0]!=0 &&\
			   (strstr(lparam.riga[i].u.par[j].valore_str,\
				  str) ||\
			    strstr(lparam.riga[i].u.par[j].descr_str,\
				  str)))\
				{\
				trovato=1;\
				*poslist=i;\
				*posriga=j;\
				return(i);\
				}\
			}\
		i=next_pos_lista(i,direz);\
		}\
	}			\
if(i==start && !trovato) \
	{\
	*poslist= -1;\
	*posriga= -1;\
	return(-1);\
	}\
}\
\
\
\
next_pos_lista(inizio,direz)\
int inizio;  /* posizione di partenza */\
int direz;  /* direzione dello spostamento\
		==1 -> in avanti */\
{\
int i;\
int num_righe;\
if(tipo_lista==ALL_DATA)\
	num_righe=lparam.num_righe;\
else\
	num_righe=lista.num_righe;\
if(direz==1)\
	{\
	if(inizio < (num_righe-1))	\
		i=inizio+1;	\
	else\
		i=0;\
	}\
else\
	{\
	if(inizio> 0)\
		i=inizio-1;\
	else\
		i=num_righe-1;\
	}\
return(i);\
}\
\
\
/*\
 plista_to_pvis\
   trasforma da posizione nella lista a posizione nella\
   edit window scrollabile tenendo conto del tipo di \
   variabili visualizzate\
*/\
plista_to_pvis(poslista)\
int poslista;\
{\
int i;\
int posvis; /* posizione in visualizzazione */\
int tipovar_ok;\
posvis=0;\
\
if(tipo_lista== INP_VAR)\
	tipovar_ok=TIPO_INPBLO;\
else if (tipo_lista== OUT_VAR)\
	tipovar_ok=TIPO_OUTBLO;\
\
for(i=0;i<poslista;i++)\
	{\
	if(lista.riga[i].io_blo==TIPO_DOPPIA) continue;\
	if(tipo_lista==ALL_VAR)\
		posvis++;	\
	else if(lista.riga[i].io_blo==tipovar_ok) posvis++;\
	}\
return(posvis);\
}\
\
void confirm_apply (w,which_button,call_data)\
Widget w;\
int which_button;\
XmAnyCallbackStruct *call_data;\
{\
/*\
 L'utente ha richiesto di continuare\
 senza salvare (Continue)\
*/\
if (which_button == 0)\
	{	\
        aggiorna_all_lists();\
	modified=False;\
	}\
\
/* Chiudi la window di conferma */\
XtDestroyWidget(w);\
\
}\
\
void confirm_close (w,which_button,call_data)\
Widget w;\
int which_button;\
XmAnyCallbackStruct *call_data;\
{\
/*\
 L'utente ha richiesto di continuare perdendo\
 i dati (Continue)\
*/\
if (which_button == 0)\
	{\
	modified=False;\
	free_righe_edit();\
	UxDestroyInterface(vardata_dialog);\
	n_editors--;\
	}\
\
/* Chiudi la window di conferma */\
XtDestroyWidget(w);\
\
}\
\
void confirm_recreate (w,which_button,call_data)\
Widget w;\
int which_button;\
XmAnyCallbackStruct *call_data;\
{\
Widget sw_sel; \
/* Chiudi la window di conferma */\
XtDestroyWidget(w);\
XSync((XtDisplay(w)),False);\
/*\
 Se Continue l'utente prosegue \
 altrimenti (Cancel) ritorna alla \
 condizione di partenza\
*/\
if (which_button != 100)\
	{\
	tipo_lista=which_button;\
	recreate_edit();\
	modified=False;\
	}\
else\
/*\
 Riposiziona l'option menu sulla \
 opzione di partenza\
*/\
	{\
	switch(tipo_lista)\
		{\
		case ALL_VAR:\
		sw_sel=valori_Variables;\
		break;\
		case INP_VAR:\
		sw_sel=valori_Inp_Var;\
		break;\
		case OUT_VAR:\
		sw_sel=valori_Out_Var;\
                break;\
		case ALL_DATA:\
		sw_sel=valori_Data;\
		break;\
		}\
	set_something(menu_valori,\
                     XmNmenuHistory,\
                     sw_sel);\
	}\
\
}
*vardata_dialog.name: vardata_dialog
*vardata_dialog.unitType: "pixels"
*vardata_dialog.x: 184
*vardata_dialog.y: 116
*vardata_dialog.width: 635
*vardata_dialog.height: 566
*vardata_dialog.compoundIcon: ""
*vardata_dialog.compoundName: "ListaEditabile"
*vardata_dialog.isCompound: "true"
*vardata_dialog.resizePolicy: "resize_grow"
*vardata_dialog.allowShellResize: "false"
*vardata_dialog.dialogTitle: "Variables values & data"
*vardata_dialog.autoUnmanage: "false"
*vardata_dialog.defaultButton: "apply_button"
*vardata_dialog.rubberPositioning: "false"

*apply_button.class: pushButtonGadget
*apply_button.parent: vardata_dialog
*apply_button.static: true
*apply_button.name: apply_button
*apply_button.x: 296
*apply_button.y: 0
*apply_button.width: 140
*apply_button.height: 30
*apply_button.labelString: "       Apply      "
*apply_button.recomputeSize: "true"
*apply_button.alignment: "alignment_center"
*apply_button.topAttachment: "attach_none"
*apply_button.topWidget: ""
*apply_button.bottomAttachment: "attach_form"
*apply_button.leftOffset: 0
*apply_button.rightAttachment: "attach_position"
*apply_button.rightOffset: 0
*apply_button.leftAttachment: "attach_position"
*apply_button.ancestorSensitive: "true"
*apply_button.resizable: "false"
*apply_button.rightPosition: 60
*apply_button.leftPosition: 40
*apply_button.bottomOffset: 10
*apply_button.compoundIcon: ""
*apply_button.compoundName: "ListaEditabile"
*apply_button.isCompound: "true"
*apply_button.activateCallback: {\
/*\
 estrae dalla window di editing le\
 variazioni effettuate e le salva\
*/\
salva_variazioni();\
/*\
aggiorna i contatori di var note/non note\
*/\
update_contatori();\
modified=False;\
glob_modified=True;\
}

*find_rc.class: rowColumn
*find_rc.parent: vardata_dialog
*find_rc.static: true
*find_rc.name: find_rc
*find_rc.unitType: "pixels"
*find_rc.x: 8
*find_rc.y: 368
*find_rc.width: 310
*find_rc.height: 40
*find_rc.orientation: "horizontal"
*find_rc.borderWidth: 1
*find_rc.leftOffset: 10
*find_rc.compoundIcon: ""
*find_rc.compoundName: "ListaEditabile"
*find_rc.isCompound: "true"
*find_rc.isInCompound: "false"
*find_rc.bottomAttachment: "attach_widget"
*find_rc.bottomWidget: "apply_button"
*find_rc.bottomOffset: 10

*labelGadget4.class: labelGadget
*labelGadget4.parent: find_rc
*labelGadget4.static: true
*labelGadget4.name: labelGadget4
*labelGadget4.x: 15
*labelGadget4.y: 385
*labelGadget4.width: 70
*labelGadget4.height: 20
*labelGadget4.labelString: "Find:"
*labelGadget4.compoundIcon: ""
*labelGadget4.compoundName: "ListaEditabile"
*labelGadget4.isCompound: "true"
*labelGadget4.isInCompound: "false"

*find_text.class: textField
*find_text.parent: find_rc
*find_text.static: true
*find_text.name: find_text
*find_text.x: 40
*find_text.y: 4
*find_text.width: 176
*find_text.height: 26
*find_text.compoundIcon: ""
*find_text.compoundName: "ListaEditabile"
*find_text.isCompound: "true"
*find_text.isInCompound: "false"
*find_text.marginHeight: 1
*find_text.marginWidth: 3
*find_text.resizeWidth: "false"

*arrowButton2.class: arrowButton
*arrowButton2.parent: find_rc
*arrowButton2.static: true
*arrowButton2.name: arrowButton2
*arrowButton2.x: 219
*arrowButton2.y: 4
*arrowButton2.width: 27
*arrowButton2.height: 27
*arrowButton2.arrowDirection: "arrow_up"
*arrowButton2.compoundIcon: ""
*arrowButton2.compoundName: "ListaEditabile"
*arrowButton2.isCompound: "true"
*arrowButton2.isInCompound: "false"
*arrowButton2.activateCallback: {\
char *str;\
char str2[50];\
int posiz,poslista;\
extern swidget create_vis_msg();\
str=UxGetText(find_text);\
\
posiz=cerca_in_lista(str,-1,&posiz,&poslista);\
if(posiz!=-1)\
	scrolla_lista(posiz,poslista);\
else\
	{\
	sprintf(str2,"Cannot find: %s",str);\
	create_vis_msg(str2); \
	}\
\
}

*arrowButton1.class: arrowButton
*arrowButton1.parent: find_rc
*arrowButton1.static: true
*arrowButton1.name: arrowButton1
*arrowButton1.x: 253
*arrowButton1.y: 4
*arrowButton1.width: 27
*arrowButton1.height: 27
*arrowButton1.arrowDirection: "arrow_down"
*arrowButton1.compoundIcon: ""
*arrowButton1.compoundName: "ListaEditabile"
*arrowButton1.isCompound: "true"
*arrowButton1.isInCompound: "false"
*arrowButton1.activateCallback: {\
char *str;\
char str2[50];\
int posiz,poslista;\
extern swidget create_vis_msg();\
str=UxGetText(find_text);\
\
posiz=cerca_in_lista(str,1,&posiz,&poslista);\
if(posiz!=-1)\
	scrolla_lista(posiz,poslista);\
else\
	{\
	sprintf(str2,"Cannot find: %s",str);\
	create_vis_msg(str2); \
	}\
}

*edit_pulldown.class: rowColumn
*edit_pulldown.parent: vardata_dialog
*edit_pulldown.static: true
*edit_pulldown.name: edit_pulldown
*edit_pulldown.rowColumnType: "menu_bar"
*edit_pulldown.rightAttachment: "attach_form"
*edit_pulldown.leftAttachment: "attach_form"
*edit_pulldown.menuAccelerator: "<KeyUp>F10"

*edit_File.class: rowColumn
*edit_File.parent: edit_pulldown
*edit_File.static: true
*edit_File.name: edit_File
*edit_File.rowColumnType: "menu_pulldown"

*edit_Load.class: pushButton
*edit_Load.parent: edit_File
*edit_Load.static: true
*edit_Load.name: edit_Load
*edit_Load.labelString: "Load"
*edit_Load.activateCallback: {\
extern Widget conferma();\
extern Widget UxTopLevel;\
static Elenco_callback data_agg_callback = {\
        {"Continue",  confirm_apply, 0 },\
        {"Cancel", confirm_apply, 1 },\
        {NULL,NULL, 0 }};\
\
if(modified)\
	{\
	conferma(vardata_dialog,"You have modified but not applied Variables values.\n All changes WILL BE LOST !!\n Continue?",\
		data_agg_callback);\
	}\
else\
	aggiorna_all_lists(); \
}

*edit_Close.class: pushButton
*edit_Close.parent: edit_File
*edit_Close.static: true
*edit_Close.name: edit_Close
*edit_Close.labelString: "Close"
*edit_Close.activateCallback: {\
\
extern Widget conferma();\
\
static Elenco_callback data_close_callback = {\
        {"Continue",  confirm_close, 0 },\
        {"Cancel", confirm_close, 1 },\
        {NULL,NULL, 0 }};\
\
if(modified)\
        {\
\
\
        conferma(vardata_dialog,"You have modified but not applied Variables values.\nAll changes WILL BE LOST!!\nContinue?",\
                data_close_callback);\
\
        }\
else\
	{\
	free_righe_edit();\
	UxDestroyInterface(vardata_dialog);\
	n_editors--;\
	}\
}

*edit_Edit.class: rowColumn
*edit_Edit.parent: edit_pulldown
*edit_Edit.static: true
*edit_Edit.name: edit_Edit
*edit_Edit.rowColumnType: "menu_pulldown"

*edit_Restore.class: pushButton
*edit_Restore.parent: edit_Edit
*edit_Restore.static: true
*edit_Restore.name: edit_Restore
*edit_Restore.labelString: "Restore values"
*edit_Restore.activateCallback: recreate_edit();

*Doc.class: rowColumn
*Doc.parent: edit_pulldown
*Doc.static: true
*Doc.name: Doc
*Doc.rowColumnType: "menu_pulldown"

*BDoc.class: pushButton
*BDoc.parent: Doc
*BDoc.static: true
*BDoc.name: BDoc
*BDoc.labelString: "Module Doc"
*BDoc.activateCallback: {\
   extern swidget listaBlocchi;\
   extern swidget create_vis_msg();\
   int num_selez;\
   int *item_positions;\
   extern char **nom_bloc;\
   int i,retval;\
   char **nome_mod;\
   char comando[100];\
   char doc_name[100];\
   char msg[100];\
    \
   retval=XmListGetSelectedPos(listaBlocchi,&item_positions,&num_selez);\
   if( retval == False )\
      num_selez = 0;\
\
\
   if( num_selez )\
   {\
      nome_mod = malloc( sizeof(char *) * num_selez );\
      if( nome_mod == NULL)\
      {\
         sprintf(msg,"%s\n","Doc Read: Error in malloc");\
         create_vis_msg(msg);\
      }\
\
      for(i=0;i<num_selez;i++)      \
      {\
         nome_mod[i]=malloc( sizeof(char) *5 );\
         printf("nome_blocco selezionato = %s\n",nom_bloc[i]);\
         sprintf(nome_mod[i],"%.4s",nom_bloc[ (item_positions[i]-1) ]);\
         tominus(nome_mod[i]);\
         printf("nome_modulo selezionato = %s\n",nome_mod[i]);\
      }\
      \
\
\
/* visualizzo solo il documento relativo al\
   primo modulo selezionato\
*/\
      sprintf(doc_name,"%s/legocad/libut/%s.doc",getenv("LEGOCAD_USER"),nome_mod[0]);\
 \
      if( esiste_file( doc_name ) )\
      {\
         sprintf(comando,"asedit -v %s &",doc_name);      \
         system(comando);\
      } \
      else\
      {\
         sprintf(msg,"%s file not found\n",doc_name);\
         create_vis_msg(msg);\
      }\
   }\
}\
 

*menu1_top_b1.class: cascadeButton
*menu1_top_b1.parent: edit_pulldown
*menu1_top_b1.static: true
*menu1_top_b1.name: menu1_top_b1
*menu1_top_b1.labelString: "File"
*menu1_top_b1.mnemonic: "F"
*menu1_top_b1.subMenuId: "edit_File"

*menu1_top_b2.class: cascadeButton
*menu1_top_b2.parent: edit_pulldown
*menu1_top_b2.static: true
*menu1_top_b2.name: menu1_top_b2
*menu1_top_b2.labelString: "Edit"
*menu1_top_b2.mnemonic: "E"
*menu1_top_b2.subMenuId: "edit_Edit"

*edit_pulldown_top_b1.class: cascadeButton
*edit_pulldown_top_b1.parent: edit_pulldown
*edit_pulldown_top_b1.static: true
*edit_pulldown_top_b1.name: edit_pulldown_top_b1
*edit_pulldown_top_b1.labelString: "Doc"
*edit_pulldown_top_b1.subMenuId: "Doc"
*edit_pulldown_top_b1.mnemonic: "D"

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.parent: vardata_dialog
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.scrollingPolicy: "application_defined"
*scrolledWindow2.x: 10
*scrolledWindow2.y: 36
*scrolledWindow2.visualPolicy: "variable"
*scrolledWindow2.scrollBarDisplayPolicy: "static"
*scrolledWindow2.shadowThickness: 0
*scrolledWindow2.rightAttachment: "attach_form"
*scrolledWindow2.rightOffset: 10
*scrolledWindow2.leftAttachment: "attach_form"
*scrolledWindow2.leftOffset: 10
*scrolledWindow2.bottomAttachment: "attach_widget"
*scrolledWindow2.bottomWidget: "edit_pulldown"
*scrolledWindow2.topAttachment: "attach_widget"
*scrolledWindow2.topWidget: "edit_pulldown"
*scrolledWindow2.topOffset: 5
*scrolledWindow2.bottomOffset: -95
*scrolledWindow2.height: 60

*listaBlocchiSel.class: scrolledList
*listaBlocchiSel.parent: scrolledWindow2
*listaBlocchiSel.static: true
*listaBlocchiSel.name: listaBlocchiSel
*listaBlocchiSel.width: 615
*listaBlocchiSel.height: 80
*listaBlocchiSel.visibleItemCount: 3
*listaBlocchiSel.listSizePolicy: "constant"
*listaBlocchiSel.selectionPolicy: "single_select"

*menu_valori.class: rowColumn
*menu_valori.parent: vardata_dialog
*menu_valori.static: true
*menu_valori.name: menu_valori
*menu_valori.rowColumnType: "menu_option"
*menu_valori.subMenuId: "valori_p1"
*menu_valori.labelString: "Show: "
*menu_valori.bottomAttachment: "attach_none"
*menu_valori.bottomWidget: ""
*menu_valori.leftOffset: 20
*menu_valori.leftPosition: 0
*menu_valori.topAttachment: "attach_widget"
*menu_valori.topWidget: "scrolledWindow2"
*menu_valori.x: 10
*menu_valori.y: 100

*valori_p1.class: rowColumn
*valori_p1.parent: menu_valori
*valori_p1.static: true
*valori_p1.name: valori_p1
*valori_p1.rowColumnType: "menu_pulldown"

*valori_Variables.class: pushButton
*valori_Variables.parent: valori_p1
*valori_Variables.static: true
*valori_Variables.name: valori_Variables
*valori_Variables.labelString: "All Variables"
*valori_Variables.activateCallback: {\
extern Widget conferma();\
static Elenco_callback data_agg_callback = {\
        {"Continue",  confirm_recreate, ALL_VAR },\
        {"Cancel", confirm_recreate, 100 },\
        {NULL,NULL, 0 }};\
\
tipo_lista=ALL_VAR;\
if(lista_edit_on)\
	{\
	if(modified)\
        	{\
        	conferma(vardata_dialog,\
                 "You have modified but not applied Variables values.\nAll changes WILL BE LOST!!\nContinue?",\
                 data_agg_callback);\
        	}\
	else\
/*\
 ricrea la nuova lista in base alla selezione effettuata\
*/\
		{\
		tipo_lista=ALL_VAR;\
		recreate_edit();\
		}\
	}\
}

*valori_Inp_Var.class: pushButton
*valori_Inp_Var.parent: valori_p1
*valori_Inp_Var.static: true
*valori_Inp_Var.name: valori_Inp_Var
*valori_Inp_Var.labelString: "Input Variables"
*valori_Inp_Var.activateCallback: {\
extern Widget conferma();\
static Elenco_callback data_agg_callback = {\
        {"Continue",  confirm_recreate, INP_VAR },\
        {"Cancel", confirm_recreate, 100 },\
        {NULL,NULL, 0 }};\
\
\
if(lista_edit_on)\
	{\
	if(modified)\
        	{\
        	conferma(vardata_dialog,\
                 "You have modified but not applied Variables values.\n All changes WILL BE LOST!!\nContinue?",\
                 data_agg_callback);\
        	}\
	else\
/*\
 ricrea la nuova lista in base alla selezione effettuata\
*/\
		{\
		tipo_lista=INP_VAR;\
		recreate_edit();\
		}\
	}\
}

*valori_Out_Var.class: pushButton
*valori_Out_Var.parent: valori_p1
*valori_Out_Var.static: true
*valori_Out_Var.name: valori_Out_Var
*valori_Out_Var.labelString: "Output Variables"
*valori_Out_Var.activateCallback: {\
extern Widget conferma();\
static Elenco_callback data_agg_callback = {\
        {"Continue",  confirm_recreate, OUT_VAR },\
        {"Cancel", confirm_recreate, 100 },\
        {NULL,NULL, 0 }};\
\
if(lista_edit_on)\
	{\
	if(modified)\
        	{\
        	conferma(vardata_dialog,\
                 "You have modified but not applied Variables values.\nAll changes WILL BE LOST !!\nContinue?",\
                 data_agg_callback);\
        	}\
	else\
/*\
 ricrea la nuova lista in base alla selezione effettuata\
*/\
		{\
		tipo_lista=OUT_VAR;\
		recreate_edit();\
		}\
	}\
}

*valori_Data.class: pushButton
*valori_Data.parent: valori_p1
*valori_Data.static: true
*valori_Data.name: valori_Data
*valori_Data.labelString: "Data"
*valori_Data.activateCallback: {\
extern Widget conferma();\
static Elenco_callback data_agg_callback = {\
        {"Continue",  confirm_recreate, ALL_DATA },\
        {"Cancel", confirm_recreate, 100 },\
        {NULL,NULL, 0 }};\
\
if(lista_edit_on)\
	{\
	if(modified)\
        	{\
        	conferma(vardata_dialog,\
                 "You have modified but not applied Variables values.\nAll changes WILL BE LOST !!\nContinue?",\
                 data_agg_callback);\
        	}\
	else\
/*\
 ricrea la nuova lista in base alla selezione effettuata\
*/\
		{\
		tipo_lista=ALL_DATA;\
		recreate_edit();\
		}\
	}\
}

*intesta_rc.class: rowColumn
*intesta_rc.parent: vardata_dialog
*intesta_rc.static: true
*intesta_rc.name: intesta_rc
*intesta_rc.x: 20
*intesta_rc.y: 10
*intesta_rc.width: 700
*intesta_rc.height: 20
*intesta_rc.rightAttachment: "attach_form"
*intesta_rc.rightOffset: 30
*intesta_rc.numColumns: 3
*intesta_rc.packing: "pack_column"
*intesta_rc.bottomAttachment: "attach_none"
*intesta_rc.bottomOffset: 0
*intesta_rc.bottomWidget: ""
*intesta_rc.leftAttachment: "attach_form"
*intesta_rc.leftOffset: 20
*intesta_rc.topAttachment: "attach_widget"
*intesta_rc.topOffset: 5
*intesta_rc.adjustLast: "true"
*intesta_rc.entryAlignment: "alignment_center"
*intesta_rc.topWidget: "menu_valori"

*labelGadget1.class: labelGadget
*labelGadget1.parent: intesta_rc
*labelGadget1.static: true
*labelGadget1.name: labelGadget1
*labelGadget1.x: 12
*labelGadget1.y: 7
*labelGadget1.width: 170
*labelGadget1.height: 25
*labelGadget1.labelString: "Known/Unknown      Value  "
*labelGadget1.compoundIcon: ""
*labelGadget1.compoundName: "ListaEditabile"
*labelGadget1.isCompound: "true"

*labelGadget2.class: labelGadget
*labelGadget2.parent: intesta_rc
*labelGadget2.static: true
*labelGadget2.name: labelGadget2
*labelGadget2.x: 200
*labelGadget2.y: 0
*labelGadget2.width: 554
*labelGadget2.height: 25
*labelGadget2.labelString: "Units"
*labelGadget2.compoundIcon: ""
*labelGadget2.compoundName: "ListaEditabile"
*labelGadget2.isCompound: "true"
*labelGadget2.alignment: "alignment_beginning"

*labelGadget3.class: labelGadget
*labelGadget3.parent: intesta_rc
*labelGadget3.static: true
*labelGadget3.name: labelGadget3
*labelGadget3.x: 120
*labelGadget3.y: 10
*labelGadget3.width: 90
*labelGadget3.height: 20
*labelGadget3.labelString: "Variable name - description"

*vardata_sw.class: scrolledWindow
*vardata_sw.parent: vardata_dialog
*vardata_sw.static: true
*vardata_sw.name: vardata_sw
*vardata_sw.scrollingPolicy: "automatic"
*vardata_sw.unitType: "pixels"
*vardata_sw.x: 10
*vardata_sw.y: 120
*vardata_sw.width: 720
*vardata_sw.height: 320
*vardata_sw.rightAttachment: "attach_form"
*vardata_sw.leftAttachment: "attach_form"
*vardata_sw.leftOffset: 10
*vardata_sw.rightOffset: 10
*vardata_sw.bottomAttachment: "attach_widget"
*vardata_sw.bottomOffset: 2
*vardata_sw.bottomWidget: "find_rc"
*vardata_sw.compoundIcon: ""
*vardata_sw.compoundName: "ListaEditabile"
*vardata_sw.isCompound: "true"
*vardata_sw.topAttachment: "attach_widget"
*vardata_sw.topWidget: "intesta_rc"

*vardata_rc.class: rowColumn
*vardata_rc.parent: vardata_sw
*vardata_rc.static: true
*vardata_rc.name: vardata_rc
*vardata_rc.unitType: "pixels"
*vardata_rc.x: 0
*vardata_rc.y: 0
*vardata_rc.width: 700
*vardata_rc.height: 410
*vardata_rc.numColumns: 1
*vardata_rc.orientation: "horizontal"
*vardata_rc.packing: "pack_column"
*vardata_rc.compoundIcon: ""
*vardata_rc.compoundName: "ListaEditabile"
*vardata_rc.isCompound: "true"
*vardata_rc.isAligned: "true"
*vardata_rc.adjustLast: "true"
*vardata_rc.adjustMargin: "false"

