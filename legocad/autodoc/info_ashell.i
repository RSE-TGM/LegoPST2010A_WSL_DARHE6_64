! UIMX ascii 2.0 key: 7564                                                      

*info_ashell.class: applicationShell
*info_ashell.parent: NO_PARENT
*info_ashell.static: true
*info_ashell.gbldecl: /*\
   modulo info_ashell.i\
   tipo \
   release 1.12\
   data 3/31/95\
   reserved @(#)info_ashell.i	1.12\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
\
#include <X11/Xlib.h>\
#include <X11/Intrinsic.h>\
\
#include "autodoc.h"\
\
/************************************************************************/\
/* VARIABILI GLOBALI ESTERNE                                            */\
/************************************************************************/\
\
extern Display *display;\
extern Pixmap pixm_noto;\
extern Pixel color_bg_label, color_select_label;\
\
XFontStruct *finfo;\
extern XmFontList fontList;\
\
extern Arg args[];\
extern int nargs;\
\
extern XmString cstring;\
\
extern char file_tempdati[], file_tempvar[];\
\
extern StructVarianti varianti_modello[];\
extern byte num_varianti, num_file_f14;\
\
extern WindowInfoStruct *winfo_list;\
\
/************************************************************************/\
/* VARIABILI GLOBALI                                                    */\
/************************************************************************/\
\
/* intestazione dati geometrici e fisici: */\
\
static TextWidgetPos text_wdg_dati[] =  { {"Name",        0,   100,  8, False },\
                                          {"Value",       110, 110, 10, False },\
                                          {"Data source", 230, 270, 27, True  },\
                                          {"Rev.",        510,  60,  4, True  },\
                                          {"Page",        580,  50,  3, True  },\
                                          {"Date",        640, 100,  8, True  },\
                                          {"Note",        750,  70,  5, True  } };\
\
\
static int num_wdg_dati = sizeof(text_wdg_dati)/sizeof(text_wdg_dati[0]);\
\
\
/* intestazione variabili del blocco nel caso in cui si considera solo il */\
/* file f14.dat del modello */\
\
static TextWidgetPos text_wdg_var[] =  { {"Symbol",      20,  100,  8, False },\
                                         {"Value",       130, 110, 10, False },\
                                         {"Unit",        250,  80,  7, False },\
                                         {"Descr.",      340,  40,  0, False },\
                                         {"Data source", 390, 270, 27, True  },\
                                         {"Rev.",        670,  60,  4, True  },\
                                         {"Page",        740,  50,  3, True  },\
                                         {"Date",        800, 100,  8, True  } };\
\
static int num_wdg_var = sizeof(text_wdg_var)/sizeof(text_wdg_var[0]);\
\
\
/* intestazione variabili del blocco nel caso in cui si considerano piu' */\
/* file f14.dat (varianti del modello) */\
\
static TextWidgetPos text_wdg_var2[] = { {"Symbol",     20, 100,  8, False },\
                                         {"Unit",      130,  80,  7, False },\
                                         {"",          220, 110, 10, False },\
                                         {"",          340, 110, 10, False },\
                                         {"",          460, 110, 10, False },\
                                         {"",          580, 110, 10, False },\
                                         {"",          700, 110, 10, False },\
                                         {"Descr.",    820,  20,  0, False } };\
\
static int num_wdg_var2 = sizeof(text_wdg_var2)/sizeof(text_wdg_var2[0]);
*info_ashell.ispecdecl: /* nota generale del blocco */\
   char *nota_blocco;\
\
/* text-widget per le informazioni aggiuntive */\
   WidgetBlock *widget_blocco;\
\
/* numero variabili o dati geometrici */\
   int num_info;\
\
/* indice del toggle premuto in precedenza */\
   Widget last_toggle;\
\
/* swidget window nota generale del blocco */\
   swidget win_note_block;\
   Boolean open_win_note;\
\
/* note del blocco */\
   HeaderNote *ptr_note;\
\
/* indice ricerca nome variabili */\
   int ind_ricerca;\
\
/* Widget contenitore */\
   Widget wrowcol;
*info_ashell.ispeclist: nota_blocco, widget_blocco, num_info, last_toggle, win_note_block, open_win_note, ptr_note, ind_ricerca, wrowcol
*info_ashell.ispeclist.nota_blocco: "unsigned char", "*%nota_blocco%"
*info_ashell.ispeclist.widget_blocco: "WidgetBlock", "*%widget_blocco%"
*info_ashell.ispeclist.num_info: "int", "%num_info%"
*info_ashell.ispeclist.last_toggle: "Widget", "%last_toggle%"
*info_ashell.ispeclist.win_note_block: "swidget", "%win_note_block%"
*info_ashell.ispeclist.open_win_note: "Boolean", "%open_win_note%"
*info_ashell.ispeclist.ptr_note: "HeaderNote", "*%ptr_note%"
*info_ashell.ispeclist.ind_ricerca: "int", "%ind_ricerca%"
*info_ashell.ispeclist.wrowcol: "Widget", "%wrowcol%"
*info_ashell.funcdecl: swidget create_info_ashell(nome_blocco,descr_blocco,flag_blocco,winfo)\
char *nome_blocco, *descr_blocco;\
char flag_blocco;  /* indica se VARIABILI o DATI_GEOMETRICI */\
WindowInfoStruct *winfo;\

*info_ashell.funcname: create_info_ashell
*info_ashell.funcdef: "swidget", "<create_info_ashell>(%)"
*info_ashell.argdecl: unsigned char *nome_blocco;\
unsigned char *descr_blocco;\
unsigned char flag_blocco;\
WindowInfoStruct *winfo;
*info_ashell.arglist: nome_blocco, descr_blocco, flag_blocco, winfo
*info_ashell.arglist.nome_blocco: "unsigned char", "*%nome_blocco%"
*info_ashell.arglist.descr_blocco: "unsigned char", "*%descr_blocco%"
*info_ashell.arglist.flag_blocco: "unsigned char", "%flag_blocco%"
*info_ashell.arglist.winfo: "WindowInfoStruct", "*%winfo%"
*info_ashell.icode: /* variabili locali */\
   InfoBlock *dati_blocco;\
   int i, j, k, y, num_int, num_dati, num_var_out, num_colonne;\
   TextWidgetPos *text_position;\
   BlockData *bdata;\
   BlockVar *bvar;\
   BlockVarNmod *bvarN;\
   Widget *wtoggle;\
   char stringa[200], *contesto;\
   WidgetBlock *wb;\
   swidget form_descr_e_tipo;\
\
/* inizializzazione puntatore note */\
   ptr_note = NULL;\
   open_win_note = False;\
\
   switch (flag_blocco)\
   {\
      case DATI_GEOMETRICI:\
           text_position = text_wdg_dati;\
           num_int = num_wdg_dati;\
           break;\
\
      case VARIABILI:\
           text_position = text_wdg_var;\
           num_int = num_wdg_var;\
           break;\
\
      case VARIABILI_N_F14:\
           text_position = text_wdg_var2;\
           num_int = num_wdg_var2;\
           break;\
   }
*info_ashell.fcode: /* inizializzazione */\
   nota_blocco = NULL;\
\
   last_toggle = NULL;\
\
   ind_ricerca = 0;\
\
   contesto = UxGetContext(info_ashell);\
