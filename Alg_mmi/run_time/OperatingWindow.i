! UIMX ascii 2.5 key: 741                                                       

*OperatingWindow.class: topLevelShell
*OperatingWindow.gbldecl: #include <stdio.h>\
#include <stdlib.h>\
#include <Xm/Protocols.h>\
#include <time.h>\
#include <Xm/MwmUtil.h>\
#include <Cs/Cs.h>\
#include <Xm/RowColumn.h>\
\
#ifndef DESIGN_TIME\
#include <Xl/XlP.h>\
#endif\
\
\
#include <Ol/OlPert.h>\
\
\
\
#include <Xl/XlIndicTelep.h>\
#include <Xl/XlPictograph.h>\
#include <Xl/XlOperableKeys.h>\
#include <Xl/XlChangePage.h>\
\
#include "other.h"\
\
#include <Ol/OlTree.h>	         /* per gestione OlTree teleperm */\
#include <Ol/OlDatabasePunti.h>  /* per gestione DatabasePunti */\
#include <Cs/Cs.h>\
#include <Xl/XlCaiAll.h>\
/* offset aggiunti alla x,y dello widget\
   che crea la OW\
*/\
#define OWXOFFSET 30      \
#define OWYOFFSET 100     \
\
/* altezza di default window extension2\
   utilizzata se non specificata da risorsa\
   height_ext2\
*/\
#define DEFAULT_HEXT2 100\
\
#define TIMEOUTMINIASD  40  /* secondi per timeOut */\
extern OlDatabasePuntiObject database_simulatore;\
\
#define HEIGHTASDSTEP	32 /* altezza di ogni cella rowColumn allarmi miniASD */ \
#define HEIGHTASDLABEL	29 /* altezza di ogni label allarmi miniASD */\
#define ALLARMI          0\
#define MANUAL           1 \
/* */\
extern Boolean EsistePagina();\
static void OperatingWindow_refreshPag();\
static void no_closeMWM();\
static Widget CreoOggettiOW();\
static Boolean CreaPaginaOW();\
\
extern AN_PAG *pagine;\
extern PAGINE_APERTE *el_pagine;\
extern int num_el_pagine;
*OperatingWindow.ispecdecl: Position owX,owY,owH;\
int ext1Aperta;\
int ext2Aperta;\
\
/* variabili per gestione oggetti interni a OW\
   ( come per i sinottici)\
*/\
\
XrmDatabase     OwDb;   /* db risorse OW pag */\
\
XtIntervalId OWtimer_refresh;  /* tempo di refresh */\
int OWkey_refresh;             /* indice del timeout di refresh */\
\
WidgetList OWlista_wid;        /* lista degli widget */\
int OWnum_wid;                 /* numero widget */\
int OWtime_ref;                /* tempo di refresh della pagina */\
\
int OWtop_x,OWtop_y,OWtop_width,OWtop_height,OWtop_tipo;\
char *OWtop_descrizione;\
/* variabili per risorse della drawing area\
*/\
int drawing_width,drawing_height;\
Pixel *drawing_background;\
\
/* stato del IMP button\
*/\
int imp_premuto;\
\
/* ultimo XlOperableKeys tipo OPKEY_EXEC premuto\
*/\
Widget lastWexec;\
\
/* bkg della pagina\
*/\
BCK_OBJ *bkg_ow;\
Region region_ow;\
\
/* altezza window extension2\
*/\
int HEXT2;\
/*\
 pixmap per eventuale stipple\
*/\
Pixmap drawing_pixmap;\
\
/* lista finestre 'Detail' figlie della OW\
*/\
int numDetail;\
Widget *Detail;\
\
/*gerarchia in formato per mini ASD */\
\
Boolean flag_aperture;\
\
char *allarm_data; \
char *manual_data;\
short indice;\
unsigned char *gerarchie; /* gerarchia della O.W. in formato SCADA */\
\
/************************************\
Oggetti per miniASD nella Extension1\
*************************************/\
Widget formAllarm,formManual; /* form che contengono i rowColumn */\
\
Widget rowColumnAllarmCai,rowColumnManualCai,rowColumnAllarm,rowColumnManual;\
\
Widget *all_caiAll_form,*all_caiMan_form,*all_caiAll,*all_caiMan,*all_label,*man_label;\
\
int num_allarm,num_manual;   /* numero allarmi e di manuali in miniASD */\
char *path_icone;         /* contiene il path relativo dove sono i .bmp ($LEGOCAD_ICO )*/\
char icon[FILENAME_MAX];  /* contiene il path completo di filename del .bmp */\

*OperatingWindow.ispeclist: owX, owY, owH, ext1Aperta, ext2Aperta, OwDb, OWtimer_refresh, OWkey_refresh, OWlista_wid, OWnum_wid, OWtime_ref, OWtop_x, OWtop_y, OWtop_width, OWtop_height, OWtop_tipo, OWtop_descrizione, drawing_width, drawing_height, drawing_background, imp_premuto, lastWexec, bkg_ow, region_ow, HEXT2, drawing_pixmap, numDetail, Detail, flag_aperture, allarm_data, manual_data, indice, gerarchie, formAllarm, formManual, rowColumnAllarmCai, rowColumnManualCai, rowColumnAllarm, rowColumnManual, all_caiAll_form, all_caiMan_form, all_caiAll, all_caiMan, all_label, man_label, num_allarm, num_manual, path_icone, icon
*OperatingWindow.ispeclist.owX: "Position", "%owX%"
*OperatingWindow.ispeclist.owY: "Position", "%owY%"
*OperatingWindow.ispeclist.owH: "Position", "%owH%"
*OperatingWindow.ispeclist.ext1Aperta: "int", "%ext1Aperta%"
*OperatingWindow.ispeclist.ext2Aperta: "int", "%ext2Aperta%"
*OperatingWindow.ispeclist.OwDb: "XrmDatabase", "%OwDb%"
*OperatingWindow.ispeclist.OWtimer_refresh: "XtIntervalId", "%OWtimer_refresh%"
*OperatingWindow.ispeclist.OWkey_refresh: "int", "%OWkey_refresh%"
*OperatingWindow.ispeclist.OWlista_wid: "WidgetList", "%OWlista_wid%"
*OperatingWindow.ispeclist.OWnum_wid: "int", "%OWnum_wid%"
*OperatingWindow.ispeclist.OWtime_ref: "int", "%OWtime_ref%"
*OperatingWindow.ispeclist.OWtop_x: "int", "%OWtop_x%"
*OperatingWindow.ispeclist.OWtop_y: "int", "%OWtop_y%"
*OperatingWindow.ispeclist.OWtop_width: "int", "%OWtop_width%"
*OperatingWindow.ispeclist.OWtop_height: "int", "%OWtop_height%"
*OperatingWindow.ispeclist.OWtop_tipo: "int", "%OWtop_tipo%"
*OperatingWindow.ispeclist.OWtop_descrizione: "unsigned char", "*%OWtop_descrizione%"
*OperatingWindow.ispeclist.drawing_width: "int", "%drawing_width%"
*OperatingWindow.ispeclist.drawing_height: "int", "%drawing_height%"
*OperatingWindow.ispeclist.drawing_background: "Pixel", "*%drawing_background%"
*OperatingWindow.ispeclist.imp_premuto: "int", "%imp_premuto%"
*OperatingWindow.ispeclist.lastWexec: "Widget", "%lastWexec%"
*OperatingWindow.ispeclist.bkg_ow: "BCK_OBJ", "*%bkg_ow%"
*OperatingWindow.ispeclist.region_ow: "Region", "%region_ow%"
*OperatingWindow.ispeclist.HEXT2: "int", "%HEXT2%"
*OperatingWindow.ispeclist.drawing_pixmap: "Pixmap", "%drawing_pixmap%"
*OperatingWindow.ispeclist.numDetail: "int", "%numDetail%"
*OperatingWindow.ispeclist.Detail: "Widget", "*%Detail%"
*OperatingWindow.ispeclist.flag_aperture: "Boolean", "%flag_aperture%"
*OperatingWindow.ispeclist.allarm_data: "unsigned char", "*%allarm_data%"
*OperatingWindow.ispeclist.manual_data: "unsigned char", "*%manual_data%"
*OperatingWindow.ispeclist.indice: "short", "%indice%"
*OperatingWindow.ispeclist.gerarchie: "unsigned char", "*%gerarchie%"
*OperatingWindow.ispeclist.formAllarm: "Widget", "%formAllarm%"
*OperatingWindow.ispeclist.formManual: "Widget", "%formManual%"
*OperatingWindow.ispeclist.rowColumnAllarmCai: "Widget", "%rowColumnAllarmCai%"
*OperatingWindow.ispeclist.rowColumnManualCai: "Widget", "%rowColumnManualCai%"
*OperatingWindow.ispeclist.rowColumnAllarm: "Widget", "%rowColumnAllarm%"
*OperatingWindow.ispeclist.rowColumnManual: "Widget", "%rowColumnManual%"
*OperatingWindow.ispeclist.all_caiAll_form: "Widget", "*%all_caiAll_form%"
*OperatingWindow.ispeclist.all_caiMan_form: "Widget", "*%all_caiMan_form%"
*OperatingWindow.ispeclist.all_caiAll: "Widget", "*%all_caiAll%"
*OperatingWindow.ispeclist.all_caiMan: "Widget", "*%all_caiMan%"
*OperatingWindow.ispeclist.all_label: "Widget", "*%all_label%"
*OperatingWindow.ispeclist.man_label: "Widget", "*%man_label%"
*OperatingWindow.ispeclist.num_allarm: "int", "%num_allarm%"
*OperatingWindow.ispeclist.num_manual: "int", "%num_manual%"
*OperatingWindow.ispeclist.path_icone: "unsigned char", "*%path_icone%"
*OperatingWindow.ispeclist.icon: "unsigned char", "%icon%[255]"
*OperatingWindow.funcdecl: swidget create_OperatingWindow(UxParent,opw,OWpag,ParentDb)\
swidget UxParent; /* drawing area parente */\
Widget opw;       /* widget pictograph o indic chiamante */    \
AN_PAG *OWpag;    /* puntatore alla pagina tipo OW da aprire */\
XrmDatabase ParentDb;   /* db delle risorse del parent */
*OperatingWindow.funcname: create_OperatingWindow
*OperatingWindow.funcdef: "swidget", "<create_OperatingWindow>(%)"
*OperatingWindow.argdecl: swidget UxParent;\
Widget opw;\
AN_PAG *OWpag;\
XrmDatabase ParentDb;
*OperatingWindow.arglist: UxParent, opw, OWpag, ParentDb
*OperatingWindow.arglist.UxParent: "swidget", "%UxParent%"
*OperatingWindow.arglist.opw: "Widget", "%opw%"
*OperatingWindow.arglist.OWpag: "AN_PAG", "*%OWpag%"
*OperatingWindow.arglist.ParentDb: "XrmDatabase", "%ParentDb%"
*OperatingWindow.icode: char nome_pag[255];\
Atom WM_DELETE_WINDOW; /* per close con MWM*/\
\
/* per gestione backgroundsinottico\
*/\
int dim[4];\
int num_b;\
extern Boolean leggi_file_bck();\
\
Pixmap pix;\
char *tipo;            /* usati nella put resource per set del background della OW */\
XrmValue value;\
XrmValue valueImp;\
int retval;\
\
/* inizializzo lista Detail window figlie della OW\
*/\
numDetail=0;\
Detail=NULL;\
\
drawing_pixmap=0;\
\
ext1Aperta =0;\
\
/* inizializzo lo stato del IMP button\
*/\
imp_premuto = 0;\
\
if( !EsistePagina(OWpag->nome) )\
{\
    printf("Error. File Page %s not exist.\n",OWpag->nome);\
    return( NULL );\
}\
\
                \
