/**********************************************************************
*
*       C Header:               pagresdef.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Jul 16 15:36:18 1998 %
*
**********************************************************************/
/*
   modulo pagresdef.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)pagresdef.h	5.1
*/
/*
   pagresdef.h
   
   contiene le definizioni delle risorse
*/

#ifndef _pagresdef_h
#define _pagresdef_h

/* risorse definite per il resource database del Context */

#define XlNproject                 "project"                      /* directory del file Context */
#define XlCProject                 "Project"
#define XlNdescription             "description"
#define XlCDescription             "Description"
#define XlNobjectLibraries         "objectLibraries"            /* directory librerie oggetti */
#define XlCObjectLibraries         "ObjectLibraries"
#define XlNanimatedIconLibraries   "animatedIconLibraries"     /* directory icone */
#define XlCAnimatedIconLibraries   "AnimatedIconLibraries"
#define XlNsimulator               "simulator"                    /* directory variabili run_time */
#define XlCSimulator               "Simulator"
#define XlNpages                   "pages"                    /* directory variabili run_time */
#define XlCPages                   "Pages"

#define XlNnumDisplay              "numDisplay"
#define XlCNumDisplay              "NumDisplay"
#define XlNdisplayList             "displayList"
#define XlCDisplayList             "DisplayList"

#define XlNhostName                "hostName"
#define XlCHostName                "HostName"

#define XlNhostNameS                "hostNameS"
#define XlCHostNameS                "HostNameS"

#define XtNpag_num                 "pag_num"
#define XtCPag_num                 "Pag_num"
#define XtNpage_list               "page_list"
#define XtCPage_list               "Page_list"
#define XtNiconlib_num             "iconlib_num"
#define XtCIconlib_num             "Iconlib_num"
#define XtNiconlib_list            "iconlib_list"
#define XtCIconlib_list            "Iconlib_list"
#define XtNiconlib_label           "iconlib_label"
#define XtCIconlib_label           "Iconlib_label"

/* risorse definite per il resource database delle pagine */
#define XtNnum_widget              "num_widget"
#define XtCNum_widget              "Num_widget"
#define XtDnum_widget              "num_widget"


#define XtNelenco_wid0               "elenco_wid0"
#define XtCElenco_wid0               "Elenco_wid0"
#define XtDelenco_wid0               "elenco_wid0"
#define XtNnextnum                   "nextnum"
#define XtCNextnum                   "Nextnum"
#define XtNnextnum                   "nextnum"


#define XlNlistChildren             "listChildren"
#define XlCListChildren             "ListChildren"

#define XlNnumFigli                 "numFigli"
#define XlCNumFigli                 "NumFigli"

/* nome della pagina */
#define XlNnomePag                  "nomePag"
#define XlCNomePag                  "NomePag"
#define XlDnomePag                  "Page name"

/* descrizione */
#define XlNdescrPag                 "top_descrizione"
#define XlCDescrPag                 "top_Descrizione"
#define XlDdescrPag                 "top_descrizione"
#define XlNdescrPag_2                 "top_descrizione_2"
#define XlCDescrPag_2                 "top_Descrizione_2"
#define XlDdescrPag_2                 "top_descrizione_2"
#define XlNdescrPag_3                 "top_descrizione_3"
#define XlCDescrPag_3                 "top_Descrizione_3"
#define XlDdescrPag_3                 "top_descrizione_3"
#define XlNdescrPag_4                 "top_descrizione_4"
#define XlCDescrPag_4                 "top_Descrizione_4"
#define XlDdescrPag_4                 "top_descrizione_4"

/* coord shell pagina */
#define XlNxPag                     "top_x"
#define XlCXPag                     "top_X"
#define XlDxPag                     "top_x"
#define XlNyPag                     "top_y"
#define XlCYPag                     "top_Y"
#define XlDyPag                     "top_y"

/* dimensioni della shell della Pagina */
#define XlNwidthPag                 "top_width"
#define XlCWidthPag                 "top_Width"
#define XlDwidthPag                 "top_width"
#define XlNheightPag                "top_height"
#define XlCHeightPag                "top_Height"
#define XlDheightPag                "top_height"
#define XlNtipoPag                  "top_tipo"
#define XlCTipoPag                  "top_Tipo"
#define XlDtipoPag                  "top_tipo"

/* dimensioni della drawing area della Pagina */
#define XlNwidthDraw                "drawing_width"
#define XlCWidthDraw                "Drawing_width"
#define XlDwidthDraw                "drawing_width"
#define XlNheightDraw               "drawing_height"
#define XlCHeightDraw               "Drawing_height"
#define XlDheightDraw               "drawing_height"

/* snap della pagina  */
#define XlNsnapPag                  "snap_pag"
#define XlCSnapPag                  "Snap_pag"
#define XlDsnapPag                  "snap_pag"


/* background drawing area */
#define XlNbackgroundDraw           "drawing_background"
#define XlCBackgroundDraw           "Drawing_background"
#define XlDbackgroundDraw           "drawing_background"

/* definizione del Context Tag Pagina */
#define XlNlistTagPag                  "listTagPag"
#define XlCListTagPag                  "ListTagPag"
#define XlNnextTagPag                   "nextTagPag"
#define XlCNextTagPag                    "NextTagPag"
#define XlDnextTagPag                   "nextTagPag"

/* definizioni della pagina Tag Reg */
#define XlNtagPag                      "tagPag"
#define XlCTagPag                      "TagPag"
#define XlDtagPag                      "tagPag"
#define XlNnextTagReg                  "nextTagReg"
#define XlCNextagReg                   "NextTagReg"
#define XlDnextTagReg                  "nextTagReg"
#define XlNnumTagReg                   "numTagReg"
#define XlCNumTagReg                   "NumTagReg"
#define XlDnumTagReg                   "numTagReg"

/*  definizioni per definire lo schema in uso o meno */
#define XlNschemeInUse                  "schemeInUse"
#define XlCSchemeInUse                  "SchemeInUse"
#define XlDschemeInUse                  "schemeInUse"

#define XlNgerarchia			"gerarchia"
#define XlCGerarchia			"Gerarchia"
#define XlDgerarchia			"gerarchia"
/* definizione per registrare la data della compilazione */
#define XlNcompilationDate                  "compilationDate"
#define XlCCompilationDate                  "CompilationDate"
#define XlDcompilationDate                  "compilationDate"

/* definizione per registrare la data della compilazione */
#define XlNregTaskSigla                     "regTaskSigla"
#define XlCRegTaskSigla                     "RegTaskSigla"
#define XlDregTaskSigla                     "regTaskSigla"

/* definizione per registrare la data della creazione della regolazione */
#define XlNregolationDate                  "regolationDate"
#define XlCRegolationDate                  "RegolationDate"
#define XlDregolationDate                  "regolationDate"

/* definizioni per la gestione della height della extension2
   della OperatingWindow. (Pagina tipo Stazioni)
*/
#define XlNheightExt2                  "height_ext2"
#define XlCHeightExt2                  "Height_ext2"
#define XlDheightExt2                  "height_ext2"

#endif