\
/* intestazione */\
   switch (flag_blocco)\
   {\
      case DATI_GEOMETRICI:\
         num_colonne = 8;\
         UxPutLabelString(label_nome_blocco, nome_blocco);\
         UxPutLabelString(label_descr_blocco, descr_blocco);\
\
         leggi_record_f14(nome_blocco,&dati_blocco, &num_dati, &ptr_note,\
			  &nota_blocco);\
\
         UxPutTitle(info_ashell, TITOLO_DATI_GEOMETRICI);\
\
         setta_label_int(label_int1, &text_position[0] );\
         setta_label_int(label_int2, &text_position[1] );\
         setta_label_int(label_int3, &text_position[2] );\
         setta_label_int(label_int4, &text_position[3] );\
         setta_label_int(label_int5, &text_position[4] );\
         setta_label_int(label_int6, &text_position[5] );\
         setta_label_int(label_int7, &text_position[6] );\
         UxPutLabelString(label_int_nome,"");\
         UxPutLabelString(label_int_descr,"");\
         break;\
\
      case VARIABILI:\
         num_colonne = 8;\
         UxPutLabelString(label_nome_blocco, nome_blocco);\
         UxPutLabelString(label_descr_blocco, descr_blocco);\
\
         UxPutTitle(info_ashell, TITOLO_VARIABILI);\
\
         leggi_var_f01(nome_blocco,&dati_blocco, &num_dati, &nota_blocco,\
                       flag_blocco);\
\
         setta_label_int(label_int1, &text_position[0] );\
         setta_label_int(label_int2, &text_position[1] );\
         setta_label_int(label_int3, &text_position[2] );\
         setta_label_int(label_int4, &text_position[3] );\
         setta_label_int(label_int5, &text_position[4] );\
         setta_label_int(label_int6, &text_position[5] );\
         setta_label_int(label_int7, &text_position[6] );\
         setta_label_int(label_int8, &text_position[7] );\
         wtoggle = (Widget *) calloc(num_dati, sizeof(Widget));\
         break;\
\
      case VARIABILI_N_F14:\
         num_colonne = 8;\
         UxDestroySwidget(label_nome_blocco);\
         UxDestroySwidget(label_descr_blocco);\
         UxDestroySwidget(pb_note_blocco);\
         UxDestroySwidget(label2);\
         UxDestroySwidget(label3);\
         UxPutSensitive(pb_info_ok, "false");\
         UxPutSensitive(pb_info_apply, "false");\
\
         UxPutTitle(info_ashell, TITOLO_STEADY_STATE_VER);\
\
         leggi_all_var_f14(nome_blocco,&dati_blocco, &num_dati, &num_var_out);\
\
         for ( i = 0, j = 2 ; i < num_varianti ; i++ )\
            if (varianti_modello[i].abilitato)\
               strcpy(text_position[j++].intestazione, \
                      varianti_modello[i].titolo);\
         for ( ; j < num_varianti+2 ; j++ )\
            strcpy(text_position[j].intestazione, "< NONE >");\
\
         setta_label_int(label_int1, &text_position[0] );\
         setta_label_int(label_int2, &text_position[1] );\
         setta_label_int(label_int3, &text_position[2] );\
         setta_label_int(label_int4, &text_position[3] );\
         setta_label_int(label_int5, &text_position[4] );\
         setta_label_int(label_int6, &text_position[5] );\
         setta_label_int(label_int7, &text_position[6] );\
         setta_label_int(label_int8, &text_position[7] );\
         wtoggle = (Widget *) calloc(num_dati, sizeof(Widget));\
         break;\
   }\
\
/* Crea il contenitore dei text e delle label */\
   nargs = 0;\
   XtSetArg(args[nargs], XmNresizePolicy, XmRESIZE_GROW); nargs++;\
   XtSetArg(args[nargs], XmNmarginHeight, 0); nargs++;\
   XtSetArg(args[nargs], XmNmarginWidth, 0); nargs++;\
   wrowcol = XmCreateBulletinBoard(UxGetWidget(scrolledWindow2), "rowcol", \
			       args, nargs);\
\
/* alloca la memoria per i text-widget */\
   widget_blocco = (WidgetBlock *) XtCalloc(num_dati, sizeof(WidgetBlock));\
\
   num_info = 0;\
   for ( i = 0, y = 0 ; i < num_dati ; i++ )\
   {\
       wb = &widget_blocco[num_info];\
\
       switch (dati_blocco[i].flag)\
       {\
          case VARIABILI:\
             bvar = &dati_blocco[i].var;\
\
             if (bvar->noto)\
	        crea_label_pixmap(wrowcol, y+10);\
\
             strcpy(wb->vars.nome,bvar->nome);\
             sprintf(wb->vars.tipo_e_descr,"--%s-- %s",bvar->tipovar,\
						  bvar->descrizione);\
             wb->vars.val_mks[0] = bvar->fval_mks;\
             wb->vars.num_valori = 1;\
             wb->vars.wnome = crea_text(wrowcol,y,bvar->nome, &text_position[0]);\
             wb->vars.valore[0] = crea_text(wrowcol,y,bvar->valore,&text_position[1]);\
             wb->vars.unita = crea_text(wrowcol,y,dim_unita_misura(bvar->nome[0]),\
			           &text_position[2]);\
             wtoggle[num_info] = crea_toggle(wrowcol, y, &text_position[3],\
					     ALTEZZA_TEXT, num_info,contesto);\
             wb->vars.source = crea_text(wrowcol,y,bvar->sorgente,&text_position[4]);\
             wb->vars.rel = crea_text(wrowcol,y,bvar->release,&text_position[5]);\
             wb->vars.pag = crea_text(wrowcol,y,bvar->pagina,&text_position[6]);\
             wb->vars.data = crea_text(wrowcol,y,bvar->data,&text_position[7]);\
             num_info++;\
             y += ALTEZZA_TEXT+5;\
             break;\
\
          case VARIABILI_N_F14:\
             bvarN = &dati_blocco[i].varN;\
\
             if (bvarN->noto)\
                crea_label_pixmap(wrowcol, y+10);\
\
             strcpy(wb->vars.nome,bvarN->nome);\
             sprintf(wb->vars.tipo_e_descr,"%s %s",bvarN->nome_blk,\
					      bvarN->descrizione);\
             wb->vars.num_valori = bvarN->num_valori;\
             for ( k=0 ; k<bvarN->num_valori ; k++)\
                 wb->vars.val_mks[k] = bvarN->fval_mks[k];\
             wb->vars.wnome = crea_labelG(wrowcol,y,bvarN->nome, &text_position[0]);\
             wb->vars.unita = crea_labelG(wrowcol,y,dim_unita_misura(bvarN->nome[0]),\
				          &text_position[1]);\
             wb->vars.valore[0] = crea_labelG(wrowcol,y,bvarN->valori[0],&text_position[2]);\
             wb->vars.valore[1] = crea_labelG(wrowcol,y,bvarN->valori[1],&text_position[3]);\
             wb->vars.valore[2] = crea_labelG(wrowcol,y,bvarN->valori[2],&text_position[4]);\
             wb->vars.valore[3] = crea_labelG(wrowcol,y,bvarN->valori[3],&text_position[5]);\
             wb->vars.valore[4] = crea_labelG(wrowcol,y,bvarN->valori[4],&text_position[6]);\
             wb->vars.num_valori = bvarN->num_valori;\
             wtoggle[num_info] = crea_toggle(wrowcol, y, &text_position[7],\
					     ALTEZZA_TEXT, num_info,contesto);\
             num_info++;\
             y += ALTEZZA_TEXT+5;\
             break;\
\
          case DATI_GEOMETRICI:\
             bdata = &dati_blocco[i].dati;\
\
             wb->data.open_win = False;\
             strcpy(wb->data.nome,bdata->nome);\
             wb->vars.wnome = crea_text(wrowcol,y,bdata->nome,&text_position[0]);\
             crea_text(wrowcol,y,bdata->valore,&text_position[1]);\
             wb->data.source = crea_text(wrowcol,y,bdata->sorgente,&text_position[2]);\
             wb->data.rel = crea_text(wrowcol,y,bdata->release,&text_position[3]);\
             wb->data.pag = crea_text(wrowcol,y,bdata->pagina,&text_position[4]);\
             wb->data.data = crea_text(wrowcol,y,bdata->data,&text_position[5]);\
             wb->data.nota = crea_text(wrowcol,y,bdata->note,&text_position[6]);\
             XtAddCallback(widget_blocco[num_info].data.nota,\
			   XmNvalueChangedCallback,\
			   callback_ins_nota,\
			   UxGetContext(rtrn));\
\
             set_something(wb->data.nota,XmNuserData, num_info);\
             wb->data.pb_nota = crea_pb_note(wrowcol,y,num_info,\
					     contesto, !Empty(bdata->note));\
             num_info++;\
\
             y += ALTEZZA_TEXT+5;\
             break;\
\
          case COMMENTO:\
\
             crea_label(wrowcol,y,dati_blocco[i].comment.commento);\
             y += ALTEZZA_TEXT+5;\
\
             break;\
      }\
   }\
