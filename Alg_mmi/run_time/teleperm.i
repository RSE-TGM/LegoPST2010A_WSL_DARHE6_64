! UIMX ascii 2.5 key: 8292                                                      

*teleperm.class: topLevelShell
*teleperm.gbldecl: #include <stdio.h>\
#include <sys/stat.h>\
#include <sys/types.h>\
#include <stdlib.h>\
#include <string.h>\
#include <assert.h>\
#include <sys/param.h>\
#include <Xm/MwmUtil.h>\
#include <X11/Xlib.h>\
#include <time.h>\
#include <Ol/OlTree.h>	         /* per gestione OlTree teleperm */\
#include <Ol/OlDatabasePunti.h>  /* per gestione DatabasePunti */\
#include <Xl/XlChangePage.h>     /* per gestione oggetto XlChangePage */\
#include <Xl/XlPictograph.h>    \
#include "other.h"\
#include <Xl/XlCai.h>\
#include <Xl/XlCaiAll.h>\
#ifndef DESIGN_TIME\
#include <Xl/Xl.h>\
#endif\
#include <other.h>\
#include <Cs/Cs.h>	/* per comunocazioni per AlarmPage */\
\
extern XrmDatabase ApplDb;    /* db delle risorse della applicazione */\
\
extern OlTreeObject root_oltree;  /* OlTree root */\
\
extern AN_PAG *pagine;     /* lista delle pagine */\
extern int totale_pagine;\
extern OlDatabasePuntiObject database_simulatore;\
extern int database_type;\
extern Boolean allPageFlag;\
extern Boolean scada_on;\
extern Boolean topologia_on;\
extern PAGINE_APERTE *el_pagine;\
extern int num_el_pagine;\
\
/* dichiaro la routine di refresh  definita nella aux function\
*/\
static void teleperm_refreshPag();\
\
extern swidget create_topLevelShell1();\
extern swidget popup_topLevelShellStaz();\
extern Boolean PrintAllarmi();\
extern ClosePageStaz();\
\
extern ScriviTestoInfo();\
 \
extern Boolean EsistePagina();\
\
int  getSubLevel();\
void set_titleLabel();\
\
static void teleperm_refreshTime();\
static void teleperm_refreshCai();\
/*\
static void build_cai();\
*/\
extern AN_DISPLAY *elenco_display;\
\
/***************\
definizioni\
***************/\
#define TIPOSTAZIONE   1\
#define TIPOOW		2\
\
#define ROOT_LEVEL 100\
#define VERTMENUON 1\
#define ORIZMENUON 2\
#define PLANTMENUON 3\
\
/* definizioni nomi bitmap utilizzati per i bottoni del footer\
*/\
#define previousBMP "previous.bmp"\
#define swscreenBMP "cscreen.bmp"\
#define leftBMP "left.bmp"\
#define upBMP "up.bmp"\
#define rightBMP "right.bmp"\
#define swscreenBMP "cscreen.bmp"\
#define ackaudBMP "ackaud.bmp"\
#define ackalBMP "ackal.bmp"\
#define hardcopyBMP "hardcopy.bmp"\
#define helpBMP "help.bmp"\
#define precessDisplayBMP "overview.bmp"\
#define logoffBMP "logon.bmp"\
#define plantOverviewBMP "overview.bmp"\
\
\
\
\
\
/*\
Defaults per Info plot e aing\
*/\
#define TMPINFOFILE	"/WidResources_"\
#define DEFEDITOR       "vi"\
#define DEFTMPDIR       "/tmp"\
#define SISTEMLABEL     "Sist."\
\
#define ALLMAXLUNNOMEWID 256\
#define NUMMAXZONE	32\
#define MAXNUMALLVIS	16\
#define SEPARATORALARM  "|"\
#define KKSTAGLEN	4\
#define MAXLUNTOKEN	150\
#define NUMTOKEN	4\
#define MODO_ALLARMI	0\
#define MODO_ARCHIVIO	1\
\
\
#define HEIGHTSMALLFORMHEADER 55\
#define HEADERTRERIGHE 19\
#define HEADERQUATTRORIGHE 25\
#define HEADERCINQUERIGHE 31\
#define INDALLPAG	-15\
#define INDALLPAGFROMPLANT -30\
#define SINCROCLOSEALLPAG	-10\
#define TOLERANCE_N_TIME        180     /* sec per time-out pag all tasto [n] */\
#define DEF_TIME_OUT_N		50000   /* sec per usleep tasto [n]   */\
/* \
Dichiarazione di variabili per pagina allarmi che devono essere globali perche'\
e' possibile avere una sola pagina allarmi attiva per volta.\
In particolore  la situazione zone deve essere unica (anche per miniASD)\
*/\
/* \
Variabili per pagina allarmi\
*/\
int last_indice_fa=0;\
int num_zone;\
\
int last_zone_pressed;   /* ultima zona selezionata (per 2 utenti allPage o  dati all non validi */\
int zone_ko;\
int allPageOnScreen=-1;\
int zone_status[NUMMAXZONE];   /* tipo int per compatibilita' con msg per client_scada */\
int zone_status_old[NUMMAXZONE];/*vecchia situazione impostazione zone */\
int selectable_zone[NUMMAXZONE];  /* tabella fa attive */\
Boolean prima_apertura_all=True; /* tiene conto se non ho ancora richiesto gli allarmi */\
Boolean prima_apertura_teleperm=True;\
XtIntervalId  timer_timerefreshAll; /* per Refresh Pagina Allarmi */
*teleperm.ispecdecl: char *path_icone;         /* contiene il path relativo dove sono i .bmp ($LEGOCAD_ICO )*/\
char icon[FILENAME_MAX];  /* contiene il path completo di filename del .bmp */\
char iconOnScreen[FILENAME_MAX];  /* contiene il path completo di filename del .bmp relativo anche allo screen */\
\
/* variabili per la gestione della pagina come sinottico\
*/\
XtIntervalId timer_refresh;  /* tempo di refresh */\
int key_refresh;             /* indice del timeout di refresh */\
\
\
\
Region region_sin;           /* regione di ridisegno */\
WidgetList lista_wid;        /* lista degli widget */\
int num_wid;                 /* numero widget */\
int time_ref;                /* tempo di refresh della pagina */\
\
int top_x,top_y,top_width,top_height,top_tipo;\
char *top_descrizione;\
int progress ;               /* progressivo del nodo di OlTree */\
/* indice della pagina corrente, indice della pagina nuova \
   questi indici sono mantenuti costantemente aggiornati\
   per la gestione del previous\
*/\
int pos_pag_curr,pos_pag_new;  \
\
/* lista delle pagine figlie (OW e affini)\
*/\
int numChildPagList;\
Widget *ChildPagList;\
\
\
/* lista delle functional area (pagine di primo livello)\
   utilizzate nel metodo plantMenu\
*/\
\
int *listaPushButton;\
int *lista_fa,num_fa;\
\
int num_telepag;\
\
/* menu dinamici gerarchia orizzontale \
*/\
Widget OrizMenu,OrizPopup,OrizPane;\
Widget *listaPushButtonOr;\
Widget PlantMenu,PlantPane,*listaPushButtonPlant,*listaLabelPlant;\
\
/* Boolean per verifica esistenza menu hor. jerarqia\
*/\
int OrizMenuIsActive;\
\
/* menu dinamici gerarchia verticale \
*/\
Widget VertMenu,VertPopup,VertPane,VertTop,RowPull;\
Widget *listaPushButtonVr;\
Widget *listaCaiVr;\
Widget listaCaiHeader[MAXNUMCAIXLINE];     /* lista di Cai su cornice pagina */\
Widget *listaCaiFormVr;			  /* lista Form che contengono i Cai */\
Widget *listaPlantAsd;			  /* lista bottoni Asd per Plant menu' */\
int npagPulldown;\
/* Boolean per verifica esistenza menu hor. jerarqia\
*/\
int VertMenuIsActive;\
\
OlTreeObject curr_level;  /* OlTree livello corrente */\
\
XtIntervalId  timer_timerefresh; /* timeout refresh time field */\
XtIntervalId  timer_timerefreshCai;\
XtIntervalId  timer_timerefreshCaiHeader;\
\
char gerarchiaHeader[30];\
char labelCaiHeader[100];\
int screen_selezionato;\
int screen_switched;\
XrmDatabase PagDb;\
int pullMenuOn;		/* In order to Know which pullDownMenu is already On */\
Widget *pullDownActive;  /* Global variable to avoid more pullDownsMenus active */\
\
                      /* Colori di default per bottoni header */\
Pixel def_background_butt,def_armColor_butt,def_topShadowColor_butt,def_bottomShadowColor_butt;\
					/* colori linee emissione e rientro */\
char def_background_emission[256];\
char def_background_acknowledge[256];\
\
Widget all_topLevelShell;\
Widget all_form_topLevelShell;\
Widget all_form_title,all_old,all_new,all_old_button,all_new_label,all_old_label,all_new_button,all_title_label;\
Widget all_header_mainForm,header_rowColumn;\
Widget *lista_header_label,*lista_header_rowColumn,*lista_header_copri,*lista_header_form,*lista_header_button;\
Widget all_formAll,all_rowColumn_caiAll,all_rowColumn_nameAll,all_rowColumn_descrAll,all_rowColumn_dataAll;\
Widget *all_caiAll_form,*all_name_label,*all_descr_label,*all_data_label,*all_caiAll;\
Widget all_button_minus,all_button_plus,all_button_n;\
int modoPageAll;	/*stato pagina allarmi (modo ARCHIVIO o ALLARMI ) */\
\
/*\
Array per lo stato delle zone\
*/\
\
/*\
Array di strighe per contenere le strighe con gerarchia di ogni CaiAll\
*/\
char gerarchiaValoreAll[MAXNUMALLVIS][10*N_GERARCHIE];\
\
/*\
Situazione allarmi vecchia (utilizzata per evitare spiacevoli "flickeraggi"\
*/\
DATI_ALLARMI_SHM  old_allarmi;\
/*\
 Pixmap utilizzato come stipple per lo sfondo\
*/\
Pixmap drawing_pixmap;\
XrmDatabase OldTeleDb;\
\
/*\
Modifiche 14/7/98 per Info Plot  Aing\
*/\
int operazione_attiva;  /* 0 -> NOP 1 -> INFO 2 -> Plot 3 -> Aing */\
Boolean InfoUsed;\
Widget  ListaWidVar[7];\
Pixel def_col_menuSystem;   /* colore di default del menuSystem */
*teleperm.ispeclist: path_icone, icon, iconOnScreen, timer_refresh, key_refresh, region_sin, lista_wid, num_wid, time_ref, top_x, top_y, top_width, top_height, top_tipo, top_descrizione, progress, pos_pag_curr, pos_pag_new, numChildPagList, ChildPagList, listaPushButton, lista_fa, num_fa, num_telepag, OrizMenu, OrizPopup, OrizPane, listaPushButtonOr, PlantMenu, PlantPane, listaPushButtonPlant, listaLabelPlant, OrizMenuIsActive, VertMenu, VertPopup, VertPane, VertTop, RowPull, listaPushButtonVr, listaCaiVr, listaCaiHeader, listaCaiFormVr, listaPlantAsd, npagPulldown, VertMenuIsActive, curr_level, timer_timerefresh, timer_timerefreshCai, timer_timerefreshCaiHeader, gerarchiaHeader, labelCaiHeader, screen_selezionato, screen_switched, PagDb, pullMenuOn, pullDownActive, def_background_butt, def_armColor_butt, def_topShadowColor_butt, def_bottomShadowColor_butt, def_background_emission, def_background_acknowledge, all_topLevelShell, all_form_topLevelShell, all_form_title, all_old, all_new, all_old_button, all_new_label, all_old_label, all_new_button, all_title_label, all_header_mainForm, header_rowColumn, lista_header_label, lista_header_rowColumn, lista_header_copri, lista_header_form, lista_header_button, all_formAll, all_rowColumn_caiAll, all_rowColumn_nameAll, all_rowColumn_descrAll, all_rowColumn_dataAll, all_caiAll_form, all_name_label, all_descr_label, all_data_label, all_caiAll, all_button_minus, all_button_plus, all_button_n, modoPageAll, gerarchiaValoreAll, old_allarmi, drawing_pixmap, OldTeleDb, operazione_attiva, InfoUsed, ListaWidVar, def_col_menuSystem
*teleperm.ispeclist.path_icone: "unsigned char", "*%path_icone%"
*teleperm.ispeclist.icon: "unsigned char", "%icon%[255]"
*teleperm.ispeclist.iconOnScreen: "unsigned char", "%iconOnScreen%[255]"
*teleperm.ispeclist.timer_refresh: "XtIntervalId", "%timer_refresh%"
*teleperm.ispeclist.key_refresh: "int", "%key_refresh%"
*teleperm.ispeclist.region_sin: "Region", "%region_sin%"
*teleperm.ispeclist.lista_wid: "WidgetList", "%lista_wid%"
*teleperm.ispeclist.num_wid: "int", "%num_wid%"
*teleperm.ispeclist.time_ref: "int", "%time_ref%"
*teleperm.ispeclist.top_x: "int", "%top_x%"
*teleperm.ispeclist.top_y: "int", "%top_y%"
*teleperm.ispeclist.top_width: "int", "%top_width%"
*teleperm.ispeclist.top_height: "int", "%top_height%"
*teleperm.ispeclist.top_tipo: "int", "%top_tipo%"
*teleperm.ispeclist.top_descrizione: "unsigned char", "*%top_descrizione%"
*teleperm.ispeclist.progress: "int", "%progress%"
*teleperm.ispeclist.pos_pag_curr: "int", "%pos_pag_curr%"
*teleperm.ispeclist.pos_pag_new: "int", "%pos_pag_new%"
*teleperm.ispeclist.numChildPagList: "int", "%numChildPagList%"
*teleperm.ispeclist.ChildPagList: "Widget", "*%ChildPagList%"
*teleperm.ispeclist.listaPushButton: "int", "*%listaPushButton%"
*teleperm.ispeclist.lista_fa: "int", "*%lista_fa%"
*teleperm.ispeclist.num_fa: "int", "%num_fa%"
*teleperm.ispeclist.num_telepag: "int", "%num_telepag%"
*teleperm.ispeclist.OrizMenu: "Widget", "%OrizMenu%"
*teleperm.ispeclist.OrizPopup: "Widget", "%OrizPopup%"
*teleperm.ispeclist.OrizPane: "Widget", "%OrizPane%"
*teleperm.ispeclist.listaPushButtonOr: "Widget", "*%listaPushButtonOr%"
*teleperm.ispeclist.PlantMenu: "Widget", "%PlantMenu%"
*teleperm.ispeclist.PlantPane: "Widget", "%PlantPane%"
*teleperm.ispeclist.listaPushButtonPlant: "Widget", "*%listaPushButtonPlant%"
*teleperm.ispeclist.listaLabelPlant: "Widget", "*%listaLabelPlant%"
*teleperm.ispeclist.OrizMenuIsActive: "int", "%OrizMenuIsActive%"
*teleperm.ispeclist.VertMenu: "Widget", "%VertMenu%"
*teleperm.ispeclist.VertPopup: "Widget", "%VertPopup%"
*teleperm.ispeclist.VertPane: "Widget", "%VertPane%"
*teleperm.ispeclist.VertTop: "Widget", "%VertTop%"
*teleperm.ispeclist.RowPull: "Widget", "%RowPull%"
*teleperm.ispeclist.listaPushButtonVr: "Widget", "*%listaPushButtonVr%"
*teleperm.ispeclist.listaCaiVr: "Widget", "*%listaCaiVr%"
*teleperm.ispeclist.listaCaiHeader: "Widget", "%listaCaiHeader%[5]"
*teleperm.ispeclist.listaCaiFormVr: "Widget", "*%listaCaiFormVr%"
*teleperm.ispeclist.listaPlantAsd: "Widget", "*%listaPlantAsd%"
*teleperm.ispeclist.npagPulldown: "int", "%npagPulldown%"
*teleperm.ispeclist.VertMenuIsActive: "int", "%VertMenuIsActive%"
*teleperm.ispeclist.curr_level: "OlTreeObject", "%curr_level%"
*teleperm.ispeclist.timer_timerefresh: "XtIntervalId", "%timer_timerefresh%"
*teleperm.ispeclist.timer_timerefreshCai: "XtIntervalId", "%timer_timerefreshCai%"
*teleperm.ispeclist.timer_timerefreshCaiHeader: "XtIntervalId", "%timer_timerefreshCaiHeader%"
*teleperm.ispeclist.gerarchiaHeader: "unsigned char", "%gerarchiaHeader%[30]"
*teleperm.ispeclist.labelCaiHeader: "unsigned char", "%labelCaiHeader%[100]"
*teleperm.ispeclist.screen_selezionato: "int", "%screen_selezionato%"
*teleperm.ispeclist.screen_switched: "int", "%screen_switched%"
*teleperm.ispeclist.PagDb: "XrmDatabase", "%PagDb%"
*teleperm.ispeclist.pullMenuOn: "int", "%pullMenuOn%"
*teleperm.ispeclist.pullDownActive: "Widget", "*%pullDownActive%"
*teleperm.ispeclist.def_background_butt: "Pixel", "%def_background_butt%"
*teleperm.ispeclist.def_armColor_butt: "Pixel", "%def_armColor_butt%"
*teleperm.ispeclist.def_topShadowColor_butt: "Pixel", "%def_topShadowColor_butt%"
*teleperm.ispeclist.def_bottomShadowColor_butt: "Pixel", "%def_bottomShadowColor_butt%"
*teleperm.ispeclist.def_background_emission: "unsigned char", "%def_background_emission%[256]"
*teleperm.ispeclist.def_background_acknowledge: "unsigned char", "%def_background_acknowledge%[256]"
*teleperm.ispeclist.all_topLevelShell: "Widget", "%all_topLevelShell%"
*teleperm.ispeclist.all_form_topLevelShell: "Widget", "%all_form_topLevelShell%"
*teleperm.ispeclist.all_form_title: "Widget", "%all_form_title%"
*teleperm.ispeclist.all_old: "Widget", "%all_old%"
*teleperm.ispeclist.all_new: "Widget", "%all_new%"
*teleperm.ispeclist.all_old_button: "Widget", "%all_old_button%"
*teleperm.ispeclist.all_new_label: "Widget", "%all_new_label%"
*teleperm.ispeclist.all_old_label: "Widget", "%all_old_label%"
*teleperm.ispeclist.all_new_button: "Widget", "%all_new_button%"
*teleperm.ispeclist.all_title_label: "Widget", "%all_title_label%"
*teleperm.ispeclist.all_header_mainForm: "Widget", "%all_header_mainForm%"
*teleperm.ispeclist.header_rowColumn: "Widget", "%header_rowColumn%"
*teleperm.ispeclist.lista_header_label: "Widget", "*%lista_header_label%"
*teleperm.ispeclist.lista_header_rowColumn: "Widget", "*%lista_header_rowColumn%"
*teleperm.ispeclist.lista_header_copri: "Widget", "*%lista_header_copri%"
*teleperm.ispeclist.lista_header_form: "Widget", "*%lista_header_form%"
*teleperm.ispeclist.lista_header_button: "Widget", "*%lista_header_button%"
*teleperm.ispeclist.all_formAll: "Widget", "%all_formAll%"
*teleperm.ispeclist.all_rowColumn_caiAll: "Widget", "%all_rowColumn_caiAll%"
*teleperm.ispeclist.all_rowColumn_nameAll: "Widget", "%all_rowColumn_nameAll%"
*teleperm.ispeclist.all_rowColumn_descrAll: "Widget", "%all_rowColumn_descrAll%"
*teleperm.ispeclist.all_rowColumn_dataAll: "Widget", "%all_rowColumn_dataAll%"
*teleperm.ispeclist.all_caiAll_form: "Widget", "*%all_caiAll_form%"
*teleperm.ispeclist.all_name_label: "Widget", "*%all_name_label%"
*teleperm.ispeclist.all_descr_label: "Widget", "*%all_descr_label%"
*teleperm.ispeclist.all_data_label: "Widget", "*%all_data_label%"
*teleperm.ispeclist.all_caiAll: "Widget", "*%all_caiAll%"
*teleperm.ispeclist.all_button_minus: "Widget", "%all_button_minus%"
*teleperm.ispeclist.all_button_plus: "Widget", "%all_button_plus%"
*teleperm.ispeclist.all_button_n: "Widget", "%all_button_n%"
*teleperm.ispeclist.modoPageAll: "int", "%modoPageAll%"
*teleperm.ispeclist.gerarchiaValoreAll: "unsigned char", "%gerarchiaValoreAll%[16][60]"
*teleperm.ispeclist.old_allarmi: "DATI_ALLARMI_SHM", "%old_allarmi%"
*teleperm.ispeclist.drawing_pixmap: "Pixmap", "%drawing_pixmap%"
*teleperm.ispeclist.OldTeleDb: "XrmDatabase", "%OldTeleDb%"
*teleperm.ispeclist.operazione_attiva: "int", "%operazione_attiva%"
*teleperm.ispeclist.InfoUsed: "Boolean", "%InfoUsed%"
*teleperm.ispeclist.ListaWidVar: "Widget", "%ListaWidVar%[7]"
*teleperm.ispeclist.def_col_menuSystem: "Pixel", "%def_col_menuSystem%"
*teleperm.funcdecl: swidget create_teleperm(UxParent,Pag,nome_display)\
swidget UxParent;\
AN_PAG *Pag;             /* puntatore ai dati della pagina */\
char *nome_display;      /* nome del display di output della pagina */ \

*teleperm.funcname: create_teleperm
*teleperm.funcdef: "swidget", "<create_teleperm>(%)"
*teleperm.argdecl: swidget UxParent;\
AN_PAG *Pag;\
unsigned char *nome_display;
*teleperm.arglist: UxParent, Pag, nome_display
*teleperm.arglist.UxParent: "swidget", "%UxParent%"
*teleperm.arglist.Pag: "AN_PAG", "*%Pag%"
*teleperm.arglist.nome_display: "unsigned char", "*%nome_display%"
*teleperm.icode: /* Per scelta pixmap a seconda dello screen */\
int numero_screen;\
\
/*XrmDatabase PagDb;*/\
char nome_pag[255];\
OlTreeObject curr_oltree;\
\
\
/* per gestione sinottico\
*/\
int dim[4];\
int num_b;\
extern Boolean leggi_file_bck();\
int *ind_list,nlist,i;\
\
\
/* variabili per risorse della drawing area\
*/\
int drawing_width,drawing_height;\
Pixel *drawing_background;\
Pixmap pix;\
\
\
\
/* inizializzazione \
*/\
drawing_pixmap=0;\
numChildPagList=0;\
ChildPagList=NULL;\
screen_switched = False;\
\
pullMenuOn=False; \
\
OrizMenuIsActive = False;\
VertMenuIsActive = False;\
\
modoPageAll=MODO_ALLARMI;\
\
pullDownActive=NULL;	/* Inizialize pointer to pullDownMenu */ \
npagPulldown=0;\
if( !EsistePagina(Pag->nome) )\
{\
      printf("Error. File Page %s not exist.\n",Pag->nome);\
      return( NULL );\
}\
/********************************************\
Inizio inizializzazione var glob pagAll\
Questa parte viene eseguita solo alla prima\
apertura di una pag teleperm\
*********************************************/\
if(prima_apertura_teleperm)\
   {\
   /*\
   Setto a 0 la situazione vecchi allarmi\
   */\
   memset(&old_allarmi,0,sizeof(DATI_ALLARMI_SHM));\
   /*\
   Inizializzo stato delle zone\
   */\
\
   for(i=0;i<NUMMAXZONE;i++)\
	   {\
	   zone_status[i]=0;\
	   zone_status_old[i]=0;\
           }\
   num_zone=16; /* num_zone su layout grafico */\
\
   \
\
   last_zone_pressed=-1;      /* ultimo bottone-zona premuto */\
   zone_ko=-1;             /* zona gia' selezionata */\
   prima_apertura_teleperm=False;   \
   /*************************************************\
   Fine settaggio var globali per pagina ALLARMI\
   *************************************************/\
   }\
\
/*\
Calcolo la situazione delle fa con le selectable_zone\
*/\
num_telepag=0;\
recognize_fa();\
/*************************************************\
Fine settaggio var locali  per pagina ALLARMI\
*************************************************/\
\
/* file delle risorse della pagina da caricare\
*/\
   sprintf(nome_pag,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),Pag->nome);\
\
/* carico il db della pagina\
*/\
  if( (PagDb = XrmGetFileDatabase(nome_pag)) == NULL)\
  {\
      printf("Error. Cannot open page %s\n",nome_pag);\
      return(NULL);\
  }\
\
/* merge db della pagina e della applicazione (quello salvato su file)\
*/\
   XrmCombineFileDatabase( "ApplDb.res", &PagDb ,True);\
\
/* setto il display su PagDb \
   NOTA come parametro display devo utilizzare quello del parent\
   perche la applicazioni e' multidisplay o mulriscreen.\
*/\
   XrmSetDatabase(XtDisplay(UxParent),PagDb);\
\
/* mi serve solo per caricare il time_ref\
*/\
if(!GetResTopLevel(UxParent,&top_x,&top_y,&top_width,&top_height,&time_ref,\
		&top_tipo,&top_descrizione))\
	return(False);\
\
/* recupero le risorse della drawing area\
*/\
   if(!GetResDrawing(UxParent,&drawing_width,&drawing_height,&drawing_background,&drawing_pixmap))\
		return(False);\
\
operazione_attiva=OPERAZIONE_NOP;
*teleperm.fcode: screen_selezionato = XDefaultScreen(XtDisplay(rtrn));\
elenco_display[0].scr[screen_selezionato].wteleperm = rtrn;\
\
\
printf("screen default = %d\n",screen_selezionato);\
printf("wteleperm[0] - %d\n",elenco_display[0].scr[0].wteleperm);\
printf("wteleperm[1] - %d\n",elenco_display[0].scr[1].wteleperm);\
\
/* provo a impostare le heigth e la width in base alle dimensioni dello screen\
*/\
{\
   int h,w;\
  \
  h = HeightOfScreen( XtScreen(rtrn) );\
  w = WidthOfScreen( XtScreen(rtrn) );\
  \
  printf("Set dimensioni dello screen w=%d h=%d\n",w,h);\
 \
  XtVaSetValues( rtrn, \
                 XmNheight,h,\
                 XmNwidth, w,\
                 NULL);\
\
  XtVaGetValues( rtrn, \
                 XmNheight,&h,\
                 XmNwidth, &w,\
                 NULL);\
\
  printf("Get dimensioni della pagina w=%d h=%d\n",w,h);\
\
}\
\
teleperm_refreshTime(Ora);\
\
/* setto i pixmap sui bottoni dlla pagina teleperm \
   i .bmp so trovano in $LEGOCAD_ICO \
*/\
\
path_icone=(char *)getenv("LEGOCAD_ICO");\
\
if(path_icone==NULL)\
{\
   printf("\nERROR Environment variable LEGOCAD_ICO is not defined. Exit.\n");\
   exit(1);\
}\
\
sprintf(icon,"%s/overview.bmp",path_icone);\
UxPutStrRes(plantOverview,XmNlabelPixmap,icon);\
UxPutStrRes(processDisplay,XmNlabelPixmap,icon);\
\
sprintf(icon,"%s/previous.bmp",path_icone);\
UxPutStrRes(previous,XmNlabelPixmap,icon);\
\
sprintf(icon,"%s/left.bmp",path_icone);\
UxPutStrRes(left,XmNlabelPixmap,icon);\
\
sprintf(icon,"%s/up.bmp",path_icone);\
UxPutStrRes(up,XmNlabelPixmap,icon);\
\
sprintf(icon,"%s/right.bmp",path_icone);\
UxPutStrRes(right,XmNlabelPixmap,icon);\
\
sprintf(icon,"%s/cscreen.bmp",path_icone);\
UxPutStrRes(swscreen,XmNlabelPixmap,icon);\
UxPutStrRes(swscreen,XmNlabelInsensitivePixmap,icon);\
\
sprintf(icon,"%s/ackal.bmp",path_icone);\
UxPutStrRes(ackal,XmNlabelPixmap,icon);\
\
sprintf(icon,"%s/ackaud.bmp",path_icone);\
UxPutStrRes(ackaud,XmNlabelPixmap,icon);\
\
sprintf(icon,"%s/hardcopy.bmp",path_icone);\
UxPutStrRes(hardcopy,XmNlabelPixmap,icon);\
\
sprintf(icon,"%s/help.bmp",path_icone);\
UxPutStrRes(help,XmNlabelPixmap,icon);\
\
sprintf(icon,"%s/logon.bmp",path_icone);\
UxPutStrRes(logoff,XmNlabelPixmap,icon);\
\
\
\
/* setto il background della drawingArea\
*/\
if(drawing_pixmap)\
	{\
	set_something(drawingArea,XmNbackgroundPixmap,drawing_pixmap);\
	}\