/* file delle risorse della pagina da caricare\
*/\
sprintf(nome_pag,"%s/%s.rtf",XlGetenv("LEGOMMI_PAGINE"),OWpag->nome);\
\
                \
/* carico il db della pagina\
*/\
if( (OwDb = XrmGetFileDatabase(nome_pag)) == NULL)\
{\
   printf("Error. Cannot open page %s\n",nome_pag);\
   return(NULL);\
}\
\
/* recupero il background della drawing area della pagina\
   che uso poi nella PutResource per forzare il bkg\
   di tutti gli oggetti figli \
*/\
XrmGetResource(OwDb,"drawing_background",(char*)NULL,&tipo,&value);\
\
/* merge db della pagina e della applicazione (quello salvato su file)\
*/\
XrmCombineFileDatabase( "ApplDb.res", &OwDb ,True);\
\
/* setto il bkg di tutti gli oggetti figli della OW\
   al colore della drawing area della pagina\
   La Ow risulta cosi di un colore tutta uniforme\
*/\
XrmPutResource(&OwDb,"*OperatingWindow.mainForm.footerForm*background",tipo,&value);\
XrmPutResource(&OwDb,"*OperatingWindow.mainForm.headerForm*background",tipo,&value);\
/*\
Modifica by Fabio\
*/\
XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.*XmLabel.background",tipo,&value);\
XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.*XmForm.background",tipo,&value);\
XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.formAllarm.*XmRowColumn.background",tipo,&value);\
XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.background",tipo,&value);\
XrmPutResource(&OwDb,"*OperatincWindow.mainForm.extension1.*XmScrolledWindow.background",tipo,&value);\
/*XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.*XmPushButton.background",tipo,&value);*/\
XrmPutResource(&OwDb,"*OperatingWindow.mainForm.extension1.*XmScrollBar.background",tipo,&value);\
\
/* \
setto il display su PagDb\
*/\
XrmSetDatabase(XtDisplay((Widget)UxParent),OwDb);\
\
/* mi serve solo per caricare il time_ref\
*/\
if(!GetResTopLevel(opw,&OWtop_x,&OWtop_y,&OWtop_width,&OWtop_height,&OWtime_ref,\
		&OWtop_tipo,&OWtop_descrizione))\
	return(False);\
\
/* recupero le risorse della drawing area\
*/\
if(!GetResDrawing(opw,&drawing_width,&drawing_height,&drawing_background,&drawing_pixmap))\
		return(False);\
\
/* recupero la dimensione della extension2 dalla risorsa\
   height_ext2   e la imposto alla variabile HEXT2\
   che viene utilizzata per calcolare le dimensioni della\
   extension2 e quindi della drawing area della OW\
*/\
retval = XrmGetResource(OwDb,"height_ext2",(char*)NULL,&tipo,&value);\
\
if( retval && (value.size > 1))\
   HEXT2 = atoi(value.addr);\
else\
   HEXT2 = DEFAULT_HEXT2;\
\
flag_aperture=0;\
/*\
Setto a zero No allarmi per OperatingWindow\
*/\
num_manual=0;\
num_allarm=0;
*OperatingWindow.fcode: {\
long  decor;\
Widget child;  /* a perdere */\
Position x,y;\
\
/* set frame sul pictograph/indic\
*/\
XtVaSetValues(opw,XlNowOpen,True,NULL);\
\
\
/* richiedo la x e la y del parent\
   per poter riposizionare la ow vicino al parent\
   (se il parent diretto non e' la drawing area\
    richiedo il parent)\
*/\
\
if( XlIsXlComposite(XtParent(opw)) )\
   XtVaGetValues(XtParent(opw),XmNx,&owX,XmNy,&owY,XmNheight,&owH,NULL);\
else\
   XtVaGetValues(opw,XmNx,&owX,XmNy,&owY,XmNheight,&owH,NULL);\
\
x = owX;\
y = owY;\
\
/* sposto le coordinate di visualizzazione della OW\
   rispetto a quelle dello widget chiamante in base ad un offset prefissato\
   attualmente fissato come define (potrebbe diventare una risorsa della applicazione)\
*/\
x += OWXOFFSET;\
y += OWYOFFSET;\
\
\
/* set della posizione della operating Window \
   ( rispetto al parent widget )\
   e della sua dimensione esterna \
*/\
XtVaSetValues(OperatingWindow,XmNx,x,XmNy,y,\
              XmNwidth,OWtop_width,XmNheight,OWtop_height,NULL);\
\
\
/* setto la posizione  dimensioni della drawing area\
   e della OW in base alle risorse \
*/\
XtVaSetValues(drawingAreaOW,\
              XmNwidth,drawing_width,XmNheight,drawing_height,NULL);\
\
/* decorazioni mwm per OW\
*/\
\
OperatingWindow_decorationToggle(OperatingWindow,&UxEnv);\
\
}\
\
/* set titolo blank*/\
set_something(OperatingWindow,XmNtitle," ");\
/*\
set_something(OperatingWindow,XmNtitle,OWpag->nome);\
*/\
\
/* setto il background della drawingArea\
*/\
if(drawing_pixmap)\
	set_something(drawingAreaOW,XmNbackgroundPixmap,drawing_pixmap);\
else\
	set_something(drawingAreaOW,XmNbackground,drawing_background);\
\
if(!CreaPagina(drawingAreaOW,&OWlista_wid, &OWnum_wid))\
	return(NULL);\
\
\
if((OWkey_refresh=InsElencoPagine(OWpag->nome,OWlista_wid,OWnum_wid,OWtime_ref)) == -1)\
	return(NULL);\
\
/* set del timer di refresh e della routine di refresh (teleperm_refreshPag)\
*/\
OWtimer_refresh = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (OperatingWindow),\
            (unsigned long) (OWtime_ref*100) ,OperatingWindow_refreshPag, OperatingWindow );\
\
/* disabilito la chiusura della finestra da MWM\
*/\
 WM_DELETE_WINDOW=XmInternAtom(XtDisplay(OperatingWindow),"WM_DELETE_WINDOW",False);\
XmAddWMProtocolCallback(OperatingWindow,WM_DELETE_WINDOW,no_closeMWM,NULL);\
\
\
/* faccio sparire la extension2\
   chiudendola\
*/\
ext2Aperta = 1;\
OperatingWindow_OpenExt2(rtrn,&UxEnv,drawingAreaOW);\
\
/* inizializzo come insensitive il bottone di Ejecutar\
   che viene reso sensitive solo se c'e' una perturbazione disponibile a essere\
   da lui inviata\
*/\
XtVaSetValues(Ejecutar,\
              XmNsensitive,False,\
              NULL);\
\
/*\
  inizializza la regione di ridisegno dello sfondo\
*/\
   if(OWpag->sfondo==NULL)\
	leggi_file_bck(UxParent,OWpag->nome,"bkg",&(OWpag->sfondo),dim);\
   else	 \
      AllocaColoriSfondo(UxParent,OWpag->sfondo);\
\
\
\
region_ow=NULL;\
\
/* setto le descrizione idcode e funcode\
*/\
OperatingWindow_SetDescr(OperatingWindow,&UxEnv);\
\
/* distruggo i bottoni Ejecutar e IMP\
   verificando se ci sono bottoni tipo OPKEY_IMP\
   e OPKEY_EXEC\
*/\
OperatingWindow_configBottoni(OperatingWindow,&UxEnv);/*\
Setto bottoni per miniASD\
*/\
/* setto i pixmap sui bottoni dlla pagina teleperm \
   i .bmp so trovano in $LEGOCAD_ICO \
*/\
\
path_icone=(char *)getenv("LEGOCAD_ICO");\
\
if(path_icone==NULL)\
{\
   printf("\nERROR Environment variable LEGOCAD_ICO is not defined. Exit.\n");\
   \
}\
\
sprintf(icon,"%s/ackmaMiniASD.bmp",path_icone);\
UxPutStrRes(dummy_ric_manual,XmNlabelPixmap,icon);\
sprintf(icon,"%s/nullMiniASD.bmp",path_icone);\
UxPutStrRes(dummy_ric_manual,XmNlabelInsensitivePixmap,icon);\
UxPutStrRes(dummy_ric_all,XmNlabelInsensitivePixmap,icon);\
\
sprintf(icon,"%s/ackalMiniASD.bmp",path_icone);\
UxPutStrRes(dummy_ric_all,XmNlabelPixmap,icon);\
\
\
\
return(rtrn);\

*OperatingWindow.auxdecl: /* \
routine per aprire una pagina da oggetto cambio pagina interno alla OW\
*/\
void OperatingWindow_OpenPage(drawing,nomePag,tipoOpen)\
Widget drawing;\
char *nomePag;\
int tipoOpen;\
{\
   /* salvo il context\
   */\
   _UxCOperatingWindow            *UxSaveCtx = UxOperatingWindowContext;\
\
   /* recupero il context\
   */\
   UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( drawing );\
\
   OperatingWindow_chPage(OperatingWindow,&UxEnv,drawing,nomePag,tipoOpen);\
\
   /* rispristino il context salvato\
   */ \
   UxOperatingWindowContext = UxSaveCtx;\
}\
\
\
/* interfaccia per apertura extension2\
   w = indice di widget tipo ChangePage posto\
      sulla OperatingWindow di tipo OPEN_EXT2\
*/\
void apriExt2( Widget wid )\
{   \
   /* salvo il context\
   */\
   _UxCOperatingWindow            *UxSaveCtx = UxOperatingWindowContext;\
\
   /* recupero il context\
   */\
   UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( wid );\
\
   /* chiamo la funzione di apertura della Extension2\
   */ \
   OperatingWindow_OpenExt2(OperatingWindow,&UxEnv, drawingAreaOW );\
\
   /* rispristino il context salvato\
   */ \
   UxOperatingWindowContext = UxSaveCtx;\
}\
\
/* interfaccia esterna per chiusura della OW\
*/\
Boolean OW_close( Widget OW)\
{\
   OperatingWindow_closeOW(OW,&UxEnv);\
   return(True);\
}\
\
/*******************************************************\
 * store pert\
 *\
 * CB associata agli operable Keys di tipo OPKEY_EXEC\
 *\
 * stabilisce quale perturbazione deve essere inviata \
 * dalla activate callback del tasto ejecutar\
 * \
 *******************************************************/\
void store_pert(Widget w)\
{\
   Pixel bg_butt;\
   /* salvo il context\
   */\
   _UxCOperatingWindow            *UxSaveCtx = UxOperatingWindowContext;\
\
   /* recupero il context\
   */\
   UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( XtParent(w) );\
 \
   if( w != NULL )\
   {   \
      /* memorizzo l'indice di Widget relativo all'OperableKeys \
      di tipo EXEC che e' stato premuto e rendo sensitive il\
      bottone Ejecutar\
      */\
      lastWexec = w;\
\
      XtVaGetValues( lastWexec,XlNhstateBg,&bg_butt,NULL);\
\
      XtVaSetValues(Ejecutar,\
                 XmNsensitive,True,\
                 XmNbackground,bg_butt,\
                 NULL);\
   }\
\
   /* rispristino il context salvato\
   */ \
   UxOperatingWindowContext = UxSaveCtx;\
  \
}\
\
/*******************\
 *\
 ********************/\