\
   if ( flag_blocco == VARIABILI_N_F14 || flag_blocco == VARIABILI)\
   {\
      XtManageChildren(wtoggle, num_info);\
      free(wtoggle);\
   }\
\
   XtFree(dati_blocco);\
\
   XtManageChild(wrowcol);\
\
   UxPopupInterface(rtrn, no_grab);\
   return(rtrn);
*info_ashell.auxdecl: /*** Widget crea_text(padre, testo, y, text_info)\
 ***   Parametri:\
 ***     Widget padre: padre del widget da creare\
 ***     int y : posizione y\
 ***     char *testo : testo da visualizzare/modificare\
 ***     TextWidgetPos *text_info : struttura che contiene le informazioni\
 ***                                sul text-widget (posizione, editabile ...)\
 ***\
 ***   Descrizione:\
 ***     Crea i text widget utilizzati per visualizzare o modificare le\
 ***     informazioni delle variabili o dei dati geometrici di un blocco\
 ***     (sorgente del dato, release, pagina, ... ).\
 ***/\
Widget crea_text(padre, y, testo, text_info)\
Widget padre;\
int y;\
char *testo;\
TextWidgetPos *text_info;\
{\
   Widget wdg;\
   char *classe;\
\
   if ( text_info->editable )\
      classe = "TextInfoBlock";\
   else\
      classe = "TextInfoReadonly";\
   nargs = 0;\
   XtSetArg (args[nargs],XmNy,y); nargs++;\
   XtSetArg (args[nargs],XmNheight,ALTEZZA_TEXT); nargs++;\
   XtSetArg (args[nargs],XmNleftAttachment,XmATTACH_POSITION); nargs++;\
   XtSetArg (args[nargs],XmNrightAttachment,XmATTACH_POSITION); nargs++;\
   XtSetArg (args[nargs],XmNx,text_info->leftpos); nargs++;\
   XtSetArg (args[nargs],XmNwidth,text_info->rightpos); nargs++;\
   XtSetArg (args[nargs],XmNmaxLength,text_info->num_col);nargs++;\
   XtSetArg (args[nargs],XmNfontList,fontList);nargs++;\
   XtSetArg (args[nargs],XmNvalue,testo);nargs++;\
   XtSetArg (args[nargs],XmNeditable,text_info->editable);nargs++;\
   wdg = (Widget) XmCreateTextField(padre,classe,args,nargs);\
   XtManageChild (wdg);\
\
   return(wdg);\
}\
/*** Widget crea_labelG(padre, testo, y, text_info)\
 ***   Parametri:\
 ***     Widget padre: padre del widget da creare\
 ***     int y : posizione y\
 ***     char *testo : testo da visualizzare/modificare\
 ***     TextWidgetPos *text_info : struttura che contiene le informazioni\
 ***                                sul text-widget (posizione, editabile ...)\
 ***\
 ***   Descrizione:\
 ***     Crea i text widget utilizzati per visualizzare o modificare le\
 ***     informazioni delle variabili o dei dati geometrici di un blocco\
 ***     (sorgente del dato, release, pagina, ... ).\
 ***/\
Widget crea_labelG(padre, y, testo, text_info)\
Widget padre;\
int y;\
char *testo;\
TextWidgetPos *text_info;\
{\
   Widget wdg;\
\
   cstring = CREATE_CSTRING(testo);\
   nargs = 0;\
   XtSetArg (args[nargs],XmNy,y); nargs++;\
   XtSetArg (args[nargs],XmNheight,ALTEZZA_TEXT); nargs++;\
   XtSetArg (args[nargs],XmNx,text_info->leftpos); nargs++;\
   XtSetArg (args[nargs],XmNwidth,text_info->rightpos); nargs++;\
   XtSetArg (args[nargs],XmNfontList,fontList);nargs++;\
   XtSetArg (args[nargs],XmNlabelString,cstring);nargs++;\
   XtSetArg (args[nargs],XmNalignment,XmALIGNMENT_BEGINNING);nargs++;\
   XtSetArg (args[nargs],XmNrecomputeSize,False);nargs++;\
   wdg = (Widget) XmCreateLabel(padre,"TextInfoReadonly",args,nargs);\
   XtManageChild (wdg);\
   XmStringFree(cstring);\
   return(wdg);\
}\
\
/*** Widget crea_toggle(padre, y, text_info, indice)\
 ***   Parametri:\
 ***     Widget padre: padre del widget da creare\
 ***     int y : posizione y\
 ***     TextWidgetPos *text_info : struttura che contiene le informazioni\
 ***                                sul text-widget (posizione, editabile ...)\
 ***     int indice : indice array widget_blocco[];\
 ***\
 ***   Descrizione:\
 ***     Crea i toggle-button utilizzati per visualizzare la descrizione\
 ***     di una variabile.\
 ***/\
Widget crea_toggle(padre, y, text_info, h, indice, contesto)\
Widget padre;\
int y;\
TextWidgetPos *text_info;\
int h;\
int indice;\
char *contesto;\
{\
   Widget wdg;\
   swidget swdg;\
\
   nargs = 0;\
   XtSetArg (args[nargs],XmNy,y); nargs++;\
   XtSetArg (args[nargs],XmNheight,h); nargs++;\
   XtSetArg (args[nargs],XmNleftAttachment,XmATTACH_POSITION); nargs++;\
   XtSetArg (args[nargs],XmNrightAttachment,XmATTACH_POSITION); nargs++;\
   XtSetArg (args[nargs],XmNx,text_info->leftpos); nargs++;\
   XtSetArg (args[nargs],XmNwidth,text_info->rightpos); nargs++;\
   XtSetArg (args[nargs], XmNlabelString, CREATE_CSTRING("")); nargs++;\
   XtSetArg (args[nargs], XmNuserData, indice); nargs++;\
   wdg = XmCreateToggleButton(padre,"TextInfoBlock",args,nargs);\
   XtAddCallback(wdg,XmNarmCallback,callback_toggle,contesto);\
   XtAddCallback(wdg,XmNdisarmCallback,setta_toggle,NULL);\
\
   return(wdg);\
}\
\
/*** void setta_label_int(swdg, info_pos)\
 ***   Parametri:\
 ***     swidget swdg : shadow widget;\
 ***     TextWidgetPos *info_pos : informazioni sulle position.\
 ***\
 ***   Descrizione:\
 ***     Setta le position delle label di intestazione.\
 ***/\
void setta_label_int(swdg, info_pos)\
swidget swdg;\
TextWidgetPos *info_pos;\
{\
   cstring = CREATE_CSTRING(info_pos->intestazione);\
   nargs = 0;\
   XtSetArg(args[nargs], XmNx, info_pos->leftpos); nargs++;\
   XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;\
   XtSetValues(UxGetWidget(swdg), args, nargs);\
   XmStringFree(cstring);\
}\
\
/*** int crea_label(padre, testo, y)\
 ***   Parametri:\
 ***     Widget padre: padre del widget da creare\
 ***     int y : posizione y\
 ***     char *testo : testo da visualizzare\
 ***\
 ***   Descrizione:\
 ***     Crea la label di commento. Ritorna l'altezza della label\
 ***/\