else\
	set_something(drawingArea,XmNbackground,drawing_background);\
\
/* inizia la gestione della pagina come sinottico\
*/\
\
/*\
  inizializza la regione di ridisegno\
*/\
if(Pag->sfondo==NULL)	\
   leggi_file_bck(UxParent,Pag->nome,"bkg",&(Pag->sfondo),dim);\
else\
   AllocaColoriSfondo(UxParent,Pag->sfondo);\
\
\
region_sin=NULL;\
\
if(!CreaPagina(drawingArea,&lista_wid, &num_wid))\
	return(NULL);\
\
if((key_refresh=InsElencoPagine(Pag->nome,lista_wid,num_wid,time_ref)) == -1)\
	return(NULL);\
\
/* set del timer di refresh e della routine di refresh (teleperm_refreshPag)\
*/\
timer_refresh = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (teleperm),\
            (unsigned long) (time_ref*100) ,teleperm_refreshPag, teleperm );\
\
\
\
/* elimino le decorazioni di window manager\
*/\
teleperm_decorationToggle(rtrn,&UxEnv);\
\
/* aggiorno la header area\
*/\
teleperm_aggHeaderArea(rtrn,&UxEnv);\
\
/* aggiorno la title area\
*/\
teleperm_aggTitleArea(teleperm,&UxEnv);\
\
/* recupero le informazioni sulla pagina corrente\
*/\
/* Carlo. provo la gestione di pagine senza gerarchia\
if( OlTreeGetPage(root_oltree,&curr_oltree,&progress,&pos_pag_curr,Pag->gerarchia) == False )\
{\
   printf("Error retrieving hierarchy information for this page\n");\
   return(False);\
}\
*/\
\
if( strcmp(Pag->gerarchia,"-1,-1,-1,-1,-1,-1") != NULL)\
{\
   if( OlTreeGetPage(root_oltree,&curr_oltree,&progress,&pos_pag_curr,Pag->gerarchia) == False )\
   {\
      printf("Error retrieving hierarchy information for this page\n");\
      return(False);\
   }\
}\
else\
{\
   printf("Pagina fuori gerarchia %s\n",Pag->nome);\
   for(i=0;i<totale_pagine;i++)\
      if( strcmp(Pag->nome,pagine[i].nome)==NULL)\
      {\
          pos_pag_curr=i;\
          break;\
      }\
}\
                \
\
if( elenco_display[0].num_screens < 2 )\
   set_something(swscreen,XmNsensitive,False);\
\
pos_pag_new = pos_pag_curr;\
\
/* Creo caiHeader per configurazione con scada */\
if(scada_on)\
	{\
	teleperm_createCaiHeader(teleperm,&UxEnv);\
\
	teleperm_createButtonPixmap(teleperm,&UxEnv);\
\
	}\
\
else\
	{	\
	set_something(plantButton,XmNsensitive,False);\
	/*set_something(orizHierButton,XmNsensitive,False);\
	set_something(vertHierButton,XmNsensitive,False);*/\
	set_something(isa,XmNsensitive,False);\
	}\
/*\
Se mmi senza -Topologia, disattiva bottoni Plot ed Aing\
*/ \
if(!topologia_on)\
  {\
  set_something(plot,XmNsensitive,False);\
  set_something(aing,XmNsensitive,False);\
  }\
else\
  {\
  /*\
  Per plot Aing Info\
  */\
  get_something(menuSystem_csbutt,XmNbackground,&def_col_menuSystem);\
  }\
InfoUsed=False;\
return(rtrn);\

*teleperm.auxdecl: /********************************  \
 * interfaccia per uso esterno del \
 * metodo aggListChild\
 ********************************/\
int aggiornaListChild( Widget ow )\
{\
   Widget parent;\
 \
   parent = XtParent(ow);\
   teleperm_aggListChild( parent,&UxEnv, ow );\
}\
\
/***********************\
* costruzione dei CAI\
************************/\
static void build_cai(listaCai,nomeLista,parent,leftWidget,gerarchia,i)\
Widget *listaCai;\
char *nomeLista;\
Widget parent;\
Widget leftWidget;\
char *gerarchia;\
int i;\
{\
char nomeCai[100];\
Dimension alt,larg;\
XmFontList caiFont;\
Pixel background_parent;\
\
\
/*\
Lettera e bordo Cai in base a parent background\
*/\
get_something(parent,XmNbackground,&background_parent);\
/*\
Posizione Cai in base a widget di sx\
*/\
get_something(leftWidget,XmNheight,&alt);\
get_something(leftWidget,XmNwidth,&larg);\
/*printf("builCai: gerarchia=%s\n",gerarchia);*/\
\
        strcpy(nomeCai,nomeLista);\
        strcat(nomeCai,"A");\
if(parent==leftWidget) /* Cai appaiono da soli */\
	{\
	listaCai[i*MAXNUMCAIXLINE]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			parent,\
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,leftWidget,\
			XmNtopWidget,leftWidget,*/\
			XmNtopAttachment,XmATTACH_FORM,\
			XmNleftAttachment,XmATTACH_FORM,\
			XlNtipoCai, CAI_A,\
			XmNleftOffset,LEFTOFFSET,\
			XlNcolorBord,background_parent,\
			XmNtopOffset,TOPOFFSET,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
			XlNvarGerarchia,gerarchia,\
			NULL);\
	}\
else\
	{\
	listaCai[i*MAXNUMCAIXLINE]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			parent,\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,leftWidget,\
			XmNtopAttachment,XmATTACH_FORM,\
			XlNtipoCai, CAI_A,\
			XmNleftOffset,LEFTOFFSET,\
			XlNcolorBord,background_parent,\
			XmNtopOffset,TOPOFFSET,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
			XlNvarGerarchia,gerarchia,\
			NULL);\
	}		\
	UxPutContext( listaCai[i*MAXNUMCAIXLINE],(char *) UxTelepermContext );\
\
        strcpy(nomeCai,nomeLista);\
        strcat(nomeCai,"W");\
\
	listaCai[i*MAXNUMCAIXLINE+1]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			parent,\
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,*/\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,listaCai[i*MAXNUMCAIXLINE],\
			/*XmNtopWidget,leftWidget,*/\
			XmNtopAttachment,XmATTACH_FORM,\
			XlNtipoCai, CAI_W,\
			XmNleftOffset,LEFTOFFSET,\
			XmNtopOffset,TOPOFFSET,\
			XlNcolorBord,background_parent,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
			XlNvarGerarchia,gerarchia,\
			NULL);\
\
	UxPutContext( listaCai[i*MAXNUMCAIXLINE+1],(char *) UxTelepermContext );\
\
        strcpy(nomeCai,nomeLista);\
        strcat(nomeCai,"T");\
\
	listaCai[i*MAXNUMCAIXLINE+2]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			parent,\
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,*/\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,listaCai[i*MAXNUMCAIXLINE+1],\
			/*XmNtopWidget,leftWidget,*/\
			XmNtopAttachment,XmATTACH_FORM,\
			XlNtipoCai, CAI_T,\
			XmNleftOffset,LEFTOFFSET,\
			XmNtopOffset,TOPOFFSET,\
			XlNcolorBord,background_parent,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
\
			XlNvarGerarchia,gerarchia,\
			NULL);\
\
	UxPutContext( listaCai[i*MAXNUMCAIXLINE+2],(char *) UxTelepermContext );\
\
        strcpy(nomeCai,nomeLista);\
        strcat(nomeCai,"M");\
	listaCai[i*MAXNUMCAIXLINE+3]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			parent,\
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,*/\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,listaCai[i*MAXNUMCAIXLINE+2],\
			/*XmNtopWidget,leftWidget,*/\
			XmNtopAttachment,XmATTACH_FORM,\
			XlNtipoCai, CAI_M,\
			XmNleftOffset,LEFTOFFSET,\
			XmNtopOffset,TOPOFFSET,\
			XlNcolorBord,background_parent,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
\
			XlNvarGerarchia,gerarchia,\
			NULL);\
\
	UxPutContext( listaCai[i*MAXNUMCAIXLINE+3],(char *) UxTelepermContext );\
\
        strcpy(nomeCai,nomeLista);\
        strcat(nomeCai,"F");\
	listaCai[i*MAXNUMCAIXLINE+4]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			parent,\
			/*XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,*/\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,listaCai[i*MAXNUMCAIXLINE+3],\
			/*XmNtopWidget,leftWidget,*/\
			XmNtopAttachment,XmATTACH_FORM,\
			XlNtipoCai, CAI_F,\
			XmNleftOffset,LEFTOFFSET,\
			XmNtopOffset,TOPOFFSET,\
			XlNcolorBord,background_parent,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
\
			XlNvarGerarchia,gerarchia,\
			NULL);\
\
	UxPutContext( listaCai[i*MAXNUMCAIXLINE+4],(char *) UxTelepermContext );\
\
\
\
\
}\
\
static void teleperm_refreshTime(wid)\
swidget wid;\
{\
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;\
   float simTime;\
\
   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );\
\
/* refresh del tempo di simulazione\
*/\
  simTime = OlGetTime(database_simulatore);\
  teleperm_dispTime(teleperm,&UxEnv,simTime);\
\
/* \
        carica il timer per il refresh\
*/\
   timer_timerefresh = XtAppAddTimeOut (\
         XtWidgetToApplicationContext (wid),\
         (unsigned long) (1000) ,teleperm_refreshTime, wid);\
\
   UxTelepermContext = UxSaveCtx;\
 \
}\
static void teleperm_refreshCai(wid)\
swidget wid;\
{\
int i;\
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;\
\
\
   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );\
/*\
Faccio la refresh dei soli Cai del pullDownMenu \
attivo in quel momento\
*/\
\
\
   XlRefreshWidget(listaCaiVr,npagPulldown);\
\
   timer_timerefreshCai = XtAppAddTimeOut (\
         XtWidgetToApplicationContext (wid),\
         (unsigned long) (1000) ,teleperm_refreshCai, wid);\
\
\
   UxTelepermContext = UxSaveCtx;\
 \
}\
static void teleperm_refreshCaiHeader(wid)\
swidget wid;\
{\
int i;\
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;\
\
\
   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );\
\
   XlRefreshWidget(listaCaiHeader,MAXNUMCAIXLINE);\
\
\
   timer_timerefreshCaiHeader = XtAppAddTimeOut (\
         XtWidgetToApplicationContext (wid),\
         (unsigned long) (1000) ,teleperm_refreshCaiHeader, wid);\
\
\
   UxTelepermContext = UxSaveCtx;\
 \
}\
static void teleperm_refreshAllPage(wid)\
swidget wid;\
{\
  _UxCteleperm            *UxSaveCtx = UxTelepermContext;\
\
\
   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );\
/*\
chiamo metodo di Refresh per pagina allarmi \
*/\
teleperm_refreshAllPageWidgets(teleperm,&UxEnv);\
	timer_timerefreshAll = XtAppAddTimeOut (XtWidgetToApplicationContext (wid),\
		(unsigned long) (1000) ,teleperm_refreshAllPage,wid);\
\
\
\
   UxTelepermContext = UxSaveCtx;\
 \
}\
\
static void teleperm_refreshPag(wid)\
swidget wid;\
{\
   int i;\
   Boolean found = False;\
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;\
   float simTime;\
\
/* recupero il context \
*/\
   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );\
\
  if(!OlSetDataPage(database_simulatore,key_refresh))\
  {\
        printf("Error in refresh\n");\
        return;\
  }\
\
  if(OlGetDataStatus(database_simulatore,key_refresh)) {   \
        XlRefreshWidget(lista_wid,num_wid);\
  }\
  else {\
/*\
	MAURIC. Gestione del refresh dell'oggetto XlCurve. L'oggetto XlCurve deve essere\
	rinfrescato anche se non fa riferimento al database del simulatore (deve visualizzare\
	i valori presenti nel file f22circ.dat per un certo numero di variabili configurate).\
        05/11/1997\
*/ \
     i=0;\
     while((found==False)&&(i<num_wid)) {\
        found=XlIsCurve(lista_wid[i]);\
        i++;\
     }\
     if(found==True)\
        XlRefreshWidget(lista_wid,num_wid);\
  }\
\
   if(!OlUnsetDataPage(database_simulatore,key_refresh))\
        {\
        printf("Error in refresh\n");\
        return;\
        }\
\
/*\
        carica il timer per il refresh\
*/\
      timer_refresh = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (teleperm),\
            (unsigned long) (time_ref*100) ,teleperm_refreshPag, teleperm);\
\
/* switch del context\
*/\
   UxTelepermContext = UxSaveCtx;\
\
\
}\
\
\
\
/* routine interfaccia verso moduli esterni per chiusura pagina\
*/\
void telep_chiudi_pag( w )\
Widget w;\
{\
   /* chiamo il metodo closePag\
   */\
   teleperm_closePag( w,&UxEnv,w);\
}\
/*\
Funzione per aprire pagine di Stazione da PlantDisplay di \
tipo Teleperm\
*/\
void teleperm_apriStaz(pagina,Padre, nome_disp,sfondo_staz)\
char *pagina;\
Widget Padre;\
char *nome_disp;\
BCK_OBJ *sfondo_staz;\
{\
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;\
\
\
   UxTelepermContext = (_UxCteleperm *) UxGetContext( Padre );\
   \
   teleperm_openStaz(elenco_display[0].scr[screen_selezionato].wteleperm,&UxEnv,pagina,Padre, nome_disp,(char *)sfondo_staz);\
\
   UxTelepermContext = UxSaveCtx;\
}\
/*\
routine interfaccia verso moduli esterni per navigazione teleperm\
*/\
void teleperm_naviga(wid,direction, indice)\
Widget wid;\
int direction;\
int indice;\
{\
   _UxCteleperm            *UxSaveCtx = UxTelepermContext;\
\
\
   UxTelepermContext = (_UxCteleperm *) UxGetContext( wid );\
\
/*\
Invoco la teleperm navigation passandogli come parametro il wteleperm del giusto screen \
per permettere elaborazione del  Context corretto\
N.B.\
Lo screen_selezionato deve essere quello Della interfaccia chiamante\
Passo anche come parametro il widget chiamante\
*/\
\
\
if( elenco_display[0].scr[screen_selezionato].wteleperm != NULL )\
        teleperm_navigation(elenco_display[0].scr[screen_selezionato].wteleperm,&UxEnv,direction,indice,screen_selezionato,wid);\
else\
	{\
        if(pos_pag_new==INDALLPAG) /* creo teleperm con pag corrente */\
		{\
		if(pos_pag_curr<0)\
			{\
			fprintf(stderr,"Error: invalid index of selected pag\n");\
                        UxTelepermContext = UxSaveCtx;\
			return;\
			}\
\
		elenco_display[0].scr[screen_selezionato].wteleperm = create_teleperm(elenco_display[0].scr[screen_selezionato].topLevel,\
                                                           &pagine[pos_pag_curr],"nome_display");\
\
                if( elenco_display[0].scr[screen_selezionato].wteleperm > 0 )\
        	   UxPopupInterface(elenco_display[0].scr[screen_selezionato].wteleperm,no_grab);\
		}\
     	else\
        	{\
\
	        elenco_display[0].scr[screen_selezionato].wteleperm = create_teleperm(elenco_display[0].scr[screen_selezionato].topLevel,\
                                                           &pagine[pos_pag_new],"nome_display");\
\
                if( elenco_display[0].scr[screen_selezionato].wteleperm  > 0)\
         	   UxPopupInterface(elenco_display[0].scr[screen_selezionato].wteleperm,no_grab); \
       		}\
         \
           if( elenco_display[0].scr[screen_selezionato].wteleperm  > 0)\
	      teleperm_navigation(elenco_display[0].scr[screen_selezionato].wteleperm,&UxEnv,direction,indice,screen_selezionato,wid);\
\
	}\
\
   UxTelepermContext = UxSaveCtx;\
}\
\
\
/* routine per aprire una pagina da oggetto cambio pagina\
*/\
void teleperm_changePage(drawing,nomePag,tipoOpen)\
Widget drawing;\
char *nomePag;\
int tipoOpen;\
{\
   teleperm_chPage(teleperm,&UxEnv,drawing,nomePag,tipoOpen);\
}\
\
/* get della lista degli indici delle pagine figlie \
   della pagina di un livello dato\
*/\
int getSubLevel(OlTreeObject level,int **lista_ind,int *npag)\
{\
   int i;\
  \
   /* alloco la lista delle pagine (superdimensionata)\
      puo' contenere la lista di tutte le pagine\
   */\
   if( ((*lista_ind) = (int *)XtCalloc(totale_pagine,sizeof(int))) == NULL)\
   {\
       printf("getSubLevel ERROR in malloc: lista_ind\n");\
       return(False);;\
   }\
\
   /* get della lista della pagine figlie del livello dato\
   */ \
   if( OlTreeGetSubInfo( level,(*lista_ind) ) == True ) \
   {\
      (*npag)  = 0 ;\
      while( (*lista_ind)[ *npag ] != -1)      \
         (*npag) ++; \
   }       \
   else\
   {\
      XtFree(*lista_ind);\
      *lista_ind = NULL;\
      *npag = 0;     \
      return(False);\
   }\
\
   return(True);\
\
}\
\
\
\
/* callback per i bottoni del plantMenu (creato dinamicamente)\
   che chiama il metodo navigation passandogli l'indice di pagina da visualizzare\
*/\
static void view_fa(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)\
{\
   int indice;\
   OlTreeObject app_oltree,curr_oltree;\
   _UxCteleperm            *UxSaveCtx, *UxContext;\
\
   UxSaveCtx = UxTelepermContext;\
   UxTelepermContext = UxContext =\
                        (_UxCteleperm *) UxGetContext( UxWidget );\
\
   indice = (int)UxClientData;\
/*\
Sostituita teleperm_navigation con teleperm naviga \
*/\
   teleperm_naviga(UxWidget,GOTOPAG,indice);\
\
   UxTelepermContext = UxSaveCtx;\
}\
/*\
Callback per pulsanti di navigazione pagAllarmi\
*/\
static void command_alarm(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)\
{\
int comando;\
   _UxCteleperm            *UxSaveCtx, *UxContext;\
\
   UxSaveCtx = UxTelepermContext;\
   UxTelepermContext = UxContext =\
                        (_UxCteleperm *) UxGetContext( UxWidget );\
\
comando=(int)UxClientData;\
/*\
Spedisco comando allo Scada\
*/\
if(comando==OL_MODO_ALLARMI)\
	{\
	modoPageAll=MODO_ALLARMI;\
	}\
else if(comando==OL_MODO_ARCHIVIO)\
	{\
	modoPageAll=MODO_ARCHIVIO;\
	}\
\
\
OlCommandAllarmi(database_simulatore,comando);\
\
}\
/*\
callback per aperura pagina Allarmi da plant Menu'\
*/\
static void open_allPag_fa(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)\
{\
int indice_fa,i;\
   _UxCteleperm            *UxSaveCtx, *UxContext;\
\
   UxSaveCtx = UxTelepermContext;\
   UxTelepermContext = UxContext =\
                        (_UxCteleperm *) UxGetContext( UxWidget );\
\
\
   indice_fa = (int)UxClientData;\
\
\
/*\
Seleziono la zona di impianto solamente se posso aprire la pagina allarmi\
cioe' se la pagAll e' sullo screen selezionato o\
se la pagAll non e' ancora stata aperta\
*/\
if((allPageOnScreen==-1) || (allPageOnScreen==screen_selezionato))\
        {\
	printf("\n\n VALORE di indice_fa=%d\n\n",indice_fa);\
	for(i=0;i<NUMMAXZONE;i++)\
		{\
		if(i==indice_fa)\
			zone_status[i]=1;\
		else\
			zone_status[i]=0;\
		}\
	}\
/*\
Parte per creazione Pag Allarmi\
*/\
\
teleperm_naviga(UxWidget,GOTOPAG,INDALLPAGFROMPLANT);\
 \
}\
\
\
/*\
callback per bottone newest per pagAllarmi [n]\
*/\
static void go_newest(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)\
{\
DATI_ALLARMI_SHM allarmi,vecchi_allarmi;\
int num_tot_allarmi,old_allarmi_a;\
long n_sleep;\
time_t time_end,time_start;  /* Var per timeout */\
\
 _UxCteleperm            *UxSaveCtx, *UxContext;\
\
   UxSaveCtx = UxTelepermContext;\
   UxTelepermContext = UxContext =\
                        (_UxCteleperm *) UxGetContext( UxWidget );\
\
/*acquisisco allarmi */\
OlGetDataAllarmi(database_simulatore,&allarmi);\
\
if(modoPageAll==MODO_ALLARMI)\
	num_tot_allarmi=allarmi.num_all_da_ric;\
else num_tot_allarmi=allarmi.num_all_arc;\
\
memset(&vecchi_allarmi,0,sizeof(DATI_ALLARMI_SHM));\
old_allarmi_a=0;\
\
printf("go_newest:allarmi.num_all_da_ric=%d allarmi.num_all_arc=%d\n",allarmi.num_all_da_ric,allarmi.num_all_arc);\
/*\
Variabile ambiente per taratura tempo di sleep su lettura shm\
*/\
if( XlGetenv("N_SLEEP") != NULL )\
   n_sleep=atol(XlGetenv("N_SLEEP"));\
else\
   n_sleep=DEF_TIME_OUT_N; \
\
printf("go_newest:num_tot_allarmi=%d n_sleep=%ld\n",num_tot_allarmi,n_sleep);\
\
/*\
Finche' non sono arrivato agli allarmi piu' nuovi...\
invia comando ALLARMI_AVANTI\
*/\
time(&time_start);\
while(allarmi.allarmi_a<num_tot_allarmi)\
	{\
        time(&time_end);\
        if((time_end-time_start) > TOLERANCE_N_TIME)\
           {\
           printf("\nWARNING : Time-out elapsed \n");\
           printf("WARNING : Impossible retrieving newest Alarms\n\n");\
           break;\
           }\
/*\
printf("\ngo_newest:allarmi.allarmi_a=%d num_tot_allarmi=%d\n\n",allarmi.allarmi_a,num_tot_allarmi);\
*/\
	if((OlGetDataAllarmi(database_simulatore,&allarmi)) &&\
           (old_allarmi_a!=allarmi.allarmi_a) &&\
           (allarmi.allarmi_a<num_tot_allarmi))\
		{\
                printf("gonewest: lancio comando AVANTI\n");\
                time(&time_start);\
		if(OlCommandAllarmi(database_simulatore,OL_AVANTI_ALLARMI))\
/*\
			memcpy(&vecchi_allarmi,&allarmi,sizeof(DATI_ALLARMI_SHM));\
*/\
                        old_allarmi_a=allarmi.allarmi_a;\
		else \
			{\
			printf("WARNING : Impossible retrieving newest Alarms\n");\
			break;\
			}\
		}\
        usleep(n_sleep);\
	}\
\
printf("go_newest:exit !!!\n");\
}\
/*\
Callback per pulsanti di header per pagAllarmi\
*/\
\
static void select_zone(Widget UxWidget,XtPointer UxClientData,XtPointer UxCallbackArg)\
{\
 int zona; /* zona selezionata passata come argomanto della callback*/  \
Boolean zone_attive; /* verifico che esistano zone attive */\
int kk;\
 Pixel background_color,arm_color,top_shadow,bottom_shadow;/* Pixels per effetto "schiacciamento bottone*/\
   _UxCteleperm            *UxSaveCtx, *UxContext;\
\
\
   UxSaveCtx = UxTelepermContext;\
   UxTelepermContext = UxContext =\
                        (_UxCteleperm *) UxGetContext( UxWidget );\
\
   zona = (int)UxClientData;\
   zone_attive=False;\
\
/* \
Cambia visualizzazione bottone \
*/\
\
/* Acquisisco valori dei colori del bottone */\
\
XtVaGetValues(UxWidget,XmNarmColor,&arm_color,NULL);\
XtVaGetValues(UxWidget,XmNbackground,&background_color,NULL);\
XtVaGetValues(UxWidget,XmNtopShadowColor,&top_shadow,NULL);\
XtVaGetValues(UxWidget,XmNbottomShadowColor,&bottom_shadow,NULL);\
\
/* Setto nuovi valori del bottone (scambio bordini e sfondi)*/\
\
XtVaSetValues(UxWidget,XmNbackground,arm_color,NULL);\
XtVaSetValues(UxWidget,XmNarmColor,background_color,NULL);\
XtVaSetValues(UxWidget,XmNtopShadowColor,bottom_shadow,NULL);\
XtVaSetValues(UxWidget,XmNbottomShadowColor,top_shadow,NULL);\
\
/*Cambia lo stato della zona*/\
if(zone_status[zona]==1)\
	zone_status[zona]=0;\
else\
       {\
	zone_status[zona]=1;\
        last_zone_pressed=zona;    /* tiene conto della ultima zona premuta X due\
                                    utenti che selezionano la stessa zona */\
       }\
printf("zona premuta=%d\n",zona);\
\
/*\
Verifico se esistono zone attive\
*/\
for(kk=1;kk<NUMMAXZONE;kk++)\
          {\
          if(zone_status[kk]==1)\
               {\
              zone_attive=True; /* almeno una zona e' attiva */\
              break;\
              }\
          }\
/* Se la zona non e' stata selezionata da altro utente */\
if(zone_ko==-1)\
	{\
	if((modoPageAll== MODO_ALLARMI) && zone_attive)\
 		{\
		OlTeleperm_richiediAllarmi(database_simulatore,zone_status);\
		}\
	else if((modoPageAll== MODO_ARCHIVIO) && zone_attive)\
		{\
		/* Sospendo refresh per evitare visualizzazione dopo OlTeleperm_richiediAllarmi */\
		XtRemoveTimeOut(timer_timerefreshAll);\
		\
		OlTeleperm_richiediAllarmi(database_simulatore,zone_status);\
		OlCommandAllarmi(database_simulatore,OL_MODO_ARCHIVIO);	\
		/* Rimetto il Refresh */\
		teleperm_refreshAllPage(all_form_topLevelShell);\
		}\
       } /* end if(zone_ko==-1) */\
\
   UxTelepermContext = UxSaveCtx;\
}\
\
/* setta il titolo della pagina nella titleAreaForm\
   Il titolo impostato equivale alla risorsa della pagina top_descrizione\
   che e' presente come stringa nella struttura della pagina\
*/\
void set_titleLabel(char *descr)\
{\
   XmString xstr;\
  \
   xstr = XmStringCreateSimple(descr);   \
   set_something(titleLabel,XmNlabelString,xstr);\
   XmStringFree(xstr);\
}\
\
/* interfaccia per l'esterno del metodo\
*/\
int teleperm_IcoSelect( Widget UxThis, Environment *penv, Widget w)\
{\
   teleperm_WidgetSelect(UxThis,penv,w);\
}\
/* \
Interfaccia per l'esterno del metodo\
*/\
int teleperm_ApplSelect( Widget UxThis, Environment *penv, Widget w)\
{\
   teleperm_application(UxThis,penv,w);\
}\
int recognize_fa()\
{\
int indice_fa,i;\
char *str,appo[200];\
/*******************************************************\
Ricavo la lista delle functional Area\
Vado a vedere quali nodi del primo livello sono attivi\
-> abilito le corrispondenti fa\
********************************************************/\
memset(selectable_zone,0,NUMMAXZONE*sizeof(int));\
num_telepag=0;\
if( getSubLevel(root_oltree,&lista_fa,&num_fa) != True )\
    return;\
printf("numero di fa=%d\n",num_fa);\
/*\
Vado a determinare le zone attive\
*/\
if(num_fa)\
        for(i=0;i<num_fa;i++)\
                {\
		if( !PagIsTeleperm(pagine[lista_fa[i]]) )\
                        {\
                         printf("###############################################################\n");\
                         printf("SEVERE ERROR: functional area associated with a notteleperm page\n");\
                         printf(" ERROR: functional area=%d -- notteleperm page=%s\n",i,pagine[lista_fa[i]].nome);\
                         printf("###############################################################\n");\
                        return;\
                        }\
                strcpy(appo,pagine[lista_fa[i]].gerarchia);\
                strtok(appo,",");\
                str=strtok((char *)NULL,",");\
                if(!str)\
                        {\
                        printf("ERROR: hierarchy function Area page not correct!\n");\
                        return(-1);\
                        }\
                indice_fa=atoi(str);\
                /*\
                Associo l' indice del nodo nell' elenco pagine, alla zona\
                abilitata\
                */\
                if(indice_fa)  /* Escludo la zona 0 */\
			{\
                        selectable_zone[indice_fa]=lista_fa[i];\
			num_telepag++;\
			if(indice_fa>last_indice_fa)\
				last_indice_fa=indice_fa;\
			/*printf("num_telepag=%d lista_fa[%d]=%d indice_fa=%d\n",num_telepag,i,lista_fa[i],indice_fa);*/\
			}\
                }\
                  \
printf("num_telepag=%d \n",num_telepag);\
printf("last_indice_fa=%d \n",last_indice_fa);\
/* \
Parte che decide quante righe nella parte header AllPag devo utilizzare \
*/ \
if((last_indice_fa>0) && (last_indice_fa<=18))\
      {\
      num_zone=HEADERTRERIGHE;   /* tre righe */\
      }\
else if((last_indice_fa>18) && (last_indice_fa<25))\
      {\
      num_zone=HEADERQUATTRORIGHE;     /* 4 righe */\
      }\
else if(( last_indice_fa>25) && (last_indice_fa<31))\
      {\
      num_zone=HEADERCINQUERIGHE;    /* 5 righe di bottoni */\
      }                 \
XtFree(lista_fa);\
return(1);                                \
}\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\