static void no_closeMWM(UxWidget,UxClientData,UxCallbackArg)\
Widget UxWidget;\
XtPointer UxClientData,UxCallbackArg;\
{\
   return;\
}\
\
/*************************************************\
 * refresh della pagina tipo Operating Window\
 *************************************************/\
\
static void OperatingWindow_refreshPag(wid)\
swidget wid;\
{\
   int i;\
   _UxCOperatingWindow            *UxSaveCtx = UxOperatingWindowContext;\
   float simTime;\
\
/* recupero il context \
*/\
   UxOperatingWindowContext = (_UxCOperatingWindow *) UxGetContext( wid );\
\
  if(!OlSetDataPage(database_simulatore,OWkey_refresh))\
  {\
        printf("Error in refresh\n");\
        return;\
  }\
\
  if(OlGetDataStatus(database_simulatore,OWkey_refresh))  \
        {\
        XlRefreshWidget(OWlista_wid,OWnum_wid);\
        if(num_allarm>0 && num_allarm <17)\
           XlRefreshWidget(all_caiAll,num_allarm);\
        if(num_manual>0 && num_manual <17)\
           XlRefreshWidget(all_caiMan,num_manual);\
        }\
   if(!OlUnsetDataPage(database_simulatore,OWkey_refresh))\
   {\
      printf("Error in refresh\n");\
      return;\
   }\
\
/*\
        carica il timer per il refresh\
*/\
      OWtimer_refresh = XtAppAddTimeOut (\
            XtWidgetToApplicationContext (OperatingWindow),\
            (unsigned long) (OWtime_ref*100) ,OperatingWindow_refreshPag, OperatingWindow);\
\
/* switch del context\
*/\
   UxOperatingWindowContext = UxSaveCtx;\
\
\
}\
\
\

*OperatingWindow_OpenExt1.class: method
*OperatingWindow_OpenExt1.name: OpenExt1
*OperatingWindow_OpenExt1.parent: OperatingWindow
*OperatingWindow_OpenExt1.methodType: int
*OperatingWindow_OpenExt1.methodArgs: 
*OperatingWindow_OpenExt1.methodBody: Dimension wh,ww,ext1h;\
Position x,y;\
int      off_dwa;\
\
/* apertura della Ext1 \
*/\
if( !ext1Aperta )\
{\
 \
   /* recupero le attuali dimensioni della OW e della \
      extension1\
      calcolo le nuove dimesioni della OW sommandogli \
      quelle della extension1 e le impongo      \
   */\
   XtVaGetValues(OperatingWindow,XmNwidth,&ww,XmNheight,&wh,NULL);\
   XtVaGetValues(extension1,XmNheight,&ext1h,NULL);\
\
   wh += ext1h;\
   XtVaSetValues(OperatingWindow,XmNheight,wh,NULL);      \
\
   /* riposiziono la drawing area che deve essere \
      sotto la extension1 (la ext1 non deve coprirla)\
      modifico il topOffset della drawing area\
   */\
\
   XtVaGetValues(drawingAreaOW,XmNtopOffset,&off_dwa,NULL);\
\
printf("OPENEXT1: APRIRE PRIMA off_dwa = %d\n",off_dwa);\
\
/*\
   XtVaGetValues(drawingAreaOW,XmNx,&x,XmNy,&y,NULL);\
   y += (ext1h);\
   XtMoveWidget(drawingAreaOW,x,y);\
   if( ext2Aperta )\
   {\
      y += HEXT2;\
   }\
*/\
\
   off_dwa += (ext1h);\
\
printf("OPENEXT1: APRIRE DOPO off_dwa = %d\n",off_dwa); \
\
   XtVaSetValues(drawingAreaOW,XmNtopOffset,off_dwa,NULL);\
\
   /* setto la width della extension1 come quella del parent\
   */   \
   XtVaSetValues(extension1,XmNwidth,ww,NULL);\
\
   /* mappo la extension 1 con i suoi children\
   */ \
   XtMapWidget(extension1);\
   \
   /* inverto la direzione dello\
      arrowButton per indicare\
      che attiva la chiusura della extension\
   */\
   XtVaSetValues(bOpenExt1,XmNarrowDirection,XmARROW_DOWN,NULL);\
\
   /* set variabile di controllo\
   */\
   ext1Aperta = 1;\
   \
}\
else /* chisura extension1 */\
{\
\
   /* recupero le attuali dimensioni della OW e della \
      extension1 e la posizione della drawing area\
      calcolo le nuove dimesioni della OW sottraendogli \
      quelle della extension1 e le impongo  \
      calcolo le nuove coordinate della drawing area\
      e le impongo    \
   */\
   XtVaGetValues(OperatingWindow,XmNheight,&wh,NULL);\
   XtVaGetValues(extension1,XmNheight,&ext1h,NULL);\
\
   XtVaGetValues(drawingAreaOW,XmNtopOffset,&off_dwa,NULL);\
\
printf("OPENEXT1: CHIUDERE off_dwa = %d\n",off_dwa);\
\
   wh -= ext1h;\
   XtVaSetValues(OperatingWindow,XmNheight,wh,NULL);\
\
/*\
   XtVaGetValues(drawingAreaOW,XmNx,&x,XmNy,&y,NULL);\
   y -= (ext1h);\
   XtMoveWidget(drawingAreaOW,x,y);\
*/\
\
   off_dwa -= (ext1h);\
   XtVaSetValues(drawingAreaOW,XmNtopOffset,off_dwa,NULL);\
 \
   /* smappo la extension 1 con i suoi children\
   */ \
   XtUnmapWidget(extension1);\
\
   /* inverto la direzione dello\
       arrowButton per indicare\
       che attiva la chiusura della extension\
   */\
    XtVaSetValues(bOpenExt1,XmNarrowDirection,XmARROW_UP,NULL);\
  \
    /* reset variabile controllo\
    */\
    ext1Aperta=0;\
}

*OperatingWindow_decorationToggle.class: method
*OperatingWindow_decorationToggle.name: decorationToggle
*OperatingWindow_decorationToggle.parent: OperatingWindow
*OperatingWindow_decorationToggle.methodType: int
*OperatingWindow_decorationToggle.methodArgs: 
*OperatingWindow_decorationToggle.methodBody: Arg args[2];\
int nargs;\
int decorOn;\
char *tipo;\
XrmValue value;\
char risorsa[50];\
char appo[50];\
Display *disp;\
\
disp = XtDisplay(UxThis);\
\
sprintf(risorsa,"teleperm.decorazioni");\
XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);\
strncpy(appo,value.addr,(int)value.size);\
decorOn = atoi(appo);\
\
if( decorOn == 0) \
{\
nargs=0;\
/* decorazioni con titolo e bordino*/\
XtSetArg(args[0],XmNmwmDecorations,MWM_DECOR_TITLE|MWM_DECOR_BORDER);\
nargs++;\
XtSetValues(UxThis,args,nargs);\
}\
else /* decorazioni complete */\
{\
nargs=0;\
XtSetArg(args[0],XmNmwmDecorations,MWM_DECOR_ALL);\
nargs++;\
XtSetValues(UxThis,args,nargs);\
}\


*OperatingWindow_OpenExt2.class: method
*OperatingWindow_OpenExt2.name: OpenExt2
*OperatingWindow_OpenExt2.parent: OperatingWindow
*OperatingWindow_OpenExt2.methodType: int
*OperatingWindow_OpenExt2.methodArgs: Widget drawing_area;\

*OperatingWindow_OpenExt2.methodBody: Position x,y;\
int      h,hext1;\
int      off_dwa;\
\
/* apro la extension2 \
*/\
if( !ext2Aperta )\
{\
   /* recupero la dimensione della OW e\
      le coordinate della drawing area\
      calcolo la nuova altezza della OW sommandogli la \
      HEXT2\
      muovo la drawing area  \
   */\
\
   XtVaGetValues(OperatingWindow,XmNheight,&h,NULL);\
   h += HEXT2;\
   XtVaSetValues(OperatingWindow,XmNheight,h,NULL);\
\
/*\
   XtVaGetValues(drawingAreaOW,XmNx,&x,XmNy,&y,NULL);\
   y += HEXT2;\
   if( ext1Aperta )\
   { \
      XtVaGetValues(extension1,XmNheight,&hext1,NULL);\
      printf("extension1 h=%d\n",hext1);\
      y += hext1;\
   }\
   XtMoveWidget(drawingAreaOW,x,y);\
*/\
\
   XtVaGetValues(drawingAreaOW,XmNtopOffset,&off_dwa,NULL);\
\
printf("OPENEXT2: APRIRE PRIMA off_dwa = %d\n",off_dwa);\
\
   off_dwa += HEXT2;\
\
printf("OPENEXT2: APRIRE DOPO off_dwa = %d\n",off_dwa);\
\
   XtVaSetValues(drawingAreaOW,XmNtopOffset,off_dwa,NULL);\
\
   ext2Aperta = 1; \
\
}\
else\
{\
   /* recupero la dimensione della OW e\
      le coordinate della drawing area\
      calcolo la nuova altezza della OW sottraendogli la \
      HEXT2\
      muovo la drawing area  \
   */\
\
   XtVaGetValues(OperatingWindow,XmNheight,&h,NULL);\
   h -= HEXT2;\
   XtVaSetValues(OperatingWindow,XmNheight,h,NULL);\
\
/*\
   XtVaGetValues(drawingAreaOW,XmNx,&x,XmNy,&y,NULL);\
   y -= HEXT2;\
   XtMoveWidget(drawingAreaOW,x,y);\
*/\
\
   XtVaGetValues(drawingAreaOW,XmNtopOffset,&off_dwa,NULL);\
\
printf("OPENEXT2: CHIUDERE off_dwa = %d\n",off_dwa);\
\
   off_dwa -= HEXT2;\
   XtVaSetValues(drawingAreaOW,XmNtopOffset,off_dwa,NULL);\
\
   ext2Aperta = 0;\
}\

*OperatingWindow_OpenExt2.arguments: drawing_area
*OperatingWindow_OpenExt2.drawing_area.def: "Widget", "%drawing_area%"

*OperatingWindow_abilitaOpKeys.class: method
*OperatingWindow_abilitaOpKeys.name: abilitaOpKeys
*OperatingWindow_abilitaOpKeys.parent: OperatingWindow
*OperatingWindow_abilitaOpKeys.methodType: Boolean
*OperatingWindow_abilitaOpKeys.methodArgs: int tipo_opkey;\
Boolean stato;\

*OperatingWindow_abilitaOpKeys.methodBody: /* recupero la lista dei children \
   e per quelli del tipo_opkey\
   faccio le opportune abilitazioni;\
*/\
extern Boolean XlOperableKeysAbleImp();\
extern Boolean XlIsOperableKeyImp();\
WidgetList listChildren;\
Cardinal numChildren;\
int i,numAbilitati;\
\
XtVaGetValues(drawingAreaOW,XmNchildren,&listChildren,\
                            XmNnumChildren,&numChildren,NULL);\
\
printf("numChildren = %d\n",numChildren);\
\
numAbilitati=0;\
for(i=0;i<numChildren;i++)\
{\
\
   if( XlIsOperableKeysImp( listChildren[i]) )\
   { \
\
      if( XlOperableKeysAbleImp(listChildren[i],stato) )\
\
          numAbilitati++;\
\
      else\
\
         return(False);\
\
   } \
\
}\
\
if( numAbilitati > 0 )\
   return(True);\
\
return(False);
*OperatingWindow_abilitaOpKeys.arguments: tipo_opkey, stato
*OperatingWindow_abilitaOpKeys.tipo_opkey.def: "int", "%tipo_opkey%"
*OperatingWindow_abilitaOpKeys.stato.def: "Boolean", "%stato%"