int crea_label(padre, y, testo)\
Widget padre;\
int y;\
char *testo;\
{\
   Widget wdg;\
   Dimension h;\
   XmString cstring;\
\
   cstring = CREATE_CSTRING(testo);\
\
   nargs = 0;\
   XtSetArg(args[nargs], XmNx, 0); nargs++;\
   XtSetArg(args[nargs], XmNy, y); nargs++;\
   XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;\
   XtSetArg(args[nargs], XmNfontList, fontList); nargs++;\
   XtSetArg(args[nargs], XmNrecomputeSize, False); nargs++;\
   XtSetArg(args[nargs], XmNheight, ALTEZZA_TEXT); nargs++;\
   XtSetArg(args[nargs], XmNalignment, XmALIGNMENT_BEGINNING); nargs++;\
   wdg = XmCreateLabel(padre,"Commento",args,nargs);\
   XtManageChild(wdg);\
\
   XmStringFree(cstring);\
\
   get_something(wdg, XmNheight, &h);\
\
   return((int) h);\
}\
\
/*** int crea_label_pixmap(padre, y)\
 ***   Parametri:\
 ***     Widget padre: padre del widget da creare\
 ***     int y : posizione y\
 ***\
 ***   Descrizione:\
 ***     Crea la label-pixmap.\
 ***/\
int crea_label_pixmap(padre, y)\
Widget padre;\
int y;\
{\
   Widget wdg;\
\
   nargs = 0;\
   XtSetArg(args[nargs], XmNx, 0); nargs++;\
   XtSetArg(args[nargs], XmNy, y); nargs++;\
   XtSetArg(args[nargs], XmNlabelPixmap, pixm_noto); nargs++;\
   XtSetArg(args[nargs], XmNlabelType, XmPIXMAP); nargs++;\
   XtSetArg(args[nargs], XmNrecomputeSize, True); nargs++;\
   XtSetArg(args[nargs], XmNalignment, XmALIGNMENT_BEGINNING); nargs++;\
   wdg = XmCreateLabel(padre,"LabelPixmap",args,nargs);\
   XtManageChild(wdg);\
\
   return(0);\
}\
\
/*** Widget crea_pb_note(padre, y, indice, contesto, sensitivo)\
 ***   Parametri:\
 ***     Widget padre: padre del widget da creare.\
 ***     int y : posizione y.\
 ***     int indice : indice array widget_blocco[].\
 ***     char *contesto : contesto della window.\
 ***     Boolean sensitivo : indica se il push-button deve essere attivo.\
 ***\
 ***   Descrizione:\
 ***     Crea il push-button NOTE di un dato geometrico\
 ***/\
Widget crea_pb_note(padre, y, indice, contesto, sensitivo)\
Widget padre;\
int y;\
int indice;\
char *contesto;\
Boolean sensitivo;\
{\
   Widget wdg;\
   XmString cstring;\
\
   cstring = CREATE_CSTRING("N");\
\
   nargs = 0;\
   XtSetArg(args[nargs], XmNx, 830); nargs++;\
   XtSetArg(args[nargs], XmNwidth, 20); nargs++;\
   XtSetArg(args[nargs], XmNy, y+5); nargs++;\
   XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;\
   XtSetArg(args[nargs], XmNrecomputeSize, True); nargs++;\
   XtSetArg(args[nargs], XmNsensitive, sensitivo); nargs++;\
   XtSetArg(args[nargs], XmNuserData, indice); nargs++;\
\
   wdg = XmCreatePushButton(padre,"NoteDatoGeometrico",args,nargs);\
   XtAddCallback(wdg,XmNactivateCallback,callback_note,contesto);\
   XtManageChild(wdg);\
\
   XmStringFree(cstring);\
\
   return(wdg);\
}\
\
/*** void set_label(wdg, stringa)\
 ***    Parametri:\
 ***       Widget wdg: label \
 ***       char *stringa: stringa\
 ***\
 ***    Descrizione:\
 ***       Assegna una stringa alla label wdg\
 ***/\
void set_label(wdg, stringa)\
Widget wdg;\
char *stringa;\
{\
   XmString cstring;\
\
   cstring = CREATE_CSTRING(stringa);\
   set_something(wdg, XmNlabelString, cstring);\
   XmStringFree(cstring);\
}\
\
/*** void callback_note(w, contesto, call_data)\
 ***   Parametri:\
 ***      Widget w: widget\
 ***      char *contesto: contesto\
 ***      XmAnyCallbackStruct *call_data: non utilizzato.\
 ***\
 ***   Descrizione:\
 ***      Callback dei push-button delle note dei dati geometrici.\
 ***/\
void callback_note(w, contesto, call_data)\
Widget w;\
char *contesto;\
XmAnyCallbackStruct *call_data;\
{\
   int ind;\
   char *str;\
   HeaderNote *p_nota;\
#ifndef DESIGN_TIME\
   _UxCinfo_ashell *UxSaveCtx, *UxContext;\
   WidgetBlock *wb;\
\
   UxSaveCtx = UxInfo_ashellContext;\
   UxInfo_ashellContext = UxContext = (_UxCinfo_ashell *) contesto;\
\
   get_something(w, XmNuserData, &ind);\
\
   wb = &widget_blocco[ind];\
\
   if (!wb->data.open_win)\
   {\
      str = XmTextGetString(wb->data.nota);\
      p_nota = cerca_testo(ptr_note, str);\
      if (p_nota == NULL)\
         p_nota = appendi_lista(&ptr_note, str);\
\
      wb->data.win_note = create_window_notes(&p_nota->testo, nome_blocco, str,\
					 &wb->data.open_win);\
      free(str);\
   }\
\
   UxInfo_ashellContext = UxSaveCtx;\
#endif\
}\
\
/*** void callback_ins_nota(w, contesto, call_data)\
 ***   Parametri:\
 ***      Widget w: widget\
 ***      char *contesto: contesto\
 ***      XmAnyCallbackStruct *call_data: non utilizzato.\
 ***\
 ***   Descrizione:\
 ***      Questa callback attiva i push-button delle note se l'utente ha\
 ***      inserito qualcosa nel text delle note.\
 ***/\
void callback_ins_nota(w, contesto, call_data)\
Widget w;\
char *contesto;\
XmAnyCallbackStruct *call_data;\
{\
   int ind;\
   char *str;\
#ifndef DESIGN_TIME\
   _UxCinfo_ashell *UxSaveCtx, *UxContext;\
   WidgetBlock *wb;\
\
   UxSaveCtx = UxInfo_ashellContext;\
   UxInfo_ashellContext = UxContext = (_UxCinfo_ashell *) contesto;\
\
   get_something(w, XmNuserData, &ind);\
\
   wb = &widget_blocco[ind];\
\
   str = XmTextGetString(w);\
   if (strlen(str))\
      set_something(wb->data.pb_nota, XmNsensitive, True);\
   else\
      set_something(wb->data.pb_nota, XmNsensitive, False);\
   XtFree(str);\
\
   UxInfo_ashellContext = UxSaveCtx;\
#endif\
}\
\
/*** void callback_toggle(w, contesto, tg_struct)\
 ***   Parametri:\
 ***      Widget w: widget\
 ***      char *contesto: contesto\
 ***      XmToggleButtonCallbackStruct *tg_struct: non utilizzato.\
 ***\
 ***   Descrizione:\
 ***      Visualizzazione della descrizione della variabile selezionata con\
 ***      il toggle-button.\
 ***/\