*teleperm_moveright.class: method
*teleperm_moveright.name: moveright
*teleperm_moveright.parent: teleperm
*teleperm_moveright.methodType: int
*teleperm_moveright.methodArgs: int *pcurr;\
int *pnew;\

*teleperm_moveright.methodBody: int progr;\
OlTreeObject curr_oltree;\
\
\
/* recupero le informiazioni sulla pagina corrente\
*/\
if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcurr,Pag->gerarchia) == False )\
{\
   printf("Error retrieving hierarchy information for this page\n");\
   return(False);\
}\
\
\
/* recupero le informazioni sulla pagina a destra\
*/\
OlTreeGetRight(curr_oltree,pnew);\
\
\
return(True);
*teleperm_moveright.arguments: pcurr, pnew
*teleperm_moveright.pcurr.def: "int", "*%pcurr%"
*teleperm_moveright.pnew.def: "int", "*%pnew%"

*teleperm_moveup.class: method
*teleperm_moveup.name: moveup
*teleperm_moveup.parent: teleperm
*teleperm_moveup.methodType: int
*teleperm_moveup.methodArgs: int *pcurr;\
int *pnew;\

*teleperm_moveup.methodBody: OlTreeObject curr_oltree;\
int progr;\
\
\
/* recupero le informiazioni sulla pagina corrente\
*/\
if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcurr,Pag->gerarchia) == False )\
{\
   printf("Error retrieving hierarchy information for this page\n");\
   return(False);\
}\
\
/* \
recupero le informazioni sulla pagina parent\
*/\
OlTreeGetTop(curr_oltree,pnew);\
\
\
return(True);
*teleperm_moveup.arguments: pcurr, pnew
*teleperm_moveup.pcurr.def: "int", "*%pcurr%"
*teleperm_moveup.pnew.def: "int", "*%pnew%"

*teleperm_moveleft.class: method
*teleperm_moveleft.name: moveleft
*teleperm_moveleft.parent: teleperm
*teleperm_moveleft.methodType: int
*teleperm_moveleft.methodArgs: int *pcurr;\
int *pnew;\

*teleperm_moveleft.methodBody: OlTreeObject curr_oltree;\
int progr;\
/* recupero le informazioni sulla pagina corrente\
*/\
if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcurr,Pag->gerarchia) == False )\
{\
   printf("Error retrieving hierarchy information for this page\n");\
   return(False);\
}\
\
\
/* recupero le informazioni sulla pagina a destra\
*/\
OlTreeGetLeft(curr_oltree,pnew);\
\
\
return(True);
*teleperm_moveleft.arguments: pcurr, pnew
*teleperm_moveleft.pcurr.def: "int", "*%pcurr%"
*teleperm_moveleft.pnew.def: "int", "*%pnew%"

*teleperm_closePag.class: method
*teleperm_closePag.name: closePag
*teleperm_closePag.parent: teleperm
*teleperm_closePag.methodType: void
*teleperm_closePag.methodArgs: Widget w;\

*teleperm_closePag.methodBody: extern Boolean OW_close();\
int i;\
char *envvar;\
char comando[FILENAME_MAX*2];\
char appo[100];\
int localScreen=0;\
\
        /* elimino le OW aperte\
        */\
        teleperm_closeOW(teleperm,&UxEnv);\
        /*\
        Se ho aperto la pagina allarmi sullo Screen da chiudere -> la chiudo\
        */\
        localScreen=XScreenNumberOfScreen(XtScreen(UxThis));\
\
        if( localScreen == allPageOnScreen )\
                {\
                teleperm_close_allPage(elenco_display[0].scr[allPageOnScreen].wteleperm,&UxEnv);\
                allPageOnScreen=SINCROCLOSEALLPAG;\
                }\
        /* libero la pagina teleperm\
        */\
        /*\
        elenco_display[0].scr[screen_selezionato].wteleperm = NULL;\
        */\
        /* reset dell'indice di pagina\
           Tengo conto dell'effettico screen sul quale e' visualizzata\
        */\
\
        /* chiudendo la pagina devo aggiornare\
            la variabile screen_selezionato sull'altro screen\
        */\
        if( screen_selezionato == 1)\
           screen_selezionato = 0;\
        else\
           screen_selezionato = 1;\
\
                XtRemoveTimeOut(timer_timerefresh);\
        if((allPageOnScreen!=SINCROCLOSEALLPAG )|| (allPageOnScreen==-1))\
                {\
\
                DelElencoPagine(key_refresh, drawingArea);\
\
                XSync(XtDisplay(w),False);\
                XtRemoveTimeOut(timer_refresh);\
                XtFree(lista_wid);\
                }\
        else if(allPageOnScreen==SINCROCLOSEALLPAG)\
           allPageOnScreen=-1;\
\
        /*\
        Rimuovi timeout dei Cai sul 'costolone' pag teleperm solo se lo scada e' agganciato\
        */\
        if(scada_on)\
                XtRemoveTimeOut(timer_timerefreshCaiHeader);\
\
        if(pullDownActive)\
                {\
                if(scada_on)\
                        XtRemoveTimeOut(timer_timerefreshCai);\
                UxDestroyInterface(*pullDownActive);\
                if(scada_on)\
                   {\
                    XtFree(listaCaiVr);\
                    XtFree(listaCaiFormVr);\
                    XtFree(listaPushButton);\
                   }\
                pullDownActive=NULL;\
                }\
        elenco_display[0].scr[DefaultScreen(XtDisplay(teleperm))].wteleperm = NULL;\
\
        prima_apertura_all=True;\
\
        if(drawing_pixmap)\
                {\
                XFreePixmap(XtDisplay(teleperm),drawing_pixmap);\
                drawing_pixmap=0;\
                }\
\
        UxDestroyInterface( teleperm );\
\
/*\
Eliminazione eventuali file tmp per info da teleperm\
*/\
if(InfoUsed)\
   {  \
   strcpy(comando,"rm ");\
   if((envvar=(char *) getenv("TMPDIR"))==NULL)\
      {\
      strcat(comando,"/tmp");\
      }\
   else\
      strcat(comando,envvar);\
\
   strcat(comando,TMPINFOFILE);\
   sprintf(appo,"%d",getpid());\
   strcat(comando,appo);\
   strcat(comando,"_");\
   strcat(comando,"*");\
   system(comando);\
   \
} /* end if InfoUsed */\
/*\
   system(comando);\
*/
*teleperm_closePag.arguments: w
*teleperm_closePag.w.def: "Widget", "%w%"

*teleperm_popupPage.class: method
*teleperm_popupPage.name: popupPage
*teleperm_popupPage.parent: teleperm
*teleperm_popupPage.methodType: int
*teleperm_popupPage.methodArgs: unsigned char *nomePag;\
int tipo;\

*teleperm_popupPage.methodBody: /* questo metodo effettua il popup di una pagina \
   sopra una pagina di tipo teleperm\
*/\
\
return(True);
*teleperm_popupPage.arguments: nomePag, tipo
*teleperm_popupPage.nomePag.def: "unsigned char", "*%nomePag%"
*teleperm_popupPage.tipo.def: "int", "%tipo%"

*teleperm_decorationToggle.class: method
*teleperm_decorationToggle.name: decorationToggle
*teleperm_decorationToggle.parent: teleperm
*teleperm_decorationToggle.methodType: void
*teleperm_decorationToggle.methodArgs: 
*teleperm_decorationToggle.methodBody: int decorOn;\
char *tipo;\
XrmValue value;\
char risorsa[50];\
char appo[50];\
\
sprintf(risorsa,"teleperm.decorazioni");\
XrmGetResource(UxDisplay->db,risorsa,(char*)NULL,&tipo,&value);\
strncpy(appo,value.addr,(int)value.size);\
decorOn = atoi(appo);\
\
if( decorOn == 0) \
{\
   /* questo mette solo un sottile bordino \
   XtVaSetValues(UxThis,XmNmwmDecorations,MWM_DECOR_BORDER,NULL);\
   */\
   /* elimina tutte le decorazioni\
   */\
   XtVaSetValues(UxThis,XmNmwmDecorations,0,NULL);\
}\
else\
{\
   printf("\n\nWARNING you have application resource 'decoration' set to 1\n");\
   printf("in this mode you can resize this shell\n");\
   printf("change $XAPPLRESDIR/run_time resource file for change\n\n\n");\
\
\
   XtVaSetValues( UxThis,\
                  XmNmwmDecorations,MWM_DECOR_ALL,\
                  XmNallowShellResize, True,\
                  XmNminWidth, 400,\
                  XmNminHeight, 400,\
                  NULL);\
                     \
}\


*teleperm_previousPag.class: method
*teleperm_previousPag.name: previousPag
*teleperm_previousPag.parent: teleperm
*teleperm_previousPag.methodType: int
*teleperm_previousPag.methodArgs: int *pcur;\
int *pnew;\

*teleperm_previousPag.methodBody: /* questo metodo permette di rivisualizzare la penultima pagina visualizzata\
   Attivando due volte consecutove questo metodo devo ritornare sulla prima pagina \
   cha ha attivato il metodo (circolare su due pagine)\
*/\
\
int prev;\
\
printf("METODO PREVIOUS\n");\
\
\
if( pos_pag_curr == pos_pag_new )\
   return(True);\
\
(*pcur) = pos_pag_new;\
(*pnew) = pos_pag_curr;\
\
return(True);\

*teleperm_previousPag.arguments: pcur, pnew
*teleperm_previousPag.pcur.def: "int", "*%pcur%"
*teleperm_previousPag.pnew.def: "int", "*%pnew%"

*teleperm_chPage.class: method
*teleperm_chPage.name: chPage
*teleperm_chPage.parent: teleperm
*teleperm_chPage.methodType: void
*teleperm_chPage.methodArgs: Widget w;\
unsigned char *nomePg;\
int tipoApertura;\

*teleperm_chPage.methodBody: int ind_pag;  /* indice della pagina nel vettore delle pagine */\
Widget newPag; /* top widget nuova pagina */\
\
if( !strlen(nomePg) ) \
   return;\
\
/* apertura di una pagina\
*/\
if( (tipoApertura != CLOSE_PAGE) || (tipoApertura != CHANGE_PAGE) )\
{\
   /* la pagina non e' gia' aperta\
   */\
   if( !PaginaAperta(w,nomePg) )\
   {\
      if( !CanOpenPage(w) )\
         return;\
\
      printf("Abilitato ad aprire la pagina\n");\
\
      ind_pag=NumeroPagina(nomePg);\
    \
      printf("nella lista la pagina e' %s\n",pagine[ind_pag].nome);\
\
      /* verifico il tipo di pagina e la apro. \
         Nota, la pagina corrente e la nuova pagina hanno lo stesso parent.\
      */\
      if( strcmp(pagine[ind_pag].tipo,"Sinottico") == 0)\
         newPag = create_topLevelShell1(nomePg,XtParent(UxThis),nome_display,pagine[ind_pag].sfondo);\
      if( strcmp(pagine[ind_pag].tipo,"Stazioni") == 0)\
         newPag = popup_topLevelShellStaz(nomePg,XtParent(UxThis),nome_display,pagine[ind_pag].sfondo);\
\
      if( newPag == NULL )\
      {\
         popup_errorDialog("Errore Creazione pagina",w);\
         return;\
      }\
   }\
   else\
      printf("La pagina sembra gia aperta\n");\
}\
else\
   printf("tipoApertura non e' diverso da ClosePage\n");
*teleperm_chPage.arguments: w, nomePg, tipoApertura
*teleperm_chPage.w.def: "Widget", "%w%"
*teleperm_chPage.nomePg.def: "unsigned char", "*%nomePg%"
*teleperm_chPage.tipoApertura.def: "int", "%tipoApertura%"

*teleperm_dispData.class: method
*teleperm_dispData.name: dispData
*teleperm_dispData.parent: teleperm
*teleperm_dispData.methodType: int
*teleperm_dispData.methodArgs: 
*teleperm_dispData.methodBody: int dd,mm,yy;\
char data_oggi[20];\
XmString xstr;\
\
if( data(&dd,&mm,&yy) == 1)\
{\
   sprintf(data_oggi,"%d-%d-%d",dd,mm,yy);\
\
   xstr = XmStringCreateSimple(data_oggi);\
\
   set_something(Data,XmNlabelString,xstr);\
   \
   XmStringFree(xstr); \
\
   return(True);\
}\
else\
   return(False);\


*teleperm_dispTime.class: method
*teleperm_dispTime.name: dispTime
*teleperm_dispTime.parent: teleperm
*teleperm_dispTime.methodType: int
*teleperm_dispTime.methodArgs: float tempoSim;\

*teleperm_dispTime.methodBody: extern void conv_time();\
char ora[20];\
XmString xstr;\
\
conv_time(tempoSim,ora);\
\
xstr = XmStringCreateSimple(ora);\
set_something(Ora,XmNlabelString,xstr);\
XmStringFree(xstr);\
return(True);
*teleperm_dispTime.arguments: tempoSim
*teleperm_dispTime.tempoSim.def: "float", "%tempoSim%"

*teleperm_vertHier.class: method
*teleperm_vertHier.name: vertHier
*teleperm_vertHier.parent: teleperm
*teleperm_vertHier.methodType: int
*teleperm_vertHier.methodArgs: int **lista_ind;\
int *npag;\

*teleperm_vertHier.methodBody: OlTreeObject curr_oltree;\
int pcur,i,progr;\
\
 \
if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,&pcur,Pag->gerarchia) == False )\
{\
      printf("Error retrieving hierarchy information for this page\n");\
      (*lista_ind) = NULL;\
      (*npag) = 0;\
      return(False);\
}\
\
\
\
   /* recupero il parent del livello attuale \
      e la lista dei figli, ottengo cosi la lista verticale della gerarchia\
   */\
\
   getSubLevel( curr_oltree, lista_ind, npag);\
\
 \

*teleperm_vertHier.arguments: lista_ind, npag
*teleperm_vertHier.lista_ind.def: "int", "**%lista_ind%"
*teleperm_vertHier.npag.def: "int", "*%npag%"

*teleperm_orizHier.class: method
*teleperm_orizHier.name: orizHier
*teleperm_orizHier.parent: teleperm
*teleperm_orizHier.methodType: int
*teleperm_orizHier.methodArgs: int **lista_ind;\
int *npag;\

*teleperm_orizHier.methodBody: OlTreeObject curr_oltree;\
int i;\
int pcur,parente,progr;\
\
 \
/* recupero il parent della pagina attuale\
   e la lista dei figli, ottengo cosi la lista orizzontale della gerarchia\
   NOTA Pag e' il puntatore alla pagina correntemente visualizzata e la\
   sua definizione sta nel Context.\
*/\
\
/* recupero le informazioni sulla pagina corrente\
*/\
if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,&pcur,Pag->gerarchia) == False )\
{\
      printf("Error retrieving hierarchy information for this page\n");\
      (*lista_ind) = NULL;\
      (*npag) = 0;\
      return(False);\
}\
\
if( curr_oltree == root_oltree )\
{\
      (*lista_ind) = NULL;\
      (*npag) = 0; \
      return(True);\
}    \
\
/* recupero l'indice del padre \
*/\
OlTreeGetTop( curr_oltree, &parente);\
\
 \
/* recupero le informazioni sul padre\
*/ \
if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,&pcur,pagine[parente].gerarchia) == False )\
{\
      printf("Error retrieving hierarchy information for this page\n");      \
      return(False);\
}\
\
/* recupero lista indici pagine figlie, cioe' la lista orizzontale\
*/\
if( getSubLevel( curr_oltree, lista_ind, npag) != True)\
{\
   printf("DEBUG orizHier metod no SubLevel\n");\
   return(False);\
}\
\
return(True);\

*teleperm_orizHier.arguments: lista_ind, npag
*teleperm_orizHier.lista_ind.def: "int", "**%lista_ind%"
*teleperm_orizHier.npag.def: "int", "*%npag%"

*teleperm_aggTitleArea.class: method
*teleperm_aggTitleArea.name: aggTitleArea
*teleperm_aggTitleArea.parent: teleperm
*teleperm_aggTitleArea.methodType: int
*teleperm_aggTitleArea.methodArgs: 
*teleperm_aggTitleArea.methodBody: /* set title area\
*/\
int npag,*lista_ind;\
\
set_titleLabel(Pag->descrizione);\
\
/* set menu jerarqia horizontal\
*/\
teleperm_orizHier(teleperm,&UxEnv,&lista_ind,&npag);\
if(  npag> 0 )\
   {\
   set_something(orizHierButton,XmNsensitive,True); \
   \
   }\
else\
   set_something(orizHierButton,XmNsensitive,False); \
\
if(lista_ind)\
   XtFree(lista_ind);\
\
/* set menu jerarqia vertical\
*/\
teleperm_vertHier(teleperm,&UxEnv,&lista_ind,&npag);\
if(  npag> 0 )\
   { \
   set_something(vertHierButton,XmNsensitive,True);   \
   \
   }\
else\
   set_something(vertHierButton,XmNsensitive,False);   \
if(lista_ind)\
   XtFree(lista_ind);\
\
return(True);\


*teleperm_aggHeaderArea.class: method
*teleperm_aggHeaderArea.name: aggHeaderArea
*teleperm_aggHeaderArea.parent: teleperm
*teleperm_aggHeaderArea.methodType: int
*teleperm_aggHeaderArea.methodArgs: 
*teleperm_aggHeaderArea.methodBody: teleperm_dispData(teleperm,&UxEnv);\
/*\
teleperm_plantMenu(teleperm,&UxEnv);\
*/\
\


*teleperm_navigation.class: method
*teleperm_navigation.name: navigation
*teleperm_navigation.parent: teleperm
*teleperm_navigation.methodType: int
*teleperm_navigation.methodArgs: int direction;\
int pag_ind;\
int screen_selected;\
Widget calling;\

*teleperm_navigation.methodBody: /*\
Come primo parametro viene passata l' interfaccia su cui\
aprire una pagina.\
Come 4o parametro (screen_selected) lo screen su cui verra' visualizzata la pag\
Come 5o parametro (calling) un widget appartenente alla interfaccia chiamante\
*/\
\
\
/*\
N.B.\
 poslocal contiene la pagina attualmente visualizzata su UxThis \
*/\
int retval,poscurr,posnew,poslocal,i;\
extern int num_el_pagine;\
extern PAGINE_APERTE *el_pagine;\
\
\
poslocal= pos_pag_new;\
poscurr = pos_pag_curr;\
posnew = pos_pag_new;\
\
/*\
printf("\n\nNAVIGATION numero_screen=%d allPageOn=%d prevAll=%d\n\n",numero_screen,allPageOnScreen,prevAll);  \
printf("\n\nNAVIGATION pos_pag_new=%d pos_pag_curr=%d \n\n",pos_pag_new,pos_pag_curr);\
*/\
/*\
Acquisisco informazioni dalla interfaccia chiamante\
*/\
switch( direction )\
{\
   case LEFT:\
      retval = teleperm_moveleft(calling,&UxEnv,&poscurr,&posnew);\
   break;\
   case RIGTH:\
      retval = teleperm_moveright(calling,&UxEnv,&poscurr,&posnew);\
   break;\
   case UP:\
      retval = teleperm_moveup(calling,&UxEnv,&poscurr,&posnew);\
   break;\
   case PREVIOUS:\
      retval = teleperm_previousPag(calling,&UxEnv,&poscurr,&posnew);\
   break; \
   case PLANT_OVW:\
      retval = teleperm_moveroot(calling,&UxEnv,&poscurr,&posnew);\
   break;\
   case GOTOPAG:\
      retval = teleperm_gotopag(calling,&UxEnv,&poscurr,&posnew,pag_ind);\
   break;\
}\
\
if( retval == False )\
{\
   printf("telperm_navigation: direction = %d nothing on this direction\n",direction);\
   return(False);\
}\
\
\
\
\
/*\
printf("\n\n NAVIGATION: valori di posnew=%d e poscurr=%d screen_selected=%d allPageOnScreen=%d\n\n",pos_pag_new,pos_pag_curr,screen_selected,allPageOnScreen);\
*/\
/* \
Devo fare una distinzione :\
INDALLPAG e' un indice fitttizio per pag allarmi chiamata da isa\
INDALLPAGFROMPLANT e' un indice fitttizio per pag allarmi chiamata da plant Menu'\
Segue una serie di controlli per gestire eccezioni su apertura da pagAll\
*/ \
\
if((posnew==INDALLPAG) && (allPageOnScreen!=-1)  ) /* tentativo di riaprire pag allarmi da isa */\
 	return(False);\
if(posnew==INDALLPAGFROMPLANT)  /* tentativo di aprire pag allarmi da plantMenu */\
	{\
	posnew=INDALLPAG;			        /* Controlli su apertura pagAll da plantMenu end -> */\
						        /* segnalo che devo aprire una pagAllarmi */\
	if(allPageOnScreen!=-1) 			/* pagAll gia aperta */\
	   if(screen_selected!=allPageOnScreen)         /* tentativo di aprira allPag da planMenu su uno screen */\
		   return(False);                       /* con pag allarmi gia' aperta su un altro -> VIETATO !*/ \
	}\
\
\
         /*\
         Blocco per la gestione della apertura della pagina allarmi di \
         tipo non-Teleperm. Viene aperta se la pagAll-teleperm non e' gia' aperta\
         Se la pagAll-Teleperm e' gia' aperta, viene impedito di aprire una pagina\
         di tipo Teleperm con l' oggetto XlAllarmi\
         */ \
\
         if( (allPageOnScreen!=-1) && (posnew!=INDALLPAG))       \
           {\
            printf("DEBUG: Effettuo confronto con =%s \n",pagine[posnew].nome);\
            if( teleperm_isOldAlarmPage(UxThis,pEnv,pagine[posnew].nome ))\
              {\
              return(False);\
              }\
            }\
/*\
Controlli su aperture pagine normali \
*/\
\
if(posnew!=INDALLPAG)\
  if( el_pagine != NULL)\
   	for(i=0;i<num_el_pagine;i++)\
   	  { \
      	    if( !strcmp(el_pagine[i].nome,pagine[posnew].nome) )\
      	     {\
             printf("DEBUG:posnew=%s  el_pagine=%s\n",pagine[posnew].nome,el_pagine[i].nome);\
             return(False);\
      	     }       \
   	  }\
\
/* GESTIONE DUE SCREEN\
   chiamo il METODO ridisegna per il refresh della sola drawing area\
   oppure creo la interfaccia su l'altro screen\
\
printf("navigation screen selezionato - %d\n",screen_selected);\
printf("wteleperm[0] - %d\n",elenco_display[0].scr[0].wteleperm);\
printf("wteleperm[1] - %d\n",elenco_display[0].scr[1].wteleperm);\
*/\
/*	printf("\n\nNAVIGATION MIDL posnew=%d poscurr=%d \n\n",posnew,poscurr); */\
\
if( elenco_display[0].scr[screen_selected].wteleperm != NULL )\
{\
/*printf("\n\n elenco_display!= NULL%d\n\n",posnew);*/\
  /* chiudo le operating window\
  */ \
  teleperm_closeOW(elenco_display[0].scr[screen_selected].wteleperm,&UxEnv);\
  \
  if(allPageOnScreen!=-1 && screen_selected==allPageOnScreen)\
	{\
/*printf("\n\nCHIUDO ALLPAG\n\n");*/\
	teleperm_close_allPage(elenco_display[0].scr[allPageOnScreen].wteleperm,&UxEnv);\
	allPageOnScreen=SINCROCLOSEALLPAG;\
	}\
	\
  \
  if(posnew==INDALLPAG)\
	{\
\
/*printf("\n\nCREO ALLPAG con ridisegna\n\n");*/\
\
	if(teleperm_create_allPage(elenco_display[0].scr[screen_selected].wteleperm,&UxEnv)<0)\
           {\
           posnew=poscurr;\
           fprintf(stderr,"\n Impossible to open All page \n");\
           }\
        else\
	   allPageOnScreen=screen_selected;\
	}\
  else\
	{\
	/*printf("\n\nRIDISEGNO %d\n\n",posnew);*/\
        teleperm_ridisegna(elenco_display[0].scr[screen_selected].wteleperm,&UxEnv,posnew);\
	if(allPageOnScreen==SINCROCLOSEALLPAG)  /* vedo se e' stata appena chiusa la pagALL */\
		   allPageOnScreen=-1;\
\
        /*\
        Se contiene XlAllarmi, alla prossima riapertura della pagina Allarmi \
        si dovra' richiedere gli allarmi per rinfrescare i valori sull' header della \
        pagina allarmi di tipo Teleperm\
        */\
        if( teleperm_isOldAlarmPage(UxThis,pEnv,pagine[posnew].nome) )\
           prima_apertura_all=True;\
\
	}\
}\
else\
{\
printf("\n\n FORBIDDEN OPERATION \n\n ");\
}\
/*printf("\n\nNAVIGATION FINAL pos_pag_new=%d pos_pag_curr=%d \n\n",posnew,poscurr);*/\
\
\
if( poscurr != posnew )\
  {\
/* Aggiornamento indici */\
      pos_pag_curr = poslocal;\
      pos_pag_new = posnew;\
  }\
/*\
Destroy previous page pullDown menu\
*/\
\
if(pullDownActive)\
	{\
	if(scada_on)\
           XtRemoveTimeOut(timer_timerefreshCai);\
           \
           \
	UxDestroyInterface(*pullDownActive);\
        if(scada_on)\
           {\
            XtFree(listaCaiVr);\
            XtFree(listaCaiFormVr);\
            XtFree(listaPushButton);\
           }\
	pullDownActive=NULL;\
	}\
\
return(True);\
\
\

*teleperm_navigation.arguments: direction, pag_ind, screen_selected, calling
*teleperm_navigation.direction.def: "int", "%direction%"
*teleperm_navigation.pag_ind.def: "int", "%pag_ind%"
*teleperm_navigation.screen_selected.def: "int", "%screen_selected%"
*teleperm_navigation.calling.def: "Widget", "%calling%"

*teleperm_ridisegna.class: method
*teleperm_ridisegna.name: ridisegna
*teleperm_ridisegna.parent: teleperm
*teleperm_ridisegna.methodType: int
*teleperm_ridisegna.methodArgs: int ind_pag;\

*teleperm_ridisegna.methodBody: /* metodo che distrugge la drawing area e la ricrea\
   la pagina da ricreare e' individuata dal puntatore Pag \
   che e' definito nel context e che viene svicciato\
   dalle funzioni di navigazione \
*/\
\
extern void exposeCB_drawingArea();\
char nome_pag[255];\
\
  \
/* variabili per risorse della drawing area\
*/\
int drawing_width,drawing_height;\
Pixel *drawing_background;\
Pixmap pix;\
\
\
/* per gestione sinottico\
*/\
int dim[4];\
int num_b;\
extern Boolean leggi_file_bck();\
\
\
 \
Pag = (AN_PAG *)&pagine[ind_pag]; \
\
 \