*OperatingWindow_closeOW.class: method
*OperatingWindow_closeOW.name: closeOW
*OperatingWindow_closeOW.parent: OperatingWindow
*OperatingWindow_closeOW.methodType: Boolean
*OperatingWindow_closeOW.methodArgs: 
*OperatingWindow_closeOW.methodBody: extern int aggiornaListChild();\
extern int ClosePageStazFromOW();\
int i,j;\
Widget ref=NULL;\
\
if( numDetail )\
{\
    printf("numDetail  =%d\n",numDetail );\
\
   for(i=0;i<num_el_pagine;i++)\
   {\
\
      if( el_pagine[i].w )\
         ref = XtParent(XtParent(XtParent(XtParent(el_pagine[i].w))));\
      else\
        continue;\
\
printf("ref = %d\n",ref);\
\
      for(j=0;j<numDetail;j++)\
         if( ref == Detail[j] )\
         {  \
              printf("Deve essere eliminata la DetailWindow\n");\
/*\
              ClosePageStazFromOW( Detail[j] );\
*/\
              ClosePageStaz( Detail[j] );\
              break;\
         } \
   }\
}\
\
/* resetto la risorsa del pictograph o indicatore\
   che ha attivato la OW\
   opw (parametro) e' l'indice del w che ha creato la OW\
*/\
XtVaSetValues(opw,XlNowOpen,False,NULL);\
\
DelElencoPagine(OWkey_refresh, drawingAreaOW );\
\
XSync(XtDisplay(UxThis),False);\
\
/* rimuovo il timer del refresh\
*/\
XtRemoveTimeOut(OWtimer_refresh);\
\
/* distruggo il db corrente\
   e rispristino quello del parent\
*/\
XrmDestroyDatabase(OwDb);\
XrmSetDatabase(XtDisplay((Widget)UxParent),ParentDb);\
\
/* elimino dalla lista delle OW aperte mantenuta\
   dalla interfaccia teleperm chiamante\
*/ \
aggiornaListChild( OperatingWindow );\
/*\
 Elimina il pixmap di sfondo se esiste\
*/\
if(drawing_pixmap)\
	XFreePixmap(XtDisplay((Widget)UxParent),drawing_pixmap);\
\
/*\
Elimino shm associate alle  window Extension se attive\
*/\
if(flag_aperture && (indice>=0))\
      {\
       if((OlElimina_shmMiniASD(database_simulatore,indice)<0))\
          printf(stderr,"ERROR: impossible to destroy shm for this O.W indice=%d\n",indice);\
      }\
/* \
chiudo la finestra \
*/\
\
UxDestroyInterface(OperatingWindow);\


*OperatingWindow_debug.class: method
*OperatingWindow_debug.name: debug
*OperatingWindow_debug.parent: OperatingWindow
*OperatingWindow_debug.methodType: int
*OperatingWindow_debug.methodArgs: 
*OperatingWindow_debug.methodBody: printf("Stampa di debug\n");

*OperatingWindow_chPage.class: method
*OperatingWindow_chPage.name: chPage
*OperatingWindow_chPage.parent: OperatingWindow
*OperatingWindow_chPage.methodType: void
*OperatingWindow_chPage.methodArgs: Widget w;\
unsigned char *nomePg;\
int tipoApertura;\

*OperatingWindow_chPage.methodBody: /*********\
 effettua il popup o la navigazione\
  di una pagina, che viene richiamata da un change page\
  posto sulla OperatingWindow\
**********************************************************/\
extern swidget create_topLevelShell1();\
extern swidget popup_topLevelShellStaz();\
extern void teleperm_naviga();\
extern int NumeroPagina();\
\
int ind_pag;  /* indice della pagina nel vettore delle pagine */\
Widget newPag; /* top widget nuova pagina */\
\
if( !strlen(nomePg) ) \
   return;\
\
\
/* apertura di una pagina\
*/\
if( (tipoApertura != CLOSE_PAGE) )\
{\
   /* la pagina non e' gia' aperta\
   */\
   if( !PaginaAperta(w,nomePg) )\
   {\
      if( !CanOpenPage(w) )\
         return;\
\
\
      ind_pag=NumeroPagina(nomePg);\
    \
      if( (Detail = (Widget *)XtRealloc( Detail, sizeof(Widget) * (numDetail+1))) == NULL)\
      {\
          fprintf(stderr,"OW: Error in allocation of Detail list\n");\
          return;\
      }\
\
      /* verifico il tipo di pagina e la apro. \
         Nota, la pagina corrente e la nuova pagina hanno lo stesso parent.\
         Att.ne la gestione del tipo Sinottico,Stazioni o teleperm\
         determina il tipo e il modo di apertura della pagina\
         se il tipo e' teleperm viene effettuata una navigazione\
         altrimenti viene fatto il popup della pagina con layout\
         e funzionalita' basate sul tipo\
         La attivazione con CHANGE_PAGE o NEW_PAGE e' \
         ininfluente.\
      */\
      if( strcmp(pagine[ind_pag].tipo,"Sinottico") == 0)\
      {\
         /* Pagine di tipo sinottico non dovrebbero essere mai chiamate\
         */\
         Detail[numDetail] = newPag = create_topLevelShell1(nomePg,UxThis,"nome_display",pagine[ind_pag].sfondo);\
         numDetail++;\
      if( newPag == NULL )\
         { \
         popup_errorDialog("SBAGLIO pagina",w);\
         return;\
         }\
      }\
      if( strcmp(pagine[ind_pag].tipo,"Stazioni") == 0)\
      {\
/*         printf("chiamo la stazione con parent = %s\n",XtName(UxThis)); */\
         Detail[numDetail] = newPag = popup_topLevelShellStaz(nomePg,UxThis,"nome_display",pagine[ind_pag].sfondo);\
         numDetail++;\
       if( newPag == NULL )\
         { \
         popup_errorDialog("SBAGLIO pagina",w);\
         return;\
         }\
      }\
      if( (strcmp(pagine[ind_pag].tipo,"Teleperm") == 0) ||\
          (strcmp(pagine[ind_pag].tipo,"Regolazione") == 0) ) {\
/*\
printf("OperatingWindow: aprire pagina regolazione --> nomepg = %s\n", nomePg);\
*/\
         teleperm_naviga(XtParent(UxThis),GOTOPAG,NumeroPagina(nomePg));\
/*\
printf("OperatingWindow: dopo chiamata a teleperm_naviga!!!\n");\
*/\
\
      }\
\
\
   }\
}\
/***\
else if( (tipoApertura == CHANGE_PAGE) )\
{\
   printf("chiamo la teleperm_naviga da CHANGE_PAGE\n");\
   teleperm_naviga(UxThis,GOTOPAG,NumeroPagina(nomePg));     \
}\
***/\
\

*OperatingWindow_chPage.arguments: w, nomePg, tipoApertura
*OperatingWindow_chPage.w.def: "Widget", "%w%"
*OperatingWindow_chPage.nomePg.def: "unsigned char", "*%nomePg%"
*OperatingWindow_chPage.tipoApertura.def: "int", "%tipoApertura%"

*OperatingWindow_SetDescr.class: method
*OperatingWindow_SetDescr.name: SetDescr
*OperatingWindow_SetDescr.parent: OperatingWindow
*OperatingWindow_SetDescr.methodType: int
*OperatingWindow_SetDescr.methodArgs: 
*OperatingWindow_SetDescr.methodBody: /* recupero le risorse top_descrizione_2,_3\
   che contengono le label da settare nelle\
   IdcodeLabel e funcodeLabel\
   ( le due descrizioni accanto all'arroe button )\
*/\
\
char *tipo;\
XrmValue value;\
char risorsa[100];\
char descr2[100];\
char descr3[100];\
XmString appo;\
Display *disp;\
\
disp = XtDisplay( UxThis );\
\
sprintf(risorsa,"top_descrizione_2");\
XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);\
strncpy(descr2,value.addr,(int)value.size);\
\
sprintf(risorsa,"top_descrizione_3");\
XrmGetResource(disp->db,risorsa,(char*)NULL,&tipo,&value);\
strncpy(descr3,value.addr,(int)value.size);\
\
appo = XmStringCreateSimple( descr2 );\
XtVaSetValues( idcodeLabel,XmNlabelString,appo,NULL);\
XmStringFree( appo );\
\
appo = XmStringCreateSimple( descr3 );\
XtVaSetValues( funcodeLabel,XmNlabelString,appo,NULL);\
XmStringFree( appo );\


*OperatingWindow_configBottoni.class: method
*OperatingWindow_configBottoni.name: configBottoni
*OperatingWindow_configBottoni.parent: OperatingWindow
*OperatingWindow_configBottoni.methodType: int
*OperatingWindow_configBottoni.methodArgs: 
*OperatingWindow_configBottoni.methodBody: /* recupero la lista dei children \
    e controllo se sono presenti OperableKeys\
    di tipo OPKEY_IMP e OPKEY_EXEC\
    se non ce ne sono elimino i tasti \
    EJECUTAR E IMP\
*/\
\
Cardinal numChildren;\
WidgetList listChildren;\
int i;\
Boolean ExecYes,ImpYes;\
\
ExecYes=False;\
ImpYes=False;\
\
/* recupero la lista dei children\
   della drawing area\
*/\
XtVaGetValues(drawingAreaOW,XmNchildren,&listChildren,\
                            XmNnumChildren,&numChildren,\
                            NULL);\
\
for(i=0;i<numChildren;i++)\
{\
   if( XlIsOperableKeysImp( listChildren[i]) )\
      ImpYes=True;\
   if( XlIsOperableKeysExec( listChildren[i]) )\
      ExecYes=True;\
}\
\
if( !ImpYes )\
  XtDestroyWidget( IMP );\
if(!ExecYes )\
  XtDestroyWidget( Ejecutar );\
\


*OperatingWindow_reqAlarms.class: method
*OperatingWindow_reqAlarms.name: reqAlarms
*OperatingWindow_reqAlarms.parent: OperatingWindow
*OperatingWindow_reqAlarms.methodType: int
*OperatingWindow_reqAlarms.methodArgs: 
*OperatingWindow_reqAlarms.methodBody: char appo_gerarchia[LUN_GERAR];\
\
int i;\
\
/*\
Metodo per preparare la gerarchia secondo \
modalita' tabelle SCADA (XtCalloc imposta da AIC che non sembra digerire array di \
unsigned char come var specifiche)\
*/\
if((gerarchie=(unsigned char *)XtCalloc(N_GERARCHIE,sizeof(unsigned char)))==NULL)\
   {\
    printf("ERROR: impossible to allocate memory for gerarchia miniASD\n");\
    return(-1);\
   }\
strcpy(appo_gerarchia,OWpag->gerarchia);\
printf("gerarchia=%s \n",appo_gerarchia);\
gerarchie[0]=(unsigned char)atoi((strtok(appo_gerarchia,",")));\
\
for(i=1;i<N_GERARCHIE;i++)\
   {\
   gerarchie[i]=(char unsigned) atoi((strtok((char *) NULL,",")));   \
\
   }\
printf("gerarchia=\n");\
\
for(i=0;i<N_GERARCHIE;i++)\
   {\
   printf(" %d ",gerarchie[i]);\
   }\