void callback_toggle(w, contesto, tg_struct)\
Widget w;\
char *contesto;\
XmToggleButtonCallbackStruct *tg_struct;\
{\
   int ind;\
#ifndef DESIGN_TIME\
   _UxCinfo_ashell *UxSaveCtx, *UxContext;\
   UxSaveCtx = UxInfo_ashellContext;\
   UxInfo_ashellContext = UxContext = (_UxCinfo_ashell *) contesto;\
\
   get_something(w, XmNuserData, &ind);\
\
   if (last_toggle != w)\
   {\
      if (last_toggle != NULL)\
         XmToggleButtonSetState(last_toggle, False, False);\
      last_toggle = w;\
      UxPutLabelString(label_nome_var, widget_blocco[ind].vars.nome);\
      UxPutLabelString(label_tipo_e_descr, widget_blocco[ind].vars.tipo_e_descr);\
   }\
\
   tg_struct->set = True;\
\
   UxInfo_ashellContext = UxSaveCtx;\
#endif\
}\
\
/*** void setta_toggle(w, client_data, tg_struct)\
 ***   Parametri:\
 ***      Widget w: widget\
 ***      XtPointer client_data: non utilizzato.\
 ***      XmToggleButtonCallbackStruct *tg_struct: struttura toggle-button.\
 ***\
 ***   Descrizione:\
 ***     Il toggle button rimane settato.\
 ***/\
void setta_toggle(w, client_data, tg_struct)\
Widget w;\
XtPointer client_data;\
XmToggleButtonCallbackStruct *tg_struct;\
{\
   XmToggleButtonSetState(w, True, False);\
}\
\
/*** int salva_info_blocco(chiudi)\
 ***   Parametri:\
 ***      Boolean chiudi : indica se si deve chiudere la window oppure no\
 ***\
 ***   Descrizione:\
 ***      Salva le informazioni del blocco nel file temporaneo.\
 ***      N.B. : SETTARE IL CONTEXT CORRETTO PRIMA DI CHIAMARE QUESTA FUNZIONE!\
 ***/\
int salva_info_blocco( chiudi )\
Boolean chiudi;\
{\
   FILE *fp_temp, *fp_app;\
   char file_app[256], *file_temp;\
   char int_blocco[30], buffer[91];\
   char *nome, *sorg, *rel, *pag, *data, *nota;\
   int i;\
   HeaderNote *p_nota;\
\
#ifndef DESIGN_TIME\
   if (flag_blocco != VARIABILI_N_F14)\
   {\
      if (flag_blocco == DATI_GEOMETRICI)\
         file_temp = file_tempdati;\
      else\
         file_temp = file_tempvar;\
\
      tmpnam(file_app);\
\
      if ((fp_app = fopen(file_app,"w+")) == NULL)\
         return(1);\
\
      if ((fp_temp = fopen(file_temp,"r")) == NULL)\
         return(1);\
\
      sprintf(int_blocco,"*LG*DATI DEL BLOCCO %s\n",nome_blocco);\
\
      while ( fgets(buffer,90,fp_temp) != NULL && \
              strncmp(buffer,int_blocco,strlen(int_blocco)-1) )\
          fputs(buffer, fp_app);\
\
      fputs(int_blocco, fp_app);\
\
   /* copia le nuove informazioni */\
      for ( i=0 ; i<num_info ; i++)\
      {\
\
         if (flag_blocco == DATI_GEOMETRICI)\
         {\
            nome = widget_blocco[i].data.nome;\
            sorg = XmTextFieldGetString(widget_blocco[i].data.source);\
            rel = XmTextFieldGetString(widget_blocco[i].data.rel);\
            pag = XmTextFieldGetString(widget_blocco[i].data.pag);\
            data = XmTextFieldGetString(widget_blocco[i].data.data);\
            nota = XmTextFieldGetString(widget_blocco[i].data.nota);\
         }\
         else\
         {\
            nome = widget_blocco[i].vars.nome;\
            sorg = XmTextFieldGetString(widget_blocco[i].vars.source);\
            rel = XmTextFieldGetString(widget_blocco[i].vars.rel);\
            pag = XmTextFieldGetString(widget_blocco[i].vars.pag);\
            data = XmTextFieldGetString(widget_blocco[i].vars.data);\
            nota = "";\
         }\
\
         fprintf(fp_app,"%-8.8s|%-27.27s|%-4.4s|%-3.3s|%-8.8s|%-5.5s\n",\
                         nome, sorg, rel, pag, data, nota);\
\
         XtFree(sorg);\
         XtFree(rel);\
         XtFree(pag);\
         XtFree(data);\
         if (flag_blocco == DATI_GEOMETRICI)\
            XtFree(nota);\
      }\
\
   /* note generali del blocco */\
      if (nota_blocco != NULL)\
      {\
         fprintf(fp_app, "*LG*NOTE GENERALI DEL BLOCCO %s\n", nome_blocco);\
         fprintf(fp_app, "%s\n",nota_blocco);\
      }\
\
   /* note dei singoli dati geometrici */\
      if (flag_blocco == DATI_GEOMETRICI)\
         for ( p_nota = ptr_note ; p_nota != NULL ; p_nota = p_nota->next_header )\
         {\
            for ( i=0 ; i<num_info ; i++ )\
            {\
                nota = XmTextFieldGetString(widget_blocco[i].data.nota);\
                if ( !strcmp(nota, p_nota->nota) )\
                   break;\
                XtFree(nota);\
            }   \
         \
            if ( i<num_info )\
            {\
               fprintf(fp_app, "*LG*NOTE DEL BLOCCO %s NOTA %s\n",\
	 	               nome_blocco, p_nota->nota);\
               fprintf(fp_app, "%s\n", p_nota->testo);\
               XtFree(nota);\
            }\
         }\
\
   /* copia le informazioni relative ai blocchi rimanenti */\
      if ( !feof(fp_temp) )\
      {\
         while ( fgets(buffer, 90, fp_temp) != NULL && \
                 strncmp(buffer, "*LG*DATI DEL BLOCCO ", 19));\
         if ( !feof(fp_temp) )\
         {\
            fputs(buffer, fp_app);\
            while ( fgets(buffer,90,fp_temp) != NULL )\
               fputs(buffer, fp_app);\
         }\
      }\
\
      fclose(fp_app);\
      fclose(fp_temp);\
\
      copia_file(file_app, file_temp);\
\
#ifdef VMS\
      remove(file_app);\
#else\
      unlink(file_app);\
#endif\
   }\
#endif\
\
   if (chiudi)\
      chiudi_info_ashell();\
}\
\
/*** void aggiorna_unita_misura()\
 ***\
 ***   Descrizione: \
 ***      aggiorna i valori delle variabili delle window aperte \
 ***      secondo le unita di misura stabilite.\
 ***/\
void aggiorna_unita_misura()\
{\
   WindowInfoStruct *win_info;\
   int i, j;\
   char strval[20];\
\
#ifndef DESIGN_TIME\
   _UxCinfo_ashell *UxSaveCtx, *UxContext;\
   UxSaveCtx = UxInfo_ashellContext;\
\
   for ( win_info = winfo_list ; win_info != NULL ; win_info = win_info->next )\
   {\
       UxInfo_ashellContext = UxContext = (_UxCinfo_ashell *) UxGetContext(win_info->swindow);\
\
       for ( i=0 ; i<num_info ; i++ )\
       {\
          WidgetBlock *wb;\
          double fval;\
\
          wb = widget_blocco+i;\
\
          if (win_info->flag == VARIABILI)\
             XmTextSetString(wb->vars.unita, dim_unita_misura(wb->vars.nome[0]));\
          else\
             set_label(wb->vars.unita, dim_unita_misura(wb->vars.nome[0]));\
\
          for ( j=0 ; j<wb->vars.num_valori ; j++ )\
          {\
              fval = converti_val( *wb->vars.nome, wb->vars.val_mks[j] );\
              sprintf( strval, "%10.4e", fval);\
              if (win_info->flag == VARIABILI)\
                 XmTextSetString( wb->vars.valore[j], strval );\
              else\
                 set_label( wb->vars.valore[j], strval );\
          }\
       }\
   }\
\
   UxInfo_ashellContext = UxSaveCtx;\
#endif\
}\
\
/*** void find_var_name(verso)\
 ***    Parametri:\
 ***       byte verso : indica il verso di ricerca ( 0: GIU', 1:SU' )\
 ***\
 ***    Descrizione:\
 ***       ricerca la variabile nella lista. Se la variabile viene trovata\
 ***       il nome della variabile viene evidenziato.\
 ***/\