/* nome del file delle risorse della pagina da caricare\
*/\
sprintf(nome_pag,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),Pag->nome);\
\
\
/* carico il db della pagina\
*/\
\
if( (PagDb = XrmGetFileDatabase(nome_pag)) == NULL )\
{\
   printf("Error. Cannot open page %s\n",nome_pag);\
   return(1);\
}\
\
/* prima di switchare il db delle risorse su quello della\
   pagina in apertura devo ditruggere il precedente.\
   Per fare cio' devo distruggere anche i cai posti nell'header\
   che fanno riferimento alle risorse del vecchio db.\
   Ricreo quindi i cai header dopo avere ripristinato il nuovo\
   db delle risorse\
*/\
\
/* rimuovo il timeout dei cai header prima della destroy del database\
   delle risorse\
   (se sono stati creati, vale a dire se scada_on)\
*/\
if( scada_on)\
{\
   XtRemoveTimeOut(timer_timerefreshCaiHeader);\
\
/* distruggo i cai nell'header\
*/\
   XtDestroyWidget(listaCaiHeader[0]);\
   XtDestroyWidget(listaCaiHeader[1]);\
   XtDestroyWidget(listaCaiHeader[2]);\
   XtDestroyWidget(listaCaiHeader[3]);\
   XtDestroyWidget(listaCaiHeader[4]);\
}\
\
/* distruggo il db delle risorse precedente\
*/\
XrmDestroyDatabase( (Display *)(XtDisplay(UxThis))->db);\
\
\
/*\
Combino database della applicazione con quello della pagina \
*/\
XrmCombineFileDatabase("ApplDb.res",&PagDb,True);\
/* setto il display su PagDb\
*/\
XrmSetDatabase(XtDisplay(teleperm),PagDb);\
\
/* ricreo i caiHeader\
*/\
if( scada_on )\
   teleperm_createCaiHeader(UxThis,&UxEnv);\
\
/* mi serve solo per caricare il time_ref\
*/\
if(!GetResTopLevel(UxParent,&top_x,&top_y,&top_width,&top_height,&time_ref,\
		&top_tipo,&top_descrizione))\
	return(False);\
/*\
 Se nella pagina visualizzata era presente un pixmap di sfondo\
 lo libera\
*/\
if(drawing_pixmap)\
	{\
	XFreePixmap(XtDisplay(teleperm),drawing_pixmap);\
	drawing_pixmap=0;\
	}\
/* recupero le risorse della drawing area\
*/\
if(!GetResDrawing(UxParent,&drawing_width,&drawing_height,&drawing_background, &drawing_pixmap))\
   return(1);\
\
/* aggiornamento elenchi pagine per refresh\
*/\
if(allPageOnScreen!=SINCROCLOSEALLPAG)  /* Se pagina allarmi era attiva non distruggere drawing area inesistenti*/\
	{\
	DelElencoPagine(key_refresh, drawingArea);\
	XSync(XtDisplay(drawingArea),False);\
	XtRemoveTimeOut(timer_refresh);\
        XtFree(lista_wid);\
	}\
/* inizializza la regione di ridisegno\
*/\
\
/*\
Devo discriminare fra pagina allarmi e altri tipi di pagina\
*/\
\
\
\
if( Pag->sfondo == NULL)\
   leggi_file_bck(UxParent,Pag->nome,"bkg",&(Pag->sfondo),dim);\
else  \
   AllocaColoriSfondo(UxParent,Pag->sfondo);\
\
\
region_sin=NULL;\
\
/* distuggo la drawing area\
*/\
if(allPageOnScreen!=SINCROCLOSEALLPAG)\
	XtDestroyWidget( drawingArea);\
\
/* creo la nuova drawing area ignorando le dimensioni\
   presenti nel file delle risorse\
   ma gestendo gli attachment \
   le dimensioni della drawing area sono quindi \
   width = width del form genitore\
   height = heigth del form genitore - TopOffset  - BottomOffset\
   y = y del genitore + TopOffset\
    \
*/\
drawingArea = XtVaCreateManagedWidget( "drawingArea",\
                        xmDrawingAreaWidgetClass,\
                        formTop,\
                        XmNresizePolicy, XmRESIZE_NONE,\
                        XmNbottomAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        XmNrightAttachment, XmATTACH_FORM,\
                        XmNtopAttachment, XmATTACH_FORM,\
                        XmNtopOffset, 60,\
                        XmNbottomOffset, 35,\
                        XmNmarginHeight, 0,\
                        XmNmarginWidth, 0,\
                        NULL );\
/* \
   setto il background della drawingArea\
*/\
if(drawing_pixmap)\
       set_something(drawingArea,XmNbackgroundPixmap,drawing_pixmap);\
else\
	set_something(drawingArea,XmNbackground,drawing_background);\
/*\
   set callback per ridisegno background\
*/\
XtAddCallback( drawingArea, XmNexposeCallback,\
                (XtCallbackProc) exposeCB_drawingArea,\
                (XtPointer) UxTelepermContext );\
\
\
UxPutContext( drawingArea, (char *) UxTelepermContext );\
\
/* creazione di tutti gli widget della drawing area\
*/\
if(!CreaPagina(drawingArea,&lista_wid, &num_wid))\
  return(1);\
\
/* aggiorno la title area\
*/\
if( teleperm_aggTitleArea(teleperm,&UxEnv) == False ) \
   printf("Aggiornamento title Area non riuscito correttamente\n");\
\
\
if((key_refresh=InsElencoPagine(Pag->nome,lista_wid,num_wid,time_ref)) == -1)\
return(1);\
/*\
Aggiorno vecchio indice della pagina \
*/\
\
timer_refresh = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (teleperm),\
            (unsigned long) (time_ref*100) ,teleperm_refreshPag, teleperm );\
\
\
return(0);
*teleperm_ridisegna.arguments: ind_pag
*teleperm_ridisegna.ind_pag.def: "int", "%ind_pag%"

*teleperm_moveroot.class: method
*teleperm_moveroot.name: moveroot
*teleperm_moveroot.parent: teleperm
*teleperm_moveroot.methodType: int
*teleperm_moveroot.methodArgs: int *pcurr;\
int *pnew;\

*teleperm_moveroot.methodBody: OlTreeObject curr_oltree;\
int progr,i;\
\
/* recupero l'indice relativo all root\
   e se non ci sono errori aggiorno il puntatore\
   pcur per la gestione del previous\
*/\
\
if( OlTreeGetPosInfo(root_oltree,pnew) == False )\
   return(False);\
\
*pcurr = pos_pag_new;\
\
#ifdef PROVO_A_NON_FARLO\
/* recupero le informazioni sulla pagina corrente\
*/\
if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcurr,Pag->gerarchia) == False )\
{\
\
   /* 20-6-97 carlo gestione pagine fuori gerarchia\
   printf("Error retrieving hierarchy information for this page\n");\
   return(False);\
   */\
\
   for(i=0;i<totale_pagine;i++)\
      if( strcmp(pagine[i].gerarchia,"0,-1,-1,-1,-1,-1") == NULL)\
      {\
         *pnew = i;\
          break;\
      }\
\
      if( i == totale_pagine)\
      {\
          printf("Root page not found\n");\
          return(False);\
      }\
\
      curr_oltree = root_oltree;\
      return(True);\
}\
\
/*\
recupero le informazioni sulla pagina parent\
*/\
while ( curr_oltree != root_oltree )\
   curr_oltree = OlTreeGetTop(curr_oltree,pnew);\
\
#endif\
\
return(True);\
\
\
\
\
\

*teleperm_moveroot.arguments: pcurr, pnew
*teleperm_moveroot.pcurr.def: "int", "*%pcurr%"
*teleperm_moveroot.pnew.def: "int", "*%pnew%"

*teleperm_gotopag.class: method
*teleperm_gotopag.name: gotopag
*teleperm_gotopag.parent: teleperm
*teleperm_gotopag.methodType: int
*teleperm_gotopag.methodArgs: int *pcur;\
int *pnew;\
int indice;\

*teleperm_gotopag.methodBody: OlTreeObject curr_oltree;\
int progr;\
\
/* recupero le informazioni sulla pagina corrente\
   nota: \
   pos_pag_curr e' indice della pagina corrente\
   e' importante mantenerlo aggiornato per la gestione del previous \
\
PROVO COMMENTANDO QUESTA PARTE a \
   gestire il salto da pagine fuori gerarchia\
   if( OlTreeGetPage(root_oltree,&curr_oltree,&progr,pcur,Pag->gerarchia) == False )\
   {\
      printf("Error retrieving hierarchy information for this page\n");\
      return;\
   }\
*/\
\
/* aggiorno l'indice della pagina pcur per\
   mantenere le funzionalita' di previous\
   Non aggiorno nulla se riapro una pagina allarmi\
*/\
\
  (*pcur) = pos_pag_new;\
\
/* setto la variabile globale (nel context)\
   pos_pag_new indice della pagina da visualizzare\
   e' importante mantenerlo aggiornato per la gestione del previous \
*/\
   (*pnew) = indice;\

*teleperm_gotopag.arguments: pcur, pnew, indice
*teleperm_gotopag.pcur.def: "int", "*%pcur%"
*teleperm_gotopag.pnew.def: "int", "*%pnew%"
*teleperm_gotopag.indice.def: "int", "%indice%"

*teleperm_switchScreen.class: method
*teleperm_switchScreen.name: switchScreen
*teleperm_switchScreen.parent: teleperm
*teleperm_switchScreen.methodType: int
*teleperm_switchScreen.methodArgs: 
*teleperm_switchScreen.methodBody: /* switch dello screen \
 */\
if( elenco_display[0].num_screens > 1 )\
{    \
   if(  screen_selezionato == 0   )\
      screen_selezionato = 1;\
   else \
      screen_selezionato--;\
}\
\
\


*teleperm_WidgetSelect.class: method
*teleperm_WidgetSelect.name: WidgetSelect
*teleperm_WidgetSelect.parent: teleperm
*teleperm_WidgetSelect.methodType: int
*teleperm_WidgetSelect.methodArgs: Widget w;\

*teleperm_WidgetSelect.methodBody: /* recupero il nome della OW da aprire\
   e faccio blinkare il frame dello widget \
   chiamante\
*/\
\
extern swidget create_OperatingWindow();\
swidget Ow=NULL;\
char *nome_pag;\
char nome_ow[255];\
FILE *fp;\
struct stat StatBuff;\
int i,posnew;\
Widget padre; /* padre del pictogrraph/indic */\
char class_name[100];\
\
#ifndef DESIGN_TIME\
/* recupero il nome della OW da aprire\
*/\
XtVaGetValues(w,XlNpaginaStazioni,&nome_pag,NULL);\
#endif\
\
strcpy(class_name, XlGetClassName(XtClass(w)) );\
\
printf("classe oggetto selezionato %s\n",class_name);\
\
if( strcmp( class_name , "IndicTelep" ) &&\
    strcmp( class_name , "Pictograph") )\
{\
   printf("Class parent not valid\n");\
   return(False);\
}\
\
/* verifica sul nome\
*/\
if( strlen(nome_pag) == 0 )\
{\
    printf("Not OW associated\n");\
    return(False);\
}\
\
/* individuo il file per verificare che esista il compilato\
*/\
sprintf(nome_ow,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),nome_pag);\
\
if( stat(nome_ow,&StatBuff) != 0 )\
{\
    printf("Cannot open associated OW\n");\
    return(False);\
}\
\
/* recupero l'indice nella lista delle pagine\
*/\
posnew = -1;\
for(i=0;i<totale_pagine;i++)\
    if( strcmp(pagine[i].nome,nome_pag) == NULL)\
    {\
       posnew = i;\
       break;\
    }\
\
if( posnew == -1 )\
{\
   printf("Page not faound in context\n");\
   return(False);\
}\
\
if( PaginaAperta(w,nome_pag) )\
{\
   printf("Page already open\n");\
   return(False);\
}\
\
if( !CanOpenPage(w) )\
{\
   printf("Cannot open page %s\n",nome_pag);\
   return(False);\
}\
\
printf("Open the associated OW\n");\
\
/* cerco la drawing area parent del pictograph/Indic\
*/\
padre = w;\
while( (xmDrawingAreaWidgetClass != XtClass(padre)) )\
   padre = XtParent(padre); \
\
/* creo la interfaccia e aggiorno la lista\
   delle OW aperte\
*/\
\
Ow = create_OperatingWindow(padre,w,&pagine[posnew],PagDb);\
\
if( Ow != NULL )\
{\
\
   /* alloco spazio per la lista delle pagine figlie\
   */\
   if( (ChildPagList = (Widget *) XtRealloc( ChildPagList,\
           sizeof( Widget ) * (numChildPagList+1) )) == NULL )\
   {\
      fprintf(stderr,"Teleperm: Error in allocation of childPag list\n");\
      return(False);\
   }\
\
   ChildPagList[ numChildPagList ] = Ow;\
   numChildPagList++;\
\
printf("Aperta OW = %d \n",ChildPagList[ numChildPagList-1 ]);\
printf("numChildPagList = %d\n",numChildPagList);\
\
   UxPopupInterface(Ow,no_grab);\
}\
\
return(True);\
\

*teleperm_WidgetSelect.arguments: w
*teleperm_WidgetSelect.w.def: "Widget", "%w%"

*teleperm_createCaiHeader.class: method
*teleperm_createCaiHeader.name: createCaiHeader
*teleperm_createCaiHeader.parent: teleperm
*teleperm_createCaiHeader.methodType: int
*teleperm_createCaiHeader.methodArgs: 
*teleperm_createCaiHeader.methodBody: /*\
Funzione che permette di disegnare i Cai sull' header della pagina teleperm.\
La funzione e' invocata alla fine del final code dell' interfaccia teleperm\
*/\
char nomeCai[100];      /* MAXCHAR_PAGNAME */\
Pixel background_parent;\
\
\
\
/* gerarchia relativa a root cablata */\
strcpy(gerarchiaHeader,"[0][-1][-1][-1][-1][-1]");\
\
/* Valore sfondo per Cai in transparent  */\
get_something(formCaiPlant,XmNbackground,&background_parent);\
\
	strcpy(labelCaiHeader,"HeaderCai");\
        strcpy(nomeCai,labelCaiHeader);\
        strcat(nomeCai,"A");\
\
	listaCaiHeader[0]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			formCaiPlant,\
			XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,isa,\
			XmNtopWidget,isa,\
			XlNtipoCai, CAI_A,\
			XlNcolorBord,background_parent,\
			XmNleftOffset,LEFTOFFSET,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
			XlNvarGerarchia,gerarchiaHeader,\
			NULL);\
\
	UxPutContext( listaCaiHeader[0],(char *) UxTelepermContext );\
\
        strcpy(nomeCai,labelCaiHeader);\
        strcat(nomeCai,"W");\
\
	listaCaiHeader[1]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			formCaiPlant,\
			XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,\
			XmNtopWidget,isa,\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,listaCaiHeader[0],\
			XlNtipoCai, CAI_W,\
			XlNcolorBord,background_parent,\
			XmNleftOffset,LEFTOFFSET,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
			XlNvarGerarchia,gerarchiaHeader,\
			NULL);\
\
	UxPutContext( listaCaiHeader[1],(char *) UxTelepermContext );\
        strcpy(nomeCai,labelCaiHeader);\
        strcat(nomeCai,"T");\
\
	listaCaiHeader[2]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			formCaiPlant,\
			XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,\
			XmNtopWidget,isa,\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,listaCaiHeader[1],\
			XlNcolorBord,background_parent,\
			XlNtipoCai, CAI_T,\
			XmNleftOffset,LEFTOFFSET,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
			XlNvarGerarchia,gerarchiaHeader,\
			NULL);\
\
	UxPutContext( listaCaiHeader[2],(char *) UxTelepermContext );	\
\
        strcpy(nomeCai,labelCaiHeader);\
        strcat(nomeCai,"M");\
\
	listaCaiHeader[3]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			formCaiPlant,\
			XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,\
			XmNtopWidget,isa,\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,listaCaiHeader[2],\
			XlNcolorBord,background_parent,\
			XlNtipoCai, CAI_M,\
			XmNleftOffset,LEFTOFFSET,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
			XlNvarGerarchia,gerarchiaHeader,\
			NULL);\
\
	UxPutContext( listaCaiHeader[3],(char *) UxTelepermContext );	\
\
        strcpy(nomeCai,labelCaiHeader);\
        strcat(nomeCai,"F");\
\
	listaCaiHeader[4]= XtVaCreateManagedWidget(nomeCai,\
			xlCaiWidgetClass,\
			formCaiPlant,\
			XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,\
			XmNtopWidget,isa,\
			XmNleftAttachment,XmATTACH_WIDGET,\
			XmNleftWidget,listaCaiHeader[3],\
			XlNtipoCai, CAI_F,\
			XlNcolorBord,background_parent,\
			XmNleftOffset,LEFTOFFSET,\
#ifndef DESIGN_TIME\
			XlNconfig, False,\
#endif\
			XlNvarGerarchia,gerarchiaHeader,\
			NULL);\
\
	UxPutContext( listaCaiHeader[4],(char *) UxTelepermContext );	\
\
/*\
Setto il database dei punti per ogni oggetto Cai\
*/\
OlSetDatabasePunti(listaCaiHeader,MAXNUMCAIXLINE,database_simulatore);\
/*\
Innesco Refresh del Cai\
*/\
teleperm_refreshCaiHeader(formCaiPlant);\
\


*teleperm_aggListChild.class: method
*teleperm_aggListChild.name: aggListChild
*teleperm_aggListChild.parent: teleperm
*teleperm_aggListChild.methodType: int
*teleperm_aggListChild.methodArgs: Widget childW;\

*teleperm_aggListChild.methodBody: /****************************************************\
 * aggiorno la lista delle pagine figlie durante\
 * la chiusura di una di esse\
 ***************************************************/\
int i;\
\
for( i=0;i<numChildPagList;i++)\
   if( childW == ChildPagList[i] )\
   {\
      ChildPagList[i] = NULL;\
      \
      /* non decremento il contatore delle pagine \
         perche' mii basero' sul NULL in ChildPagList\
         per descriminare se la OW e' aperta o chiusa\
      */\
   }\
\
return(True);
*teleperm_aggListChild.arguments: childW
*teleperm_aggListChild.childW.def: "Widget", "%childW%"

*teleperm_closeOW.class: method
*teleperm_closeOW.name: closeOW
*teleperm_closeOW.parent: teleperm
*teleperm_closeOW.methodType: int
*teleperm_closeOW.methodArgs: 
*teleperm_closeOW.methodBody: extern Boolean OW_close();\
Widget drawing;\
int i;\
XrmDatabase StazDb;\
\
/* elimino tutte le OW eventualmente aperte\
*/\
for(i=0;i<numChildPagList;i++)\
{\
   if( (ChildPagList[i] != NULL) )\
   {\
       if( !XtIsRealized( ChildPagList[i] ) )\
          continue;\
\
      /* chiudo solo se lo screen selezionato e' quello dove risiede la OW\
      \
      if( XScreenNumberOfScreen(XtScreen(ChildPagList[i])) == screen_selezionato )\
      Questo test potrebbe essere errato perche' lo screen potrebbe essere stato switchato \
      */\
if( XScreenNumberOfScreen(XtScreen(ChildPagList[i])) == \
    XScreenNumberOfScreen(XtScreen( UxThis )) )\
         {\
         \
         OW_close(ChildPagList[i]);\
         }\
   }\
\
}\
\
\
for(i=0;i<num_el_pagine;i++)\
   {\
   if(el_pagine[i].w!=NULL)\
      {\
      /* Ricavo la drawing Area del padre\
         per capire il tipo di pagina */\
      drawing=el_pagine[i].w;\
      if( !strcmp(XtName(drawing),DRAWING_STAZ))\
         {\
         if( XScreenNumberOfScreen(XtScreen(drawing)) ==\
              XScreenNumberOfScreen(XtScreen( UxThis )) )\
              {\
              printf("Sto per chiudere la pagina di Staz.\n");\
              ClosePageStaz(drawing);\
              /* \
              La stazione elimina il database delle risorse \
              devo ripristinarlo\
              */\
              \
              XrmSetDatabase(XtDisplay(UxThis),PagDb); \
              }\
         }\
      }\
\
   }\
\


*teleperm_drawPush.class: method
*teleperm_drawPush.name: drawPush
*teleperm_drawPush.parent: teleperm
*teleperm_drawPush.methodType: int
*teleperm_drawPush.methodArgs: Widget w;\
unsigned char *bmpName;\

*teleperm_drawPush.methodBody: char pathBmp[255];\
        int ret;\
        Pixmap bmp,pix;\
        int xh,yh,width,height;\
        Pixel bkg_col,arm_col,bot_col,top_col,dummy_col,fg_col;\
        GC gcapp;\
        XGCValues values;\
        unsigned long valuemask =  GCForeground | GCBackground ;\
\
        /* costruisco il file name completo\
        */\
        sprintf(pathBmp,"%s/%s",getenv("LEGOCAD_ICO"),bmpName);\
         \
        /* recupero colori e dimensioni dello widget chiamante\
        */\
        XtVaGetValues(w,\
                            XmNforeground,&fg_col,\
                            XmNbackground,&bkg_col,\
                            XmNarmColor,&arm_col,\
                            XmNbottomShadowColor,&bot_col,\
                            XmNtopShadowColor,&top_col,\
                            XmNx,&xh,\
                            XmNy,&yh,\
                            XmNwidth,&width,\
                            XmNheight,&height,\
                            NULL);\
\
        /* leggo il file bitmap\
        */\
        ret=XReadBitmapFile(XtDisplay(w),\
                        RootWindow(XtDisplay(w),DefaultScreen(XtDisplay(w))),\
                        pathBmp,&width,\
                        &height,\
                        &bmp,&xh,&yh);\
\
          if(ret==BitmapSuccess)\
                printf("Bitmap caricato correttamente\n");\
           else if(ret==BitmapOpenFailed)\
                printf("Apertura fallita\n");\
           else if(ret==BitmapFileInvalid)\
                printf("File bitmap non valido \n");\
           else if(ret==BitmapNoMemory)\
                printf("No memory\n");\
           if(ret!=BitmapSuccess)\
           {\
                printf("Impossibile leggere il file con XReadBitmap\n");\
                return(False);\
           }\
\
\
           /* Creo un pixmap delle dimensioni del bottone\
           */\
           pix=XCreatePixmap(XtDisplay(w),\
                             RootWindow(XtDisplay(w),\
                             DefaultScreen(XtDisplay(w))),\
                             width,\
                             height,\
                             DefaultDepth(XtDisplay(w),\
                             DefaultScreen(XtDisplay(w))));\
\
\
           /* inverto i colori del bottone\
              bkg, arm, top shadow e bottom shadow\
           */\
           dummy_col = bkg_col;\
           bkg_col = arm_col;\
           arm_col = dummy_col;\
           dummy_col = top_col;\
           top_col = bot_col;\
           bot_col = dummy_col;\
\
        /* setto il GC di appoggio\
           per impostare i colori di backg e foreg al pixmap\
        */\
           values.foreground = fg_col;\
           values.background = bkg_col;\
\
           gcapp = XtGetGC(w,valuemask,&values);\
\
           /* tramite la copyPlane ottengo che il pixmap\
              venga costruito in base al bitmap letto\
             con i colori impostati dal GC\
           */\
           XCopyPlane(XtDisplay(w),bmp,pix,\
                gcapp,0,0,\
                width,height,\
                0, 0, 1);\
\
           /* assegno allo widget chiamante il pixmap e i colori\
              nuovi.\
           */\
           XtVaSetValues(w,\
                            XmNforeground,fg_col,\
                            XmNbackground,bkg_col,\
                            XmNarmColor,arm_col,\
                            XmNbottomShadowColor,bot_col,\
                            XmNtopShadowColor,top_col,\
                            XmNlabelPixmap,pix,\
                            NULL);\
        \
/* libero il pixmap\
        XFreePixmap(XtDisplay(w),pix);\
*/\

*teleperm_drawPush.arguments: w, bmpName
*teleperm_drawPush.w.def: "Widget", "%w%"
*teleperm_drawPush.bmpName.def: "unsigned char", "*%bmpName%"

*teleperm_createButtonPixmap.class: method
*teleperm_createButtonPixmap.name: createButtonPixmap
*teleperm_createButtonPixmap.parent: teleperm
*teleperm_createButtonPixmap.methodType: int
*teleperm_createButtonPixmap.methodArgs: 
*teleperm_createButtonPixmap.methodBody: Pixmap pix;\
Pixel bg,fg;\
char pathBMP[255];\
int numero_screen;\
#ifdef GESTIONE_SU_SCREEN_DIVERSI\
numero_screen=XScreenNumberOfScreen(XtScreen(previous));\
\
XtVaGetValues(previous,\
              XmNforeground,&fg,\
              XmNbackground,&bg,\
              NULL);\
\
sprintf(pathBMP,"%s/previous%d.bmp",getenv("LEGOCAD_ICO"),numero_screen);\
\
pix = XmGetPixmap( XtScreen(UxThis),\
                   pathBMP,\
                   fg,bg);\
\
if( pix == XmUNSPECIFIED_PIXMAP )\
{\
   printf("invalid pixmap %s\n",pathBMP);\
   return(False);\
}\
\
XtVaSetValues(previous,\
              XmNlabelType,XmPIXMAP,\
              XmNlabelPixmap,pix,\
              NULL);\
#endif\
return(True);\


*teleperm_create_allPage.class: method
*teleperm_create_allPage.name: create_allPage
*teleperm_create_allPage.parent: teleperm
*teleperm_create_allPage.methodType: int
*teleperm_create_allPage.methodArgs: 
*teleperm_create_allPage.methodBody: /*\
Funzione per la creazione della pagina allarmi\
*/\
Position xShell,yShell;\
int i,j;\
int last_zone;   /* indice ultima zona attivabile */\
Pixel background_color,arm_color,top_shadow,bottom_shadow; /* Pixel per bottoni header */\
char *nome_header,*nomeWidget;\
Pixel background_parent;  /* background del parent dei Cai */\
Boolean readButtColor=False;\
char *tipo;\
XrmValue value;\
/* \
In base al num_telepag possono essere visualizzati allarmi fino a 30 \
zone di impianto.\
Ne vengono influenzati la altezza della header_form , e i bordi ed i margini\
dei rowColumn contenenti  le informazioni sugli allarmi.La dimensione \
delle form contenute nell' header e' fissa.\
*/\
\
int height_header_form,dim_entryBorder,dim_marginHeight;\
\
/* \
Acquisisco valore risorsa per background per emissioni e rientri label\
*/\
XrmGetResource(UxDisplay->db,"teleperm.emission",(char*)NULL,&tipo,&value);\
strncpy(def_background_emission,value.addr,(int)value.size);\
/*printf("\n\n def_background_emission=%s\n\n",def_background_emission);*/\
\
XrmGetResource(UxDisplay->db,"teleperm.ack",(char*)NULL,&tipo,&value);\
strncpy(def_background_acknowledge,value.addr,(int)value.size);\
/*printf("\n\n def_background_acknowledge=%s\n\n",def_background_acknowledge);*/\
\
/*\
Controllo che pagina allarmi vecchi tipo non sia gia' stata aperta\
Se non e' stata aperta nessuna pagAll set a 1 il flag di sync.\
*/\
if(!OlCanOpenAllarmPage(database_simulatore))\
   return -1;\
else\
   if(!OlSetOpeningAllarmPage(database_simulatore,1)) /* Posso settare a 1 ? */\
      return -1;\
   \
/* Setto a true flag per apertura pagina allarmi cosicche' non possa aprirla \
un altro screen\
*/\
if(!allPageFlag)\
      allPageFlag=True;\
else\
      return -1;\
/*\
Setto le caratteristiche della interfaccia: No righe per dimensioni di\
ogni lista_header_form\
*/\
if(num_zone==HEADERTRERIGHE)\
      {\
      height_header_form=3*HEIGHTSMALLFORMHEADER+7;\
      dim_entryBorder=4;\
      dim_marginHeight=3;\
      }\
else if(num_zone==HEADERQUATTRORIGHE)\
      {\
      height_header_form=4*HEIGHTSMALLFORMHEADER+7;\
      dim_entryBorder=2;\
      dim_marginHeight=1;\
      }\
else if(num_zone==HEADERCINQUERIGHE)\
      {\
      height_header_form=5*HEIGHTSMALLFORMHEADER+10;\
      dim_entryBorder=0;\
      dim_marginHeight=0;\
      }\
else\
      {\
      printf("ERROR: num_telepag=%d Zone number not correct\n");\
      return(-1);\
      }\
\
/*\
Setto il database delle risorse\
*/\
XrmSetDatabase(XtDisplay(UxThis),PagDb); \
/* Se un pullDown e' active eliminalo */\
 if(pullDownActive)\
                {\
                XtRemoveTimeOut(timer_timerefreshCai);\
                UxDestroyInterface(*pullDownActive);\
                XtFree(listaCaiVr);\
                XtFree(listaCaiFormVr);\
                XtFree(listaPushButton);\
                pullDownActive=NULL;\
                }\