printf("\n");\
\
/* \
Chiamo metodo per creazione shm associate miniASD\
Viene associato un indice alla O.W.\
Tale indice e' l' indice nell' array delle shm associate al miniASD.\
Viene anche utilizzato per la distruzione della shm associata\
*/\
\
if (OlInserisci_shmMiniASD(database_simulatore,&allarm_data,&manual_data,&indice)<0)\
   {\
   printf("richiediAllarmiMiniASD:FALLITA creazione shm per ASD\n");\
   return(-1);\
   }\
\
\
/*\
Chiamo metodo Ol per richiesta allarmi a client_scada\
*/\
\
if(!OlRichiediAllarmiMiniASD(database_simulatore,gerarchie,indice,MINIASD_ALARM_REQ,ALL_M))\
   {\
   printf("ERROR: Impossible to send request alarms ASD to client_scada\n");\
   return(-1);\
   }\
/*\
Chiamo metodo Ol per richiesta manual a client_scada\
*/\
\
if(!OlRichiediAllarmiMiniASD(database_simulatore,gerarchie,indice,MINIASD_MANUAL_REQ,ALL_M))\
   {\
   printf("ERROR: Impossible to send request alarms ASD to client_scada\n");\
   return(-1);\
   }\
\
return(1);\
\


*OperatingWindow_ricMiniASD.class: method
*OperatingWindow_ricMiniASD.name: ricMiniASD
*OperatingWindow_ricMiniASD.parent: OperatingWindow
*OperatingWindow_ricMiniASD.methodType: int
*OperatingWindow_ricMiniASD.methodArgs: int tipo_allarmi;\

*OperatingWindow_ricMiniASD.methodBody: /*\
\
Metodo che permette di attivare la richiesta di riconoscimento di un singolo \
allarme per miniASD\
Oppure di piu' allarmi contemporaneamente\
*/\
int i;\
\
/*\
Disabilito bottoni chiusura O.W.\
*/\
\
\
if(tipo_allarmi==ALLARMI)\
   {\
   /*\
   Riconosco tutti gli allarmi\
   */\
 /*  for(i=0;i<num_allarm;i++)\
      {\
       if(!OlRiconosciAllarmiMiniASD(database_simulatore,gerarchie,indice,\
           0,ALL_M,num_allarm,i))\
         {\
         printf("ERROR: Impossible to send request alarms ASD to client_scada\n");\
         return(-1);\
         }\
      } */\
    if(!OlRiconosciAllarmiMiniASD(database_simulatore,gerarchie,indice,\
           0,ALL_M,num_allarm,OPERAZIONERICALL))\
         {\
         printf("ERROR: Impossible to send request alarms ASD to client_scada\n");\
         return(-1);\
         }\
   }\
\
else if(tipo_allarmi==MANUAL)\
   {\
   /*\
   Riconosco tutti gli allarmi\
   */\
  /* for(i=0;i<num_manual;i++)\
      {\
       if(!OlRiconosciManualiMiniASD(database_simulatore,gerarchie,indice,\
           0,ALL_M,num_manual,i))\
         {\
         printf("ERROR: Impossible to send request alarms ASD to client_scada\n");\
         return(-1);\
         }\
      }\
   */\
    if(!OlRiconosciManualiMiniASD(database_simulatore,gerarchie,indice,\
           0,ALL_M,num_manual,OPERAZIONERICALL))\
         {\
         printf("ERROR: Impossible to send request manuals ASD to client_scada\n");\
         return(-1);\
         }\
   }\
/*\
Riattivo pulsanti di chiusura\
*/\
\
return(1);
*OperatingWindow_ricMiniASD.arguments: tipo_allarmi
*OperatingWindow_ricMiniASD.tipo_allarmi.def: "int", "%tipo_allarmi%"

*OperatingWindow_CreateExt1.class: method
*OperatingWindow_CreateExt1.name: CreateExt1
*OperatingWindow_CreateExt1.parent: OperatingWindow
*OperatingWindow_CreateExt1.methodType: int
*OperatingWindow_CreateExt1.methodArgs: 
*OperatingWindow_CreateExt1.methodBody: int i;\
DATI_ALLARMI_SHM dati_allarm;\
DATI_ALLARMI_SHM dati_manual;\
DATI_ALLARMI_SHM *p_allarm_data;\
Widget sb;\
int increment,maximum,minimum,page_incr,slider_size,value;\
\
/* Var di appoggio per stringhe per widge*/\
char nomeWidget[256],appo_descr[256]; \
char descr_token[3][256];\
char *str;\
char *tipo_cai; /* punt. tipo di Cai */\
\
XrmSetDatabase(XtDisplay((Widget)UxThis),OwDb);\
/* \
Verfica su num_allarm e num_manual\
*/\
\
num_allarm =0;  /* provvisorio per DEBUG */\
num_manual=0;\
\
if(num_allarm || num_manual)\
   {\
   fprintf(stderr,"WARNING: num_allarm=%d e num_manual=%d not zero\n",\
           num_allarm,num_manual);\
   return(-1);\
   }\
\
\
\
/*\
Attendo che il client_scada abbia messo i dati nelle shm e li copi poi \
nelle variabili dati_allarm dati_manual\
La gestione e' affidata ad un semaforo.\
*/\
if(!OlGetDatiMiniASD(database_simulatore,&dati_allarm,&dati_manual,indice))\
   {\
   fprintf(stderr,"WARNING: Impossible to retrieve valid data for miniASD\n");\
   num_allarm=0;\
   num_manual=0;\
   }\
else\
   {\
   num_allarm=dati_allarm.n_all;\
   num_manual=dati_manual.n_all;\
   }\
\
printf("num_allarm=%d\n",num_allarm);\
printf("num_manual=%d\n",num_manual);\
\
/*\
Abilito bottoni di riconoscimento solo se il No di all>0\
*/\
if (num_allarm > 0)\
    set_something(dummy_ric_all,XmNsensitive,True);\
else \
    set_something(dummy_ric_all,XmNsensitive,False);\
    \
if (num_manual > 0)\
    set_something(dummy_ric_manual,XmNsensitive,True);\
else \
    set_something(dummy_ric_manual,XmNsensitive,False);\
/*\
Spazio per allocazione dinamica oggetti per miniASD\
*/\
if ( (all_caiAll_form = (Widget *) XtCalloc(1, num_allarm* sizeof(Widget)) )\
                       == NULL)\
       {\
       fprintf(stderr," OW:Error in malloc: all_caiAll_form");\
       return(-1);\
       }\
if ( (all_label = (Widget *) XtCalloc(1, num_allarm* sizeof(Widget)) )\
                       == NULL)\
       {\
       fprintf(stderr," OW:Error in malloc: all_label");\
       return(-1);\
       }\
if ( (all_caiAll = (Widget *) XtCalloc(1, num_allarm* sizeof(Widget)) )\
                       == NULL)\
       {\
       fprintf(stderr," OW:Error in malloc: all_caiAll");\
       return(-1);\
       }\
\
\
if ( (all_caiMan_form = (Widget *) XtCalloc(1, num_manual* sizeof(Widget)) )\
                       == NULL)\
       {\
       fprintf(stderr," OW:Error in malloc: all_caiMan_form");\
       return(-1);\
       }\
if ( (man_label = (Widget *) XtCalloc(1, num_manual * sizeof(Widget)) )\
                       == NULL)\
       {\
       fprintf(stderr," OW:Error in malloc: man_label");\
       return(-1);\
       }\
if ( (all_caiMan = (Widget *) XtCalloc(1, num_manual * sizeof(Widget)) )\
                       == NULL)\
       {\
       fprintf(stderr," OW:Error in malloc: all_caiMan");\
       return(-1);\
       }\
\
/*\
Vado a costruire gli oggetti contenuti nelle scrolled Window\
*/\
\
/*\
Form entro scrolled window\
*/\
       formAllarm = XtVaCreateManagedWidget( "formAllarm",\
                        xmFormWidgetClass,\
                        scrolledAlarmMiniASD,\
                        /*XmNwidth, 700,*/\
                        XmNheight, HEIGHTASDSTEP*num_allarm,\
                        XmNresizePolicy, XmRESIZE_NONE,\
                        XmNx, 0,\
                        XmNy, 0,\
                       /* RES_CONVERT( XmNbackground, "midnight blue" ),*/\
                        NULL );\
        UxPutContext( formAllarm, (char *) UxOperatingWindowContext );\
/*\
RowColumn per contenitori CAi\
*/\
\
       rowColumnAllarmCai = XtVaCreateManagedWidget( "rowColumnAllarmCai",\
                        xmRowColumnWidgetClass,\
                        formAllarm,\
                        /*XmNwidth, 30, */\
                        XmNx, 0,\
                        XmNy, 0,\
                       /* RES_CONVERT( XmNbackground, "cyan" ), */\
                        XmNadjustLast, FALSE,\
                        XmNadjustMargin, FALSE,\
                        XmNtopOffset, 0,\
                        XmNtopAttachment, XmATTACH_FORM,\
                        XmNleftOffset, 0,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        XmNbottomOffset, 0,\
                        XmNbottomAttachment, XmATTACH_FORM,\
                        NULL );\
        UxPutContext( rowColumnAllarmCai, (char *) UxOperatingWindowContext );\
/*\
rowColumn per contenere stringhe allarmi\
*/\
rowColumnAllarm=XtVaCreateManagedWidget( "rowColumnAllarm",\
                        xmRowColumnWidgetClass,\
                        formAllarm,\
                       /* XmNwidth, 600,*/\
                        XmNheight, HEIGHTASDSTEP*num_allarm,\
                        XmNx, 0,\
                        XmNy, 0,\
                        XmNtopOffset, 0,\
                        XmNtopAttachment, XmATTACH_FORM,\
                        XmNbottomOffset, 0,\
                        XmNbottomAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftWidget, rowColumnAllarmCai,\
                        /*RES_CONVERT( XmNbackground, "forest green"),*/\
                        NULL );\
        UxPutContext( rowColumnAllarm, (char *) UxOperatingWindowContext );\