void find_var_name(verso)\
byte verso;\
{\
   char *nome_da_trovare, *nome;\
   int i, step, valore, slider_size, len_nome, minimum, maximum;\
   Dimension bb_height;\
   Widget vscrollbar;\
\
#ifndef DESIGN_TIME\
   nome_da_trovare = XmTextGetString(UxGetWidget(text_find_nome));\
   len_nome = strlen(nome_da_trovare);\
\
   step = (verso) ? 1 : -1;\
\
   for ( i = ind_ricerca+step ; i < num_info && i >= 0 ; i += step )\
   {\
       if (flag_blocco == DATI_GEOMETRICI)\
          nome = widget_blocco[i].data.nome;\
       else\
          nome = widget_blocco[i].vars.nome;\
\
       if ( Utstrstr(nome, nome_da_trovare) != NULL )\
          break;\
   }\
\
   if ( i >= 0 && i < num_info )\
   {\
      get_something( UxGetWidget(scrolledWindow2), XmNverticalScrollBar,\
		     &vscrollbar );\
      get_something( wrowcol, XmNheight, &bb_height );\
\
      nargs = 0;\
      XtSetArg( args[nargs], XmNsliderSize, &slider_size ); nargs++;\
      XtSetArg( args[nargs], XmNminimum, &minimum ); nargs++;\
      XtSetArg( args[nargs], XmNmaximum, &maximum ); nargs++;\
      XtGetValues( vscrollbar, args, nargs );\
\
      valore = (i*(ALTEZZA_TEXT+5)*(maximum-minimum) )/bb_height+minimum;\
\
      if ( valore > (maximum - slider_size) )\
         valore = maximum - slider_size;\
\
      XmScrollBarSetValues( vscrollbar, valore, slider_size, 0, 0, True );\
\
      switch (flag_blocco)\
      {\
           case DATI_GEOMETRICI:\
                XmTextFieldSetSelection(widget_blocco[i].data.wnome,0,8,CurrentTime);\
                break;\
\
           case VARIABILI:\
                XmTextFieldSetSelection(widget_blocco[i].vars.wnome,0,8,CurrentTime);\
                break;\
\
           case VARIABILI_N_F14:\
		set_something(widget_blocco[ind_ricerca].vars.wnome, XmNbackground, \
                              color_bg_label);\
		set_something(widget_blocco[i].vars.wnome, XmNbackground, color_select_label);\
                break;\
      }\
\
      ind_ricerca = i;\
\
   }\
\
   XtFree(nome_da_trovare);\
#endif\
}\
\
/*** void chiudi_info_ashell()\
 ***\
 ***   Descrizione: \
 ***      chiude la window delle informazioni del blocco e dealloca la memoria\
 ***      utilizzata. N.B. : SETTARE IL CONTEXT CORRETTO PRIMA DI CHIAMARE \
 ***      QUESTA FUNZIONE!\
 ***/\
void chiudi_info_ashell()\
{\
   int i;\
   WindowInfoStruct *winfoprec = NULL, *winfotmp;\
\
#ifndef DESIGN_TIME\
   free(nome_blocco);\
   free(descr_blocco);\
\
   if (open_win_note)\
      UxDestroySwidget(win_note_block);\
\
   if (flag_blocco == DATI_GEOMETRICI)\
   {\
      for ( i=0 ; i<num_info ; i++)\
      {\
         if (widget_blocco[i].data.open_win)\
            UxDestroySwidget(widget_blocco[i].data.win_note);\
      }\
   }\
\
   cancella_testi(&ptr_note);\
\
   if (winfo != NULL)\
   {\
      for ( winfotmp = winfo_list ; winfotmp != winfo && winfotmp != NULL ; \
            winfoprec = winfotmp, winfotmp = winfotmp->next );\
\
      if (winfotmp != NULL)\
      {\
         if (winfoprec != NULL)\
            winfoprec->next = winfotmp->next;\
         else\
            winfo_list = NULL;\
         free(winfo);\
      }\
   }\
\
   XtFree(widget_blocco);\
   UxDestroySwidget(info_ashell);\
#endif\
}
*info_ashell.name: info_ashell
*info_ashell.x: 200
*info_ashell.y: 150
*info_ashell.width: 940
*info_ashell.height: 410
*info_ashell.defaultFontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"
*info_ashell.background: "#4f9f9f"

*form1.class: form
*form1.parent: info_ashell
*form1.static: true
*form1.name: form1
*form1.resizePolicy: "resize_none"
*form1.unitType: "pixels"
*form1.x: 170
*form1.y: 110
*form1.width: 460
*form1.height: 190
*form1.background: "#4f9f9f"

*pb_note_blocco.class: pushButton
*pb_note_blocco.parent: form1
*pb_note_blocco.static: true
*pb_note_blocco.name: pb_note_blocco
*pb_note_blocco.x: 10
*pb_note_blocco.y: 10
*pb_note_blocco.width: 70
*pb_note_blocco.height: 30
*pb_note_blocco.foreground: "Green"
*pb_note_blocco.labelString: "Note..."
*pb_note_blocco.background: "#4f9f9f"
*pb_note_blocco.topAttachment: "attach_form"
*pb_note_blocco.topOffset: 10
*pb_note_blocco.activateCallback: {\
#ifndef DESIGN_TIME\
if (!open_win_note)\
   win_note_block = create_window_notes(&nota_blocco, nome_blocco, NULL,\
					&open_win_note );\
#endif\
}

*label2.class: label
*label2.parent: form1
*label2.static: true
*label2.name: label2
*label2.x: 100
*label2.y: 10
*label2.width: 90
*label2.height: 20
*label2.labelString: "Block name:"
*label2.alignment: "alignment_beginning"
*label2.leftAttachment: "attach_widget"
*label2.leftOffset: 20
*label2.leftWidget: "pb_note_blocco"
*label2.background: "#4f9f9f"
*label2.topAttachment: "attach_form"
*label2.topOffset: 15
*label2.rightAttachment: "attach_none"

*label_nome_blocco.class: label
*label_nome_blocco.parent: form1
*label_nome_blocco.static: true
*label_nome_blocco.name: label_nome_blocco
*label_nome_blocco.x: 200
*label_nome_blocco.y: 10
*label_nome_blocco.width: 110
*label_nome_blocco.height: 20
*label_nome_blocco.alignment: "alignment_beginning"
*label_nome_blocco.labelString: ""
*label_nome_blocco.leftAttachment: "attach_widget"
*label_nome_blocco.leftOffset: 10
*label_nome_blocco.leftWidget: "label2"
*label_nome_blocco.background: "#4f9f9f"
*label_nome_blocco.topAttachment: "attach_form"
*label_nome_blocco.topOffset: 15
*label_nome_blocco.rightAttachment: "attach_none"

*label3.class: label
*label3.parent: form1
*label3.static: true
*label3.name: label3
*label3.x: 325
*label3.y: 10
*label3.width: 100
*label3.height: 20
*label3.alignment: "alignment_beginning"
*label3.labelString: "Description:"
*label3.leftAttachment: "attach_widget"
*label3.leftOffset: 15
*label3.leftWidget: "label_nome_blocco"
*label3.background: "#4f9f9f"
*label3.topAttachment: "attach_form"
*label3.topOffset: 15
*label3.rightAttachment: "attach_none"

*label_descr_blocco.class: label
*label_descr_blocco.parent: form1
*label_descr_blocco.static: true
*label_descr_blocco.name: label_descr_blocco
*label_descr_blocco.x: 435
*label_descr_blocco.y: 10
*label_descr_blocco.width: 400
*label_descr_blocco.height: 20
*label_descr_blocco.alignment: "alignment_beginning"
*label_descr_blocco.labelString: ""
*label_descr_blocco.leftAttachment: "attach_widget"
*label_descr_blocco.leftOffset: 10
*label_descr_blocco.leftWidget: "label3"
*label_descr_blocco.rightAttachment: "attach_form"
*label_descr_blocco.rightOffset: 5
*label_descr_blocco.background: "#4f9f9f"
*label_descr_blocco.topAttachment: "attach_form"
*label_descr_blocco.topOffset: 15