\
/*\
Uguaglio gli indici della vecchia e della nuova pagina  \
per funzionamaento pushButton Previous\
*/\
\
\
\
/*\
Deseleziono i bottoni per navigazione\
*/\
XtSetSensitive(left,False);\
XtSetSensitive(right,False);\
XtSetSensitive(up,False);\
/* acquisisco la posizione della main di teleperm */\
get_something(	teleperm,XmNx,&xShell);		\
get_something(	teleperm,XmNy,&yShell);	\
\
\
/*****************************************************\
Parte riservata ad allocazione per oggetti multipli\
*******************************************************/\
\
if ( (lista_header_form = (Widget *) XtCalloc(1, num_zone * sizeof(Widget)) ) == NULL)\
{\
   printf("Allarm Page: Error in malloc: lista_header_form\n");\
   return(-1);\
}\
if ( (lista_header_button = (Widget *) XtCalloc(1, num_zone * sizeof(Widget)) ) == NULL)\
{\
   printf("Allarm Page: Error in malloc: lista_header_button\n");\
   return(-1);\
}\
if ( (lista_header_rowColumn = (Widget *) XtCalloc(1, num_zone * sizeof(Widget)) ) == NULL)\
{\
   printf("Allarm Page: Error in malloc: lista_header_rowColumn\n");\
   return(-1);\
}\
if((nome_header=XtCalloc(1, sizeof(char)*ALLMAXLUNNOMEWID))==NULL)\
	{ \
	printf("nome_headerFont Error in malloc: createAllPage\n");\
        return(-1);\
	}\
\
if ( (lista_header_label = (Widget *) XtCalloc(1, num_zone * 4* sizeof(Widget)) ) == NULL)\
	{\
	printf("nome_headerFont Error in malloc: lista_header_label\n");\
        return(-1);\
	}\