/*\
Parte per costruzione oggetti allocati dinamicamente\
*/\
for(i=0;i<num_allarm;i++)\
   {\
\
/*\
Vado a ricavare la stringa che scrivero' nella label\
*/\
strcpy(appo_descr,dati_allarm.descr[i]);\
str=strtok(appo_descr,"$");\
if(str)\
   {\
   str=strtok((char *)NULL,"|");\
   str++;             /* salto il tipo di allarme */\
   while(*str==' ')   /* salto spazi vuoti che SCADA spedisce */\
      str++;\
   if(str)\
      strcpy(descr_token[0],str);\
   else \
      strcpy(descr_token[0],"");\
   \
   str=strtok((char *)NULL,"|");\
   if(str)\
      strcpy(descr_token[1],str);\
   else\
      strcpy(descr_token[1],"");\
   }\
   strcpy(descr_token[2],dati_allarm.data[i]);\
  \
   sprintf(appo_descr,"%-*.*s %-*.*s %-*.*s",41,41,descr_token[0],10,10,\
             descr_token[1],10,10,descr_token[2]);\
\
/*printf("label=%s\n",appo_descr);*/\
\
   strcpy(nomeWidget,"");\
   sprintf(nomeWidget,"%d",i);\
   strcat(nomeWidget,"_allLabelASD");\
\
       all_label[i] = XtVaCreateManagedWidget( nomeWidget,\
                        xmLabelWidgetClass,\
                        rowColumnAllarm,\
                        XmNx, 100,\
                        XmNy, 40,\
                        XmNrecomputeSize, FALSE,\
                        /*XmNwidth, 600,*/\
                        XmNheight, 29,\
                        /*XmNfontList, UxConvertFontList( "courier_bold10" ),*/\
                        RES_CONVERT( XmNlabelString, appo_descr ),\
                        NULL );\
        UxPutContext( all_label[i], (char *) UxOperatingWindowContext  );\
/*\
Parte per inserimento form per cai\
*/ \
   strcpy(nomeWidget,"");\
   sprintf(nomeWidget,"%d",i);\
   strcat(nomeWidget,"_formCaiAllASD");\
\
   all_caiAll_form[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xmFormWidgetClass,\
                        rowColumnAllarmCai,\
                        XmNresizePolicy, XmRESIZE_NONE,\
                        XmNheight, 29,\
                        XmNwidth, 29,\
                        /*RES_CONVERT( XmNbackground, "white"),*/\
                        NULL );\
        UxPutContext( all_caiAll_form[i], (char *) UxOperatingWindowContext  );\
/*\
Parte per inserimento CAI\
*/\
       strcpy(nomeWidget,"");\
       sprintf(nomeWidget,"%d",i);\
       strcat(nomeWidget,"_CaiAll");\
/*\
Determino il tipo di Cai che e' la  lettera dopo $ del name_all \
*/\
       tipo_cai=strchr(dati_allarm.descr[i],'$');\
       if(!tipo_cai)\
           {\
           fprintf(stderr,"WARNING:Impossble to determine CAI[%d] type\n",i);\
           }\
\
       all_caiAll[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xlCaiAllWidgetClass,\
                        all_caiAll_form[i],\
                        XmNx, 0,\
                        XmNy, 0,\
                        XmNheight, 20,\
                        XmNwidth, 20,\
                        XmNtopAttachment,XmATTACH_FORM,\
                        XmNleftAttachment,XmATTACH_FORM,\
#ifndef DESIGN_TIME\
                        XlNconfig, False,\
#endif\
                        XlNtipoCaiAll,(int)( *(tipo_cai+1) ),\
                        \
                        XlNstatus, (int)dati_allarm.emission[i],\
                        NULL );\
\
        UxPutContext( all_caiAll[i], (char *) UxOperatingWindowContext );\
                                                                      \
                                               \
   }/* end for num_allarm */\
\
/*\
Setto database dei punti per CaiAll\
*/\
OlSetDatabasePunti(all_caiAll,num_allarm,database_simulatore);\
\
/*\
Parte per gestione (parziale) scrollbar \
*/\
XtVaGetValues(scrolledAlarmMiniASD,XmNverticalScrollBar,&sb,NULL);\
\
XtVaGetValues( sb,\
              XmNincrement, &increment,\
              XmNmaximum, &maximum,\
              XmNminimum,   &minimum,\
              XmNpageIncrement, &page_incr,\
              XmNsliderSize, &slider_size,\
              XmNvalue, &value,\
              NULL);\
\
/*\
printf("DEBUG:increment=%d maximum=%d minimum=%d page_incr=%d slider_size=%d value=%d\n",increment,maximum,minimum,page_incr,slider_size,value);\
*/\
XtVaSetValues(sb,\
             XmNincrement,HEIGHTASDSTEP,\
             XmNpageIncrement,HEIGHTASDSTEP*3,\
             NULL);\
\
\
/************************\
Parte per Manual\
*************************/\
/*\
Vado a costruire gli oggetti contenuti nelle scrolled Window\
*/\
\
/*\
Form entro scrolled window\
*/\
       formManual = XtVaCreateManagedWidget( "formManual",\
                        xmFormWidgetClass,\
                        scrolledManualMiniASD,\
                        XmNheight, HEIGHTASDSTEP*num_manual,\
                        XmNresizePolicy, XmRESIZE_NONE,\
                        XmNx, 0,\
                        XmNy, 0,\
                        NULL );\
        UxPutContext( formManual, (char *) UxOperatingWindowContext );\
\
/*\
RowColumn per contenitori CAi\
*/\
\
       rowColumnManualCai = XtVaCreateManagedWidget( "rowColumnManualCai",\
                        xmRowColumnWidgetClass,\
                        formManual,\
                        /*XmNwidth, 30, */\
                        XmNx, 0,\
                        XmNy, 0,\
                        XmNadjustLast, FALSE,\
                        XmNadjustMargin, FALSE,\
                        XmNtopOffset, 0,\
                        XmNtopAttachment, XmATTACH_FORM,\
                        XmNleftOffset, 0,\
                        XmNleftAttachment, XmATTACH_FORM,\
                        XmNbottomOffset, 0,\
                        XmNbottomAttachment, XmATTACH_FORM,\
                        NULL );\
        UxPutContext( rowColumnManualCai, (char *) UxOperatingWindowContext );\
/*\
rowColumn per contenere stringhe manual\
*/\
rowColumnManual=XtVaCreateManagedWidget( "rowColumnManual",\
                        xmRowColumnWidgetClass,\
                        formManual,\
                        XmNheight, HEIGHTASDSTEP*num_manual,\
                        XmNx, 0,\
                        XmNy, 0,\
                        XmNtopOffset, 0,\
                        XmNtopAttachment, XmATTACH_FORM,\
                        XmNbottomOffset, 0,\
                        XmNbottomAttachment, XmATTACH_FORM,\
                        XmNleftAttachment, XmATTACH_WIDGET,\
                        XmNleftWidget, rowColumnManualCai,\
                        NULL );\
        UxPutContext( rowColumnManual, (char *) UxOperatingWindowContext );\
\
/*\
Parte per costruzione oggetti allocati dinamicamente\
*/\
for(i=0;i<num_manual;i++)\
   {\
/*\
Vado a ricavare la stringa che scrivero' nella label\
*/\
strcpy(appo_descr,dati_manual.descr[i]);\
str=strtok(appo_descr,"$");\
if(str)\
   {\
   str=strtok((char *)NULL,"|");\
   str++;             /* salto il tipo di manual */\
   while(*str==' ')   /* salto spazi vuoti che SCADA spedisce */\
      str++;\
   if(str)\
      strcpy(descr_token[0],str);\
   else \
      strcpy(descr_token[0],"");\
   \
   str=strtok((char *)NULL,"|");\
   if(str)\
      strcpy(descr_token[1],str);\
   else\
      strcpy(descr_token[1],"");\
   }\
   strcpy(descr_token[2],dati_manual.data[i]);\
  \
   sprintf(appo_descr,"%-*.*s %-*.*s %-*.*s",41,41,descr_token[0],10,10,\
             descr_token[1],10,10,descr_token[2]);\
\
/*printf("label=%s\n",appo_descr);*/\
\
   strcpy(nomeWidget,"");\
   sprintf(nomeWidget,"%d",i);\
   strcat(nomeWidget,"_manLabelASD");\
\
       man_label[i] = XtVaCreateManagedWidget( nomeWidget,\
                        xmLabelWidgetClass,\
                        rowColumnManual,\
                        XmNx, 100,\
                        XmNy, 40,\
                        XmNrecomputeSize, FALSE,\
                        /*XmNwidth, 600,*/\
                        XmNheight, 29,\
                        /*XmNfontList, UxConvertFontList( "courier_bold10" ),*/\
                        RES_CONVERT( XmNlabelString, appo_descr ),\
                        NULL );\
        UxPutContext( man_label[i], (char *) UxOperatingWindowContext  );\
/*\
Parte per inserimento form per cai\
*/ \
   strcpy(nomeWidget,"");\
   sprintf(nomeWidget,"%d",i);\
   strcat(nomeWidget,"_formCaiManASD");\
\
   all_caiMan_form[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xmFormWidgetClass,\
                        rowColumnManualCai,\
                        XmNresizePolicy, XmRESIZE_NONE,\
                        XmNheight, 29,\
                        XmNwidth, 29,\
                        /*RES_CONVERT( XmNbackground, "white"),*/\
                        NULL );\
        UxPutContext( all_caiMan_form[i], (char *) UxOperatingWindowContext  );\
/*\
Parte per inserimento CAI\
*/\
       strcpy(nomeWidget,"");\
       sprintf(nomeWidget,"%d",i);\
       strcat(nomeWidget,"_CaiMan");\
/*\
Determino il tipo di Cai che e' la  lettera dopo $ del name_man \
*/\
       tipo_cai=strchr(dati_manual.descr[i],'$');\
       if(!tipo_cai)\
           {\
           fprintf(stderr,"WARNING:Impossble to determine CAI[%d] type\n",i);\
           }\
\
       all_caiMan[i]= XtVaCreateManagedWidget( nomeWidget,\
                        xlCaiAllWidgetClass,\
                        all_caiMan_form[i],\
                        XmNx, 0,\
                        XmNy, 0,\
                        XmNheight, 20,\
                        XmNwidth, 20,\
                        XmNtopAttachment,XmATTACH_FORM,\
                        XmNleftAttachment,XmATTACH_FORM,\
#ifndef DESIGN_TIME\
                        XlNconfig, False,\
#endif\
                        XlNtipoCaiAll,(int)( *(tipo_cai+1) ),\
                        \
                        XlNstatus, (int)dati_manual.emission[i],\
                        NULL );\
\
        UxPutContext( all_caiMan[i], (char *) UxOperatingWindowContext );\
                                                                      \
                                               \
   }/* end for num_manual */\
\
/*\
Setto database dei punti per CaiMan\
*/\
OlSetDatabasePunti(all_caiMan,num_manual,database_simulatore);\
\
/*\
Parte per gestione scrollbar\
*/\
XtVaGetValues(scrolledManualMiniASD,XmNverticalScrollBar,&sb,NULL);\
\
XtVaGetValues( sb,\
              XmNincrement, &increment,\
              XmNmaximum, &maximum,\
              XmNminimum,   &minimum,\
              XmNpageIncrement, &page_incr,\
              XmNsliderSize, &slider_size,\
              XmNvalue, &value,\
              NULL);\
/*\
printf("DEBUGmanual:increment=%d maximum=%d minimum=%d page_incr=%d slider_size=%d value=%d\n",increment,maximum,minimum,page_incr,slider_size,value);\
*/\
XtVaSetValues(sb,\
             XmNincrement,HEIGHTASDSTEP,\
             XmNpageIncrement,HEIGHTASDSTEP*3,\
             NULL);\
\
\
\
\


*OperatingWindow_DestroyExt1.class: method
*OperatingWindow_DestroyExt1.name: DestroyExt1
*OperatingWindow_DestroyExt1.parent: OperatingWindow
*OperatingWindow_DestroyExt1.methodType: int
*OperatingWindow_DestroyExt1.methodArgs: 
*OperatingWindow_DestroyExt1.methodBody: /********************\
Parte per allarmi\
********************/\
/*\
Distruggo oggetti creati e le memorie allocate\
*/\
if(num_allarm)\
   {  \
    XtDestroyWidget(formAllarm);\
    XtFree(all_caiAll_form);\
    XtFree(all_label);\
    XtFree(all_caiAll);\
   /*\
   Metto a 0 num_allarm per bloccare XlRefresh\
   */\
   num_allarm=0;\
   }\
\
/********************\
Parte per manual\
********************/\
/*\
Distruggo oggetti creati e le memorie allocate\
*/\
if(num_manual)\
   {  \
    XtDestroyWidget(formManual);\
    XtFree(all_caiMan_form);\
    XtFree(man_label);\
    XtFree(all_caiMan);\
   /*\
   Metto a 0 num_manual per bloccare XlRefresh\
   */\
   num_manual=0;\
   }