*pb_info_ok.class: pushButton
*pb_info_ok.parent: form1
*pb_info_ok.static: true
*pb_info_ok.name: pb_info_ok
*pb_info_ok.x: 10
*pb_info_ok.y: 370
*pb_info_ok.width: 242
*pb_info_ok.height: 30
*pb_info_ok.labelString: "Ok"
*pb_info_ok.leftAttachment: "attach_form"
*pb_info_ok.leftOffset: 10
*pb_info_ok.rightAttachment: "attach_position"
*pb_info_ok.rightPosition: 30
*pb_info_ok.topAttachment: "attach_none"
*pb_info_ok.topOffset: 0
*pb_info_ok.bottomAttachment: "attach_form"
*pb_info_ok.bottomOffset: 10
*pb_info_ok.background: "#4f9f9f"
*pb_info_ok.activateCallback: {\
salva_info_blocco(True);\
}

*pb_info_apply.class: pushButton
*pb_info_apply.parent: form1
*pb_info_apply.static: true
*pb_info_apply.name: pb_info_apply
*pb_info_apply.x: 302
*pb_info_apply.y: 370
*pb_info_apply.width: 236
*pb_info_apply.height: 30
*pb_info_apply.labelString: "Apply"
*pb_info_apply.bottomAttachment: "attach_form"
*pb_info_apply.bottomOffset: 10
*pb_info_apply.leftAttachment: "attach_position"
*pb_info_apply.leftOffset: 0
*pb_info_apply.leftPosition: 36
*pb_info_apply.rightAttachment: "attach_position"
*pb_info_apply.rightPosition: 64
*pb_info_apply.topAttachment: "attach_none"
*pb_info_apply.topOffset: 0
*pb_info_apply.background: "#4f9f9f"
*pb_info_apply.activateCallback: {\
salva_info_blocco(False);\
}

*pb_info_cancel.class: pushButton
*pb_info_cancel.parent: form1
*pb_info_cancel.static: true
*pb_info_cancel.name: pb_info_cancel
*pb_info_cancel.x: 588
*pb_info_cancel.y: 370
*pb_info_cancel.width: 242
*pb_info_cancel.height: 30
*pb_info_cancel.labelString: "Cancel"
*pb_info_cancel.bottomAttachment: "attach_form"
*pb_info_cancel.bottomOffset: 10
*pb_info_cancel.leftAttachment: "attach_position"
*pb_info_cancel.leftOffset: 0
*pb_info_cancel.leftPosition: 70
*pb_info_cancel.rightAttachment: "attach_form"
*pb_info_cancel.rightOffset: 10
*pb_info_cancel.topAttachment: "attach_none"
*pb_info_cancel.topOffset: 0
*pb_info_cancel.activateCallback: {\
chiudi_info_ashell();\
\
}
*pb_info_cancel.background: "#4f9f9f"
*pb_info_cancel.bottomPosition: 0

*separatorGadget1.class: separatorGadget
*separatorGadget1.parent: form1
*separatorGadget1.static: true
*separatorGadget1.name: separatorGadget1
*separatorGadget1.x: 10
*separatorGadget1.y: 40
*separatorGadget1.width: 820
*separatorGadget1.height: 10
*separatorGadget1.leftAttachment: "attach_form"
*separatorGadget1.leftOffset: 10
*separatorGadget1.rightAttachment: "attach_form"
*separatorGadget1.rightOffset: 10
*separatorGadget1.topAttachment: "attach_widget"
*separatorGadget1.topOffset: 10
*separatorGadget1.topWidget: "label_nome_blocco"

*separatorGadget3.class: separatorGadget
*separatorGadget3.parent: form1
*separatorGadget3.static: true
*separatorGadget3.name: separatorGadget3
*separatorGadget3.x: 10
*separatorGadget3.y: 350
*separatorGadget3.width: 820
*separatorGadget3.height: 10
*separatorGadget3.bottomAttachment: "attach_widget"
*separatorGadget3.bottomOffset: 5
*separatorGadget3.bottomWidget: "pb_info_cancel"
*separatorGadget3.leftAttachment: "attach_form"
*separatorGadget3.leftOffset: 10
*separatorGadget3.rightAttachment: "attach_form"
*separatorGadget3.rightOffset: 10
*separatorGadget3.topAttachment: "attach_none"

*bulletinBoard1.class: bulletinBoard
*bulletinBoard1.parent: form1
*bulletinBoard1.static: true
*bulletinBoard1.name: bulletinBoard1
*bulletinBoard1.resizePolicy: "resize_any"
*bulletinBoard1.x: 10
*bulletinBoard1.y: 130
*bulletinBoard1.width: 940
*bulletinBoard1.height: 30
*bulletinBoard1.leftAttachment: "attach_form"
*bulletinBoard1.leftOffset: 10
*bulletinBoard1.rightAttachment: "attach_form"
*bulletinBoard1.rightOffset: 10
*bulletinBoard1.topAttachment: "attach_widget"
*bulletinBoard1.topOffset: 10
*bulletinBoard1.topWidget: "separatorGadget1"
*bulletinBoard1.background: "#4f9f9f"

*label_int1.class: label
*label_int1.parent: bulletinBoard1
*label_int1.static: true
*label_int1.name: label_int1
*label_int1.x: 10
*label_int1.y: 0
*label_int1.width: 60
*label_int1.height: 30
*label_int1.alignment: "alignment_beginning"
*label_int1.labelString: ""
*label_int1.background: "#4f9f9f"
*label_int1.foreground: "#e8b500"

*label_int2.class: label
*label_int2.parent: bulletinBoard1
*label_int2.static: true
*label_int2.name: label_int2
*label_int2.x: 90
*label_int2.y: 0
*label_int2.width: 60
*label_int2.height: 30
*label_int2.alignment: "alignment_beginning"
*label_int2.labelString: ""
*label_int2.background: "#4f9f9f"
*label_int2.foreground: "#e8b500"

*label_int3.class: label
*label_int3.parent: bulletinBoard1
*label_int3.static: true
*label_int3.name: label_int3
*label_int3.x: 160
*label_int3.y: 0
*label_int3.width: 60
*label_int3.height: 30
*label_int3.alignment: "alignment_beginning"
*label_int3.labelString: ""
*label_int3.background: "#4f9f9f"
*label_int3.foreground: "#e8b500"

*label_int4.class: label
*label_int4.parent: bulletinBoard1
*label_int4.static: true
*label_int4.name: label_int4
*label_int4.x: 230
*label_int4.y: 0
*label_int4.width: 60
*label_int4.height: 30
*label_int4.alignment: "alignment_beginning"
*label_int4.labelString: ""
*label_int4.background: "#4f9f9f"
*label_int4.foreground: "#e8b500"

*label_int5.class: label
*label_int5.parent: bulletinBoard1
*label_int5.static: true
*label_int5.name: label_int5
*label_int5.x: 300
*label_int5.y: 0
*label_int5.width: 60
*label_int5.height: 20
*label_int5.alignment: "alignment_beginning"
*label_int5.labelString: ""
*label_int5.background: "#4f9f9f"
*label_int5.foreground: "#e8b500"

*label_int6.class: label
*label_int6.parent: bulletinBoard1
*label_int6.static: true
*label_int6.name: label_int6
*label_int6.x: 390
*label_int6.y: 0
*label_int6.width: 70
*label_int6.height: 30
*label_int6.alignment: "alignment_beginning"
*label_int6.labelString: ""
*label_int6.background: "#4f9f9f"
*label_int6.foreground: "#e8b500"

*label_int7.class: label
*label_int7.parent: bulletinBoard1
*label_int7.static: true
*label_int7.name: label_int7
*label_int7.x: 480
*label_int7.y: 0
*label_int7.width: 70
*label_int7.height: 30
*label_int7.labelString: ""
*label_int7.alignment: "alignment_beginning"
*label_int7.background: "#4f9f9f"
*label_int7.foreground: "#e8b500"