/*\
Allocazioni per label per allarmi\
*/\
if ( (all_caiAll_form = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)\
	{\
	printf("creaAllPage Error in malloc: all_caiAll_form\n");\
        return(-1);\
	}\
if ( (all_caiAll = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)\
	{\
	printf("creaAllPage Error in malloc: all_caiAll\n");\
        return(-1);\
	}\
if ( (all_name_label = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)\
	{\
	printf("creaAllPage Error in malloc: all_name_label\n");\
        return(-1);\
	}\
if ( (all_descr_label = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)\
	{\
	printf("creaAllPage Error in malloc: all_descr_label\n");\
        return(-1);\
	}\
if ( (all_data_label = (Widget *) XtCalloc(1,  MAXNUMALLVIS * sizeof(Widget)) ) == NULL)\
	{\
	printf("creaAllPage Error in malloc: all_data_label\n");\
        return(-1);\
	}\
\
/*******************************************************\
Fine parte riservata ad allocazione per oggetti multipli\
********************************************************/\
\
/*\
Inizializzazioni\
*/\
strcpy(nome_header,"header");\
for(i=0;i<MAXNUMALLVIS;i++)\
	strcpy(gerarchiaValoreAll[i],"");\
/*\
Inizio costruzione oggetti\
Distruggo la pagina precedente\
*/\
if(allPageOnScreen!=SINCROCLOSEALLPAG)\
	{\
	DelElencoPagine(key_refresh, drawingArea);\
	XSync(XtDisplay(drawingArea),False);\
	XtRemoveTimeOut(timer_refresh);\
	XtDestroyWidget( drawingArea);\
        XtFree(lista_wid);\
	}\
/*Eliminazione della pagina precedente */\
all_form_topLevelShell=XtVaCreateManagedWidget( "all_form_topLevelShell",\
                        xmFormWidgetClass,\
                        formTop,\
                        XmNwidth, 200,\
                        XmNheight, 960,\
                        XmNresizePolicy, XmRESIZE_NONE,\
			XmNbottomAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        XmNrightAttachment, XmATTACH_FORM,\
                        XmNtopAttachment, XmATTACH_FORM,\
                        XmNtopOffset, 30,\
                        XmNbottomOffset, 35,\
                        XmNunitType, XmPIXELS,\
			/*RES_CONVERT( XmNbackground, "#000000" ),*/\
                        NULL );\
        UxPutContext( all_form_topLevelShell, (char *) UxTelepermContext );\
\
all_form_title = XtVaCreateManagedWidget( "all_form_title",\
                        xmFormWidgetClass,\
                        all_form_topLevelShell,\
                        XmNwidth, 1275,\
                        XmNheight, 40,\
                        XmNresizePolicy, XmRESIZE_NONE,\
                        XmNx, 0,\
                        XmNy, 0,\
                       /* RES_CONVERT( XmNbackground, "cyan" ),*/\
                        XmNrightAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        NULL );\
        UxPutContext( all_form_title, (char *) UxTelepermContext );\
\
all_new_button = XtVaCreateManagedWidget( "all_new_button",\
                        xmPushButtonWidgetClass,\
                        all_form_title,\
                        XmNx, 10,\
                        XmNy, 10,\
			XmNleftOffset, 3,\
                        XmNbottomAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        XmNbottomOffset, 3,\
                        NULL );\
        UxPutContext( all_new_button, (char *) UxTelepermContext  );\
\
	XtAddCallback(all_new_button, XmNactivateCallback,\
                    (XtCallbackProc)command_alarm,OL_MODO_ALLARMI);\
\
        /* Creation of label all new */\
all_new = XtVaCreateManagedWidget( "all_new",\
                        xmLabelWidgetClass,\
                        all_form_title,\
                        XmNx, 90,\
                        XmNy, 10,\
			XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftOffset, 5,\
			XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,\
			XmNbottomWidget, all_new_button,\
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,\
			XmNtopWidget, all_new_button,\
			XmNleftWidget, all_new_button,\
                        NULL );\
        UxPutContext( all_new, (char *) UxTelepermContext  );\
\
\
        /* Creation of label12 */\
all_old_button = XtVaCreateManagedWidget( "all_old_button",\
                        xmPushButtonWidgetClass,\
                        all_form_title,\
                        XmNx, 170,\
                        XmNy, 10,\
			XmNleftWidget, all_new,\
			XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftOffset, 10,\
			XmNbottomAttachment, XmATTACH_FORM,\
                        XmNbottomOffset, 3,\
                        NULL );\
 UxPutContext( all_old_button, (char *) UxTelepermContext  );\
\
	XtAddCallback(all_old_button, XmNactivateCallback,\
                    (XtCallbackProc)command_alarm,OL_MODO_ARCHIVIO);\
all_old = XtVaCreateManagedWidget( "all_old",\
                        xmLabelWidgetClass,\
                        all_form_title,\
                        XmNx, 240,\
                        XmNy, 10,\
			XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,\
			XmNbottomWidget, all_old_button,\
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,\
			XmNtopWidget, all_old_button,\
			XmNleftWidget, all_old_button,\
                        XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftOffset, 5,\
                        NULL );\
        UxPutContext( all_old, (char *) UxTelepermContext );\
\
\
        /* Creation of label  title*/\
all_title_label = XtVaCreateManagedWidget( "all_title_label",\
                        xmLabelWidgetClass,\
                        all_form_title,\
                        XmNx, 460,\
                        XmNy, 0,\
                        XmNwidth, 300,\
                        NULL );\
        UxPutContext( all_old, (char *) UxTelepermContext );\
\
all_header_mainForm = XtVaCreateManagedWidget( "all_header_mainForm",\
                        xmFormWidgetClass,\
                        all_form_topLevelShell,\
                        XmNwidth, 1258,\
                        XmNheight,  height_header_form,\
                        XmNresizePolicy, XmRESIZE_NONE,\
                        XmNx, 0,\
			XmNtopAttachment,XmATTACH_WIDGET,\
			XmNtopWidget,all_form_title,\
                        XmNrightAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        /*RES_CONVERT( XmNbackground, "gray" ),*/\
                        NULL );\
        UxPutContext( all_header_mainForm, (char *) UxTelepermContext );\
\
header_rowColumn = XtVaCreateManagedWidget( "header_rowColumn",\
                        xmRowColumnWidgetClass,\
                        all_header_mainForm,\
                        XmNwidth, 1654,\
                        XmNheight, 162,\
                        XmNx, 0,\
                        XmNy, 0,\
                        XmNnumColumns, 3,\
                        XmNpacking, XmPACK_TIGHT,\
                        XmNorientation, XmHORIZONTAL,\
                        XmNadjustLast, FALSE,\
                        XmNrightAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_FORM,\
			XmNbottomAttachment, XmATTACH_FORM,\
                        XmNtopAttachment, XmATTACH_FORM,\
			XmNresizeHeight, TRUE,\
                        XmNresizeWidth, FALSE,\
			XmNisAligned, FALSE,\
                        XmNresizable, FALSE,\
			XmNmarginHeight, 1,\
                        XmNmarginWidth, 1,\
                        NULL );\
        UxPutContext( header_rowColumn, (char *) UxTelepermContext );\
/*\
Costruisco num_zone pulsanti di selezione delle zone:\
la zona 0 e' utilizzata per gli allarmi di diagnostica (parto con i=1)\
*/\
\
for(i=1;i<num_zone;i++)\
	{\
	if((nomeWidget=XtCalloc(1, sizeof(char)*ALLMAXLUNNOMEWID))==NULL)\
   		{\
      		printf("create_allPage Error in malloc: nomeWidget\n");\
      		return(-1);;\
   		}\
	sprintf(nomeWidget,"%d",i);\
	strcat(nomeWidget,nome_header);	/* inserisco "header" nel nome */\
	strcat(nomeWidget,"_form");\
\
lista_header_form[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xmFormWidgetClass,\
                        header_rowColumn,\
                        XmNwidth, 207,\
                        XmNheight, 55,\
                        XmNresizePolicy, XmRESIZE_NONE,\
                        XmNx, 3,\
                        XmNy, 3,\
                        NULL );\
        UxPutContext( lista_header_form[i], (char *) UxTelepermContext );	\
/*\
Creo gli altri oggetti solo se la zona e' abilitabile\
Le zone (function Area) abilitabili sono state  settate nella creazione \
della pagina teleperm\
*/\
	if(selectable_zone[i])\
	  {\
/*\
Inserisco il bottone per ogni Zona\
*/\
	  strcpy(nomeWidget,"");\
	  sprintf(nomeWidget,"%d",i);\
          strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */\
	  strcat(nomeWidget,"_button");\
\
          lista_header_button[i]=XtVaCreateManagedWidget( nomeWidget,\
                        xmPushButtonWidgetClass,\
                        lista_header_form[i],\
                        XmNx, 0,\
                        XmNy, 30,\
                        XmNwidth, 207,\
                        XmNheight, 30,\
			RES_CONVERT( XmNlabelString,pagine[selectable_zone[i]].descrizione),\
                        XmNbottomAttachment, XmATTACH_FORM,\
                        XmNrightAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        NULL );\
           UxPutContext( lista_header_button[i], (char *) UxTelepermContext );\
/*\
Acquisisco valori variabili back e arm per gestione piu' utenti con la stessa\
pagina allarmi-> vedi codice inizion metodo refresh pagina allarmi\
readButtColor e' usata per non acquisire colori bottoni + di una volta.\
*/\
      if(!readButtColor)\
              {\
              get_something(lista_header_button[i],XmNbackground,&def_background_butt);\
              get_something(lista_header_button[i],XmNarmColor,&def_armColor_butt);\
              get_something(lista_header_button[i],XmNtopShadowColor,&def_topShadowColor_butt);\
              get_something(lista_header_button[i],XmNbottomShadowColor,&def_bottomShadowColor_butt);\
              readButtColor=True;\
              }\
/*\
Setto subito colori dei bottoni in base alle zone attivate\
N.B.\
All' iesimo bottone e' associata la zona i+1 poiche' nella zona 0\
vi sono gli allarmi di diagnostica generale.\
*/\
	  if(zone_status[i])\
	  	{\
		/* Acquisisco valori dei colori del bottone */\
\
		XtVaGetValues(lista_header_button[i],XmNarmColor,&arm_color,NULL);\
		XtVaGetValues(lista_header_button[i],XmNbackground,&background_color,NULL);\
		XtVaGetValues(lista_header_button[i],XmNtopShadowColor,&top_shadow,NULL);\
		XtVaGetValues(lista_header_button[i],XmNbottomShadowColor,&bottom_shadow,NULL);\
\
/* Setto nuovi valori del bottone (scambio bordini e sfondi)*/\
\
		XtVaSetValues(lista_header_button[i],XmNbackground,arm_color,NULL);\
		XtVaSetValues(lista_header_button[i],XmNarmColor,background_color,NULL);\
		XtVaSetValues(lista_header_button[i],XmNtopShadowColor,bottom_shadow,NULL);\
		XtVaSetValues(lista_header_button[i],XmNbottomShadowColor,top_shadow,NULL);\
		}\
		\
/*\
Acquisisco valori dei colori dei bottoni\
*/\
    	  XtAddCallback(lista_header_button[i], XmNactivateCallback,\
                    (XtCallbackProc)select_zone,i);\
\
/* rowColumn per indicatori per ogni zona */\
          strcpy(nomeWidget,"");\
          sprintf(nomeWidget,"%d",i);\
          strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */\
          strcat(nomeWidget,"_rowColumn");\
\
          lista_header_rowColumn[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xmRowColumnWidgetClass,\
                        lista_header_form[i],\
                        XmNwidth, 210,\
                        XmNheight, 30,\
                        XmNx, 0,\
                        XmNy, 0,\
                        XmNbottomAttachment, XmATTACH_WIDGET,\
                        XmNbottomWidget, lista_header_button[i],\
                        XmNrightAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        XmNnumColumns, 4,\
                        XmNpacking, XmPACK_COLUMN,\
                        XmNadjustLast, FALSE,\
                        XmNtopAttachment, XmATTACH_FORM,\
			RES_CONVERT( XmNbackground, "ivory"),\
			XmNisAligned, FALSE,\
                        NULL );\
           UxPutContext( lista_header_rowColumn[i], (char *) UxTelepermContext );\
\
	  	  strcpy(nomeWidget,"");\
        	  sprintf(nomeWidget,"%d",i);\
        	  strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */\
        	  strcat(nomeWidget,"_labelNew");\
\
           lista_header_label[i*4]=XtVaCreateManagedWidget( nomeWidget,\
                        xmLabelWidgetClass,\
                        lista_header_rowColumn[i],\
                        XmNx, 3,\
                        XmNy, 3,\
                        XmNwidth, 49,\
                        XmNrecomputeSize, FALSE,\
                        XmNheight, 20,\
                        NULL );\
\
        	UxPutContext( lista_header_label[i*4], (char *) UxTelepermContext );\
\
		strcpy(nomeWidget,"");\
        	sprintf(nomeWidget,"%d",i);\
        	strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */\
        	strcat(nomeWidget,"_labelNewDisplay");\
\
	        lista_header_label[i*4+1]=XtVaCreateManagedWidget( nomeWidget,\
                        xmLabelWidgetClass,\
                        lista_header_rowColumn[i],\
			XmNx, 13,\
                        XmNy, 13,\
                        XmNwidth, 49,\
                        XmNrecomputeSize, FALSE,\
                        XmNheight, 20,\
			XmNalignment, XmALIGNMENT_END,\
                        RES_CONVERT( XmNlabelString, "-" ),\
                        NULL );\
\
                UxPutContext( lista_header_label[i*4+1], (char *) UxTelepermContext);\
		\
		strcpy(nomeWidget,"");\
        	sprintf(nomeWidget,"%d",i);\
        	strcat(nomeWidget,nome_header); /* inserisco "header" nel nome */\
        	strcat(nomeWidget,"_labelOld");\
lista_header_label[i*4+2]= XtVaCreateManagedWidget( nomeWidget,\
                        xmLabelWidgetClass,\
                        lista_header_rowColumn[i],\
                        XmNx, 85,\
                        XmNy, 13,\
                        XmNwidth, 49,\
                        XmNrecomputeSize, FALSE,\
                        XmNheight, 20,\
                        NULL );\
        UxPutContext( lista_header_label[i*4+2], (char *) UxTelepermContext );\
\
		strcpy(nomeWidget,"");\
        	sprintf(nomeWidget,"%d",i);\
        	strcat(nomeWidget,nome_header); /*inserisco "header" nel nome */\
        	strcat(nomeWidget,"_labelOldDisplay");\
\
	        lista_header_label[i*4+3]=XtVaCreateManagedWidget( nomeWidget,\
                        xmLabelWidgetClass,\
                        lista_header_rowColumn[i],\
			XmNx, 157,\
                        XmNy, 13,\
                        XmNwidth, 49,\
                        XmNrecomputeSize, FALSE,\
                        XmNheight, 20,\
			XmNalignment, XmALIGNMENT_END,\
                        RES_CONVERT( XmNlabelString, "-" ),\
                        NULL );\
\
                UxPutContext( lista_header_label[i*4+3], (char *) UxTelepermContext);\
		\
          last_zone=i; /* ultima zona selezionabile */\
	  } /* end if selectable_zone */\
	else\
	  {\
	  lista_header_button[i]=NULL;\
	  lista_header_rowColumn[i]=NULL;\
	  lista_header_label[i*4]=NULL;\
	  lista_header_label[i*4+1]=NULL;\
	  lista_header_label[i*4+2]=NULL;\
	  lista_header_label[i*4+3]=NULL;\
	  }\
\
	XtFree(nomeWidget);	\
\
	} /* end for X header */                                                              \
/*\
Istanzio form che conterra' i rowColumn per le label\
*/                                                                   \
\
        all_formAll = XtVaCreateManagedWidget( "all_formAll",\
                        xmFormWidgetClass,\
                        all_form_topLevelShell,\
                        XmNwidth, 1270,\
                        XmNheight, 1050,\
                        XmNresizePolicy, XmRESIZE_NONE,\
                        XmNx, 0,\
                        /*RES_CONVERT( XmNbackground, "midnight blue" ),*/\
                        XmNrightAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        XmNtopAttachment, XmATTACH_WIDGET,\
                        XmNtopWidget, all_header_mainForm ,\
			XmNtopOffset, 5,\
                        NULL );\
\
        UxPutContext( all_formAll, (char *) UxTelepermContext );\
/*\
Istanzio le rowColumn che conterranno le label per gli allarmi\
*/\
\
all_rowColumn_caiAll=XtVaCreateManagedWidget( "all_rowColumn_CaiAll",\
                        xmRowColumnWidgetClass,\
                        all_formAll,\
                        XmNwidth, 35,\
                        XmNheight, 692,\
                        XmNx, 1,\
                        XmNy, 0,\
                        XmNresizeWidth, TRUE,\
                        XmNresizeHeight, TRUE,\
                        XmNentryBorder, dim_entryBorder,\
                        XmNmarginHeight, dim_marginHeight,\
                        XmNtopOffset, 0,\
                        XmNtopAttachment, XmATTACH_FORM,\
                        /*RES_CONVERT( XmNbackground, "white"),*/\
                        NULL );\
        UxPutContext( all_rowColumn_caiAll, (char *) UxTelepermContext );\
\
all_rowColumn_nameAll=XtVaCreateManagedWidget( "all_rowColumn_nameAll",\
                        xmRowColumnWidgetClass,\
                        all_formAll,\
                        /*XmNwidth, 347,*/\
                        /*XmNheight, 692,*/\
                        XmNx, 40,\
                        XmNy, 0,\
                        XmNresizeWidth, TRUE,\
                        XmNresizeHeight, TRUE,\
                        XmNentryBorder, dim_entryBorder,\
                        XmNmarginHeight, dim_marginHeight,\
                        XmNtopOffset, 0,\
                        XmNtopAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftWidget, all_rowColumn_caiAll,\
			/*RES_CONVERT( XmNbackground, "aquamarine"),*/\
                        NULL );\
        UxPutContext( all_rowColumn_nameAll, (char *) UxTelepermContext );\
\
all_rowColumn_descrAll = XtVaCreateManagedWidget( "all_rowColumn_descrAll",\
                        xmRowColumnWidgetClass,\
                        all_formAll,\
                        /*XmNwidth, 614,*/\
                        XmNx, 374,\
                        XmNy, 0,\
                        XmNresizeWidth, TRUE,\
                        XmNresizeHeight, TRUE,\
                        XmNentryBorder, dim_entryBorder,\
                        XmNmarginHeight, dim_marginHeight,\
                        XmNtopOffset, 0,\
                        XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftOffset, 0,\
                        XmNleftWidget, all_rowColumn_nameAll,\
                        XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,\
                        XmNtopWidget, all_rowColumn_nameAll,\
                        XmNnumColumns, 1,\
                        XmNpacking, XmPACK_TIGHT,\
			/*RES_CONVERT( XmNbackground, "forest green"),*/\
                        NULL );\
        UxPutContext( all_rowColumn_descrAll, (char *) UxTelepermContext );\
\
all_rowColumn_dataAll = XtVaCreateManagedWidget( "all_rowColumn_data",\
                        xmRowColumnWidgetClass,\
                        all_formAll,\
                        /*XmNwidth, 213,*/\
                        /*XmNheight, 695,*/\
                        XmNx, 276,\
                        XmNy, 11,\
                        XmNresizeWidth, TRUE,\
                        XmNresizeHeight, TRUE,\
                        XmNentryBorder, dim_entryBorder,\
                        XmNmarginHeight, dim_marginHeight,\
                        XmNnumColumns, 1,\
                        XmNpacking, XmPACK_TIGHT,\
                        XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftWidget, all_rowColumn_descrAll,\
                        XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,\
                        XmNtopOffset, 0,\
                        XmNtopWidget, all_rowColumn_descrAll,\
			/*RES_CONVERT( XmNbackground, "cornsilk"),*/\
                        NULL );\
        UxPutContext( all_rowColumn_dataAll, (char *) UxTelepermContext );\
\
for(i=0;i<MAXNUMALLVIS;i++)\
	{\
	if((nomeWidget=XtCalloc(1, sizeof(char)*ALLMAXLUNNOMEWID))==NULL)\
   		{\
      		printf("create_allPage Error in malloc: nomeWidget\n");\
      		return(-1);;\
   		}\
/*\
Creazione delle form contenenti i caiAll\
*/\
		strcpy(nomeWidget,"");\
        	sprintf(nomeWidget,"%d",i);\
        	strcat(nomeWidget,"_formCaiAll");\
all_caiAll_form[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xmFormWidgetClass,\
                        all_rowColumn_caiAll,\
                        XmNx, 3,\
                        XmNy, 4,\
			XmNresizePolicy, XmRESIZE_NONE,\
                        XmNheight, 32,\
                        XmNwidth, 32,\
                        NULL );\
        UxPutContext( all_caiAll_form[i], (char *) UxTelepermContext );\
\
/*\
Creazione dei caiAll\
Devo acquisire il background del parent per disegnarlo in transparent quando\
disattivato\
*/\
		get_something(all_caiAll_form[i],XmNbackground,&background_parent);\
\
		strcpy(nomeWidget,"");\
        	sprintf(nomeWidget,"%d",i);\
        	strcat(nomeWidget,"_CaiAll");\
\
all_caiAll[i]= XtVaCreateManagedWidget( nomeWidget,\
			xlCaiAllWidgetClass,\
                        all_caiAll_form[i],\
                        XmNx, 3,\
                        XmNy, 4,\
                        XmNheight, 25,\
                        XmNwidth, 25,\
/*			XmNtopOffset,TOPOFFSET,\
			XmNleftOffset,LEFTOFFSET,*/\
			XlNcolorBord,background_parent,\
			XmNtopAttachment,XmATTACH_FORM,\
			XmNleftAttachment,XmATTACH_FORM,\
			XlNtipoCai, CAI_A,\
#ifndef DESIGN_TIME\
                        XlNconfig, False,\
#endif\
			XlNstatus, SPENTO,\
                        NULL );\
        UxPutContext( all_caiAll[i], (char *) UxTelepermContext );\
\
\
		strcpy(nomeWidget,"");\
        	sprintf(nomeWidget,"%d",i);\
        	strcat(nomeWidget,"_labelNameAlarm");\
all_name_label[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xmLabelWidgetClass,\
                        all_rowColumn_nameAll,\
                        XmNx, 3,\
                        XmNy, 218,\
                        XmNheight, 32,\
                        XmNrecomputeSize, FALSE,\
                        /*XmNwidth, 250,*/\
			RES_CONVERT(XmNlabelString," "),\
                        NULL );\
\
        UxPutContext( all_name_label[i], (char *) UxTelepermContext );\
/*\
Istanzio label per descrizione allarmi\
*/\
	        strcpy(nomeWidget,"");\
                sprintf(nomeWidget,"%d",i);\
                strcat(nomeWidget,"_labelDescrAlarm");\
\
all_descr_label[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xmLabelWidgetClass,\
                        all_rowColumn_descrAll,\
                        XmNx, 3,\
                        XmNy, 4,\
                        XmNheight, 32,\
                        XmNrecomputeSize, FALSE,\
                        /*XmNwidth, 670,*/\
			RES_CONVERT(XmNlabelString," "),\
                        XmNalignment, XmALIGNMENT_CENTER,\
                        NULL );\
\
        UxPutContext( all_descr_label[i], (char *) UxTelepermContext );\
\
/*\
Istanzio label per data allarmi\
*/\
                strcpy(nomeWidget,"");\
                sprintf(nomeWidget,"%d",i);\
                strcat(nomeWidget,"_labelDataAlarm");\
\
all_data_label[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xmLabelWidgetClass,\
                        all_rowColumn_dataAll,\
                        XmNx, 3,\
                        XmNy, 4,\
                        XmNheight, 32,\
                        XmNrecomputeSize, FALSE,\
                        /*XmNwidth, 200,*/\
			RES_CONVERT(XmNlabelString," "),\
                        XmNalignment, XmALIGNMENT_END,\
                        NULL );\
\
        UxPutContext( all_data_label[i], (char *) UxTelepermContext );\
	\
	XtFree(nomeWidget);\
	}\
/*\
Creazione bottoni per scorrimento pagina allarmi\
*/\
	all_button_minus=XtVaCreateManagedWidget( "all_button_minus",\
                        xmPushButtonWidgetClass,\
                        all_formAll,\
                        XmNx, 1210,\
                        XmNy, 10,\
                        XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftOffset, 3,\
                        XmNleftWidget, all_rowColumn_dataAll,\
                        XmNtopOffset, 0,\
                        RES_CONVERT( XmNlabelString, "[-]" ),\
                        NULL );\
        UxPutContext( all_button_minus, (char *) UxTelepermContext );\
/*\
Callaback per comandi allarmi\
*/\
	XtAddCallback(all_button_minus, XmNactivateCallback,\
                    (XtCallbackProc)command_alarm,OL_INDIETRO_ALLARMI);\
\
        all_button_plus = XtVaCreateManagedWidget( "all_button_plus",\
                        xmPushButtonWidgetClass,\
                        all_formAll,\
                        XmNx, 1210,\
                        XmNy, 635,\
                        RES_CONVERT( XmNlabelString, "[+]" ),\
                        XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,\
                        XmNbottomOffset, 10,\
                        XmNbottomWidget, all_rowColumn_dataAll,\
                        XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftOffset, 4,\
                        XmNleftWidget, all_rowColumn_dataAll,\
                        NULL );\
        UxPutContext( all_button_plus, (char *) UxTelepermContext );\
	\
        XtAddCallback(all_button_plus, XmNactivateCallback,\
                    (XtCallbackProc)command_alarm,OL_AVANTI_ALLARMI);\
\
	all_button_n = XtVaCreateManagedWidget( "all_button_n",\
                        xmPushButtonWidgetClass,\
                        all_formAll,\
                        XmNx, 1210,\
                        XmNy, 690,\
                        RES_CONVERT( XmNlabelString, "[n]" ),\
                        XmNtopAttachment, XmATTACH_WIDGET,\
                        XmNtopOffset, 5,\
                        XmNtopWidget, all_button_plus,\
                        XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftOffset, 4,\
                        XmNleftWidget, all_rowColumn_dataAll,\
                        NULL );\
        UxPutContext( all_button_n, (char *) UxTelepermContext );\
	XtAddCallback(all_button_n, XmNactivateCallback,\
                    (XtCallbackProc)go_newest,NULL);\
\
\
for(i=0;i<NUMMAXZONE;i++)\
	{\
	\
	if(zone_status[i])   /* Se trovo una zona attiva richiedo Allarmi */\
		{\
		OlTeleperm_richiediAllarmi(database_simulatore,zone_status);\
		break;\
		}\
	}\
printf("MAINALLPAGE Ho richiesto gli allarmi\n");\
OlSetDatabasePunti(all_caiAll,MAXNUMALLVIS,database_simulatore);\
teleperm_refreshAllPage(all_form_topLevelShell);\
/*\
Parte per visualizzare immediatamente la situazione allarmi\
nella parte di header della pagina Allarmi.\
Viene settata la richiesta allarmi per la zona  0 (destinata ad essere\
la zona di servizio ) dopodiche ' viene risettata a\
zero la zona in zone_status e rinviata la richiesta allarmi per \
avere la situazione pulita.\
*/ \
\
if(prima_apertura_all)\
      {\
      /*zone_status[last_zone]=1;*/\
      zone_status[0]=1;\
      OlTeleperm_richiediAllarmi(database_simulatore,zone_status);\
      /*zone_status[last_zone]=0;*/\
      zone_status[0]=0;\
      OlTeleperm_richiediAllarmi(database_simulatore,zone_status);\
      prima_apertura_all=False;\
      }\
XtFree(nome_header);\
\
\
\
\
\
\
\
\
\


*teleperm_close_allPage.class: method
*teleperm_close_allPage.name: close_allPage
*teleperm_close_allPage.parent: teleperm
*teleperm_close_allPage.methodType: Boolean
*teleperm_close_allPage.methodArgs: 
*teleperm_close_allPage.methodBody: if((allPageOnScreen==-1) || (OlCanOpenAllarmPage(database_simulatore)))\
	return(False);\
XtRemoveTimeOut(timer_timerefreshAll); /*elimino timeoutRefresh */ \
XtDestroyWidget(all_form_topLevelShell); /*Distruggo l' interfaccia */\
/***********\
Parte destinata a liberazione memoria oggetti multipli\
***********/\
\
XtFree(lista_header_form);\
XtFree(lista_header_button);\
XtFree(lista_header_rowColumn); \
XtFree(lista_header_label); \
XtFree(all_caiAll_form); \
\
XtFree(all_caiAll);\
XtFree(all_name_label); \
XtFree(all_descr_label); \
\
XtFree(all_data_label); \
memset(&old_allarmi,0,sizeof(DATI_ALLARMI_SHM)); /*vecchi allarmi azzerati */\
	\
			\
/*\
Riattiva pulsanti navigazione\
*/\
XtSetSensitive(left,True);\
XtSetSensitive(right,True);\
XtSetSensitive(up,True);\
/*\
Ripristina modalita' allarmi pendenti\
*/\
modoPageAll=MODO_ALLARMI;\
allPageFlag=False;\
OlSetOpeningAllarmPage(database_simulatore,0); /* Posso settare a 1 ? */\
 \


*teleperm_refreshAllPageWidgets.class: method
*teleperm_refreshAllPageWidgets.name: refreshAllPageWidgets
*teleperm_refreshAllPageWidgets.parent: teleperm
*teleperm_refreshAllPageWidgets.methodType: int
*teleperm_refreshAllPageWidgets.methodArgs: 
*teleperm_refreshAllPageWidgets.methodBody: int i,tot_all_da_ric,tot_all_arc;\
        int kk;\
        Boolean zone_attive; /* almeno una zona attiva */\
        char appo[MAXLUNTOKEN],appo_descr[MAXLUNTOKEN],*str,*str1,*str2,descr_token[NUMTOKEN][MAXLUNTOKEN];\
        XmString stringa;\
        char *tipo_cai;\
        char gerarchiaNome[10* N_GERARCHIE];\
        DATI_ALLARMI_SHM app_allarmi;\
        int primo_set_zone_ko=0;\
        tot_all_da_ric=0;\
        tot_all_arc=0;\
        zone_attive=False;\
            for(kk=1;kk<NUMMAXZONE;kk++)\
                        {\
                        if(zone_status[kk]==1)\
                                {\
                                zone_attive=True; /* almeno una zona e' attiva */\
                                break;\
                                }\
                        }\
        /***************************************************************************\
        Parte riservata alla gestione di allarmi non validi\
        Gli allarmi non validi possono essere dovuti a diversi tipi di situazione:\
                1) selezione di una zona gia' selezionata da altro mmi\
                2) situazione di attesa temporanea\
                3) messaggio da Scada che non arrivera' piu'\
        ***************************************************************************/\
\
        if(!OlGetDataAllarmi(database_simulatore,&app_allarmi)) /* acquisisco all SHM */\
                {\
                printf("WARNING:Waiting for valid alarm data\n");\
                 for(kk=0;kk<MAXNUMALLVIS;kk++)\
                        {\
                        /*\
                        Se non vi sono dati validi, cancella visualizzazione allarmi\
                        */\
\
                        if((app_allarmi.descr[kk][0]==NULL) || !zone_attive )\
                                {\
                                stringa=XmStringCreateSimple("");\
                                set_something(all_name_label[kk],XmNlabelString,stringa);\
                                set_something(all_name_label[kk],XmNlabelString,stringa);\
                                set_something(all_descr_label[kk],XmNlabelString,stringa);\
                                XmStringFree(stringa);\
                                XtVaSetValues(all_name_label[kk],XmNbackground,def_background_butt,NULL);\
                                XtVaSetValues(all_descr_label[kk],XmNbackground,def_background_butt,NULL);\
                                XtVaSetValues(all_caiAll_form[kk],XmNbackground,def_background_butt,NULL);\
                                XtVaSetValues(all_data_label[kk],XmNbackground,def_background_butt,NULL);\
\
                                set_something(all_caiAll[kk],XlNstatus,(int)SPENTO);\
                                set_something(all_caiAll[kk],XlNvarGerarchia,"[-1][-1][-1][-1][-1][-1]");\
                                }\
                        /*\
                        setto a zero la vecchia SHM per innescare l' eventuale refresh\
                        */\
                        memset(&old_allarmi,0,sizeof(DATI_ALLARMI_SHM));\
                        }\
                /* Chiamo refresh per spegnere i Cai */\
                XlRefreshWidget(all_caiAll,MAXNUMALLVIS);\
        /*\
        Se e' stato premuto un bottone, verifica che non sia gia' segnalato (zone_ko==-1) e\
        setta il colore di segnalazione zona ko.\
        */\
                if((last_zone_pressed!=-1) && (zone_ko==-1) && zone_attive)\
                        {\
                        /* Cambio colore a bottone con zona ko */\
\
                        XtVaSetValues(lista_header_button[last_zone_pressed],RES_CONVERT(XmNbackground,"yellow"\
),NULL);\
                        zone_ko=last_zone_pressed;\
                        primo_set_zone_ko=zone_ko;\
                        /* Premuta zona ko -> disabilito altri pulsanti */\
                        for(kk=1;kk<num_zone;kk++)\
                                {\
                                if(kk!=zone_ko && selectable_zone[kk])\
                                        XtVaSetValues(lista_header_button[kk],XmNsensitive,False,NULL);\
                                }\
\
                        }\
        /*\
        Quando il tasto relativo a zona selezionata gia' da altro utente,\
        viene disabilitato; riabilita gli altri tasti e ripristina il colore originario\
        Tutti i tasti (cioe' le zone) saranno disabilitati.\
        */\
                if((zone_ko!=-1) && (zone_status[zone_ko]==0) &&\
                         (!primo_set_zone_ko)  &&  (zone_ko==last_zone_pressed))\
                        {\
                        for(kk=1;kk<num_zone;kk++)\
                                {\
                                if(selectable_zone[kk])  /* zona con pag esistente a livello 0 */\
                                        {\
                                        XtVaSetValues(lista_header_button[kk],XmNsensitive,True,NULL);\
                                        XtVaSetValues(lista_header_button[kk],XmNbackground,def_background_butt,NULL);\
                                        XtVaSetValues(lista_header_button[kk],XmNarmColor,def_armColor_butt,NULL);\
                                        XtVaSetValues(lista_header_button[kk],XmNtopShadowColor,def_topShadowColor_butt,NULL);\
                                        XtVaSetValues(lista_header_button[kk],XmNbottomShadowColor,def_bottomShadowColor_butt,NULL);\
                                        zone_status[kk]=0;\
                                        }\
                                }\
                        zone_ko=-1;  /* situazione di nuovo ok */\
                        }\
                primo_set_zone_ko=0;\
                return(0); /* esci da routine */\
                }\
        /*\
        Ripristino colore di eventuale zona_ko .\
        Questa parte viene eseguita quando sono stati trovati in una refresh precedente\
        dei dati non validi (caso 2) :situazione pero' non dovuta alla selezione di una pagina allarme\
        gia' selezionata da altro utente\
        */\
        if(zone_ko!=-1)\
                {\
                if(zone_status[zone_ko])\
                        {\
                        XtVaSetValues(lista_header_button[zone_ko],XmNarmColor,def_background_butt,NULL);\
                        XtVaSetValues(lista_header_button[zone_ko],XmNbackground,def_armColor_butt,NULL);\
                        }\
                else\
                        {\
                        XtVaSetValues(lista_header_button[zone_ko],XmNbackground,def_background_butt,NULL);\
                        XtVaSetValues(lista_header_button[zone_ko],XmNarmColor,def_armColor_butt,NULL);\
\
                        }\
                 for(kk=1;kk<num_zone;kk++)\
                      {\
                      if((kk!=zone_ko) && (selectable_zone[kk]))\
                      XtVaSetValues(lista_header_button[kk],XmNsensitive,True,NULL);\
                      }\
                zone_ko=-1;\
                last_zone_pressed=-1;\
                if(modoPageAll== MODO_ARCHIVIO)\
                        {\
                        OlTeleperm_richiediAllarmi(database_simulatore,zone_status);\
                        OlCommandAllarmi(database_simulatore,OL_MODO_ARCHIVIO);\
                        }\
                else\
                        OlTeleperm_richiediAllarmi(database_simulatore,zone_status);\
                }\
/*****************************************************************\
	Fine parte riservata a gestione dati non validi\
*****************************************************************/\
/*\
Innesco Refresh dei CaiAll\
*/\
XlRefreshWidget(all_caiAll,MAXNUMALLVIS);\
\
/*\
Verifico che ci sia stato qualche cambiamento nella situazione allarmi\
o che sia stato premuto o rilasciato qualche bottone per attivaz. zone\
*/\
if( (memcmp(&app_allarmi,&old_allarmi,sizeof(DATI_ALLARMI_SHM))!=0) || (memcmp(zone_status,zone_status_old,NUMMAXZONE*sizeof(int))) )\
	{\
	memcpy(&(old_allarmi),&app_allarmi,\
                sizeof(DATI_ALLARMI_SHM));\
	memcpy(zone_status_old,zone_status,\
                sizeof(int)*NUMMAXZONE);\
/*\
Debug prova\
*/\
printf("allarmi_da=%d allarmi_a=%d\n",app_allarmi.allarmi_da,app_allarmi.allarmi_a);\
/*\
Se cerco di visualizzare allarmi in archivio che non ci sono\
esco da modo ARCHIVIO e visualizzo allarmi da ric se ve ne sono\
*//*	\
	if(modoPageAll==MODO_ARCHIVIO)\
		{\
		if(app_allarmi.num_all_arc==0)\
			modoPageAll=MODO_ALLARMI;\
		}\
*/\
/*\
Se non esistono allarmi da riconoscere -> deseleziona il pulsante di acknowledge\
Se\
 il numero di allarmi e' < 16 deseleziona il tasto +\
*/\
	if(modoPageAll==MODO_ALLARMI)\
		{\
/* \
Setto pulsante acknowledge per riconoscere prim gli allarmi piu' vecchi\
*/\
		if((app_allarmi.num_all_da_ric >0) && (app_allarmi.allarmi_da == 1))\
			XtSetSensitive(ackal,True);\
		else \
			XtSetSensitive(ackal,False);\
/* \
Setto pulsante minus  disabilitato se n allarmi =0 o se inizio pag\
*/\
\
		if(app_allarmi.allarmi_da>1) /* non e' la pag + vecchia */\
			XtSetSensitive(all_button_minus,True);\
		else \
			XtSetSensitive(all_button_minus,False);\
/*\
Se non sono arrivato alla pagina piu' nuova button + e n attivi\
*/\
			\
		if(app_allarmi.num_all_da_ric<MAXNUMALLVIS)\
			{\
                        XtSetSensitive(all_button_plus,False);\
                        XtSetSensitive(all_button_n,False);\
			}\
		else\
			{\
			if((app_allarmi.allarmi_a<app_allarmi.num_all_da_ric)) \
				{\
				XtSetSensitive(all_button_plus,True);\
				XtSetSensitive(all_button_n,True);\
				}\
			else \
				{\
				XtSetSensitive(all_button_plus,False);\
				XtSetSensitive(all_button_n,False);\
				}\
			}\
		} \
	else if(modoPageAll==MODO_ARCHIVIO)\
		{\
		XtSetSensitive(ackal,False);\
		if(app_allarmi.allarmi_da!=1)\
                        XtSetSensitive(all_button_minus,True);\
                else XtSetSensitive(all_button_minus,False);\
\
		if(app_allarmi.num_all_arc<MAXNUMALLVIS)\
			{\
                        XtSetSensitive(all_button_plus,False);\
                        XtSetSensitive(all_button_n,False);\
			}\
		else\
			{\
               		 if((app_allarmi.allarmi_a<app_allarmi.num_all_arc))\
				{\
                        	XtSetSensitive(all_button_plus,True);\
				XtSetSensitive(all_button_n,True);\
				}\
       		         else \
				{\
				XtSetSensitive(all_button_plus,False);\
				XtSetSensitive(all_button_n,False);\
				}\
			}\
		}\
	\
/*\
Parte riguardante il totale degli allarmi da riconoscere e archiviati \
visualizzati in alto a dx nella pagina Allarmi.Il totale deve essere calcolato\
(in num_all_da_ric e num_all_arc vi sono solo gli allarmi delle zone selezionabili)\
*/\
	for(kk=1;kk<NUMMAXZONE;kk++)\
                {\
                if(selectable_zone[kk])\
                   {\
		   tot_all_da_ric+=app_allarmi.n_all_pen[kk];\
		   tot_all_arc+=app_allarmi.n_all_arc[kk];\
                   }\
      		if(zone_status[kk]==1)\
             		zone_attive=True; /* almeno una zona e' attiva */\
		}\
/*\
Setto i tasti per switch modo\
*/\
	if(modoPageAll==MODO_ALLARMI)\
                {\
		if(tot_all_arc>0 && zone_attive)\
			XtSetSensitive(all_old_button,True);\
		else XtSetSensitive(all_old_button,False);\
		XtSetSensitive(all_new_button,False);\
		}\
	else if(modoPageAll==MODO_ARCHIVIO)\
		{\
		XtSetSensitive(all_old_button,False);\
		XtSetSensitive(all_new_button,True);\
		}\
        sprintf(appo,"%d",tot_all_da_ric);\
        stringa=XmStringCreateSimple(appo);\
        set_something(all_new,XmNlabelString,stringa);\
        XmStringFree(stringa);\
        sprintf(appo,"%d",tot_all_arc);\
        stringa=XmStringCreateSimple(appo);\
        set_something(all_old,XmNlabelString,stringa);\
        XmStringFree(stringa);\
/*\
Parte riguardante la visualizzazione del numero di allarmi archiviati e pendenti per ogni\
Zona\
*/\
\
        for(kk=1;kk<num_zone;kk++)\
                {\
		if(selectable_zone[kk])\
			{\
       		        sprintf(appo,"%d",app_allarmi.n_all_pen[kk]);\
                 	stringa=XmStringCreateSimple(appo);\
                	set_something(lista_header_label[kk*4+1],XmNlabelString,stringa);\
\
 	                sprintf(appo,"%d",app_allarmi.n_all_arc[kk]);\
                        XmStringFree(stringa);\
        	        stringa=XmStringCreateSimple(appo);\
                	set_something(lista_header_label[kk*4+3],XmNlabelString,stringa);\
                        XmStringFree(stringa);\
			}\
                }\
	/* Se nessuna zona e' attiva invia richiesta cancellazione pagAll */\
	if (!zone_attive)\
		{\
		OlCommandAllarmi(database_simulatore,OL_CHIUDI_ALLARMI);\
		}\
/*\
Parte riguardante la visualizzazione degli allarmi e delle date per ogni allarme\
*/ \
        for(kk=0;kk<MAXNUMALLVIS;kk++)\
                {\
		\
		/* \
		Stringa con il NOME dell' allarme solo se allarme esiste\
		(tecnica di Marcello) . Se la descriz. non esiste o\
		non vi sono zone attive -> pagAllarmi e' vuota\
		*/\
		\
		if((app_allarmi.descr[kk][0]==NULL) || !zone_attive )\
			{\
			stringa=XmStringCreateSimple("");\
			set_something(all_name_label[kk],XmNlabelString,stringa);\
			set_something(all_descr_label[kk],XmNlabelString,stringa);\
			set_something(all_data_label[kk],XmNlabelString,stringa);	\
                        XmStringFree(stringa);\
\
			set_something(all_caiAll[kk],XlNstatus,(int)SPENTO);	\
			set_something(all_caiAll[kk],XlNvarGerarchia,"[-1][-1][-1][-1][-1][-1]");\
			XtVaSetValues(all_name_label[kk],XmNbackground,def_background_butt,NULL);\
                        XtVaSetValues(all_descr_label[kk],XmNbackground,def_background_butt,NULL);\
                        XtVaSetValues(all_caiAll_form[kk],XmNbackground,def_background_butt,NULL);\
                        XtVaSetValues(all_data_label[kk],XmNbackground,def_background_butt,NULL);\
			\
			}\
		else\
			{\
			/*\
			Imposto la gerarchia per ogni caiAll\
			Devo prima trasformare la sequenza di int in una stringa separata da []\
			*/\
			strcpy(gerarchiaValoreAll[kk],"");\
			for(i=0;i<N_GERARCHIE;i++)\
                        	{\
				strcpy(gerarchiaNome,"");\
			/*\
			Se livello !=-1 lo trasformo come unsigned per valori super. a 127\
			Devo scrivere -1 con strcpy.\
			*/\
                        	if(app_allarmi.hierarchy[kk][i]!=-1)\
                                                sprintf(gerarchiaNome,"\[%d\]",(unsigned char)(app_allarmi.hierarchy[kk][i]));\
                                        else\
                                                strcpy(gerarchiaNome,"[-1]");\
				strcat(gerarchiaValoreAll[kk],gerarchiaNome);\
                        	}\
			/*printf("gerarchiaValore=%s\n",gerarchiaValoreAll[kk]);*/\
\
			set_something(all_caiAll[kk],XlNvarGerarchia,gerarchiaValoreAll[kk]);\
\
			/*\
			Analisi descrizione\
			*/\
\
			strcpy(appo_descr,"");\
			\
			strcpy(appo,app_allarmi.descr[kk]);\
			str=strtok(appo,"_");\
			if(str)\
				strcpy(appo_descr,appo);\
			stringa=XmStringCreateSimple(appo_descr);\
			if(app_allarmi.emission[kk]==EMISSIONE)\
				XtVaSetValues(all_name_label[kk],RES_CONVERT(XmNbackground,def_background_emission), NULL);\
			else if(app_allarmi.emission[kk]==RIENTRO)\
                		XtVaSetValues(all_name_label[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);\
			set_something(all_name_label[kk],XmNlabelString,stringa);\
                        XmStringFree(stringa);\
\
			strcpy(appo_descr,"");\
		/*\
		Verifico tipo di CaiAll\
		*/\
			tipo_cai=strchr(app_allarmi.descr[kk],'$');\
			if(tipo_cai)\
				set_something(all_caiAll[kk],XlNtipoCaiAll,(int)( *(tipo_cai+1) ));\
		\
		/*\
		Filtro il KKS prima e dopo la DESCRIZIONE\
                Ho 3 campi separati da '|' :\
                      1) Descrizione principale\
                      2) Descrizione secondaria 1a parte\
                      3) Descrizione secondaria 2a parte\
\
Es:\
\
TAG| KKS  | |   Descrizione principale                | 1a sec| 2a secondaria\
\
  S_JR0400$A                       Turbo ALTERNATORE  |1o all | °k/cm. \
		\
*/\
			str=strtok((char *)NULL,"$");	\
			if(str)\
			{\
                                /* In descr_token[0] es: JR0400 */\
\
				strcpy(descr_token[0],str);\
 						/*printf("descr_token[0]=%s\n",descr_token[0]);*/\
				str=strtok((char *)NULL,SEPARATORALARM);\
                                /* In descr_token[1] descriz. principale */\
                                /* Salto tipo allarme e caratteri inutili */\
                                str++;\
                                while(*str==' ')\
                                   str++;\
				if(str)\
					strcpy(descr_token[1],str);\
				else strcpy(descr_token[1],"");\
 						/*printf("descr_token[1]=%s\n",descr_token[1]);*/\
\
				str=strtok((char *)NULL,SEPARATORALARM);\
                                /* In descr_token[2] 1a descriz. secondaria  */\
				if(str)\
					{\
					 strcpy(descr_token[2],str);\
 						/*printf("descr_token[2]=%s\n",descr_token[2]);*/\
					}\
				else strcpy(descr_token[2],"");\
\
				/*printf("appo_descr prima di strtok=%s\n",appo_descr);*/\
				str=strtok((char *)NULL,SEPARATORALARM);\
                                /* In descr_token[3] 2a descriz. secondaria  */\
					if(str)\
						{\
						strcpy(descr_token[3],str);\
 						/*printf("descr_token[3]=%s\n",descr_token[3]);*/\
\
						}\
					else strcpy(descr_token[3],"");\
				sprintf(appo_descr,"%-*.*s %-*.*s %-*.*s %-*.*s",5,6,descr_token[0],41,41,descr_token[1],10,10,descr_token[2],10,10,descr_token[3]);\
				/*printf("descrfinal=%s\n",appo_descr);*/\
				stringa=XmStringCreateSimple(appo_descr);\
				\
				/*\
				Setto lo stato del CaiAll associato\
				*/\
				if(tipo_cai)\
					set_something(all_caiAll[kk],XlNstatus,(int)(app_allarmi.emission[kk]));\
					\
        		        if(app_allarmi.emission[kk]==EMISSIONE)\
					{\
					XtVaSetValues(all_descr_label[kk],RES_CONVERT(XmNbackground, def_background_emission),NULL);\
					XtVaSetValues(all_caiAll_form[kk],RES_CONVERT(XmNbackground, def_background_emission),NULL);\
					}\
				else if(app_allarmi.emission[kk]==RIENTRO)\
					{\
                			XtVaSetValues(all_descr_label[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);\
                			XtVaSetValues(all_caiAll_form[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);\
					}\
				set_something(all_descr_label[kk],XmNlabelString,stringa);\
                        XmStringFree(stringa);\
			}/* end if(str) per 2a parte descr */\
		else\
			{\
			strcpy(appo_descr," ");\
			stringa=XmStringCreateSimple(appo_descr);\
			set_something(all_descr_label[kk],XmNlabelString,stringa);\
                        XmStringFree(stringa);\
			}\
\
/*\
Parte per DATA\
*/\
		\
			strcpy(appo,app_allarmi.data[kk]);\
			stringa=XmStringCreateSimple(appo);\
\
			if(app_allarmi.emission[kk]==EMISSIONE)\
					XtVaSetValues(all_data_label[kk],RES_CONVERT(XmNbackground, def_background_emission),NULL);\
				else if(app_allarmi.emission[kk]==RIENTRO)\
                			XtVaSetValues(all_data_label[kk],RES_CONVERT(XmNbackground, def_background_acknowledge),NULL);\
			set_something(all_data_label[kk],XmNalignment,XmALIGNMENT_END);\
			set_something(all_data_label[kk],XmNlabelString,stringa);\
                        XmStringFree(stringa);\
			}  /* end else sulla descr e zone_attive*/\
		} /*end for*/\
\
	} /* end if(memcmp) */\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\


*teleperm_openTopProcDisplay.class: method
*teleperm_openTopProcDisplay.name: openTopProcDisplay
*teleperm_openTopProcDisplay.parent: teleperm
*teleperm_openTopProcDisplay.methodType: int
*teleperm_openTopProcDisplay.methodArgs: 
*teleperm_openTopProcDisplay.methodBody: char pagName[255];\
char *tipo;\
XrmValue value;\
char risorsa[50];\
Display *disp;\
int i,indice_pagina;\
\
disp = XtDisplay(UxThis);\
\
sprintf(risorsa,"teleperm.topProcDisplay");\
        \
XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);\
        \
if( (value.addr == NULL) || (value.size == 0) )\
{\
   fprintf(stderr,"Warning: cannnot open NULL process display\n");\
   return(False);;\
}\
\
strncpy(pagName,value.addr,(int)value.size);\
\
indice_pagina = 0;       \
for( i=0;i < totale_pagine; i++ )\
   if( !strcmp(pagine[i].nome,pagName) )\
   {\
      indice_pagina = i;\
      break;\
   }\
\
if( i >= totale_pagine )\
{\
   fprintf(stderr,"Warning: topProcessDisplay not found in list\n");\
   return(False);;\
}\
\
teleperm_naviga(UxThis , GOTOPAG,indice_pagina);\
\
return(True);\
 

*teleperm_openStaz.class: method
*teleperm_openStaz.name: openStaz
*teleperm_openStaz.parent: teleperm
*teleperm_openStaz.methodType: int
*teleperm_openStaz.methodArgs: unsigned char *pagina;\
Widget Padre;\
unsigned char *nome_disp;\
unsigned char *sfondo_staz;\

*teleperm_openStaz.methodBody: Widget w;\
\
\
w=popup_topLevelShellStaz(pagina,Padre,elenco_display[screen_selezionato].nome,\
                          (BCK_OBJ *)sfondo_staz);\
\
\
XrmSetDatabase(XtDisplay((Widget)Padre),PagDb);\
\

*teleperm_openStaz.arguments: pagina, Padre, nome_disp, sfondo_staz
*teleperm_openStaz.pagina.def: "unsigned char", "*%pagina%"
*teleperm_openStaz.Padre.def: "Widget", "%Padre%"
*teleperm_openStaz.nome_disp.def: "unsigned char", "*%nome_disp%"
*teleperm_openStaz.sfondo_staz.def: "unsigned char", "*%sfondo_staz%"

*teleperm_application.class: method
*teleperm_application.name: application
*teleperm_application.parent: teleperm
*teleperm_application.methodType: int
*teleperm_application.methodArgs: Widget w;\

*teleperm_application.methodBody: printf("DEBUG: entrato nel metodo application operazione_attiva=%d\n",operazione_attiva);\
\
/*\
Verifica tipo di operazione \
*/\
switch(operazione_attiva)\
   {\
   case OPERAZIONE_NOP:\
      {\
      break; 0; /* No operation set */\
      }\
   case OPERAZIONE_INFO:\
      {\
      teleperm_info(UxThis,pEnv,w);\
      break ;\
      }\
    case OPERAZIONE_XAING:\
      {\
      teleperm_xaing(UxThis,pEnv,w);\
      break ;\
      }\
    case OPERAZIONE_XPLOT:\
      {\
      teleperm_xplot(UxThis,pEnv,w);\
      break ;\
      }\
   }\
\
return operazione_attiva;\

*teleperm_application.arguments: w
*teleperm_application.w.def: "Widget", "%w%"

*teleperm_info.class: method
*teleperm_info.name: info
*teleperm_info.parent: teleperm
*teleperm_info.methodType: int
*teleperm_info.methodArgs: Widget w;\

*teleperm_info.methodBody: FILE *fp;\
\
char *envvar;\
char nomefile[FILENAME_MAX];\
char editor[FILENAME_MAX];\
char comando[FILENAME_MAX*2];\
char filtro[FILENAME_MAX];\
char appo[200];\
char num_widget[100];\
char *tipo;\
XrmValue value;\
char risorsa[50];\
Display *disp;\
\
\
static int nwidget=1;\
\
\
if((envvar=(char *) getenv("TMPDIR"))==NULL)\
   {\
   strcpy(nomefile,DEFTMPDIR);\
   }\
else\
   strcpy(nomefile,envvar);\
\
\
\
/*\
Ricavo nome file\
*/\
sprintf(num_widget,"%d",nwidget);  /* No file di Info*/\
sprintf(appo,"%d",getpid());\
\
strcat(nomefile,TMPINFOFILE);\
strcat(nomefile,appo);\
strcat(nomefile,"_");\
strcat(nomefile,num_widget);\
strcat(nomefile,".tmp");\
\
\
\
\
if((fp=fopen(nomefile,"w"))==0)\
   {\
   printf("ERROR: Impossible to open the temporay file =%s \n",nomefile);\
   return -1;\
   }\
\
\
if(ScriviTestoInfo(w,fp))\
   fclose(fp);\
else\
   return -1;\
\
\
InfoUsed=True;\
/*\
Filtraggio file\
*/\
disp = XtDisplay(UxThis);\
\
sprintf(risorsa,"teleperm.InfoFilter"); \
XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);\
\
\
\
if( ((value.addr != NULL) && (value.size != 0)) )\
   {\
   /*\
   Esegue filtraggio\
   */\
   strncpy(filtro,value.addr,(int)value.size);\
\
   /*\
   Verifico che non ci siano solo spazi\
   */\
   strcpy(appo,"");\
   sscanf(filtro,"%s",appo);\
\
   if(strlen(appo))\
      {\
      strcpy(comando,"cat ");\
      strcat(comando,nomefile);\
      strcat(comando," | ");\
      strcat(comando,filtro);\
      strcat(comando," >> appo ");\
      system(comando);\
\
      /*\
      Copia file filtrato su originale\
      */\
      strcpy(comando,"cp ");\
      strcat(comando," appo ");\
      strcat(comando,nomefile);\
      system(comando);\
      system("rm appo");\
      }\
\
   }\
\
\
/*\
Vado ad editare il file \
*/\
\
if((envvar=(char *) getenv("TPEDITOR"))==NULL) /* Verifico editor teleperm */\
   {\
   strcpy(editor,DEFEDITOR);\
   }\
else\
   strcpy(editor,envvar);\
/*\
Preparazione comando\
*/\
if(strcmp(editor,"asedit"))  /* Se e' asedit inutile lanciare xterm */\
   strcpy(comando,"xterm -e ");\
else\
   strcpy(comando," ");\
strcat(comando,editor);\
strcat(comando," ");\
strcat(comando,nomefile);\
strcat(comando,"&");\
\
/* \
Esecuzione comando\
*/\
system(comando);\
\
nwidget++;\
return 1;\
\

*teleperm_info.arguments: w
*teleperm_info.w.def: "Widget", "%w%"

*teleperm_xaing.class: method
*teleperm_xaing.name: xaing
*teleperm_xaing.parent: teleperm
*teleperm_xaing.methodType: int
*teleperm_xaing.methodArgs: Widget w;\

*teleperm_xaing.methodBody: /*\
Verify if the widget accepts the Aing procedure\
*/\
if(AcceptAing(w))\
   {\
   if(!ActivateAing(w,drawingArea,\
                   elenco_display[0].nome,\
                   &(ListaWidVar[0])))\
                            popup_errorDialog("Variable not defined",\
                                drawingArea);\
   }\
else\
   printf("WARNIG: widget doesn't fit Aing\n");\

*teleperm_xaing.arguments: w
*teleperm_xaing.w.def: "Widget", "%w%"

*teleperm_xplot.class: method
*teleperm_xplot.name: xplot
*teleperm_xplot.parent: teleperm
*teleperm_xplot.methodType: int
*teleperm_xplot.methodArgs: Widget w;\

*teleperm_xplot.methodBody: if(AcceptPlot(w))\
   {\
   if(!ActivatePlot(w,\
                   drawingArea,\
                    elenco_display[0].nome,\
                   &(ListaWidVar[0])))\
                            popup_errorDialog("Variable not defined",\
                                drawingArea);\
   }\
else\
    printf("WARNIG: widget doesn't fit Plot or Topology not loaded \n");
*teleperm_xplot.arguments: w
*teleperm_xplot.w.def: "Widget", "%w%"

*teleperm_isOldAlarmPage.class: method
*teleperm_isOldAlarmPage.name: isOldAlarmPage
*teleperm_isOldAlarmPage.parent: teleperm
*teleperm_isOldAlarmPage.methodType: int
*teleperm_isOldAlarmPage.methodArgs: unsigned char *pag_candidata;\

*teleperm_isOldAlarmPage.methodBody: /*\
Metodo per determinare se su una pagina di tipo teleperm di nome "nome_pag", e' presente\
l' oggetto di libreria pagina Allarmi( XlAllarmi).\
Per ottenere questo, verifico se nel database risorse della pagina da esaminare\
e' presente nella risorsa elenco widget il nome del widget XlAllarmi\
*/\
XrmDatabase db;\
char nome_pag[FILENAME_MAX];\
char *tipo;\
XrmValue value;\
int ret;\
char *appo=NULL;\
/*\
Path full della pagina\
*/\
sprintf(nome_pag,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),pag_candidata);\
\
/*\
Carico DB risorse associato alla pagina\
*/\
if( (db = XrmGetFileDatabase(nome_pag)) == NULL )\
        {\
           fprintf(stderr,"Error. Cannot open page %s\n",nome_pag);\
           return(-1);\
        }\
/*\
Verifico se la risorsa esiste\
*/\
if(XrmGetResource(db,"elenco_wid0",(char *)NULL,&tipo,&value))\
   {\
             \
   if(!(appo=(char *)XtCalloc(1,(int)(value.size+1))))\
      {\
      fprintf(stderr,"ERROR: Impossible to allocate memory\n");\
      return -1;\
      }\
             \
      strncpy(appo,value.addr,(int)value.size);\
      if(strstr(appo,"Allarmi") )\
         ret=1;\
      else ret=0;\
             \
    }\
else\
    return -1;\
\
\
/*\
Destroy del db\
*/\
XrmDestroyDatabase(db);\
if(appo)\
   XtFree(appo);\
printf("DEBUG: pagina=%s ret=%d\n",pag_candidata,ret);\
\
\
return  ret;\

*teleperm_isOldAlarmPage.arguments: pag_candidata
*teleperm_isOldAlarmPage.pag_candidata.def: "unsigned char", "*%pag_candidata%"

*teleperm.static: true
*teleperm.name: teleperm
*teleperm.parent: NO_PARENT
*teleperm.parentExpression: UxParent
*teleperm.x: 150
*teleperm.y: 190
*teleperm.height: 660
*teleperm.mwmDecorations: MWM_DECOR_RESIZEH | MWM_DECOR_MINIMIZE
*teleperm.minHeight: 1024
*teleperm.minWidth: 1280
*teleperm.mwmMenu.source: public
*teleperm.mwmMenu: ""
*teleperm.createManaged: "false"

*formTop.class: form
*formTop.static: true
*formTop.name: formTop
*formTop.parent: teleperm
*formTop.resizePolicy: "resize_none"
*formTop.unitType: "pixels"
*formTop.x: 240
*formTop.y: 230
*formTop.width: 340
*formTop.height: 140
*formTop.navigationType: "none"
*formTop.traversalOn: "false"

*screenFooterForm.class: form
*screenFooterForm.static: true
*screenFooterForm.name: screenFooterForm
*screenFooterForm.parent: formTop
*screenFooterForm.resizePolicy: "resize_none"
*screenFooterForm.x: 0
*screenFooterForm.y: 610
*screenFooterForm.width: 1110
*screenFooterForm.height: 35
*screenFooterForm.leftAttachment: "attach_form"
*screenFooterForm.rightAttachment: "attach_form"
*screenFooterForm.topAttachment: "attach_none"
*screenFooterForm.topOffset: 0
*screenFooterForm.bottomAttachment: "attach_form"
*screenFooterForm.background.source: public
*screenFooterForm.background: "#a0a050"

*rcFooter.class: rowColumn
*rcFooter.static: true
*rcFooter.name: rcFooter
*rcFooter.parent: screenFooterForm
*rcFooter.x: 10
*rcFooter.y: 0
*rcFooter.width: 1210
*rcFooter.height: 30
*rcFooter.bottomAttachment: "attach_form"
*rcFooter.bottomOffset: 0
*rcFooter.leftAttachment: "attach_form"
*rcFooter.leftOffset: 50
*rcFooter.rightAttachment: "attach_form"
*rcFooter.rightOffset: 0
*rcFooter.topAttachment: "attach_form"
*rcFooter.topOffset: 0
*rcFooter.spacing: 30
*rcFooter.orientation: "horizontal"
*rcFooter.background.source: public
*rcFooter.background: "#a0a050"

*previous.class: pushButton
*previous.static: true
*previous.name: previous
*previous.parent: rcFooter
*previous.labelString: "Previous"
*previous.labelType: "pixmap"
*previous.labelPixmap: previousBMP
*previous.y: 0
*previous.activateCallback: {\
int numero_screen; /* numero screen di questa interfaccia */\
\
numero_screen=XScreenNumberOfScreen(XtScreen(UxWidget));\
/*\
Se il numero di screen e' quello dell' interfaccia cui appartiene qusto bottone,\
usa il previous altrimenti deve usare un gotopag.\
Se non facessi cosi' userei il previous della interfaccia remota.\
*/\
if(numero_screen==screen_selezionato)\
	teleperm_naviga(UxWidget,PREVIOUS,NULL);\
else\
	teleperm_naviga(UxWidget,GOTOPAG,pos_pag_curr);\
/*\
Es.:\
Se sono sullo screen 0	con l' ultima chiamata attivo la pagina di indice pos_pag_curr (screen 0)0\
sullo screen 1. Verranno aggiornate le var pos_pag_curr e pos_pag_new sullo screen 1 dalla\
procedura teleperm_navigation.\
*/\
\
}
*previous.background.source: public
*previous.background: "#ffefd5"

*left.class: pushButton
*left.static: true
*left.name: left
*left.parent: rcFooter
*left.labelString: "Left"
*left.labelPixmap: leftBMP
*left.labelType: "pixmap"
*left.activateCallback: {\
\
  teleperm_naviga(UxWidget,LEFT,NULL);\
\
\
}
*left.background.source: public
*left.background: "#ffefd5"
*left.x: 590
*left.y: -1

*up.class: pushButton
*up.static: true
*up.name: up
*up.parent: rcFooter
*up.labelString: "Up"
*up.labelPixmap: upBMP
*up.labelType: "pixmap"
*up.activateCallback: {\
  teleperm_naviga(UxWidget,UP,NULL);\
\
\
}
*up.background.source: public
*up.background: "#ffefd5"

*right.class: pushButton
*right.static: true
*right.name: right
*right.parent: rcFooter
*right.labelString: "Right"
*right.labelPixmap: rightBMP
*right.labelType: "pixmap"
*right.activateCallback: {\
  teleperm_naviga(UxWidget,RIGTH,NULL);\
\
\
}
*right.background.source: public
*right.background: "#ffefd5"
*right.bottomShadowColor: "#feeed4"
*right.x: 590
*right.y: -1

*swscreen.class: pushButton
*swscreen.static: true
*swscreen.name: swscreen
*swscreen.parent: rcFooter
*swscreen.labelString: "switch scr"
*swscreen.labelPixmap: swscreenBMP
*swscreen.labelType: "pixmap"
*swscreen.activateCallback: {\
int numero_screen; /* per determinare quale pixmap usare */\
int stato;\
char nome_bitmap[256];\
 \
teleperm_switchScreen(teleperm,&UxEnv);\
\
teleperm_drawPush(teleperm,&UxEnv, UxWidget,swscreenBMP);\
\
if( screen_switched != True )\
\
   screen_switched = True;\
else\
   screen_switched = False;\
  \
\
\
}
*swscreen.background.source: public
*swscreen.background: "#ffefd5"
*swscreen.x: 403
*swscreen.y: 13

*ackaud.class: pushButton
*ackaud.static: true
*ackaud.name: ackaud
*ackaud.parent: rcFooter
*ackaud.labelString: "Alarm Off"
*ackaud.labelPixmap: ackaudBMP
*ackaud.labelType: "pixmap"
*ackaud.background.source: public
*ackaud.background: "#ffefd5"

*ackal.class: pushButton
*ackal.static: true
*ackal.name: ackal
*ackal.parent: rcFooter
*ackal.labelString: "Ack Alarm"
*ackal.labelPixmap: ackalBMP
*ackal.labelType: "pixmap"
*ackal.background.source: public
*ackal.background: "#ffefd5"
*ackal.activateCallback: {\
if(allPageOnScreen==-1)\
	return;\
else\
 OlCommandAllarmi(database_simulatore,OL_RICONOSCI_ALLARMI);\
}

*hardcopy.class: pushButton
*hardcopy.static: true
*hardcopy.name: hardcopy
*hardcopy.parent: rcFooter
*hardcopy.labelString: "Hardcopy"
*hardcopy.labelPixmap: hardcopyBMP
*hardcopy.labelType: "pixmap"
*hardcopy.background.source: public
*hardcopy.background: "#ffefd5"
*hardcopy.activateCallback: {\
if(allPageOnScreen!=-1)\
{\
	if(!PrintAllarmi(all_form_topLevelShell))\
		fprintf(stderr,"Hardcopy error on Alarm Page\n");	\
}\
else	\
{\
\
\
if(!PrintScreen(drawingArea,"nome_disp","Pagina","False",Pag->sfondo))\
   fprintf(stderr,"Hardcopy error\n");\
}\
\
}

*help.class: pushButton
*help.static: true
*help.name: help
*help.parent: rcFooter
*help.labelString: "Help"
*help.labelPixmap: helpBMP
*help.labelType: "pixmap"
*help.background.source: public
*help.background: "#ffefd5"
*help.x: 590
*help.y: -1
*help.activateCallback: {\
/*\
Setta operazione attiva come INFO.\
\
Passaggi leciti:\
NOP-> INFO\
INFO->NOP\
*/\
if(operazione_attiva==OPERAZIONE_NOP)\
   {\
   operazione_attiva=OPERAZIONE_INFO;\
   XtVaSetValues(aing,XmNsensitive,False,NULL);\
   XtVaSetValues(plot,XmNsensitive,False,NULL);\
   }\
else if(operazione_attiva==OPERAZIONE_INFO)\
   {\
   operazione_attiva=OPERAZIONE_NOP;\
   XtVaSetValues(aing,XmNsensitive,True,NULL);\
   XtVaSetValues(plot,XmNsensitive,True,NULL);\
   }\
else return;\
\
teleperm_drawPush(teleperm,&UxEnv, UxWidget,helpBMP);\
\
}

*screenHeaderForm.class: form
*screenHeaderForm.static: true
*screenHeaderForm.name: screenHeaderForm
*screenHeaderForm.parent: formTop
*screenHeaderForm.resizePolicy: "resize_none"
*screenHeaderForm.x: 290
*screenHeaderForm.y: 50
*screenHeaderForm.width: 990
*screenHeaderForm.height: 30
*screenHeaderForm.leftAttachment: "attach_form"
*screenHeaderForm.rightAttachment: "attach_form"
*screenHeaderForm.topAttachment: "attach_form"
*screenHeaderForm.background.source: public
*screenHeaderForm.background: "#a0a050"
*screenHeaderForm.topOffset: 0

*rcProcess.class: rowColumn
*rcProcess.static: true
*rcProcess.name: rcProcess
*rcProcess.parent: screenHeaderForm
*rcProcess.x: 600
*rcProcess.y: 0
*rcProcess.width: 140
*rcProcess.height: 40
*rcProcess.orientation: "horizontal"
*rcProcess.bottomAttachment: "attach_form"
*rcProcess.bottomOffset: 2
*rcProcess.topAttachment: "attach_form"
*rcProcess.topOffset: 2
*rcProcess.marginHeight: 0
*rcProcess.marginWidth: 0
*rcProcess.background.source: public
*rcProcess.background: "#8fbc8f"

*proceso.class: pushButton
*proceso.static: true
*proceso.name: proceso
*proceso.parent: rcProcess
*proceso.labelString.source: public
*proceso.labelString: "Proceso"
*proceso.x: 0
*proceso.y: 0
*proceso.background.source: public
*proceso.background: "PapayaWhip"
*proceso.width: 90

*processDisplay.class: pushButton
*processDisplay.static: true
*processDisplay.name: processDisplay
*processDisplay.parent: rcProcess
*processDisplay.labelString: "Up"
*processDisplay.labelPixmap: "overview.bmp"
*processDisplay.labelType: "pixmap"
*processDisplay.width: 30
*processDisplay.x: 30
*processDisplay.y: 0
*processDisplay.background.source: public
*processDisplay.background: "PapayaWhip"
*processDisplay.activateCallback: {\
int retval;\
\
retval = teleperm_openTopProcDisplay(teleperm,&UxEnv); \
}

*formSystem.class: form
*formSystem.static: true
*formSystem.name: formSystem
*formSystem.parent: screenHeaderForm
*formSystem.resizePolicy: "resize_none"
*formSystem.x: 880
*formSystem.y: 10
*formSystem.bottomAttachment: "attach_form"
*formSystem.bottomOffset: 2
*formSystem.rightAttachment: "attach_form"
*formSystem.rightOffset: 30
*formSystem.topAttachment: "attach_form"
*formSystem.topOffset: 2

*menuSystem.class: rowColumn
*menuSystem.static: true
*menuSystem.name: menuSystem
*menuSystem.parent: formSystem
*menuSystem.rowColumnType: "menu_bar"
*menuSystem.menuAccelerator: "<KeyUp>F10"
*menuSystem.x: 10
*menuSystem.y: 0
*menuSystem.bottomAttachment: "attach_form"
*menuSystem.topAttachment: "attach_form"
*menuSystem.leftAttachment: "attach_form"
*menuSystem.rightAttachment: "attach_form"
*menuSystem.background: "#ffefd5"

*menuSystem_rc1.class: rowColumn
*menuSystem_rc1.static: true
*menuSystem_rc1.name: menuSystem_rc1
*menuSystem_rc1.parent: menuSystem
*menuSystem_rc1.rowColumnType: "menu_pulldown"

*menuSystem_rc1_b7.class: separatorGadget
*menuSystem_rc1_b7.static: true
*menuSystem_rc1_b7.name: menuSystem_rc1_b7
*menuSystem_rc1_b7.parent: menuSystem_rc1

*logoff.class: pushButton
*logoff.static: true
*logoff.name: logoff
*logoff.parent: menuSystem_rc1
*logoff.labelString: "logoff "
*logoff.labelType: "pixmap"
*logoff.labelPixmap.source: public
*logoff.labelPixmap: "logon.bmp"
*logoff.activateCallback: {\
extern int password_ok;\
extern void quit_proc();\
extern swidget popup_password();\
\
/* chiamo il metodo di close\
*/\
popup_password( teleperm );\
\
}

*menuSystem_rc1_b8.class: separatorGadget
*menuSystem_rc1_b8.static: true
*menuSystem_rc1_b8.name: menuSystem_rc1_b8
*menuSystem_rc1_b8.parent: menuSystem_rc1

*commonAck.class: pushButton
*commonAck.static: true
*commonAck.name: commonAck
*commonAck.parent: menuSystem_rc1
*commonAck.labelString: "Common Ack"
*commonAck.labelPixmap.source: public
*commonAck.labelPixmap: "logon.bmp"
*commonAck.labelType: "pixmap"
*commonAck.activateCallback.source: public
*commonAck.activateCallback: 

*menuSystem_rc1_b9.class: separatorGadget
*menuSystem_rc1_b9.static: true
*menuSystem_rc1_b9.name: menuSystem_rc1_b9
*menuSystem_rc1_b9.parent: menuSystem_rc1

*logSelection.class: pushButton
*logSelection.static: true
*logSelection.name: logSelection
*logSelection.parent: menuSystem_rc1
*logSelection.labelString: "LogSelection"
*logSelection.labelPixmap.source: public
*logSelection.labelPixmap: "logon.bmp"
*logSelection.labelType: "pixmap"
*logSelection.activateCallback.source: public
*logSelection.activateCallback: 

*menuSystem_rc1_b10.class: separatorGadget
*menuSystem_rc1_b10.static: true
*menuSystem_rc1_b10.name: menuSystem_rc1_b10
*menuSystem_rc1_b10.parent: menuSystem_rc1

*IncidentRew.class: pushButton
*IncidentRew.static: true
*IncidentRew.name: IncidentRew
*IncidentRew.parent: menuSystem_rc1
*IncidentRew.labelString: "IncidentReview"
*IncidentRew.labelPixmap.source: public
*IncidentRew.labelPixmap: "logon.bmp"
*IncidentRew.labelType: "pixmap"
*IncidentRew.activateCallback.source: public
*IncidentRew.activateCallback: 

*menuSystem_rc1_b11.class: separatorGadget
*menuSystem_rc1_b11.static: true
*menuSystem_rc1_b11.name: menuSystem_rc1_b11
*menuSystem_rc1_b11.parent: menuSystem_rc1

*longTermArc.class: pushButton
*longTermArc.static: true
*longTermArc.name: longTermArc
*longTermArc.parent: menuSystem_rc1
*longTermArc.labelString: "Long Term Arc"
*longTermArc.labelPixmap.source: public
*longTermArc.labelPixmap: "logon.bmp"
*longTermArc.labelType: "pixmap"
*longTermArc.activateCallback.source: public
*longTermArc.activateCallback: 

*menuSystem_rc1_b12.class: separatorGadget
*menuSystem_rc1_b12.static: true
*menuSystem_rc1_b12.name: menuSystem_rc1_b12
*menuSystem_rc1_b12.parent: menuSystem_rc1

*aing.class: pushButton
*aing.static: true
*aing.name: aing
*aing.parent: menuSystem_rc1
*aing.labelString: "Aing"
*aing.labelPixmap.source: public
*aing.labelPixmap: "logon.bmp"
*aing.labelType: "string"
*aing.mnemonic: "A"
*aing.activateCallback: {\
char aingColor[256];\
char *tipo;\
XrmValue value;\
\
if(operazione_attiva==OPERAZIONE_NOP)\
   {\
    \
   operazione_attiva=OPERAZIONE_XAING;\
\
   /*\
   Cerco il colore come risorsa da run_time\
   */\
   XrmGetResource((XtDisplay(aing))->db,"teleperm.aingColor",(char *)NULL,&tipo,&value);\
   if(value.size)\
      strncpy(aingColor,value.addr,(int)value.size);\
   else \
      strcpy(aingColor,"blue");\
\
   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNbackground, aingColor),NULL);\
   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNlabelString,"Aing"),NULL);\
   XtVaSetValues(help,XmNsensitive,False,NULL);\
   XtVaSetValues(plot,XmNsensitive,False,NULL);\
   }\
else if(operazione_attiva==OPERAZIONE_XAING)\
   {\
   operazione_attiva=OPERAZIONE_NOP;\
   XtVaSetValues(menuSystem_csbutt,XmNbackground,def_col_menuSystem,NULL);\
   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNlabelString,SISTEMLABEL),NULL);\
   XtVaSetValues(help,XmNsensitive,True,NULL);\
   XtVaSetValues(plot,XmNsensitive,True,NULL);\
   }\