*OperatingWindow.static: true
*OperatingWindow.name: OperatingWindow
*OperatingWindow.parent: NO_PARENT
*OperatingWindow.parentExpression: UxParent
*OperatingWindow.x: 440
*OperatingWindow.y: 231
*OperatingWindow.width: 325
*OperatingWindow.height: 400
*OperatingWindow.mwmDecorations: -1
*OperatingWindow.allowShellResize: "true"
*OperatingWindow.mwmFunctions: -1

*mainForm.class: form
*mainForm.static: true
*mainForm.name: mainForm
*mainForm.parent: OperatingWindow
*mainForm.resizePolicy: "resize_none"
*mainForm.unitType: "pixels"
*mainForm.x: 10
*mainForm.y: 10
*mainForm.width: 360
*mainForm.height: 380
*mainForm.navigationType: "none"

*footerForm.class: form
*footerForm.static: true
*footerForm.name: footerForm
*footerForm.parent: mainForm
*footerForm.resizePolicy: "resize_none"
*footerForm.x: 10
*footerForm.y: 370
*footerForm.width: 370
*footerForm.height: 40
*footerForm.bottomAttachment: "attach_form"
*footerForm.bottomOffset: 0
*footerForm.leftAttachment: "attach_form"
*footerForm.leftOffset: 0
*footerForm.rightAttachment: "attach_form"
*footerForm.rightOffset: 0
*footerForm.topAttachment: "attach_none"
*footerForm.topPosition: 0
*footerForm.navigationType: "none"
*footerForm.traversalOn: "false"

*fEjecutar.class: form
*fEjecutar.static: true
*fEjecutar.name: fEjecutar
*fEjecutar.parent: footerForm
*fEjecutar.resizePolicy: "resize_none"
*fEjecutar.x: 10
*fEjecutar.y: 10
*fEjecutar.width: 90
*fEjecutar.height: 20
*fEjecutar.bottomAttachment: "attach_form"
*fEjecutar.bottomOffset: 0
*fEjecutar.leftAttachment: "attach_form"
*fEjecutar.leftOffset: 0
*fEjecutar.rightAttachment: "attach_position"
*fEjecutar.rightPosition: 33
*fEjecutar.topAttachment: "attach_form"
*fEjecutar.topOffset: 0

*Ejecutar.class: pushButton
*Ejecutar.static: true
*Ejecutar.name: Ejecutar
*Ejecutar.parent: fEjecutar
*Ejecutar.x: 20
*Ejecutar.y: 10
*Ejecutar.width: 90
*Ejecutar.height: 20
*Ejecutar.bottomAttachment: "attach_form"
*Ejecutar.bottomOffset: 1
*Ejecutar.leftAttachment: "attach_form"
*Ejecutar.leftOffset: 5
*Ejecutar.rightAttachment: "attach_form"
*Ejecutar.rightOffset: 5
*Ejecutar.topAttachment: "attach_form"
*Ejecutar.topOffset: 1
*Ejecutar.fontList.source: public
*Ejecutar.fontList: "helvetica14"
*Ejecutar.activateCallback: {\
extern void XlOperableKeysSendPert();\
Pixel bg_butt;\
\
/* invio la perturbazione associata all'ultimo OPKEY_EXEC\
   che e' stato premuto\
*/\
\
if( lastWexec != NULL )\
{\
   XlOperableKeysSendPert( lastWexec );\
\
   XtVaGetValues( lastWexec,XlNlstateBg,&bg_butt,NULL);\
\
   /* reset dell'indice di widget \
   */\
   lastWexec = NULL;\
\
   /* rendo insensitive il bottone di ejecutar\
      (che deve risultare sensitive solo quando c'e' una perturbazione da inviare)\
   */\
   XtVaSetValues(Ejecutar,\
                  XmNsensitive,False,\
                  XmNbackground,bg_butt,\
                  NULL);\
\
}\
\
}
*Ejecutar.foreground.source: public
*Ejecutar.foreground: "WhiteSmoke"
*Ejecutar.armColor.source: public
*Ejecutar.armColor: "#6b7491"
*Ejecutar.background.source: public
*Ejecutar.background: "#7e88ab"
*Ejecutar.bottomShadowColor.source: public
*Ejecutar.bottomShadowColor: "#987867"
*Ejecutar.labelString.source: public
*Ejecutar.labelString: "Ejecutar"
*Ejecutar.topShadowColor.source: public
*Ejecutar.topShadowColor: "#dcbca3"

*fIMP.class: form
*fIMP.static: true
*fIMP.name: fIMP
*fIMP.parent: footerForm
*fIMP.resizePolicy: "resize_none"
*fIMP.x: 10
*fIMP.y: 10
*fIMP.width: 90
*fIMP.height: 20
*fIMP.leftAttachment: "attach_position"
*fIMP.leftOffset: 0
*fIMP.rightAttachment: "attach_position"
*fIMP.rightPosition: 66
*fIMP.leftPosition: 33
*fIMP.bottomAttachment: "attach_form"
*fIMP.bottomOffset: 0
*fIMP.topAttachment: "attach_form"
*fIMP.topOffset: 0

*IMP.class: pushButton
*IMP.static: true
*IMP.name: IMP
*IMP.parent: fIMP
*IMP.x: 20
*IMP.y: 10
*IMP.width: 90
*IMP.height: 20
*IMP.bottomAttachment: "attach_form"
*IMP.bottomOffset: 1
*IMP.leftAttachment: "attach_form"
*IMP.leftOffset: 5
*IMP.rightAttachment: "attach_form"
*IMP.rightOffset: 5
*IMP.topAttachment: "attach_form"
*IMP.topOffset: 1
*IMP.fontList.source: public
*IMP.fontList: "helvetica14"
*IMP.activateCallback: {\
extern void EffettoPushButton();\
Pixel bkg_col,arm_col,top_col,bot_col,dummy_col;\
\
\
/* inverto i colori di arm e background ad ogni pressione\
   del bottone cosi da dare la impressione dello stato\
   premuto o rilasciato del tasto\
*/ \
\
/* recupero i colori correnti\
\
XtVaGetValues(UxWidget,XmNwidth,&w,XmNheight,&h,\
                         XmNbackground,&bkg_col,\
                         XmNarmColor,&arm_col,\
                         XmNbottomShadowColor,&bot_col,\
                         XmNtopShadowColor,&top_col,\
                         NULL);\
*/\
\
\
/* se il bottone e' premuto\
    disabilito tutto\
*/                      \
if( imp_premuto )\
{\
              \
/* disabilitazione degli OperableKeys di tipo IMPULSE\
   abilitaOpkeys();        \
*/\
   if( OperatingWindow_abilitaOpKeys(OperatingWindow,&UxEnv,OPKEY_IMPULSE,False) )\
   {\
      /* inverto i colori\
     \
      dummy_col = bkg_col;\
      bkg_col = arm_col;\
      arm_col = dummy_col; \
      dummy_col = top_col;\
      top_col = bot_col;\
      bot_col = dummy_col;\
   \
      XtVaSetValues(UxWidget,\
                    XmNbackground,bkg_col,\
                    XmNarmColor,arm_col,\
                    XmNbottomShadowColor,bot_col,\
                    XmNtopShadowColor,top_col,\
                    NULL);          \
      */\
\
      EffettoPushButton(UxWidget);\
      imp_premuto = False;\
   }\
}\
else\
{\
\
/* se e' disabilitato il bottone IMPULSE lo abilito\
   abilitazione degli OperableKeys di tipo IMPULSE\
   disabilitaOpKeys();        \
*/\
   if( OperatingWindow_abilitaOpKeys(OperatingWindow,&UxEnv,OPKEY_IMPULSE,True) )\
   {\
      /* inverto i colori\
      \
      dummy_col = bkg_col;\
      bkg_col = arm_col;\
      arm_col = dummy_col; \
\
      dummy_col = top_col;\
      top_col = bot_col;\
      bot_col = dummy_col;\
\
      XtVaSetValues(UxWidget,\
                    XmNbackground,bkg_col,\
                    XmNarmColor,arm_col,\
                    XmNbottomShadowColor,bot_col,\
                    XmNtopShadowColor,top_col,\
                    NULL);          \
*/\
      EffettoPushButton( UxWidget );\
\
      imp_premuto = True;\
   }\
}\
\
\
}
*IMP.labelType: "string"
*IMP.armPixmap: "/usr/include/X11/bitmaps/mailfull"
*IMP.armColor.source: public
*IMP.armColor: "#6b7491"
*IMP.bottomShadowColor.source: public
*IMP.bottomShadowColor: "#987867"
*IMP.foreground.source: public
*IMP.foreground: "WhiteSmoke"
*IMP.topShadowColor.source: public
*IMP.topShadowColor: "#dcbca3"
*IMP.background.source: public
*IMP.background: "#7e88ab"

*fCerrar.class: form
*fCerrar.static: true
*fCerrar.name: fCerrar
*fCerrar.parent: footerForm
*fCerrar.resizePolicy: "resize_none"
*fCerrar.x: 139
*fCerrar.y: 10
*fCerrar.width: 90
*fCerrar.height: 20
*fCerrar.bottomAttachment: "attach_form"
*fCerrar.bottomOffset: 0
*fCerrar.leftAttachment: "attach_position"
*fCerrar.leftOffset: 0
*fCerrar.leftPosition: 66
*fCerrar.rightAttachment: "attach_form"
*fCerrar.rightOffset: 0
*fCerrar.topAttachment: "attach_form"
*fCerrar.topOffset: 0

*Cerrar.class: pushButton
*Cerrar.static: true
*Cerrar.name: Cerrar
*Cerrar.parent: fCerrar
*Cerrar.x: 20
*Cerrar.y: 10
*Cerrar.width: 90
*Cerrar.height: 20
*Cerrar.bottomAttachment: "attach_form"
*Cerrar.bottomOffset: 1
*Cerrar.leftAttachment: "attach_form"
*Cerrar.leftOffset: 5
*Cerrar.rightAttachment: "attach_form"
*Cerrar.rightOffset: 5
*Cerrar.topAttachment: "attach_form"
*Cerrar.topOffset: 1
*Cerrar.activateCallback: {\
/*\
  chiudo la OW\
*/\
OperatingWindow_closeOW(OperatingWindow,&UxEnv);\
\
\
}
*Cerrar.fontList.source: public
*Cerrar.fontList: "helvetica14"
*Cerrar.armColor.source: public
*Cerrar.armColor: "#6b7491"
*Cerrar.background.source: public
*Cerrar.background: "#7e88ab"
*Cerrar.bottomShadowColor.source: public
*Cerrar.bottomShadowColor: "#987867"
*Cerrar.foreground.source: public
*Cerrar.foreground: "WhiteSmoke"
*Cerrar.topShadowColor.source: public
*Cerrar.topShadowColor: "#dcbca3"

*headerForm.class: form
*headerForm.static: true
*headerForm.name: headerForm
*headerForm.parent: mainForm
*headerForm.resizePolicy: "resize_none"
*headerForm.x: 0
*headerForm.y: 0
*headerForm.width: 330
*headerForm.height: 70
*headerForm.bottomAttachment: "attach_none"
*headerForm.bottomPosition: 13
*headerForm.leftAttachment: "attach_form"
*headerForm.leftOffset: 0
*headerForm.rightAttachment: "attach_form"
*headerForm.rightOffset: 0
*headerForm.topAttachment: "attach_form"
*headerForm.topOffset: 0
*headerForm.bottomOffset: 345
*headerForm.navigationType: "none"
*headerForm.traversalOn: "false"