*label_int8.class: label
*label_int8.parent: bulletinBoard1
*label_int8.static: true
*label_int8.name: label_int8
*label_int8.x: 580
*label_int8.y: 0
*label_int8.width: 80
*label_int8.height: 30
*label_int8.alignment: "alignment_beginning"
*label_int8.labelString: ""
*label_int8.background: "#4f9f9f"
*label_int8.foreground: "#e8b500"

*labelGadget12.class: labelGadget
*labelGadget12.parent: form1
*labelGadget12.static: true
*labelGadget12.name: labelGadget12
*labelGadget12.x: 10
*labelGadget12.y: 320
*labelGadget12.width: 50
*labelGadget12.height: 34
*labelGadget12.bottomAttachment: "attach_widget"
*labelGadget12.bottomOffset: 10
*labelGadget12.bottomWidget: "separatorGadget3"
*labelGadget12.leftAttachment: "attach_form"
*labelGadget12.leftOffset: 10
*labelGadget12.topAttachment: "attach_none"
*labelGadget12.labelString: "FIND:"
*labelGadget12.alignment: "alignment_beginning"

*text_find_nome.class: textField
*text_find_nome.parent: form1
*text_find_nome.static: true
*text_find_nome.name: text_find_nome
*text_find_nome.x: 60
*text_find_nome.y: 311
*text_find_nome.width: 100
*text_find_nome.background: "#4f9f9f"
*text_find_nome.maxLength: 8
*text_find_nome.bottomAttachment: "attach_widget"
*text_find_nome.bottomOffset: 10
*text_find_nome.bottomWidget: "separatorGadget3"
*text_find_nome.leftAttachment: "attach_widget"
*text_find_nome.leftOffset: 0
*text_find_nome.leftWidget: "labelGadget12"
*text_find_nome.resizable: "false"
*text_find_nome.topAttachment: "attach_none"

*arrowButton3.class: arrowButton
*arrowButton3.parent: form1
*arrowButton3.static: true
*arrowButton3.name: arrowButton3
*arrowButton3.x: 210
*arrowButton3.y: 310
*arrowButton3.width: 34
*arrowButton3.height: 34
*arrowButton3.background: "#4f9f9f"
*arrowButton3.bottomAttachment: "attach_widget"
*arrowButton3.bottomOffset: 10
*arrowButton3.bottomWidget: "separatorGadget3"
*arrowButton3.leftAttachment: "attach_widget"
*arrowButton3.leftOffset: 5
*arrowButton3.leftWidget: "text_find_nome"
*arrowButton3.topAttachment: "attach_none"
*arrowButton3.activateCallback: {\
find_var_name(0);\
}

*arrowButton4.class: arrowButton
*arrowButton4.parent: form1
*arrowButton4.static: true
*arrowButton4.name: arrowButton4
*arrowButton4.x: 250
*arrowButton4.y: 310
*arrowButton4.width: 34
*arrowButton4.height: 34
*arrowButton4.background: "#4f9f9f"
*arrowButton4.bottomAttachment: "attach_widget"
*arrowButton4.bottomOffset: 10
*arrowButton4.bottomWidget: "separatorGadget3"
*arrowButton4.leftAttachment: "attach_widget"
*arrowButton4.leftOffset: 5
*arrowButton4.leftWidget: "arrowButton3"
*arrowButton4.topAttachment: "attach_none"
*arrowButton4.arrowDirection: "arrow_down"
*arrowButton4.activateCallback: {\
find_var_name(1);\
}

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.parent: form1
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.scrollingPolicy: "automatic"
*scrolledWindow2.x: 20
*scrolledWindow2.y: 130
*scrolledWindow2.width: 800
*scrolledWindow2.height: 210
*scrolledWindow2.leftAttachment: "attach_form"
*scrolledWindow2.leftOffset: 10
*scrolledWindow2.rightAttachment: "attach_form"
*scrolledWindow2.rightOffset: 10
*scrolledWindow2.topAttachment: "attach_widget"
*scrolledWindow2.topOffset: 5
*scrolledWindow2.topWidget: "bulletinBoard1"
*scrolledWindow2.background: "#4f9f9f"
*scrolledWindow2.bottomAttachment: "attach_widget"
*scrolledWindow2.bottomOffset: 10
*scrolledWindow2.bottomWidget: "text_find_nome"

*label_int_nome.class: labelGadget
*label_int_nome.parent: form1
*label_int_nome.static: true
*label_int_nome.name: label_int_nome
*label_int_nome.x: 293
*label_int_nome.y: 315
*label_int_nome.width: 77
*label_int_nome.height: 30
*label_int_nome.alignment: "alignment_beginning"
*label_int_nome.labelString: "Var. name:"
*label_int_nome.bottomAttachment: "attach_widget"
*label_int_nome.bottomOffset: 10
*label_int_nome.bottomWidget: "separatorGadget3"
*label_int_nome.leftAttachment: "attach_widget"
*label_int_nome.leftOffset: 30
*label_int_nome.leftWidget: "arrowButton4"
*label_int_nome.topAttachment: "attach_none"
*label_int_nome.resizable: "false"

*label_nome_var.class: labelGadget
*label_nome_var.parent: form1
*label_nome_var.static: true
*label_nome_var.name: label_nome_var
*label_nome_var.x: 393
*label_nome_var.y: 315
*label_nome_var.width: 97
*label_nome_var.height: 30
*label_nome_var.alignment: "alignment_beginning"
*label_nome_var.bottomAttachment: "attach_widget"
*label_nome_var.bottomOffset: 10
*label_nome_var.bottomWidget: "separatorGadget3"
*label_nome_var.leftAttachment: "attach_widget"
*label_nome_var.leftOffset: 10
*label_nome_var.leftWidget: "label_int_nome"
*label_nome_var.topAttachment: "attach_none"
*label_nome_var.labelString: ""
*label_nome_var.resizable: "false"

*label_int_descr.class: labelGadget
*label_int_descr.parent: form1
*label_int_descr.static: true
*label_int_descr.name: label_int_descr
*label_int_descr.x: 500
*label_int_descr.y: 315
*label_int_descr.width: 120
*label_int_descr.height: 30
*label_int_descr.alignment: "alignment_beginning"
*label_int_descr.bottomAttachment: "attach_widget"
*label_int_descr.bottomOffset: 10
*label_int_descr.bottomWidget: "separatorGadget3"
*label_int_descr.leftAttachment: "attach_widget"
*label_int_descr.leftOffset: 10
*label_int_descr.leftWidget: "label_nome_var"
*label_int_descr.topAttachment: "attach_none"
*label_int_descr.labelString: "Type and descr.:"
*label_int_descr.resizable: "false"

*label_tipo_e_descr.class: labelGadget
*label_tipo_e_descr.parent: form1
*label_tipo_e_descr.static: true
*label_tipo_e_descr.name: label_tipo_e_descr
*label_tipo_e_descr.x: 770
*label_tipo_e_descr.y: 320
*label_tipo_e_descr.width: 150
*label_tipo_e_descr.height: 30
*label_tipo_e_descr.alignment: "alignment_beginning"
*label_tipo_e_descr.bottomAttachment: "attach_widget"
*label_tipo_e_descr.bottomOffset: 10
*label_tipo_e_descr.bottomWidget: "separatorGadget3"
*label_tipo_e_descr.leftAttachment: "attach_widget"
*label_tipo_e_descr.leftOffset: 10
*label_tipo_e_descr.leftWidget: "label_int_descr"
*label_tipo_e_descr.rightAttachment: "attach_form"
*label_tipo_e_descr.rightOffset: 10
*label_tipo_e_descr.topAttachment: "attach_none"
*label_tipo_e_descr.labelString: ""
*label_tipo_e_descr.resizable: "false"