else return;\
}

*menuSystem_rc1_b13.class: separatorGadget
*menuSystem_rc1_b13.static: true
*menuSystem_rc1_b13.name: menuSystem_rc1_b13
*menuSystem_rc1_b13.parent: menuSystem_rc1

*plot.class: pushButton
*plot.static: true
*plot.name: plot
*plot.parent: menuSystem_rc1
*plot.labelString: "Plot"
*plot.mnemonic: "P"
*plot.activateCallback: {\
char plotColor[256];\
char *tipo;\
XrmValue value;\
\
\
if(operazione_attiva==OPERAZIONE_NOP)\
   {\
\
   operazione_attiva=OPERAZIONE_XPLOT;\
\
           /*\
           Cerco il colore come risorsa da run_time\
           */\
           XrmGetResource((XtDisplay(aing))->db,"teleperm.plotColor",(char *)NULL,&tipo,&value);\
           if(value.size)\
              strncpy(plotColor,value.addr,(int)value.size);\
           else\
              strcpy(plotColor,"green");\
\
\
   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNbackground, plotColor),NULL);\
   XtVaSetValues(help,XmNsensitive,False,NULL);\
   XtVaSetValues(aing,XmNsensitive,False,NULL);\
   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNlabelString,"Plot"),NULL);\
   }\
else if(operazione_attiva==OPERAZIONE_XPLOT)\
   {\
   operazione_attiva=OPERAZIONE_NOP;\
   XtVaSetValues(menuSystem_csbutt,XmNbackground,def_col_menuSystem,NULL);\
   XtVaSetValues(menuSystem_csbutt,RES_CONVERT(XmNlabelString,SISTEMLABEL),NULL);\
   XtVaSetValues(help,XmNsensitive,True,NULL);\
   XtVaSetValues(aing,XmNsensitive,True,NULL);\
   }\
else return;\
}

*menuSystem_csbutt.class: cascadeButton
*menuSystem_csbutt.static: true
*menuSystem_csbutt.name: menuSystem_csbutt
*menuSystem_csbutt.parent: menuSystem
*menuSystem_csbutt.labelString: SISTEMLABEL
*menuSystem_csbutt.subMenuId: "menuSystem_rc1"
*menuSystem_csbutt.x: 0
*menuSystem_csbutt.y: 0
*menuSystem_csbutt.background.source: public
*menuSystem_csbutt.background: "#ffefd5"

*rcData.class: rowColumn
*rcData.static: true
*rcData.name: rcData
*rcData.parent: screenHeaderForm
*rcData.x: 5
*rcData.y: 2
*rcData.height: 26
*rcData.orientation: "horizontal"
*rcData.bottomAttachment: "attach_form"
*rcData.bottomOffset: 2
*rcData.topAttachment: "attach_form"
*rcData.topOffset: 2
*rcData.leftAttachment: "attach_form"
*rcData.leftOffset: 5
*rcData.spacing: 10
*rcData.background.source: public
*rcData.background: "DarkSeaGreen"
*rcData.marginWidth: 2
*rcData.width: 175

*Data.class: label
*Data.static: true
*Data.name: Data
*Data.parent: rcData
*Data.labelString: "27-11-96"
*Data.width: 78
*Data.background.source: public
*Data.background: "DarkSeaGreen"
*Data.foreground.source: public
*Data.foreground: "yellow"
*Data.fontList.source: public
*Data.fontList: "helvetica10"

*Ora.class: label
*Ora.static: true
*Ora.name: Ora
*Ora.parent: rcData
*Ora.labelString: "09:32:54"
*Ora.width: 88
*Ora.background.source: public
*Ora.background: "#8fbc8f"
*Ora.foreground.source: public
*Ora.foreground: "yellow"
*Ora.fontList: "helvetica10"
*Ora.height: 20

*formCaiPlant.class: form
*formCaiPlant.static: true
*formCaiPlant.name: formCaiPlant
*formCaiPlant.parent: screenHeaderForm
*formCaiPlant.resizePolicy: "resize_none"
*formCaiPlant.x: 190
*formCaiPlant.y: 2
*formCaiPlant.width: 380
*formCaiPlant.height: 26
*formCaiPlant.bottomAttachment: "attach_form"
*formCaiPlant.bottomOffset: 2
*formCaiPlant.topAttachment: "attach_form"
*formCaiPlant.topOffset: 2
*formCaiPlant.leftAttachment: "attach_form"
*formCaiPlant.leftOffset: 190
*formCaiPlant.background.source: public
*formCaiPlant.background: "DarkSeaGreen"

*isa.class: pushButton
*isa.static: true
*isa.name: isa
*isa.parent: formCaiPlant
*isa.labelString.source: public
*isa.labelString: "ISA"
*isa.width: 45
*isa.x: 150
*isa.y: 0
*isa.background.source: public
*isa.background: "SpringGreen3"
*isa.marginHeight: 1
*isa.marginWidth: 1
*isa.height: 25
*isa.activateCallback: {\
int numero_screen;\
if(allPageOnScreen!=-1)\
	return;\
teleperm_naviga(UxWidget,GOTOPAG,INDALLPAG);\
}

*plantOverview.class: pushButton
*plantOverview.static: true
*plantOverview.name: plantOverview
*plantOverview.parent: formCaiPlant
*plantOverview.labelString: "Up"
*plantOverview.labelType: "pixmap"
*plantOverview.width: 38
*plantOverview.x: 120
*plantOverview.y: 0
*plantOverview.labelPixmap: "overview.bmp"
*plantOverview.background.source: public
*plantOverview.background: "#8fbc8f"
*plantOverview.marginHeight: 1
*plantOverview.marginWidth: 1
*plantOverview.activateCallback: {\
teleperm_naviga(UxWidget,PLANT_OVW,NULL);\
\
\
}
*plantOverview.height: 25
*plantOverview.bottomAttachment: "attach_form"
*plantOverview.topAttachment: "attach_form"