*bOpenExt1.class: arrowButton
*bOpenExt1.static: true
*bOpenExt1.name: bOpenExt1
*bOpenExt1.parent: headerForm
*bOpenExt1.x: 289
*bOpenExt1.y: 0
*bOpenExt1.width: 36
*bOpenExt1.height: 30
*bOpenExt1.bottomAttachment: "attach_none"
*bOpenExt1.leftAttachment: "attach_self"
*bOpenExt1.rightAttachment: "attach_form"
*bOpenExt1.rightOffset: 0
*bOpenExt1.topAttachment: "attach_none"
*bOpenExt1.topOffset: 0
*bOpenExt1.bottomOffset: 0
*bOpenExt1.bottomPosition: 0
*bOpenExt1.activateCallback: {\
\
/*unsigned char *gerarchie;*/\
\
if(!flag_aperture)\
   {\
/*\
Chiamo metodo che richiede allarmi allo scada in base alla gerarchia\
della O.W..Restituisce se tutto OK, l' indice della shm nell' array\
dell ' oggetto OLDatabasePunti. \
*/\
\
   if((OperatingWindow_reqAlarms(OperatingWindow,&UxEnv))<0)\
      {\
      fprintf(stderr,"ERROR: Impossible to request alarms this O.W.\n");\
      return;\
      } \
   flag_aperture=1;\
   OperatingWindow_CreateExt1(OperatingWindow,&UxEnv);\
   }\
else     /* Chiusura Window Extension1 */\
   { \
/*\
Elimino shm associate alla shm se esistono\
*/\
   if(indice>=0)\
      {\
       if((OlElimina_shmMiniASD(database_simulatore,indice)<0))\
          printf(stderr,"ERROR: impossible to destroy shm for this O.W indice=%d\n",indice);\
      indice=-1;\
      }\
\
   flag_aperture=0; \
   XtFree(gerarchie);\
/*\
Chiamo il metodo con cui  distruggo widget contenuti nella EW1\
*/\
\
OperatingWindow_DestroyExt1(OperatingWindow,&UxEnv);\
\
   }\
\
/*\
chiamo il metodo di apri/chiudi window extension1\
*/\
OperatingWindow_OpenExt1(OperatingWindow,&UxEnv);\
\
\
}
*bOpenExt1.sensitive: "true"

*idcodeLabel.class: label
*idcodeLabel.static: true
*idcodeLabel.name: idcodeLabel
*idcodeLabel.parent: headerForm
*idcodeLabel.x: 10
*idcodeLabel.y: 7
*idcodeLabel.width: 340
*idcodeLabel.height: 20
*idcodeLabel.labelString: "IDENTIFICATIONCODE"
*idcodeLabel.bottomAttachment: "attach_none"
*idcodeLabel.leftAttachment: "attach_form"
*idcodeLabel.leftOffset: 0
*idcodeLabel.rightAttachment: "attach_widget"
*idcodeLabel.rightOffset: 5
*idcodeLabel.rightWidget: "bOpenExt1"
*idcodeLabel.topAttachment: "attach_none"
*idcodeLabel.topOffset: 0
*idcodeLabel.fontList.source: public
*idcodeLabel.fontList: "helvetica14"

*funcodeLabel.class: label
*funcodeLabel.static: true
*funcodeLabel.name: funcodeLabel
*funcodeLabel.parent: headerForm
*funcodeLabel.x: 0
*funcodeLabel.y: 38
*funcodeLabel.width: 338
*funcodeLabel.height: 20
*funcodeLabel.labelString: "FUNCTION NAME"
*funcodeLabel.alignment: "alignment_center"
*funcodeLabel.bottomAttachment: "attach_none"
*funcodeLabel.leftAttachment: "attach_form"
*funcodeLabel.leftOffset: 0
*funcodeLabel.rightAttachment: "attach_widget"
*funcodeLabel.rightWidget: "bOpenExt1"
*funcodeLabel.topAttachment: "attach_none"
*funcodeLabel.fontList.source: public
*funcodeLabel.fontList: "helvetica14"

*separatorGadget2.class: separatorGadget
*separatorGadget2.static: true
*separatorGadget2.name: separatorGadget2
*separatorGadget2.parent: headerForm
*separatorGadget2.x: 10
*separatorGadget2.y: 31
*separatorGadget2.width: 250
*separatorGadget2.height: 3
*separatorGadget2.leftAttachment: "attach_form"
*separatorGadget2.leftOffset: 0
*separatorGadget2.rightAttachment: "attach_form"
*separatorGadget2.rightWidget: ""
*separatorGadget2.topAttachment: "attach_widget"
*separatorGadget2.topOffset: 3
*separatorGadget2.topWidget: "idcodeLabel"

*separatorGadget3.class: separatorGadget
*separatorGadget3.static: true
*separatorGadget3.name: separatorGadget3
*separatorGadget3.parent: headerForm
*separatorGadget3.x: 10
*separatorGadget3.y: 61
*separatorGadget3.width: 250
*separatorGadget3.height: 3
*separatorGadget3.leftAttachment: "attach_form"
*separatorGadget3.leftOffset: 0
*separatorGadget3.rightAttachment: "attach_form"
*separatorGadget3.rightOffset: 0
*separatorGadget3.topAttachment: "attach_widget"
*separatorGadget3.topOffset: 2
*separatorGadget3.topWidget: "funcodeLabel"

*extension1.class: form
*extension1.static: true
*extension1.name: extension1
*extension1.parent: mainForm
*extension1.resizePolicy: "resize_any"
*extension1.x: 0
*extension1.y: 70
*extension1.width: 295
*extension1.height: 260
*extension1.leftAttachment: "attach_form"
*extension1.leftOffset: 0
*extension1.rightAttachment: "attach_form"
*extension1.rightOffset: 0
*extension1.bottomAttachment: "attach_none"
*extension1.createManaged: "false"
*extension1.ancestorSensitive: "true"
*extension1.topAttachment: "attach_none"
*extension1.topOffset: 0

*dummy_ric_all.class: pushButton
*dummy_ric_all.static: true
*dummy_ric_all.name: dummy_ric_all
*dummy_ric_all.parent: extension1
*dummy_ric_all.isCompound: "true"
*dummy_ric_all.compoundIcon: "push.xpm"
*dummy_ric_all.compoundName: "push_Button"
*dummy_ric_all.x: 250
*dummy_ric_all.y: 30
*dummy_ric_all.activateCallback: {\
\
int increment,maximum,minimum,page_incr,slider_size,value;\
if(flag_aperture)\
   {\
\
/*\
Invio richiesta riconoscimento allarmi (parametro ALLARMI)\
*/\
 \
\
  if((OperatingWindow_ricMiniASD(OperatingWindow,&UxEnv,ALLARMI))<0)\
      {\
      fprintf(stderr,"ERROR: Impossible to request alarms this O.W.\n");\
      return;\
      }\
   /* Disabilito bottone  e ne setto le dimensioni*/\
   set_something(dummy_ric_all,XmNsensitive,False);\
\
   }\
}
*dummy_ric_all.width.source: public
*dummy_ric_all.width: 40
*dummy_ric_all.labelPixmap: "ackalMiniASD.bmp"
*dummy_ric_all.labelType: "pixmap"
*dummy_ric_all.height.source: public
*dummy_ric_all.height: 46
*dummy_ric_all.labelInsensitivePixmap: "nullMiniASD.bmp"

*scrolledAlarmMiniASD.class: scrolledWindow
*scrolledAlarmMiniASD.static: true
*scrolledAlarmMiniASD.name: scrolledAlarmMiniASD
*scrolledAlarmMiniASD.parent: extension1
*scrolledAlarmMiniASD.scrollingPolicy: "automatic"
*scrolledAlarmMiniASD.width: 250
*scrolledAlarmMiniASD.height: 130
*scrolledAlarmMiniASD.isCompound: "true"
*scrolledAlarmMiniASD.compoundIcon: "scrlwnd.xpm"
*scrolledAlarmMiniASD.compoundName: "scrolled_Window"
*scrolledAlarmMiniASD.x: 0
*scrolledAlarmMiniASD.y: 0
*scrolledAlarmMiniASD.scrollBarDisplayPolicy: "static"

*scrolledManualMiniASD.class: scrolledWindow
*scrolledManualMiniASD.static: true
*scrolledManualMiniASD.name: scrolledManualMiniASD
*scrolledManualMiniASD.parent: extension1
*scrolledManualMiniASD.scrollingPolicy: "automatic"
*scrolledManualMiniASD.width: 270
*scrolledManualMiniASD.height: 120
*scrolledManualMiniASD.isCompound: "true"
*scrolledManualMiniASD.compoundIcon: "scrlwnd.xpm"
*scrolledManualMiniASD.compoundName: "scrolled_Window"
*scrolledManualMiniASD.x: 0
*scrolledManualMiniASD.y: 130
*scrolledManualMiniASD.topAttachment: "attach_widget"
*scrolledManualMiniASD.topOffset: 0
*scrolledManualMiniASD.topWidget: "scrolledAlarmMiniASD"
*scrolledManualMiniASD.bottomAttachment: "attach_form"
*scrolledManualMiniASD.rightAttachment: "attach_opposite_widget"
*scrolledManualMiniASD.rightWidget: "scrolledAlarmMiniASD"
*scrolledManualMiniASD.leftAttachment: "attach_form"
*scrolledManualMiniASD.scrollBarDisplayPolicy: "static"

*dummy_ric_manual.class: pushButton
*dummy_ric_manual.static: true
*dummy_ric_manual.name: dummy_ric_manual
*dummy_ric_manual.parent: extension1
*dummy_ric_manual.isCompound: "true"
*dummy_ric_manual.compoundIcon: "push.xpm"
*dummy_ric_manual.compoundName: "push_Button"
*dummy_ric_manual.x: 250
*dummy_ric_manual.y: 160
*dummy_ric_manual.activateCallback: {\
\
\
if(flag_aperture)\
   {\
\
   if((OperatingWindow_ricMiniASD(OperatingWindow,&UxEnv,MANUAL))<0)\
      {\
      fprintf(stderr,"ERROR: Impossible to request alarms this O.W.\n");\
      return;\
      }\
\
   set_something(dummy_ric_manual,XmNsensitive,False);\
   }\
}
*dummy_ric_manual.width.source: public
*dummy_ric_manual.width: 40
*dummy_ric_manual.labelPixmap: "ackmaMiniASD.bmp"
*dummy_ric_manual.labelType: "pixmap"
*dummy_ric_manual.foreground.source: public
*dummy_ric_manual.foreground: "black"
*dummy_ric_manual.height.source: public
*dummy_ric_manual.height: 46
*dummy_ric_manual.labelInsensitivePixmap: "nullMiniASD.bmp"

*drawingAreaOW.class: drawingArea
*drawingAreaOW.static: true
*drawingAreaOW.name: drawingAreaOW
*drawingAreaOW.parent: mainForm
*drawingAreaOW.x: 0
*drawingAreaOW.y: 70
*drawingAreaOW.width: 325
*drawingAreaOW.height: 290
*drawingAreaOW.topAttachment: "attach_form"
*drawingAreaOW.leftAttachment: "attach_form"
*drawingAreaOW.leftOffset: 0
*drawingAreaOW.rightAttachment: "attach_form"
*drawingAreaOW.rightOffset: 0
*drawingAreaOW.exposeCallback: {\
#ifndef DESIGN_TIME\
disegna_bck(UxWidget,OWpag->sfondo,UxCallbackArg,&(region_ow),False);\
#endif\
}
*drawingAreaOW.topOffset: 71
*drawingAreaOW.navigationType: "none"
*drawingAreaOW.marginHeight: 0
*drawingAreaOW.marginWidth: 0