*plantButton.class: pushButton
*plantButton.static: true
*plantButton.name: plantButton
*plantButton.parent: formCaiPlant
*plantButton.isCompound: "true"
*plantButton.compoundIcon: "push.xpm"
*plantButton.compoundName: "push_Button"
*plantButton.x: 10
*plantButton.y: 0
*plantButton.width: 90
*plantButton.height: 27
*plantButton.labelString: "PLANT"
*plantButton.activateCallback: {\
int i,kk;\
char *nomePushButton;\
int *lista_ind,npag;\
char *gerarchiaValore;\
char nomeCai[100];\
char *nomeLabel;\
char *gerarchiaNome;\
Position xShell,yShell,xButton;\
Dimension heightButton;\
extern int PagIsTeleperm();\
extern OlTreeObject root_oltree;\
int indice_fa;\
char appo[100],*str;\
\
gerarchiaNome=NULL;\
gerarchiaValore=NULL;\
/*\
Se esiste qualche altro pullDownMenu eliminalo\
*/\
if (pullDownActive)\
	{				/* Verifico se e' questo stesso Menu */\
	if(pullMenuOn==PLANTMENUON)   /* Second click -> close VertMenu */\
		{\
		XtRemoveTimeOut(timer_timerefreshCai);\
		UxDestroyInterface(*pullDownActive);\
		XtFree(listaCaiVr);\
		XtFree(listaCaiFormVr);		\
                XtFree(listaPushButtonPlant);\
                XtFree(listaPlantAsd);\
		pullDownActive=NULL;\
	        pullMenuOn=0;\
		return;\
		}\
	else\
		{\
				/* elimino altro pullDownMenu */\
		XtRemoveTimeOut(timer_timerefreshCai);\
		UxDestroyInterface(*pullDownActive); /* other pullDownMenu Type */\
		XtFree(listaCaiVr);\
		XtFree(listaCaiFormVr);\
                XtFree(listaPushButton);\
		pullDownActive=NULL;\
		}\
	\
	}\
\
if(!num_telepag)\
	return;     /* no pages under Vertical hierarchy */if( (listaPushButtonPlant = (Widget *) XtCalloc(1, num_telepag * sizeof(Widget)) ) == NULL)\
{\
   printf("plantMenu. Error in malloc: listaPushButton\n");\
   return;\
}\
/*\
Assegno al puntatore dell' interfaccia listaPushButton listaPushButtonVr\
cosi' da poterlo poi eliminare da qualunque interfaccia\
*/\
listaPushButton=listaPushButtonPlant;\
if( (listaCaiVr = (Widget *) XtCalloc(1, num_telepag *MAXNUMCAIXLINE*sizeof(Widget)) ) == NULL)\
{\
   printf("plantMenu. Error in malloc: listaCai\n");\
   return;\
}\
\
if ( (listaCaiFormVr = (Widget *) XtCalloc(1, num_telepag * sizeof(Widget)) ) == NULL)\
{\
   printf("vertHierMenu. Error in malloc: listaCaiForm\n");\
   return;\
}\
if ( (listaPlantAsd = (Widget *) XtCalloc(1, num_telepag * sizeof(Widget)) ) == NULL)\
{\
   printf("vertHierMenu. Error in malloc: listaPlantAsd\n");\
   return;\
}\
get_something(	teleperm,XmNx,&xShell);		\
get_something(	teleperm,XmNy,&yShell);		\
get_something(	formCaiPlant,XmNx,&xButton);\
\
\
PlantMenu = XtVaCreatePopupShell("PlantMenu",\
			topLevelShellWidgetClass,\
			plantButton,\
			XmNallowShellResize, True,\
                        XmNx, (xShell+xButton),\
                        XmNy, (yShell+30),\
			XmNmwmDecorations, 0 ,\
			NULL );\
UxPutContext( PlantMenu, (char *) UxTelepermContext );\
\
/*\
Point to pullDownMenu\
*/\
\
pullDownActive=&PlantMenu;\
pullMenuOn=PLANTMENUON; /* menu attivo Plantmenu */\
\
\
PlantPane=XtVaCreateManagedWidget( "plantPane",\
                        xmFormWidgetClass,\
                        PlantMenu,\
                        NULL );\
\
UxPutContext( PlantPane, (char *) UxTelepermContext );\
\
RowPull=XtVaCreateManagedWidget( "rowColumnPull",\
				xmRowColumnWidgetClass,\
				PlantPane,\
				XmNpacking,XmPACK_COLUMN,\
				XmNorientation,XmHORIZONTAL,\
				XmNnumColumns, num_telepag,\
				XmNtopAttachment,XmATTACH_FORM,\
				XmNleftAttachment,XmATTACH_FORM,\
				NULL);\
UxPutContext( RowPull, (char *) UxTelepermContext );\
\
i=0;\
for(kk=0; kk < num_zone ; kk++)\
{\
 if(selectable_zone[kk])\
  {\
    		/*      Ricavo nome del Bottone 	*/\
   if( (nomePushButton = XtCalloc(1, sizeof(char)* (strlen(pagine[selectable_zone[kk]].descrizione) +20) )) == NULL)\
   {\
      printf("plantMenu Error in malloc: nomePushButton\n");\
      return;\
   }\
   strcpy(nomePushButton, pagine[selectable_zone[kk] ].descrizione);\
 \
  if( (nomeLabel = XtCalloc(1, sizeof(char)* (strlen(pagine[selectable_zone[kk]].descrizione) +20) )) == NULL)\
   {\
      printf("plantMenu Error in malloc: nomeLabel\n");\
      return;\
   }\
\
\
  if( (gerarchiaNome = XtCalloc(1, sizeof(char)* (strlen(pagine[selectable_zone[kk]].gerarchia) +20) )) == NULL)\
   {\
      printf("plantMenu Error in malloc: nomeLabel\n");\
      return;\
   }\
  if( (gerarchiaValore = XtCalloc(1, sizeof(char)* (strlen(pagine[selectable_zone[kk]].gerarchia) +20) )) == NULL)\
   {\
      printf("plantMenu Error in malloc: nomeLabel\n");\
      return;\
   }\
\
strcpy(gerarchiaNome,pagine[selectable_zone[kk]].gerarchia);\
hierarchy_format_new(gerarchiaValore,gerarchiaNome);\
\
/*printf("gerarchiaValore=%s\n",gerarchiaValore);*/\
\
 strcpy(nomeLabel,"CAI of ");\
 strcat(nomeLabel,pagine[selectable_zone[kk]].descrizione);\
\
   /* push button */\
if(i==0)\
  listaPushButtonPlant[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmPushButtonWidgetClass,\
                        RowPull,\
/*\
			XmNtopAttachment,XmATTACH_FORM,\
			XmNleftAttachment,XmATTACH_FORM,\
*/  \
                        RES_CONVERT( XmNlabelString, nomePushButton ),\
                        NULL );\
else\
  listaPushButtonPlant[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmPushButtonWidgetClass,\
                        RowPull,\
/*\
			XmNtopAttachment,XmATTACH_WIDGET,\
			XmNleftAttachment,XmATTACH_FORM,\
			XmNtopWidget,listaPushButtonPlant[i-1],\
*/\
                        RES_CONVERT( XmNlabelString, nomePushButton ),\
                        NULL );	\
\
   UxPutContext( listaPushButtonPlant[i], (char *) UxTelepermContext );\
\
   XtAddCallback(listaPushButtonPlant[i], XmNactivateCallback,\
                    (XtCallbackProc)view_fa,selectable_zone[kk] ); \
\
\
/*\
Costruisco Nome form dei Cai\
*/\
strcat(nomePushButton,"FORM");\
/*printf("nomeformCai=%s\n",nomePushButton);*/\
\
listaCaiFormVr[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmFormWidgetClass,\
                        RowPull,\
                        XmNwidth, 250,\
                       	RES_CONVERT( XmNbackground, "#000000"),\
			NULL );\
\
UxPutContext( listaCaiFormVr[i], (char *) UxTelepermContext );\
\
/*\
Creo lista di bottoni ASD per Plant Menu' \
*/\
strcpy(nomePushButton,"");\
sprintf(nomePushButton,"%d",i);\
strcat(nomePushButton,"ASD");\
\
listaPlantAsd[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmPushButtonWidgetClass,\
                        listaCaiFormVr[i],\
                        XmNwidth, 45,\
			XmNheight, 25,\
			XmNtopAttachment,XmATTACH_FORM,\
			XmNleftAttachment,XmATTACH_FORM,\
			XmNleftOffset,LEFTOFFSET,\
			XmNtopOffset,TOPOFFSET,\
			NULL );\
\
UxPutContext( listaPlantAsd[i], (char *) UxTelepermContext );\
\
XtAddCallback(listaPlantAsd[i], XmNactivateCallback,\
                    (XtCallbackProc)open_allPag_fa,kk ); \
\
build_cai(listaCaiVr,nomeLabel,listaCaiFormVr[i],listaPlantAsd[i],gerarchiaValore,i);\
\
\
\
   XtFree(nomePushButton);  \
   XtFree(nomeLabel);\
if(gerarchiaNome)\
   XtFree(gerarchiaNome);\
if(gerarchiaValore)\
   XtFree(gerarchiaValore);\
  i++; /*incremento contatore lista oggetti */\
   /*printf("i=%d selectable_zone[%d]=%d\n",i,kk,selectable_zone[kk]);*/\
  }/* end if selectable_zone */\
}/* end for */\
printf("NUM_TELEPAG=%d i=%d\n",num_telepag,i);\
npagPulldown=i*MAXNUMCAIXLINE;\
UxPopupInterface(PlantMenu,no_grab);\
\
/*\
Cai refresh routine with a XtAppAddTimeOut inside \
*/\
\
OlSetDatabasePunti(listaCaiVr,npagPulldown,database_simulatore);\
teleperm_refreshCai(PlantMenu);\
\
\
\
\
\
}
*plantButton.leftAttachment: "attach_form"

*separatorGadget1.class: separatorGadget
*separatorGadget1.static: true
*separatorGadget1.name: separatorGadget1
*separatorGadget1.parent: screenHeaderForm
*separatorGadget1.x: 0
*separatorGadget1.y: 30
*separatorGadget1.width: 1260
*separatorGadget1.height: 10
*separatorGadget1.bottomAttachment: "attach_form"
*separatorGadget1.bottomOffset: 0
*separatorGadget1.leftAttachment: "attach_form"
*separatorGadget1.leftOffset: 0
*separatorGadget1.rightAttachment: "attach_form"
*separatorGadget1.rightOffset: 0
*separatorGadget1.topAttachment: "attach_form"
*separatorGadget1.topOffset: 29

*proceso1.class: pushButton
*proceso1.static: true
*proceso1.name: proceso1
*proceso1.parent: screenHeaderForm
*proceso1.labelString.source: public
*proceso1.labelString: "IC-ASD"
*proceso1.x: 890
*proceso1.y: 0
*proceso1.background.source: public
*proceso1.background: "SpringGreen3"
*proceso1.bottomAttachment: "attach_form"
*proceso1.leftAttachment: "attach_form"
*proceso1.leftOffset: 750
*proceso1.topAttachment: "attach_form"
*proceso1.topOffset: 2
*proceso1.bottomOffset: 2

*drawingArea.class: drawingArea
*drawingArea.static: true
*drawingArea.name: drawingArea
*drawingArea.parent: formTop
*drawingArea.resizePolicy: "resize_none"
*drawingArea.x: 240
*drawingArea.y: 100
*drawingArea.width: 1040
*drawingArea.height: 877
*drawingArea.bottomAttachment: "attach_form"
*drawingArea.leftAttachment: "attach_form"
*drawingArea.rightAttachment: "attach_form"
*drawingArea.topAttachment: "attach_form"
*drawingArea.topOffset: 60
*drawingArea.bottomOffset: 35
*drawingArea.background: "black"
*drawingArea.exposeCallback: {\
#ifndef DESIGN_TIME\
/*\
disegna_bck(UxWidget,bkg_sin,UxCallbackArg,&(region_sin),False);\
*/\
disegna_bck(UxWidget,Pag->sfondo,UxCallbackArg,&(region_sin),False);\
\
#endif\
}
*drawingArea.traversalOn: "false"
*drawingArea.navigationType: "none"
*drawingArea.marginHeight: 0
*drawingArea.marginWidth: 0

*titleAreaform.class: form
*titleAreaform.static: true
*titleAreaform.name: titleAreaform
*titleAreaform.parent: formTop
*titleAreaform.resizePolicy: "resize_none"
*titleAreaform.x: 0
*titleAreaform.y: 40
*titleAreaform.width: 1250
*titleAreaform.height: 30
*titleAreaform.background.source: public
*titleAreaform.background: "#a0a050"
*titleAreaform.topAttachment: "attach_form"
*titleAreaform.topOffset: 30
*titleAreaform.leftAttachment: "attach_form"
*titleAreaform.leftOffset: 0
*titleAreaform.rightAttachment: "attach_form"

*titleLabel.class: label
*titleLabel.static: true
*titleLabel.name: titleLabel
*titleLabel.parent: titleAreaform
*titleLabel.x: 580
*titleLabel.y: 0
*titleLabel.width: 450
*titleLabel.height: 30
*titleLabel.bottomAttachment: "attach_form"
*titleLabel.topAttachment: "attach_form"
*titleLabel.topOffset: 00
*titleLabel.leftAttachment: "attach_form"
*titleLabel.leftOffset: 510
*titleLabel.rightAttachment: "attach_form"
*titleLabel.rightOffset: 250
*titleLabel.labelString.source: public
*titleLabel.labelString: "display title"
*titleLabel.fontList.source: public
*titleLabel.fontList: "helvetica18"
*titleLabel.background.source: public
*titleLabel.background: "#a0a050"

*vertHierButton.class: pushButton
*vertHierButton.static: true
*vertHierButton.name: vertHierButton
*vertHierButton.parent: titleAreaform
*vertHierButton.isCompound: "true"
*vertHierButton.compoundIcon: "push.xpm"
*vertHierButton.compoundName: "push_Button"
*vertHierButton.x: 230
*vertHierButton.y: 0
*vertHierButton.width: 170
*vertHierButton.height: 27
*vertHierButton.labelString: "Vert. Hierarchy"
*vertHierButton.activateCallback: {\
int i;\
char *nomePushButton;\
int *lista_ind,npag;\
char *gerarchiaValore;\
char nomeCai[100];\
char *nomeLabel;\
char *gerarchiaNome;\
Position xShell,yShell,xButton;\
Dimension heightButton;\
\
\
/*\
Risettaggio database risorse\
*/\
gerarchiaNome=NULL;\
gerarchiaValore=NULL;\
XrmSetDatabase(XtDisplay(UxWidget),PagDb); \
\
/*\
Se esiste qualche altro pullDownMenu eliminalo\
*/\
\
if (pullDownActive)\
	{				/* Verifico se e' questo stesso Menu */\
	if(pullMenuOn==VERTMENUON)   /* Second click -> close VertMenu */\
		{\
		if(scada_on)\
			XtRemoveTimeOut(timer_timerefreshCai);\
		UxDestroyInterface(*pullDownActive);\
		XtFree(listaCaiVr);\
		XtFree(listaCaiFormVr);\
		XtFree(listaPushButton);\
		pullDownActive=NULL;\
	        pullMenuOn=0;\
		return;\
		}\
	else\
		{\
				/* elimino altro pullDownMenu */\
		if(scada_on)\
			XtRemoveTimeOut(timer_timerefreshCai);\
		UxDestroyInterface(*pullDownActive); /* other pullDownMenu Type */\
		XtFree(listaCaiVr);\
		XtFree(listaCaiFormVr);\
		XtFree(listaPushButton);\
		pullDownActive=NULL;\
		}\
	\
	}\
/*\
Acquisisco gerarchia Verticale \
*/\
teleperm_vertHier(teleperm,&UxEnv,&lista_ind,&npag);\
\
if(!npag)\
	return;     /* no pages under Vertical hierarchy */\
if( (listaPushButtonVr = (Widget *) XtCalloc(1, npag * sizeof(Widget)) ) == NULL)\
{\
   printf("vertHierMenu. Error in malloc: listaPushButton\n");\
   return;\
}\
/*\
Assegno al puntatore dell' interfaccia listaPushButton listaPushButtonVr\
cosi' da poterlo poi eliminare da qualunque interfaccia\
*/\
listaPushButton=listaPushButtonVr;\
if( (listaCaiVr = (Widget *) XtCalloc(1, npag *MAXNUMCAIXLINE*sizeof(Widget)) ) == NULL)\
{\
   printf("vertHierMenu. Error in malloc: listaCai\n");\
   return;\
}\
if ( (listaCaiFormVr = (Widget *) XtCalloc(1, npag * sizeof(Widget)) ) == NULL)\
{\
   printf("vertHierMenu. Error in malloc: listaCaiForm\n");\
   return;\
}\
get_something(	teleperm,XmNx,&xShell);		\
get_something(	teleperm,XmNy,&yShell);		\
get_something(	vertHierButton,XmNx,&xButton);\
\
\
VertMenu = XtVaCreatePopupShell("VertMenu",\
			topLevelShellWidgetClass,\
			vertHierButton,\
			XmNallowShellResize, True,\
                        XmNx, (xShell+xButton),\
                        XmNy, (yShell+60),\
			XmNmwmDecorations, 0 ,\
			NULL );\
UxPutContext( VertMenu, (char *) UxTelepermContext );\
\
/*\
Point to pullDownMenu\
*/\
pullDownActive=&VertMenu;\
pullMenuOn=VERTMENUON; /* menu attivo Vertmenu */\
\
\
VertPane=XtVaCreateManagedWidget( "formCaiPull",\
                        xmFormWidgetClass,\
                        VertMenu,\
                        NULL );\
\
UxPutContext( VertPane, (char *) UxTelepermContext );\
\
RowPull=XtVaCreateManagedWidget( "rowColumnPull",\
				xmRowColumnWidgetClass,\
				VertPane,\
				XmNpacking,XmPACK_COLUMN,\
				XmNorientation,XmHORIZONTAL,\
				XmNnumColumns, npag,\
				XmNtopAttachment,XmATTACH_FORM,\
				XmNleftAttachment,XmATTACH_FORM,\
				NULL);\
UxPutContext( RowPull, (char *) UxTelepermContext );\
\
for(i=0; i < npag; i++)\
{\
    		/*      Ricavo nome del Bottone 	*/\
   if( (nomePushButton = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].descrizione) +20) )) == NULL)\
   {\
      printf("vertMenu Error in malloc: nomePushButton\n");\
      return;\
   }\
   strcpy(nomePushButton, pagine[ lista_ind[i] ].descrizione);\
 \
  if( (nomeLabel = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].descrizione) +20) )) == NULL)\
   {\
      printf("vertMenu Error in malloc: nomeLabel\n");\
      return;\
   }\
/*\
Alloco gerarchiaNome per gerarchia con ',' e gerarchiaValore per gerarchia con '['\
*/\
\
  if( (gerarchiaNome = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].gerarchia) +20) )) == NULL)\
   {\
      printf("vertMenu Error in malloc: nomeLabel\n");\
      return;\
   }\
\
 if( (gerarchiaValore = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].gerarchia) +20) )) == NULL)\
   {\
      printf("vertMenu Error in malloc: nomeLabel\n");\
      return;\
   }\
strcpy(gerarchiaNome,pagine[lista_ind[i]].gerarchia);\
\
hierarchy_format_new(gerarchiaValore,gerarchiaNome);\
\
/*\
printf("gerarchiaNome=%s\n",gerarchiaNome);\
printf("gerarchiaValore=%s\n",gerarchiaValore);\
*/\
\
 strcpy(nomeLabel,"CAI of ");\
 strcat(nomeLabel,pagine[lista_ind[i]].descrizione);\
\
   /* push button */\
if(i==0)\
  listaPushButtonVr[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmPushButtonWidgetClass,\
                        RowPull,\
/*\
			XmNtopAttachment,XmATTACH_FORM,\
			XmNleftAttachment,XmATTACH_FORM,\
*/\
                        RES_CONVERT( XmNlabelString, nomePushButton ),\
                        NULL );\
else\
  listaPushButtonVr[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmPushButtonWidgetClass,\
                        RowPull,\
/*\
			XmNtopAttachment,XmATTACH_WIDGET,\
			XmNleftAttachment,XmATTACH_FORM,\
			XmNtopWidget,listaPushButtonVr[i-1],\
*/\
                        RES_CONVERT( XmNlabelString, nomePushButton ),\
                        NULL );	\
\
   UxPutContext( listaPushButtonVr[i], (char *) UxTelepermContext );\
\
   XtAddCallback(listaPushButtonVr[i], XmNactivateCallback,\
                    (XtCallbackProc)view_fa,lista_ind[i] ); \
\
/*\
Costruisco Nome form dei Cai\
*/\
strcat(nomePushButton,"FORM");\
  \
listaCaiFormVr[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmFormWidgetClass,\
                        RowPull,\
                        XmNwidth, 200,\
                       	RES_CONVERT( XmNbackground, "#000000" ),\
			NULL );\
\
 UxPutContext( listaCaiFormVr[i], (char *) UxTelepermContext );\
\
/* Costruisci lista di cai solo se mmi agganciato con scada */\
if(scada_on)\
      build_cai(listaCaiVr,nomeLabel,listaCaiFormVr[i],listaCaiFormVr[i],gerarchiaValore,i);\
  \
   XtFree(nomePushButton);\
   XtFree(nomeLabel);\
\
if(gerarchiaNome)\
   XtFree(gerarchiaNome);\
if(gerarchiaValore)\
   XtFree(gerarchiaValore);\
}/* end for */\
/* Innesco refresh dei cai solo se esistono */\
if(scada_on)\
      {\
      npagPulldown=npag*MAXNUMCAIXLINE;\
\
	OlSetDatabasePunti(listaCaiVr,npagPulldown,database_simulatore);\
\
	/*\
	Cai refresh routine with a XtAppAddTimeOut inside \
	*/\
\
	teleperm_refreshCai(VertMenu);\
	}  \
UxPopupInterface(VertMenu,no_grab);\
\
XtFree(lista_ind);\
\
\
}
*vertHierButton.highlightColor: "yellow"

*orizHierButton.class: pushButton
*orizHierButton.static: true
*orizHierButton.name: orizHierButton
*orizHierButton.parent: titleAreaform
*orizHierButton.x: 20
*orizHierButton.y: 0
*orizHierButton.width: 170
*orizHierButton.height: 27
*orizHierButton.labelString: "Horiz. Hierarchy"
*orizHierButton.activateCallback: {\
int i;\
char *nomePushButton;\
int *lista_ind,npag;\
char *gerarchiaValore;\
char *nomeLabel;\
char *gerarchiaNome;\
Position xShell,yShell,xButton;\
Dimension heightButton;\
\
npag=0;\
gerarchiaNome=NULL;\
gerarchiaValore=NULL;\
/*\
Se esiste qualche altro pullDownMenu eliminalo\
*/\
if (pullDownActive)\
	{				/* Verifico se e' questo stesso Menu */\
	if(pullMenuOn==ORIZMENUON)   /* Second click -> close VertMenu */\
		{\
		if(scada_on)\
			XtRemoveTimeOut(timer_timerefreshCai);\
		UxDestroyInterface(*pullDownActive);\
		XtFree(listaCaiVr);\
		XtFree(listaCaiFormVr);\
		XtFree(listaPushButton);\
		pullDownActive=NULL;\
		return;\
		}\
	else\
		{\
				/* elimino altro pullDownMenu */\
		if(scada_on)\
			XtRemoveTimeOut(timer_timerefreshCai);\
		UxDestroyInterface(*pullDownActive); /* other pullDownMenu Type */\
		XtFree(listaCaiVr);\
		XtFree(listaCaiFormVr);\
		XtFree(listaPushButton);\
		pullDownActive=NULL;\
		}\
	\
	}\
/*\
Acquisisco gerarchia Verticale \
*/\
teleperm_orizHier(teleperm,&UxEnv,&lista_ind,&npag);\
\
if(!npag)\
	{\
	return;\
	}     /* no pages under Horizontal hierarchy */\
if( (listaPushButtonOr = (Widget *) XtCalloc(1, npag * sizeof(Widget)) ) == NULL)\
{\
   printf("orizHierMenu. Error in malloc: listaPushButton\n");\
   return;\
}\
/*\
Assegno al puntatore dell' interfaccia listaPushButton listaPushButtonVr\
cosi' da poterlo poi eliminare da qualunque interfaccia\
*/\
listaPushButton=listaPushButtonOr;\
if( (listaCaiVr = (Widget *) XtCalloc(1, npag *MAXNUMCAIXLINE*sizeof(Widget)) ) == NULL)\
{\
   printf("orizHierMenu. Error in malloc: listaCaiVr\n");\
   return;\
}\
\
if( (listaCaiFormVr = (Widget *) XtCalloc(1, npag *MAXNUMCAIXLINE*sizeof(Widget)) ) == NULL)\
{\
   printf("orizHierMenu. Error in malloc: listaCaiFormVr\n");\
   return;\
}\
\
get_something(	teleperm,XmNx,&xShell);		\
get_something(	teleperm,XmNy,&yShell);		\
get_something(	orizHierButton,XmNx,&xButton);\
\
printf("OrizMenu is about to be created\n");\
OrizMenu = XtVaCreatePopupShell("VertMenu",\
			topLevelShellWidgetClass,\
			orizHierButton,\
			XmNallowShellResize, True,\
                        XmNx, (xShell+xButton),\
                        XmNy, (yShell+60),\
			XmNmwmDecorations, 0 ,\
			NULL );\
UxPutContext( OrizMenu, (char *) UxTelepermContext );\
/*\
Point to pullDownMenu\
*/\
pullDownActive=&OrizMenu;\
pullMenuOn=ORIZMENUON;    /* Menu attivo  orizzontale */\
printf("npag=%d\n",npag);\
\
OrizPane=XtVaCreateManagedWidget( "rowColumn1",\
                        xmFormWidgetClass,\
                        OrizMenu,\
                       	NULL );\
\
UxPutContext( OrizPane, (char *) UxTelepermContext );\
\
RowPull=XtVaCreateManagedWidget( "rowColumnPull",\
				xmRowColumnWidgetClass,\
				OrizPane,\
				XmNpacking,XmPACK_COLUMN,\
				XmNorientation,XmHORIZONTAL,\
				XmNnumColumns, npag,\
				XmNtopAttachment,XmATTACH_FORM,\
				XmNleftAttachment,XmATTACH_FORM,\
				NULL);\
UxPutContext( RowPull, (char *) UxTelepermContext );\
\
for(i=0; i < npag; i++)\
{\
    		/*      Ricavo nome del Bottone 	*/\
   if( (nomePushButton = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].descrizione) +20) )) == NULL)\
   {\
      printf("vertMenu Error in malloc: nomePushButton\n");\
      return;\
   }\
   strcpy(nomePushButton, pagine[ lista_ind[i] ].descrizione);\
 \
  if( (nomeLabel = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].descrizione) +20) )) == NULL)\
   {\
      printf("vertMenu Error in malloc: nomeLabel\n");\
      return;\
   }\
\
\
  if( (gerarchiaNome = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].gerarchia) +20) )) == NULL)\
   {\
      printf("vertMenu Error in malloc: nomeLabel\n");\
      return;\
   }\
\
  if( (gerarchiaValore = XtCalloc(1, sizeof(char)* (strlen(pagine[lista_ind[i]].gerarchia) +20) )) == NULL)\
   {\
      printf("vertMenu Error in malloc: nomeLabel\n");\
      return;\
   }\
\
strcpy(gerarchiaNome,pagine[lista_ind[i]].gerarchia);\
hierarchy_format_new(gerarchiaValore,gerarchiaNome);\
\
\
 strcpy(nomeLabel,"CAI of ");\
 strcat(nomeLabel,pagine[lista_ind[i]].descrizione);\
\
   /* push button */\
if(i==0)\
  listaPushButtonOr[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmPushButtonWidgetClass,\
                        RowPull,\
/*\
			XmNtopAttachment,XmATTACH_FORM,\
			XmNleftAttachment,XmATTACH_FORM,\
*/\
                        RES_CONVERT( XmNlabelString, nomePushButton ),\
                        NULL );\
else\
  listaPushButtonOr[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmPushButtonWidgetClass,\
                        RowPull,\
/*\
			XmNtopAttachment,XmATTACH_WIDGET,\
			XmNleftAttachment,XmATTACH_FORM,\
*/\
			XmNtopWidget,listaPushButtonOr[i-1],\
                        RES_CONVERT( XmNlabelString, nomePushButton ),\
                        NULL );	\
\
   UxPutContext( listaPushButtonOr[i], (char *) UxTelepermContext );\
\
   XtAddCallback(listaPushButtonOr[i], XmNactivateCallback,\
                    (XtCallbackProc)view_fa,lista_ind[i] ); \
/*\
Costruisco Nome form dei Cai\
*/\
strcat(nomePushButton,"FORM");\
  \
listaCaiFormVr[i] = XtVaCreateManagedWidget( nomePushButton,\
                        xmFormWidgetClass,\
                        RowPull,\
                        XmNwidth, 200,\
                       	RES_CONVERT( XmNbackground, "#000000" ),\
			NULL );\
\
UxPutContext( listaCaiFormVr[i], (char *) UxTelepermContext );\
/* Costruisci lista di cai solo se mmi agganciato con scada */\
if(scada_on)\
      build_cai(listaCaiVr,nomeLabel,listaCaiFormVr[i],listaCaiFormVr[i],gerarchiaValore,i);\
\
   XtFree(nomePushButton);\
\
   XtFree(nomeLabel);\
\
   if(gerarchiaNome)\
      XtFree(gerarchiaNome);\
   if(gerarchiaValore)\
      XtFree(gerarchiaValore);\
}/* end for */\
\
/* Innesco refresh dei cai solo se esistono */\
if(scada_on)\
      {\
      npagPulldown=npag*MAXNUMCAIXLINE;\
      \
      /*\
      Cai refresh routine with a XtAppAddTimeOut inside \
      */\
      OlSetDatabasePunti(listaCaiVr,npagPulldown,database_simulatore);\
\
      teleperm_refreshCai(OrizMenu);\
      }\
\
UxPopupInterface(OrizMenu,no_grab);\
XtFree(lista_ind);\
\
}

